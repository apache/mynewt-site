# Image Manager




###Description

This library accepts incoming image management commands from newtmgr and acts on them.

Images can be uploaded, present images listed, and system can be told to switch to another image.

Currently the package assumes that there are 2 image slots, one active one and another one in standby. When new image is uploaded, it replaces the one in standby slot. This is the model for scenario when MCU has internal flash only, it executes the code from that flash, and there is enough space to store 2 full images.

Image manager interacts with bootloader by telling it to boot to a specific image. At the moment this has to be done by writing a file which contains a version number of the image to boot. Note that image manager itself does not replace the active image.

Image manager also can upload files to filesystem as well as download them.

Note that commands accessing filesystems (next boot target, file upload/download) will not be available unless project includes filesystem implementation.

###Data structures

N/A.

###List of Functions

<Comments such as these instructions are placed within angle brackets. List all the functions here. Note how the anchors work. You put the text you want to show up as a link within [] and the relevant #heading within (). Note that the header has to have at least 2 words for the anchor to work - that's how it is. "no-highlight" disables syntax highlighting. You can enable it for a particular language by specifying what the language is instead of "no-highlight". Be warned that this highlighting or no-highlighting specification may not show up nicely on Mou.>

The functions available in imgmgr are:

| Function | Description |
|---------|-------------|
| [imgr_ver_parse](imgr_ver_parse.md) | Parses character string containing specified image version number and writes that to given image_version struct. |
| [imgr_ver_str](imgr_ver_str.md) | Takes version string from specified image_version struct and formats it into a printable string. |
