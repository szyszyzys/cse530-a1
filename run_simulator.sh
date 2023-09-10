#!/bin/sh
# Run Simulator on input traces 

trace_file=${1:-'./traces/'}

for trace in $trace_file/*.out
do
  f=$(echo "${trace##*/}");
  tracename=$(echo $f| cut  -d'.' -f 1);
  echo $tracename	
  filename="${tracename}_stats.out"
  echo "Running $tracename on simulator"
  time python ./Simulator/src/cache_simulator.py -pdc ../config/config_simple_multilevel -t $trace | tee stats.txt
  mv ./Simulator/src/cache_simulator.log $filename
done
