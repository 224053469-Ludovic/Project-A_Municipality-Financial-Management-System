#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPARTMENTS 10

extern char departments[MAX_DEPARTMENTS][50];
extern float budgets[MAX_DEPARTMENTS];
extern float expenditures[MAX_DEPARTMENTS];
extern int departmentCount;

void budgetMenu(void);
void enterBudgets(void);
void enterExpenditure(void);
void displayBudgets(void);
void showOverBudget(void);

#endif