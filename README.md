# PlatformFolders [![Build Status](https://travis-ci.org/sago007/PlatformFolders.svg?branch=master)](https://travis-ci.org/sago007/PlatformFolders) [![AppVeyor](https://img.shields.io/appveyor/ci/sago007/PlatformFolders.svg?label=Windows)](https://ci.appveyor.com/project/sago007/platformfolders) [![license](https://img.shields.io/github/license/sago007/PlatformFolders.svg)](https://raw.githubusercontent.com/sago007/PlatformFolders/master/LICENSE) [![Join the chat at https://gitter.im/PlatformFolders/Lobby](https://badges.gitter.im/PlatformFolders/Lobby.svg)](https://gitter.im/PlatformFolders/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/729e36adcf5c4523bd136de1b33441cb)](https://www.codacy.com/app/github_43/PlatformFolders?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=sago007/PlatformFolders&amp;utm_campaign=Badge_Grade)

A C++ library to look for special directories like "My Documents" and "%APPDATA%" so that you do not need to write Linux, Windows and Mac OS X specific code

Can be found at: https://github.com/sago007/PlatformFolders

Releases can be downloaded here: https://github.com/sago007/PlatformFolders/releases

# Rationale
There are a lot of platform abstraction libraries available. You can get graphics abstraction libraries, GUI abstraction libraries and file abstraction libraries.

But folder abstraction seems to be more difficult.
My problem was that the code that found the place to save data was platform dependent. This cluttered my code and often I would not discover that it did not compile until moving it to the different platforms.

I have written a bit more about it here: http://sago007.blogspot.dk/2015/10/abstraction-for-special-folders.html

There are some alternatives that you might consider instead:
  * QStandardPaths - http://doc.qt.io/qt-5/qstandardpaths.html
  * glib - https://developer.gnome.org/glib/stable/glib-Miscellaneous-Utility-Functions.html

Both are properly more mature than this library. However they are both parts of large frameworks and using them with libraries outside the framework may not be that simple.

# Documentation

Aside from this page there are also Doxygen available at http://sago007.github.io/PlatformFolders/html/doxygen/

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

It is also possible to compile and it like:
```
mkdir -p build
cd build
cmake ..
make
```
Just be aware that Mac OS X requires "-framework CoreServices" during linking no matter the choice.

# Hello World

This sample program gets all folders from the system:
```
#include <iostream>
#include <stirng>
#include <vector>
#include "sago/platform_folders.h"

using std::cout;

int main()
{
	cout << "Config: " << sago::getConfigHome() << "\n";
	cout << "Data: " << sago::getDataHome() << "\n";
	cout << "Cache: " << sago::getCacheDir() << "\n";
	cout << "Documents: " << sago::getDocumentsFolder() << "\n";
	cout << "Desktop: " << sago::getDesktopFolder() << "\n";
	cout << "Pictures: " << sago::getPicturesFolder() << "\n";
	cout << "Music: " << sago::getMusicFolder() << "\n";
	cout << "Video: " << sago::getVideoFolder() << "\n";
	cout << "Download: " << sago::getDownloadFolder1() << "\n";
	cout << "Save Games 1: " << sago::getSaveGamesFolder1() << "\n";
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

# C++ support
Versions up to 3.X.X should compile with any C++98 compiler.
Versions from 4.0.0 and up requires a C++11 compatible compiler.

The aim is to always support the default C++ compiler on the oldest supported version of Ubuntu. This is a very basic library and it is not supposed to force you to upgrade.

# Encoding
From version 3.0 UTF-8 is always used on Windows and will also be the default on almost any other system.
Before version 3.0 Windows used ANSI encoding. Microsoft's default choice of UTF-16 is not compatible with platform independent code.
Although the user may use an characters they want I recommend, that the program should not have non ASCII characters in the source code itself.

# Licence
Provided under the MIT license for the same reason XDG is licensed under it. So that you can quickly copy-paste the methods you need or just include the "sago"-folder.
