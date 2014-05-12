#!/bin/sh
#setting time out value for an instance;
TIMEOUT="1200";
export TIMEOUT
# Setting the value for the job cohort size
 COHORTSIZE="8";
export COHORTSIZE
# Setting the value for the wait time before subittng a new cohort of jobs

 WAITTIME="60";
export WAITTIME

# Setting the value for initial ramp-up time 

RAMPUPTIME="5"
export RAMPUPTIME

#setting the value for the path to the worker solver 

#WORKERSOLVER="/home/sasghar/test/minisat/core/minisat"
WORKERSOLVER="/home/sasghar/benchmark/minisat/core/minisat"

export WORKERSOLVER

#setting the value of temporary ioutpit file
OUTPUTFILE="://home//sasghar//test/test.out"
export OUTPUTFILE

#run the solver
for i in $(cat Lists/list | grep -v '#')
do
echo $i
 ./DMSAT $i
  qdel -u sasghar
done
#time ./DMSAT /home/sasghar/Random/RandomBench/SAT09/RANDOM/MEDIUM/3SAT/UNKNOWN/400/unif-k3-r4.25-v400-c1700-S387386125-069.cnf
 #./DMSAT /home/sasghar/Random/unsat/unifk3r425v360c1530S1028159446096 

#valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./DMSAT  /home/sasghar/Random/SAT/unifk3r425v360c1530S1459690542033

#time ./DMSAT  /home/sasghar/Random/SAT/unif-k3-r4.25-v360-c1530-S1459690542-033.cnf

#time ./DMSAT /home/sasghar/Random/unsat/unifk3r425v360c1530S1369720750015
#time ./DMSAT  /home/sasghar/Random/SAT/unifk3r425v380c1615S1041106011094
