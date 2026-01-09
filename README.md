

# gRPC Calculator Service (C++)

This project is a **gRPC-based client-server calculator application**
implemented in **C++** using **Protocol Buffers** and **gRPC**.

It was developed as a **technical case study** to demonstrate backend service
design, gRPC communication, and database persistence.

---

## Features

- gRPC client-server architecture
- Protocol Buffers for message serialization
- Supported operations:
  - Sum
  - Subtraction
  - Multiplication
  - Division
- Variable-length input support for all operations
- PostgreSQL persistence for all operations and operands
- Clean CMake-based build system
- Docker-based database setup

---

## Problem Description

The system consists of two main components:

1. **gRPC Calculator Service**
   - Exposes arithmetic operations via gRPC
   - Accepts a list of numbers for each operation
   - Returns the calculated result

2. **Database Persistence Layer**
   - Every calculation request is persisted
   - Each operation is stored once
   - Each operand is stored in a separate row
   - Operand order is preserved using an index field

---

## Database Design

The PostgreSQL database uses the following schema:

### operations
| Column | Type |
|------|------|
| id | SERIAL PRIMARY KEY |
| operation_type | VARCHAR |
| created_at | TIMESTAMP |

### operation_numbers
| Column | Type |
|------|------|
| id | SERIAL PRIMARY KEY |
| operation_id | INTEGER (FK) |
| idx | INTEGER |
| value | DOUBLE PRECISION |

The schema is defined in `db/schema.sql`.

---

## gRPC API

**Service:** `CalculatorService`

### RPC Methods
- `Sum(NumberList) -> CalcResult`
- `Sub(NumberList) -> CalcResult`
- `Mul(NumberList) -> CalcResult`
- `Div(NumberList) -> CalcResult`

---

## Project Structure

```text
gRPC-Calculator-Service/
├── proto/              # .proto definitions
├── src/
│   ├── server/         # Server implementation
│   └── client/         # Client implementation
├── generated/          # Protobuf & gRPC generated files
├── db/
│   └── schema.sql      # Database schema
├── docker-compose.yml  # PostgreSQL & pgAdmin setup
├── CMakeLists.txt
├── README.md
├── LICENSE
└── .gitignore
````

---

## Requirements

* CMake ≥ 3.20
* C++17 compatible compiler
* vcpkg (recommended)
  * Make sure to set the environment variable before building:
    * `setx VCPKG_ROOT "<root>\vcpkg"`
* gRPC & Protobuf 
* Docker & Docker Compose
---

## Quick Start

```bash
git clone <repository-url>
cd gRPC-Calculator-Service

# Start PostgreSQL & pgAdmin via Docker
docker compose up -d

# Build the project
cmake -B build -S .
cmake --build build --config Release
```

---

## How to Run

### 1. Start the Server

```bash
.\build\Release\server.exe
```

The server listens on:

```text
0.0.0.0:50051
```

### 2. Run the Client

```bash
.\build\Release\client.exe
```

---

## Notes for Reviewers

* PostgreSQL and pgAdmin are provided via Docker Compose.
* Database initialization is handled via `schema.sql`.
* The persistence layer is separated from gRPC logic for clarity and maintainability.
* The project is structured to be easily extendable with additional operations or services.

---

## Author

**Yavuz Hanege**

