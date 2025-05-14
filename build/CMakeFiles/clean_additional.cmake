# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\FileCommander_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\FileCommander_autogen.dir\\ParseCache.txt"
  "FileCommander_autogen"
  )
endif()
