#include <iostream>
#include <vector>
#include <cstdlib> // for rand()
#include <ctime> // for time()

void parsec_roi_begin()
{

}

void parsec_roi_end()
{

}


typedef std::vector<std::vector<int>> Matrix;

Matrix generateRandomMatrix(int rows, int cols) {
    Matrix matrix(rows, std::vector<int>(cols, 0));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = 1 + rand() % 1000;
        }
    }
    return matrix;
}


//Matrix convolution(const Matrix &input, const Matrix &kernel) {
//    int inputRows = input.size();
//    int inputCols = input[0].size();
//    int kernelRows = kernel.size();
//    int kernelCols = kernel[0].size();
//
//    int outputRows = inputRows;
//    int outputCols = inputCols;
//    Matrix output(outputRows, std::vector<int>(outputCols, 0));
//
//    int padRow = kernelRows / 2;
//    int padCol = kernelCols / 2;
//
//    for (int i = 0; i < outputRows; ++i) {
//        for (int j = 0; j < outputCols; ++j) {
//            int sum = 0;
//            for (int m = -padRow; m <= padRow; ++m) {
//                for (int n = -padCol; n <= padCol; ++n) {
//                    if (i + m >= 0 && i + m < inputRows && j + n >= 0 && j + n < inputCols) {
//                        sum += input[i + m][j + n] * kernel[padRow + m][padCol + n];
//                    }
//                }
//            }
//            output[i][j] = sum;
//        }
//    }
//    return output;
//}

Matrix convolution(const Matrix &input, const Matrix &kernel) {
    int inputRows = input.size();
    int inputCols = input[0].size();

    int kernelRows = kernel.size();
    int kernelCols = kernel[0].size();

    int outputRows = inputRows - kernelRows + 1;
    int outputCols = inputCols - kernelCols + 1;

    Matrix output(outputRows, std::vector<int>(outputCols, 0));

    for (int i = 0; i < outputRows; ++i) {
        for (int j = 0; j < outputCols; ++j) {
            for (int m = 0; m < kernelRows; ++m) {
                for (int n = 0; n < kernelCols; ++n) {
                    output[i][j] += input[i + m][j + n] * kernel[m][n];
                }
            }
        }
    }

    return output;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <random_seed> <kernel_size>" << std::endl;
        std::cerr << "Kernel size must be one of: 3, 5, 7" << std::endl;
        return 1;
    }

    int seed = std::stoi(argv[1]); // Convert argument from string to int
    int kernal_size=std::stoi(argv[2]);
    srand(seed);

    // 256x256 input matrix initialized with random values between 0 and 1
    Matrix input = generateRandomMatrix(32, 32);

    // 3x3 kernel with random values (you can replace this with a Gaussian kernel or other kernel values)
    Matrix kernel = generateRandomMatrix(kernal_size, kernal_size);

    // Perform convolution
    parsec_roi_begin();
    Matrix output = convolution(input, kernel);
    parsec_roi_end();


    return 0;
}
