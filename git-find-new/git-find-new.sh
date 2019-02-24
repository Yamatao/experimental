#!/usr/bin/env bash
 
usage() {
  echo "$0 <path> <word> - searches through new commits in a git repository for a specific word"
  echo "Example: $0 . \"fix crash\""
}
 
if [[ $# -ne 2 ]]; then
  usage
  exit 1
fi
 
REPO_PATH="$1"
WORDS="$2"
 
if [[ ! -d "$REPO_PATH/.git" ]]; then
  echo "Can't file .git directory in the given path"
  exit 1
fi
 
git --version >>/dev/null
if [[ $? != "0" ]]; then
  echo "Git is not installed"
  exit 1
fi
 
cd $REPO_PATH
git fetch origin master &>/dev/null
LOG=`git log --no-color --oneline master..origin/master`
 
IFS=$'\n'
 
for COMMIT in $LOG
do
  if echo "$COMMIT" | grep -i -q "$WORDS"; then
    echo "$COMMIT"
  fi
done