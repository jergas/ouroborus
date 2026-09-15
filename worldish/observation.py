"""Read-only organism inspection, prana accounting and bounded JSONL traces.

No observation path draws randomness or calls consuming notification methods
(such as hasEaten). Trace I/O failures disable recording, not the simulation.
"""
from collections import UserDict
from dataclasses import asdict
import hashlib
import json
from pathlib import Path
import random

TRACE_MODES = ("off", "events", "instructions")
MAX_INSPECT_TEXT = 8192
MAX_INSPECT_WORDS = 256
MAX_AGENT_CHOICES = 1024
MAX_TRACE_BYTES = 64 * 1024 * 1024
MAX_EVENT_BYTES = 256 * 1024


def validate_trace(mode, limit):
    if mode not in TRACE_MODES:
        raise ValueError("Unknown trace mode")
    if type(limit) is not int or not 1 <= limit <= 1_000_000:
        raise ValueError("Trace limit must be an integer from 1 to 1,000,000")


def stable_value(value):
    if value is None or isinstance(value, (str, int, float, bool)):
        return value
    if isinstance(value, (tuple, list)):
        return [stable_value(item) for item in value]
    if callable(value):
        return f"{value.__module__}.{value.__qualname__}"
    return str(value)


def digest(value):
    data = json.dumps(value, ensure_ascii=True, separators=(",", ":"), sort_keys=True)
    return hashlib.sha256(data.encode()).hexdigest()


class TraceWriter:
    def __init__(self, mode="off", limit=100_000, path="events.jsonl"):
        validate_trace(mode, limit)
        self.mode, self.limit = mode, limit
        self.count = 0
        self.bytes_written = 0
        self.truncated = False
        self.error = None
        self.file = None
        if mode != "off":
            try:
                self.file = Path(path).open("w", encoding="utf-8", buffering=1)
            except OSError as error:
                self.error = str(error)

    @property
    def active(self):
        return self.file is not None and not self.truncated and self.error is None

    def write(self, event):
        if not self.active:
            return
        try:
            data = json.dumps({"sequence": self.count, **event},
                              ensure_ascii=True, allow_nan=False) + "\n"
            size = len(data.encode("utf-8"))
            reason = ("events" if self.count >= self.limit else
                      "event_bytes" if size > MAX_EVENT_BYTES else
                      "total_bytes" if self.bytes_written + size > MAX_TRACE_BYTES else None)
            if reason:
                self.file.write(json.dumps({"event": "trace_limit", "reason": reason,
                                            "limit": self.limit, "tick": event.get("tick")}) + "\n")
                self.truncated = True
                self.close()
                return
            self.file.write(data)
            self.count += 1
            self.bytes_written += size
        except (OSError, TypeError, ValueError) as error:
            self.error = str(error)
            self.close()

    def close(self):
        if self.file is not None:
            try:
                self.file.close()
            except OSError as error:
                self.error = str(error)
            self.file = None

    def summary(self):
        return {"mode": self.mode, "events_written": self.count,
                "limit": self.limit, "truncated": self.truncated, "error": self.error,
                "bytes_written": self.bytes_written, "byte_limit": MAX_TRACE_BYTES,
                "event_byte_limit": MAX_EVENT_BYTES}


class Observation:
    def __init__(self, specific, language, options, metrics, table, launch=None):
        self.specific = specific
        self.language, self.options = language, options
        self.metrics, self.table = metrics, table
        self.tick = 0
        self.genomes = {}
        self.selected_id = ""
        self.selected_last = None
        self.founder_prana = 0
        self.preset_offspring_prana = 0
        self.transferred_prana = 0
        self.death_prana = 0
        self.source_net_change = 0
        self.trace = TraceWriter(getattr(specific, "trace_mode", "off"),
                                 getattr(specific, "trace_limit", 100_000))
        self.emit("run", schema=1, specificity=getattr(specific, "__name__", "unknown"),
                  language=language, execution=asdict(options),
                  launch=launch or {}, random_state=random.getstate(),
                  world={key: stable_value(getattr(specific, key, None)) for key in (
                      "size", "topology", "neighborhood", "rule", "automaton", "seed",
                      "avatars", "prana", "mana", "reproduction_policy", "offspring_prana",
                      "reproduction_threshold", "doomsday", "agentThreads", "agentThreadsNumber",
                      "annumDelay", "agentsDelay", "compiling", "seedCode")},
                  scheduling="sequential lifecycle visits unless experimental mode is selected")

    def emit(self, event, **values):
        self.trace.write({"tick": self.tick, "event": event, **values})

    def attach(self, entry, code):
        # Key by the full raw representation, never canonicalize synonymous DNA.
        key = digest({"language": self.language, "raw": code})
        if key not in self.genomes:
            raw = code if isinstance(code, str) else "".join(code or [])
            compact = raw if isinstance(code, list) else raw.replace(" ", "")
            words = [compact[i:i + 2] for i in range(0, len(compact), 2)]
            if self.language == "forager-v1":
                from .forager_vm import OPERATIONS
                decoded = [OPERATIONS[word].__name__ if word in OPERATIONS else "noop"
                           for word in words]
                meaning = {"language": self.language, "instructions": decoded,
                           "threshold": entry.reproduction_threshold}
            else:
                decoded = [str(self.table.get(word, "Unknown source word")) for word in words]
                meaning = {"language": self.language, "instructions": decoded,
                           "boilerplate": self.table.get("boilerplate", "")}
            info = {"genome_id": key, "program_id": digest(meaning), "raw": raw,
                    "words": words, "decoded": decoded, "language": self.language}
            self.genomes[key] = info
            self.emit("genome", genome_id=key, program_id=info["program_id"],
                      raw=code, language=self.language, decoded=decoded)
        entry.genome_info = self.genomes[key]
        entry.observation = self
        if entry.execution_metrics is not None:
            entry.execution_metrics = ObservedMetrics(entry.execution_metrics, entry, self)

    def born(self, entry, transferred=False):
        amount = entry.agent.tellPrana()
        parent = entry.fatum.get("parent")
        if transferred:
            self.transferred_prana += amount
        elif parent is None:
            self.founder_prana += amount
        else:
            self.preset_offspring_prana += amount
        self.emit("birth", agent_id=entry.name, parent=parent,
                  generation=entry.fatum.get("generation", 0),
                  genome_id=entry.genome_info["genome_id"], prana=amount,
                  address=entry.agent.tellAddress(),
                  funding="transfer" if transferred else "founder" if parent is None else "preset")

    def died(self, entry):
        amount = entry.agent.tellPrana()
        self.death_prana += amount
        self.emit("death", agent_id=entry.name, prana_removed=amount,
                  address=entry.agent.tellAddress())
        if self.selected_id == entry.name:
            self.selected_last = self.describe(entry, "dead")

    def live_finished(self, entry, before, failed=False):
        after = entry.agent.tellPrana()
        if entry.execution_options is None:
            self.source_net_change += after - before
        self.emit("live_error" if failed else "live", agent_id=entry.name,
                  prana_before=before, prana_after=after,
                  source_net_change=after - before if entry.execution_options is None else None,
                  lifecycle_request=entry.fatum.get("prayer"),
                  execution_state=dict(entry.execution_state) if entry.execution_options is not None else None)

    def ledger(self, bodies):
        actual = sum(body.tellPrana() for body in bodies)
        food = self.metrics["food_eaten"] * 5
        compute = self.metrics["compute_prana"]
        maintenance = self.metrics["maintenance_prana"]
        accounted = (self.founder_prana + self.preset_offspring_prana + food
                     - compute - maintenance - self.death_prana + self.source_net_change)
        return {"scope": "agent prana; CA food generation is outside this ledger",
                "founder_input": self.founder_prana,
                "preset_offspring_input": self.preset_offspring_prana,
                "food_input": food, "compute_spent": compute,
                "maintenance_spent": maintenance, "death_removed": self.death_prana,
                "source_net_change": self.source_net_change,
                "transferred": self.transferred_prana,
                "accounted_live_prana": accounted, "live_prana": actual,
                "balance_error": actual - accounted}

    def describe(self, entry, status="alive"):
        info = entry.genome_info
        words, decoded = info["words"], info["decoded"]
        budgeted = entry.execution_options is not None
        state = entry.execution_state if budgeted else {}
        ip = state.get("ip")
        from itertools import islice
        lines = [f"{'→' if index == ip else ' '} {index}: {word}  {instruction.strip()}"
                 for index, (word, instruction) in enumerate(islice(zip(words, decoded), MAX_INSPECT_WORDS))]
        return {"id": entry.name, "status": status, "tick": self.tick,
                "address": list(entry.agent.tellAddress()), "prana": entry.agent.tellPrana(),
                "lifecycle_request": entry.fatum.get("prayer"),
                "pending_request": state.get("prayer"), "instruction_position": ip,
                "compute_credits": state.get("credit"),
                "next_word": words[ip] if ip is not None and 0 <= ip < len(words) else None,
                "parent": entry.fatum.get("parent"), "generation": entry.fatum.get("generation", 0),
                "genome_id": info["genome_id"], "program_id": info["program_id"],
                "language": info["language"], "execution_method": self.options.execution_method,
                "raw_genome": info["raw"][:MAX_INSPECT_TEXT], "word_count": len(words),
                "decoded_display": "\n".join(lines)[:MAX_INSPECT_TEXT],
                "truncated": len(info["raw"]) > MAX_INSPECT_TEXT or len(words) > MAX_INSPECT_WORDS
                             or len("\n".join(lines)) > MAX_INSPECT_TEXT,
                "metrics": dict(entry.local_metrics) if budgeted else None,
                "energy_policy": self.options.energy_policy if budgeted else "source-defined"}

    def select(self, agent_id, book):
        self.selected_id = agent_id
        self.selected_last = None
        return self.inspection(book)

    def inspection(self, book):
        if self.selected_last and self.selected_last.get("status") == "dead":
            return self.selected_last
        if not self.selected_id:
            return {}
        entry = book.get(self.selected_id)
        if entry is not None and getattr(entry, "agent", None) is not None:
            self.selected_last = self.describe(entry)
        return self.selected_last or {"id": self.selected_id, "status": "unavailable", "tick": self.tick}

    def close(self):
        self.trace.close()


class ObservedMetrics(UserDict):
    """Shared totals, per-organism deltas, and optional instruction events."""
    def __init__(self, totals, entry, observation):
        self.data = totals
        self.entry, self.observation = entry, observation
        self.before = None

    def __setitem__(self, key, value):
        delta = value - self.data.get(key, 0)
        self.data[key] = value
        self.entry.local_metrics[key] = self.entry.local_metrics.get(key, 0) + delta

    def before_instruction(self, creature, state):
        if not self.observation.trace.active:
            self.before = None
            return
        self.before = {"prana": creature.tellPrana(), "address": creature.tellAddress(),
                       "state": dict(state), "metrics": dict(self.entry.local_metrics)}

    def after_instruction(self, creature, state):
        before = self.before
        if before is None:
            return
        self.before = None
        observer, entry = self.observation, self.entry
        ip = before["state"]["ip"]
        delta = {key: value - before["metrics"].get(key, 0)
                 for key, value in entry.local_metrics.items()}
        values = {"agent_id": entry.name, "ip": ip, "word": entry.genome_info["words"][ip],
                  "prana_before": before["prana"], "prana_after": creature.tellPrana(),
                  "address_before": before["address"], "address_after": creature.tellAddress(),
                  "pending_before": before["state"]["prayer"], "pending_after": state["prayer"],
                  "credit_before": before["state"]["credit"], "credit_after": state["credit"],
                  "costs": {key: delta.get(key, 0) for key in ("compute_prana", "maintenance_prana")},
                  "food_eaten": delta.get("food_eaten", 0)}
        if observer.trace.mode == "instructions":
            observer.emit("instruction", **values)
        elif (values["prana_before"] != values["prana_after"]
              or values["address_before"] != values["address_after"]
              or values["pending_before"] != values["pending_after"]
              or values["food_eaten"] or any(values["costs"].values())):
            observer.emit("action", **values)
