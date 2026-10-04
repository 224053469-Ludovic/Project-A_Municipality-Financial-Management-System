#include <stdio.h>
#include <string.h>
#include "employees.h"

void addEmployee(Employee employees[], int *count)
{
    if (*count >= MAX_EMPLOYEES)
    {
        printf("Employee limit reached.\n");
        return;
    }

    printf("\nEnter Employee ID: ");
    scanf("%d", &employees[*count].employeeID);

    getchar();

    printf("Enter Employee Name: ");
    fgets(employees[*count].name,
          sizeof(employees[*count].name), stdin);

    employees[*count].name[
        strcspn(employees[*count].name, "\n")] = '\0';

    printf("Enter Department: ");
    fgets(employees[*count].department,
          sizeof(employees[*count].department), stdin);

    employees[*count].department[
        strcspn(employees[*count].department, "\n")] = '\0';

    printf("Enter Basic Salary: ");
    scanf("%f", &employees[*count].basicSalary);

    printf("Enter Housing Allowance: ");
    scanf("%f", &employees[*count].housingAllowance);

    printf("Enter Transport Allowance: ");
    scanf("%f", &employees[*count].transportAllowance);

    (*count)++;

    printf("\nEmployee added successfully!\n");
}

void displayEmployees(Employee employees[], int count)
{
    int i;

    if (count == 0)
    {
        printf("\nNo employees registered.\n");
        return;
    }

    printf("\n========== EMPLOYEE LIST ==========\n");

    for (i = 0; i < count; i++)
    {
        printf("\nEmployee ID: %d\n",
               employees[i].employeeID);

        printf("Name: %s\n",
               employees[i].name);

        printf("Department: %s\n",
               employees[i].department);

        printf("Basic Salary: N$%.2f\n",
               employees[i].basicSalary);

        printf("Housing Allowance: N$%.2f\n",
               employees[i].housingAllowance);

        printf("Transport Allowance: N$%.2f\n",
               employees[i].transportAllowance);

        printf("Total Salary: N$%.2f\n",
               calculateSalary(employees[i]));
    }
}

void searchEmployee(Employee employees[], int count)
{
    int id;
    int i;
    int found = 0;

    printf("\nEnter Employee ID to search: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++)
    {
        if (employees[i].employeeID == id)
        {
            printf("\nEmployee Found!\n");

            printf("ID: %d\n",
                   employees[i].employeeID);

            printf("Name: %s\n",
                   employees[i].name);

            printf("Department: %s\n",
                   employees[i].department);

            printf("Basic Salary: N$%.2f\n",
                   employees[i].basicSalary);

            printf("Total Salary: N$%.2f\n",
                   calculateSalary(employees[i]));

            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("\nEmployee not found.\n");
    }
}

float calculateSalary(Employee employee)
{
    return employee.basicSalary
           + employee.housingAllowance
           + employee.transportAllowance;
}void displayEmployeeMenu(void)
{
    printf("\n===== EMPLOYEE MANAGEMENT =====\n");
    printf("1. Add Employee\n");
    printf("2. Display Employees\n");
    printf("3. Search Employee\n");
    printf("0. Back\n");
    printf("Enter choice: ");
}

