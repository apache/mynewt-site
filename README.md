The Apache MyNewt site is built using [MkDocs](http://www.mkdocs.org/).

## Setup

Clone the repo:

    git clone https://github.com/apache/incubator-mynewt-site
    cd incubator-mynewt-site

Optional: it's a very good idea to use a `virtualenv`:

    virtualenv venv
    . venv/bin/activate

Install the requirements:

    pip install -r requirements.txt

## Submitting updates

1. Fork the repo.
1. Work on the `develop` branch.
1. Preview your changes using MkDocs.
    * `mkdocs serve`
    * visit [http://localhost:8000](http://localhost:8000)
1. Submit a pull request.

## Releasing a versioned set of MyNewt documentation
When a new release of MyNewt OS and its associated tools occurs, the documentation in the git `develop` branch of this repository should be in sync with the released version. The following steps will create a documentation branch for the release and make it available as the default documentation from the mynewt-site.

### Build

1. Merge pull requests to `develop` on github.
1. While in `develop`, do 'git pull --rebase origin develop` to pull the latest merged changes.
1. Switch to the master branch.
    * `git checkout master`
1. Create a new _stanza_ in `mkdocs.yml` to reflect the new version.
    * and update the `latest` flag, only one release should be marked latest.
    * **and update version to match the new branch name.**
1. Commit this change.
1. Create a branch from master to reflect this new version.
1. Run: `./build.py`

### Test

1. Run: `./serve.py`
1. Visit [http://localhost:8000](http://localhost:8000)

### Deploy

1. Run: `./deploy.sh`
1. This will leave you on the `asf-site` branch.
1. Commit & push the changes.

## Links to Documentation

For the deployed site a version prefix is added to the URL for each mkdocs page. When developing there is no version prefix. If you want to link from a _site page_ to a _documentation page_ you should prefix the URL with */DOCSLINK/* so that the user is taken to the correct location when browsing in production.

## Link Checking

1. Grab a link checking tool like [Integrity](http://peacockmedia.software/mac/integrity/free.html)
1. Run: `./build.py --test-build`
1. Run: `./serve.py`
1. point the link checker at http://localhost:8000/
