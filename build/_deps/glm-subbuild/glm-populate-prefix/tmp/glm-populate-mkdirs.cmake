# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/Users/malexander/Documents/KanaeGameEngine/build/_deps/glm-src")
  file(MAKE_DIRECTORY "/Users/malexander/Documents/KanaeGameEngine/build/_deps/glm-src")
endif()
file(MAKE_DIRECTORY
  "/Users/malexander/Documents/KanaeGameEngine/build/_deps/glm-build"
  "/Users/malexander/Documents/KanaeGameEngine/build/_deps/glm-subbuild/glm-populate-prefix"
  "/Users/malexander/Documents/KanaeGameEngine/build/_deps/glm-subbuild/glm-populate-prefix/tmp"
  "/Users/malexander/Documents/KanaeGameEngine/build/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp"
  "/Users/malexander/Documents/KanaeGameEngine/build/_deps/glm-subbuild/glm-populate-prefix/src"
  "/Users/malexander/Documents/KanaeGameEngine/build/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/malexander/Documents/KanaeGameEngine/build/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/malexander/Documents/KanaeGameEngine/build/_deps/glm-subbuild/glm-populate-prefix/src/glm-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
