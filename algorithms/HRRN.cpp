#include <bits/stdc++.h>

using namespace std;

const int stacks = 1000;

// Struct
struct Process {
    int pid; // Process ID
    int bt;  // Burst Time
    int art; // Arrival time
    int ct;  // Completion time
    int wat; // Waiting time
    int btt; // Burst time
    int ta;  // Turnaround time
    int pr;  // Priority
};

// Function to compare arrival times
bool compare(Process a, Process b) {
    return a.art < b.art;
}

// Function to calculate response ratio
double responseRatio(Process p, int time) {
    return (double)(time - p.art + p.bt) / p.bt;
}

// Function to perform HRRN scheduling
void performHRRNScheduling() {
    auto begin = chrono::high_resolution_clock::now();
    double tstp;
    int total_wt;
    int total_tat;
    int wt[stacks];
    double tst;
    int sum;
    double cpuUt;

    Process process[stacks];

    
    ifstream myfile;
    ofstream schedFile;
    myfile.open("../datagen/datagen.txt");
    schedFile.open("../outputs/HRRN_output.txt");

    

    for (int i = 1; i <= stacks; i++) {
        myfile >> process[i].pid;
        myfile >> process[i].art;
        myfile >> process[i].bt;
        process[i].btt = process[i].bt;
        myfile >> process[i].pr;
    }

    // Sorting the processes according to arrival time
    sort(process, process + stacks, compare);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    int i = 0;
    int pcom = 0;

    // While all processes are not completed
    while (pcom < stacks) {
        int selectedProcess = -1;
        double maxResponseRatio = -1.0;

        for (int j = 1; j <= stacks; j++) {
            if (process[j].art > i)
                break;
            // If process is not completed
            if (process[j].bt != 0) {
                // Calculate response ratio
                double responseRatioValue = responseRatio(process[j], i);
                // If response ratio is greater than max response ratio
                if (responseRatioValue > maxResponseRatio) {
                    maxResponseRatio = responseRatioValue;
                    selectedProcess = j;
                }
            }
        }

        // If no process is selected
        if (selectedProcess != -1) {
            process[selectedProcess].ct = i + process[selectedProcess].bt;
            process[selectedProcess].bt = 0;
            pcom++;
            i = process[selectedProcess].ct;
        } else {
            i++;
        }
    }

    //Printing the output
    schedFile << "Process " << "\t" << "Arrival Time" << "\t" << "Burst Time" << "\t" << "Priority"
              << "\t" << "Completion Time   " << "\t" << "Waiting Time " << "\t" << "Turnaround Time" << endl;
    schedFile << endl;

    for (int i = 1; i <= stacks; i++) {
        total_wt = 0;
        total_tat = 0;


        // Calculating turnaround time
        process[i].wat = process[i].ct - process[i].art;
        process[i].ta = process[i].wat + process[i].btt;

        // Calculating total waiting time
        total_wt = total_wt + process[i].wat;
        total_tat = total_tat + process[i].ta;

        // Calculating total completion time/service time
        tst = (double)tst + process[i].ct;
        tstp = (double)tstp + process[i].pid;

        // Outputting the results to the file
        schedFile << process[i].pid << "\t\t" << process[i].art << "\t\t" << process[i].btt << "\t\t" << process[i].pr
                  << "\t\t" << process[i].ct << "\t\t" << "\t\t" << process[i].wat << "\t\t" << process[i].ta;
        schedFile << endl;
    }

    // Calculating CPU utilization and idle time
    auto end = chrono::high_resolution_clock::now();
    auto dur = end - begin;
    auto ms = chrono::duration_cast<chrono::milliseconds>(dur).count();

    double CPUUTL = 0;
    double CPUIDL = 0;
    CPUUTL = ((tstp / tst)) * 100;
    CPUIDL = 100 - CPUUTL;

    schedFile << "\n_________________________________________________________" << endl;
    schedFile << "\n             Statistics for the RUN" << endl;
    schedFile << "\n     Number of processes: " << stacks;
    schedFile << "\n     Total Elapsed time:  " << ms << " ms ";
    schedFile << "\n     Average Waiting Time = "
              << total_wt;
    schedFile << "\n     Average Turn Around time = "
              << total_tat;
    schedFile << "     Throughput = "
              << (double)stacks / ms << endl;
    schedFile << "     CPU utilization =  Usage: "
              << CPUUTL << "%";
    schedFile << "   Idle: " << CPUIDL << "%";
    schedFile << "\n     Average Waiting Time = "
              << (double)total_wt / stacks;
    schedFile << " ms";
    schedFile << "\n     Average Turnaround Time = "
              << (double)total_tat / stacks;
    schedFile << " ms" << endl;
    schedFile << "     Average response time = "
              << (tst - process[stacks].ct) / stacks << "ms" << endl;
    schedFile << "_________________________________________________________" << endl;

    cout << "\nThe HRRN Scheduling Has Been Successfully Processed!" << endl
         << "\nPlease Look the Output in the File Named HRRN_output.txt" << endl;

    myfile.close();
    schedFile.close();
}

int main() {
    performHRRNScheduling();
    return 0;
}
