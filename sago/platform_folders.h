/*
  Its is under the MIT license, to encourage reuse by cut-and-paste.

  The original files are hosted here: https://github.com/sago007/PlatformFolders
  
  Copyright (c) 2015 Poul Sander

  Permission is hereby granted, free of charge, to any person
  obtaining a copy of this software and associated documentation files
  (the "Software"), to deal in the Software without restriction,
  including without limitation the rights to use, copy, modify, merge,
  publish, distribute, sublicense, and/or sell copies of the Software,
  and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
  ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#ifndef SAGO_PLATFORM_FOLDERS_H
#define	SAGO_PLATFORM_FOLDERS_H

#include <vector>
#include <string>

/**
 * The namespace I use for common function. Nothing special about it.
 */
namespace sago {

/**
 * Retrives the base folder for storring data files.
 * You must add the program name yourself like this:
 * @code{.cpp}
 * string data_home = getDataHome()+"/My Program Name/";
 * @endcode
 * On Windows this defaults to %APPDATA% (Roaming profile)
 * On Linux this defaults to ~/.local/share but can be configured
 * @return The base folder for storring program data.
 */
std::string getDataHome();
/**
 * Retrives the base folder for storring config files.
 * You must add the program name yourself like this:
 * @code{.cpp}
 * string data_home = getConfigHome()+"/My Program Name/";
 * @endcode
 * On Windows this defaults to %APPDATA% (Roaming profile)
 * On Linux this defaults to ~/.config but can be configured
 * @return The base folder for storring config data.
 */
std::string getConfigHome();
/**
 * Retrives the base folder for storring cache files.
 * You must add the program name yourself like this:
 * @code{.cpp}
 * string data_home = getCacheDir()+"/My Program Name/";
 * @endcode
 * On Windows this defaults to %APPDATALOCAL%
 * On Linux this defaults to ~/.cache but can be configured
 * @return The base folder for storring data that do not need to be backed up.
 */
std::string getCacheDir();
/**
 * This will append extra folders that your program should be looking for data files in.
 * This does not normally include the path returned by GetDataHome().
 * If you want all the folders you should do something like:
 * @code{.cpp}
 * vector<string> folders;
 * folders.push_back(getDataHome());
 * appendAdditionalDataDirectories(folders);
 * for (string s& : folders) {
 *     s+="/My Program Name/";
 * }
 * @endcode
 * You must apply "/My Program Name/" to all the strings.
 * The string at the lowest index has the highest priority.
 * @param homes A vector that extra folders will be appended to.
 */
void appendAdditionalDataDirectories(std::vector<std::string>& homes);
/**
 * This will append extra folders that your program should be looking for config files in.
 * This does not normally include the path returned by GetConfigHome().
 * If you want all the folders you should do something like:
 * @code{.cpp}
 * std::vector<std::string> folders;
 * folders.push_back(sago::getConfigHome());
 * sago::appendAdditionalConfigDirectories(folders);
 * for (std::string s& : folders) {
 *     s+="/My Program Name/";
 * }
 * @endcode
 * You must apply "/My Program Name/" to all the strings.
 * The string at the lowest index has the highest priority.
 * @param homes A vector that extra folders will be appended to.
 */
void appendAdditionalConfigDirectories(std::vector<std::string>& homes);

/**
 * This class contains methods for finding the system depended special folders.
 * For Windows these folders are either by convention or given by CSIDL.
 * For Linux XDG convention is used.
 * The Linux version has very little error checking and assumes that the config is correct
 */
class PlatformFolders {
public:
	PlatformFolders();
	~PlatformFolders();
	/**
	 * The folder that represents the desktop.
	 * Normally you should try not to use this folder.
	 * @return Absolute path to the user's desktop
	 */
	std::string getDesktopFolder() const;
	/**
	 * The folder to store user documents to
	 * @return Absolute path to the "Documents" folder
	 */
	std::string getDocumentsFolder() const;
	/**
	 * The folder for storring the user's pictures.
	 * @return Absolute path to the "Picture" folder
	 */
	std::string getPicturesFolder() const;
	/**
	 * The folder where files are downloaded.
	 * @note Windows: This version is XP compatible and returns the Desktop. Vista and later has a dedicated folder.
	 * @return Absolute path to the folder where files are downloaded to.
	 */
	std::string getDownloadFolder1() const;
	/**
	 * The folder where music is stored
	 * @return Absolute path to the music folder
	 */
	std::string getMusicFolder() const;
	/**
	 * The folder where video is stored
	 * @return Absolute path to the video folder
	 */
	std::string getVideoFolder() const;
	/**
	 * The base folder for storring saved games.
	 * You must add the program name to it like this:
	 * @code{.cpp}
	 * PlatformFolders pf;
	 * string saved_games_folder = pf.getSaveGamesFolder1()+"/My Program Name/";
	 * @endcode
	 * @note Windows: This is an XP compatible version and returns the path to "My Games" in Documents. Vista and later has an official folder.
	 * @note Linux: XDF does not define a folder for saved games. This will just return the same as GetDataHome()
	 * @return The folder base folder for storring save games.
	 */
	std::string getSaveGamesFolder1() const;
private:
	PlatformFolders(const PlatformFolders&);
	PlatformFolders& operator=(const PlatformFolders&);
	struct PlatformFoldersData;
	PlatformFoldersData *data;
};

}  //namespace sago

#endif	/* PLATFORM_FOLDERS_H */

