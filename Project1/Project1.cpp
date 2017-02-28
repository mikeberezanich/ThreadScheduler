// Project1.cpp : Defines the entry point for the console application.
//

#include "myscheduler.h"

int main(int argc, char* argv[])
{
		cout << "Testbench via Kenneth Au\n\n";
	
		cout << "\tOutput for 1 CPU FCFS\n";
		MyScheduler ms1 = MyScheduler(Policy::FCFS, 1);
		ms1.CreateThread(1, 24, 0, 9000);
		ms1.CreateThread(2, 3, 0, 9001);
		ms1.CreateThread(3, 4, 0, 9002);
		ms1.Go();
		/* Results should be:
		Thread ID : 9000 Finishing Time : 25 CPU No. : 0
		Thread ID : 9001 Finishing Time : 28 CPU No. : 0
		Thread ID : 9002 Finishing Time : 32 CPU No. : 0  */
	
		
		
	
		cout << "\tOutput for 2 CPU FCFS\n";
		MyScheduler ms2 = MyScheduler(Policy::FCFS, 2);
		ms2.CreateThread(1, 24, 0, 9000);
		ms2.CreateThread(2, 3, 0, 9001);
		ms2.CreateThread(3, 4, 0, 9002);
		ms2.Go();
		/* Results should be:
		Thread ID : 9001 Finishing Time :  5 CPU No. : 1
		Thread ID : 9002 Finishing Time :  9 CPU No. : 1
		Thread ID : 9000 Finishing Time : 25 CPU No. : 0  */

		cout << "\tOutput for 1 CPU STRFwoP\n";
		MyScheduler ms7 = MyScheduler(Policy::STRFwoP, 1);
		ms7.CreateThread(1, 24, 0, 9000);
		ms7.CreateThread(2, 3, 0, 9001);
		ms7.CreateThread(3, 4, 0, 9002);
		ms7.Go();
	
	
		cout << "\tOutput for 3 CPU FCFS\n";
		MyScheduler ms3 = MyScheduler(Policy::FCFS, 3);
		ms3.CreateThread(1, 24, 0, 9000);
		ms3.CreateThread(2, 3, 0, 9001);
		ms3.CreateThread(3, 4, 0, 9002);
		ms3.Go();
		/* Results should be:
		Thread ID : 9001 Finishing Time :  5 CPU No. : 1
		Thread ID : 9002 Finishing Time :  7 CPU No. : 2
		Thread ID : 9000 Finishing Time : 25 CPU No. : 0  */

		/*MyScheduler ms = MyScheduler(Policy::FCFS, 1);
		ms.CreateThread(0, 1, 0, 00);
		ms.CreateThread(0, 2, 0, 01);
		ms.CreateThread(0, 4, 0, 02);
		ms.CreateThread(0, 8, 0, 03);
		ms.CreateThread(0, 16, 0, 04);
		ms.CreateThread(0, 32, 0, 05);
		ms.CreateThread(0, 64, 0, 06);
		ms.CreateThread(0, 128, 0, 07);
		ms.Go();*/



	return 0;
}

