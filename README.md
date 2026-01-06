# zeromq-playground
Boilerplate code for myself regarding zeromq.

[ZeroMQ](https://zeromq.org) is an asynchronous high-performance messaging library that works brokerless. It supports a variety of messaging patters such as pub/sub, req/rep, client/server etc. over a variety of transport layers (TCP, in-process, inter-process, multicast, WebSocket and more).

This project is designed as a practice project as well as a boilerplate code for myself. It demonstrates a variety of capabilities of ZeroMQ using small modules. Module design docs and necessary information can be found below or within the module directory.

### Building and Running

Toolchain I use:

- **Compiler:** Apple clang version 16.0.0
- **Build System:** CMake 4.0.3
- **Dependency Management:** [vcpkg](https://github.com/Microsoft/vcpkg)

**CMake** and **vcpkg** are prerequisities to fetch dependencies and build the project.

#### Dependencies:
- [cppzmq](https://github.com/zeromq/cppzmq)
- [spdlog](https://github.com/gabime/spdlog)

In order to get dependencies and build, below commands shall be executed:

*Get vcpkg first*
```
git clone https://github.com/microsoft/vcpkg "$HOME/vcpkg"
export VCPKG_ROOT="$HOME/vcpkg"
```

*Configure, fetch dependencies and build*
```
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

