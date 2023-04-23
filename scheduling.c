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

// TODO: define constants if needed

void info_sch_problem(char *context, sch_problem *sch);
void info_sch_solution(char *context, sch_solution *sol);
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
  info_sch_problem("sch_table_malloc",sch);
}

/**
  Free the memory occupied by the table of the scheduling
  problem at sch.

  @param sch the address of the scheduling problem
*/
void sch_table_free(sch_problem *sch) {
  info_sch_problem("sch_table_free",sch);
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
  // TODO
  sch_solution *sol = (sch_solution*) malloc(sizeof(sch_solution));
  sch_solution_malloc(sol);
  info_sch_solution("sch_fcfs",sol);
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
  printf("%s: %p contains:\n", context, sch);
  printf("table: %i entries\n",sch->num);
  printf("i | ID | ARRIVAL | BURST\n");
  printf("------------------------\n");
  if (sch->num > 0) {
    for (int i = 0; i < sch->num; i++) {
      printf("%i | %i  |    %i    |  %i   \n",
        i,
        sch->table[i][0],
        sch->table[i][1],
        sch->table[i][2]);
    }
  }
  printf("\n");
}

void info_sch_solution(char *context, sch_solution *sol) {
  printf("%s: %p contains:\n", context, sol);
  printf("solution: %i entries\n",sol->num);
  printf("order\n");
  printf("------------------------\n");
  if (sol->num > 0) {
    for (int i = 0; i < sol->num; i++) {
      printf("%i ,",sol->order[i]);
    }
    printf("\n");
  }
  printf("avg. wait: %f\n\n", sol->wait_average);
}

void sch_solution_malloc(sch_solution *sol) {
  sol->num = 0;
  sol->order = (int*) malloc(0 * sizeof(int));
  sol->wait_average = 0.0;
}
