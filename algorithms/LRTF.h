#ifndef LRTF_H
#define LRTF_H

#include <bits/stdc++.h>
using namespace std;
const int stacks = 1000;

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

bool compareArrival(const Process &a, const Process &b);
bool compareRemainingTime(const Process &a, const Process &b);
void performLRTFScheduling();

#endif
