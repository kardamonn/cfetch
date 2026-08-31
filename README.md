# cfetch

!! THIS CODE IS AI-ASSISTED MEANING I DID USE AI TO HELP ME WHILE WRITING AND DEBUGGING IT !!

Building cfetch and installing it:

Run `make` from the source directory to build cfetch without installing it.

Run `sudo make install` (or `doas`, depending on which one you have installed)
to build and install cfetch system-wide.

Uninstalling cfetch:

Run `sudo make uninstall` (or `doas`, depending on which one you have installed)
from the source directory.

Custom logo:

You can put your own logo in:

`~/.config/cfetch/logo.txt`

If the directory doesn't exist, create it with:

`mkdir -p ~/.config/cfetch`

Then create the logo file:

`touch ~/.config/cfetch/logo.txt`

Put your ASCII logo inside the file.

If no custom logo is present, cfetch will use the default ASCII cat.

Changing the colors:

Yes I finally added border and label color changing.

First off make sure `~/.config/cfetch/config` exists
(If not present make it with `mkdir -p ~/.config/cfetch/` then cd into it with `cd ~/.config/cfetch/` and finally create the config file by running `touch config`.
inside the config you can change:
logo colors, border colors and label colors.

example config file:
label_color=blue
logo=color=green
border_color=magenta

Supported colors: black, red, green, yellow, blue, magenta, cyan, white.

License:

MIT License, see LICENSE for more info.

Known issues:

GPU detection is currently based on a small built-in PCI ID table.
Some GPUs may be displayed as "Unknown GPU (vendor:device)".

If your GPU is detected as unknown feel free to open an issue with the reported vendor/device ID and I'll fix it in my spare time.

Some package managers may not be detected. Currently cfetch supports: apk, dnf, dpkg, portage, pacman. 

If your package manager isn't detected feel free to open an issue with your package manager's name and I'll add it to the list.
