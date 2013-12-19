/*
 * JobController.h
 *
 *  Created on: 2011-08-17
 *      Author: sasghar
 */
#ifndef JOBCONTROLLER_H_
#define JOBCONTROLLER_H_
#include <string.h>
#include <iostream>
#include<vector>
#include<map>
#include<time.h>
#include <pthread.h>

using namespace std;
class JobController {
private:
	map<int,int> batchCounter;
	string solverPAth;
	string outPutPath;


public:

	int current_batch;
	clock_t StartTime;
	pthread_mutex_t mutex1;
	vector<string> jobsIds;
	char* outputFile;
	JobController();
	virtual ~JobController();
	bool runjob(vector<string> argv, char* outPut );

	string runAsyncjob(vector<string> argv, char* outPut );
	bool analysis(char* outPut);
	bool waitforJobs(string jobid);
	bool cleanUp();
};

#endif /* JOBCONTROLLER_H_ */
