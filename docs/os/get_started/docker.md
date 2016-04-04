## Everything You Need in a Docker Container

Docker provides a quick and easy way to get up and running with Mynewt. The
newt command line tool and the entire build toolchain is available in a single
docker container. The container is all that's needed to run your Mynewt based
application in the simulator.  Enabling USB2 with your docker installation will
allow you to load your application on a supported device.

### Install Docker
Install docker for your platform. [Mac OS X](https://docs.docker.com/mac/) / [Windows](https://docs.docker.com/windows/) / [Linux](https://docs.docker.com/linux/)

Make sure to double click the Docker Quickstart Terminal application if you're on Mac or Windows.

### Use the newt wrapper script
Use the newt wrapper script to invoke newt.  Create the following file, name it
`newt`, make it executable, and put it in your path.

```bash
#!/bin/bash

docker run -ti --rm --device=/dev/bus/usb --privileged -v $(pwd):/workspace -w /workspace mynewt/newt:latest /newt "$@"
```

This will allow you to run newt as if it was natively installed.  You can now
follow the normal tutorials using the newt wrapper script.

You can upgrade your container by running `docker pull mynewt/newt:latest` when
updates are made available.

If you plan on loading your application on an actual device, continue on to
configure USB2 support.

### Enable USB2 Support for Mac or Windows

#### Install VirtualBox extension pack
Docker uses a VirtualBox Linux VM to run containers.  A free VirtualBox
extension pack is required to enable USB2 support.  Download the [VirtualBox
5.0.16 Oracle VM VirtualBox Extension
Pack](http://download.virtualbox.org/virtualbox/5.0.16/Oracle_VM_VirtualBox_Extension_Pack-5.0.16-105871.vbox-extpack)
and double click to install

#### Enable USB2 and select your device
* The "default" VM created by docker-machine must first be stopped before you
  can enable USB2.  You can run the command `docker-machine stop default` or
  use the VirtualBox UI to stop the VM.
* Enable USB2 using the VirtualBox UI. Select the "default"
  VM->Settings->Ports->USB2 to enable USB2.   Add your device to the USB Device
  Filters to make the device visible in the docker container.  See the image below.

<img src="../pics/virtualbox_usb.jpg" width="728px" />

* Restart the "default" VM by running `docker-machine start default` or by
  using the VirtualBox UI.


