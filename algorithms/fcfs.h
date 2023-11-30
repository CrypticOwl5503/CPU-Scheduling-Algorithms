#ifndef fcfs_h
#define fcfs_h

#include <bits/stdc++.h>

using namespace std;

const int stacks = 1000;

void calculateCPUUtilization(double& CPUUTL, double& CPUIDL, double tst, double tstp);
void processFCFS(ifstream& myfile, ofstream& schedFile);

#endif