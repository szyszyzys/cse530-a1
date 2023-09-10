#include <vector>

typedef std::vector<std::vector<int>> Matrix;
void parsec_roi_begin()
{

}

void parsec_roi_end()
{

}
Matrix gather(const Matrix &src, const Matrix &indices) {
    int rows = indices.size();
    int cols = indices[0].size();

    Matrix output(rows, std::vector<int>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int src_row = indices[i][j] / src[0].size();
            int src_col = indices[i][j] % src[0].size();
            output[i][j] = src[src_row][src_col];
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

Matrix main (int argc, char* argv[]) {
	string filename;
	filename = argv[2];
    size = argv[3]

	Matrix source(size, std::vector<int>(size, 0)), indices(size, std::vector<int>(size, 0));
	read (filename, source, indices);
    parsec_roi_begin();
	gather(source, indices);
    Matrix output = parsec_roi_end();
	return output;
}
