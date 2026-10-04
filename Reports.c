#include <stdio.h>
#include <string.h>
#include "reports.h"

void displayEmployeeReport(int employeeCount, double salaries[], char names[][50], char departments[][30])
{
    int i;
    double total = 0.0, average = 0.0, highest = 0.0, lowest = 0.0;

    printf("\n=======================================\n");
    printf("           EMPLOYEE REPORT\n");
    printf("=========================================\n");

    if (employeeCount <= 0)
    {
        printf("No employees registered in the system.\n");
        printf("======================================\n");
        return;
    }

    highest = salaries[0];
    lowest  = salaries[0];

    for (i = 0; i < employeeCount; i++)
    {
        total = total + salaries[i];

        if (salaries[i] > highest)
            highest = salaries[i];

        if (salaries[i] < lowest)
            lowest = salaries[i];
    }

    average = total / employeeCount;

    printf("Total Employees  : %d\n", employeeCount);
    printf("Total Salary Bill: N$%.2f\n", total);
    printf("Average Salary   : N$%.2f\n", average);
    printf("Highest Salary   : N$%.2f\n", highest);
    printf("Lowest Salary    : N$%.2f\n", lowest);

    printf("\n-----------------------------------\n");
    printf("%-25s %-15s %-12s\n", "Employee Name", "Department", "Salary");
    printf("-------------------------------------\n");

    for (i = 0; i < employeeCount; i++)
    {
        printf("%-25s %-15s N$%-10.2f\n", names[i], departments[i], salaries[i]);
    }

    printf("======================================\n");
}

void displayBudgetReport(int departmentCount, char deptNames[][30], double allocated[], double expenditure[])
{
    int i;
    double totalAllocated = 0.0, totalExpenditure = 0.0, totalRemaining = 0.0, remaining = 0.0;
    int exceededCount = 0;

    printf("\n====================================\n");
    printf("             BUDGET REPORT\n");
    printf("======================================\n");

    if (departmentCount <= 0)
    {
        printf("No departmental budgets captured.\n");
        printf("==================================\n");
        return;
    }

    printf("%-15s %-15s %-15s %-15s %-15s\n", "Department", "Allocated", "Expenditure", "Remaining", "Status");
    printf("-----------------------------------------------\n");

    for (i = 0; i < departmentCount; i++)
    {
        remaining = allocated[i] - expenditure[i];

        totalAllocated   = totalAllocated + allocated[i];
        totalExpenditure = totalExpenditure + expenditure[i];
        totalRemaining   = totalRemaining + remaining;

        printf("%-15s N$%-13.2f N$%-13.2f N$%-13.2f ", deptNames[i], allocated[i], expenditure[i], remaining);

        if (expenditure[i] > allocated[i])
        {
            printf("OVER BUDGET\n");
            exceededCount++;
        }
        else if (expenditure[i] == allocated[i])
        {
            printf("FULLY SPENT\n");
        }
        else
        {
            printf("WITHIN BUDGET\n");
        }
    }

    printf("--------------------------------------------------\n");
    printf("Total Allocated Budget : N$%.2f\n", totalAllocated);
    printf("Total Expenditure      : N$%.2f\n", totalExpenditure);
    printf("Total Remaining Budget : N$%.2f\n", totalRemaining);

    printf("\n--- Departments Exceeding Budget ---\n");

    if (exceededCount == 0)
    {
        printf("None. All departments are within their allocated budget.\n");
    }
    else
    {
        for (i = 0; i < departmentCount; i++)
        {
            if (expenditure[i] > allocated[i])
            {
                printf(" - %s (Overspent by N$%.2f)\n", deptNames[i], expenditure[i] - allocated[i]);
            }
        }
        printf("\nTotal departments over budget: %d\n", exceededCount);
    }

    printf("=======================================\n");
}

void displaySupplierReport(int supplierCount, char supplierNames[][100], char emails[][100], char phones[][30], char towns[][50])
{
    int i;

    printf("\n=====================================\n");
    printf("            SUPPLIER REPORT\n");
    printf("=======================================\n");

    if (supplierCount <= 0)
    {
        printf("No suppliers registered in the system.\n");
        printf("===================================\n");
        return;
    }

    printf("Total Registered Suppliers: %d\n", supplierCount);
    printf("---------------------------------------\n");

    for (i = 0; i < supplierCount; i++)
    {
        printf("Supplier %d\n", i + 1);
        printf("  Name : %s\n", supplierNames[i]);
        printf("  Email: %s\n", emails[i]);
        printf("  Phone: %s\n", phones[i]);
        printf("  Town : %s\n", towns[i]);
        printf("  Name Length: %d characters\n", (int)strlen(supplierNames[i]));
        printf("------------------------------------\n");
    }

    printf("=======================================\n");
}

void displayAssetReport(int assetCount, char assetNames[][50], char assetTypes[][30], double purchaseValues[], char assetDepartments[][30], char conditions[][20])
{
    int i;
    double totalValue = 0.0, averageValue = 0.0;
    int goodCount = 0, fairCount = 0, poorCount = 0;

    printf("\n============================================\n");
    printf("              ASSET REPORT\n");
    printf("============================================\n");

    if (assetCount <= 0)
    {
        printf("No assets registered in the system.\n");
        printf("============================================\n");
        return;
    }

    printf("%-20s %-12s %-15s %-15s %-10s\n", "Asset Name", "Type", "Department", "Value", "Condition");
    printf("------------------------------------------------------\n");

    for (i = 0; i < assetCount; i++)
    {
        printf("%-20s %-12s %-15s N$%-13.2f %-10s\n", assetNames[i], assetTypes[i], assetDepartments[i], purchaseValues[i], conditions[i]);

        totalValue = totalValue + purchaseValues[i];

        if (strcmp(conditions[i], "Good") == 0)
            goodCount++;
        else if (strcmp(conditions[i], "Fair") == 0)
            fairCount++;
        else
            poorCount++;
    }

    averageValue = totalValue / assetCount;

    printf("------------------------------------------------------\n");
    printf("Total Assets        : %d\n", assetCount);
    printf("Total Asset Value   : N$%.2f\n", totalValue);
    printf("Average Asset Value : N$%.2f\n", averageValue);
    printf("\nCondition Breakdown:\n");
    printf("  Good : %d\n", goodCount);
    printf("  Fair : %d\n", fairCount);
    printf("  Poor : %d\n", poorCount);

    printf("====================================\n");
}

void displayReportsMenu(void)
{
    printf("\n==================================\n");
    printf("            REPORTS MENU\n");
    printf("====================================\n");
    printf("  1. Employee Report\n");
    printf("  2. Budget Report\n");
    printf("  3. Supplier Report\n");
    printf("  4. Asset Report\n");
    printf("  5. Back to Main Menu\n");
    printf("===================================\n");
    printf("Enter your choice: ");
}

void reportsMenu(void)
{
    int choice = 0;

    do
    {
        displayReportsMenu();
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("\n[Employee Report selected]\n");
                break;
            case 2:
                printf("\n[Budget Report selected]\n");
                break;
            case 3:
                printf("\n[Supplier Report selected]\n");
                break;
            case 4:
                printf("\n[Asset Report selected]\n");
                break;
            case 5:
                printf("\nReturning to Main Menu...\n");
                break;
            default:
                printf("\nInvalid choice. Please enter 1-5.\n");
        }

    } while (choice != 5);
}