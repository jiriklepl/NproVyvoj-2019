
echo "$(((RANDOM % 63500) + 1500))" | ltrace -Sc -o ltrace.log bin/server &
PID=$!
sleep 1 # should be safe
kill $(pgrep -P $PID)
sleep 1 # to have nice output
c++filt < ltrace.log # demangles all names
