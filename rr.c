#include<stdio.h> 
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h> 
struct process_deets{
	int pids;
	int at,bt;
	
  }pro[5];
int main() 
{ 
 
  int i,count,j,n,time,remain,flag=0,time_quantum; 
  int wait_time=0,turnaround_time=0,at[10],bt[10],rt[10]; 
  remain=n; 
 
for ( i = 0; i < 5; i++ )
{
        if ( vfork() == 0 )
        {   
          pro[i].pids=getpid();
          printf("PID:%d~\n",pro[i].pids);
            printf("Enter the arrival time of the child %d\n",getpid());
	          scanf("%d",&pro[i].at);
	          printf("Enter the burst time of the child %d\n",getpid());
	          scanf("%d",&pro[i].bt);
            exit(getpid());
            kill(getpid(), SIGSTOP);
        }  
      
}
for(i=0;i<5;i++){
at[i]=pro[i].at;
bt[i]=pro[i].bt;
}

  printf("Enter Time Quantum:\t"); 
  scanf("%d",&time_quantum); 
  printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n"); 
  for(time=0,count=0;remain!=0;) 
  { 
    if(rt[count]<=time_quantum && rt[count]>0) 
    { //if process finishes before time slot
      time+=rt[count]; 
      rt[count]=0; 
      flag=1;
      kill(pro[count].pids,SIGCONT); 
    } 
    else if(rt[count]>0) 
    {  kill(pro[count].pids,SIGCONT); 
      rt[count]-=time_quantum; 
      time+=time_quantum; 
       kill(pro[count].pids,SIGSTOP); 
    } 
    if(rt[count]==0 && flag==1) 
    { 
      remain--; 
      printf("P[%d]\t|\t%d\t|\t%d\n",pro[count].pids,time-at[count],time-at[count]-bt[count]); 
      wait_time+=time-at[count]-bt[count]; 
      turnaround_time+=time-at[count]; 
      flag=0; 
    } 
    if(count==n-1) 
      count=0; 
    else if(at[count+1]<=time) 
      count++; 
    else 
      count=0; 
  } 
  printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n); 
  printf("Avg Turnaround Time = %f",turnaround_time*1.0/n); 
  
  return 0; 
}

