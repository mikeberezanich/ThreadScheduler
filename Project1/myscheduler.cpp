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
	struct ThreadDescriptorBlock *tdb = new ThreadDescriptorBlock;

	//Add each of the attributes
	tdb->tid = tid;
	tdb->remaining_time = remaining_time;
	tdb->arriving_time = arriving_time;
	tdb->priority = priority;

	//Packaged each of them into an element of the vector
	threadVector.push_back(tdb);

}

/****************************************************
Sorts the CPU processes by their arrival time.

Used by FCFS_policy: FIRST COME FIRST SERVE
****************************************************/
void MyScheduler::SortbyAT(){ 

	//insertion sort the arrays based on arrival time
	//for all the elements in the threadVector
	for (int i = 0; i < threadVector.size(); i++) { 
		int j = i - 1;
		ThreadDescriptorBlock *temp = threadVector.at(i);
		while(j >= 0 && temp->arriving_time < threadVector.at(j)->arriving_time) {
			threadVector.at(j + 1) = threadVector.at(j);
			j--;
		}
		threadVector.at(j + 1) = temp; 
	}

	//at this point the vector should be sorted by arriving_time


}

/****************************************************
Sorts the CPU processes by their remaining time.

Used by STRFwoP_policy: SHORTEST TIME REMAINING W/O PREEMPTION
Used by STRFwP_policy: SHORTEST TIME REMAINING WITH PREEMPTION
****************************************************/
void MyScheduler::SortByRT() {

	for (int i = 0; i < threadVector.size(); i++) { 
		int j = i - 1;
		ThreadDescriptorBlock *temp = threadVector.at(i);
		while(j >= 0 && temp->remaining_time < threadVector.at(j)->remaining_time) {
			threadVector.at(j + 1) = threadVector.at(j);
			j--;
		}
		threadVector.at(j + 1) = temp; 
	}

}

/****************************************************
Sorts the CPU processes by their priority.

Used by PBS_policy: PRIORITY BASED SCHEDULING
****************************************************/
void MyScheduler::SortByP() {

	for (int i = 0; i < threadVector.size(); i++) {
		int j = i - 1;
		ThreadDescriptorBlock *temp = threadVector.at(i);
		while (j >= 0 && temp->priority <= threadVector.at(j)->priority) {
			if (temp->priority == threadVector.at(j)->priority) {
				if (temp->arriving_time < threadVector.at(j)->arriving_time) {
					threadVector.at(j + 1) = threadVector.at(j);
				} //might need an else here to break out of loop?
			}
			else {
				threadVector.at(j + 1) = threadVector.at(j);
			}
			j--;
		}
		threadVector.at(j + 1) = temp;
	}

}

//Returns position of next available thread in threadVector 
//or a -1 if all threads are already assigned to a CPU
int MyScheduler::FindNextThread() {
	for (int i = 0; i < threadVector.size(); i++) {
		bool alreadyScheduled = false;
		
		for (int j = 0; j < num_cpu && !alreadyScheduled; j++) {
			if (CPUs[j] == threadVector.at(i)) {
				alreadyScheduled = true;
				
				/*cout << "Comparing thread: " << threadVector.at(i)->tid << " with CPU " << j << " which is executing "
				<< CPUs[j]->tid << endl;*/
			}

			
			/*cout << "Is thread: " << threadVector.at(i)->tid << " already scheduled to a CPU: " << alreadyScheduled << endl;*/
		}

		if (!alreadyScheduled && timer >= threadVector.at(i)->arriving_time) {
			/*cout << "Assigning thread: " << threadVector.at(i)->tid << " to a CPU" << endl;*/
			return i;
		}
	}

	return -1;
}

bool MyScheduler::AssignThreadToCpu(ThreadDescriptorBlock *&tcpu) {
	int pos = FindNextThread();

	//if FindNextThread finds a thread that needs assigned
	if (pos != -1)
		tcpu = threadVector.at(pos);
	else
		return false;

	return true;
}



bool MyScheduler::Dispatch() {

	//Remove completed threads from threadVector
	for (int i = 0; i < threadVector.size(); i++) {
		if (threadVector.at(i)->remaining_time < 1) {
			//delete threadVector.at(i); or &threadVector.at(i); ? Do we need one of these or will erase do this
			threadVector.erase(threadVector.begin() + i);
		}
	}

	//If no threads left, we are finished
	if (threadVector.size() < 1)
		return false;

	switch (policy)
	{
	case FCFS:		//First Come First Serve
		SortbyAT();
		break;
	case PBS:		//Priority Based Scheduling, with preemption
		SortByP();
		break;
	case STRFwoP:	//Shortest Time Remaining First, without preemption
	case STRFwP:	//Shortest Time Remaining First, with preemption
		SortByRT(); //Both use SortByRT()
		break;
	default:
		cout << "Invalid policy!";
		throw 0;
	}

	bool threadsAvailable = true;
	//Assign each cpu to the beginning elements of our now sorted thread vector
	//This assumes that the vector has been sorted by scheduling policy
	//If FindNextThread() call returns with error, no threads can be scheduled yet so we escape
	for (int i = 0; i < num_cpu && threadsAvailable; i++) {

		//For non preemptive policies, wait until the next cpu is null
		if (policy == FCFS || policy == STRFwoP) {
			if (CPUs[i] == NULL) {
				threadsAvailable = AssignThreadToCpu(CPUs[i]);
			}
		}
		else if (policy == STRFwP) {
			ThreadDescriptorBlock *temp;
			threadsAvailable = AssignThreadToCpu(temp);

			if (threadsAvailable) {
				if (CPUs[i] != NULL) {
					if (temp->remaining_time < CPUs[i]->remaining_time) {
						threadsAvailable = AssignThreadToCpu(CPUs[i]);
					}
				}
				else {
					threadsAvailable = AssignThreadToCpu(CPUs[i]);
				}				
			}
		}
		else if (policy == PBS) {
			ThreadDescriptorBlock *temp;
			threadsAvailable = AssignThreadToCpu(temp);

			if (threadsAvailable) {
				if (CPUs[i] != NULL) {
					if (temp->priority <= CPUs[i]->priority) {
						threadsAvailable = AssignThreadToCpu(CPUs[i]);
					}
				}
				else {
					threadsAvailable = AssignThreadToCpu(CPUs[i]);
				}
			}
		}

	}
	

	//Printing for debugging purposes
	/*for (int i = 0; i < threadVector.size(); i++) {
		if (i < num_cpu)
			cout << "CPU " << i << " executing thread " << CPUs[i]->tid << endl;

		cout << "Thread " << threadVector.at(i)->tid << " - Rtime: " << threadVector.at(i)->remaining_time << endl;
		system("pause");
	}*/

	return true;
}
