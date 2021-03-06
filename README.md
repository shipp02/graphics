# How to build
You need cmake, make and [conan](https://conan.io/) to build
```
# Create a out-of-source build directory
mkdir build
cd build
# Run conan to fetch dependencies and generate appropriate file to add them
conan install ..
# Run cmake to generate Makefile and configure build
cmake ..
# Create the lighting demo from two.cpp file
make lighting
# Create a game like demo from one.cpp
make conan1
```
# Included helper classes file for OpenGL
1. ``shader.h``
  - Not intended to be used directly.
  - Constructor creates a shader from a source file of the provided shader type.
  - Destrucor will delete the shader.

2. ``program.h``
- This will create a program from a Vertex Shader and Fragment shader files.

# TODO
- [ ] Better error checking.
- [ ] Create the Vao object to take care of all concerns of drawing objects.
- [ ] Use the event loop for updates to state at the right time using libuv. 
- [ ] Make a Watchable the file and make the GUI change accordingly. Using YAML?

