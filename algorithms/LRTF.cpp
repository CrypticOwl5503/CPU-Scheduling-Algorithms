#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

struct Process {
    int pid;  // Process ID
    int bt;   // Burst Time
    int art;  // Arrival Time
    int ct;   // Completion Time
    int wat;  // Waiting Time
    int btt;  // Remaining Burst time (used for calculations)
    int ta;   // Turnaround Time
    int pr;   // Priority (not used in LRTF)
};

bool compareArrival(const Process &a, const Process &b) {
    return a.art < b.art;
}

bool compareRemainingTime(const Process &a, const Process &b) {
    return a.btt < b.btt;
}

void performLRTFScheduling() {
    int stacks = 1000;

    // Object
    vector<Process> process(stacks);

    // File stream, opens the files
    ifstream myfile;
    ofstream schedFile;
    myfile.open("../datagen/datagen.txt");
    schedFile.open("../outputs/LRTF_output.txt");

    // Local variable
    int total_wt = 0;
    int total_tat = 0;

    auto begin = chrono::high_resolution_clock::now();

    cout << "Processing... Please Wait..." << endl;

    // Getting all the values from the input text file
    for (int i = 0; i < stacks; i++) {
        myfile >> process[i].pid;
        myfile >> process[i].art;
        myfile >> process[i].bt;
        process[i].btt = process[i].bt; // It will be used for the algorithm
        myfile >> process[i].pr;
    }

    // Sorting processes based on arrival time
    sort(process.begin(), process.end(), compareArrival);

    int current_time = 0;

    while (!process.empty()) {
        // Select the process with the longest remaining burst time
        auto longest_process = max_element(process.begin(), process.end(), compareRemainingTime);

        // Move the time to the arrival time of the selected process
        current_time = max(current_time, longest_process->art);

        // Update remaining burst time
        longest_process->btt--;

        // If the process completes, update completion time and remove it from the vector
        if (longest_process->btt == 0) {
            longest_process->ct = current_time + 1;
            longest_process->wat = current_time - longest_process->art;
            longest_process->ta = longest_process->wat + longest_process->bt;

            // Update total waiting and turnaround time
            total_wt += longest_process->wat;
            total_tat += longest_process->ta;

            // Output the result into a text file
            schedFile << longest_process->pid << "\t\t" << longest_process->art << "\t\t" << longest_process->bt << "\t\t" << longest_process->pr
                       << "\t\t" << longest_process->ct << "\t\t" << "\t\t" << longest_process->wat << "\t\t" << longest_process->ta;
            schedFile << endl;

            // Remove the selected process from the vector
            process.erase(longest_process);
        }

        // Move time to the next time unit
        current_time++;
    }

    // Calculations for the elapsed time
    auto end = chrono::high_resolution_clock::now();
    auto dur = end - begin;
    auto ms = chrono::duration_cast<chrono::milliseconds>(dur).count();

    // Calculations for CPU UTILIZATION and CPU IDLE
    double CPUUTL = 0;
    double CPUIDL = 0;
    CPUUTL = (static_cast<double>(current_time) / current_time) * 100;
    CPUIDL = 100 - CPUUTL;

    schedFile << "\n_________________________________________________________" << endl;
    schedFile << "\n             Statistics for the LRTF Run" << endl;
    schedFile << "\n     Number of processes: " << stacks;
    schedFile << "\n     Total Elapsed time:  " << ms << " ms ";
    schedFile << "\n     Average Waiting Time = " << static_cast<double>(total_wt) / stacks;
    schedFile << "\n     Average Turn Around time = " << static_cast<double>(total_tat) / stacks;
    schedFile << "\n     Throughput = " << static_cast<double>(stacks) / ms << endl;
    schedFile << "     CPU utilization =  Usage: " << CPUUTL << "%";
    schedFile << "   Idle: " << CPUIDL << "%";
    schedFile << "\n_________________________________________________________" << endl;

    cout << "\nThe LRTF Scheduling Has Been Successfully Processed!" << endl
         << "\nPlease Look at the Output in the File Named LRTF_output.txt" << endl;

    // Closing the files
    myfile.close();
    schedFile.close();
}

int main() {
    performLRTFScheduling();
    return 0;
}
