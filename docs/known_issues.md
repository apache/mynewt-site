## Known Issues

Here is a list of known issues and workarounds:

1. `newt install` returns the following error:

        ReadDesc: No matching branch for apache-mynewt-core repo
        No matching branch for apache-mynewt-core repo 

    If you installed a binary version of newt 1.0 or built newt from source using Go version 1.7.5 or earlier, you might see this error because the apache-mynewt-core Git repository location changed due to Mynewt's graduation from an incubator project to an Apache top level project. Go does not support HTTP redirect in Go versions 1.7.5 or earlier.  You can use one of the following workarounds:

       **Workaround 1:** Edit the `project.yml` file and change the line `repo: incubator-mynewt-core` as shown in the following example to `repo: mynewt-core`:

            repository.apache-mynewt-core:
                type: github
                vers: 1-latest
       	        user: apache
                repo: incubator-mynewt-core

       **Workaround 2:** If you are buiding newt from source, use Go version 1.7.6 or higher to build newt. You can download Go from [https://golang.org/dl/](https://golang.org/dl/).
 
      


