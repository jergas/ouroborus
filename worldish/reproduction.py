"""Additional world-owned reproduction policies."""


def transfer_birth(organizer, parent):
    """Create a funded child atomically; preparation cannot consume prana.

    The parent funds exactly the child's initial energy. The child is already
    instantiated when published and activates at its next lifecycle visit.
    Callers serialize world updates, as the existing sequence schedulers do.
    """
    observer = getattr(organizer.generator, "observation", None)
    amount = organizer.specific.offspring_prana
    if type(amount) is not int or amount <= 0:
        raise ValueError("offspring_prana must be a positive integer")
    if parent.fatum["prayer"] != "GrantChild":
        return None
    if parent.agent.tellPrana() < amount:
        if observer is not None:
            observer.emit("birth_rejected", agent_id=parent.name, reason="insufficient_prana",
                          available=parent.agent.tellPrana(), required=amount)
        parent.fatum["prayer"] = "Live"
        return None

    from .placement import offspring_address
    child_name = None
    try:
        child_name = organizer.generator.generateGenotype(parent.fatum["code"], organizer.book)
        child = organizer.book[child_name]
        child.fatum.update(code=parent.fatum["code"], prana=amount,
                           mana=organizer.specific.mana,
                           address=offspring_address(organizer, parent, "transfer"), prayer="BeBirthed",
                           parent=parent.name,
                           generation=parent.fatum.get("generation", 0) + 1)
        from . import sound_globals
        if sound_globals.simWSound:
            from .agents_sound import VocalTract
            child.fatum["voice"] = VocalTract(child.fatum["address"][0], organizer.width)
        child.callModule()
        child.instantiateAgent(organizer.earth)
        if child.agent.tellPrana() != amount:
            raise ValueError("Child constructor must preserve transferred prana")
        organizer.earth.addAgent(child.agent)
    except BaseException:
        if observer is not None:
            observer.emit("birth_failed", agent_id=parent.name, child_id=child_name,
                          reason="preparation_failed", prana=parent.agent.tellPrana())
        if child_name is not None:
            child = organizer.book.pop(child_name, None)
            if child is not None and child.agent is not None:
                organizer.earth.removeAgent(child.agent)
        raise

    parent.agent.losePrana(amount)
    parent.fatum["prana"] = parent.agent.tellPrana()
    parent.fatum["prayer"] = "Live"
    child.fatum["birth_complete"] = True
    organizer.births += 1
    organizer.prana_transferred += amount
    organizer.max_generation = max(organizer.max_generation, child.fatum["generation"])
    if observer is not None:
        observer.born(child, transferred=True)
        observer.emit("transfer", agent_id=parent.name, child_id=child_name,
                      parent_debit=amount, child_credit=amount,
                      parent_prana_after=parent.agent.tellPrana())
    return child_name
