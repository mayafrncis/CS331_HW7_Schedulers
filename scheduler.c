#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct process {
	int pid; 
	int arrival_time;
	int burst_time;
	int turnaround_time;
	int waiting_time;
	int response_time;
};

int compAT(const void* a, const void* b){
	struct process* p1 = (struct process*) a;
	struct process* p2 = (struct process*) b;
	return p1->arrival_time - p2->arrival_time;
}

int compBT(const void* a, const void* b){
        struct process* p1 = (struct process*) a;
        struct process* p2 = (struct process*) b;
        return p1->burst_time - p2->burst_time;
}


void print(int n, struct process* processes, int sched) {
	if (sched == 0) {
		printf("=== Shortest Job First (SJF) ===\n");
	} else if (sched == 1) {
		printf("=== First Come First Served (FCFS) ===\n");
	}
	printf("Gantt Chart: |");
	for (int i = 0; i < n; i++) { // make spaces according to burst time, a space per time
		for(int j = 0; j < processes[i].burst_time; j++) {
			printf(" ");
		}
		printf("P%d", processes[i].pid);
		for (int j = 0; j < processes[i].burst_time; j++) {
			printf(" ");
		}
		printf("|");
	}
	printf("\nPID   AT    BT    WT    TAT   RT\n");
	float sumWT = 0;
	float sumTAT = 0;
	float sumRT = 0;
	for (int i = 0; i < n; i++) {
		printf("%-5d %-5d %-5d %-5d %-5d %-5d", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time, processes[i].response_time);
		printf("\n");
		sumWT += processes[i].waiting_time;
		sumTAT += processes[i].turnaround_time;
		sumRT += processes[i].response_time;
	}
	printf("\nAverage Waiting Time: %.2f\n", sumWT/n);
	printf("Average Turnaround Time: %.2f\n", sumTAT/n);
	printf("Average Response Time: %.2f\n", sumRT/n);
}

void fcfs(struct process* processes, int n) {
	qsort(processes, n, sizeof(struct process), compAT);
	processes[0].turnaround_time = processes[0].burst_time;
	for (int i = 1; i < n; i++) {
		processes[i].waiting_time = processes[i-1].waiting_time + processes[i-1].burst_time - processes[i].arrival_time + processes[i-1].arrival_time;
		processes[i].response_time = processes[i].waiting_time;
		processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
	}
}

void sjf(struct process* processes, int n) {
	int current_time = 0;
	int count = 0;
	struct process schedule[n];
	bool scheduled[n];
	for(int i = 0;i < n; i++){
		scheduled[i] = false;
	}

	while (count < n) {
		int shortest = INT_MAX;
		int chosen = -1; // -1 as a flag for no processes to schedule
		for (int j = 0; j < n; j++) { // to loop through all the processes and find all those available at that time
			if (scheduled[j] == false && processes[j].arrival_time <= current_time && processes[j].burst_time < shortest) {
				shortest = processes[j].burst_time;
				chosen = j;
			}
		}
		if (chosen == -1) {
			current_time++;
		} else {
			scheduled[chosen] = true;
			schedule[count] = processes[chosen];
			current_time += processes[chosen].burst_time;
			count++;
		}
	}
	schedule[0].waiting_time = 0;
	schedule[0].response_time = 0;
	schedule[0].turnaround_time = schedule[0].burst_time;
	for (int i = 1; i < n; i++) {
		schedule[i].waiting_time = schedule[i-1].waiting_time + schedule[i-1].burst_time + schedule[i-1].arrival_time - schedule[i].arrival_time;
		schedule[i].response_time = schedule[i].waiting_time;
		schedule[i].turnaround_time = schedule[i].waiting_time + schedule[i].burst_time;
	}
	for (int i = 0; i < n; i++) {
		processes[i] = schedule[i];
	}
}

int main() {
	int n;
	printf("Enter the number of processes: ");
	scanf("%d", &n);

	struct process* processes = (struct process*) malloc(sizeof(struct process) * n);
	for (int i = 0; i < n; i++) {
		processes[i].pid = i + 1;
		printf("\nEnter the arrival time and burst time for process:");
		scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
	}

	//sjf(processes, n);
	fcfs(processes,n);

	print(n, processes, 1); // 0 as a flag for sjf and 1 for fcfs;
	return 0;
}
