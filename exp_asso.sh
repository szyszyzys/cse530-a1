#!/bin/sh
# Run Simulator on input traces

trace_file=${1:-'./traces/'}
associativitys='1 2 4 8 16'

f=$(echo "${trace_file##*/}");
tracename=$(echo $f| cut  -d'.' -f 1);
filename="${tracename}_as_stats.out"

if [ -e "results/$filename" ]; then
    rm "results/$filename"
fi

for associativity in $associativitys
  do
    echo "current associativity $associativity" >> ./metrics.txt
    echo " " >> ./metrics.txt

    filename="${tracename}_as_stats.out"

    echo "Running $tracename on simulator"
    if [[ $filename == conv* ]]; then
      config_file='./Simulator/config/config_conv.yml'
    else
      config_file='./Simulator/config/config_simple_multilevel.yml'
    fi
    time python ./Simulator/src/cache_simulator.py -pdc $config_file -t $trace_file -a $associativity | tee stats.txt

  done

mv cache_simulator.log simulator_log/$filename
mv ./metrics.txt results/$filename

cat results/$filename  | grep -A 5 cache_1
