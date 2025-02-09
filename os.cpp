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

void fcfs(vector<Process> processes) {
    int time = 0;
    vector<int> gantt_chart;
    
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrival_time < b.arrival_time;
    });
    
    for (auto& p : processes) {
        if (time < p.arrival_time) {
            time = p.arrival_time;
        }
        p.waiting_time = time - p.arrival_time;
        p.turnaround_time = p.waiting_time + p.burst_time;
        p.completion_time = time + p.burst_time;
        time += p.burst_time;
        gantt_chart.insert(gantt_chart.end(), p.burst_time, p.id);
    }
    
    displayGanttChart(gantt_chart);
    calculateMetrics(processes);
}

void sjf(vector<Process> processes) {
    int time = 0, completed = 0;
    vector<int> gantt_chart;
    vector<bool> visited(processes.size(), false);
    
    while (completed < processes.size()) {
        int idx = -1, min_burst = INT_MAX;
        for (int i = 0; i < processes.size(); i++) {
            if (!visited[i] && processes[i].arrival_time <= time && processes[i].burst_time < min_burst) {
                min_burst = processes[i].burst_time;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        auto& p = processes[idx];
        p.waiting_time = time - p.arrival_time;
        p.turnaround_time = p.waiting_time + p.burst_time;
        p.completion_time = time + p.burst_time;
        time += p.burst_time;
        visited[idx] = true;
        completed++;
        gantt_chart.insert(gantt_chart.end(), p.burst_time, p.id);
    }
    
    displayGanttChart(gantt_chart);
    calculateMetrics(processes);
}

void roundRobin(vector<Process> processes, int quantum) {
    int time = 0;
    queue<int> q;
    vector<int> gantt_chart;
    for (int i = 0; i < processes.size(); i++) q.push(i);
    
    while (!q.empty()) {
        int idx = q.front(); q.pop();
        auto& p = processes[idx];
        if (p.remaining_time > quantum) {
            p.remaining_time -= quantum;
            time += quantum;
            gantt_chart.insert(gantt_chart.end(), quantum, p.id);
            q.push(idx);
        } else {
            time += p.remaining_time;
            gantt_chart.insert(gantt_chart.end(), p.remaining_time, p.id);
            p.remaining_time = 0;
            p.completion_time = time;
            p.turnaround_time = p.completion_time - p.arrival_time;
            p.waiting_time = p.turnaround_time - p.burst_time;
        }
    }
    
    displayGanttChart(gantt_chart);
    calculateMetrics(processes);
}

void priorityScheduling(vector<Process> processes) {
    int time = 0, completed = 0;
    vector<int> gantt_chart;
    vector<bool> visited(processes.size(), false);
    
    while (completed < processes.size()) {
        int idx = -1, highest_priority = INT_MAX;
        for (int i = 0; i < processes.size(); i++) {
            if (!visited[i] && processes[i].arrival_time <= time && processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        auto& p = processes[idx];
        p.waiting_time = time - p.arrival_time;
        p.turnaround_time = p.waiting_time + p.burst_time;
        p.completion_time = time + p.burst_time;
        time += p.burst_time;
        visited[idx] = true;
        completed++;
        gantt_chart.insert(gantt_chart.end(), p.burst_time, p.id);
    }
    
    displayGanttChart(gantt_chart);
    calculateMetrics(processes);
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