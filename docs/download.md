## Latest Apache Mynewt OS Release

### Latest Apache Mynewt Core OS Release

*   Release Version: Apache Mynewt 1.7.0
*   Release Date: August 4, 2019
*   [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-1.7.0)
*   [Release Download](https://www.apache.org/dyn/closer.lua/mynewt/apache-mynewt-1.7.0/)
 *  [core](https://www.apache.org/dyn/closer.lua/mynewt/apache-mynewt-1.7.0/apache-mynewt-core-1.7.0.tgz)
    [[PGP]](https://www.apache.org/dist/mynewt/apache-mynewt-1.7.0/apache-mynewt-core-1.7.0.tgz.asc)
    [[SHA512]](https://www.apache.org/dist/mynewt/apache-mynewt-1.7.0/apache-mynewt-newt-1.7.0.tgz.sha512)
 *   [newt](https://www.apache.org/dyn/closer.lua/mynewt/apache-mynewt-1.7.0/apache-mynewt-newt-1.7.0.tgz)
    [[PGP]](https://www.apache.org/dist/mynewt/apache-mynewt-1.7.0/apache-mynewt-newt-1.7.0.tgz.asc)
    [[SHA512]](https://www.apache.org/dist/mynewt/apache-mynewt-1.7.0/apache-mynewt-newt-1.7.0.tgz.sha512)

### Latest Apache Mynewt NimBLE (Bluetooth Stack) Release

Mynewt's Bluetooth stack is now a separate release with a porting layer that allows it to be easily ported to another OS!

*   Release Version: Apache NimBLE 1.2.0
*   Release Date: August 4, 2019
*   [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-NimBLE-1.2.0)
*   [Release Download](https://www.apache.org/dyn/closer.lua/mynewt/apache-nimble-1.2.0/apache-mynewt-nimble-1.2.0.tgz)
    [[PGP]](https://www.apache.org/dist/mynewt/apache-nimble-1.2.0/apache-mynewt-nimble-1.2.0.tgz.asc)
    [[SHA512]](https://www.apache.org/dist/mynewt/apache-nimble-1.2.0/apache-mynewt-nimble-1.2.0.tgz.sha512)

#### Fresh install

If you are brand new to Mynewt, go to [Quick Start](/latest/get_started/). The Newt tool will automatically download the latest release.

If you have already installed the Newt tool but not started any project yet, go to [Create Your First Project](/latest/get_started/project_create.html). The Newt tool will automatically download the latest release.

#### Upgrade

If you have already installed the Newt tool and started a project that installed a previous version of Apache Mynewt, upgrade using Newt tool:

```
$ newt upgrade
```

### Code in development

While the use of one of the official releases listed above is generally recommended, you may be interested in seeing work in progress.

The most recent code that is fairly stable over the full OS resides in the `master` branch of the Mynewt git repository. You may view or fork the repositories for Mynewt OS and Newt Tool from the Apache mirror on github.com.

*   [Apache Mynewt OS mirror on github.com](https://github.com/apache/incubator-mynewt-core/tree/master)
*   [Apache Newt Tool mirror on github.com](https://github.com/apache/incubator-mynewt-newt/tree/master)

The most recent code to support a major feature (e.g. Bluetooth 5) can be found in a long-lived feature branch dedicated to that feature (bluetooth5, in the example for Bluetooth 5) and not the master. If you are interested in seeing the latest code for that feature, you can clone the desired branch using git:

```
$ git clone git://github.com/apache/incubator-mynewt-core.git -b <feature-branch-name>
$ git clone git://github.com/apache/incubator-mynewt-newt.git -b <feature-branch-name>
```

<br>

For general information on using Git at Apache, go to https://git-wip-us.apache.org.

<br>

### Prior Releases

#### Apache Mynewt Core

*   Apache Mynewt 0.8.0-b2-incubating, [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-0.8.0-b2-incubating), [Release Archive](https://archive.apache.org/dist/incubator/mynewt/apache-mynewt-0.8.0-b2-incubating/)
*   Apache Mynewt 0.8.0-incubating, [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-0.8.0-incubating), [Release Archive](https://archive.apache.org/dist/incubator/mynewt/apache-mynewt-0.8.0-incubating/)
*   Apache Mynewt 0.9.0-incubating, [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-0.9.0-incubating), [Release Archive](https://archive.apache.org/dist/incubator/mynewt/apache-mynewt-0.9.0-incubating/)
*   Apache Mynewt 1.0.0-b1-incubating, [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-1.0.0-b1-incubating), [Release Archive](https://archive.apache.org/dist/incubator/mynewt/apache-mynewt-1.0.0-b1-incubating/)
*   Apache Mynewt 1.0.0-b2-incubating, [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-1.0.0-b2-incubating), [Release Archive](https://archive.apache.org/dist/incubator/mynewt/apache-mynewt-1.0.0-b2-incubating/)
*   Apache Mynewt 1.0.0-incubating, [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-1.0.0-incubating), [Release Archive](https://archive.apache.org/dist/incubator/mynewt/apache-mynewt-1.0.0-incubating/)
*   Apache Mynewt 1.1.0, [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-1.1.0), [Release Archive](https://archive.apache.org/dist/mynewt/apache-mynewt-1.1.0/)
*   Apache Mynewt 1.2.0, [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-1.2.0), [Release Archive](https://archive.apache.org/dist/mynewt/apache-mynewt-1.2.0/)
*   Apache Mynewt 1.3.0 [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-1.3.0), [Release Archive](https://www.apache.org/dyn/closer.lua/mynewt/apache-mynewt-1.3.0)
*   Apache Mynewt 1.4.0 [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-1.4.0), [Release Archive](https://www.apache.org/dyn/closer.lua/mynewt/apache-mynewt-1.4.0)
*   Apache Mynewt 1.4.1 [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-1.4.1), [Release Archive](https://www.apache.org/dyn/closer.lua/mynewt/apache-mynewt-1.4.1)
*   Apache Mynewt 1.5.0 [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-1.5.0), [Release Archive](https://www.apache.org/dyn/closer.lua/mynewt/apache-mynewt-1.5.0)
*   Apache Mynewt 1.6.0 [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-1.6.0), [Release Archive](https://www.apache.org/dyn/closer.lua/mynewt/apache-mynewt-1.6.0)

#### Apache Mynewt NimBLE (Bluetooth Stack)

*   Apache NimBLE 1.0.0 [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-1.4.0), [Release Archive](https://www.apache.org/dyn/closer.lua/mynewt/apache-nimble-1.0.0)
*   Apache NimBLE 1.1.0 [Release Notes](https://cwiki.apache.org/confluence/display/MYNEWT/RN-NimBLE-1.1.0), [Release Archive](https://www.apache.org/dyn/closer.lua/mynewt/apache-nimble-1.1.0)

<br>
<br>
