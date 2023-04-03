cd libpriqueue
gcc -c libpriqueue.c -o libpriqueue.o
cd ..;gcc queuetest.c libpriqueue/libpriqueue.o -o results
./results