size1=${1:-'10'}
size2=${2:-'3'}
sparsity=${3:-'50'}
input_file=${4:-'input_matrix.in'}
input_file_convol=${5:-'input_matrix_convolution.in'}
python utils/random_matrix_generator.py --n1 $size1 --n2 $size1 --dump $input_file --sparsity $sparsity

python utils/random_matrix_generator.py --n1 $size1 --n2 $size2 --dump $input_file_convol --sparsity $sparsity
