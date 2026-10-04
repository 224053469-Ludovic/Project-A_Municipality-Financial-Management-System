#include <stdio.h>
#include "validation.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "asset.h"
/*#include "reports.h" outstanding */

void displayMenu(void);

int main(void)
{
    int choice;

    do
    {
        displayMenu();
        choice = readChoice(1, 6);

        switch (choice)
        {
        case 1:
            employeeMenu();
            break;

        case 2:
            budgetMenu();
            break;

        case 3:
            supplierMenu();
            break;

        case 4:
            assetMenu();
            break;

        case 5:
            /* TODO: replace with displayReports() when reports.h/.c are added */
            printf("\nReports module is not available yet.\n");
            break;

        case 6:
            printf("\nThank you for using MFMS. Goodbye!\n");
            break;
        }
    } while (choice != 6);
    return 0;
}

void displayMenu(void)
{
    printf("\n");
    printf("====================================\n");
    printf("Welcome to the MFMS Main Menu\n");
    printf("====================================\n");
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
}
