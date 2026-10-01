#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMPLOYEES 100

typedef struct {
    int   id;
    char  name[50];
    char  department[50];
    float basicSalary;
    float housingAllowance;
    float transportAllowance;
} Employee;

Employee employees[MAX_EMPLOYEES];
int      employeeCount = 0;

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void readString(const char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}

void pauseScreen(void) {
    printf("\nPress Enter to continue...");
    getchar();
}

float calculateTotalSalary(Employee e) {
    return e.basicSalary + e.housingAllowance + e.transportAllowance;
}

void addEmployee(void) {
    if (employeeCount >= MAX_EMPLOYEES) {
        printf("Employee list is full.\n");
        return;
    }

    Employee e;

    printf("Enter Employee ID: ");
    if (scanf("%d", &e.id) != 1) {
        clearInputBuffer();
        printf("Invalid ID.\n");
        return;
    }
    clearInputBuffer();

    readString("Enter Name: ", e.name, sizeof(e.name));
    if (strlen(e.name) == 0) {
        printf("Name cannot be empty.\n");
        return;
    }

    readString("Enter Department: ", e.department, sizeof(e.department));

    printf("Enter Basic Salary: ");
    if (scanf("%f", &e.basicSalary) != 1) {
        clearInputBuffer();
        printf("Invalid salary.\n");
        return;
    }
    clearInputBuffer();
    if (e.basicSalary < 0) {
        printf("Salary cannot be negative.\n");
        return;
    }

    printf("Enter Housing Allowance: ");
    if (scanf("%f", &e.housingAllowance) != 1) {
        clearInputBuffer();
        printf("Invalid housing allowance.\n");
        return;
    }
    clearInputBuffer();
    if (e.housingAllowance < 0) {
        printf("Housing allowance cannot be negative.\n");
        return;
    }

    printf("Enter Transport Allowance: ");
    if (scanf("%f", &e.transportAllowance) != 1) {
        clearInputBuffer();
        printf("Invalid transport allowance.\n");
        return;
    }
    clearInputBuffer();
    if (e.transportAllowance < 0) {
        printf("Transport allowance cannot be negative.\n");
        return;
    }

    employees[employeeCount] = e;
    employeeCount++;
    printf("Employee added successfully.\n");
}

void displayEmployees(void) {
    if (employeeCount == 0) {
        printf("No employees to display.\n");
        return;
    }

    printf("\n%-5s %-20s %-15s %-12s %-12s %-12s %-12s\n",
           "ID", "Name", "Department", "Basic", "Housing",
           "Transport", "Total");
    printf("--------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < employeeCount; i++) {
        printf("%-5d %-20s %-15s %-12.2f %-12.2f %-12.2f %-12.2f\n",
               employees[i].id,
               employees[i].name,
               employees[i].department,
               employees[i].basicSalary,
               employees[i].housingAllowance,
               employees[i].transportAllowance,
               calculateTotalSalary(employees[i]));
    }
}

void searchEmployee(void) {
    if (employeeCount == 0) {
        printf("No employees to search.\n");
        return;
    }

    char query[50];
    readString("Enter employee name or ID to search: ", query, sizeof(query));

    int found = 0;
    int searchId = atoi(query);

    for (int i = 0; i < employeeCount; i++) {
        if (strcmp(employees[i].name, query) == 0 ||
            employees[i].id == searchId) {
            printf("\nFound Employee:\n");
            printf("  ID                 : %d\n", employees[i].id);
            printf("  Name               : %s\n", employees[i].name);
            printf("  Department         : %s\n", employees[i].department);
            printf("  Basic Salary       : N$%.2f\n", employees[i].basicSalary);
            printf("  Housing Allowance  : N$%.2f\n", employees[i].housingAllowance);
            printf("  Transport Allowance: N$%.2f\n", employees[i].transportAllowance);
            printf("  Total Salary       : N$%.2f\n", calculateTotalSalary(employees[i]));
            found = 1;
        }
    }

    if (!found) {
        printf("No employee found matching '%s'.\n", query);
    }
}

void calculateSalaryInfo(void) {
    if (employeeCount == 0) {
        printf("No employees available.\n");
        return;
    }

    int id;
    printf("Enter Employee ID to calculate salary: ");
    if (scanf("%d", &id) != 1) {
        clearInputBuffer();
        printf("Invalid ID.\n");
        return;
    }
    clearInputBuffer();

    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == id) {
            printf("\n========================================\n");
            printf("  SALARY BREAKDOWN\n");
            printf("========================================\n");
            printf("  Employee : %s (ID %d)\n",
                   employees[i].name, employees[i].id);
            printf("  Dept     : %s\n", employees[i].department);
            printf("----------------------------------------\n");
            printf("  Basic Salary      : N$%10.2f\n", employees[i].basicSalary);
            printf("  Housing Allowance : N$%10.2f\n", employees[i].housingAllowance);
            printf("  Transport Allow.  : N$%10.2f\n", employees[i].transportAllowance);
            printf("----------------------------------------\n");
            printf("  TOTAL SALARY      : N$%10.2f\n",
                   calculateTotalSalary(employees[i]));
            printf("========================================\n");
            return;
        }
    }

    printf("Employee with ID %d not found.\n", id);
}

void employeeMenu(void) {
    int choice;

    do {
        printf("\n===== EMPLOYEE MANAGEMENT =====\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Calculate Salary Information\n");
        printf("5. Back to Main Menu\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            if (feof(stdin)) {
                printf("\nEnd of input reached. Exiting.\n");
                return;
            }
            clearInputBuffer();
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: addEmployee();          pauseScreen(); break;
            case 2: displayEmployees();     pauseScreen(); break;
            case 3: searchEmployee();       pauseScreen(); break;
            case 4: calculateSalaryInfo();  pauseScreen(); break;
            case 5: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);
}

int main(void) {
    printf("Welcome to the Municipal Financial Management System.\n");
    employeeMenu();
    printf("\nGoodbye!\n");
    return 0;
}
