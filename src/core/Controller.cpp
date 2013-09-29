/*
 * Controller.cpp
 *
 *  Created on: Sep 22, 2012
 *      Author: MacBookPro
 */

#include "Controller.h"


using namespace std;
pthread_t thread;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
struct Argumnets {
   int argc;
   char ** argv;
};


int main(int argc, char *argv[])
{

	 if( argc != 2 )
	   {
		 cout<<"missing arguments"<<endl;
		 exit(0);
	   }
	 SetEnv();

	string argvstr;
	for (int i =1;i<argc;i++)
		argvstr=(string)argv[i]+",";
	//mainSolver(argc,argv);
	sartMain(argc,argv);
	submitthreads(argvstr);
	pthread_join( thread, NULL);
	//

return 0;
	// printStats1(*solver);
}

int SetEnv()
{
	/*************************************/
	string pPath;

	  pPath = getenv ("COHORTSIZE");
	  if (pPath.c_str()!=NULL)
		  pathlength= atoi(pPath.c_str());
	  else
	  {
		  cout<< "Environment variable COHORTSIZE is not set"<<endl;
		  exit(0);

	  }
	//  cout<<"pathlength="<<pathlength<<endl;

	  pPath = getenv ("WAITTIME");
	 	  if (pPath.c_str()!=NULL)
	 		  waitTime= atoi(pPath.c_str());
	 	  else
	 	  {
	 		  cout<< "Environment variable is not set"<<endl;
	 		 exit(0);


	 	  }
		//  cout<<"waitTime="<<waitTime<<endl;




	 	 pPath = getenv ("RAMPUPTIME");
	 	 	 	  if (pPath.c_str()!=NULL)
	 	 	 		initialWait= atoi(pPath.c_str());
	 	 	 	  else
	 	 	 	  {
	 	 	 		  cout<< "Environment variable RAMPUPTIME is not set"<<endl;
	 	 	 		 exit(0);


	 	 	 	  }

	 	// cout<<"initialWait="<<initialWait<<endl;




	  return 0;
	/**************************************/


}
void *submit(void* ptr)

{
	pthread_mutex_lock( &mutex1 );


	char* args=(char*) ptr;
	//cout<<"Recieved job ID"<<args<<endl;
	pthread_mutex_unlock( &mutex1 );


	jc.waitforJobs(args);


	return NULL;

}

void *submit1(void* ptr)

{
	//pthread_mutex_lock( &mutex1 );
	struct Argumnets *Data;
	Data =( struct Argumnets*)ptr;
	 pthread_mutex_unlock( &mutex1 );

	printf("**********************************************\n");
	mainSolver(Data->argc, Data->argv);
	printf("**********************************************\n");

	jc.cleanUp();
	exit(0);
return NULL;

}

void sartMain(int argc, char *argv[])
{

	struct Argumnets data;
	int    i = 0;
	    size_t n = 0;
	    memset(&data,0,sizeof(data));
	    data.argc = argc;
	    /* alloc one more element than 'argc' to terminate 's.argv' with NULL */
	    data.argv = (char**)malloc((argc + 1) * sizeof(char*));
	    /* terminate 's.argv' with NULL exactly as 'argv' in 'main' */
	    data.argv[argc] = NULL;
	    for(i = 0; i < argc; ++i)
	    {
	    	data.argv[i] = strdup(argv[i]);
	    }

		pthread_create( &thread, NULL, submit1, (void*) &data);
		sleep (1);




}

void submitthreads(string argv)
{
	//return;

	    pthread_t threads[N];
		int count=0;
		struct Argumnets data [N];
		Pdata *tdata;
		vector<string> tokens;
		string args[N];
		vector<char*> paths;
		sleep (initialWait);

		for(int i=0; i<N;i++)
		{


			args[i] = getPaths(pathlength);
		    tokens=Fewfirst(args[i],pathlength);
		    if(tokens.size()<=0)
		    {
		    	continue;
		    }
		    jc.current_batch=i;


			tdata = new Pdata;
			tdata->paths=tokens;
			tdata->argv=argv;


				/*for(unsigned int j=0;j<tokens.size();j++)
						   {
						   		  cout<<j+1<<": "<<tokens[j]<<endl;
						   }*/
				//sleep (10);
				//continue;


		//	string argb=argv+"-g,"+	tokens[j];
			//cout<<j+1<<": "<<argb<<endl;
			//paths=buildPaths(args,argc,argv);
		    //paths.push_back(NULL);

		   // cout<<"TMP =========="<<args<<endl;


	   pthread_create( &threads[i], NULL, BuildPaths, (void *) tdata);
	   //sleep(1);
							   //}
	    pthread_join( threads[i], NULL);
	    tokens.clear();
	 	sleep (waitTime);
		}


		WaitThreads(threads,N);


}

void WaitThreads(pthread_t thread[], const int N)
{
	for(int i=0;i<N;i++)
	{
    pthread_join( thread[i], NULL);
	}
}

vector<string> Fewfirst(string Pathstr, int length) {
	//int length=4;

	char * pch =(char*)Pathstr.c_str();
	vector<char*> tokens;
	vector<string> FewF;
		 pch = strtok (pch," ,.");
		  while (pch != NULL)
		  {
			  tokens.push_back(pch);
			  pch = strtok (NULL, " ,.");
		  }
if(tokens.size()<length)
length=tokens.size();
		  string path="";
		  string mainPath;
		  string p1="";
		  string p2="";
		  if((tokens.size())<=0)
		  {
			  return FewF;
		  }

		  for(unsigned int i=0;i<tokens.size()-length;i++)
		 		  {
		 			  p1+=(string)tokens[i]+",";
		 			  p2+=(string)tokens[i]+",";


		 		  }

		 		   p1+=tokens[tokens.size()-length];
		 		   p2+="-"+(string)tokens[tokens.size()-length];
		 		  string p1a;//=p1+",";
		 		 string p2a;//=p2+",";
		 		// cout<<p1<<endl;
		 		 //cout<<p2<<endl;




		 		  for(unsigned int i=tokens.size()-length;i<tokens.size();i++)
		 		  {
		 			   p1a=p1+",";
		 			   p2a=p2+",";

		 			 for(unsigned int j=tokens.size()-length+1;j<i+1; j++)
		 			 {

		 				 if(j==i)
		 				 {
		 				     mainPath+=p1a + "-"+ tokens[j]+"#";
		 				     mainPath+=p2a+"-"+tokens[j]+"#";
		 					// path+=p1+tokens[j]+"-";
		 					 //path+=
		 				 }
		 				 else
		 				 {
		 					 p1a+=(string)tokens[j]+",";
		 					 p2a+=(string)tokens[j]+",";
		 				 }

		 			 }
		 			 //count++;
		 		  }
		 		  p1a=p1+",";
		 		  p2a=p2+",";
		 		  for(unsigned int i=tokens.size()-length+1;i<tokens.size();i++)
		 		  		  {
		 			  p1a+= (string)tokens[i]+",";
		 			  p2a+=(string)tokens[i]+",";
		 		  		  }
		 		  p1a+="#";
		 		  p2a+="#";

mainPath+=p1a+p2a;
//cout<<mainPath<<endl;
tokens.clear();

free(pch);
char *pch2 =(char*)mainPath.c_str();
pch2 = strtok (pch2," #");
		  while (pch2 != NULL)
		  {
			 // cout<<"Pch: "<<pch<<endl;


			  FewF.push_back((string)pch2);
			  pch2 = strtok (NULL, " #");
		  }




return FewF;


}
void *BuildPaths(void* ptr)
{

	pthread_t threads[ThreadN];
	string JIDs[ThreadN];
	vector<string> tokens;
	Pdata *P_data;
	P_data=(Pdata *) ptr;
	tokens=P_data->paths;
	string argv=P_data->argv;
	for(unsigned int j=0;j<tokens.size();j++)
	   {
		 string path=argv+"-g,"+tokens[j];



					 JIDs[j]=SbmitJobs((char *)path.c_str());
					//cout<<"Submitted Job ID ="<<JIDs[j]<<endl;
			 pthread_create( &threads[j], NULL, submit, (void *) JIDs[j].c_str());
		}


	free(ptr);
	pthread_exit(NULL);
}
char* SbmitJobs(char* paths)
{
		vector<char*> tokens;
		vector<string> ThreadPath;


		 char * pch;

		 pch = strtok (paths," ,.");
		  while (pch != NULL)
		  {
			  ThreadPath.push_back((string)pch);
			 // cout <<"Argv ="<<(string)pch<<endl;
			  pch = strtok (NULL, " ,.");
		  }
		  free(pch);

		return jc.runAsyncjob(ThreadPath, "//home//sasghar//test/test.out.");



}

