# PlatformFolders
A self contained C++ abstraction library so that you do not need to have Windows and Linux specific code to look for special directories

# Rationale
There are a lot of platform abstraction libraries available. You can get graphics abstraction libraries, GUI abstraction libraries and file abstraction libraries.

But folder abstraction seems to be more difficult.
My problem was that the code that found the place to save data was platform dependent. This cluttered my code and often I would not discover that it did not compile until moving it to the different platforms.

# Windows support
For Windows the folders are fetched using SHGetFolderPath.
The amount of supported folders differ from Windows version and this library targets XP and newer... and I'll drop XP support very soon. 
Currently "Save Games" and "Downloads" should not be used as they are undefined on XP. 

# Linux support
In Linux a lot of these folders are not official defined. However this library uses XDG user dirs.

# Mac OS X support
Currently not supported. The Mac OS X C++ documentation is very slim and I could not get FSFindFolder to work (I need to link against something). As a result you will simply get the XDG defined folders if you try to use compile it on Mac.
If someone could tell me what I need to link to get "_FSFindFolder" I'll add support for Mac as well.

# Usage
Copy "sago/platform_files.cpp" and "sago/platform_fildes.h" to your program and make sure that the cpp file is compiled and linked.

# Hello World

This sample program gets all folders from the system:
```
#include <iostream>
#include "sago/platform_folders.h"

using namespace std;
using namespace sago;

int main()
{
	cout << "Config: " << getConfigHome() << endl;
	cout << "Data: " << getDataHome() << endl;
	cout << "Cache: " << getCacheDir() << endl;
	PlatformFolders p;
	cout << "Documents: " << p.getDocumentsFolder() << endl;
	cout << "Desktop: " << p.getDesktopFolder() << endl;
	cout << "Pictures: " << p.getPicturesFolder() << endl;
	cout << "Music: " << p.getMusicFolder() << endl;
	cout << "Video: " << p.getVideoFolder() << endl;
	cout << "Download: " << p.getDownloadFolder1() << endl;
	cout << "Save Games 1: " << p.getSaveGamesFolder1() << endl;
	return 0;
}
```

The output on Linux would look like this:
```
Config: /home/poul/.config
Data: /home/poul/.local/share
Cache: /home/poul/.cache
Documents: /home/poul/Dokumenter
Desktop: /home/poul/Skrivebord
Pictures: /home/poul/Billeder
Music: /home/poul/Musik
Video: /home/poul/Videoklip
Download: /home/poul/Hentede filer
Save Games 1: /home/poul/.local/share
```

# Licence 
Provided under the MIT license for the same reason XDG is licenced under it. So that you can quickly copy-paste the methods you need or just include the "sago"-folder.
