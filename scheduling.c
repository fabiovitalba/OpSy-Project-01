/**
  @brief Implementation of non pre-emptive algorithms for process
         scheduling.

         Firt Come First Served: FCFS
         Shortest-Job First: SJF

  Scheduling on one CPU.
*/

#include "scheduling.h"

// TODO: include libraries if needed

// TODO: define constants if needed

// TODO: Declare helper functions, if any

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
  // TODO
}

/**
  Free the memory occupied by the table of the scheduling
  problem at sch.

  @param sch the address of the scheduling problem
*/
void sch_table_free(sch_problem *sch) {
  // TODO
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
}

// TODO: define helper functions, if any
