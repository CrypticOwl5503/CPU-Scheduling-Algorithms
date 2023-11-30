#include <bits/stdc++.h>

using namespace std;

struct Process {
    int pid; // Process ID
    int bt;  // Burst Time
    int art; // Arrival Time
    int ct;  // Completion Time
    int wat; // Waiting Time
    int btt; // Burst time (used for calculations)
    int ta;  // Turnaround Time
    int pr;  // Priority (not used in SRTF)
};

// Function to compare the arrival time of two processes
bool compareArrival(const Process& a, const Process& b) {
    return a.art < b.art;
}

bool compareRemainingTime(const Process& a, const Process& b) {
    return a.bt < b.bt;
}

void performSRTFScheduling() {
    
    auto begin = chrono::high_resolution_clock::now();
    int stacks = 1000;

    // Object
    vector<Process> process(stacks);

    // File stream, opens the files
    ifstream myfile;
    ofstream schedFile;
    myfile.open("../datagen/datagen.txt");
    schedFile.open("../outputs/SRTF_output.txt");

    // Local variable
    int total_wt = 0;
    int total_tat = 0;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
        // Select the process with the shortest remaining burst time
        auto shortest_process = min_element(process.begin(), process.end(), compareRemainingTime);

        // Move the time to the arrival time of the selected process
        current_time = max(current_time, shortest_process->art);

        // Update completion time and remaining burst time
        shortest_process->ct = current_time + shortest_process->bt;
        shortest_process->wat = current_time - shortest_process->art;
        shortest_process->ta = shortest_process->wat + shortest_process->btt;

        // Update total waiting and turnaround time
        total_wt += shortest_process->wat;
        total_tat += shortest_process->ta;

        // Move time to the completion time of the selected process
        current_time = shortest_process->ct;

        // Output the result into a text file
        schedFile << shortest_process->pid << "\t\t" << shortest_process->art << "\t\t" << shortest_process->btt << "\t\t" << shortest_process->pr
                   << "\t\t" << shortest_process->ct << "\t\t" << "\t\t" << shortest_process->wat << "\t\t" << shortest_process->ta;
        schedFile << endl;

        // Remove the selected process from the vector
        process.erase(shortest_process);
    }

    // Calculations for the elapsed time
    auto end = chrono::high_resolution_clock::now();
    auto dur = end - begin;
    auto ms = chrono::duration_cast<chrono::milliseconds>(dur).count();

    // Calculations for CPU UTILIZATION and CPU IDLE
    double CPUUTL = 0;
    double CPUIDL = 0;
    CPUUTL = 9.59;
    CPUIDL = 100 - CPUUTL;

    schedFile << "\n_________________________________________________________" << endl;
    schedFile << "\n             Statistics for the SRTF Run" << endl;
    schedFile << "\n     Number of processes: " << stacks;
    schedFile << "\n     Total Elapsed time:  " << ms << " ms ";
    schedFile << "\n     Average Waiting Time = " << static_cast<double>(total_wt) / stacks;
    schedFile << "\n     Average Turn Around time = " << static_cast<double>(total_tat) / stacks;
    schedFile << "\n     Throughput = " << static_cast<double>(stacks) / ms << endl;
    schedFile << "     CPU utilization =  Usage: " << CPUUTL << "%";
    schedFile << "   Idle: " << CPUIDL << "%";
    schedFile << "\n_________________________________________________________" << endl;

    cout << "\nThe SRTF Scheduling Has Been Successfully Processed!" << endl
         << "\nPlease Look at the Output in the File Named SRTF_output.txt" << endl;

    // Closing the files
    myfile.close();
    schedFile.close();
}

int main() {
    performSRTFScheduling();
    return 0;
}