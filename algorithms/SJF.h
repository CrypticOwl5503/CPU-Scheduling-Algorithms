#ifndef SJF_H
#define SJF_H

#include <bits/stdc++.h>
using namespace std;

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

bool compare(Process a, Process b);
bool compare2(Process a, Process b);
void shortestJobFirstScheduling(Process process[]);

#endif


