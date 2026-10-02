#include <stdio.h>
#include <string.h>
#include "budget.h"

char departments[MAX_DEPARTMENTS][50];
float budgets[MAX_DEPARTMENTS];
float expenditures[MAX_DEPARTMENTS];
int departmentCount = 0;

void budgetMenu(void)
{
    int choice;

    do
    {
        printf("\n===== BUDGET MANAGEMENT =====\n");
        printf("1. Enter Department Budgets\n");
        printf("2. Enter Expenditure\n");
        printf("3. Display Budget Information\n");
        printf("4. Show Departments Over Budget\n");
        printf("5. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
            case 1:
                enterBudgets();
                break;

            case 2:
                enterExpenditure();
                break;

            case 3:
                displayBudgets();
                break;

            case 4:
                showOverBudget();
                break;

            case 5:
                printf("Returning to Main Menu...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 5);
}

void enterBudgets(void)
{
    int i;

    printf("\n===== ENTER DEPARTMENT BUDGETS =====\n");

    printf("Enter number of departments (1-%d): ", MAX_DEPARTMENTS);
    scanf("%d", &departmentCount);
    getchar();

    if (departmentCount < 1 || departmentCount > MAX_DEPARTMENTS)
    {
        printf("Invalid number of departments.\n");
        departmentCount = 0;
        return;
    }

    for (i = 0; i < departmentCount; i++)
    {
        printf("\nEnter department %d name: ", i + 1);
        fgets(departments[i], 50, stdin);

        departments[i][strcspn(departments[i], "\n")] = '\0';

        do
        {
            printf("Enter allocated budget for %s: N$", departments[i]);
            scanf("%f", &budgets[i]);
            getchar();

            if (budgets[i] < 0)
            {
                printf("Budget cannot be negative. Try again.\n");
            }

        } while (budgets[i] < 0);

        expenditures[i] = 0;
    }

    printf("\nDepartment budgets saved successfully!\n");
}

void enterExpenditure(void)
{
    int i;

    if (departmentCount == 0)
    {
        printf("\nNo departments have been entered yet.\n");
        printf("Please enter department budgets first.\n");
        return;
    }

    printf("\n===== ENTER EXPENDITURE =====\n");

    for (i = 0; i < departmentCount; i++)
    {
        do
        {
            printf("Enter expenditure for %s: N$", departments[i]);
            scanf("%f", &expenditures[i]);
            getchar();

            if (expenditures[i] < 0)
            {
                printf("Expenditure cannot be negative. Try again.\n");
            }

        } while (expenditures[i] < 0);
    }

    printf("\nExpenditure recorded successfully!\n");
}

void displayBudgets(void)
{
    int i;
    float remaining;

    if (departmentCount == 0)
    {
        printf("\nNo budget information available.\n");
        return;
    }

    printf("\n========== BUDGET INFORMATION ==========\n");

    for (i = 0; i < departmentCount; i++)
    {
        remaining = budgets[i] - expenditures[i];

        printf("\nDepartment: %s\n", departments[i]);
        printf("Allocated Budget: N$%.2f\n", budgets[i]);
        printf("Expenditure: N$%.2f\n", expenditures[i]);
        printf("Remaining Budget: N$%.2f\n", remaining);

        if (expenditures[i] <= budgets[i])
        {
            printf("Status: WITHIN BUDGET\n");
        }
        else
        {
            printf("Status: OVER BUDGET\n");
        }
    }
}

void showOverBudget(void)
{
    int i;
    int found = 0;

    if (departmentCount == 0)
    {
        printf("\nNo budget information available.\n");
        return;
    }

    printf("\n===== DEPARTMENTS OVER BUDGET =====\n");

    for (i = 0; i < departmentCount; i++)
    {
        if (expenditures[i] > budgets[i])
        {
            printf("\nDepartment: %s\n", departments[i]);
            printf("Budget: N$%.2f\n", budgets[i]);
            printf("Expenditure: N$%.2f\n", expenditures[i]);
            printf("Exceeded By: N$%.2f\n",
                   expenditures[i] - budgets[i]);

            found = 1;
        }
    }

    if (!found)
    {
        printf("No departments are over budget.\n");
    }
}