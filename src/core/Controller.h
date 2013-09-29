/*
 * Controller.h
 *
 *  Created on: Sep 22, 2012
 *      Author: MacBookPro
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "Main.h"
#include <string.h>
#include <map>
#include<vector>
#include "JobController.h"
#include <ctime>
#include <stdlib.h>

typedef struct PathData {
	vector<string> paths;
	string argv;
} Pdata;

//submuitters
const int N=12;
int pathlength=4;
int waitTime=1200;
int initialWait=15;
const int ThreadN=pathlength*2;
void sartMain(int argc, char *argv[]);
void submitthreads(string argv);
// threads
JobController jc;
void *BuildPaths(void* ptr);
void *submit(void* ptr);
void *submit1(void* ptr);
char* SbmitJobs(char* paths);
void WaitThreads(pthread_t thread[], const int N);
int SetEnv();

vector<string> Fewfirst(string Pathstr,int length);

#endif /* CONTROLLER_H_ */
