### How do I submit a bug?

If you do not have a JIRA account sign up for an account on [JIRA](https://issues.apache.org/jira/secure/Signup!default.jspa).

Submit a request to the @dev mailing list for your JIRA username to be added to the Apache Mynewt (MYNEWT) project. You can view the issues on JIRA for the MYNEWT project without an account but you need to log in for reporting a bug. 

Log in. Choose the "MYNEWT" project. Click on the "Create" button to create a ticket. Choose "Bug" as the Issue Type. Fill in the bug description, how it is triggered, and other details. 

### How do I request a feature?

If you do not have a JIRA account sign up for an account on [JIRA](https://issues.apache.org/jira/secure/Signup!default.jspa).

Submit a request to the @dev mailing list for your JIRA username to be added to the Apache Mynewt (MYNEWT) project. You can view the issues on JIRA for the MYNEWT project without an account but you need to log in for reporting a bug. 

Log in. Choose the "MYNEWT" project. Click on the "Create" button to create a ticket. Choose "Wish" as the Issue Type. Fill in the feature description,  benefits, and any other implementation details. Note in the description whether you want to work on it yourself. 

If you are not a committer and you wish to work on it, someone who is on the committer list will have to review your request and assign it to you. You will have to refer to this JIRA ticket in your pull request.

### I am not on the committer list. How do I submit a patch? 

You submit your proposed changes for your peers with committer status to review and merge. 

You may choose to submit patches in one of the two following ways:

1\. Fork the mirror on github.com to create your very own repo. Clone the forked repository into a local branch on your machine and make your changes. Push the branch to your fork on github. Then submit a pull request from that branch on your github repo:

```no-highlight
steps here
```

In the comment for the pull request, include a description of the changes you have made and why. Github will automatically notify everyone on the commits@mynewt.incubator.apache.org mailing list about the newly opened pull requests. You can open a pull request even if you don't think the code is ready for merging but want some discussion on the matter.
Upon receiving notification, one or more committers will review your work, ask for edits or clarifications, and merge when your proposed changes are ready.

2\.Use the `git format-patch` command to produce a patch file. Submit the patch (your code changes along with a diff from the old code) via email to the @dev mailing list. Summarize the issue and your work in the email. Regular project members will review your suggested patch and add it to the repository, acknowledging your contribution by referencing your name in the commit message.
