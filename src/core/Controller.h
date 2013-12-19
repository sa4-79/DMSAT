/*
 * Controller.h
 *
 *  Created on: Sep 22, 2012
 *      Author: MacBookPro
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "zhelpers.h"
#include "Main.h"
#include <string.h>
#include <map>
#include<vector>
#include "JobController.h"
#include <ctime>
#include <stdlib.h>

#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>


typedef struct PathData {
	vector<string> paths;
	string argv;
} Pdata;

//submuitters
const int SUBSCRIBERS_EXPECTED=1;

const int N=12;
int timeoutVal=1200; //Default Timeout
int pathlength=4;
int waitTime=1200;
int initialWait=15;
//vector<string> LearnetClausesLocal;
vector<string> LearnetClauses;
bool readLock=false;
bool writeLock=false;
const int ThreadN=pathlength*2;
void sartMain(int argc, char *argv[]);
void submitthreads(string argv);
// threads
JobController jc;
void *TimeoutEx(void* ptr);
void *BuildPaths(void* ptr);
void *submit(void* ptr);
void *submit1(void* ptr);
string SbmitJobs(char* paths);
void *communicator(void* ptr);
void *Broker(void* ptr);
void *Publisher(void* ptr);
void WaitThreads(pthread_t thread[], const int N);
int SetEnv();
//vector<string> LearnetClauses;


vector<string> Fewfirst(string Pathstr,int length);

#endif /* CONTROLLER_H_ */
