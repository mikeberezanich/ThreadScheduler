/********************************************************************
File: myscheduler.h
Authors: Mike Berezanich
		 Aishwarya Patankar
		 Ryan Gleason

Date: 3/1/2017

Purpose: contains the function definitions and the data structure definition

*********************************************************************/

#pragma once
#include <vector>
//myschedule.h
/* Students need to define their own data structure to contain
   and access objects from 'thread class'. The 'CreateThread()'
   function should insert the threads into the student defined
   data structure after creating them.
   They are allowed to add any additional functionality (only
   declaration in this file, define in 'myschedule.cpp')
   which they might find helpful.*/

#include "scheduler.h"


class MyScheduler: public Scheduler {
public:
	//use a standard vector as our data structure for holding threads
	std::vector<ThreadDescriptorBlock *> threadVector;
	
	MyScheduler(Policy p, unsigned int n) : Scheduler(p, n) {}

	bool Dispatch() override; //Function to implement scheduling policy and to keep a check on processed threads
	void CreateThread(int arriving_time, int remaining_time, int priority, int tid) override; //Function to create threads and insert them in student defined data structure
	
	//helper functions
	int FindNextThread();
	bool AssignThreadToCpu(ThreadDescriptorBlock *&tcpu);

	//helper functions used to sort threads based on policy
	void SortbyAT();
	void SortByRT();
	void SortByP();
};
