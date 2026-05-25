#include <iostream>
// Enables processor clock intrinsics
#ifdef _MSC_VER
#include <intrin.h> // For Visual Studio
#else
#include <x86intrin.h> // For GCC/Clang
#endif
// This function measures pure jitter when using RAM
int get_pure_hardware_bit () {
// 64 KB of memory to ensure a breakout through the L1 cache and into RAM
constant size int = 1024 * 64;

// Volatile prevents the compiler from cutting this code fragment during optimization
volatile char* buffer = new char[size];

// 1. Fixed processor clock cycles TO
unsigned long long start_cycles = __rdtsc();

// 2. Perform CPU -> RAM -> CPU Bits operations
for (int i = 0; i < size; ++i) {
buffer[i] = i ^ 0x55; // Write to RAM
volatile character read_back = buffer[i]; // Read from RAM
}
// 3. Capture CPU cycles AFTER
unsigned long long end_cycles = __rdtsc();

delete[] buffer;

// Calculate the net time difference (per CPU cycle)
unsigned long long time_spent = end_cycles - start_cycles;

// Extract the least significant bit (0 or 1).

// The number of cycles can be ~300,000, but due to hardware physics
// it will sometimes be even (300,002) and sometimes odd (300,003).

return time_spent & 1;

}
interval main() {
std::cout << "Measuring CPU-RAM-CPU latency (pure hardware jitter)..." << std::endl;

unsigned char true_random_byte = 0;

// Collect 8 bits into one byte
for (int i = 0; i <8; ++i) {
int bit = get_pure_hardware_bit();

true_random_byte = (true_random_byte << 1) | chunk;

std::cout << "bit " << i + 1 << " collected. Value: " << bit << std::endl;

}
std::cout << "\nRandom number " << (int)true_random_byte << std::endl;

return 0;

}
