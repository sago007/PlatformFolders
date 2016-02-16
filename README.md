# PlatformFolders [![Build Status](https://travis-ci.org/sago007/PlatformFolders.svg?branch=master)](https://travis-ci.org/sago007/PlatformFolders)
A self contained C++ abstraction library so that you do not need to have Linux, Windows and Mac OS X specific code to look for special directories

Can be found at: https://github.com/sago007/PlatformFolders

# Rationale
There are a lot of platform abstraction libraries available. You can get graphics abstraction libraries, GUI abstraction libraries and file abstraction libraries.

But folder abstraction seems to be more difficult.
My problem was that the code that found the place to save data was platform dependent. This cluttered my code and often I would not discover that it did not compile until moving it to the different platforms.

I have written a bit more about it here: http://sago007.blogspot.dk/2015/10/abstraction-for-special-folders.html

There are some alternatives that you might consider instead:
  * QStandardPaths - http://doc.qt.io/qt-5/qstandardpaths.html 
  * glib - https://developer.gnome.org/glib/stable/glib-Miscellaneous-Utility-Functions.html

Both are properly more mature than this library. However they are both parts of large frameworks and using them with libraries outside the framework may not be that simple. 

# Windows support
For Windows the folders are fetched using SHGetFolderPath.
The amount of supported folders differ from Windows version and this library targets XP and newer... and I'll drop XP support very soon. 
Currently "Save Games" and "Downloads" should not be used as they are undefined on XP. 


# Linux support
In Linux a lot of these folders are not official defined. However this library uses XDG user dirs.

# Mac OS X support
Uses the deprecated FSFindFolder (there is no C++ alternative). It requires "-framework CoreServices" during linking.

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

On Windows it could be:
```
Config: C:\users\poul\Application Data
Data: C:\users\poul\Application Data
Cache: C:\users\poul\Local Settings\Application Data
Documents: C:\users\poul\Mine dokumenter
Desktop: C:\users\poul\Skrivebord
Pictures: C:\users\poul\Mine Billeder
Music: C:\users\poul\Min Musik
Video: C:\users\poul\Mine Film
Download: C:\users\poul\Skrivebord
Save Games 1: C:\users\poul\Mine dokumenter\My Games
```

On Mac OS X it could be:
```
Config: /Users/poul/Library/Application Support
Data: /Users/poul/Library/Application Support
Cache: /Users/poul/Library/Caches
Documents: /Users/poul/Documents
Desktop: /Users/poul/Desktop
Pictures: /Users/poul/Pictures
Music: /Users/poul/Music
Video: /Users/poul/Movies
Download: /Users/poul/Downloads
Save Games 1: /Users/poul/Library/Application Support
```

# Encoding
For Windows ANSI encoding is always used. Microsoft's implementation of "Unicode" is simply not compatible with platform independent code.
For all other systems the local encoding is used. For most systems this is UTF-8.
Generally you should only append simple ASCII chars to the paths. 

# Licence 
Provided under the MIT license for the same reason XDG is licenced under it. So that you can quickly copy-paste the methods you need or just include the "sago"-folder.
