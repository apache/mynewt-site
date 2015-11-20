## How to Edit Docs  

### Objective

We will go through the process of downloading existing doccumentation and adding some content to a test document.

### Markdown, MkDocs, Mou

The Mynewt documentation you see on the Apache incubator website is a bunch of HTML files generated using MkDocs which is a simple static site generation tool geared towards building project documentation. You can read about it at [http://www.mkdocs.org](http://www.mkdocs.org). Documentation source files are written in Markdown, and configured with a single YAML configuration file. Markdown is a lightweight markup language with plain text formatting syntax designed so that it can be converted to HTML and many other formats using a tool (which in our case is MkDocs).

You do not need to install MkDocs unless you want to actually render your documentation in HTML in order to preview it before pushing your content to the remote repository. Typically, using a Markdown editor such as [Mou](http://25.io/mou/) is enough to check how it will look after the document has gone through MkDocs. Go ahead and download [Mou](http://25.io/mou/). If you are on a Windows machine, download the [editor of your choice](http://alternativeto.net/software/mou/?platform=windows).

Currently someone in the project is designated to use MkDocs to generate the HTML pages periodically after changes have been reviewed and accepted into the master branch.


### Access to the Apache repo


Get an account on Apache. You do not need an account to view the website or clone the repository but you need it to push changes to it.


### Making a local copy

* Copy the document source files into a local directory and look at the contents of the copied directory to get an idea of the directory structure. 

        $ git clone https://git-wip-us.apache.org/repos/asf/incubator-mynewt-site.git
        Cloning into 'incubator-mynewt-site'...
        remote: Counting objects: 330, done.
        remote: Compressing objects: 100% (263/263), done.
        remote: Total 330 (delta 120), reused 0 (delta 0)
        Receiving objects: 100% (330/330), 4.34 MiB | 830.00 KiB/s, done.
        Resolving deltas: 100% (120/120), done.
        Checking connectivity... done.
        $ ls
        incubator-mynewt-site
        $ ls incubator-mynewt-site/
        docs		images		mkdocs.yml
        
* Create a new branch to work on your documentation and move to that branch.

        $ git checkout -b <your-branch-name>


### File to be edited

The file you will edit is [try_markdown.md](./try_markdown.md).

### Editing an existing page 

* Open the application Mou.

* Open the file incubator-mynewt-site/docs/chapter1/try_markdown.md in Mou.

* Edit the last item on the list.

* Save and quit the application.

You may want to review the documentation organization back in [Home](../index.md) to remind you how to locate files easily. The corresponding directory tree structure is shown below.

      .
      ├── docs
      │   ├── chapter1
      │   │   ├── how_to_edit_docs.md
      │   │   ├── newt_concepts.md
      │   │   ├── pics
      │   │   │   ├── bottomview.png
      │   │   │   └── topview.png
      │   │   ├── project1.md
      │   │   └── try_markdown.md
      │   ├── chapter2
      │   │   ├── project2.md
      │   │   ├── project3.md
      │   │   ├── ... (more to be added)
      │   │   └── vocabulary.md
      │   ├── chapter3
      │   │   ├── newt_ops.md
      │   │   └── newt_tool_reference.md
      │   ├── chapter4
      │   │   ├── context_switch.md
      │   │   ├── event_queue.md
      │   │   ├── heap.md
      │   │   ├── mbufs.md
      │   │   ├── memory_pool.md
      │   │   ├── mutex.md
      │   │   ├── mynewt_os.md
      │   │   ├── port_os.md
      │   │   ├── sanity.md
      │   │   ├── semaphore.md
      │   │   ├── task.md
      │   │   ├── time.md
      │   │   └── ... (more to be added)
      │   ├── chapter5
      │   │   ├── bootloader.md
      │   │   ├── console.md
      │   │   ├── filesystem.md
      │   │   ├── shell.md
      │   │   ├── testutil.md
      │   │   └── ... (more to be added)
      │   ├── chapter6
      │   │   ├── dist.md
      │   │   └── ... (more to be added)
      │   ├── extra.css
      │   ├── images
      │   │   └── egg-logo.png
      │   └── index.md
      ├── images
      │   ├── asf_logo_wide.gif
      │   ├── content-bg.png
      │   └── egg-logo.png
      ├── mkdocs.yml


### Adding a new page

If you create a new file somewhere in the `docs` subdirectory to add a new page, you have to add a line in the `mkdocs.yml` file at the correct level. For example, if you add a new module named "Ethernet" by creating a new file named `ethernet.md` in the chapter5 subdirectory, you have to insert the following line under `Modules:` in the `mkdocs.yml` file.

        - 'Ethernet': 'chapter5/ethernet.md'

### Pushing changes to remote

* Check whether your remote git repository is set up.

        $ git remote -v
        origin	https://git-wip-us.apache.org/repos/asf/incubator-mynewt-site.git (fetch)
        origin	https://git-wip-us.apache.org/repos/asf/incubator-mynewt-site.git (push)

* If it is not, set it up. Otherwise, proceed to the next step.


        $ git remote add origin https://git-wip-us.apache.org/repos/asf/incubator-mynewt-site.git 
       
* Commit and push the changes to the remote repository. Instead of "Green Arrow" type in your username.

        $ git add -A 
        $ git commit -m "Green Arrow's first doc change"
        $ git push -u origin <your-branch-name>
        
* You can see the changed Markdown file if you traverse the tree on the git repository [ https://git-wip-us.apache.org/repos/asf/incubator-mynewt-site.git]( https://git-wip-us.apache.org/repos/asf/incubator-mynewt-site.git).

* A commit notification automatically goes out to the commits@mynewt.incubator.apache.org mailing list. The "upstream" manager pulls the notified changes, reviews it, and merges it to the master branch if all is well. Otherwise you get an email for further changes.


### Conversion to HTML

The conversion of the Markdown files to HTML for the website happens manually and statically using MkDocs. You cannot see automatic and immediate rendering in HTML upon making a change in the Markdown file. You can choose to stop here and proceed to changing other Markdown files in your branch.

### Local preview of HTML files

However, you have the option to download MkDocs and do a local conversion yourself to preview the pages using the built-in devserver that comes with MkDocs. But first you will have to install MkDocs for that. In order to install MkDocs you'll need Python installed on your system, as well as the Python package manager, pip. You can check if you have them already (usually you will).

        $ python --version
        Python 2.7.2
        $ pip --version
        pip 1.5.2
        $ pip install mkdocs

You will then run the built-in webserver from the root of the documentation directory using the command `mkdocs serve`. The root directory for documentation is `incubator-mynewt-site` or the directory with the `mkdocs.yml` file.

        $ ls
        docs		images		mkdocs.yml
        $ mkdocs serve
        
Then go to [http://127.0.0.1:8000](http://127.0.0.1:8000) to preview your pages and see how they will look on the website! Remember that the Myself website itself will not be updated.
        
For more information on MkDocs go to [http://www.mkdocs.org]. 