## How to Edit Docs  

### Objective

We will go through the process of downloading existing doccumentation and adding some content to a test document.

### Markdown, MkDocs, Mou

The Mynewt documentation you see on the Apache incubator website is a bunch of HTML files generated using MkDocs which is a simple static site generation tool geared towards building project documentation. You can read about it at [http://www.mkdocs.org](http://www.mkdocs.org). Documentation source files are written in Markdown, and configured with a single YAML configuration file. Markdown is a lightweight markup language with plain text formatting syntax designed so that it can be converted to HTML and many other formats using a tool (which in our case is MkDocs).

You do not need to install MkDocs unless you want to actually render your documentation in HTML before pushing your content to the remote repository. Typically, using a Markdown editor such as [Mou](http://25.io/mou/) is enough to check how it will look after the document has gone through MkDocs. Go ahead and download [Mou](http://25.io/mou/). If you are on a Windows machine, download the [editor of your choice](http://alternativeto.net/software/mou/?platform=windows).

Currently someone in the project is designated to use MkDocs to generate the HTML pages periodically after changes have been reviewed and accepted by the group.

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

### Adding a new page

If you create a new file somewhere in the `docs` subdirectory to add a new page, you have to add a line in the `mkdocs.yml` file at the correct level. For example, if you add a new module named "Ethernet" by creating a new file named `ethernet.md` in the chapter5 subdirectory, you have to insert the following line under `Modules:` in the `mkdocs.yml` file.

        - 'Ethernet': 'chapter5/ethernet.md'

### Pushing changes to remote

* Set up your remote git repository

        $ git remote add origin https://git-wip-us.apache.org/repos/asf/incubator-mynewt-site.git
        $ git remote -v
        origin	https://git-wip-us.apache.org/repos/asf/incubator-mynewt-site.git (fetch)
        origin	https://git-wip-us.apache.org/repos/asf/incubator-mynewt-site.git (push)
        
* Commit and push the changes to the remote repository.

        $ git add -A 
        $ git commit -m "Green Arrow's first doc change"
        $ git push -u origin <your-branch-name>
        
 