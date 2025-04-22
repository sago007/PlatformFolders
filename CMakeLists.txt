cmake_minimum_required(VERSION 3.0.0..3.30.3 FATAL_ERROR)
project(platform_folders VERSION 3.2.2 LANGUAGES CXX)

# Since it's off, the library will be static by default
option(BUILD_SHARED_LIBS "Build shared instead of static." OFF)

add_library(${PROJECT_NAME}
	sago/platform_folders.cpp
)

# Where to search for the header
# The BUILD/INSTALL interface expressions are for exporting
target_include_directories(${PROJECT_NAME} PRIVATE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sago>
	$<INSTALL_INTERFACE:sago>
)

# Define the header as public for installation
set_target_properties(${PROJECT_NAME} PROPERTIES
	PUBLIC_HEADER "sago/platform_folders.h"
)

# Apple requires linking to CoreServices
# Check sys name instead of "APPLE" for cross-compilation
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	# Find the framework
	# ref: https://developer.apple.com/library/content/documentation/MacOSX/Conceptual/OSX_Technology_Overview/SystemFrameworks/SystemFrameworks.html
	find_library(_CoreServices_FRAMEWORK
		NAMES "CoreServices.framework" "CoreServices"
		PATH_SUFFIXES "CoreServices"
		PATHS "/System/Library/Frameworks"
	)
	# Make sure it was found
	if(NOT _CoreServices_FRAMEWORK)
		message(FATAL_ERROR "Could not find the CoreServices framework!")
	endif()
	# Link to the CoreServices framework. This also sets the correct linking options
	# "If the library file is in a Mac OSX framework, the Headers directory of the framework will also be processed as a usage requirement."
	target_link_libraries(${PROJECT_NAME} PRIVATE "${_CoreServices_FRAMEWORK}")
endif()

# Defines standardized defaults for install paths
include(GNUInstallDirs)
# For the config and configversion macros
include(CMakePackageConfigHelpers)

# Controls what dir to prefix for the lib, so <sago/platform_folders.h>
set(_PROJECT_INSTALL_PREFIX_DIR "sago")
# Controls where the exports, config, and configversion files install to
set(_PROJECT_INSTALL_CMAKE_DIR "${CMAKE_INSTALL_FULL_LIBDIR}/cmake/${_PROJECT_INSTALL_PREFIX_DIR}")

# Gives "Make install" esque operations a location to install to...
# and creates a .cmake file to be exported
install(TARGETS ${PROJECT_NAME}
	EXPORT "${PROJECT_NAME}-targets"
	LIBRARY DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}/${_PROJECT_INSTALL_PREFIX_DIR}"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}/${_PROJECT_INSTALL_PREFIX_DIR}"
	# Tells it where to put your headers if any set by set_target_properties
	PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_FULL_INCLUDEDIR}/${_PROJECT_INSTALL_PREFIX_DIR}"
	# Tells export where your includes folder is | Note that the private include path is not needed here
	INCLUDES DESTINATION "${CMAKE_INSTALL_FULL_INCLUDEDIR}/${_PROJECT_INSTALL_PREFIX_DIR}"
)

# "The install(TARGETS) and install(EXPORT) commands work together to install a target and a file to help import it"
# Installs a cmake file which external projects can import.
install(EXPORT "${PROJECT_NAME}-targets"
	DESTINATION "${_PROJECT_INSTALL_CMAKE_DIR}"
)

# "The export command is used to generate a file exporting targets from a project build tree"
# Creates an import file for external projects which are aware of the build tree.
# May be useful for cross-compiling
export(TARGETS ${PROJECT_NAME}
	FILE "${PROJECT_NAME}-exports.cmake"
)

configure_package_config_file("${PROJECT_NAME}Config.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	# Tells the config file where it will be installed, so it can be correctly imported
	INSTALL_DESTINATION "${_PROJECT_INSTALL_CMAKE_DIR}"
	# This passes the variables to the cmake.in file, which uses them
	PATH_VARS PROJECT_NAME
)

# Creates the project's ConfigVersion.cmake file
# This allows for find_package() to use a version in the call
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	# This'll require versioning in the project() call
	VERSION ${CMAKE_PROJECT_VERSION}
	# Just assuming Semver is followed
	COMPATIBILITY SameMajorVersion
)

# Install the ConfigVersion file, which is located in the build dir
install(FILES
		"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
		"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION "${_PROJECT_INSTALL_CMAKE_DIR}"
)

# A module for testing the library
include(CTest)
# BUILD_TESTING is defined (default ON) in CTest
if(BUILD_TESTING)
	set(_PROJECT_TEST_NAME "${PROJECT_NAME}_test")
	add_executable(${_PROJECT_TEST_NAME} platform_folders.cpp)

	target_link_libraries(${_PROJECT_TEST_NAME} PRIVATE ${PROJECT_NAME})

	# Since tests aren't installed, no reason to give it an INSTALL_INTERFACE
	target_include_directories(${_PROJECT_TEST_NAME} PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sago>
	)

	# Creates the "MyTest" test that runs the test executable created above
	# This is triggered by things like "make test"
	add_test(NAME MyTest COMMAND ${_PROJECT_TEST_NAME})
endif()
