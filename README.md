libgit2-porcelain
=================

Playground for porcelain commands built on libgit2.

revwalk
-------
gcc ./revwalk.c -lgit2 -o bin/revwalk

walks the revision history from HEAD of the current git directory
