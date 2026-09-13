# ADR 0002: Keep the active components together

Status: Accepted by the user
Recorded: 2026-09-13; incorporates the latest user decision.

## Decision

Keep Birdcage and Worldish in one repository for now. Keep the website alongside them. They have distinct responsibilities but coordinated changes during restoration are easier to build, test, and review together. Separate Python packages do not require separate Git repositories.

The website is still live according to the user; no website deployment was performed in this session. On 2026-09-13 the user explicitly requested publishing on GitHub and selected public visibility. The public repository https://github.com/jergas/ouroborus was created and configured as origin; main is the publication branch.

A future extraction of Birdcage could make sense if it gains independent users and releases. Revisit once the Python 3 baseline and interfaces are understood, preferably before public releases and issues/PRs accumulate. Git history can be filtered later, but commit hashes change and cross-component commits become partial histories; retain the complete original import/archive.

## Scope update from the user on 2026-09-13

- ouroborus-cpp was removed because it was largely irrelevant to the main project and only historically interesting.
- Removal is committed as a5ad657 (Remove ouroborus-cpp directory). Original contents remain in earlier Git history.
- /home/edgar/Projects/backups/ouroborus-cpp-20260913.tar.gz exists (about 34 MiB, checked 2026-09-13). Its presence was verified; its contents were not re-audited during this documentation task.
- Circadian remains in the repository and may be worth resurrecting. It has not been included in the Birdcage/Worldish Python 3 port or current test scope.
- No repeat removal or backup operation is pending merely because an old handoff suggested one.

README.md now reflects the removal of ouroborus-cpp and retention of Circadian.
