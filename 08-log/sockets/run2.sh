PORT=$(((RANDOM % 63500) + 1500))
echo "$PORT" | ltrace -Sc -o ltrace.log bin/server &
PID=$!
for i in $(seq 1 100); do
    printf "localhost\n$PORT\nmessage\n.\n" | bin/client
done
kill $(pgrep -P $PID)
c++filt < ltrace.log # demangles all names
