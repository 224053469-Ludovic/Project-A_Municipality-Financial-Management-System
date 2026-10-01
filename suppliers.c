/* ---------------------------------------------------------------
 * suppliers.c - Supplier Management module (Student 3)
 *
 * Stores supplier records in parallel arrays: index i in every
 * array refers to the same supplier.
 *
 * Features: add, display, search (ID / name / town), compare two
 * suppliers, supplier report, and full input validation.
 * --------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "suppliers.h"

/* ---------- Storage (arrays) ---------- */
static char supplierId[MAX_SUPPLIERS][ID_LEN];
static char supplierName[MAX_SUPPLIERS][NAME_LEN];
static char supplierEmail[MAX_SUPPLIERS][EMAIL_LEN];
static char supplierPhone[MAX_SUPPLIERS][PHONE_LEN];
static char supplierTown[MAX_SUPPLIERS][TOWN_LEN];
static int  supplierCount = 0;

/* ---------- Private helper prototypes ---------- */
static int  readLine(const char *prompt, char *buf, int size);
static void trim(char *s);
static void toUpperStr(char *s);
static void toLowerCopy(const char *src, char *dst, int size);
static int  containsIgnoreCase(const char *text, const char *pattern);
static int  sameTextIgnoreCase(const char *a, const char *b);
static int  readChoice(int min, int max);
static int  isValidId(const char *id);
static int  isValidEmail(const char *email);
static int  isValidPhone(const char *phone);
static int  findSupplierById(const char *id);
static void buildLabel(int index, char *out, int size);
static void printTableHeader(void);
static void printSupplierRow(int index);
static int  readExistingSupplier(const char *prompt);

/* =================================================================
 *  INPUT / STRING HELPERS
 * ================================================================= */

/* Reads one line safely with fgets. Returns 1 on success, 0 on EOF. */
static int readLine(const char *prompt, char *buf, int size)
{
    printf("%s", prompt);

    if (fgets(buf, size, stdin) == NULL)
    {
        buf[0] = '\0';
        return 0;
    }

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n')
    {
        buf[len - 1] = '\0';
    }
    else
    {
        /* Input was longer than the buffer: throw away the rest */
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
    }

    trim(buf);
    return 1;
}

/* Removes leading and trailing spaces. */
static void trim(char *s)
{
    int start = 0;
    while (isspace((unsigned char)s[start]))
    {
        start++;
    }
    if (start > 0)
    {
        memmove(s, s + start, strlen(s + start) + 1);
    }

    int len = (int)strlen(s);
    while (len > 0 && isspace((unsigned char)s[len - 1]))
    {
        s[--len] = '\0';
    }
}

static void toUpperStr(char *s)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        s[i] = (char)toupper((unsigned char)s[i]);
    }
}

static void toLowerCopy(const char *src, char *dst, int size)
{
    int i;
    for (i = 0; src[i] != '\0' && i < size - 1; i++)
    {
        dst[i] = (char)tolower((unsigned char)src[i]);
    }
    dst[i] = '\0';
}

/* 1 if 'pattern' appears anywhere inside 'text' (case-insensitive). */
static int containsIgnoreCase(const char *text, const char *pattern)
{
    char t[NAME_LEN + EMAIL_LEN];
    char p[NAME_LEN + EMAIL_LEN];

    toLowerCopy(text, t, (int)sizeof t);
    toLowerCopy(pattern, p, (int)sizeof p);

    return strstr(t, p) != NULL;
}

/* 1 if both strings are equal ignoring upper/lower case. */
static int sameTextIgnoreCase(const char *a, const char *b)
{
    char x[NAME_LEN + EMAIL_LEN];
    char y[NAME_LEN + EMAIL_LEN];

    toLowerCopy(a, x, (int)sizeof x);
    toLowerCopy(b, y, (int)sizeof y);

    return strcmp(x, y) == 0;
}

/* Reads a menu number between min and max; repeats until valid. */
static int readChoice(int min, int max)
{
    char line[32];
    char *end;

    while (1)
    {
        if (!readLine("Enter your choice: ", line, (int)sizeof line))
        {
            return max; /* input closed: leave the menu */
        }

        long value = strtol(line, &end, 10);

        if (line[0] != '\0' && *end == '\0' && value >= min && value <= max)
        {
            return (int)value;
        }
        printf("  Invalid choice. Please enter a number from %d to %d.\n", min, max);
    }
}

/* =================================================================
 *  VALIDATION
 * ================================================================= */

/* ID: 2-9 letters/digits, no spaces (e.g. S001). */
static int isValidId(const char *id)
{
    size_t len = strlen(id);

    if (len < 2 || len >= ID_LEN)
    {
        return 0;
    }
    for (size_t i = 0; i < len; i++)
    {
        if (!isalnum((unsigned char)id[i]))
        {
            return 0;
        }
    }
    return 1;
}

/* Email: one '@', text before it, and a '.' after it (not at the end). */
static int isValidEmail(const char *email)
{
    for (int i = 0; email[i] != '\0'; i++)
    {
        if (isspace((unsigned char)email[i]))
        {
            return 0;
        }
    }

    const char *at = strchr(email, '@');
    if (at == NULL || at == email || strchr(at + 1, '@') != NULL)
    {
        return 0;
    }

    const char *dot = strrchr(at, '.');
    if (dot == NULL || dot == at + 1 || dot[1] == '\0')
    {
        return 0;
    }
    return 1;
}

/* Phone: digits, spaces, '+' and '-' only, with 7 to 15 digits. */
static int isValidPhone(const char *phone)
{
    int digits = 0;

    for (int i = 0; phone[i] != '\0'; i++)
    {
        if (isdigit((unsigned char)phone[i]))
        {
            digits++;
        }
        else if (phone[i] != ' ' && phone[i] != '+' && phone[i] != '-')
        {
            return 0;
        }
    }
    return digits >= 7 && digits <= 15;
}

/* =================================================================
 *  LOOKUP / DISPLAY HELPERS
 * ================================================================= */

/* Returns the array index of a supplier ID, or -1 if not found. */
static int findSupplierById(const char *id)
{
    for (int i = 0; i < supplierCount; i++)
    {
        if (strcmp(supplierId[i], id) == 0)
        {
            return i;
        }
    }
    return -1;
}

/* Builds a label such as "S001 - Windhoek Office Supplies". */
static void buildLabel(int index, char *out, int size)
{
    if (size < ID_LEN + NAME_LEN + 4)
    {
        out[0] = '\0';
        return;
    }
    strcpy(out, supplierId[index]);
    strcat(out, " - ");
    strcat(out, supplierName[index]);
}

static void printTableHeader(void)
{
    printf("\n%-9s %-30s %-40s %-16s %-20s\n",
           "ID", "NAME", "EMAIL", "TELEPHONE", "TOWN");
    for (int i = 0; i < 118; i++)
    {
        putchar('-');
    }
    putchar('\n');
}

static void printSupplierRow(int index)
{
    printf("%-9s %-30s %-40s %-16s %-20s\n",
           supplierId[index], supplierName[index], supplierEmail[index],
           supplierPhone[index], supplierTown[index]);
}

/* Asks for an ID until an existing one is entered. Returns its index,
 * or -1 if the user types 0 to cancel. */
static int readExistingSupplier(const char *prompt)
{
    char id[ID_LEN];

    while (1)
    {
        if (!readLine(prompt, id, (int)sizeof id))
        {
            return -1;
        }
        if (strcmp(id, "0") == 0)
        {
            return -1;
        }

        toUpperStr(id);
        int index = findSupplierById(id);
        if (index >= 0)
        {
            return index;
        }
        printf("  No supplier with ID '%s'. Try again or enter 0 to cancel.\n", id);
    }
}

/* =================================================================
 *  PUBLIC FUNCTIONS
 * ================================================================= */

int getSupplierCount(void)
{
    return supplierCount;
}

void addSupplier(void)
{
    char id[ID_LEN];
    char name[NAME_LEN];
    char email[EMAIL_LEN];
    char phone[PHONE_LEN];
    char town[TOWN_LEN];
    char label[ID_LEN + NAME_LEN + 4];

    printf("\n--- ADD SUPPLIER ---\n");

    if (supplierCount >= MAX_SUPPLIERS)
    {
        printf("The supplier register is full (%d suppliers).\n", MAX_SUPPLIERS);
        return;
    }

    /* Supplier ID: valid format and unique */
    while (1)
    {
        if (!readLine("Supplier ID (e.g. S001): ", id, (int)sizeof id))
        {
            return;
        }
        toUpperStr(id);

        if (!isValidId(id))
        {
            printf("  Invalid ID. Use 2-9 letters/digits with no spaces.\n");
        }
        else if (findSupplierById(id) >= 0)
        {
            printf("  That ID already exists. Please use a different ID.\n");
        }
        else
        {
            break;
        }
    }

    /* Supplier name: not empty, at least 2 characters */
    while (1)
    {
        if (!readLine("Supplier name: ", name, (int)sizeof name))
        {
            return;
        }
        if (strlen(name) >= 2)
        {
            break;
        }
        printf("  Name cannot be empty (minimum 2 characters, maximum %d).\n", NAME_LEN - 1);
    }

    /* Email */
    while (1)
    {
        if (!readLine("Email: ", email, (int)sizeof email))
        {
            return;
        }
        if (isValidEmail(email))
        {
            break;
        }
        printf("  Invalid email. Example: sales@company.com.na\n");
    }

    /* Telephone */
    while (1)
    {
        if (!readLine("Telephone number: ", phone, (int)sizeof phone))
        {
            return;
        }
        if (isValidPhone(phone))
        {
            break;
        }
        printf("  Invalid number. Use 7-15 digits (spaces, '+' and '-' allowed).\n");
    }

    /* Town / location */
    while (1)
    {
        if (!readLine("Town/Location: ", town, (int)sizeof town))
        {
            return;
        }
        if (strlen(town) >= 2)
        {
            break;
        }
        printf("  Town cannot be empty.\n");
    }

    /* Store the record */
    strcpy(supplierId[supplierCount], id);
    strcpy(supplierName[supplierCount], name);
    strcpy(supplierEmail[supplierCount], email);
    strcpy(supplierPhone[supplierCount], phone);
    strcpy(supplierTown[supplierCount], town);

    buildLabel(supplierCount, label, (int)sizeof label);
    supplierCount++;

    printf("\nSupplier added successfully: %s\n", label);
}

void displaySuppliers(void)
{
    printf("\n--- REGISTERED SUPPLIERS ---\n");

    if (supplierCount == 0)
    {
        printf("No suppliers have been registered yet.\n");
        return;
    }

    printTableHeader();
    for (int i = 0; i < supplierCount; i++)
    {
        printSupplierRow(i);
    }
    printf("\nTotal suppliers: %d\n", supplierCount);
}

void searchSupplier(void)
{
    char term[NAME_LEN];
    int found = 0;

    printf("\n--- SEARCH SUPPLIER ---\n");

    if (supplierCount == 0)
    {
        printf("No suppliers have been registered yet.\n");
        return;
    }

    printf("1. Search by Supplier ID\n");
    printf("2. Search by Name (partial match)\n");
    printf("3. Search by Town (partial match)\n");
    printf("4. Cancel\n");

    int choice = readChoice(1, 4);
    if (choice == 4)
    {
        return;
    }

    while (1)
    {
        if (!readLine("Enter search text: ", term, (int)sizeof term))
        {
            return;
        }
        if (strlen(term) > 0)
        {
            break;
        }
        printf("  Search text cannot be empty.\n");
    }

    if (choice == 1)
    {
        toUpperStr(term);
        int index = findSupplierById(term);
        if (index >= 0)
        {
            printTableHeader();
            printSupplierRow(index);
            found = 1;
        }
    }
    else
    {
        for (int i = 0; i < supplierCount; i++)
        {
            const char *field = (choice == 2) ? supplierName[i] : supplierTown[i];

            if (containsIgnoreCase(field, term))
            {
                if (found == 0)
                {
                    printTableHeader();
                }
                printSupplierRow(i);
                found++;
            }
        }
    }

    if (found == 0)
    {
        printf("\nNo supplier found matching '%s'.\n", term);
    }
    else
    {
        printf("\n%d supplier(s) found.\n", found);
    }
}

void compareSuppliers(void)
{
    char label1[ID_LEN + NAME_LEN + 4];
    char label2[ID_LEN + NAME_LEN + 4];

    printf("\n--- COMPARE SUPPLIERS ---\n");

    if (supplierCount < 2)
    {
        printf("At least two registered suppliers are needed to compare.\n");
        return;
    }

    printf("(Enter 0 at any prompt to cancel)\n");

    int a = readExistingSupplier("First supplier ID: ");
    if (a < 0)
    {
        return;
    }

    int b = readExistingSupplier("Second supplier ID: ");
    if (b < 0)
    {
        return;
    }

    if (a == b)
    {
        printf("You selected the same supplier twice.\n");
        return;
    }

    buildLabel(a, label1, (int)sizeof label1);
    buildLabel(b, label2, (int)sizeof label2);

    printf("\n%-12s | %-34s | %-34s\n", "", label1, label2);
    printf("-------------+------------------------------------+-----------------------------------\n");
    printf("%-12s | %-34s | %-34s\n", "Email", supplierEmail[a], supplierEmail[b]);
    printf("%-12s | %-34s | %-34s\n", "Telephone", supplierPhone[a], supplierPhone[b]);
    printf("%-12s | %-34s | %-34s\n", "Town", supplierTown[a], supplierTown[b]);
    printf("%-12s | %-34zu | %-34zu\n", "Name length", strlen(supplierName[a]), strlen(supplierName[b]));

    printf("\nResult: ");
    if (sameTextIgnoreCase(supplierTown[a], supplierTown[b]))
    {
        printf("both suppliers are based in %s.\n", supplierTown[a]);
    }
    else
    {
        printf("the suppliers are based in different towns.\n");
    }

    int order = strcmp(supplierName[a], supplierName[b]);
    if (order < 0)
    {
        printf("Alphabetically, '%s' comes before '%s'.\n", supplierName[a], supplierName[b]);
    }
    else if (order > 0)
    {
        printf("Alphabetically, '%s' comes before '%s'.\n", supplierName[b], supplierName[a]);
    }
    else
    {
        printf("The two suppliers have exactly the same name.\n");
    }
}

void displaySupplierReport(void)
{
    printf("\n========================================\n");
    printf("            SUPPLIER REPORT\n");
    printf("========================================\n");

    if (supplierCount == 0)
    {
        printf("No suppliers have been registered yet.\n");
        return;
    }

    printf("Total Suppliers: %d\n", supplierCount);
    printTableHeader();
    for (int i = 0; i < supplierCount; i++)
    {
        printSupplierRow(i);
    }

    /* Suppliers per town: count each town once */
    printf("\nSuppliers per town:\n");
    for (int i = 0; i < supplierCount; i++)
    {
        int alreadyCounted = 0;
        for (int j = 0; j < i; j++)
        {
            if (sameTextIgnoreCase(supplierTown[i], supplierTown[j]))
            {
                alreadyCounted = 1;
                break;
            }
        }
        if (alreadyCounted)
        {
            continue;
        }

        int total = 0;
        for (int k = 0; k < supplierCount; k++)
        {
            if (sameTextIgnoreCase(supplierTown[i], supplierTown[k]))
            {
                total++;
            }
        }
        printf("  %-20s : %d\n", supplierTown[i], total);
    }
}

void supplierMenu(void)
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("          SUPPLIER MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Compare Two Suppliers\n");
        printf("5. Supplier Report\n");
        printf("6. Back to Main Menu\n");

        choice = readChoice(1, 6);

        switch (choice)
        {
            case 1: addSupplier();           break;
            case 2: displaySuppliers();      break;
            case 3: searchSupplier();        break;
            case 4: compareSuppliers();      break;
            case 5: displaySupplierReport(); break;
            case 6: printf("Returning to main menu...\n"); break;
        }
    } while (choice != 6);
}

/* Demo data so you can test searching/reports without typing everything */
void loadSampleSuppliers(void)
{
    const char *ids[]    = {"S001", "S002", "S003", "S004"};
    const char *names[]  = {"Windhoek Office Supplies", "Namib Construction CC",
                            "Swakop IT Solutions", "Windhoek Fleet Services"};
    const char *emails[] = {"sales@wos.com.na", "info@namibcon.com.na",
                            "support@swakopit.com.na", "orders@wfs.com.na"};
    const char *phones[] = {"+264 61 123 4567", "+264 64 987 6543",
                            "+264 64 555 0101", "+264 61 777 8899"};
    const char *towns[]  = {"Windhoek", "Walvis Bay", "Swakopmund", "Windhoek"};

    for (int i = 0; i < 4 && supplierCount < MAX_SUPPLIERS; i++)
    {
        if (findSupplierById(ids[i]) >= 0)
        {
            continue; /* already loaded */
        }
        strcpy(supplierId[supplierCount], ids[i]);
        strcpy(supplierName[supplierCount], names[i]);
        strcpy(supplierEmail[supplierCount], emails[i]);
        strcpy(supplierPhone[supplierCount], phones[i]);
        strcpy(supplierTown[supplierCount], towns[i]);
        supplierCount++;
    }
}
