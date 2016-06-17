The Apache MyNewt site is built using [MkDocs](http://www.mkdocs.org/).

## Setup
### For all contributors:
* Install MkDocs on your system.

### Additionally for mynewt-site committers:
* `pip install GitPython`
* `pip install sh`

## Submitting updates

1. Fork the repo.
1. Work on the `develop` branch.
1. Preview your changes using MkDocs.
    * `mkdocs serve`
    * visit http://localhost:8000
1. Submit a pull request.

## Releasing a versioned set of MyNewt documentation
When a new release of MyNewt occurs, the git `develop` branch of this repository should be in sync with that released version.

### Build
1. Merge `develop` to `master`.
1. Switch to the master branch.
    * `git checkout master`
1. Create a new _stanza_ in `mkdocs.yml` to reflect the new version.
    * and update the `latest` flag, only one release should be marked latest.
    * **and update version to match the new branch name.**
1. Commit this change.
1. Create a branch from master to reflect this new version.
1. Run: `./build.py`

### Test

### Deploy
