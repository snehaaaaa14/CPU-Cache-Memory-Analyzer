# CPU Cache Memory Analyzer

## Project Overview

CPU Cache Memory Analyzer is a C++ based system-level project that analyzes memory access performance using different access patterns.

The project measures the time required to access different memory sizes using sequential, strided, and random memory access patterns.

## Objectives

- Analyze memory access performance.
- Compare different memory access patterns.
- Observe the effect of memory size on access time.
- Understand the relationship between CPU cache and main memory.
- Generate test results in CSV format.

## Technologies Used

- C++
- Linux / Ubuntu
- GNU Compiler Collection (G++)
- Make
- Git & GitHub

## Features

- Detects CPU information from `/proc/cpuinfo`.
- Displays CPU cache information.
- Supports three memory test sizes:
  - 4 MB
  - 64 MB
  - 256 MB
- Performs:
  - Sequential access
  - Strided access
  - Random access
- Saves test results automatically to `results/results.csv`.

## Project Structure

```text
CPU-Cache-Memory-Analyzer/
├── src/
│   └── main.cpp
├── results/
│   └── results.csv
├── Makefile
└── README.md
