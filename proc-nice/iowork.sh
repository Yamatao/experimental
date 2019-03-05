./a.out first &
pid1="$!"

./a.out second &
pid2="$!"

#renice -n -20 -p $pid2
ionice -c 2 -n 7 -p $pid1
ionice -c 2 -n 0 -p $pid2

sleep 30
