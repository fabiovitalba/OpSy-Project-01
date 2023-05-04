#include "scheduling.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define VERBOSE 1

#define W_ALGO  3
#define W_TEST  5
#define W_FAIL  7
#define W_PASS  1

#define GREEN  "\033[0;32m"
#define RED    "\033[0;31m"
#define CYAN   "\033[0;36m"
#define NORMAL "\033[0m"


void test0();
void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();
void test9();
void test10();
void test11();

void manualTest();


int main() {
  test0();
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  test8();
  test9();
  test10();
  test11();

  //manualTest();
}

/*
 *
 *                 HELPERS
 *
 */

void print_message(char *message, int ast) {
  if (ast == W_FAIL) {
      printf(RED);
  } else if (ast == W_PASS) {
    printf(GREEN);
  } else {
    printf(CYAN);    
  }
  for (int i = 0; i < ast; i++) {
    printf("*");
  }
  printf(" %s\n", message);
  printf(NORMAL);
}

void print_solution(sch_solution sol) {
  printf("Order of scheduling: ");  
  for (int i = 0; i < sol.num; i++) {
    printf("%d ", sol.order[i]);
  }
  printf("\nAverage wait %f\n", sol.wait_average);
}

int check_order(int a[], int b[], int num) {
  for (int i = 0; i < num; i++) {
    if (a[i] != b[i]) {
      return 0;
    }
  }
  return 1;
}

int solution_check_equals(sch_solution a, sch_solution b) {
  if (a.num != b.num ||
      !check_order(a.order, b.order, a.num) ||
      //a.wait_average != b.wait_average) {
      (fabsf(a.wait_average - b.wait_average) > 0.00001)) {
    print_message("FAIL", W_FAIL);
    return 0;
  } else {
    print_message("pass", W_PASS);
    return 1;
  }
}

void check_fcfs(sch_problem *sch, sch_solution *expected_fcfs) {
  print_message("fcfs", W_ALGO);
  sch_solution * sol_fcfs = sch_fcfs(sch);
  if (VERBOSE) print_solution(*sol_fcfs);
  solution_check_equals(*sol_fcfs, *expected_fcfs);
  free(sol_fcfs->order);
  free(sol_fcfs);
  free(expected_fcfs->order);
  free(expected_fcfs);  
}

void check_sjf(sch_problem *sch, sch_solution *expected_sjf) {
  print_message("sjf", W_ALGO);
  sch_solution * sol_sjf = sch_sjf(sch);
  if (VERBOSE) print_solution(*sol_sjf);
  solution_check_equals(*sol_sjf, *expected_sjf);
  free(sol_sjf->order);
  free(sol_sjf);
  free(expected_sjf->order);
  free(expected_sjf);  
}


/*
 *
 *                      TESTS
 *
 */

void test0() {
  print_message("Test 0", W_TEST);
  // scheduling problem instance  
  sch_problem *sch = (sch_problem*) malloc(sizeof(sch_problem));
  sch->num = 0;
  sch_table_malloc(sch);
  // expected fcfs solution instance
  sch_solution *expected_fcfs = (sch_solution*) malloc(sizeof(sch_solution));
  expected_fcfs->num = 0;
  expected_fcfs->order = (int*) malloc(0 * sizeof(int));
  expected_fcfs->wait_average = 0.0;
  // expected sjf solution instance
  sch_solution *expected_sjf = (sch_solution*) malloc(sizeof(sch_solution));
  expected_sjf->num = 0;
  expected_sjf->order = (int*) malloc(0 * sizeof(int));
  expected_sjf->wait_average = 0.0;

  // check (and free memory solutions)
  check_fcfs(sch, expected_fcfs);
  check_sjf(sch, expected_sjf);

  // free
  sch_table_free(sch);
  free(sch);
}

void test1() {
  print_message("Test 1", W_TEST);
  // scheduling problem instance  
  sch_problem *sch = (sch_problem*) malloc(sizeof(sch_problem));
  sch->num = 2;
  sch_table_malloc(sch);
  sch->table[0][ID] = 1;  
  sch->table[0][ARRIVAL] = 0;
  sch->table[0][BURST] = 3;
  sch->table[1][ID] = 2;
  sch->table[1][ARRIVAL] = 0;
  sch->table[1][BURST] = 2;
  // expected fcfs solution instance
  sch_solution *expected_fcfs = (sch_solution*) malloc(sizeof(sch_solution));
  expected_fcfs->num = 2;
  expected_fcfs->order = (int*) malloc(2 * sizeof(int));
  expected_fcfs->order[0] = 1;
  expected_fcfs->order[1] = 2;
  expected_fcfs->wait_average = 1.5;
  // expected sjf solution instance
  sch_solution *expected_sjf = (sch_solution*) malloc(sizeof(sch_solution));
  expected_sjf->num = 2;
  expected_sjf->order = (int*) malloc(2 * sizeof(int));
  expected_sjf->order[0] = 2;
  expected_sjf->order[1] = 1;
  expected_sjf->wait_average = 1.0;

  // check (and free memory solutions)
  check_fcfs(sch, expected_fcfs);
  check_sjf(sch, expected_sjf);

  // free
  sch_table_free(sch);
  free(sch);
}

void test2() {
  print_message("Test 2", W_TEST);
  // scheduling problem instance  
  sch_problem *sch = (sch_problem*) malloc(sizeof(sch_problem));
  sch->num = 3;
  sch_table_malloc(sch);
  sch->table[0][ID] = 1;
  sch->table[0][ARRIVAL] = 0;
  sch->table[0][BURST] = 3;
  sch->table[1][ID] = 2;
  sch->table[1][ARRIVAL] = 2;
  sch->table[1][BURST] = 3;
  sch->table[2][ID] = 3;
  sch->table[2][ARRIVAL] = 3;
  sch->table[2][BURST] = 1;
  // expected fcfs solution instance
  sch_solution *expected_fcfs = (sch_solution*) malloc(sizeof(sch_solution));
  expected_fcfs->num = 3;
  expected_fcfs->order = (int*) malloc(3 * sizeof(int));
  expected_fcfs->order[0] = 1;
  expected_fcfs->order[1] = 2;
  expected_fcfs->order[2] = 3;
  expected_fcfs->wait_average = 4.0 / 3;
  // expected sjf solution instance
  sch_solution *expected_sjf = (sch_solution*) malloc(sizeof(sch_solution));
  expected_sjf->num = 3;
  expected_sjf->order = (int*) malloc(3 * sizeof(int));
  expected_sjf->order[0] = 1;
  expected_sjf->order[1] = 3;
  expected_sjf->order[2] = 2;
  expected_sjf->wait_average = 2.0 / 3;

  // check (and free memory solutions)
  check_fcfs(sch, expected_fcfs);
  check_sjf(sch, expected_sjf);

  // free
  sch_table_free(sch);
  free(sch);
}

void test3() {
  print_message("Test 3", W_TEST);
  // scheduling problem instance  
  sch_problem *sch = (sch_problem*) malloc(sizeof(sch_problem));
  sch->num = 4;
  sch_table_malloc(sch);
  sch->table[0][ID] = 1;
  sch->table[0][ARRIVAL] = 2;
  sch->table[0][BURST] = 2;
  sch->table[1][ID] = 2;
  sch->table[1][ARRIVAL] = 3;
  sch->table[1][BURST] = 1;
  sch->table[2][ID] = 3;
  sch->table[2][ARRIVAL] = 1;
  sch->table[2][BURST] = 4;
  sch->table[3][ID] = 4;
  sch->table[3][ARRIVAL] = 9;
  sch->table[3][BURST] = 2;
  // expected fcfs solution instance
  sch_solution *expected_fcfs = (sch_solution*) malloc(sizeof(sch_solution));
  expected_fcfs->num = 4;
  expected_fcfs->order = (int*) malloc(4 * sizeof(int));
  expected_fcfs->order[0] = 3;
  expected_fcfs->order[1] = 1;
  expected_fcfs->order[2] = 2; 
  expected_fcfs->order[3] = 4; 
  expected_fcfs->wait_average = 1.75;
  // expected sjf solution instance
  sch_solution *expected_sjf = (sch_solution*) malloc(sizeof(sch_solution));
  expected_sjf->num = 4;
  expected_sjf->order = (int*) malloc(4 * sizeof(int));
  expected_sjf->order[0] = 3;
  expected_sjf->order[1] = 2;
  expected_sjf->order[2] = 1;
  expected_sjf->order[3] = 4;  
  expected_sjf->wait_average = 1.5;

  // check (and free memory solutions)
  check_fcfs(sch, expected_fcfs);
  check_sjf(sch, expected_sjf);

  // free
  sch_table_free(sch);
  free(sch);
}

void test4() {
  print_message("Test 4", W_TEST);
  // scheduling problem instance  
  sch_problem *sch = (sch_problem*) malloc(sizeof(sch_problem));
  sch->num = 3;
  sch_table_malloc(sch);
  sch->table[0][ID] = 7;
  sch->table[0][ARRIVAL] = 0;
  sch->table[0][BURST] = 1;
  sch->table[1][ID] = 5;
  sch->table[1][ARRIVAL] = 2;
  sch->table[1][BURST] = 1;
  sch->table[2][ID] = 3;
  sch->table[2][ARRIVAL] = 3;
  sch->table[2][BURST] = 1;
  // expected fcfs solution instance
  sch_solution *expected_fcfs = (sch_solution*) malloc(sizeof(sch_solution));
  expected_fcfs->num = 3;
  expected_fcfs->order = (int*) malloc(3 * sizeof(int));
  expected_fcfs->order[0] = 7;
  expected_fcfs->order[1] = 5;
  expected_fcfs->order[2] = 3;
  expected_fcfs->wait_average = 0.0;
  // expected sjf solution instance
  sch_solution *expected_sjf = (sch_solution*) malloc(sizeof(sch_solution));
  expected_sjf->num = 3;
  expected_sjf->order = (int*) malloc(3 * sizeof(int));
  expected_sjf->order[0] = 7;
  expected_sjf->order[1] = 5;
  expected_sjf->order[2] = 3;
  expected_sjf->wait_average = 0.0;

  // check (and free memory solutions)
  check_fcfs(sch, expected_fcfs);
  check_sjf(sch, expected_sjf);

  // free
  sch_table_free(sch);
  free(sch);
}

void test5() {
  print_message("Test 5", W_TEST);
  // scheduling problem instance  
  sch_problem *sch = (sch_problem*) malloc(sizeof(sch_problem));
  sch->num = 5;
  sch_table_malloc(sch);
  sch->table[0][ID] = 1;
  sch->table[0][ARRIVAL] = 2;
  sch->table[0][BURST] = 6;
  sch->table[1][ID] = 2;
  sch->table[1][ARRIVAL] = 5;
  sch->table[1][BURST] = 2;
  sch->table[2][ID] = 3;
  sch->table[2][ARRIVAL] = 1;
  sch->table[2][BURST] = 8;
  sch->table[3][ID] = 4;
  sch->table[3][ARRIVAL] = 0;
  sch->table[3][BURST] = 3;
  sch->table[4][ID] = 5;
  sch->table[4][ARRIVAL] = 4;
  sch->table[4][BURST] = 4;
  // expected fcfs solution instance
  sch_solution *expected_fcfs = (sch_solution*) malloc(sizeof(sch_solution));
  expected_fcfs->num = 5;
  expected_fcfs->order = (int*) malloc(5 * sizeof(int));
  expected_fcfs->order[0] = 4;
  expected_fcfs->order[1] = 3;
  expected_fcfs->order[2] = 1;
  expected_fcfs->order[3] = 5;
  expected_fcfs->order[4] = 2;
  expected_fcfs->wait_average = 8.0;
  // expected sjf solution instance
  sch_solution *expected_sjf = (sch_solution*) malloc(sizeof(sch_solution));
  expected_sjf->num = 5;
  expected_sjf->order = (int*) malloc(5 * sizeof(int));
  expected_sjf->order[0] = 4;
  expected_sjf->order[1] = 1;
  expected_sjf->order[2] = 2;
  expected_sjf->order[3] = 5;
  expected_sjf->order[4] = 3;
  expected_sjf->wait_average = 5.2;

  // check (and free memory solutions)
  check_fcfs(sch, expected_fcfs);
  check_sjf(sch, expected_sjf);

  // free
  sch_table_free(sch);
  free(sch);
}

void test6() {
  print_message("Test 6", W_TEST);
  // scheduling problem instance  
  sch_problem *sch = (sch_problem*) malloc(sizeof(sch_problem));
  sch->num = 4;
  sch_table_malloc(sch);
  sch->table[0][ID] = 1;
  sch->table[0][ARRIVAL] = 0;
  sch->table[0][BURST] = 6;
  sch->table[1][ID] = 2;
  sch->table[1][ARRIVAL] = 0;
  sch->table[1][BURST] = 8;
  sch->table[2][ID] = 3;
  sch->table[2][ARRIVAL] = 0;
  sch->table[2][BURST] = 7;
  sch->table[3][ID] = 4;
  sch->table[3][ARRIVAL] = 0;
  sch->table[3][BURST] = 3;
  // expected fcfs solution instance
  sch_solution *expected_fcfs = (sch_solution*) malloc(sizeof(sch_solution));
  expected_fcfs->num = 4;
  expected_fcfs->order = (int*) malloc(4 * sizeof(int));
  expected_fcfs->order[0] = 1;
  expected_fcfs->order[1] = 2;
  expected_fcfs->order[2] = 3; 
  expected_fcfs->order[3] = 4; 
  expected_fcfs->wait_average = 10.25;
  // expected sjf solution instance
  sch_solution *expected_sjf = (sch_solution*) malloc(sizeof(sch_solution));
  expected_sjf->num = 4;
  expected_sjf->order = (int*) malloc(4 * sizeof(int));
  expected_sjf->order[0] = 4;
  expected_sjf->order[1] = 1;
  expected_sjf->order[2] = 3;
  expected_sjf->order[3] = 2;  
  expected_sjf->wait_average = 7.0;

  // check (and free memory solutions)
  check_fcfs(sch, expected_fcfs);
  check_sjf(sch, expected_sjf);

  // free
  sch_table_free(sch);
  free(sch);
}

void test7() {
  print_message("Test 7", W_TEST);
  // scheduling problem instance  
  sch_problem *sch = (sch_problem*) malloc(sizeof(sch_problem));
  sch->num = 3;
  sch_table_malloc(sch);
  sch->table[0][ID] = 1;
  sch->table[0][ARRIVAL] = 9;
  sch->table[0][BURST] = 7;
  sch->table[1][ID] = 2;
  sch->table[1][ARRIVAL] = 9;
  sch->table[1][BURST] = 7;
  sch->table[2][ID] = 3;
  sch->table[2][ARRIVAL] = 6;
  sch->table[2][BURST] = 0;
  // expected fcfs solution instance
  sch_solution *expected_fcfs = (sch_solution*) malloc(sizeof(sch_solution));
  expected_fcfs->num = 3;
  expected_fcfs->order = (int*) malloc(3 * sizeof(int));
  expected_fcfs->order[0] = 3;
  expected_fcfs->order[1] = 1;
  expected_fcfs->order[2] = 2;
  expected_fcfs->wait_average = 2.333333;
  // expected sjf solution instance
  sch_solution *expected_sjf = (sch_solution*) malloc(sizeof(sch_solution));
  expected_sjf->num = 3;
  expected_sjf->order = (int*) malloc(3 * sizeof(int));
  expected_sjf->order[0] = 3;
  expected_sjf->order[1] = 1;
  expected_sjf->order[2] = 2;
  expected_sjf->wait_average = 2.333333;

  // check (and free memory solutions)
  check_fcfs(sch, expected_fcfs);
  check_sjf(sch, expected_sjf);

  // free
  sch_table_free(sch);
  free(sch);
}

void test8() {
  print_message("Test 8", W_TEST);
  // scheduling problem instance  
  sch_problem *sch = (sch_problem*) malloc(sizeof(sch_problem));
  sch->num = 3;
  sch_table_malloc(sch);
  sch->table[0][ID] = 1;
  sch->table[0][ARRIVAL] = 9;
  sch->table[0][BURST] = 5;
  sch->table[1][ID] = 2;
  sch->table[1][ARRIVAL] = 7;
  sch->table[1][BURST] = 0;
  sch->table[2][ID] = 3;
  sch->table[2][ARRIVAL] = 5;
  sch->table[2][BURST] = 5;
  // expected fcfs solution instance
  sch_solution *expected_fcfs = (sch_solution*) malloc(sizeof(sch_solution));
  expected_fcfs->num = 3;
  expected_fcfs->order = (int*) malloc(3 * sizeof(int));
  expected_fcfs->order[0] = 3;
  expected_fcfs->order[1] = 2;
  expected_fcfs->order[2] = 1;
  expected_fcfs->wait_average = 1.66667;
  // expected sjf solution instance
  sch_solution *expected_sjf = (sch_solution*) malloc(sizeof(sch_solution));
  expected_sjf->num = 3;
  expected_sjf->order = (int*) malloc(3 * sizeof(int));
  expected_sjf->order[0] = 3;
  expected_sjf->order[1] = 2;
  expected_sjf->order[2] = 1;
  expected_sjf->wait_average = 1.66667;

  // check (and free memory solutions)
  check_fcfs(sch, expected_fcfs);
  check_sjf(sch, expected_sjf);

  // free
  sch_table_free(sch);
  free(sch);
}

void test9() {
  print_message("Test 9", W_TEST);
  // scheduling problem instance  
  sch_problem *sch = (sch_problem*) malloc(sizeof(sch_problem));
  sch->num = 3;
  sch_table_malloc(sch);
  sch->table[0][ID] = 1;
  sch->table[0][ARRIVAL] = 10;
  sch->table[0][BURST] = 2;
  sch->table[1][ID] = 2;
  sch->table[1][ARRIVAL] = 6;
  sch->table[1][BURST] = 2;
  sch->table[2][ID] = 3;
  sch->table[2][ARRIVAL] = 5;
  sch->table[2][BURST] = 6;
  // expected fcfs solution instance
  sch_solution *expected_fcfs = (sch_solution*) malloc(sizeof(sch_solution));
  expected_fcfs->num = 3;
  expected_fcfs->order = (int*) malloc(3 * sizeof(int));
  expected_fcfs->order[0] = 3;
  expected_fcfs->order[1] = 2;
  expected_fcfs->order[2] = 1;
  expected_fcfs->wait_average = 2.666667;
  // expected sjf solution instance
  sch_solution *expected_sjf = (sch_solution*) malloc(sizeof(sch_solution));
  expected_sjf->num = 3;
  expected_sjf->order = (int*) malloc(3 * sizeof(int));
  expected_sjf->order[0] = 3;
  expected_sjf->order[1] = 1;
  expected_sjf->order[2] = 2;
  expected_sjf->wait_average = 2.666667;

  // check (and free memory solutions)
  check_fcfs(sch, expected_fcfs);
  check_sjf(sch, expected_sjf);

  // free
  sch_table_free(sch);
  free(sch);
}

void test10() {
  print_message("Test 10", W_TEST);
  // scheduling problem instance  
  sch_problem *sch = (sch_problem*) malloc(sizeof(sch_problem));
  sch->num = 3;
  sch_table_malloc(sch);
  sch->table[0][ID] = 1;
  sch->table[0][ARRIVAL] = 8;
  sch->table[0][BURST] = 0;
  sch->table[1][ID] = 2;
  sch->table[1][ARRIVAL] = 7;
  sch->table[1][BURST] = 7;
  sch->table[2][ID] = 3;
  sch->table[2][ARRIVAL] = 8;
  sch->table[2][BURST] = 6;
  // expected fcfs solution instance
  sch_solution *expected_fcfs = (sch_solution*) malloc(sizeof(sch_solution));
  expected_fcfs->num = 3;
  expected_fcfs->order = (int*) malloc(3 * sizeof(int));
  expected_fcfs->order[0] = 2;
  expected_fcfs->order[1] = 1;
  expected_fcfs->order[2] = 3;
  expected_fcfs->wait_average = 4.333333;
  // expected sjf solution instance
  sch_solution *expected_sjf = (sch_solution*) malloc(sizeof(sch_solution));
  expected_sjf->num = 3;
  expected_sjf->order = (int*) malloc(3 * sizeof(int));
  expected_sjf->order[0] = 2;
  expected_sjf->order[1] = 1;
  expected_sjf->order[2] = 3;
  expected_sjf->wait_average = 4.333333;

  // check (and free memory solutions)
  check_fcfs(sch, expected_fcfs);
  check_sjf(sch, expected_sjf);

  // free
  sch_table_free(sch);
  free(sch);
}

void test11() {
  print_message("Test 11", W_TEST);
  // scheduling problem instance  
  sch_problem *sch = (sch_problem*) malloc(sizeof(sch_problem));
  sch->num = 2;
  sch_table_malloc(sch);
  sch->table[0][ID] = 1;
  sch->table[0][ARRIVAL] = 3;
  sch->table[0][BURST] = 0;
  sch->table[1][ID] = 2;
  sch->table[1][ARRIVAL] = 3;
  sch->table[1][BURST] = 1;
  // expected fcfs solution instance
  sch_solution *expected_fcfs = (sch_solution*) malloc(sizeof(sch_solution));
  expected_fcfs->num = 2;
  expected_fcfs->order = (int*) malloc(2 * sizeof(int));
  expected_fcfs->order[0] = 1;
  expected_fcfs->order[1] = 2;
  expected_fcfs->wait_average = 0.5;
  // expected sjf solution instance
  sch_solution *expected_sjf = (sch_solution*) malloc(sizeof(sch_solution));
  expected_sjf->num = 2;
  expected_sjf->order = (int*) malloc(2 * sizeof(int));
  expected_sjf->order[0] = 1;
  expected_sjf->order[1] = 2;
  expected_sjf->wait_average = 0.5;

  // check (and free memory solutions)
  check_fcfs(sch, expected_fcfs);
  check_sjf(sch, expected_sjf);

  // free
  sch_table_free(sch);
  free(sch);
}

void manualTest() {
  print_message("Manual test", W_ALGO);
  sch_problem *sch = sch_get_scheduling_problem_instance();
  sch_solution *sol_fcfs = sch_fcfs(sch);
  print_solution(*sol_fcfs);
  sch_solution *sol_sjf = sch_sjf(sch);
  print_solution(*sol_sjf);

  sch_table_free(sch);
  free(sch);
  free(sol_fcfs->order);
  free(sol_fcfs);  
  free(sol_sjf->order);
  free(sol_sjf);  
}
