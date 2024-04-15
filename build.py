#!/usr/bin/env python

from __future__ import print_function
from os import path, listdir
import sh
from mkdocs import config
import yaml

# repos of products that are released together
mynewt_repos = ['mynewt-core', 'mynewt-newt', 'mynewt-newtmgr']
nimble_repo = 'mynewt-nimble'
revisioned_repos = [nimble_repo] + mynewt_repos[:]
dependent_repos = ['mynewt-documentation'] + revisioned_repos[:]

BSP_DIR = "hw/bsp"
BSP_ARCH_NAMES = {
    'arc': 'ARC',
    'cortex_m0': 'Cortex-M0',
    'cortex_m3': 'Cortex-M3',
    'cortex_m33': 'Cortex-M33',
    'cortex_m4': 'Cortex-M4',
    'cortex_m7': 'Cortex-M7',
    'mips': 'MIPS',
    'pic32': 'PIC32',
    'rv32imac': 'RISC-V',
}


class BSP:
    '''
    Stores data for Mynewt BSPs
    '''

    def __init__(self, name, url, maker, arch):
        self.name = name
        self.url = url
        self.maker = maker
        self._arch = arch

    def arch(self):
        return BSP_ARCH_NAMES[self._arch]

    def repr(self):
        return "{}(name={}, url={}, maker={})".format(
            self.__class__.__name__, self.name, self.url, self.maker)


def generate_supported_boards(filename, bsps):
    with open(filename, 'w') as f:
        f.write("<ul>\n")
        for bsp in bsps:
            f.write("<li>\n")
            f.write("<a href=\"{}\"> {} </a> from {} ({})\n".format(bsp.url,
                                                                    bsp.name,
                                                                    bsp.maker,
                                                                    bsp.arch()))
            f.write("</li>\n")
        f.write("</ul>\n")


def find_BSPs():
    bsp_dir = path.join(cwd, '../mynewt-core', BSP_DIR)
    if not path.isdir(bsp_dir):
        raise Exception("The directory %s does not exist".format(bsp_dir))
    bsps = []
    for bsp in listdir(bsp_dir):
        with open(path.join(bsp_dir, bsp, "bsp.yml"), 'r') as f:
            data = yaml.full_load(f)
            if data.get('bsp.exclude_site') == 1:
                print("{} has 'exclude_site' set, skipping".format(bsp))
                continue
            for k in ['bsp.name', 'bsp.url', 'bsp.maker', 'bsp.arch']:
                if k not in data:
                    print("{} is missing metadata".format(bsp))
                    break
            else:
                bsp = BSP(name=data['bsp.name'], url=data['bsp.url'],
                          maker=data['bsp.maker'], arch=data['bsp.arch'])
                bsps.append(bsp)
    bsps_sorted = sorted(bsps, key=lambda bsp: bsp.name.lower())
    return bsps_sorted


def build(cwd, site_dir):

    cfg = config.load_config()

    # sanity check - dependent_repos exist in '..'
    for repo in dependent_repos:
        d = path.join(cwd, '..', repo)
        print('Verifying repo dependency in {}'.format(d))
        if not path.isdir(d):
            print("The directory %s does not exist".format(d))
            return

    # return all extra repos to master in case last run failed
    for repo in revisioned_repos:
        repo_dir = path.normpath(path.join(cwd, '..', repo))
        sh.git('checkout', 'master', _cwd=repo_dir)

    # sanity check - only one latest
    latest = False
    latest_version = None
    for version in cfg['extra']['versions']:
        if not latest and 'latest' in version and version['latest']:
            print('Latest is {}'.format(version['label']))
            latest = True
            latest_version = version['label']
        elif latest and 'latest' in version and version['latest']:
            print('ERROR: More than one version is latest.')
            print('Only one version can be latest: True.')
            print('Check mkdocs.yml.')
            return

    print("Building site pages")
    sh.rm('-rf', site_dir)

    bsps = find_BSPs()
    generate_supported_boards("custom-theme/supported-boards.html", bsps)

    sh.mkdocs('build', '--clean', '--site-dir', site_dir)

    for version in cfg['extra']['versions']:
        print("Building doc pages for: {}".format(version['label']))

        if 'sha' not in version:
            sh.mkdocs('build', '--site-dir',
                      path.join(site_dir, version['dir']),
                      _cwd=path.join("versions", version['dir']))

        else:
            sha = version['sha']
            for repo in mynewt_repos:
                repo_dir = path.normpath(path.join(cwd, '..', repo))
                sh.git('checkout', sha, _cwd=repo_dir)

            sha = version['nimble_sha']
            nimble_dir = path.normpath(path.join(cwd, '..', nimble_repo))
            sh.git('checkout', sha, _cwd=nimble_dir)

            repo_dir = path.normpath(path.join(cwd, '..',
                                               'mynewt-documentation'))
            sh.make('clean', _cwd=repo_dir)
            sh.make('docs',
                    'O=-A cur_version={} -A latest_version={}'.format(
                        version['label'], latest_version), _cwd=repo_dir)
            sh.mv(path.join(repo_dir, '_build', 'html'),
                  path.join(site_dir, version['dir']))

        if 'latest' in version and version['latest']:
            sh.ln('-s', version['dir'], 'latest', _cwd=site_dir)


if __name__ == '__main__':
    cwd = path.dirname(path.abspath(__file__))
    build(cwd, path.join(cwd, "site"))
