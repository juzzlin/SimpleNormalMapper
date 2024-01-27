## Simple Normal Mapper

<table>
  <tr>
    <td>
      <img src="https://cloud.githubusercontent.com/assets/2587783/7400815/3b03a18c-eec8-11e4-8488-d637b536d2d1.png"></img>
    </td>
    <td>
      <img src="https://cloud.githubusercontent.com/assets/2587783/21721271/3e3e8f0c-d430-11e6-92da-4a7299e2b98d.png"></img>
    </td>
  </tr>
</table>

Simple Normal Mapper is a graphical editor with which one can generate normal maps for 2D images.

Normal maps are used, for example, in 2D games to make an illusion of
a 3D object.

## Building the project

Currently the build depends on `Qt 5` and `CMake` only. Support for `Qt 6` is preliminary and can be explicitly enabled.

Use the official `Qt SDK` or install the needed development tools from a package repository.

Building for Linux in a nutshell:

    $ mkdir build && cd build

    $ cmake ..

    $ cmake --build . -j4

`Qt 6` can be explicitly enabled by:

    $ cmake -DBUILD_WITH_QT6=ON ..

Create a Debian package for Debian-based Linux distributions (in build dir):

    $ cpack -G DEB

## Licence

GNU GPL v3

