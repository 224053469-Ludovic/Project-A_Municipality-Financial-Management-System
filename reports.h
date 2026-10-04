#ifndef REPORTS_H
#define REPORTS_H

#define MAX_EMPLOYEES 100
#define MAX_DEPARTMENTS 10
#define MAX_SUPPLIERS 100
#define MAX_ASSETS 100

void displayEmployeeReport(int employeeCount,
                           double salaries[],
                       char names[][50],
                           char departments[][30]);

void displayBudgetReport(int departmentCount,
                         char deptNames[][30],
                         double allocated[],
                         double expenditure[]);

void displaySupplierReport(int supplierCount,
                           char supplierNames[][100],
                           char emails[][100],
                           char phones[][30],
                           char towns[][50]);
                          
void displayAssetReport(int assetCount,
                        char assetNames[][50],
                        char assetTypes[][30],
                        double purchaseValues[],
                        char assetDepartments[][30],
                        char conditions[][20]);

void displayReportsMenu(void);
void reportsMenu(void);

#endif