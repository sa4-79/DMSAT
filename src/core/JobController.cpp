/*
 * JobController.cpp
 *
 *  Created on: 2011-08-17
 *      Author: sasghar
 */

#include <stdio.h>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <drmaa.h>
#include <string>
#include <fstream>
#include "JobController.h"
using namespace std;

JobController::JobController()
{
//	 mutex1 = PTHREAD_MUTEX_INITIALIZER;
	 char error[DRMAA_ERROR_STRING_BUFFER];
	 current_batch=0;
		    int errnum = 0;
	errnum = drmaa_init (NULL, error, DRMAA_ERROR_STRING_BUFFER);

		    if (errnum != DRMAA_ERRNO_SUCCESS) {
		       fprintf (stderr, "Could not initialize the DRMAA library: %s\n", error);

		    }

		    string pPath;

		    pPath = getenv ("WORKERSOLVER");
		   	 	 	 	 if (pPath.c_str()!=NULL)
		   	 	 	 		 solverPAth=pPath;
		   	 	 	 	else
		   	 	 	 		  {
		   	 	 	 		 	cout<< "Environment variable WORKERSOLVER is not set"<<endl;
		   	 	 	 		 	exit(0);


		   	 	 	 		  }

		   	 		 	// cout<<"jc.solverPAth="<<solverPAth<<endl;


		   	 	 pPath = getenv ("OUTPUTFILE");
		   	 	 	 	 if (pPath.c_str()!=NULL)
		   	 	 	 		 outPutPath=pPath;
		   	 	 	 	 else
		   	 	 	 		  {
		   	 	 	 		 	 	cout<< "Environment variable OUTPUTFILE is not set"<<endl;
		   	 	 	 		 	 	 exit(0);


		   	 	 	 		 	 }
		   	 		 	// cout<<"jc.outPutPath="<<outPutPath<<endl;


		   	 	 	     if(remove(pPath.substr(1).c_str())!= 0)
		   	 	 	 	    cout<<"Error deleting file"<<endl;
		   	 	 	 	 else
		   	 	 	 	    cout<<"File successfully deleted"<<endl;

		    /* solverPAth="/home/sasghar/test/minisat/core/minisat_static";
		     outPutPath="://home//sasghar//test/test.out";
		     string temp=outPutPath;
		     if(remove(temp.substr(1).c_str())!= 0)
		         cout<<"Error deleting file"<<endl;
		      else
		         cout<<"File successfully deleted"<<endl;*/

}

JobController::~JobController() {
	// TODO Auto-generated destructor stub
}

bool JobController::runjob(vector<string> argv, char* outPut )
{
	pthread_mutex_lock( &mutex1);
	char error[DRMAA_ERROR_STRING_BUFFER];
	    int errnum = 0;
	    drmaa_job_template_t *jt = NULL;

	    const char** bargv= (const char**)malloc((argv.size() + 1) * sizeof(const char*));
	    	    /* terminate 's.argv' with NULL exactly as 'argv' in 'main' */
	    bargv[argv.size()] = NULL;
	    	    for(int i = 0; i < argv.size(); ++i)
	    	    {
	    	    	bargv[i] = (const char*)strdup(argv[i].c_str());
	    	    }


	   pthread_mutex_unlock( &mutex1 );

	  	  // return true;





	    errnum = drmaa_allocate_job_template (&jt, error, DRMAA_ERROR_STRING_BUFFER);

	    if (errnum != DRMAA_ERRNO_SUCCESS) {
	       fprintf (stderr, "Could not create job template: %s\n", error);
	    }
	    else {

			errnum = drmaa_set_attribute( jt, DRMAA_OUTPUT_PATH,
					(const char*)outPutPath.c_str(), error,
	    	        DRMAA_ERROR_STRING_BUFFER - 1);


			errnum = drmaa_set_attribute (jt, DRMAA_REMOTE_COMMAND,(const char*)solverPAth.c_str(),
				                                    error, DRMAA_ERROR_STRING_BUFFER);
	      		/* errnum = drmaa_set_attribute (jt, DRMAA_REMOTE_COMMAND,"/home/sasghar/test/minisat.sh",
	                                    error, DRMAA_ERROR_STRING_BUFFER);
				  drmaa_set_attribute(jt, DRMAA_NATIVE_SPECIFICATION, "-w n -b no",
	    		   	   	   	   error, DRMAA_ERROR_STRING_BUFFER - 1);*/
			drmaa_set_attribute(jt, DRMAA_NATIVE_SPECIFICATION, "-j y -w n -b yes -l h_rt=24:00:00 -cwd",
				    		   	   	   	   error, DRMAA_ERROR_STRING_BUFFER - 1);


	       if (errnum != DRMAA_ERRNO_SUCCESS) {
	          fprintf (stderr, "Could not set attribute \"%s\": %s\n",
	                   DRMAA_REMOTE_COMMAND, error);
	       }
	       else {
	         // const char *args[2] = {CNF, NULL};

	          errnum = drmaa_set_vector_attribute (jt, DRMAA_V_ARGV, bargv, error,
	                                              DRMAA_ERROR_STRING_BUFFER);

	  	    //cout<<"*****************CNF"<<bargv[0]<<"*******************"<<endl;
	          free(bargv);

	  	 // free(bargv);

	       }

	       if (errnum != DRMAA_ERRNO_SUCCESS) {
	          fprintf (stderr, "Could not set attribute \"%s\": %s\n",
	                   DRMAA_REMOTE_COMMAND, error);
	       }
	       else {
	          char jobid[DRMAA_JOBNAME_BUFFER];
	          char jobid_out[DRMAA_JOBNAME_BUFFER];
	          int status = 0;
	          drmaa_attr_values_t *rusage = NULL;

	          errnum = drmaa_run_job (jobid, DRMAA_JOBNAME_BUFFER, jt, error,
	                                  DRMAA_ERROR_STRING_BUFFER);

	          if (errnum != DRMAA_ERRNO_SUCCESS) {
	             fprintf (stderr, "Could not submit job: %s\n", error);
	          }
	          else {
	             //printf ("Your job has been submitted with id %s\n", jobid);
	             jobsIds.push_back(jobid);
	            // pthread_mutex_unlock( &mutex1 );

	            errnum = drmaa_wait (jobid, jobid_out, DRMAA_JOBNAME_BUFFER, &status,
	                                  DRMAA_TIMEOUT_WAIT_FOREVER, &rusage, error,
	                                  DRMAA_ERROR_STRING_BUFFER);

	             if (errnum != DRMAA_ERRNO_SUCCESS) {
	                fprintf (stderr, "Could not wait for job: %s\n", error);
	             }
	             else {
	                char usage[DRMAA_ERROR_STRING_BUFFER];
	                int aborted = 0;

	                drmaa_wifaborted(&aborted, status, NULL, 0);

	                if (aborted == 1) {
	                   printf("Job %s never ran\n", jobid);
	                }
	                else {
	                   int exited = 0;

	                   drmaa_wifexited(&exited, status, NULL, 0);

	                   if (exited == 1) {
	                      int exit_status = 0;

	                      drmaa_wexitstatus(&exit_status, status, NULL, 0);
	                      printf("Job %s finished regularly with exit status %d\n", jobid, exit_status);
	                      analysis(outPut);
	                      //
	                      return false;
	                   }
	                   else {
	                      int signaled = 0;

	                      drmaa_wifsignaled(&signaled, status, NULL, 0);

	                      if (signaled == 1) {
	                         char termsig[DRMAA_SIGNAL_BUFFER+1];

	                         drmaa_wtermsig(termsig, DRMAA_SIGNAL_BUFFER, status, NULL, 0);
	                         printf("Job %s finished due to signal %s\n", jobid, termsig);
	                      }
	                      else {
	                         printf("Job %s finished with unclear conditions\n", jobid);
	                      }
	                   } /* else */
	                } /* else*/

	                //printf ("Job Usage:\n");

	              /*  while (drmaa_get_next_attr_value (rusage, usage, DRMAA_ERROR_STRING_BUFFER) == DRMAA_ERRNO_SUCCESS) {
	                   printf ("  %s\n", usage);
	                }*/

	                drmaa_release_attr_values (rusage);
	             } /* else */
	          } /* else */
	       } /* else */

	       errnum = drmaa_delete_job_template (jt, error, DRMAA_ERROR_STRING_BUFFER);

	       if (errnum != DRMAA_ERRNO_SUCCESS) {
	          fprintf (stderr, "Could not delete job template: %s\n", error);
	       }
	    } /* else */

	    errnum = drmaa_exit (error, DRMAA_ERROR_STRING_BUFFER);

	    if (errnum != DRMAA_ERRNO_SUCCESS) {
	       fprintf (stderr, "Could not shut down the DRMAA library: %s\n", error);
	   		exit(0);
	       return 1;


	    }

	    return 0;
}
bool JobController::analysis(char* outPut)
	{

    string str;


   // ifstream myfile(outPut);
	 string temp=outPutPath;

	ifstream myfile(temp.substr(1).c_str());
	       if(!myfile) //Always test the file open.
	    {
	                cout<<"Error opening output file "<<outPut<<endl;
	                return -1;
	    }
	    while(!myfile.eof())
	    {
	   	getline(myfile,str);
	   	if(str=="SATISFIABLE")
	   	{
	   		cout<<"SATISFIABLE"<<endl;
	   		cleanUp();
	   		exit(0);

	   	}

	    }

	}
bool JobController::waitforJobs(string jobid)
{
	 char jobid_out[DRMAA_JOBNAME_BUFFER];
	 char jobidu[DRMAA_JOBNAME_BUFFER];
	strcpy(jobidu, jobid.c_str());

	 char error[DRMAA_ERROR_STRING_BUFFER];
	 int status = 0;
	 int errnum = 0;
	int batchId=current_batch;
	batchCounter[batchId]+=1;
	jobsIds.push_back(jobid);

	/* errnum = drmaa_init (NULL, error, DRMAA_ERROR_STRING_BUFFER);

	 			if (errnum != DRMAA_ERRNO_SUCCESS) {
	 				fprintf (stderr, "Could not initialize the DRMAA library: %s\n", error);
	 				return NULL;
	 				 }*/

		          drmaa_attr_values_t *rusage = NULL;

		          {
           	         // cout<<"Job started"<<"Batch Id "<<batchId<<" Batch Id Coun="<<batchCounter[batchId]<<endl;

		        	            errnum = drmaa_wait (jobidu, jobid_out, DRMAA_JOBNAME_BUFFER, &status,
		        	                                  DRMAA_TIMEOUT_WAIT_FOREVER, &rusage, error,
		        	                                  DRMAA_ERROR_STRING_BUFFER);

		        	             if (errnum != DRMAA_ERRNO_SUCCESS) {
		        	               // fprintf (stderr, "Could not wait for job: %s\n", error);
		        	             }
		        	             else {
		        	                char usage[DRMAA_ERROR_STRING_BUFFER];
		        	                int aborted = 0;

		        	                drmaa_wifaborted(&aborted, status, NULL, 0);

		        	                if (aborted == 1) {
		        	                  // printf("Job %s never ran\n and clenedup", jobid);
		        	                }
		        	                else {
		        	                   int exited = 0;

		        	                   drmaa_wifexited(&exited, status, NULL, 0);

		        	                   if (exited == 1) {
		        	                      int exit_status = 0;

		        	                      drmaa_wexitstatus(&exit_status, status, NULL, 0);
		        	                      //printf("Job %s finished regularly with exit status %d\n", jobidu, exit_status);
		        	                      if(exit_status==10)
		        	                      {
		        	                    	  cout<<"Formula is SATISFIABLE"<<endl
		        	                    		  <<"Output model is written in the file "<<outPutPath<<endl;
		        	                    	  printf("Time taken: %.2fs\n", (double)(clock() - StartTime)/CLOCKS_PER_SEC);
		        	                    	  	   		cleanUp();
		        	                    	  	   		exit(0);
		        	                      }
		        	                      else
		        	                      {
		        	                      //analysis("//home//sasghar//test/test.out");
		        	                      batchCounter[batchId]-=1;
		        	                      }
		        	           	        //  cout<<"Job finished with UNSATISFIABLE"<<"Batch Id "<<batchId<<" Batch Id Coun="<<batchCounter[batchId]<<endl;

		        	           	     if(batchCounter[batchId]<=0)
		        	           	     {
		        	           	    	cout<<"Formula is UNSATISFIABLE"<<endl;
		        	           	    	printf("Time taken: %.2fs\n", (double)(clock() - StartTime)/CLOCKS_PER_SEC);
		        	           	    	cleanUp();
		        	           	 	    exit(20);

		        	           	     }

		        	                      //
		        	                      return false;
		        	                   }
		        	                   else {
		        	                      int signaled = 0;

		        	                      drmaa_wifsignaled(&signaled, status, NULL, 0);

		        	                      if (signaled == 1) {
		        	                         char termsig[DRMAA_SIGNAL_BUFFER+1];

		        	                         drmaa_wtermsig(termsig, DRMAA_SIGNAL_BUFFER, status, NULL, 0);
		        	                         printf("Job %s finished due to signal %s\n", jobidu, termsig);
		        	                      }
		        	                      else {
		        	                         printf("Job %s finished with unclear conditions\n", jobidu);
		        	                      }
		        	                   } /* else */
		        	                } /* else*/

		        	                //printf ("Job Usage:\n");

		        	              /*  while (drmaa_get_next_attr_value (rusage, usage, DRMAA_ERROR_STRING_BUFFER) == DRMAA_ERRNO_SUCCESS) {
		        	                   printf ("  %s\n", usage);
		        	                }*/

		        	                drmaa_release_attr_values (rusage);
		        	             } /* else */
		        	          }/* else */
		          /*errnum = drmaa_exit (error, DRMAA_ERROR_STRING_BUFFER);

		         	    if (errnum != DRMAA_ERRNO_SUCCESS) {
		         	       fprintf (stderr, "Could not shut down the DRMAA library: %s\n", error);
		         	    }*/

		         	       return true;

	}
bool JobController::cleanUp()
{
	int errnum = 0;
	  char error[DRMAA_ERROR_STRING_BUFFER];
	  int freeedCpus=0;
	  int runningCpus=0;

  	 for(unsigned int i=0;i<jobsIds.size();i++)
  	 {
  		//cout<<jobsIds[i]<<endl;
  		errnum = drmaa_control (jobsIds[i].c_str(), DRMAA_CONTROL_TERMINATE, error, DRMAA_ERROR_STRING_BUFFER);
  		if (errnum != DRMAA_ERRNO_SUCCESS)
  		{
  		   fprintf (stderr, "Could not kill job: %s\n", error);
  		 freeedCpus++;

  		}

  		else
  		{
  			//cout<<"job #"<<jobsIds[i]<<" killed successfully"<<endl;
  			runningCpus++;
  		}

  	 }
  	cout<< runningCpus <<" running jobs are killed successfully, total number of reused CPUs is "<<freeedCpus<<endl;
  	errnum = drmaa_exit (error, DRMAA_ERROR_STRING_BUFFER);
  					if (errnum != DRMAA_ERRNO_SUCCESS) {
  						fprintf (stderr, "Could not shut down the DRMAA library: %s\n", error);
  						return NULL;
  					}


}

string JobController::runAsyncjob(vector<string> argv, char* outPut )
{
	// cout<<"jc.outPutPath="<<outPutPath<<endl;

	const char** bargv= (const char**)malloc((argv.size() + 1) * sizeof(const char*));
		    bargv[argv.size()] = NULL;
		    	    for(int i = 0; i < argv.size(); ++i)
		    	    {
		    	    	bargv[i] = (const char*)strdup(argv[i].c_str());
		    	    }


		  // cout<<"*****************CNF"<<bargv[2]<<"*******************"<<endl;


		   char jobid[DRMAA_JOBNAME_BUFFER];
		   char error[DRMAA_ERROR_STRING_BUFFER];
		   int errnum = 0;
		   drmaa_job_template_t *jt = NULL;

			/*errnum = drmaa_init (NULL, error, DRMAA_ERROR_STRING_BUFFER);

			if (errnum != DRMAA_ERRNO_SUCCESS) {
				fprintf (stderr, "Could not initialize the DRMAA library: %s\n", error);
				return NULL;
				 }*/

			errnum = drmaa_allocate_job_template (&jt, error, DRMAA_ERROR_STRING_BUFFER);

			if (errnum != DRMAA_ERRNO_SUCCESS) {
				fprintf (stderr, "Could not create job template: %s\n", error);
				}
				else {
					errnum = drmaa_set_attribute( jt, DRMAA_OUTPUT_PATH,
							(const char*)outPutPath.c_str(), error,
									DRMAA_ERROR_STRING_BUFFER - 1);



							errnum = drmaa_set_attribute (jt, DRMAA_REMOTE_COMMAND,(const char*)solverPAth.c_str(),
																	error, DRMAA_ERROR_STRING_BUFFER);
							drmaa_set_attribute(jt, DRMAA_NATIVE_SPECIFICATION, "-j y -w n -b yes -l h_rt=24:00:00 -cwd",
														   error, DRMAA_ERROR_STRING_BUFFER - 1);

				   if (errnum != DRMAA_ERRNO_SUCCESS) {
					   fprintf (stderr, "Could not set attribute \"%s\": %s\n",
						 DRMAA_REMOTE_COMMAND, error);
					   }
				   else {
					 //  const char *args[2] = {"5", NULL};

					   errnum = drmaa_set_vector_attribute (jt, DRMAA_V_ARGV, bargv, error,
																	  DRMAA_ERROR_STRING_BUFFER);
				   }

				   if (errnum != DRMAA_ERRNO_SUCCESS) {
					   fprintf (stderr, "Could not set attribute \"%s\": %s\n",
							   DRMAA_REMOTE_COMMAND, error);
				   }
				   else {


					   errnum = drmaa_run_job (jobid, DRMAA_JOBNAME_BUFFER, jt, error,
							   DRMAA_ERROR_STRING_BUFFER);

					   if (errnum != DRMAA_ERRNO_SUCCESS) {
						   fprintf (stderr, "Could not submit job: %s\n", error);
					   }
					   else {
						  // printf ("Your job has been submitted with id %s\n", jobid);

					   }
				   } /* else */

				   errnum = drmaa_delete_job_template (jt, error, DRMAA_ERROR_STRING_BUFFER);

				   if (errnum != DRMAA_ERRNO_SUCCESS) {
					   fprintf (stderr, "Could not delete job template: %s\n", error);
				   }
				} /* else */
				/*errnum = drmaa_exit (error, DRMAA_ERROR_STRING_BUFFER);
				if (errnum != DRMAA_ERRNO_SUCCESS) {
					fprintf (stderr, "Could not shut down the DRMAA library: %s\n", error);
					return NULL;
				}*/
				return string(jobid);

	}

