#include <bits/stdc++.h>

using namespace std;

// seed for random number generation
long int seed = 56329;

// Function to generate uniformly distributed random
double generateRandomNumber(std::mt19937& generator)
{
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

// Function to generate exponentially distributed random
double generateExponential(float mean, std::mt19937& generator)
{
    std::exponential_distribution<double> distribution(1.0 / mean);
    return distribution(generator);
}

// Function to generate parameters
void generateParameters(int ave_interarrival_time,
                        int last_arival_time,
                        int max_CPU_size,
                        int min_CPU_size,
                        int* priority,
                        long* arrival_time,
                        int* CPU_burst_size,
                        std::mt19937& generator)
{// function parameters
    *priority = 1 + int(10 * generateRandomNumber(generator));
    *arrival_time = static_cast<long>(last_arival_time + generateExponential(static_cast<float>(ave_interarrival_time), generator) + 0.5);
    *CPU_burst_size = min_CPU_size + int((max_CPU_size - min_CPU_size) * generateRandomNumber(generator));
}

int main()
{
    // initializing variables
    int max_CPU_burst = 20;  // reasonable value
    int min_CPU_burst = 5;   // reasonable value
    int this_CPU_burst_length;
    int this_priority;
    int ave_interarr_time = 10;  // reasonable value
    int last_arrival_time = 0;
    long this_arrival_time;

    ofstream myfile;
    myfile.open("datagen.txt");

    // outputs header to the file
    std::mt19937 generator(seed);

    for (int i = 1; i <= 1000; i++)
    {
        generateParameters(ave_interarr_time, last_arrival_time, max_CPU_burst,
                           min_CPU_burst, &this_priority, &this_arrival_time,
                           &this_CPU_burst_length, generator);

        myfile << setw(4) << i << setw(12) << this_arrival_time << setw(20) << this_CPU_burst_length;
        myfile << setw(6) << this_priority << endl;

        last_arrival_time = this_arrival_time;
    }

    cout << endl;
    cout << "Data have been Generated!" << endl;

    myfile.close();

    return 0;
}
