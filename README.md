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

I didn't bother implementing a color configuration, so the colors can be
changed directly in `output.c`.

The color definitions are near the top of the file, for example:

`#define COLOR_BORDER "\033[35m"`

Remember to rebuild and reinstall cfetch after changing the colors:

`sudo make install`

(or `doas make install` if you use doas).

License:

MIT License, see LICENSE for more info.

Known issues:

GPU detection is currently based on a small built-in PCI ID table.
Some GPUs may be displayed as "Unknown GPU (vendor:device)".

If your GPU is detected as unknown feel free to open an issue with the reported vendor/device ID and I'll fix it in my spare time.

Some package managers may not be detected, currently the fetch supports: apk, dnf, dpkg, portage, pacman. 

If your package manager isn't detected feel free to open an issue with your package manager's name and I'll add it to the list.
