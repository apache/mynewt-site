The Apache MyNewt site is built using [MkDocs](http://www.mkdocs.org/).

## Setup

Clone the repo:

    git clone https://github.com/apache/mynewt-site
    cd mynewt-site

Optional: it's a very good idea to use a `virtualenv`:

    virtualenv venv
    . venv/bin/activate

Install the requirements:

    pip install -r requirements.txt

## Submitting updates

1. Fork the repo.
1. Work on the `master` branch.
1. Preview your changes using MkDocs.
    * `mkdocs serve`
    * visit [http://localhost:8000](http://localhost:8000)
1. Submit a pull request.

## Releasing a versioned set of MyNewt documentation

NOTE: When it comes time to create a static versioned set of docs from the mynewt-documentation repo for v1.4.0, these instructions will need to be modified.

When a release of MyNewt OS and its associated tools occurs, a new version directory should be created to hold all docs pertaining to that release. The documentation in the git `master` branch of this repository always shows the latest docs under development. The following steps will create a documentation directory for a new release and make it available from the mynewt-site.

### Merge all changes and update

1. Merge pull requests to `master` on github.
1. Switch to the master branch.
    * `git checkout master`
1. While in master, do `git pull --rebase origin master` to pull the latest merged changes.

### Cut the new release documentation set

NOTE: Skip these steps if you are just refreshing the current documentation or site.

1. Create a new _stanza_ in `mkdocs.yml` to reflect the new version.
    * At present `master` is the `latest` version.
    * And that should probably not change.
1. Add a new _stanza_ in "custom-theme/choose_doc_version.html" for the new version.
1. Create a new directory in the versions directory for this new version.
    * Copy the latest docs directory and mkdocs.yml file into the new version directory
    * Set extra.version to the new version in the copied mkdocs.yml file
    * Create a symbolic link to the customer-theme
1. Commit these changes.

### Build

1. Run: `./build.py`

### Test

1. Run: `./serve.py`
1. Visit [http://localhost:8000](http://localhost:8000)

### Deploy

1. Run: `./deploy.sh build`
1. This will leave you on the `asf-site` branch.
1. Commit & push the changes.

The runtime-bot github user does a build every ~15 minutes and opens a Pull
Request against the asf-site branch if there are any changes. It is recommended
that the runtime-bot PRs are used to deploy changes to the site instead of PRs
from individual contributors. The runtime-bot PRs give us repeatable builds
using known versions of the build tools.

## Links to Documentation

For the deployed site a version prefix is added to the URL for each mkdocs page. When developing there is no version prefix. If you want to link from a _site page_ to a _documentation page_ you should prefix the URL with */DOCSLINK/* so that the user is taken to the correct location when browsing in production.

## Link Checking

1. Grab a link checking tool like [Integrity](http://peacockmedia.software/mac/integrity/free.html)
1. Run: `./build.py --test-build`
1. Run: `./serve.py`
1. Point the link checker at http://localhost:8000/
