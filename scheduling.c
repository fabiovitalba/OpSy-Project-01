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
void sort_sch_problem_arrival_time(sch_problem *sch);
void sch_table_swap(sch_problem *sch, int i, int j);
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
  info_sch_solution("sch_fcfs",sol);

  sort_sch_problem_arrival_time(sch);
  info_sch_problem("sch_fcfs - sorted",sch);

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
  // TODO
  sch_solution *sol = (sch_solution*) malloc(sizeof(sch_solution));
  sch_solution_malloc(sol);
  info_sch_solution("sch_sjf",sol);
  return sol;
}

void info_sch_problem(char *context, sch_problem *sch) {
  if(!SCH_DEBUG)
    return;
  printf("%s: %p contains:\n", context, sch);
  printf("table: %i entries\n",sch->num);
  printf("i | ID | ARRIVAL | BURST\n");
  printf("------------------------\n");
  if (sch->num > 0) {
    for (int i = 0; i < sch->num; i++) {
      printf("%i | %i  |    %i    |  %i   \n",
        i,
        sch->table[i][TBL_ID],
        sch->table[i][TBL_ARRIVAL],
        sch->table[i][TBL_BURST]);
    }
  }
  printf("\n");
}

void info_sch_solution(char *context, sch_solution *sol) {
  if(!SCH_DEBUG)
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

void sort_sch_problem_arrival_time(sch_problem *sch) {
  if(sch->num > 0) {
    for(int i = 0; i < sch->num; i++) {
      for(int j = i; j < sch->num; j++) {
        if(sch->table[i][TBL_ARRIVAL] > sch->table[j][TBL_ARRIVAL]) {
          sch_table_swap(sch,i,j);
        }
      }
    }
  }
}

void sch_table_swap(sch_problem *sch, int i, int j) {
  int *temp_job = sch->table[j];
  sch->table[j] = sch->table[i];
  sch->table[i] = temp_job;
}

void sch_solution_malloc(sch_solution *sol) {
  sol->order = (int*) malloc(0 * sizeof(int));
  sol->wait_average = 0.0;
}
