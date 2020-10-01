This is the site documentation for the Apache Mynewt project. It is built using
[MkDocs](http://www.mkdocs.org/).

This repo previously contained all documentation relating to Apache Mynewt. The
project documentation now resides in the
[mynewt-documentation](https://github.com/apache/mynewt-documentation) repo.
Code specific documentation is found in various mynewt-\* code specific repos.
Archived versions of the project documentation for releases 1.3.0 and earlier
are found under `versions`.

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
    - `mkdocs serve`
    - visit [http://localhost:8000](http://localhost:8000)
1. Submit a pull request.

## Deploying the latest docs

NOTE: These instructions assume that your workspace has all the mynewt repos cloned under the same parent directory.

### First follow the steps at mynewt-documentation

Most steps for releasing docs happen at the
[mynewt-documentation](https://github.com/apache/mynewt-documentation) repo.
Follow the instructions there first.

### Merge all changes and update

1. Merge pull requests to `master` on github.
1. Switch to the master branch.
    - `git checkout master`
1. While in master, do `git pull --rebase origin master` to pull the latest merged changes.

### Cut a new versioned documentation set (if appropriate)

NOTE: Skip these steps if you are just refreshing the current documentation or site.

1. Create a new _stanza_ in `mkdocs.yml` to reflect the new version.
    - At present `master` is the `latest` version.
    - And that should probably not change.
1. Add a new _stanza_ in `custom-theme/choose_doc_version.html` for the new version.
1. Add a link to `docs/documentation.md` for the new version.
1. Add a _Disallow_ section to `extras/robots.txt` for the new version so that
   these documents do not appear in search results before the latest docs.
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

The update process replaces an earlier version of all or part of a software
system with a newer release. It commonly consists of deactivation followed 
by installation. On some systems, such as on Linux when using the system's 
package manager, the old version of a software application is typically also
uninstalled as an automatic part of the process.

## Links to Documentation

For the deployed site a version prefix is added to the URL for each mkdocs page.
When developing there is no version prefix. If you want to link from a _site
page_ to a _documentation page_ you should prefix the URL with _/DOCSLINK/_ so
that the user is taken to the correct location when browsing in production.

## Link Checking

1. Grab a link checking tool like [Integrity](http://peacockmedia.software/mac/integrity/free.html)
1. Run: `./build.py --test-build`
1. Run: `./serve.py`
1. Point the link checker at http://localhost:8000/
