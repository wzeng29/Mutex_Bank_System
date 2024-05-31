#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Define a structure for a process
struct Process {
    char proName[3];
    int arrTime;
    int burst;
    int turnAround;
    int waitTime;
    int procing;
    char a;
    int isOver;
};
struct Process* findNextProcessToRun(struct Process* processes, int num_processes, int cpu_time, int n_completed) {
    struct Process* current_process = NULL;

    if (n_completed < num_processes) {
        for (int i = 0; i < num_processes; ++i) {
            struct Process* candidate_process = &processes[i];
            
            if (candidate_process->isOver || candidate_process->arrTime > cpu_time)
                continue; // Skip completed processes and those not yet arrived
                
            if (current_process == NULL || 
                candidate_process->burst < current_process->burst ||
                (candidate_process->burst == current_process->burst && 
                 candidate_process->arrTime < current_process->arrTime)) {
                current_process = candidate_process;
            }
        }
    }
    
    return current_process;
}
void completeProcess(struct Process* process, int cpu_time, int* total_turnaround_time, int* total_waiting_time, int* n_completed) {
    process->turnAround = cpu_time - process->arrTime;
    process->waitTime = process->turnAround - process->burst;
    *total_turnaround_time += process->turnAround;
    *total_waiting_time += process->waitTime;
    printf("Process %s completed with Turnaround Time: %d, Waiting Time: %d\n",
        process->proName, process->turnAround, process->waitTime);
    process->isOver = 1;
}
int resetRunTime(runTime){
    runTime = 0;
    return runTime;
}
//main function
int main() {
    //open file
    FILE *file = fopen("sjf_input.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[256];
    int test_case_number = 0;
    //readfile
    while (fgets(line, sizeof(line), file)) {
        char lineCpy[256];
        strcpy(lineCpy, line);
        int lineLen = strlen(lineCpy);
        if (lineLen > 0) { if (lineCpy[lineLen - 1] == '\n') lineCpy[--lineLen] = '\0'; }
        test_case_number+=1;
        char *token = strtok(line, " ");
        int num_processes = 0;
        int totalTurn = 0;
        int totalWait = 0;
       //alocate struct
        struct Process processes[100];
        //str -> int
        while (token != NULL) {
            num_processes++; 
            strcpy(processes[num_processes - 1].proName, token);
            token = strtok(NULL, " ");
            processes[num_processes - 1].arrTime = atoi(token);
            token = strtok(NULL, " ");
            processes[num_processes - 1].burst = atoi(token);
            token = strtok(NULL, " ");
            processes[num_processes - 1].isOver = 0;
        }
        int cpuTime = 0;
        
        printf("Number of Processes: %d\n", num_processes);
        printf("Process Scheduling Started:\n");

        for (int i = 0; i < num_processes; i++) {
            for (int j = i + 1; j < num_processes; j++) {
                if (processes[i].arrTime > processes[j].arrTime) {
                    struct Process temp = processes[i];
                    processes[i] = processes[j];
                    processes[j] = temp;
                }
            }
        }
       //init
        int arrIndex, runTime, completedPro = 0;
        struct Process *currentProc = NULL;

        while (completedPro < num_processes) {
            if (currentProc == NULL) {
    for (int i = 0; i < num_processes; ++i) {
        int flag = currentProc==NULL;
        
        struct Process *proc = &processes[i];
        int flag1 = proc->isOver;
        int flag2 = proc->arrTime > cpuTime;
        if (proc->isOver) { continue; }

        
        else if (flag2) { continue; }

        if (flag)  { currentProc = proc; }

        if (proc->burst < currentProc->burst) { currentProc = proc; }

        if (proc->burst == currentProc->burst && proc->arrTime < currentProc->arrTime) { currentProc = proc; }
    }
}
        struct Process* nextProcess = findNextProcessToRun(processes, num_processes, cpuTime, completedPro);
        //completeProcess(processes, cpuTime, &total_turnaround_time, &total_waiting_time, &completedPro);
            

            while (arrIndex < num_processes && processes[arrIndex].arrTime == cpuTime) {  
                if (arrIndex < num_processes && processes[arrIndex].arrTime == cpuTime) break;   
                printf("CPU Time %d: [%s Arrived]", cpuTime, processes[arrIndex].proName);
                ++arrIndex;
            }
            
            
            
            if (currentProc!= NULL) {
                printf(" %s ", currentProc->proName);
                printf("[%d / %d]", runTime, currentProc->burst);
                runTime += 1;
            }




            if ( currentProc == NULL) {
                printf("CPU Time %d: None",cpuTime);
                printf(" \n");
            } 
            else {
                printf("\n");
            }

            int con = (currentProc != NULL && runTime > currentProc->burst);
            

            if (con) {
                currentProc->turnAround = cpuTime-currentProc->arrTime;
                currentProc->waitTime = currentProc->turnAround-currentProc->burst;

                totalTurn = currentProc->turnAround+ totalTurn  ;
                totalWait = currentProc->waitTime +totalWait;
                }
            
            if (con) {
                printf("Process %s completed: \n",currentProc->proName );
                printf("Turnaround Time: %d, Waiting Time: %d\n", currentProc->turnAround,currentProc->waitTime);}
            
            
            
            
            if (con) {
                currentProc->isOver = 1;
                currentProc = NULL;
                completedPro =  completedPro+1;
                runTime = 0;
            } 
            else {
                cpuTime+=1;
            }
        }
        double avg_turnaround_time, avg_waiting_time;

        avg_waiting_time = (double)totalWait / (double)num_processes;
        avg_turnaround_time = (double)totalTurn / (double)num_processes;
       

        printf("Process scheduling completed with: \n");
        printf("Avg Turnaround Time: %.2f, ",avg_turnaround_time);
        printf("Avg Waiting Time:%.2f\n", avg_waiting_time);
    }
    return 0;
}