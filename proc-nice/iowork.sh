mkdir tmp

./a.out idle_1 &
pid1=$!
echo "pid1=$pid1"

./a.out idle_2 &
pid2="$!"
echo "pid2=$pid2"

./a.out realtime_1 &
pid3="$!"
echo "pid3=$pid3"

ionice -c 3 -p $pid1 # idle class
ionice -c 3 -p $pid2 # idle class
ionice -c 1 -p $pid3 # realtime class

sleep 60
