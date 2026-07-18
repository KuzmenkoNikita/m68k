FROM ubuntu:26.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    ninja-build \
    clang \
    clangd \
    cmake \
    gdb \
    git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
