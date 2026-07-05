#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "WebP::external_sharpyuv" for configuration "MinSizeRel"
set_property(TARGET WebP::external_sharpyuv APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(WebP::external_sharpyuv PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "C"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/libsharpyuv.lib"
  )

list(APPEND _cmake_import_check_targets WebP::external_sharpyuv )
list(APPEND _cmake_import_check_files_for_WebP::external_sharpyuv "${_IMPORT_PREFIX}/lib/libsharpyuv.lib" )

# Import target "WebP::webpdecoder" for configuration "MinSizeRel"
set_property(TARGET WebP::webpdecoder APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(WebP::webpdecoder PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "${_IMPORT_PREFIX}/lib/libwebpdecoder.lib"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/bin/libwebpdecoder.dll"
  )

list(APPEND _cmake_import_check_targets WebP::webpdecoder )
list(APPEND _cmake_import_check_files_for_WebP::webpdecoder "${_IMPORT_PREFIX}/lib/libwebpdecoder.lib" "${_IMPORT_PREFIX}/bin/libwebpdecoder.dll" )

# Import target "WebP::external_libwebp" for configuration "MinSizeRel"
set_property(TARGET WebP::external_libwebp APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(WebP::external_libwebp PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "${_IMPORT_PREFIX}/lib/libwebp.lib"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/bin/libwebp.dll"
  )

list(APPEND _cmake_import_check_targets WebP::external_libwebp )
list(APPEND _cmake_import_check_files_for_WebP::external_libwebp "${_IMPORT_PREFIX}/lib/libwebp.lib" "${_IMPORT_PREFIX}/bin/libwebp.dll" )

# Import target "WebP::external_webpdemux" for configuration "MinSizeRel"
set_property(TARGET WebP::external_webpdemux APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(WebP::external_webpdemux PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "${_IMPORT_PREFIX}/lib/libwebpdemux.lib"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/bin/libwebpdemux.dll"
  )

list(APPEND _cmake_import_check_targets WebP::external_webpdemux )
list(APPEND _cmake_import_check_files_for_WebP::external_webpdemux "${_IMPORT_PREFIX}/lib/libwebpdemux.lib" "${_IMPORT_PREFIX}/bin/libwebpdemux.dll" )

# Import target "WebP::external_libwebpmux" for configuration "MinSizeRel"
set_property(TARGET WebP::external_libwebpmux APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(WebP::external_libwebpmux PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "${_IMPORT_PREFIX}/lib/libwebpmux.lib"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/bin/libwebpmux.dll"
  )

list(APPEND _cmake_import_check_targets WebP::external_libwebpmux )
list(APPEND _cmake_import_check_files_for_WebP::external_libwebpmux "${_IMPORT_PREFIX}/lib/libwebpmux.lib" "${_IMPORT_PREFIX}/bin/libwebpmux.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
