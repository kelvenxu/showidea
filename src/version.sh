#!/bin/bash

file=gitversion.h

if [ $# == 1 ]
then
  file=$1/gitversion.h
fi

echo "#ifndef __GIT_VERSION_H__" > $file
echo "#define __GIT_VERSION_H__ 1" >> $file

echo "" >> $file

git log -n 1 --oneline | sed 's/^\([^ ]*\) .*/#define GIT_SHA1 "\1"/' >> $file
git show --format="%ci" | sed -n '1,1p' | sed 's/^\([^+]*\) .*/#define GIT_STAMP "\1"/' >> $file

echo "" >> $file

echo "#define BUILD_TIME ""\"`date +'%F %T'`\"" >> $file

echo "" >> $file

echo "#endif // __GIT_VERSION_H__" >> $file

