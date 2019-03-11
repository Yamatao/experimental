#!/usr/bin/env bash

# idle
ionice -c 3 dd if=/dev/zero of=kek1.txt bs=1M count=800 oflag=direct 2>time_1 &
ionice -c 3 dd if=/dev/zero of=kek2.txt bs=1M count=800 oflag=direct 2>time_2 &
ionice -c 3 dd if=/dev/zero of=kek3.txt bs=1M count=800 oflag=direct 2>time_3 &
ionice -c 3 dd if=/dev/zero of=kek4.txt bs=1M count=800 oflag=direct 2>time_4 &

# realtime
ionice -c 1 dd if=/dev/zero of=kekr.txt bs=1M count=800 oflag=direct 2>time_r &

wait

echo "Time of an 'idle' class process:"
cat time_1
echo "Time of a 'realtime' class process:"
cat time_r
