# File          : build.sh
# Description   : This shell script is used to build the ExceptionCtrlFlow
#


echo "Build and execute the fork..."
# compile the fork.c source file
gcc fork.c -o fork.o ../liberror/liberror.so

# and execute the fork application
./fork.o
echo
sleep 2


echo "Build and execute the fork_twice..."
gcc fork_twice.c -o fork_twice.o ../liberror/liberror.so
./fork_twice.o
echo
sleep 2


echo "Build and execute the fork_triple..."
gcc fork_triple.c -o fork_triple.o ../liberror/liberror.so
./fork_triple.o
echo
sleep 2


echo "Build and execute the waitprob..."
gcc waitprob.c -o waitprob.o ../liberror/liberror.so
./waitprob.o

sleep 2
echo "Build and execute the waitprob1..."
gcc waitprob1.c -o waitprob1.o ../liberror/liberror.so
./waitprob1.o


echo "Build and execute the myecho..."
gcc myecho.c -o myecho.o
./myecho.o arg1 arg2
