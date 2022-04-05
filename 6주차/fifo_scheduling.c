#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "plist.dat"
#define _CRT_SECURE_NO_WARNINGS

void printResult(int pnum, int* pid, int* at, int* bt, int* tt, int* wt) {
    int i, sum_tt = 0, sum_wt = 0;

    printf("%15s %15s %15s %15s %15s\n", "Process id", "Arrive time", "Burst time", "Turnaround time", "Waiting time");
    for (i = 0; i < pnum; ++i) {
        printf("%15d %15d %15d %15d %15d\n", pid[i], at[i], bt[i], tt[i], wt[i]);
        sum_tt += tt[i];
        sum_wt += wt[i];
    }

    printf("  avg. of TT: %.2f\n", (float)sum_tt / pnum);
    printf("  avg. of WT: %.2f\n", (float)sum_wt / pnum);
}

void FIFO(int pnum, int* pid, int* at, int* bt, int* tt, int* wt) {
    printf("  Scheme: First-In-First-Out\n");
    int s = 0;
    for (int i = 0; i < pnum; i++) {
        if (!i) {
            if (at[i] > bt[i]) s = at[i];
            else s = bt[i];
        }
        else {
            if (at[i] > s) {
                int t = at[i] - s;
                s += t;
            }
            s += bt[i];
        }
        tt[i] = s - at[i];
        wt[i] = s - at[i] - bt[i];
    }
}

int main(void) {
    FILE* fp;
    int pnum, i, exit = 0;
    int* pid, * at, * bt, * tt, * wt;

    fp = fopen(INPUT_FILE, "r");
    //read the number of processes
    fscanf(fp, "%d", &pnum);

    pid = (int*)calloc(pnum, sizeof(int));
    at = (int*)calloc(pnum, sizeof(int));
    bt = (int*)calloc(pnum, sizeof(int));
    tt = (int*)calloc(pnum, sizeof(int));
    wt = (int*)calloc(pnum, sizeof(int));

    for (i = 0; i < pnum; i++) {
        fscanf(fp, "%d %d %d", &pid[i], &at[i], &bt[i]);
    }

    FIFO(pnum, pid, at, bt, tt, wt);
    printResult(pnum, pid, at, bt, tt, wt);

    fclose(fp);

    memset(tt, 0, sizeof(int) * pnum);
    memset(wt, 0, sizeof(int) * pnum);

    return 0;
}
