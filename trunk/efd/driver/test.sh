export	LD_LIBRARY_PATH=`pwd`
./efd1 on 1
sleep 2
./efd1 on 2
sleep 2	
./efd1 on 4
sleep 2
./efd1 off 7
sleep 2
./efd1 cycle_on 1
sleep 4
./efd1 cycle_on 2
sleep 4
./efd1 cycle_on 3
sleep 4
./efd1 cycle_off 0
