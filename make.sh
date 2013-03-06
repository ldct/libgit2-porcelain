#!/usr/bin/env bash

set -x

rm *~

gcc ./revwalk.c -lgit2 -o bin/revwalk
gcc ./revwalk-minimal.c -lgit2 -o bin/revwalk-minimal
gcc ./listrefs.c -lgit2 -o bin/listrefs
gcc ./general.c -lgit2 -o bin/general
gcc ./showindex.c -lgit2 -o bin/showindex
gcc ./listodb.c -lgit2 -o bin/listodb
gcc ./diff-cached.c -lgit2 -o bin/diff-cached
gcc ./diff.c -lgit2 -o bin/diff