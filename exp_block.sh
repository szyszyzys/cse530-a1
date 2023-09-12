#!/bin/sh
# Run Simulator on input traces

trace_file=${1:-'./traces/'}
blocks='2 4 8 16 32 64 128'



for trace in $trace_file
do
  for block in $blocks
  do
    echo "current associativity $block" >> ./metrics.txt
    echo " " >> ./metrics.txt
    f=$(echo "${trace##*/}");
    tracename=$(echo $f| cut  -d'.' -f 1);
    echo $tracename
    filename="${tracename}_block_stats.out"

    if [ -e "results/$filename" ]; then
        rm "results/$filename"
    fi

    echo "Running $tracename on simulator"
    if [[ $filename == conv* ]]; then
      config_file='./Simulator/config/config_conv.yml'
    else
      config_file='./Simulator/config/config_simple_multilevel.yml'
    fi
    time python ./Simulator/src/cache_simulator.py -pdc $config_file -t "$trace" -b "$block" | tee stats.txt
    done
done

mv ./metrics.txt results/$filename
