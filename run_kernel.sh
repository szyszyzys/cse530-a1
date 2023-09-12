#!/bin/sh
# Compile, Run and extract trace from matmul kernel

export PIN_ROOT=/home/other/CSE530-FA2022/pin-3.18-98332-gaebd7b1e6-gcc-linux

seed=${1:-42}
kernal_size=${2:-3}


rm -rf bin/
rm -rf traces/

mkdir -p bin/
mkdir -p traces/

echo Compiling convolution
g++ -std=c++11 -Wall src/convolution.cpp -o bin/convolution.o

echo Compiling gather
g++ -std=c++11 -Wall src/gather.cpp -o bin/gather.o

echo Compiling scatter
g++ -std=c++11 -Wall src/scatter.cpp -o bin/scatter.o

for task in bin/*.o
do
  f=$(echo "${task##*/}");
  task_name=$(echo $f| cut  -d'.' -f 1);
  if [[ $task_name = "convolution" ]];
  then
  trace_name="${task_name}_traces_seed_{$seed}_kernal_{$kernal_size}.out"
	echo "start convolution"
  	time $PIN_ROOT/pin -t $PIN_ROOT/source/tools/ManualExamples/obj-intel64/pinatrace.so -- $task $seed $kernal_size
  else
  trace_name="${task_name}_traces_seed_{$seed}.out"
	echo "start ${task_name}"
  	time $PIN_ROOT/pin -t $PIN_ROOT/source/tools/ManualExamples/obj-intel64/pinatrace.so -- $task $seed
  fi
  head -n 10 pinatrace.out
  mv pinatrace.out traces/$trace_name
done
