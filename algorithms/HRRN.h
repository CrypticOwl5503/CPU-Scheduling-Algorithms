#ifndef HRRN_H
#define HRRN_H

#include <bits/stdc++.h>
const int stacks = 1000;
using namespace std;

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

bool compare(Process a, Process b);
double responseRatio(Process p, int time);
void performHRRNScheduling();

#endif