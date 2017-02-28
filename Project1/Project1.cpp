// Project1.cpp : Defines the entry point for the console application.
//

#include "myscheduler.h"

int main(int argc, char* argv[])
{
		//cout << "Testbench via Kenneth Au\n\n";
	
		//cout << "\tOutput for 1 CPU FCFS\n";
		//MyScheduler ms1 = MyScheduler(Policy::FCFS, 1);
		//ms1.CreateThread(1, 24, 0, 9000);
		//ms1.CreateThread(2, 3, 0, 9001);
		//ms1.CreateThread(3, 4, 0, 9002);
		//ms1.Go();
		///* Results should be:
		//Thread ID : 9000 Finishing Time : 25 CPU No. : 0
		//Thread ID : 9001 Finishing Time : 28 CPU No. : 0
		//Thread ID : 9002 Finishing Time : 32 CPU No. : 0  */
	
		//cout << "\tOutput for 2 CPU FCFS\n";
		//MyScheduler ms2 = MyScheduler(Policy::FCFS, 2);
		//ms2.CreateThread(1, 24, 0, 9000);
		//ms2.CreateThread(2, 3, 0, 9001);
		//ms2.CreateThread(3, 4, 0, 9002);
		//ms2.Go();
		///* Results should be:
		//Thread ID : 9001 Finishing Time :  5 CPU No. : 1
		//Thread ID : 9002 Finishing Time :  9 CPU No. : 1
		//Thread ID : 9000 Finishing Time : 25 CPU No. : 0  */

		//cout << "\tOutput for 1 CPU STRFwoP\n";
		//MyScheduler ms7 = MyScheduler(Policy::STRFwoP, 1);
		//ms7.CreateThread(1, 24, 0, 9000);
		//ms7.CreateThread(2, 4, 0, 9001);
		//ms7.CreateThread(3, 3, 0, 9002);
		//ms7.Go();
	
		/////* Results should be:
		////Thread ID : 9000 Finishing Time : 25 CPU No. : 0
		////Thread ID : 9002 Finishing Time : 28 CPU No. : 0
		////Thread ID : 9001 Finishing Time : 32 CPU No. : 0
	
		//cout << "\tOutput for 3 CPU FCFS\n";
		//MyScheduler ms3 = MyScheduler(Policy::FCFS, 3);
		//ms3.CreateThread(1, 24, 0, 9000);
		//ms3.CreateThread(2, 3, 0, 9001);
		//ms3.CreateThread(3, 4, 0, 9002);
		//ms3.Go();
		///* Results should be:
		//Thread ID : 9001 Finishing Time :  5 CPU No. : 1
		//Thread ID : 9002 Finishing Time :  7 CPU No. : 2
		//Thread ID : 9000 Finishing Time : 25 CPU No. : 0  */

		///*MyScheduler ms = MyScheduler(Policy::FCFS, 1);
		//ms.CreateThread(0, 1, 0, 00);
		//ms.CreateThread(0, 2, 0, 01);
		//ms.CreateThread(0, 4, 0, 02);
		//ms.CreateThread(0, 8, 0, 03);
		//ms.CreateThread(0, 16, 0, 04);
		//ms.CreateThread(0, 32, 0, 05);
		//ms.CreateThread(0, 64, 0, 06);
		//ms.CreateThread(0, 128, 0, 07);
		//ms.Go();*/

	cout << "FCFS Policy, 2 CPUs\n";
	MyScheduler ms1 = MyScheduler(Policy::FCFS, 2);
	ms1.CreateThread(0, 12, 0, 0);
	ms1.CreateThread(5, 2, 2, 1);
	ms1.CreateThread(3, 7, 1, 2);
	ms1.CreateThread(9, 1, 10, 3);
	ms1.CreateThread(1, 4, 3, 4);
	ms1.CreateThread(5, 2, 3, 5);
	ms1.CreateThread(1, 4, 3, 6);

	ms1.Go();

	/* My results, assuming my project works...
	Thread ID : 4 Finishing Time : 5 CPU No. : 1
	Thread ID : 6 Finishing Time : 9 CPU No. : 1
	Thread ID : 0 Finishing Time : 12 CPU No. : 0
	Thread ID : 1 Finishing Time : 14 CPU No. : 0
	Thread ID : 5 Finishing Time : 16 CPU No. : 0
	Thread ID : 2 Finishing Time : 16 CPU No. : 1
	Thread ID : 3 Finishing Time : 17 CPU No. : 0
	*/

	cout << "STRFwoP Policy, 3 CPUs\n";
	MyScheduler ms2 = MyScheduler(Policy::STRFwoP, 3);
	ms2.CreateThread(0, 12, 0, 0);
	ms2.CreateThread(5, 2, 2, 1);
	ms2.CreateThread(3, 7, 1, 2);
	ms2.CreateThread(9, 1, 10, 3);
	ms2.CreateThread(1, 4, 3, 4);
	ms2.CreateThread(5, 2, 3, 5);
	ms2.CreateThread(1, 4, 3, 6);

	ms2.Go();

	/*
	Thread ID : 4 Finishing Time : 5 CPU No. : 1
	Thread ID : 6 Finishing Time : 5 CPU No. : 2
	Thread ID : 1 Finishing Time : 7 CPU No. : 1
	Thread ID : 5 Finishing Time : 7 CPU No. : 2
	Thread ID : 3 Finishing Time : 10 CPU No. : 2
	Thread ID : 0 Finishing Time : 12 CPU No. : 0
	Thread ID : 2 Finishing Time : 14 CPU No. : 1
	All the Threads have been executed !! .. Exiting Scheduler ..
	*/
	cout << "STRFwP Policy, 3 CPUs\n";
	MyScheduler ms3 = MyScheduler(Policy::STRFwP, 3);
	ms3.CreateThread(0, 12, 0, 0);
	ms3.CreateThread(5, 2, 2, 1);
	ms3.CreateThread(3, 7, 1, 2);
	ms3.CreateThread(9, 1, 10, 3);
	ms3.CreateThread(1, 4, 3, 4);
	ms3.CreateThread(5, 2, 3, 5);
	ms3.CreateThread(1, 4, 3, 6);

	ms3.Go();

	/*
	Thread ID : 6 Finishing Time : 5 CPU No. : 0
	Thread ID : 4 Finishing Time : 5 CPU No. : 1
	Thread ID : 5 Finishing Time : 7 CPU No. : 0
	Thread ID : 1 Finishing Time : 7 CPU No. : 1
	Thread ID : 2 Finishing Time : 10 CPU No. : 0
	Thread ID : 3 Finishing Time : 10 CPU No. : 1
	Thread ID : 0 Finishing Time : 16 CPU No. : 0
	All the Threads have been executed !! .. Exiting Scheduler ..
	*/

	cout << "PBS Policy, 3 CPUs\n";
	MyScheduler ms4 = MyScheduler(Policy::PBS, 3);
	ms4.CreateThread(0, 12, 5, 0);
	ms4.CreateThread(5, 2, 2, 1);
	ms4.CreateThread(3, 7, 4, 2);
	ms4.CreateThread(9, 1, 10, 3);
	ms4.CreateThread(1, 4, 3, 4);
	ms4.CreateThread(5, 2, 3, 5);
	ms4.CreateThread(1, 4, 3, 6);

	ms4.Go();

	/*
	Thread ID : 6 Finishing Time : 5 CPU No. : 0
	Thread ID : 4 Finishing Time : 5 CPU No. : 1
	Thread ID : 1 Finishing Time : 7 CPU No. : 0
	Thread ID : 5 Finishing Time : 7 CPU No. : 1
	Thread ID : 2 Finishing Time : 10 CPU No. : 0
	Thread ID : 3 Finishing Time : 10 CPU No. : 2
	Thread ID : 0 Finishing Time : 16 CPU No. : 0
	All the Threads have been executed !! .. Exiting Scheduler ..
	*/

	return 0;
}

