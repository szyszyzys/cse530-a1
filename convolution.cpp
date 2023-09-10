#include <vector>

typedef std::vector<std::vector<int>> Matrix;

void parsec_roi_begin()
{

}

void parsec_roi_end()
{

}

Matrix convolution(const Matrix &input, const Matrix &kernel) {
    int irows = input.size();
    int icols = input[0].size();
    int krows = kernel.size();
    int kcols = kernel[0].size();

    // Output size
    int orows = irows - krows + 1;
    int ocols = icols - kcols + 1;

    Matrix output(orows, std::vector<int>(ocols, 0));

    for (int i = 0; i < orows; ++i) {
        for (int j = 0; j < ocols; ++j) {
            for (int ki = 0; ki < krows; ++ki) {
                for (int kj = 0; kj < kcols; ++kj) {
                    output[i][j] += input[i + ki][j + kj] * kernel[ki][kj];
                }
            }
        }
    }

    return output;
}

void read(string filename, Matrix &A, Matrix &B) {
	string line;
	ifstream infile;
	infile.open (filename.c_str());
	int i=0, j, a;

	while (getline(infile, line) && !line.empty()) {
		istringstream iss(line);
		j = 0;
		while (iss >> a) {
			A(i,j) = a;
			j++;
		}
		i++;
	}

	i = 0;
	while (getline(infile, line)) {
		istringstream iss(line);
		j = 0;
		while (iss >> a) {
			B(i,j) = a;
			j++;
		}
		i++;
	}

	infile.close();
}

int main (int argc, char* argv[]) {
	string filename;
	filename = argv[2];
    m_size = argv[3]
    k_size = argv[4]
	Matrix input(m_size, std::vector<int>(m_size, 0)), kernal(k_size, std::vector<int>(k_size, 0));
	read (filename, input, kernal);
    parsec_roi_begin();
	convolution(input, kernal);
    parsec_roi_end();
	return 0;
}
