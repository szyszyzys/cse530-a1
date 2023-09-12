#!/bin/sh
# Run Simulator on input traces 

trace_file=${1:-'./traces/'}
associativitys='1 2'

for trace in $trace_file
do
  for associativity in $associativitys
  do
    f=$(echo "${trace##*/}");
    tracename=$(echo $f| cut  -d'.' -f 1);
    echo $tracename
    filename="${tracename}_stats.out"
    echo "Running $tracename on simulator"
    if [[ $filename == conv* ]]; then
      config_file='./Simulator/config/config_conv.yml'
    else
      config_file='./Simulator/config/config_simple_multilevel.yml'
    fi
    time python ./Simulator/src/cache_simulator.py -pdc $config_file -t $trace -a $associativity | tee stats.txt
    done
done

mv ./metrics.txt results/$filename
