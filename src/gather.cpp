#include <iostream>
#include <vector>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()

typedef std::vector<std::vector<int>> Matrix;
void parsec_roi_begin()
{

}

void parsec_roi_end()
{

}
// Function to gather data from source matrix using indices
std::vector<int> gather(const Matrix &source, const std::vector<std::pair<int, int>> &indices) {
    std::vector<int> result;
    for (const auto &index : indices) {
        int row = index.first;
        int col = index.second;
        result.push_back(source[row][col]);
    }
    return result;
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

    // Initialize matrix with random values for demonstration purposes (values between 1 and 10000)
    Matrix mat(SIZE, std::vector<int>(SIZE));
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            mat[i][j] = 1 + rand() % 10000;
        }
    }

    // Generate 1000 random indices
    std::vector<std::pair<int, int>> indices;
    for (int i = 0; i < SAMPLES; ++i) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;
        indices.push_back({row, col});
    }

    // Gather the data from the matrix using the indices
    parsec_roi_begin();
    std::vector<int> gatheredData = gather(mat, indices);
    parsec_roi_end();

    return 0;
}
