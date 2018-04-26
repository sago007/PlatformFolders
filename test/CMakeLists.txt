# Create the tester lib
add_library(platformfolders_internal_tester
	"tester.cpp"
)

target_compile_features(platformfolders_internal_tester
	PUBLIC cxx_std_11
	PRIVATE cxx_range_for
)

target_include_directories(platformfolders_internal_tester PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

# Easily define a new test to run
macro(_def_test _name)
	add_executable(${_name} "${_name}.cpp")
	target_link_libraries(${_name} PRIVATE
		platform_folders
		platformfolders_internal_tester
	)
	target_compile_features(${_name} PRIVATE
		cxx_std_11
	)
	add_test(NAME "${_name}" COMMAND "${_name}")
endmacro()

_def_test("appendAdditionalConfigDirectories")
_def_test("appendAdditionalDataDirectories")
_def_test("getCacheDir")
_def_test("getConfigHome")
_def_test("getDataHome")
_def_test("getDesktopFolder")
_def_test("getDocumentsFolder")
_def_test("getDownloadFolder1")
_def_test("getMusicFolder")
_def_test("getPicturesFolder")
_def_test("getSaveGamesFolder1")
_def_test("getVideoFolder")
_def_test("integration")
