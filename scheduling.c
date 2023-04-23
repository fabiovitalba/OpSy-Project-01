/**
  @brief Implementation of non pre-emptive algorithms for process
         scheduling.

         Firt Come First Served: FCFS
         Shortest-Job First: SJF

  Scheduling on one CPU.
*/

#include "scheduling.h"
#include <stdio.h>
#include <stdlib.h>

#define SCH_DEBUG 1
#define SCH_VERBOSE 1
#define TBL_ID 0
#define TBL_ARRIVAL 1
#define TBL_BURST 2

void info_sch_problem(char *context, sch_problem *sch);
void info_sch_solution(char *context, sch_solution *sol);
void sort_sch_problem_asc(sch_problem *sch, int sort_by);
void sch_table_swap(sch_problem *sch, int i, int j);
int get_no_of_jobs_waiting(int cycle, int next_job_id, sch_problem *sch);
void sch_solution_malloc(sch_solution *sol);

/**
  Allocate memory for the table in the scheduling problem structure sch in
  parameter. It allocates the memory to hold a matrix of int sch->num x 3.
  Each row i of the table holds the information about one job:
          sch->table[i][ID]      : i+1
          sch->table[i][ARRIVAL] : arrival time
          sch->table[i][BURST]   : burst time

  @param sch the address of the scheduling problem;
       sch->num must already contain the number of jobs
       in the instance.
*/
void sch_table_malloc(sch_problem *sch) {
  sch->table = (int**)malloc(sizeof(int*) * sch->num);
  for (int i = 0; i < sch->num; i++) {
    sch->table[i] = (int*)malloc(sizeof(int) * 3);
  }
}

/**
  Free the memory occupied by the table of the scheduling
  problem at sch.

  @param sch the address of the scheduling problem
*/
void sch_table_free(sch_problem *sch) {
  for(int i = 0; i < sch->num; i++) {
    free(sch->table[i]);
  }
  free(sch->table);
}

/**
  Get a scheduling problem instance from the user.
  
  @return the address of the scheduling problem structure
          containing the instance provided by the user
*/
sch_problem * sch_get_scheduling_problem_instance() {
  // TODO
}

/**
   Compute the solution to a scheduling problem with First Come First
   Served scheduling. Break ties in favour of the job with lower index
   in sch->table.

   @param sch the address of the scheduling problem to solve

   @return the address of the computer scheduling solution
 */
sch_solution * sch_fcfs(sch_problem *sch) {
  info_sch_problem("sch_fcfs",sch);

  sch_solution *sol = (sch_solution*) malloc(sizeof(sch_solution));
  sol->num = sch->num;
  sch_solution_malloc(sol);
  
  sort_sch_problem_asc(sch,TBL_ARRIVAL);

  int job_id = 0, cycle = 0, wait_time = 0, burst = 0;
  while(job_id < sch->num) {
    if (sch->table[job_id][TBL_ARRIVAL] <= cycle) {
      if (burst == 0) {
        // start next process
        if (SCH_VERBOSE)
          printf("(  %d) Running job %d, arrived at %d, with burst time %d.\n", cycle, sch->table[job_id][TBL_ID], sch->table[job_id][TBL_ARRIVAL], sch->table[job_id][TBL_BURST]);

        burst = sch->table[job_id][TBL_BURST];
        sol->order[job_id] = sch->table[job_id][TBL_ID];
        job_id++;
      }
    } else {
      // no process to start
      if((burst == 0) && SCH_VERBOSE)
        printf("(  %d) No job ready.\n", cycle);
    }
    if (burst > 0)
      burst--;
    wait_time += get_no_of_jobs_waiting(cycle, job_id, sch);
    cycle++;
  }
  if (sch->num > 0)
    sol->wait_average = (float)wait_time / sch->num;
  if(SCH_DEBUG)
    printf("wait_time: %d, avg: %f\n", wait_time, sol->wait_average);

  info_sch_solution("sch_fcfs - after run",sol);
  return sol;
}

/**
   Compute the solution to a scheduling problem with Shortest Job
   First scheduling. Break ties in favour of the job with lower index
   in sch->table.

   @param sch the address of the scheduling problem to solve

   @return the address of the computer scheduling solution
 */
sch_solution * sch_sjf(sch_problem *sch) {
  info_sch_problem("sch_sjf",sch);

  sch_solution *sol = (sch_solution*) malloc(sizeof(sch_solution));
  sol->num = sch->num;
  sch_solution_malloc(sol);
  /*
  info_sch_solution("sch_sjf",sol);

  sort_sch_problem_asc(sch,TBL_BURST);
  info_sch_problem("sch_sjf - sorted",sch);

  int i = 0, cycle = 0, wait_time = 0;
  while(i < sch->num) {
    if (sch->table[i][TBL_ARRIVAL] <= cycle) {
      // start next process
      if (SCH_VERBOSE)
        printf("(  %d) Running job %d, arrived at %d, with burst time %d.\n", cycle, sch->table[i][TBL_ID], sch->table[i][TBL_ARRIVAL], sch->table[i][TBL_BURST]);
      
      sol->order[i] = sch->table[i][TBL_ID];
      cycle += sch->table[i][TBL_BURST];
      i++;

      if (i < sch->num) {
        // add wait time for next process
        if (sch->table[i][TBL_ARRIVAL] < cycle)
          wait_time += cycle - sch->table[i][TBL_ARRIVAL];
      }
    } else {
      // no process to start
      if(SCH_VERBOSE)
        printf("(  %d) No job ready.\n", cycle);
      cycle++;
    }
  }
  sol->wait_average = (float)wait_time / sch->num;
  if(SCH_DEBUG)
    printf("wait_time: %d, avg: %f\n", wait_time, (float)wait_time / sch->num);

  info_sch_solution("sch_sjf - after run",sol);
  */
  return sol;
}

/**
   Prints the Scheduling Problem in a Tabular manner.

   @param context a string representing the context from where the table is printed.
   @param sch the address of the scheduling problem
 */
void info_sch_problem(char *context, sch_problem *sch) {
  if(!SCH_DEBUG)
    return;
  printf("%s: scheduling problem:\n", context);
  printf("| ID | ARRIVAL | BURST |\n");
  printf("------------------------\n");
  if (sch->num > 0) {
    for (int i = 0; i < sch->num; i++) {
      printf("| %i  |    %i    |   %i   |\n",
        sch->table[i][TBL_ID],
        sch->table[i][TBL_ARRIVAL],
        sch->table[i][TBL_BURST]);
    }
  }
  printf("\n");
}

void info_sch_solution(char *context, sch_solution *sol) {
  //if(!SCH_DEBUG)
    return;
  printf("%s: %p contains:\n", context, sol);
  printf("solution: %i entries\n",sol->num);
  printf("order: ");
  if (sol->num > 0) {
    for (int i = 0; i < sol->num; i++) {
      printf("%i ",sol->order[i]);
    }
    printf("\n");
  }
  printf("avg. wait: %f\n\n", sol->wait_average);
}

/**
   Sorts the scheduling problem based on the column passed in sort_by.
   The table is sorted in ascending, starting from the lowest value first. 

   @param sch the address of the scheduling problem to be sorted
   @param sort_by is the id of the column that is used for sorting.
 */
void sort_sch_problem_asc(sch_problem *sch, int sort_by) {
  if(sch->num > 0) {
    for(int i = 0; i < sch->num; i++) {
      for(int j = i; j < sch->num; j++) {
        if(sch->table[i][sort_by] > sch->table[j][sort_by]) {
          sch_table_swap(sch,i,j);
        }
      }
    }
  }
}

/**
   Swaps two table rows of a scheduling problem with eachother.

   @param sch the address of the scheduling problem
   @param i is the id of the first row to be swapped with the second row.
   @param j is the id of the second row to be swapped with the first row.
 */
void sch_table_swap(sch_problem *sch, int i, int j) {
  int *temp_job = sch->table[j];
  sch->table[j] = sch->table[i];
  sch->table[i] = temp_job;
}

/**
   Gets the number of jobs currently waiting for their resources.
   This function returns 0 if no jobs are currently waiting. Otherwise it will
   return 1 for each process currently waiting. (So if 3 jobs were waiting, this function
   would return 3).

   @param cycle is the current cycle number. This value is compared to the processes arrival time.
   @param next_job_id is the ID of the next job to be executed. All jobs before this ID will be ignored.
   @param sch the address of the scheduling problem

   @return the number of jobs currently waiting for their turn.
 */
int get_no_of_jobs_waiting(int cycle, int next_job_id, sch_problem *sch) {
  int jobs_waiting = 0;
  for(int i = next_job_id; i < sch->num; i++) {
    if (sch->table[i][TBL_ARRIVAL] <= cycle) {
      jobs_waiting++;
    }
  }
  return jobs_waiting;
}

void sch_solution_malloc(sch_solution *sol) {
  sol->order = (int*) malloc(0 * sizeof(int));
  sol->wait_average = 0.0;
}
