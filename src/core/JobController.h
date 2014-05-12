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
<<<<<<< HEAD
	int freedCpus;
    int runningCpus;
    int ReusedCpus;
=======
>>>>>>> eea7d1c5f1ceb25f3a27978b9d79de1cf58fbc40


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
<<<<<<< HEAD
	int getNumRunningJobs();
	int getNumSubmitted();
	int getNumFinished();
	void setReused(int Cpus);
=======
>>>>>>> eea7d1c5f1ceb25f3a27978b9d79de1cf58fbc40
	bool analysis(char* outPut);
	bool waitforJobs(string jobid);
	bool cleanUp();
};

#endif /* JOBCONTROLLER_H_ */
