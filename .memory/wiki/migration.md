# SVN migration and preservation

Source: https://svn.code.sf.net/p/ouroborus/code/
UUID: b2e75cc2-c23a-0410-bd76-b3583853a6a7

The local Git import contains all 395 SVN revisions r1-r395. The archive also contains SVN revision 0. Author usernames were retained: angolero, cincoinister, corryn, el_erno, pablod, sat_tara, and vicm3. Git-svn email identifiers USERNAME@UUID are synthetic, not verified contact addresses.

Each imported message includes a git-svn-id trailer with the original SourceForge URL, revision, and UUID. The import tip is c85290d472406d22118b1f87a2ee1a7de718a1b7 (r395). History had no conventional trunk/branches/tags paths; the entire root was imported.

## Durable archive

/home/edgar/Projects/ouroborus-svn-archive contains repository.svndump, the restored SVN repository, original verbose log.xml, revision-map.tsv, verification.json and verify.py, a complete ouroborus.git.bundle, migration logs, README.md, and SHA256SUMS.

Verification compared author/committer identities, whole-second timestamps, messages, and complete file trees/contents/modes for every revision, reading 2,103 changed/copied file versions. SVN verification, Git fsck, bundle verification, and archive checksums passed at migration.

Git does not fully represent SVN properties, empty directories, copy/merge bookkeeping, or fractional timestamp precision. Those remain in the dump and original XML log. SourceForge server hooks, ACLs, tickets, and other project services were outside the exposed SVN archive and were not retrieved.

The working .git/svn metadata points to the local restored SVN repository; the bundle preserves Git objects/refs, not .git/svn. Keep both Git and the archive. No Git-hosting remote was published during the migration/port.

The later ouroborus-cpp removal and separate tarball are documented in adrs/0002-repository-boundaries.md.
