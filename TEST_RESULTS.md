Test Results
Test Case
Phase 1 
•	Add employees 
•	Module: Employee
•	Test data: ID-1011, Name-Zambwe, Debt-Finance, Basic-N$700, Housing-N$2000, Transport-N$500    

Expected: “Employee added, total salary N$200”
Actual: 
Status: pass 


Search employee 
 Module: employee 
Test info: Search ID = 101
Expected: “Employee not found” + with details. 
Actual: 
Status: pass


Budget 
Module: Budget 
Test info: Finance budget-N$4000, EXP 34343, Works budgets-3000 
Expected:  “ Done” 
Actual: 
Status: Pass


Add Supplier 
Module: Supplier 
Test info: Z909, Windhoek, salae@yahoo.com
Expected: “Done”
Actual Status : fail

Add Asset
Module: Asset  
Test data: ID=2323, Toyota hilax, Vehicle 35, Functional, Good 
Expected: “Asset added successfully” 
Actual Status: Pass

Validation Tests 
Negative Salary 
Test data basic salary -33
Expected rejected, re-prompt 
Actual: 
Status: fail

empty employee name 
test data press enters with nothing 
expected name cannot be empty
Actual: 
Status: pass

invalid mane choice 
Test data:  99 and then x at end of the menu  
 Expected “Rejected” 
Actual:
Status: pass

Duplicate supplier ID
Test date adds Supplier with ID = 121 again 
Expected “That ID already exits”
Actual: 
Status: fail

User interface Test
Main menu displays 
Expected: Title plus 6 options 
Enter your choice 
Actual: 
Status: fail

Navigate and Exit 
Steps open submenu, return select 6 to exit 
Expected all submenu return select 6 to exit 
Status: fail


Errors found 4

Summary 4 out of 11 

Passed| Phase| failed 
Functional: 
Validation: 
User interface: 
Total: 11
