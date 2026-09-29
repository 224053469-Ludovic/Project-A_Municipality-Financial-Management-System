#include <stdio.h>
int main(void) {
    int choice;

    do {
        printf("\n===== EMPLOYEE MANAGEMENT =====\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Calculate Salary Information\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: printf("Add Employee (not yet implemented)\n"); break;
            case 2: printf("Display Employees (not yet implemented)\n"); break;
            case 3: printf("Search Employee (not yet implemented)\n"); break;
            case 4: printf("Calculate Salary (not yet implemented)\n"); break;
            case 5: printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);

    return 0;
}