#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
 
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
	int key;
  }pro[5];

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
            //exit(getpid());
            kill(getpid(), SIGSTOP);//suspends it .. can be restaretd at dequeue place
        }  
}

for(i=0;i<5;i++) //just checking if they're in the structure and printing
{
  printf("Process(%d) ID %d\n",i+1,pro[i].pids);
  printf("Priority: %d\t",pro[i].priority);
  printf("Arrival Time: %d\t",pro[i].at);
  printf("Burst Time: %d\t\n\n",pro[i].bt);
}

 for(count = 0; count < limit; count++) 
      { 
            process[count].process_id=pro[count].pids; //trasfering all the children info into scheduler
            process[count].arrival_time=pro[count].at; 
            process[count].burst_time=pro[count].bt; 
            process[count].priority =pro[count].priority;
            temp_process = process[count].priority; 
            process[count].q = Queue(temp_process);
            process[count].ready = 0; 
      }
      time = process[0].burst_time; 
      for(y = 0; y < limit; y++) 
      { 
            for(count = y; count < limit; count++) 
            { 
                  if(process[count].arrival_time < time) 
                  {
                        process[count].ready = 1;
                        
                  } 
            } 
            for(count = y; count < limit - 1; count++) 
            {
                  for(j = count + 1; j < limit; j++) 
                  { 
                        if(process[count].ready == 1 && process[j].ready == 1) 
                        { 
                              if(process[count].q == 2 && process[j].q == 1) 
                              { 
                                    temp = process[count]; 
                                    process[count] = process[j]; 
                                    process[j] = temp; 
                              } 
                        } 
                  } 
            } 
            for(count = y; count < limit - 1; count++) 
            { 
                  for(j = count + 1; j < limit; j++) 
                  {
                        if(process[count].ready == 1 && process[j].ready == 1) 
                        { 
                              if(process[count].q == 1 && process[j].q == 1) 
                              { 
                                    if(process[count].burst_time > process[j].burst_time) 
                                    { 
                                          temp = process[count]; 
                                          process[count] = process[j]; 
                                          process[j] = temp; 
                                    } 
                                    else 
                                    { 
                                          break; 
                                    } 
                              } 
                        }
                  } 
            }
        kill(process[y].process_id,SIGCONT);//process wake up based on q order  
        printf("\nProcess[%d]:\tTime:\t%d To %d\n", process[y].process_id, time, time + process[y].burst_time); 
            time = time + process[y].burst_time; 
            for(count = y; count < limit; count++) 
            { 
                  if(process[count].ready == 1) 
                  { 
                        process[count].ready = 0; 
                  } 
            } 
      } 
      return 0; 
}
