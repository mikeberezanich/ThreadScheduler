//myschedule.cpp
/*Define all the functions in 'myschedule.h' here.*/
#include "myscheduler.h"

void MyScheduler::CreateThread(int arriving_time, int remaining_time, int priority, int tid) //Thread ID not Process ID
{
	cout << "hi" << endl;
	//Function to Create Thread(s) and insert them in the student
	//defined data structure
}

/****************************************************
FCFS_policy: FIRST COME FIRST SERVE
Input: int CPU[] ----- array of all CPU's
int size  ---- size of array
Sorts the CPU processes by their arrival time.
Then schedules them by their position in the array.
****************************************************/
void MyScheduler::FCFS_policy(int CPU[], int size){
	//sort the arrays based on arrival time



}

/****************************************************
STRFwoP_policy: SHORTEST TIME REMAINING WITHOUT PREEMPTION
Input: int CPU[] ----- array of all CPU's
int size  ---- size of array
Sorts the CPU processes by their (remaining time-arrival time).
Then schedules them by their position in the array.
****************************************************/
void MyScheduler::STRFwoP_policy(int CPU[], int size){

}

/****************************************************
STRFwP_policy: SHORTEST TIME REMAINING WITH PREEMPTION
Input: int CPU[] ----- array of all CPU's
int size  ---- size of array
****************************************************/
void MyScheduler::STRFwP_policy(int CPU[], int size){

}

/****************************************************
PBS_policy: PRIORITY BASED SCHEDULING
Input: int CPU[] ----- array of all CPU's
int size  ---- size of array
Sorts the CPU processes by their priority.
Then schedules them by their position in the array.
****************************************************/
void MyScheduler::PBS_policy(int CPU[], int size){

}

bool MyScheduler::Dispatch()
{
	//Todo: Check and remove finished threads
	//Todo: Check if all the threads are finished; if so, return false
	switch(policy)
	{
		case FCFS:		//First Come First Serve
			FCFS_policy;
			break;
		case STRFwoP:	//Shortest Time Remaining First, without preemption
			STRFwoP_policy;
			break;
		case STRFwP:	//Shortest Time Remaining First, with preemption
			STRFwP_policy;
			break;
		case PBS:		//Priority Based Scheduling, with preemption
			PBS_policy;
			break;
		default :
			cout<<"Invalid policy!";
			throw 0;
	}
	return true;
}