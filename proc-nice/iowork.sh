mkdir tmp

./a.out first &
pid1="$!"
echo "pid1=$pid1"

./a.out second &
pid2="$!"
echo "pid2=$pid2"

ionice -c 3 -p $pid1 # idle class
ionice -c 1 -n 0 -p $pid2 # realtime class

sleep 60
