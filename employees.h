#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES 100

typedef struct {
    int   employeeID;
    char  name[50];
    char  department[50];
    float basicSalary;
    float housingAllowance;
    float transportAllowance;
} Employee;

void  addEmployee(Employee employees[], int *count);
void  displayEmployees(Employee employees[], int count);
void  searchEmployee(Employee employees[], int count);
float calculateSalary(Employee employee);
void  displayEmployeeMenu(void);

#endif