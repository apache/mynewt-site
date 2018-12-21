#!/bin/bash -x

# FIXME
exit 0

# Clone dependency repos
git clone --depth 1 https://github.com/apache/mynewt-documentation
git clone --depth 1 https://github.com/apache/mynewt-core
git clone --depth 1 https://github.com/apache/mynewt-newt
git clone --depth 1 https://github.com/apache/mynewt-newtmgr
git clone --depth 1 https://github.com/apache/mynewt-nimble

git clone git@github.com:apache/mynewt-site.git
cd mynewt-site
git status
./build.py
./deploy.sh build

if [[ -z $(git status -s | grep -v sitemap.xml) ]]; then
    echo "No changes"
    exit 0
fi

echo "There were changes. Create a PR"
git remote add fork git@github.com:runtime-bot/mynewt-site.git
git add .
git commit -m "asf-site update $(date)"
git push --force fork asf-site

curl -X POST -u runtime-bot:$GITHUB_TOKEN -d '{"title":"automated asf-site build","head":"runtime-bot:asf-site","base":"asf-site"}' https://api.github.com/repos/apache/mynewt-site/pulls
