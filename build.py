#!/usr/bin/env python

import os
import sh
from mkdocs import config

dependent_repos = ['mynewt-documentation', 'mynewt-core', 'mynewt-newt', 'mynewt-newtmgr', 'mynewt-nimble']

def build(cwd, site_dir):

    cfg = config.load_config()

    # sanity check - the version dirs exist as named
    for version in cfg['extra']['versions']:
        if not 'separate' in version or not version['separate']:
            d = os.path.join('versions', version['dir'])
            print 'Verifying dir %s' % (d)
            if not os.path.isdir(d):
                print "The directory %s does not exist" % (d)
                return

    # sanity check - dependent_repos exist in '..'
    for repo in dependent_repos:
        d = os.path.join(cwd, '..', repo)
        print 'Verifying repo dependency in %s' % (d)
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
        if not 'separate' in version or not version['separate']:
            sh.mkdocs('build', '--site-dir', os.path.join(site_dir, version['dir']), _cwd = os.path.join("versions", version['dir']))
        else:
            repo_dir = os.path.join(cwd, '..', 'mynewt-documentation')
            sh.make('clean', _cwd = repo_dir)
            sh.make('docs', _cwd = repo_dir)
            sh.mv(os.path.join(repo_dir, '_build', 'html'), os.path.join(site_dir, version['dir']))
        if 'latest' in version and version['latest']:
            sh.ln('-s', version['dir'], 'latest', _cwd = site_dir)

if __name__ == '__main__':
    cwd = os.path.dirname(os.path.abspath(__file__))
    build(cwd, os.path.join(cwd, "site"))
