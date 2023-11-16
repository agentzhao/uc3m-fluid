# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/rphoen/uc3m/Computer Architecture/fluid/uc3m-fluid/cmake-build-debug/_deps/gsl-src"
  "/Users/rphoen/uc3m/Computer Architecture/fluid/uc3m-fluid/cmake-build-debug/_deps/gsl-build"
  "/Users/rphoen/uc3m/Computer Architecture/fluid/uc3m-fluid/cmake-build-debug/_deps/gsl-subbuild/gsl-populate-prefix"
  "/Users/rphoen/uc3m/Computer Architecture/fluid/uc3m-fluid/cmake-build-debug/_deps/gsl-subbuild/gsl-populate-prefix/tmp"
  "/Users/rphoen/uc3m/Computer Architecture/fluid/uc3m-fluid/cmake-build-debug/_deps/gsl-subbuild/gsl-populate-prefix/src/gsl-populate-stamp"
  "/Users/rphoen/uc3m/Computer Architecture/fluid/uc3m-fluid/cmake-build-debug/_deps/gsl-subbuild/gsl-populate-prefix/src"
  "/Users/rphoen/uc3m/Computer Architecture/fluid/uc3m-fluid/cmake-build-debug/_deps/gsl-subbuild/gsl-populate-prefix/src/gsl-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/rphoen/uc3m/Computer Architecture/fluid/uc3m-fluid/cmake-build-debug/_deps/gsl-subbuild/gsl-populate-prefix/src/gsl-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/rphoen/uc3m/Computer Architecture/fluid/uc3m-fluid/cmake-build-debug/_deps/gsl-subbuild/gsl-populate-prefix/src/gsl-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
