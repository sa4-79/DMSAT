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
	jc.StartTime=clock();
<<<<<<< HEAD
	exec(" qstat -g c | grep -v 'eela.q\\|tech.q\\|test.q' | awk '{Avaliable+=$3} { Used+=$4} {total+=$5} END {print Avaliable, Used, total}'");
=======
	exec(" qstat -g c | awk '{Avaliable+=$3} { Used+=$4} {total+=$5} END {print Avaliable, Used, total}'");
>>>>>>> eea7d1c5f1ceb25f3a27978b9d79de1cf58fbc40


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
	pPath = getenv ("TIMEOUT");
		  if (pPath.c_str()!=NULL)
			  timeoutVal= atoi(pPath.c_str());
		  else
		  {
			  cout<< "Environment variable TIMEOUT is not set"<<endl;
			  exit(0);

		  }



	pPath = getenv ("COHORTSIZE");
	  if (pPath.c_str()!=NULL)
<<<<<<< HEAD
	  {
		  cohortSize= atoi(pPath.c_str());
		  pathlength=cohortSize/2;
	  }
=======
		  pathlength= atoi(pPath.c_str())/2;
>>>>>>> eea7d1c5f1ceb25f3a27978b9d79de1cf58fbc40
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
	pthread_mutex_unlock( &mutex1 );


	bool state =jc.waitforJobs(string(args));



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
	printf("Time taken: %.2fs\n", (double)(clock() - jc.StartTime)/CLOCKS_PER_SEC);
	jc.cleanUp();
	exit(0);
return NULL;

}

void sartMain(int argc, char *argv[])
{
	pthread_t threadComm, threadBroker, threadPub, threadTimeout;

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
		pthread_create( &threadBroker, NULL, Broker, NULL);
		pthread_create( &threadComm, NULL, communicator, NULL);
		pthread_create( &threadPub, NULL, Publisher, NULL);
		pthread_create( &threadTimeout, NULL, TimeoutEx, NULL);



		sleep (1);




}

void submitthreads(string argv)
{
	//return;

	    pthread_t threads[N];
		int count=0;
<<<<<<< HEAD
		int NumCpus=0;
=======
>>>>>>> eea7d1c5f1ceb25f3a27978b9d79de1cf58fbc40
		struct Argumnets data [N];
		Pdata *tdata;
		vector<string> tokens;
		string args[N];
		vector<char*> paths;
		sleep (initialWait);

		for(int i=0; i<N;i++)
		{


<<<<<<< HEAD
			/*NumCpus=jc.getNumFinished();
			cout<<"Number of free CPUS  "<<NumCpus<<" Max CPUs allowed are  "<<MAXCPUS<<endl;


			while(1)
			{
				NumCpus=jc.getNumFinished();
				if(jc.getNumSubmitted()==0)
					break;

				if (MAXCPUS/jc.getNumSubmitted() >=1 && MAXCPUS!=jc.getNumSubmitted())
				{
					pathlength=cohortSize/2;
					break;
				}
				if(jc.getNumSubmitted()-jc.getNumRunningJobs() >= 2)
				{
					cout<<"Number of avaliable CPUS  "<<jc.getNumSubmitted()-jc.getNumRunningJobs()<<endl;
					pathlength=(jc.getNumSubmitted()-jc.getNumRunningJobs())/2;
					jc.setReused(pathlength*2);
					break;

				}
				sleep(5);
			}
*/

=======
>>>>>>> eea7d1c5f1ceb25f3a27978b9d79de1cf58fbc40
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
			pthread_create( &threads[i], NULL, BuildPaths, (void *) tdata);
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
		 pch = strtok (pch," ,");
		  while (pch != NULL)
		  {
			  tokens.push_back(pch);
			  pch = strtok (NULL, " ,");
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
<<<<<<< HEAD
	int numthreads =pathlength*2;
	//pthread_t *threads = malloc(sizeof(pthread_t)*numthreads);
	pthread_t threads[numthreads];
	string JIDs[numthreads];
=======

	pthread_t threads[ThreadN];
	string JIDs[ThreadN];
>>>>>>> eea7d1c5f1ceb25f3a27978b9d79de1cf58fbc40
	vector<string> tokens;
	Pdata *P_data;
	P_data=(Pdata *) ptr;
	tokens=P_data->paths;
	string argv=P_data->argv;
	for(unsigned int j=0;j<tokens.size();j++)
	   {
		 string path=argv+"-g,"+tokens[j];



					 JIDs[j]=SbmitJobs((char *)path.c_str());
<<<<<<< HEAD
					// cout<<"Submitted Job ID ="<<JIDs[j]<<endl;
=======
					//cout<<"Submitted Job ID ="<<JIDs[j]<<endl;
>>>>>>> eea7d1c5f1ceb25f3a27978b9d79de1cf58fbc40
			 pthread_create( &threads[j], NULL, submit, (void *) JIDs[j].c_str());
		}


	free(ptr);
	pthread_exit(NULL);
}
string SbmitJobs(char* paths)
{
		vector<char*> tokens;
		vector<string> ThreadPath;


		 char * pch;

		 pch = strtok (paths," ,");
		  while (pch != NULL)
		  {
			  ThreadPath.push_back((string)pch);
			 // cout <<"Argv ="<<(string)pch<<endl;
			  pch = strtok (NULL, " ,");
		  }
		  free(pch);
		  //free(paths);

		return jc.runAsyncjob(ThreadPath, "//home//sasghar//test/test.out.");



}

void *communicator(void* ptr)
{
	  //  vector<string> LearnetClauses;
	    //  Socket to talk to clients
	    void *context = zmq_ctx_new ();
	    void *responder = zmq_socket (context, ZMQ_REP);
	    zmq_connect  (responder, "tcp://clhead:5560");
	   // assert (rc == 0);
	   bool flag=false;
	   int count=0;
	    while (1) {
	        char* buffer = s_recv (responder);
	      //  printf ("Received request for\n");
	      //  printf ("Received request= %s\n", buffer);

		   // if(string(buffer).find("LCS",0,3)!=string::npos)
		    	if (strcmp (buffer, "LCS") == 0)
		      {
			    // printf ("Received request for Storing Learnt clauses\n");
			     while(writeLock)
				 flag=false;
			     writeLock=false;
			     readLock=true;
			     s_send (responder, "ok");
			    // printf ("Received request for Storing Learnt clauses2\n");
			     continue;

		      }
/*
	  	    if(strcmp(buffer,"LCR")==0)
	  	      {
	               // printf ("Received request for sending Learnt clauses\n");
	                flag=true;
	                count=0;
	                char size[4];
	                sprintf(size,"%d",LearnetClauses.size());

	              	               // cout<<"Total clauses"<<buffer<<"\n";
	                s_send (responder, (char*)size);

	        		Publisher();
		        	//s_send (responder, "ok");

	                continue;
	  	      }*/
	  		//s_send (responder, "ok");

		    	else
	       	      {

	        		//printf ("Received request for Storing Learnt clauses3\n");
	       	        LearnetClauses.push_back(string(buffer));
	        		//printf ("Received request for Storing Learnt clauses4\n");
	       	        readLock=false;
	        		s_send (responder, "ok");
	       	       // printf ("%s\n", buffer);
	       	      }

	     delete buffer;
	     buffer=NULL;

	    }
	    return 0;
}

void *Broker(void* ptr)
{
	//  Prepare our context and sockets
	    void *context = zmq_ctx_new ();
	    void *frontend = zmq_socket (context, ZMQ_ROUTER);
	    void *backend  = zmq_socket (context, ZMQ_DEALER);
	    zmq_bind (frontend, "tcp://*:5559");
	    zmq_bind (backend,  "tcp://*:5560");

	    //  Initialize poll set
	    zmq_pollitem_t items [] = {
	        { frontend, 0, ZMQ_POLLIN, 0 },
	        { backend,  0, ZMQ_POLLIN, 0 }
	    };
	    //  Switch messages between sockets
	    while (1) {
	        zmq_msg_t message;
	        zmq_poll (items, 2, -1);
	        if (items [0].revents & ZMQ_POLLIN) {
	            while (1) {
	                //  Process all parts of the message
	                zmq_msg_init (&message);
	                zmq_msg_recv (&message, frontend, 0);
	                int more = zmq_msg_more (&message);
	                zmq_msg_send (&message, backend, more? ZMQ_SNDMORE: 0);
	                zmq_msg_close (&message);
	                if (!more)
	                    break;      //  Last message part
	            }
	        }
	        if (items [1].revents & ZMQ_POLLIN) {
	            while (1) {
	                //  Process all parts of the message
	                zmq_msg_init (&message);
	                zmq_msg_recv (&message, backend, 0);
	                int more = zmq_msg_more (&message);
	                zmq_msg_send (&message, frontend, more? ZMQ_SNDMORE: 0);
	                zmq_msg_close (&message);
	                if (!more)
	                    break;      //  Last message part
	            }
	        }
	    }
	    //  We never get here, but clean up anyhow
	    zmq_close (frontend);
	    zmq_close (backend);
	    zmq_ctx_destroy (context);
	    return 0;
}

void *Publisher(void* ptr)
{
	void *context = zmq_ctx_new ();
	bool firstPhase=true;

		    //  Socket to talk to clients
		    void *publisher = zmq_socket (context, ZMQ_PUB);

		    int sndhwm = 1100000;
		    zmq_setsockopt (publisher, ZMQ_SNDHWM, &sndhwm, sizeof (int));

		    zmq_bind (publisher, "tcp://*:5561");

		    //  Socket to receive signals
		    void *syncservice = zmq_socket (context, ZMQ_REP);
		    zmq_bind (syncservice, "tcp://*:5562");
		    while(1){
					//  Get synchronization from subscribers
					//printf ("Waiting for subscribers\n");
					int subscribers = 0;
					while (subscribers < SUBSCRIBERS_EXPECTED) {
						//  - wait for synchronization request
						char *string = s_recv (syncservice);
						free (string);
						//  - send synchronization reply
						s_send (syncservice, "");
						subscribers++;
					}
					//  Now broadcast exactly 1M updates followed by END
					//printf ("Broadcasting messages\n");

					if(firstPhase)
					{
				vector<string> LearnetClausesLocal=getLearnt();
						for (int i=0; i<LearnetClausesLocal.size();i++)
						{
						//std::cout<<LearnetClausesLocal[i]<<"\n";
							LearnetClauses.push_back(LearnetClausesLocal[i]);

						}
						firstPhase=false;
					}


		//		printf ("Broadcasting messages %d \n",LearnetClauses.size() );

							for (int count = 0; count < LearnetClauses.size(); count++)
							{
								string clause=LearnetClauses[count]+"\0";
			//					printf ("Broadcasting the clause %S \n",clause.c_str());
								s_send(publisher,(char *)clause.c_str());
							}
								//s_send (publisher, "Rhubarb");

				s_send (publisher, "END");
			//	printf ("Broadcasting of %d messages finshed \n",LearnetClauses.size());
				writeLock=false;
		}
		zmq_close (publisher);
	    zmq_close (syncservice);
	    zmq_ctx_destroy (context);
        return 0;



}

void *TimeoutEx(void* ptr)
{
	sleep(timeoutVal);
	cout<<"TimeOut\n"<< "Time taken: "<< (double)(clock() - jc.StartTime)/CLOCKS_PER_SEC<<endl;
	jc.cleanUp();
    exit(-1);

}




