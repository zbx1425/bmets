## Building

This project uses the CMake build system. You are supposed to have some basic knowledges on CMake and general C++ programming.

### Linux

Clone the repository with git with the `--recursive` flag.

Install Boost, Antlr, GLM, Assimp and GLFW3 from your package manager or manually. Create a build directory, generate build files, and then run the build. AntlrCpp should be automatically cloned from Github. Prepare a proxy if you are living in the place that makes it necessary.

Some dynamic libraries might not be automatically copied, so you might have to copy them manually.

### Windows

Clone the repository with git with the `--recursive` flag.

Install Boost, Antlr, GLM, Assimp and GLFW3 at a place of your preference. In my case I was able to make use of release assets of Boost, Antlr and GLM but I had to build GLFW3 and Assimp with CMake manually, make sure you use the "x64" build target. Then set your CMake environment variables. I used the VSCode "CMake Tools" plugin, but you can use something else similar. Replace the paths accordingly.

```json
{
  "cmake.configureEnvironment": {
    "ANTLR_EXECUTABLE": "[...]/antlr4/antlr-4.9.2-complete.jar",
    "BOOST_ROOT": "[...]/boost",
    "glm_DIR": "[...]/glm/cmake/glm",
    "assimp_DIR": "[...]/assimp/lib/cmake/assimp-5.1",
    "glfw3_DIR": "[...]/glfw3/lib/cmake/glfw3"
  }
}
```

Create a build directory, generate build files, and then run the build. AntlrCpp should be automatically cloned from Github. Prepare a proxy if you are living in the place that makes it necessary.

If the first build attempt fails due to some errors in AntlrCpp, this might be a MSVC issue. Try going to `build/antlr4_runtime/src/antlr4_runtime/runtime/Cpp/runtime/CMakeLists.txt`, and locate these lines (they should be around L120):

```cmake
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set(extra_share_compile_flags "-DANTLR4CPP_EXPORTS -MP /wd4251")
  set(extra_static_compile_flags "-DANTLR4CPP_STATIC -MP")
endif()
```

Then change them to:

```cmake
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set(extra_share_compile_flags "-DANTLR4CPP_EXPORTS -MP /wd4251 /Zc:__cplusplus")
  set(extra_static_compile_flags "-DANTLR4CPP_STATIC -MP /Zc:__cplusplus")
endif()
```

Some dynamic libraries might not be automatically copied, so you might have to copy them manually.