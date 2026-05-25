A Hardware True Random Number Generator (TRNG) based on CPU-RAM timing jitter. 

> **The Story:** The core concept of this project was conceived when I was 12 years old. The idea was simple yet brilliant: measure the microscopic time variations when pushing bits between the CPU and RAM to harvest pure physical entropy. This repository contains the concrete implementation of that childhood idea in pure C++.

## How It Works 

Unlike pseudo-random generators (PRNG) that rely on mathematical formulas, this algorithm exploits **physical hardware jitter**:

1. **CPU-RAM-CPU Pipeline:** The program allocates a buffer in memory and performs bitwise operations on it.
2. **`volatile` Operations:** Using `volatile` pointers forces the compiler to bypass optimizations and execute raw reads/writes directly to the hardware.
3. **Hardware Fluctuations:** Microscopic changes in CPU temperature, cache misses, bus contention, and DRAM refresh cycles introduce tiny delays.
4. **`__rdtsc()` Precision:** We measure the exact number of CPU clock cycles elapsed. While the total time is predictable, the Least Significant Bit (LSB) of the cycle count flips unpredictably between `0` and `1` due to thermal and electronic noise.

## Features 

* **Zero OS Dependencies:** Pure hardware-level entropy, no hybrid software threading tricks.
* **Single-Threaded:** No thread-scheduling bias.
* **Low-Level Assembly:** Uses x86/x64 `__rdtsc` instructions for clock-cycle precision.

## Code Preview 

```cpp
// Microscopic time measurement
unsigned long long start_cycles = __rdtsc();

for (int i = 0; i < size; ++i) {
    buffer[i] = i ^ 0x55; 
    volatile char read_back = buffer[i]; 
}

unsigned long long end_cycles = __rdtsc();
return (end_cycles - start_cycles) & 1; // Extracting the true random bit
How to Build 🚀
You need a C++11 (or newer) compatible compiler (GCC, Clang, or MSVC) on an x86/x64 architecture.

Using GCC/Clang:
Bash
g++ -O3 main.cpp -o trng
./trng
