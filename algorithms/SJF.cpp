#include <bits/stdc++.h>


using namespace std;

int stacks = 1000;

// Struct
struct Process {
    int pid;      // Process ID
    int bt;       // Burst Time
    int art;      // Arrival time
    int ct;       // Completion time
    int wat;      // Waiting time
    int btt;      // Burst time
    int ta;       // Turnaround time
    int pr;       // Priority
};

// Function to compare arrival times
bool compare(Process a, Process b) {
    return a.art < b.art;
}

// Function to compare burst time
bool compare2(Process a, Process b) {
    return a.bt < b.bt;  // SJF uses '<' for sorting in ascending order of burst time
}

// Function for Shortest Job First (SJF) scheduling
void shortestJobFirstScheduling(Process process[]) {
    // Local variables
    auto begin = chrono::high_resolution_clock::now();
    double tstp = 0;
    int total_wt = 0;
    int total_tat = 0;
    double tst = 0;

    // File streams, opens the files
    ifstream myfile;
    ofstream schedFile;
    myfile.open("../datagen/datagen.txt");
    schedFile.open("../outputs/SJF_output.txt");

    // Local variables
    int i, j, pcom;

    cout << "Processing... Please Wait..." << endl;

    // Getting all the values from the output text file
    for (i = 1; i <= stacks; i++) {
        myfile >> process[i].pid;
        myfile >> process[i].art;
        myfile >> process[i].bt;
        process[i].btt = process[i].bt;  // It will be used for the algorithm
        myfile >> process[i].pr;
    }

    // Sorting the processes according to arrival time
    sort(process, process + stacks, compare);

    // Initializing the variables
    i = 0;
    pcom = 0;

    // Processing each process until it completes
    while (pcom < stacks) {
        for (j = 1; j <= stacks; j++) {
            if (process[j].art > i)
                break;
        }

        // Sorting the processes according to burst time (SJF)
        sort(process, process + j, compare2);

        // Selecting the shortest job in the process
        if (j > 0) {
            for (j = 1; j <= stacks; j++) {
                if (process[j].bt != 0)
                    break;
            }

        
            if (process[j].art > i) {
                i = process[j].art;
            }

            process[j].ct = i + 1;  // Calculations for the completion time
            process[j].bt--;       // Decrement the burst time
        }
        pcom = 0;
        i++;

        // If the burst time is 0, proceed to the next process
        for (j = 1; j <= stacks; j++) {
            if (process[j].bt == 0)
                pcom++;
        }
    }

    // Outputs them into a text file
    schedFile << "Process "
              << "\t"
              << "Arrival Time"
              << "\t"
              << "Burst Time"
              << "\t"
              << "Priority"
              << "\t"
              << "Completion Time   "
              << "\t"
              << "Waiting Time "
              << "\t"
              << "Turnaround Time" << endl;
    schedFile << endl;

    // Processing each process
    for (i = 1; i <= stacks; i++) {
        total_wt = 0;
        total_tat = 0;

        process[i].wat = process[i].ct - process[i].art;  // Calculating the waiting time
        process[i].ta = process[i].wat + process[i].btt;  // Calculating the turnaround time

        total_wt = total_wt + process[i].wat;    // Calculating the total waiting time
        total_tat = total_tat + process[i].ta;   // Calculating the total turnaround time

        tst = (double)tst + process[i].ct;       // Calculating the total completion time/service time
        tstp = (double)tstp + process[i].pid;    // Calculating the total number of processes

        // Output the result into a text file
        schedFile << process[i].pid << "\t\t" << process[i].art << "\t\t" << process[i].btt << "\t\t" << process[i].pr
                  << "\t\t" << process[i].ct << "\t\t"
                  << "\t\t" << process[i].wat << "\t\t" << process[i].ta;
        schedFile << endl;
    }

    // Calculations for the elapsed time
    auto end = chrono::high_resolution_clock::now();
    auto dur = end - begin;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

    // Calculations for CPU UTILIZATION and CPU IDLE
    double CPUUTL = 0;
    double CPUIDL = 0;
    CPUUTL = ((tstp / tst)) * 100;
    CPUIDL = 100 - CPUUTL;

    schedFile << "\n_________________________________________________________" << endl;
    schedFile << "\n             Statistics for the RUN" << endl;
    schedFile << "\n     Number of processes: " << stacks;
    schedFile << "\n     Total Elapsed time:  " << ms << " ms ";
    schedFile << "\n     Average Waiting Time = " << total_wt;
    schedFile << "\n     Average Turn Around time = " << total_tat;
    schedFile << "     Throughput = " << (double)stacks / ms << endl;  // Calculations for throughput
    schedFile << "     CPU utilization =  Usage: " << CPUUTL << "%";
    schedFile << "   Idle: " << CPUIDL << "%";
    schedFile << "\n     Average Waiting Time = " << (double)total_wt / stacks;  // Calculations for the average waiting time
    schedFile << " ms";
    schedFile << "\n     Average Turnaround Time = " << (double)total_tat / stacks;  // Calculations for the average turnaround time
    schedFile << " ms" << endl;
    schedFile << "     Average response time = " << (tst - process[stacks].ct) / stacks << "ms" << endl;  // Calculations for the average response time
    schedFile << "_________________________________________________________" << endl;

    cout << "\nThe Shortest Job First (SJF) Scheduling Has Been Successfully Processed!" << endl
         << "\nPlease Look the Output in the File Named SJF_output.txt" << endl;

    // Closing the files
    myfile.close();
    schedFile.close();
}

int main() {
    // Object
    Process process[stacks];

    // Calling SJF scheduling function
    shortestJobFirstScheduling(process);

    return 0;
}


