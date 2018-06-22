## Latest Apache Mynewt OS Release

### Latest Apache Mynewt Core OS Release

* Release Version: Apache Mynewt 1.4.0
* Release Date: June 13, 2018
* [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-1.4.0)
* [Release Download](http://www.apache.org/dyn/closer.lua/mynewt/apache-mynewt-1.4.0)

### Latest Apache Mynewt NimBLE (Bluetooth Stack) Release

We are pleased to announce the first release of Mynewt's Bluetooth stack. It now has a Porting Layer that allows the stack to be easily ported to another OS!

* Release Version: Apache NimBLE 1.0.0 (First separate release!) 
* Release Date: June 13, 2018
* [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-1.4.0)
* [Release Download](http://www.apache.org/dyn/closer.lua/mynewt/apache-nimble-1.0.0)

#### Fresh install

If you are brand new to Mynewt, go to [Quick Start](os/get_started/get_started/). The Newt tool will automatically download the latest release.

If you have already installed the Newt tool but not started any project yet, go to [Create Your First Project](/DOCSLINK/os/get_started/project_create/). The Newt tool will automatically download the latest release.

#### Upgrade

If you have already installed the Newt tool and started a project that installed a previous version of Apache Mynewt,  upgrade using Newt tool:

```
$ newt upgrade
```

### Code in development

While the use of one of the official releases listed above is generally recommended, you may be interested in seeing work in progress.

The most recent code that is fairly stable over the full OS resides in the `master` branch of the Mynewt git repository. You may view or fork the repositories for Mynewt OS and Newt Tool from the Apache mirror on github.com.

* [Apache Mynewt OS mirror on github.com](https://github.com/apache/incubator-mynewt-core/tree/master)
* [Apache Newt Tool mirror on github.com](https://github.com/apache/incubator-mynewt-newt/tree/master)

The most recent code to support a major feature (e.g. Bluetooth 5) can be found in a long-lived feature branch dedicated to that feature (bluetooth5, in the example for Bluetooth 5) and not the master. If you are interested in seeing the latest code for that feature,  you can clone the desired branch using git:

```
$ git clone git://github.com/apache/incubator-mynewt-core.git -b <feature-branch-name>
$ git clone git://github.com/apache/incubator-mynewt-newt.git -b <feature-branch-name>
```

<br>

For general information on using Git at Apache, go to https://git-wip-us.apache.org.

<br>

### Prior Releases

#### Apache Mynewt Core

* Apache Mynewt 0.8.0-b2-incubating, [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-0.8.0-b2-incubating), [Release Archive](https://archive.apache.org/dist/incubator/mynewt/apache-mynewt-0.8.0-b2-incubating/)
* Apache Mynewt 0.8.0-incubating, [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-0.8.0-incubating), [Release Archive](https://archive.apache.org/dist/incubator/mynewt/apache-mynewt-0.8.0-incubating/)
* Apache Mynewt 0.9.0-incubating, [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-0.9.0-incubating), [Release Archive](https://archive.apache.org/dist/incubator/mynewt/apache-mynewt-0.9.0-incubating/)
* Apache Mynewt 1.0.0-b1-incubating, [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-1.0.0-b1-incubating), [Release Archive](https://archive.apache.org/dist/incubator/mynewt/apache-mynewt-1.0.0-b1-incubating/)
* Apache Mynewt 1.0.0-b2-incubating, [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-1.0.0-b2-incubating), [Release Archive](https://archive.apache.org/dist/incubator/mynewt/apache-mynewt-1.0.0-b2-incubating/)
* Apache Mynewt 1.0.0-incubating, [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-1.0.0-incubating), [Release Archive](https://archive.apache.org/dist/incubator/mynewt/apache-mynewt-1.0.0-incubating/)
* Apache Mynewt 1.1.0, [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-1.1.0), [Release Archive](https://archive.apache.org/dist/mynewt/apache-mynewt-1.1.0/)
* Apache Mynewt 1.2.0, [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-1.2.0), [Release Archive](https://archive.apache.org/dist/mynewt/apache-mynewt-1.2.0/)
* Apache Mynewt 1.3.0 [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-1.3.0), [Release Archive](http://www.apache.org/dyn/closer.lua/mynewt/apache-mynewt-1.3.0)

#### Apache Mynewt NimBLE (Bluetooth Stack)

No archives yet


<br>
<br>
