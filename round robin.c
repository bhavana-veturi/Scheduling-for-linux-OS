#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdbool.h> //to use bool variables
 
#define N 10 
 
typedef struct 
{ 
      int process_id, arrival_time, burst_time, priority;
      
      int q, ready; 
}process_structure; 
 
int Queue(int t1) 
{ 
      if(t1 == 0 || t1 == 1 || t1 == 2 || t1 == 3) 
      { 
            return 1; 
      } 
      else
      {
            return 2; 
      }
} 
 struct process_deets{
	int pids;
	int priority;
        int at,bt;
        int wt,tat;
	int key;
  }pro[5];

void findWaitingTime(int at[5],int bt[5],int wt[5],int tat[5])  //(int processes[], int n, int bt[], int wt[], int quantum)
{  
  int i;
    int quantum=4; //time period each process gets
    int rem_bt[5]; //  // Make a copy of burst times bt[] to store remaining burst times.
    for (i=0;i<5;i++)
        rem_bt[i] =  bt[i];
 
    int t = 0; // Current time
    while (1) // Keep traversing processes in round robin manner until all of them are not done.
    {
        bool done = true;
        for (int i = 0 ; i < 5; i++)
        {
            // If burst time of a process is greater than 0 then only need to process further
            if (rem_bt[i] > 0)
            {
                done = false; // There is a pending process
 
                if (rem_bt[i] > quantum)
                {   kill(pro[i].pids,SIGCONT);//process runs for this time quantum
                    // Increase the value of t i.e. shows how much time a process has been processed
                    t += quantum;
 
                    // Decrease the burst_time of current process by quantum
                    rem_bt[i] -= quantum;
                   kill(pro[i].pids,SIGSTOP);
                }
 
                else  // If burst time is smaller than or equal to quantum. Last cycle for this process
                {   kill(pro[i].pids,SIGCONT);
                    t = t + rem_bt[i]; // Increase the value of t i.e. shows how much time a process has been processed
                    wt[i] = t - bt[i];  // Waiting time is current time minus time used by this process                
                    rem_bt[i] = 0; // As the process gets fully executed make its remaining burst time = 0
		
                }
            }
        }   
        if (done == true) // If all processes are done
          break;
    }
} 
 
// Function to calculate turn around time
void findTurnAroundTime(int bt[5],int wt[5],int tat[5]) // int processes[], int n, int bt[], int wt[], int tat[])
{
    // calculating turnaround time by adding
    // bt[i] + wt[i]
    for (int i = 0; i < 5 ; i++)
        tat[i] = bt[i] + wt[i];
}
 
// Function to calculate average time
void findavgTime(int at[5],int bt[5],int wt[5],int tat[5]) //int processes[], int n, int bt[],int quantum)
{
    findWaitingTime(at,bt,wt,tat);
 
    findTurnAroundTime(bt,wt,tat);
   
    float total_wt, total_tat;
     for (int i=0; i<5; i++) // Display processes along with all details
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf("\nProcess %d \tBurst time: %d \t Waiting Time: %d Turn Around Time: %d\n",i+1,bt[i],wt[i],tat[i]);
    }
    total_wt=total_wt/5;
    total_tat=total_tat/5;
    printf("Average waiting time=%f\n",total_wt);
    printf("Average turn around time=%f\n",total_tat);
} 


int main() 
{ 
      int  count, temp_process, time, j, i,y; 
      process_structure temp; 
      int limit=5; //number of processes is 5
      process_structure process[5]; 
for ( i = 0; i < 5; i++ )
{
        if ( vfork() == 0 )
        {   
          pro[i].pids=getpid();
          printf("~Process Number %d PID:%d~\n",i+1,pro[i].pids);
            printf("Enter the priority of the child %d\n",getpid());
	          scanf("%d",&pro[i].priority);
            printf("Enter the arrival time of the child %d\n",getpid());
	          scanf("%d",&pro[i].at);
	          printf("Enter the burst time of the child %d\n",getpid());
	          scanf("%d",&pro[i].bt);
            exit(getpid());
            kill(getpid(), SIGSTOP);//suspends it .. can be restaretd
        }  
}

for(i=0;i<5;i++) //checking if they're in the structure and printing
{
  printf("Process(%d) ID %d\n",i+1,pro[i].pids);
  printf("Priority: %d\t",pro[i].priority);
  printf("Arrival Time: %d\t",pro[i].at);
  printf("Burst Time: %d\t\n\n",pro[i].bt);
}
int at[5],bt[5],wt[5],tat[5] ;
for(i=0;i<5;i++)    //passing arrival and burst times into another array
{
at[i]=pro[i].at;
bt[i]=pro[i].bt;
wt[i]=pro[i].wt;
tat[i]=pro[i].tat;
}

findavgTime(at,bt,wt,tat);
return 0; 
}

