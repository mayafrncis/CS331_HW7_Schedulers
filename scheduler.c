#include <stdio.h>
#include <stdlib.h>

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


void print(int n, struct process* processes) {
//	printf("Gantt Chart: |");
//	for (int i = 0; i < n; i++) {
//		printf("  |  P%d", i+1);
//	}
	printf("\nPID   AT    BT    WT     TAT     RT\n");
	float sumWT = 0;
	float sumTAT = 0;
	float sumRT = 0;
	for (int i = 0; i < n; i++) {
		printf("%-5d %-5d %-5d %-5d %-5d %-5d", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].turnaround_time, processes[i].waiting_time, processes[i].response_time);
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

	fcfs(processes, n);

	print(n, processes);
	return 0;
}
