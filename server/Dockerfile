# Use the official Ubuntu as the base image
FROM ubuntu:latest

# Set the working directory
WORKDIR /app

# Install essential packages for building and running C++ programs
RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    && rm -rf /var/lib/apt/lists/*

# Copy the CMakeLists.txt and main.cpp files to the container
COPY CMakeLists.txt .
COPY main.cpp .

# Build the C++ program using CMake
RUN mkdir build && cd build && cmake .. && make

# Run the compiled C++ program
CMD ["./build/MyServerProgram"]