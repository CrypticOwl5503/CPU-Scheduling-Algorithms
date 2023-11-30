#include <bits/stdc++.h>

using namespace std;

int stacks = 1000;

struct Process {
    int pid;
    int bt;       // Burst Time
    int art;      // Arrival time
    int ct;       // Completion time
    int wat;      // Waiting time
    int btt;      // Remaining Burst time
    int ta;       // Turnaround time
    int pr;       // Priority
};

bool compare(Process a, Process b) {
    return a.art < b.art;
}
// Compares the arrival time of two processes
bool compare2(Process a, Process b) {
    return a.btt > b.btt;  
}

void longestJobFirstScheduling(Process process[]) {
    auto begin = chrono::high_resolution_clock::now();
    double tstp = 0;
    int total_wt = 0;
    int total_tat = 0;
    double tst = 0;

    ifstream myfile;
    ofstream schedFile;
    myfile.open("../datagen/datagen.txt");
    schedFile.open("../outputs/LJF_output.txt");

    int i, j, pcom;

    cout << "Processing... Please Wait..." << endl;

    for (i = 1; i <= stacks; i++) {
        myfile >> process[i].pid;
        myfile >> process[i].art;
        myfile >> process[i].bt;
        process[i].btt = process[i].bt;  // Initialize remaining burst time
        myfile >> process[i].pr;
    }

    sort(process, process + stacks, compare);

    i = 0;
    pcom = 0;

    while (pcom < stacks) {
        for (j = 1; j <= stacks; j++) {
            if (process[j].art > i)
                break;
        }

        sort(process, process + j, compare2);

        if (j > 0) {
            for (j = 1; j <= stacks; j++) {
                if (process[j].btt != 0)
                    break;
            }

            if (process[j].art > i) {
                i = process[j].art;
            }

            process[j].ct = i + process[j].btt;  // Completion time is the current time plus remaining burst time
            process[j].btt = 0;  // The process is completed, set remaining burst time to 0
        }
        pcom = 0;
        i++;

        for (j = 1; j <= stacks; j++) {
            if (process[j].btt == 0)
                pcom++;
        }
    }

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

    for (i = 1; i <= stacks; i++) {
        process[i].wat = process[i].ct - process[i].art;
        process[i].ta = process[i].wat + process[i].bt;

        total_wt = total_wt + process[i].wat;
        total_tat = total_tat + process[i].ta;

        tst = tst + process[i].ct;
        tstp = tstp + process[i].pid;

        schedFile << process[i].pid << "\t\t" << process[i].art << "\t\t" << process[i].bt << "\t\t" << process[i].pr
                  << "\t\t" << process[i].ct << "\t\t" << process[i].wat << "\t\t" << process[i].ta;
        schedFile << endl;
    }

    auto end = chrono::high_resolution_clock::now();
    auto dur = end - begin;
    auto ms = chrono::duration_cast<chrono::milliseconds>(dur).count();

    double CPUUTL = 0;
    double CPUIDL = 0;
    CPUUTL = (tstp / tst) * 100;
    CPUIDL = 100 - CPUUTL;

    schedFile << "\n_________________________________________________________" << endl;
    schedFile << "\n             Statistics for the RUN" << endl;
    schedFile << "\n     Number of processes: " << stacks;
    schedFile << "\n     Total Elapsed time:  " << ms << " ms ";
    schedFile << "\n     Average Waiting Time = " << total_wt;
    schedFile << "\n     Average Turn Around time = " << total_tat;
    schedFile << "     Throughput = " << (double)stacks / ms << endl;
    schedFile << "     CPU utilization =  Usage: " << CPUUTL << "%";
    schedFile << "   Idle: " << CPUIDL << "%";
    schedFile << "\n     Average Waiting Time = " << (double)total_wt / stacks;
    schedFile << " ms";
    schedFile << "\n     Average Turnaround Time = " << (double)total_tat / stacks;
    schedFile << " ms" << endl;
    schedFile << "     Average response time = " << (tst - process[stacks].ct) / stacks << "ms" << endl;
    schedFile << "_________________________________________________________" << endl;

    cout << "\nThe Longest Job First (LJF) Scheduling Has Been Successfully Processed!" << endl
         << "\nPlease Look the Output in the File Named LJF_output.txt" << endl;

    myfile.close();
    schedFile.close();
}

int main() {
    Process process[stacks];

    longestJobFirstScheduling(process);

    return 0;
}
