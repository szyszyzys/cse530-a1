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

void scatter(Matrix &target, const Matrix &src, const Matrix &indices) {
    int rows = indices.size();
    int cols = indices[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int target_row = indices[i][j] / target[0].size();
            int target_col = indices[i][j] % target[0].size();
            target[target_row][target_col] = src[i][j];
        }
    }
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
    size = argv[3]

	Matrix source(size, std::vector<int>(size, 0)), indices(size, std::vector<int>(size, 0)), target(size, std::vector<int>(size, 0));
	read (filename, source, indices);
    parsec_roi_begin();
	scatter(target, source, indices);
    parsec_roi_end();
	return 0;
}
