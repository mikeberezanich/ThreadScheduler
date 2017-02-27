//myschedule.cpp
/*Define all the functions in 'myschedule.h' here.*/
#include "myscheduler.h"

void MyScheduler::CreateThread(int arriving_time, int remaining_time, int priority, int tid) //Thread ID not Process ID
{
	//Created a new instance of the structure
	//Added each of the attributes
	//Packaged each of them into an element of the vector

	struct ThreadDescriptorBlock tdb;

	tdb.tid = tid;
	tdb.remaining_time = remaining_time;
	tdb.arriving_time = arriving_time;
	tdb.priority = priority;

	threadVector.push_back(tdb);

}

/****************************************************
FCFS_policy: FIRST COME FIRST SERVE
Input: int CPU[] ----- array of all CPU's
int size  ---- size of array
Sorts the CPU processes by their arrival time.
Then schedules them by their position in the array.
****************************************************/
void FCFS_policy(int threadVector[], int size){

	//insertion sort the arrays based on arrival time
	//for all the elements in the threadVector
	for (int i = 0; i<=threadVector::size(); i++){
		//Make i represent the arrival_time at element i in the vector
		int j = i - 1;
		int temp = threadVector.tdb.arriving_time[i];
		while(j >= 0 && temp < threadVector.tdb.arriving_time[j]){
			threadVector.tdb.arriving_time[j + 1] = threadVector.tdb.arriving_time[j];
			j--;
		}
		threadVector.tdb.arriving_time[j+1] = temp;

		//at this point the vector should be sorted by arriving_time
	}

	//return the threadvector? how do we get it back to the dispatch
	//are we returning a single thread or all the threads?

}

/****************************************************
STRFwoP_policy: SHORTEST TIME REMAINING WITHOUT PREEMPTION
Input: int CPU[] ----- array of all CPU's
int size  ---- size of array
Sorts the CPU processes by their (remaining time-arrival time).
Then schedules them by their position in the array.
****************************************************/
void STRFwoP_policy(int CPU[], int size){

}

/****************************************************
STRFwP_policy: SHORTEST TIME REMAINING WITH PREEMPTION
Input: int CPU[] ----- array of all CPU's
int size  ---- size of array
****************************************************/
void STRFwP_policy(int CPU[], int size){

}

/****************************************************
PBS_policy: PRIORITY BASED SCHEDULING
Input: int CPU[] ----- array of all CPU's
int size  ---- size of array
Sorts the CPU processes by their priority.
Then schedules them by their position in the array.
****************************************************/
void PBS_policy(int CPU[], int size){

}

bool MyScheduler::Dispatch()
{
	//Todo: Check and remove finished threads
	//Todo: Check if all the threads are finished; if so, return false
	switch(policy)
	{
		case FCFS:		//First Come First Serve
			//FCFS_policy();
			break;
		case STRFwoP:	//Shortest Time Remaining First, without preemption
			//STRFwoP_policy;
			break;
		case STRFwP:	//Shortest Time Remaining First, with preemption
			//STRFwP_policy;
			break;
		case PBS:		//Priority Based Scheduling, with preemption
			//PBS_policy;
			break;
		default :
			cout<<"Invalid policy!";
			throw 0;
	}
	return true;
}
