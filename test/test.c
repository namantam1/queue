#include "minunit.h"
#include "../queue.h"

typedef struct
{
    char *name;
    int salary;
} employee;

queue_ptr employees = NULL;
char *USERS[] = {"Naman", "John", "Kevin", "Kavita"};
int SALARIES[] = {20000, 40000, 18000, 25000};
int LEN = sizeof(USERS) / sizeof(char *);

void print_employee(void *data)
{
    if (data == NULL)
    {
        printf("Data is NULL!\n");
        return;
    }

    employee *emp = data;
    printf("{name: %s, salary: %d}", emp->name, emp->salary);
}

void print_employees_queue()
{
    print_queue(employees, print_employee);
}

MU_TEST(test_initial_length)
{
    employees = create_queue(sizeof(employee), NULL);
    print_employees_queue();
    mu_check(length(employees) == 0);
}

MU_TEST(test_add)
{
    print_employees_queue();
    printf("Adding %d users...\n", LEN);
    int initial_length = length(employees);

    for (int i = 0; i < LEN; i++)
    {
        add(employees, &(employee){
                            .name = USERS[i],
                            .salary = SALARIES[i]});
        printf("length: %d\n", length(employees));
        mu_assert(length(employees) == (initial_length++) + 1, "length did not increased");
    }
    print_employees_queue();
}

MU_TEST(test_peek)
{
    employee *emp = peek(employees);
    print_employee(emp);
    printf(" <-- Peek data\n");
    mu_assert(emp != NULL, "Data is NULL from the peek method");
    mu_assert_string_eq(USERS[0], (*emp).name);
    mu_assert_int_eq(SALARIES[0], (*emp).salary);
}

MU_TEST(test_dequeue)
{
    for (int i = 0; i < LEN; i++)
    {
        employee emp;
        mu_assert(dequeue(employees, &emp), "Dequeue returned false");
        print_employee(&emp);
        printf(" <-- dequeue data\n");
        mu_assert_int_eq(SALARIES[i], emp.salary);
        mu_assert_string_eq(USERS[i], emp.name);
    }
    
    print_employees_queue();
    mu_assert_int_eq(0, length(employees));
    mu_assert(!dequeue(employees, NULL), "Returning true for empty queue");
}

MU_TEST(test_empty)
{
    print_employees_queue();
    mu_assert(is_empty(employees), "Queue not found to be empty");
}

MU_TEST(test_destroy)
{
    destroy_queue(&employees);
    print_employees_queue();
    mu_assert(employees==NULL, "Employees pointer not set to null");
}

MU_TEST_SUITE(test_suite)
{
    MU_RUN_TEST(test_initial_length);
    MU_RUN_TEST(test_add);
    MU_RUN_TEST(test_peek);
    MU_RUN_TEST(test_dequeue);
    MU_RUN_TEST(test_empty);
    MU_RUN_TEST(test_destroy);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
