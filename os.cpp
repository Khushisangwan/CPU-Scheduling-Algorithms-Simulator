#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>
#include<bits/stdc++.h>

using namespace std;

struct Process {
    int id, arrival_time, burst_time, priority, waiting_time, turnaround_time, completion_time, remaining_time;
};













int main() {
    int n, choice, quantum;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> processes(n);
    
    cout << "Enter Arrival Time, Burst Time, and Priority:\n";
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cin >> processes[i].arrival_time >> processes[i].burst_time >> processes[i].priority;
        processes[i].remaining_time = processes[i].burst_time;
    }
    
    cout << "Choose Scheduling Algorithm:\n1. FCFS\n2. SJF\n3. Round Robin\n4. Priority Scheduling\nEnter choice: ";
    cin >> choice;
    
    if (choice == 3) {
        cout << "Enter time quantum: ";
        cin >> quantum;
    }
    
    switch (choice) {
        case 1: fcfs(processes); break;
        case 2: sjf(processes); break;
        case 3: roundRobin(processes, quantum); break;
        case 4: priorityScheduling(processes); break;
        default: cout << "Invalid choice!";
    }
    return 0;
}