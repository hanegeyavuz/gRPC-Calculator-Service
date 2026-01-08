FROM ubuntu:22.04

RUN apt update && apt install -y \
    build-essential \
    cmake \
    libpqxx-dev \
    protobuf-compiler \
    grpc++ \
    libgrpc++-dev

WORKDIR /app

COPY . .

RUN mkdir build && cd build && cmake .. && make

EXPOSE 50051

CMD ["./build/server"]
