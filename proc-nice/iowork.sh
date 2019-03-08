mkdir tmp

for i in {1..30}; do
	./a.out idle_$i &
	pid=$!
	ionice -c 3 -p $pid # idle class
	ionice -p $pid
done

./a.out realtime_1 &
pid="$!"
ionice -c 1 -n 0 -p $pid # realtime class
ionice -p $pid

sleep 60
