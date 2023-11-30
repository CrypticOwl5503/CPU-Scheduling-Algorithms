#include <bits/stdc++.h>
using namespace std;
// Global variables

long int seed = 56329; 

// Function to generate uniformly distributed random
//   numbers between 0 and 1.

double random( long int* seed )
{  // function random
	long int  a = 16807,        // 7^5
	          m = 2147483647,   // 2^31 - 1
		  q = 127773,           // m / a (int divide)
		  r = 2836,		        // m % a
		  lo, hi, test;
	double dm = 2147483647;

	hi = *seed / q;
	lo = *seed % q;
	test = a * lo - r * hi;
	*seed = test > 0 ? test : test + m;
	return (double)(*seed/dm);
}  // function random

double exponential(float mean)
{ // function exponential
       return (double)(-mean*log (random(&seed)));
} // function exponential


void parameters(int   ave_interarrival_time, //between process arrivals
                    int   last_arival_time, //last process arrival time
                    int max_CPU_size,   //Maximum CPU Burst Size
                    int min_CPU_size,   // Minimum CPU Burst Size
                    int* priority,          //Priority
                    long*  arrival_time, //Time of arrival
                    int* CPU_burst_size) //CPU Burst Size


{ // function parameters
  *priority = 1 + int(10*random(&seed)); //generates priority between 1 and 10
  *arrival_time = (long) (last_arival_time + exponential((float) (ave_interarrival_time)) + 0.5);
  *CPU_burst_size = min_CPU_size + int((max_CPU_size-min_CPU_size)*random(&seed)); // generates CPU Burst size
} // function parameters


int main()

{
    int   hist[10];
    int   index;
    int   i;

    int   max_CPU_burst, min_CPU_burst;
    int   this_CPU_burst_length;
    int   this_priority;
    int   ave_interarr_time;
    int last_arrival_time = 0;
    long this_arrival_time;
    int temp;

    ofstream myfile;
    myfile.open ("../outputs/datagenRR.txt");

    max_CPU_burst = 20;  // reasonable value
    min_CPU_burst = 5; 
    ave_interarr_time = 10;

// Assuming that there are 10000 processes
    for ( i = 1; i <= 15; i++ ) {

    // Generate parameters for the next process
      parameters(ave_interarr_time, last_arrival_time, max_CPU_burst,
                 min_CPU_burst, &this_priority, &this_arrival_time,
                 &this_CPU_burst_length);

      myfile << setw( 4 ) << i << setw(12)  << this_arrival_time << setw( 20) << this_CPU_burst_length;
      myfile << setw(6) << this_priority << endl;


      last_arrival_time = this_arrival_time;
    }

    cout << endl;
    cout << "Data for Round Robin Scheduling have been Generated!" << endl;

    myfile.close();

  return 0;
} // function main