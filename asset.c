#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "assets.h"
#include "employees.h"   /* clearInputBuffer */

Asset assets[MAX_ASSETS];
int assetCount = 0;

int findAssetById(int id) {
    int i;
    for (i = 0; i < assetCount; i++)
        if (assets[i].id == id) return i;
    return -1;
}

void addAsset(void) {
    Asset a;
    int valid;

    if (assetCount >= MAX_ASSETS) {
        printf("\n  [!] Asset register is full.\n");
        return;
    }

    printf("\n===== ADD ASSET =====\n");

    do {
        valid = 1;
        printf("Asset ID (positive): ");
        if (scanf("%d", &a.id) != 1) {
            printf("  [!] Invalid number.\n");
            clearInputBuffer();
            valid = 0;
        } else if (a.id <= 0) {
            printf("  [!] ID must be positive.\n");
            valid = 0;
        } else if (findAssetById(a.id) != -1) {
            printf("  [!] ID already in use.\n");
            valid = 0;
        }
    } while (!valid);
    clearInputBuffer();

    do {
        printf("Asset Name: ");
        fgets(a.name, ASSET_NAME_LEN, stdin);
        a.name[strcspn(a.name, "\n")] = '\0';
        if (strlen(a.name) == 0) printf("  [!] Name cannot be empty.\n");
    } while (strlen(a.name) == 0);

    do {
        printf("Asset Type (Vehicle/Computer/Building/Equipment/Furniture): ");
        fgets(a.type, ASSET_TYPE_LEN, stdin);
        a.type[strcspn(a.type, "\n")] = '\0';
        if (strlen(a.type) == 0) printf("  [!] Type cannot be empty.\n");
    } while (strlen(a.type) == 0);

    do {
        valid = 1;
        printf("Purchase Value (N$): ");
        if (scanf("%lf", &a.purchaseValue) != 1) {
            printf("  [!] Invalid amount.\n");
            clearInputBuffer();
            valid = 0;
        } else if (a.purchaseValue < 0) {
            printf("  [!] Value cannot be negative.\n");
            valid = 0;
        }
    } while (!valid);
    clearInputBuffer();

    do {
        printf("Department: ");
        fgets(a.department, ASSET_DEPT_LEN, stdin);
        a.department[strcspn(a.department, "\n")] = '\0';
        if (strlen(a.department) == 0)
            printf("  [!] Department cannot be empty.\n");
    } while (strlen(a.department) == 0);

    do {
        printf("Condition (New/Good/Fair/Poor): ");
        fgets(a.condition, ASSET_COND_LEN, stdin);
        a.condition[strcspn(a.condition, "\n")] = '\0';
        if (strlen(a.condition) == 0)
            printf("  [!] Condition cannot be empty.\n");
    } while (strlen(a.condition) == 0);

    assets[assetCount] = a;
    assetCount++;

    printf("\n  [OK] Asset \"%s\" registered.\n", a.name);
}

void displayAssets(void) {
    int i;

    if (assetCount == 0) {
        printf("\n  No assets registered.\n");
        return;
    }

    printf("\n==================== ASSET REGISTER ====================\n");
    printf("%-6s %-22s %-12s %12s %-15s %-8s\n",
           "ID", "Name", "Type", "Value", "Department", "Cond.");
    printf("--------------------------------------------------------------------------\n");

    for (i = 0; i < assetCount; i++) {
        printf("%-6d %-22s %-12s %12.2f %-15s %-8s\n",
               assets[i].id,
               assets[i].name,
               assets[i].type,
               assets[i].purchaseValue,
               assets[i].department,
               assets[i].condition);
    }
    printf("--------------------------------------------------------------------------\n");
    printf("Total assets: %d\n", assetCount);
}

void searchAsset(void) {
    int choice, id, i, found = 0;
    char query[ASSET_NAME_LEN];

    if (assetCount == 0) {
        printf("\n  No assets to search.\n");
        return;
    }

    printf("\n===== SEARCH ASSET =====\n");
    printf("1. By ID\n2. By Name\n3. By Type\nEnter choice: ");
    scanf("%d", &choice);
    clearInputBuffer();

    if (choice == 1) {
        printf("Asset ID: ");
        scanf("%d", &id);
        clearInputBuffer();
        i = findAssetById(id);
        if (i != -1) {
            printf("\n  ID       : %d\n", assets[i].id);
            printf("  Name     : %s\n", assets[i].name);
            printf("  Type     : %s\n", assets[i].type);
            printf("  Value    : N$%.2f\n", assets[i].purchaseValue);
            printf("  Dept     : %s\n", assets[i].department);
            printf("  Condition: %s\n", assets[i].condition);
        } else {
            printf("\n  [!] Asset ID %d not found.\n", id);
        }
    } else if (choice == 2 || choice == 3) {
        printf("Enter search text: ");
        fgets(query, ASSET_NAME_LEN, stdin);
        query[strcspn(query, "\n")] = '\0';

        for (i = 0; i < assetCount; i++) {
            char source[ASSET_NAME_LEN], lowerSrc[ASSET_NAME_LEN], lowerQ[ASSET_NAME_LEN];
            int j;

            if (choice == 2) strcpy(source, assets[i].name);
            else             strcpy(source, assets[i].type);

            for (j = 0; source[j]; j++)
                lowerSrc[j] = tolower((unsigned char)source[j]);
            lowerSrc[j] = '\0';
            for (j = 0; query[j]; j++)
                lowerQ[j] = tolower((unsigned char)query[j]);
            lowerQ[j] = '\0';

            if (strstr(lowerSrc, lowerQ) != NULL) {
                printf("\n  Match: ID %d - %s (%s, %s)\n",
                       assets[i].id, assets[i].name,
                       assets[i].type, assets[i].department);
                found = 1;
            }
        }
        if (!found)
            printf("\n  [!] No matching asset.\n");
    } else {
        printf("\n  [!] Invalid choice.\n");
    }
}
