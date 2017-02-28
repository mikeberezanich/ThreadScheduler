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
	std::vector<ThreadDescriptorBlock *> threadVector;
	bool firstPass;
	
	MyScheduler(Policy p, unsigned int n) : Scheduler(p, n) {
		firstPass = true;
	}

	bool Dispatch() override; //Function to implement scheduling policy and to keep a check on processed threads
	void CreateThread(int arriving_time, int remaining_time, int priority, int tid) override; //Function to create threads and insert them in student defined data structure
	
	int MyScheduler::FindNextThread();

	void FCFS_policy();
	void STRFwoP_policy();
	void STRFwP_policy();
	void PBS_policy();


};
