#ifndef SUPPLIERS_H
#define SUPPLIERS_H

/* ---------------------------------------------------------------
 * Supplier Management module  (Student 3)
 * Municipal Financial Management System - PAP521S Project A
 * --------------------------------------------------------------- */

#define MAX_SUPPLIERS 100
#define ID_LEN        10
#define NAME_LEN      31
#define EMAIL_LEN     41
#define PHONE_LEN     17
#define TOWN_LEN      21

/* Called from the main menu (option 3). Runs the supplier sub-menu. */
void supplierMenu(void);

/* Individual operations (also callable on their own) */
void addSupplier(void);
void displaySuppliers(void);
void searchSupplier(void);
void compareSuppliers(void);

/* Used by the Reports module (Student 5) */
void displaySupplierReport(void);
int  getSupplierCount(void);

/* Fills the register with demo data - handy for testing/demonstration */
void loadSampleSuppliers(void);

#endif
