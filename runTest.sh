LD_LIBRARY_PATH=/usr/local/lib ./server &
sleep 1
./client 1 &
./client 2 &
./client 3 &
./client 4 &
sleep 4
for x in `jobs -p |tac`
do
    kill $x
    sleep 1
done

