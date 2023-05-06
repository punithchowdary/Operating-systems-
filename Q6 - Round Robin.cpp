#include <stdio.h>
struct Process {
    int pid;
    int bt;
    int wt; 
    int tat;
};
void roundRobinScheduling(struct Process p[], int n, int tq) {
    int i, j, t, rem_bt[n];
    for (i = 0; i < n; i++)
        rem_bt[i] = p[i].bt;
    int time = 0;
    while (1) {
        int done = 1;
        for (i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = 0;
                if (rem_bt[i] > tq) {
                    time += tq;
                    rem_bt[i] -= tq;
                } else {
                    time += rem_bt[i];
                    p[i].wt = time - p[i].bt;
                    rem_bt[i] = 0;
                }
            }
        }
        if (done == 1)
            break;
    }
    for (i = 0; i < n; i++)
        p[i].tat = p[i].bt + p[i].wt;
}

int main() {
    int n, tq, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (i = 0; i < n; i++) {
        printf("Enter process %d burst time: ", i+1);
        scanf("%d", &p[i].bt);
        p[i].pid = i+1;
    }
    printf("Enter time quantum: ");
    scanf("%d", &tq);
    roundRobinScheduling(p, n, tq);
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++)
        printf("%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].bt, p[i].wt, p[i].tat);
}
