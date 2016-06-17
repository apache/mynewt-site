#!/usr/bin/env python

import os
import click
import sh
from git import Repo, Git
from mkdocs import config

@click.command()
@click.option('-s', '--site-branch', default='master', help='Use this branch as source for the top level pages')
@click.option('--dirty', default=False, is_flag=True, help='Allow outstanding modifications in the working directory')

def build(site_branch, dirty):

    # make sure there are no local mods outstanding
    repo = Repo(os.getcwd())
    if not dirty and (repo.is_dirty() or repo.untracked_files):
        print "ERROR: Your working directory has outstanding changes."
        print "If you are sure this is ok run again with --dirty."
        return

    mygit = Git(os.getcwd())
    cfg = config.load_config()

    # sanity check that the version branches exist as named
    for version in cfg['extra']['versions']:
        print 'Verifying branch %s' % (version['branch'])
        mygit.checkout(version['branch'])

    # sanity check - only one latest
    latest = False
    for version in cfg['extra']['versions']:
        if not latest and version['latest']:
            print 'Latest is %s' % (version['branch'])
            latest = True
        elif latest and version['latest']:
            print 'ERROR: More than one version is latest.'
            print 'Only one version can be latest: True.'
            print 'Check mkdocs.yml.'
            return

    mygit.checkout(site_branch)
    print "Building the top level site pages (from %s)..." % (site_branch)
    sh.mkdocs('build', '--clean')

    for version in cfg['extra']['versions']:
        mygit.checkout(version['branch'])
        print 'Building docs for: %s...' % (version['branch'])
        sh.mkdocs('build', '--site-dir', 'site/%s' % (version['branch']))
        if version['latest']:
            print 'Building latest...'
            sh.mkdocs('build', '--site-dir', 'site/latest')

if __name__ == '__main__':
    repo = Repo(os.getcwd())
    branch = repo.active_branch
    mygit = Git(os.getcwd())
    try:
        build()
    finally:
        mygit.checkout(branch.name)
