#!/bin/bash -e

if [[ "$1" != "build"  ]]; then
    echo "Deploy the mynewt website"
    echo "Make sure git status is clean and run from the master branch"
    echo
    echo "Usage: $0 build"
    exit
fi

echo Remove unwanted html templates
find site -name "*.html" | xargs grep '{%.*%}' -l | xargs rm -f

echo Copy extra static pages into site
cp -a extras/* site/

echo Change git branch to asf-site
git checkout asf-site

echo Remove old content
ls | grep -v site | xargs rm -rf

echo Copy contents of site to serving directory
cp -a site/* .

echo ---
echo --- You are now on the asf-site branch
echo --- Review git diffs before committing
echo ---
git status
