#!/bin/bash -
#===============================================================================
#
#          FILE: pre_git.sh
#
#         USAGE: ./pre_git.sh
#
#   DESCRIPTION: 
#
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: Charles Chiu (), charles.r.chiu@gmail.com
#  ORGANIZATION: 
#       CREATED: 2017年12月17日 16时40分41秒
#      REVISION:  ---
#===============================================================================

set -o nounset                              # Treat unset variables as an error
set -o xtrace
set -o errexit

echo "====================clear temp file"
echo "rm a.out"
note_home=./
find $note_home -name "a.out" | xargs -i rm -f {}
find $note_home -name "*.o" | xargs -i rm -f {}

