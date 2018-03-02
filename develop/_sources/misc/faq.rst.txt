FAQ
---

Here are some lists, grouped by categories, of frequently asked
questions.

Mynewt software questions:
^^^^^^^^^^^^^^^^^^^^^^^^^^
.. contents::
  :local:
  :depth: 1

How do I reduce the code size for my Mynewt image?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Please refer to the tutorial documentation on `reducing application code size <https://github.com/apache/mynewt-site/blob/master/docs/os/tutorials/codesize.md>`_.

I'm having issues using Newt Manager with the Adafruit nRF52DK. What do I do?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

There are two things you will need to do to fix any issues you encounter when working with the Adafruit nRF52DK and Newt Manager:

1) Specify a reduced MTU:

   You can specify the reduced MTU by adding ``mtu=128`` to your connection string. The reason for this change is that MTU is the serial boot loader used to have a smaller receive buffer (128 bytes). The newtmgr tool sends larger image chunks by default, so specifying the MTU will reduce the image size. 
\

2) Indicate that the existing image should not be erased:

   This is accomplished with the ``-e`` command line option. Your command line should look similar to the following:
   
   ``$ newtmgr --conntype serial --connextra 'dev=/dev/ttyUSB0,mtu=128' image upload -e <image-path>``
   
   This change is needed because the serial boot loader doesn't support the standalone "erase image" command - as a result, it drops the request. The newtmgr image upload command starts by sending an erase command, then times out when it doesn't receive a response. The older version of newtmgr would use smaller chunk size for images, and it did not send the standalone erase command. When newtmgr was changed in versions 1.2 and 1.3, the serial boot loader changed along with it. The latest newtmgr is not compatible with an older version of the boot loader (which your board will probably ship with) without the above workarounds.
   
Administrative questions:
^^^^^^^^^^^^^^^^^^^^^^^^^

.. contents::
  :local:
  :depth: 1

How do I submit a bug?
~~~~~~~~~~~~~~~~~~~~~~

If you do not have a JIRA account sign up
for an account on
`JIRA <https://issues.apache.org/jira/secure/Signup!default.jspa>`__.

Submit a request to the @dev mailing list for your JIRA username to be
added to the Apache Mynewt (MYNEWT) project. You can view the issues on
JIRA for the MYNEWT project without an account but you need to log in
for reporting a bug.

Log in. Choose the "MYNEWT" project. Click on the "Create" button to
create a ticket. Choose "Bug" as the Issue Type. Fill in the bug
description, how it is triggered, and other details.

How do I request a feature?
~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you do not have a JIRA account sign up for an account on
`JIRA <https://issues.apache.org/jira/secure/Signup!default.jspa>`__.

Submit a request to the @dev mailing list for your JIRA username to be
added to the Apache Mynewt (MYNEWT) project. You can view the issues on
JIRA for the MYNEWT project without an account but you need to log in
for reporting a bug.

Log in. Choose the "MYNEWT" project. Click on the "Create" button to
create a ticket. Choose "Wish" as the Issue Type. Fill in the feature
description, benefits, and any other implementation details. Note in the
description whether you want to work on it yourself.

If you are not a committer and you wish to work on it, someone who is on
the committer list will have to review your request and assign it to
you. You will have to refer to this JIRA ticket in your pull request.

I am not on the committer list. How do I submit a patch?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**You submit your proposed changes for your peers with committer status
to review and merge.**

The process to submit a Pull Request on github.com is described on the
`Confluence page for the
project <https://cwiki.apache.org/confluence/display/MYNEWT/Submitting+Pull+Requests>`__.

I am a committer in the project. Can I merge my own Pull Request into the git repository?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Yes, but only if your Pull Request has been reviewed and approved by
another committer in Apache Mynewt. The process to merge a Pull Request
is described on the `Confluence page for the
project <https://cwiki.apache.org/confluence/display/MYNEWT/Merging+Pull+Requests>`__.

I would like to make some edits to the documentation. What do I do?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You submit your proposed changes for your peers with committer status
to review and merge.

Each Mynewt repository has its own set of related documentation in the docs/ folder. The
overall project documentation is in `mynewt-documentation <https://github.com/apache/mynewt-documentation>`__
on github.com.

Navigate to the file you wish to edit on github.com. All the technical
documentation is in reStructuredText files under the ``/docs`` directory. Click
on the pencil icon ("Edit the file in your fork of this project") and
start making changes.

Click the green "Propose file change" button. You will be directed to
the page where you can start a pull request from the branch that was
created for you. The branch is gets an automatic name ``patch-#`` where
# is a number. Click on the green "Compare & pull request" to open the
pull request.

In the comment for the pull request, include a description of the
changes you have made and why. Github will automatically notify everyone
on the commits@mynewt.apache.org mailing list about the newly opened
pull requests. You can open a pull request even if you don't think the
code is ready for merging but want some discussion on the matter.

Upon receiving notification, one or more committers will review your
work, ask for edits or clarifications, and merge when your proposed
changes are ready.

If you want to withdraw the pull request simply go to your fork
``https://github.com/<your github username>/mynewt-documentation`` and click on
"branches". You should see your branch under "Your branches". Click on
the delete icon.

I would like to make some edits to the documentation but want to use an editor on my own laptop. What do I do?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You submit your proposed changes for your peers with committer status
to review and merge.

Go to the `documentation
mirror <https://github.com/apache/mynewt-documentation>`__ on github.com. You
need to create your own fork of the repo in github.com by clicking on
the "Fork" button on the top right. Clone the forked repository into
your laptop (using ``git clone`` from a terminal or using the download
buttons on the github page)and create a local branch for the edits and
switching to it (using ``git checkout -b <new-branchname>`` or GitHub
Desktop).

Make your changes using the editor of your choice. Push that branch to
your fork on github. Then submit a pull request from that branch on your
github fork.

The review and merge process is the same as other pull requests
described for earlier questions.
