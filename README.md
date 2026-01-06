# gRPC Calculator Service (C++)

This project is a simple **gRPC-based client-server calculator application**
implemented in **C++** using **Protocol Buffers** and **gRPC**.

It was developed as a technical case study.

---

## Features

- gRPC client-server architecture
- Protocol Buffers for message serialization
- Supported operations:
  - Sum
  - Subtraction
  - Multiplication
  - Division
- Clean CMake-based build system

---

## Project Structure

```text
ataves_santi_case/
├── proto/              # .proto definitions
├── src/
│   ├── server/         # Server implementation
│   └── client/         # Client implementation
├── generated/          # Protobuf & gRPC generated files
├── CMakeLists.txt
├── README.md
└── .gitignore
```

## Requirements
- CMake ≥ 3.20
- C++17 compatible compiler
- vcpkg (recommended)
- gRPC & Protobuf installed via vcpkg

## Build Instructions

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```
- Executables will be created inside the build/Release directory.

## How to Run
1.  Start the Server
```bash
.\Release\server.exe
```
Server will listen on:

```bash
0.0.0.0:50051
```
2. Run the Client
```bash
.\Release\client.exe
```

## Author
- Yavuz Hanege

