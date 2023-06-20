## CMake Stanford Lib User Guide



### `CMakeLists.txt`

**Add all libraries in the rooted CMakeLists.txt (not recommended)**

- Line 7: `file(GLOB ...)`:  [grouping files](https://cmake.org/cmake/help/latest/command/file.html#glob)

> Generate a list of files that match the `<globbing-expressions>` and store it into the `<variable>`. Globbing expressions are similar to regular expressions, but much simpler. If `RELATIVE` flag is specified, the results will be returned as relative paths to the given path.



- Line 21: `add_library()`

  **Add all libraries in the rooted CMakeLists.txt (not recommended)**

- Line 23: `app_SOUECES` stands for the source code file



### Compiling with CMake

1. In the build directory, add one more parameter to generate `compile_commands.json` so that clangd can search for libraries in lib directory (neovim lsp won't warn you): In the build, let cmake export the compile commands. [For more (project setup)](https://clangd.llvm.org/installation.html)

`cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..`

Note: clangd searches for file in the directory that is added into the `include_directories()`

2. Clangd c++ version setting: [Link](https://neovim.discourse.group/t/how-to-setup-clangd-for-c-20/1744)

`cd ~` then `touch .clangd`, finally in the `.clangd` add: 

```
CompileFlags:
  Add: [-std=c++20]
```

3. In the build directory: move the `spl.jar` file in lib to the build directory. This satisfy the Stanford lib's need for a java file.



### Add More Libraries for Future Assignment

There is an example commented in the `CMakeLists.txt`



### Load Extra Resources from `res` Folder

> When setting up a project there often comes a need to manage some additional resources that have no association to the build system at compile-time, but rather, are purely a runtime thing. These could be some configuration files, or maybe vertex/fragment shaders if you’re doing some graphics programming, or any other dependencies your compiler does not care about. They’re developed alongside the project, and would likely be installed with it as well, but for development and testing purposes it would be convenient to have them copied to a location in the build directory. This is where add_custom_command comes in. It allows to define an almost arbitrary command that’s executed at a specific point of the configure-generate-build process. One of its uses is to make the build system aware of files that are otherwise not associated with any other target. 
>
> From [CMake Managing Resources](https://jeremimucha.com/2021/05/cmake-managing-resources/)

In order to do this, all the resources should be added to the build directory, so that the program can load resources at runtime. (Example is in the `CMakeLists.txt`)

[How to copy contents of a directory into build directory after make with CMake?](https://stackoverflow.com/questions/13429656/how-to-copy-contents-of-a-directory-into-build-directory-after-make-with-cmake)

[Copy all files with given extension to output directory using CMake](https://stackoverflow.com/questions/24311402/copy-all-files-with-given-extension-to-output-directory-using-cmake)

[Copy file from source directory to binary directory using CMake](https://stackoverflow.com/questions/34799916/copy-file-from-source-directory-to-binary-directory-using-cmake)

Copy a single file:

```cmake
file(COPY file DESTINATION ${CMAKE_BINARY_DIR})
```

### Command Line Bug Fix

1. In order to fully activate the `GWindow`, the console must be activated. Use `cout ` to activate the console when running program first





