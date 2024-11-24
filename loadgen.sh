#!/bin/bash
# the loadgen was modified from part 4a
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <server_ip> <server_port>"

    exit 1
fi


SERVER_IP=$1
SERVER_PORT=$2
THREADS=$3

# ./c_labs_server run $SERVER_IP $SERVER_PORT $THREADS &

NUM_CLIENTS=(1 5 10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100)

touch results.txt
> results.txt

for i in ${NUM_CLIENTS[@]}; do
    echo -n "${i}  " >> results.txt
    x=0
    start=$(date +%s)
    for ((j=0; j<i; j++)); do

        rand=$(echo $(($RANDOM%3 + 20)))
        x=$(($x+$rand))
        echo "request #$i"
        ./c_labs_client2 $SERVER_IP $SERVER_PORT $rand &
    done
    echo -n ",$x" >> results.txt
    wait
    end=$(date +%s)
    val=$(($end-$start))
    echo ",$val" >> results.txt
    
done

echo "All clients have finished."