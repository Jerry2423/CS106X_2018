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

2. Clangd c++ version setting: [Link](https://neovim.discourse.group/t/how-to-setup-clangd-for-c-20/1744)

`cd ~` then `touch .clangd`, finally in the `.clangd` add: 

```
CompileFlags:
  Add: [-std=c++20]
```

3. In the build directory: move the `spl.jar` file in lib to the build directory. This satisfy the Stanford lib's need for a java file.



### Command Line Bug Fix

1. In order to fully activate the `GWindow`, the console must be activated. Use `cout ` to activate the console when running program first
