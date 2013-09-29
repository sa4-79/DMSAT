#!/bin/sh
# Setting the value for the job cohort size
 COHORTSIZE="4";
export COHORTSIZE
# Setting the value for the wait time before subittng a new cohort of jobs

 WAITTIME="20";
export WAITTIME

# Setting the value for initial ramp-up time 

RAMPUPTIME="15"
export RAMPUPTIME

#setting the value for the path to the worker solver 

WORKERSOLVER="/home/sasghar/test/minisat/core/minisat_static"
export WORKERSOLVER

#setting the value of temporary ioutpit file
OUTPUTFILE="://home//sasghar//test/test.out"
export OUTPUTFILE

#run the solver

time LD_LIBRARY_PATH=/opt/n1ge/lib/lx24-amd64/ ./DMSAT /home/sasghar/test/file1

