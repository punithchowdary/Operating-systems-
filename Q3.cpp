#include <stdio.h>
#define MAX_PROCESSES 10
struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};
int main() {
    int i, n;
    float total_waiting_time = 0, total_turnaround_time = 0;
    struct Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].pid = i + 1;
    }
    processes[0].waiting_time = 0;
    processes[0].turnaround_time = processes[0].burst_time;
    for (i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].turnaround_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
    printf("PID  Arrival Time  Burst Time  Waiting Time  Turnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%2d%10d%12d%14d%18d\n", processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }
    printf("Average waiting time: %.2f\n", total_waiting_time / n);
    printf("Average turnaround time: %.2f\n", total_turnaround_time / n);

    return 0;
}

