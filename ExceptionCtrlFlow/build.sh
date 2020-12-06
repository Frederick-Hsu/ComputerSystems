# File          : build.sh
# Description   : This shell script is used to build the ExceptionCtrlFlow
#


echo "Build and execute the fork..."
# compile the fork.c source file
gcc fork.c -o fork ../liberror/liberror.so

# and execute the fork application
./fork
echo
sleep 2


echo "Build and execute the fork_twice..."
gcc fork_twice.c -o fork_twice ../liberror/liberror.so
./fork_twice
echo
sleep 2


echo "Build and execute the fork_triple..."
gcc fork_triple.c -o fork_triple ../liberror/liberror.so
./fork_triple
echo
sleep 2


echo "Build and execute the waitprob..."
gcc waitprob.c -o waitprob ../liberror/liberror.so
./waitprob

sleep 2
echo "Build and execute the waitprob1..."
gcc waitprob1.c -o waitprob1 ../liberror/liberror.so
./waitprob1


echo "Build and execute the myecho..."
gcc myecho.c -o myecho
./myecho arg1 arg2