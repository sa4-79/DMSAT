#!/bin/sh
#setting time out value for an instance;
TIMEOUT="1200";
export TIMEOUT
# Setting the value for the job cohort size
for CS in 4 8 12 16 24 32
do 
COHORTSIZE=$CS;
export COHORTSIZE
MAXCPUS=$CS;
export MAXCPUS
# Setting the value for the wait time before subittng a new cohort of jobs
   for WT in 20 40 100 150 200 300
      do
        WAITTIME=$WT;
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

outFile=${CS}_${WT}
echo $outFile
#run the solver
    for i in $(cat Lists/listsat)
    do
    echo '*********************************************************'>> /home/sasghar/test/test.out
    echo $i >> OutPuts/OutputDetailed/$outFile
    ./DMSAT $i >> OutPuts/OutputDetailed/$outFile
     qdel -u sasghar 
  #dig -p 54 @192.168.0.3 $i axfr > $i.hosts
    done
  done
done

