#!/bin/sh
# Run Simulator on input traces

trace_file=${1:-'./traces/'}
hes='1 2 3'



for trace in $trace_file
do
  for he in $hes
  do
    echo "current associativity $associativity" >> ./metrics.txt
    echo " " >> ./metrics.txt
    f=$(echo "${trace##*/}");
    tracename=$(echo $f| cut  -d'.' -f 1);
    echo $tracename
    filename="${tracename}_he_stats.out"

    if [ -e "results/$filename" ]; then
    rm "results/$filename"
    fi

    echo "Running $tracename on simulator"
    if [[ $filename == conv* ]]; then
      config_file='./Simulator/config/config_conv.yml'
    else
      config_file='./Simulator/config/config_simple_multilevel.yml'
    fi
    # shellcheck disable=SC2086
    time python ./Simulator/src/cache_simulator.py -pdc $config_file -t $trace -n "$he" | tee stats.txt
    done
done

mv ./metrics.txt results/$filename
cat results/$filename  | grep -A 5 cache_1
