#define ID      0
#define ARRIVAL 1
#define BURST   2

/*
  Example:
  num: 3
  **table:
  -------------------------
  | ID  | ARRIVAL | BURST |
  -------------------------
  |  1  |   2     |  5    |
  |  2  |   0     |  6    |
  |  3  |   5     |  3    |
  -------------------------
*/
typedef struct {
  int num;
  int **table;
} sch_problem;

/*
  Example 1:
  Consider First Come First Served and table in previous comment.
  num: 3
  *order: [2, 1, 3]
  wait_average: 3.333333

  Example 2:
  Consider Shortest Job First and table in previous comment.
  num: 3
  *order: [2, 3, 1]
  wait_average: 2.666667

  Example 3:
  Consider Shortest Job First and the following table of jobs:
  -------------------------
  | ID  | ARRIVAL | BURST |
  -------------------------
  |  1  |   2     |  2    |
  |  2  |   5     |  4    |
  |  3  |   5     |  3    |
  |  4  |   5     |  4    |
  -------------------------
  num: 4
  *order: [1, 3, 2, 4]
  wait_average: 2.500000

  Example 4:
  Consider FCFS or SJF, and the following table of jobs:
  -------------------------
  | ID  | ARRIVAL | BURST |
  -------------------------
  -------------------------
  num: 0
  *order: []
  wait_average: 0.000000
*/
typedef struct {
  int num;
  int *order;
  float wait_average;
} sch_solution;

void sch_table_malloc(sch_problem *sch);
void sch_table_free  (sch_problem *sch);
sch_problem  * sch_get_scheduling_problem_instance();
sch_solution * sch_fcfs(sch_problem *sch);
sch_solution * sch_sjf (sch_problem *sch);
