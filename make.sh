#!/usr/bin/env bash

set -x

rm *~

gcc ./revwalk.c -lgit2 -o bin/revwalk
gcc ./listrefs.c -lgit2 -o bin/listrefs
gcc ./general.c -lgit2 -o bin/general
gcc ./showindex.c -lgit2 -o bin/showindex
gcc ./listodb.c -lgit2 -o bin/listodb
gcc ./diff-head-index.c -lgit2 -o bin/diff-head-index
gcc ./diff-index-workdir.c -lgit2 -o bin/diff-index-workdir
gcc ./diff-head-workdir.c -lgit2 -o bin/diff-head-workdir