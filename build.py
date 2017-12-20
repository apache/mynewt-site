#!/usr/bin/env python

import os
import sh
from git import Repo
from mkdocs import config

def build(site_dir):
    # make sure there are no local mods outstanding
    repo = Repo(os.getcwd())
    if repo.is_dirty() or repo.untracked_files:
        print "ERROR: Your working directory has outstanding changes."
        print "Commit or stash them."
        return

    cfg = config.load_config()

    # sanity check that the version dirs exist as named
    for version in cfg['extra']['versions']:
        d = os.path.join('versions', version['dir'])
        print 'Verifying dir %s' % (d)
        if not os.path.isdir(d):
            print "The directory %s does not exist" % (d)
            return

    # sanity check - only one latest
    latest = False
    for version in cfg['extra']['versions']:
        if not latest and 'latest' in version and version['latest']:
            print 'Latest is %s' % (version['dir'])
            latest = True
        elif latest and 'latest' in version and version['latest']:
            print 'ERROR: More than one version is latest.'
            print 'Only one version can be latest: True.'
            print 'Check mkdocs.yml.'
            return

    print "Building site pages"
    sh.rm('-rf', site_dir)
    sh.mkdocs('build', '--clean', '--site-dir', site_dir)

    for version in cfg['extra']['versions']:
        print "Building doc pages for: %s" % (version['dir'])
        sh.mkdocs('build', '--site-dir', os.path.join(site_dir, version['dir']), _cwd = os.path.join("versions", version['dir']))
        if 'latest' in version and version['latest']:
            sh.ln('-s', version['dir'], 'latest', _cwd = site_dir)

    # Make sure old links still work
    sh.ln('-s', 'master', 'develop', _cwd = site_dir)

if __name__ == '__main__':
    build(os.path.join(os.path.dirname(os.path.abspath(__file__)), "site"))
