//myschedule.cpp
/*Define all the functions in 'myschedule.h' here.*/
#include "myscheduler.h"

void MyScheduler::CreateThread(int arriving_time, int remaining_time, int priority, int tid) {
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
Sorts the CPU processes by their arrival time.
Then schedules them by their position in the array.
****************************************************/
void MyScheduler::FCFS_policy(){ 

	//insertion sort the arrays based on arrival time
	//for all the elements in the threadVector
	for (int i = 0; i < threadVector.size(); i++) { 
		int j = i - 1;
		ThreadDescriptorBlock temp = threadVector.at(i);
		while(j >= 0 && temp.arriving_time < threadVector.at(j).arriving_time) {
			threadVector.at(j + 1) = threadVector.at(j);
			j--;
		}
		threadVector.at(j + 1) = temp; 
	}

	//at this point the vector should be sorted by arriving_time
}

/****************************************************
STRFwoP_policy: SHORTEST TIME REMAINING WITHOUT PREEMPTION
Sorts the CPU processes by their (remaining time-arrival time).
Then schedules them by their position in the array.
****************************************************/
void MyScheduler::STRFwoP_policy() {

}

/****************************************************
STRFwP_policy: SHORTEST TIME REMAINING WITH PREEMPTION
****************************************************/
void MyScheduler::STRFwP_policy() {

}

/****************************************************
PBS_policy: PRIORITY BASED SCHEDULING
Sorts the CPU processes by their priority.
Then schedules them by their position in the array.
****************************************************/
void MyScheduler::PBS_policy() {

}

bool MyScheduler::Dispatch() {
	//Todo: Check and remove finished threads
	//Todo: Check if all the threads are finished; if so, return false
	switch(policy)
	{
		case FCFS:		//First Come First Serve
			FCFS_policy();
			break;
		case STRFwoP:	//Shortest Time Remaining First, without preemption
			STRFwoP_policy();
			break;
		case STRFwP:	//Shortest Time Remaining First, with preemption
			STRFwP_policy();
			break;
		case PBS:		//Priority Based Scheduling, with preemption
			PBS_policy();
			break;
		default :
			cout<<"Invalid policy!";
			throw 0;
	}

	//Assign each cpu to the beginning elements of our now sorted thread vector
	//This assumes that the vector has been sorted by scheduling policy
	for (int i = 0; i < num_cpu; i++) {
		CPUs[i] = &threadVector.at(i);
	}

	return true;
}
