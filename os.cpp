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


void calculateMetrics(vector<Process>& processes) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    for (const auto& p : processes) {
        total_waiting_time += p.waiting_time;
        total_turnaround_time += p.turnaround_time;
    }
    cout << "\nAverage Waiting Time: " << (float)total_waiting_time / processes.size() << " ms";
    cout << "\nAverage Turnaround Time: " << (float)total_turnaround_time / processes.size() << " ms\n";
}

void displayGanttChart(const vector<int>& gantt_chart) {
    cout << "\nGantt Chart:\n";
    for (int pid : gantt_chart) {
        cout << "| P" << pid << " ";
    }
    cout << "|\n";
}













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