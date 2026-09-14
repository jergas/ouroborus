"""Bounded newline-delimited JSON messages over a private socket pair."""
import json

VERSION = 1
MAX_MESSAGE = 1024 * 1024


def encode(message):
    payload = json.dumps({"version": VERSION, **message}, allow_nan=False).encode() + b"\n"
    if len(payload) > MAX_MESSAGE:
        raise ValueError("IPC message too large")
    return payload


class Decoder:
    def __init__(self):
        self.buffer = b""

    def feed(self, data):
        self.buffer += data
        messages = []
        while b"\n" in self.buffer:
            line, self.buffer = self.buffer.split(b"\n", 1)
            if len(line) > MAX_MESSAGE:
                raise ValueError("IPC message too large")
            message = json.loads(line)
            if not isinstance(message, dict) or message.get("version") != VERSION:
                raise ValueError("Unsupported IPC protocol")
            messages.append(message)
        if len(self.buffer) > MAX_MESSAGE:
            raise ValueError("IPC message too large")
        return messages
