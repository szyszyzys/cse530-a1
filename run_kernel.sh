#!/bin/sh
# Compile, Run and extract trace from matmul kernel

export PIN_ROOT=/home/mdl/azk6085/CSE530/pin-3.18-98332-gaebd7b1e6-gcc-linux/
size1=${1:-'10'}
size2=${2:-'10'}
sparsity=${3:-'50'}
input_file=${4:-'input_matrix.in'}
input_file_convol=${5:-'input_matrix_convolution.in'}
build_type=${6:-'normal'}
python utils/random_matrix_generator.py --n1 $size1 --n2 $size1 --dump $input_file --sparsity $sparsity

python utils/random_matrix_generator.py --n1 $size1 --n2 $size2 --dump $input_file_convol --sparsity $sparsity

if [[ $build_type = "clean" ]];
then
    echo 'clean build'
    rm -rf bin/
    rm -rf traces/
else
    echo 'recursive build'
fi

mkdir -p bin/
mkdir -p traces/

echo Compiling Matmul_boostlib
g++ -Wall src/convolution.cpp -o bin/convolution.o
#g++ -std=c++98 -Wall -O3 -g src/matmul_boostlib.cpp -o bin/matmul_boostlib.o -pedantic

echo Compiling Matmul_strassenalgo
g++ -Wall src/gather.cpp -o bin/gather.o
#g++ -std=c++98 -Wall -O3 -g src/matmul_strassenalgo.cpp -o bin/matmul_strassenalgo.o -pedantic

echo Compiling Matmul_ikjalgo
g++ -Wall src/scatter.cpp -o bin/scatter.o

for entry in bin/*.o
do
  f=$(echo "${entry##*/}");
  kernelname=$(echo $f| cut  -d'.' -f 1);
  filename="${kernelname}_traces.out"
  if [[ $kernelname = "convolution" ]];
  then
	echo "Passing matrix in csr fmt"
  	echo "Running $kernelname on $input_file"
    csrA="csrA_${input_file_convol}"
    csrB="csrB_${input_file_convol}"
  	time $PIN_ROOT/pin -t $PIN_ROOT/source/tools/ManualExamples/obj-intel64/pinatrace.so -- $entry $csrA $csrB
  else
	echo "Passing matrix in dense fmt"
  	echo "Running $kernelname on $input_file"
  	time $PIN_ROOT/pin -t $PIN_ROOT/source/tools/ManualExamples/obj-intel64/pinatrace.so -- $entry --input_file $input_file
  fi
  head pinatrace.out  
  mv pinatrace.out traces/$filename  
done

source run_simulator.sh /home/mdl/azk6085/CSE530/CachePerformanceOnMatMul/traces