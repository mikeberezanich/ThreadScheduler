/************************************************************************************
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

************************************************************************************/
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


/*************************************************************************************
Sorts the threads vector by ascneding arrival time using insertion sort

Used by FCFS_policy: FIRST COME FIRST SERVE
*************************************************************************************/
void MyScheduler::SortbyAT(){ 

	for (int i = 0; i < threadVector.size(); i++) { 
		int j = i - 1;
		ThreadDescriptorBlock *temp = threadVector.at(i);
		while(j >= 0 && temp->arriving_time < threadVector.at(j)->arriving_time) {
			threadVector.at(j + 1) = threadVector.at(j);
			j--;
		}
		threadVector.at(j + 1) = temp; 
	}

}


/*************************************************************************************
Sorts the threads vector by ascending remaining time using insertion sort

Used by STRFwoP_policy: SHORTEST TIME REMAINING W/O PREEMPTION
Used by STRFwP_policy: SHORTEST TIME REMAINING WITH PREEMPTION
*************************************************************************************/
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


/*************************************************************************************
Sorts the threads vector by descending priority using insertion sort

If two threads have the same priority, the one with the earlier arrival time will be 
put ahead of the one with the later arrival time

Used by PBS_policy: PRIORITY BASED SCHEDULING
*************************************************************************************/
void MyScheduler::SortByP() {

	for (int i = 0; i < threadVector.size(); i++) {
		int j = i - 1;
		ThreadDescriptorBlock *temp = threadVector.at(i);

		//Moves threads with higher priority to their correct position
		//If two have same priority, the thread with earlier arrival time is moved forward
		while (j >= 0 && (temp->priority < threadVector.at(j)->priority || (temp->priority == threadVector.at(j)->priority && temp->arriving_time < threadVector.at(j)->arriving_time))) {
			threadVector.at(j + 1) = threadVector.at(j);
			j--;
		}
		threadVector.at(j + 1) = temp;
	}

}


/*************************************************************************************
Used to find the next available thread to be scheduled in the thread vector 

Returns position of next available thread in the thread vector -or-
Returns a -1 if all threads are already assigned to a CPU
*************************************************************************************/
int MyScheduler::FindNextThread() {

	for (int i = 0; i < threadVector.size(); i++) {
		bool alreadyScheduled = false;
		
		//go through all our cpu's and check if any of them are already executing the current thread we're on
		for (int j = 0; j < num_cpu && !alreadyScheduled; j++) {
			if (CPUs[j] == threadVector.at(i)) {
				alreadyScheduled = true;
			}
		}

		//if the thread is not already scheduled to a cpu and has arrived, return the thread
		if (!alreadyScheduled && timer >= threadVector.at(i)->arriving_time) {
			return i;
		}
	}

	//if no threads are currently ready to be scheduled, return -1 to tell caller function that
	return -1;
}


/*************************************************************************************
Assigns a thread found by FindNextThread() call 

Usually the argument will be a pointer to one of our cpu's, but it is also sometimes
called with a temp pointer to check if any threads are currently available

Returns true if it is able to assign a thread to tcpu -or-
Returns false if no threads can be scheduled to tcpu right now
*************************************************************************************/
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
			threadVector.erase(threadVector.begin() + i);
			i--;
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

	//check if any cpu's need scheduled
	bool cpusAvailable = false;
	for (int i = 0; i < num_cpu; i++) {
		if (CPUs[i] == NULL)
			cpusAvailable = true;
	}

	//Assign each cpu to the beginning elements of our now sorted thread vector
	//This assumes that the vector has been sorted by scheduling policy
	//If FindNextThread() call returns with error, no threads can be scheduled yet so we escape
	bool threadsAvailable = true;
	for (int i = 0; i < num_cpu && threadsAvailable; i++) {

		//For non preemptive policies, wait until the next cpu is null
		if (policy == FCFS || policy == STRFwoP) {
			if (CPUs[i] == NULL) {
				threadsAvailable = AssignThreadToCpu(CPUs[i]);
			}
		}
		//For policies with preemption, we first check if any new threads are ready to be scheduled
		//If so, assign the new thread to either the first empty cpu (if there are any empty) -or-
		//Assign it to the first cpu it finds with a lower remaining time / priority
		else if (policy == STRFwP) {
			ThreadDescriptorBlock *temp;
			threadsAvailable = AssignThreadToCpu(temp);

			if (threadsAvailable) {
				if (CPUs[i] == NULL) {
					threadsAvailable = AssignThreadToCpu(CPUs[i]);
				}
				else {
					if (temp->remaining_time < CPUs[i]->remaining_time && !cpusAvailable) {
						threadsAvailable = AssignThreadToCpu(CPUs[i]);
					}
				}				
			}
		}
		else if (policy == PBS) {
			ThreadDescriptorBlock *temp;
			threadsAvailable = AssignThreadToCpu(temp);

			if (threadsAvailable) {
				if (CPUs[i] == NULL) {
					threadsAvailable = AssignThreadToCpu(CPUs[i]);
				}
				else {
					if ((temp->priority < CPUs[i]->priority || (temp->priority == CPUs[i]->priority && temp->arriving_time < CPUs[i]->arriving_time))  && !cpusAvailable) {
						threadsAvailable = AssignThreadToCpu(CPUs[i]);
					}
				}
			}
		}

	}

	return true;
}
