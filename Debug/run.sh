#!/bin/sh
#setting time out value for an instance;
TIMEOUT="1200";
export TIMEOUT
# Setting the value for the job cohort size
 COHORTSIZE="8";
export COHORTSIZE
# Setting the value for the wait time before subittng a new cohort of jobs

 WAITTIME="30";
export WAITTIME

# Setting the value for initial ramp-up time 

RAMPUPTIME="5"
export RAMPUPTIME

#setting the value for the path to the worker solver 

WORKERSOLVER="/benchmark/minisat/core/minisat"

export WORKERSOLVER

#setting the value of temporary inputpit file, the path should always start with ://
OUTPUTFILE="://test/test.out"
export OUTPUTFILE

 ./DMSAT Random/SAT11/SAT11/random/medium/unif-k3-r4.26-v250-c1065-S266251785-083.UNKNOWN.cnf
