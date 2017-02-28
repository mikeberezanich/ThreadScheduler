/********************************************************************
File: myscheduler.cpp
Authors: Mike Berezanich
		 Aishwarya Patankar
		 Ryan Gleason

Date: 3/1/2017

Purpose: schedule incoming threads using the following policies
		1. First Come First First Served (FCFS)
		2. Shortest Remaining Time First with out preemption(SRTF)
		3. SRTF, with preemption
		4. Priority Based Scheduling (PBS), with preemption

*********************************************************************/
//myschedule.cpp
/*Define all the functions in 'myschedule.h' here.*/
#include "myscheduler.h"

void MyScheduler::CreateThread(int arriving_time, int remaining_time, int priority, int tid) {
		
	//Created a new instance of the structure
	struct ThreadDescriptorBlock tdb;

	//Add each of the attributes
	tdb.tid = tid;
	tdb.remaining_time = remaining_time;
	tdb.arriving_time = arriving_time;
	tdb.priority = priority;

	//Packaged each of them into an element of the vector
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
	for (int i = 0; i < threadVector.size(); i++) { 
		int j = i - 1;
		ThreadDescriptorBlock temp = threadVector.at(i);
		while(j >= 0 && temp.remaining_time < threadVector.at(j).remaining_time) {
			threadVector.at(j + 1) = threadVector.at(j);
			j--;
		}
		threadVector.at(j + 1) = temp; 
	}
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

//Returns position of next available thread in threadVector 
//or a -1 if all threads are already assigned to a CPU
int MyScheduler::FindNextThread() {
	for (int i = 0; i < threadVector.size(); i++) {
		bool alreadyScheduled = false;
		
		for (int j = 0; j < num_cpu && !alreadyScheduled; j++) {
			if (CPUs[j] == &threadVector.at(i)) {
				alreadyScheduled = true;
				
				cout << "Comparing thread: " << threadVector.at(i).tid << " with CPU " << j << " which is executing "
				<< CPUs[j]->tid << endl;
			}

			
			cout << "Is thread already scheduled to a CPU: " << alreadyScheduled << endl;
		}

		if (!alreadyScheduled) {
			cout << "Assigning thread: " << threadVector.at(i).tid << " to a CPU" << endl;
			return i;
		}
	}

	return -1;
}

bool MyScheduler::Dispatch() {

	//Remove completed threads from threadVector
	for (int i = 0; i < threadVector.size(); i++) {
		if (threadVector.at(i).remaining_time < 1) {
			threadVector.erase(threadVector.begin() + i);
		}
	}

	//If no threads left, we are finished
	if (threadVector.size() < 1)
		return false;

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
		
		if (CPUs[i] == NULL) {
			int pos = FindNextThread();

			//if FindNextThread finds a thread that needs assigned
			if (pos != -1) {

				//so if this thread is being assigned before it's arrival time, we add the difference in time to 
				//its remaining time
				if (timer < threadVector.at(pos).arriving_time) {
					threadVector.at(pos).remaining_time += (threadVector.at(pos).arriving_time - timer);
				}

				CPUs[i] = &threadVector.at(pos);
			}
		}
	}
		

	//Printing for debugging purposes
	/*for (int i = 0; i < threadVector.size(); i++) {
		if (i < num_cpu)
			cout << "CPU " << i << " executing thread " << CPUs[i]->tid << endl;

		cout << "Thread " << threadVector.at(i).tid << " - Rtime: " << threadVector.at(i).remaining_time << endl;
		system("pause");
	}*/

	return true;
}
