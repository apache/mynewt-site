#!/usr/bin/env python

import os
import click
import sh
from git import Repo, Git
from mkdocs import config
import fileinput

@click.command()
@click.option('-s', '--site-branch', default='master', help='Use this branch as source for the top level pages')

def build(site_branch):

    # make sure there are no local mods outstanding
    repo = Repo(os.getcwd())
    if repo.is_dirty() or repo.untracked_files:
        print "ERROR: Your working directory has outstanding changes."
        print "Commit or stash them."
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
    print "Building site pages from: %s..." % (site_branch)
    sh.mkdocs('build', '--clean')

    for version in cfg['extra']['versions']:
        mygit.checkout(version['branch'])
        deployVersion(version)

def deployVersion(version):
    mygit.checkout(version['branch'])
    buildTo(version['branch'])
    if version['latest']:
        buildTo('latest')

def buildTo(branch):
    print 'Building doc pages for: %s...' % (branch)
    branchCfg = config.load_config()
    if branchCfg['extra']['version'] != branch:
        updateConfigVersion(branch)
    sh.mkdocs('build', '--site-dir', 'site/%s' % (branch))
    if branchCfg['extra']['version'] != branch:
        sh.git('checkout', '--', 'mkdocs.yml')

def updateConfigVersion(branch):
    updated = False
    for line in fileinput.input('mkdocs.yml', inplace=True):
        line = line.rstrip()
        if line.find("    version:") == 0:
            line = "    version: '%s'" % (branch)
            updated = True
        print line
    assert updated, "Could not fix the version field on %s" % (branch)

if __name__ == '__main__':
    repo = Repo(os.getcwd())
    branch = repo.active_branch
    mygit = Git(os.getcwd())
    try:
        build()
    finally:
        mygit.checkout(branch.name)
