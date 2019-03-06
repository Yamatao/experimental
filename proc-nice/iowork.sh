./a.out first &
pid1="$!"
echo "pid1=$pid1"

./a.out second &
pid2="$!"
echo "pid2=$pid2"

echo "first process ionice before: `ionice -p $pid1`"
echo "second process ionice before: `ionice -p $pid2`"
ionice -c 3 -p $pid1
ionice -c 1 -n 0 -p $pid2
echo "first process ionice after: `ionice -p $pid1`"
echo "second process ionice after: `ionice -p $pid2`"

sleep 60
