#include <random>

// Function to generate a random integer in a given range
int randint(int min, int max) {
    static std::random_device dev;       // Ensures a high-quality seed
    static std::mt19937 rng(dev());      // Mersenne Twister random number generator
    std::uniform_int_distribution<int> dist(min, max); // Define the range
    return dist(rng);                    // Generate and return the random number
}