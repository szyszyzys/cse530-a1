#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
typedef std::vector<std::vector<int>> Matrix;

void parsec_roi_begin()
{

}

void parsec_roi_end()
{

}

#include <iostream>
#include <vector>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()

typedef std::vector<std::vector<int>> Matrix;

// Function to scatter data into target matrix using indices
void scatter(Matrix &target, const std::vector<std::pair<int, int>> &indices, const std::vector<int> &data) {
    int n = indices.size();
    for (int i = 0; i < n; ++i) {
        int row = indices[i].first;
        int col = indices[i].second;
        target[row][col] = data[i];
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <random_seed>" << std::endl;
        return 1;
    }
    int seed = std::stoi(argv[1]); // Convert argument from string to int
    srand(seed);

    const int SIZE = 256;
    const int SAMPLES = 1000;

    // Initialize matrix with zeros
    Matrix mat(SIZE, std::vector<int>(SIZE, 0));

    // Generate 1000 random indices
    std::vector<std::pair<int, int>> indices;
    for (int i = 0; i < SAMPLES; ++i) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;
        indices.push_back({row, col});
    }

    // Generate 1000 random data samples (for simplicity, values between 1 and 1000)
    std::vector<int> data;
    for (int i = 0; i < SAMPLES; ++i) {
        data.push_back(1 + rand() % 1000); // Random value between 1 and 1000
    }

    // Scatter the data samples into the matrix
    parsec_roi_begin()
    scatter(mat, indices, data);
    parsec_roi_end()

    return 0;
}