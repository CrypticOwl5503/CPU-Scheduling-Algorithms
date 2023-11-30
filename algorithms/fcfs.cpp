#include <bits/stdc++.h>
using namespace std;

// Total number of processes
const int stacks = 1000;

// Function to calculate CPU utilization and idle time
void calculateCPUUtilization(double& CPUUTL, double& CPUIDL, double tst, double tstp) {
    CPUUTL = (tstp / tst) * 100;
    CPUIDL = 100 - CPUUTL;
}

// Function to process FCFS scheduling
void processFCFS(ifstream& myfile, ofstream& schedFile) {
    auto begin = chrono::high_resolution_clock::now(); //To calculate the time taken by the algorithm
    int process[stacks];
    int arrival[stacks];
    int burst[stacks];
    int priority[stacks];
    int service_time[stacks];
    int wt[stacks];
    int total_wt = 0;
    int total_tat = 0;
    double tst = 0;
    double tstp = 0;

    // Outputs header to the file
    schedFile << "Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\n";

    // Process each task for FCFS
    for (int i = 1; i <= stacks; i++) {
        service_time[0] = 0;
        wt[0] = 0;

        // Getting values from the file
        myfile >> process[i] >> arrival[i] >> burst[i] >> priority[i];

        // Calculate completion time
        service_time[i] = service_time[i - 1] + burst[i];

        if (service_time[i] < 0)
            service_time[i] = 0;

        // Calculate waiting time
        wt[i] = service_time[i] - arrival[i];

        // If waiting time is negative, change it to zero
        if (wt[i] < 0)
            wt[i] = 0;

        int tat = burst[i] + wt[i];

        // Calculate turnaround time
        total_wt += wt[i];
        total_tat += tat;

        tst += service_time[i];
        tstp += i;

        // Output results to the file
        schedFile << i << "\t\t" << arrival[i] << "\t\t" << burst[i] << "\t\t" << priority[i] << "\t\t"
                  << service_time[i] << "\t\t\t" << wt[i] << "\t\t" << tat << endl;
    }

    // Calculate CPU utilization and idle time
    double CPUUTL, CPUIDL;
    calculateCPUUtilization(CPUUTL, CPUIDL, tst, tstp);

    // Calculate elapsed time
    auto end = chrono::high_resolution_clock::now();
    auto dur = end - begin;
    auto ms = chrono::duration_cast<chrono::milliseconds>(dur).count();

    schedFile << "\nTotal Elapsed time: " << ms << " ms\n";
    // Output results to the file
    schedFile << "\n_________________________________________________________\n";
    schedFile << "\nStatistics for the RUN\n";
    schedFile << "\nNumber of processes: " << stacks;
    schedFile << "\nThroughput = " << (double)stacks / tst << endl;
    schedFile << "CPU utilization =  Usage: " << CPUUTL << "% Idle: " << CPUIDL << "%\n";
    schedFile << "Average Waiting Time = " << (double)total_wt / stacks << " ms\n";
    schedFile << "Average Turnaround Time = " << (double)total_tat / stacks << " ms\n";
    schedFile << "Average response time = " << (tst - service_time[stacks]) / stacks << "ms\n";
    schedFile << "_________________________________________________________\n";
}

int main() {
    

    // Open the files
    ifstream myfile("../datagen/datagen.txt");
    ofstream schedFile("../outputs/FCFS_output.txt");

    if (!myfile.is_open() || !schedFile.is_open()) {
        cout << "Error opening files." << endl;
        return 1;
    }

    cout << "Processing... Please Wait..." << endl;

    processFCFS(myfile, schedFile);

    
    schedFile.close();

    cout << "\nThe FCFS Scheduling Has Been Successfully Processed!" << endl
         << "\nPlease Look at the Output in the File Named FCFS_output.txt" << endl;

    myfile.close();

    return 0;
}
