#include <string.h>
#include <stdio.h>

#define MAX_ASSETS 100

// Structure for storing asset information
struct Asset {
    int assetID;
    char assetName[50];
    char assetType[30];
    float purchaseValue;
    char department[50];
    char condition[30];
};

// Global array of assets
struct Asset assets[MAX_ASSETS];

int assetCount = 0;


// ================================
// ADD ASSET
// ================================
void addAsset() {

    if (assetCount >= MAX_ASSETS) {
        printf("\nAsset register is full!\n");
        return;
    }

    printf("\n========== ADD ASSET ==========\n");

    printf("Enter Asset ID: ");
    scanf("%d", &assets[assetCount].assetID);

    printf("Enter Asset Name: ");
    scanf(" %[^\n]", assets[assetCount].assetName);

    printf("Enter Asset Type: ");
    scanf(" %[^\n]", assets[assetCount].assetType);

    printf("Enter Purchase Value: ");
    scanf("%f", &assets[assetCount].purchaseValue);

    printf("Enter Department: ");
    scanf(" %[^\n]", assets[assetCount].department);

    printf("Enter Condition: ");
    scanf(" %[^\n]", assets[assetCount].condition);

    assetCount++;

    printf("\nAsset added successfully!\n");
}


// ================================
// DISPLAY ASSETS
// ================================
void displayAssets() {

    int i;

    if (assetCount == 0) {
        printf("\nNo assets have been registered.\n");
        return;
    }

    printf("\n================ ASSET REGISTER ================\n");

    for (i = 0; i < assetCount; i++) {

        printf("\nAsset %d\n", i + 1);
        printf("----------------------------------------\n");
        printf("Asset ID       : %d\n", assets[i].assetID);
        printf("Asset Name     : %s\n", assets[i].assetName);
        printf("Asset Type     : %s\n", assets[i].assetType);
        printf("Purchase Value : %.2f\n", assets[i].purchaseValue);
        printf("Department     : %s\n", assets[i].department);
        printf("Condition      : %s\n", assets[i].condition);
    }
}


// ================================
// SEARCH ASSET
// ================================
void searchAsset() {

    int id;
    int i;
    int found = 0;

    printf("\n========== SEARCH ASSET ==========\n");

    printf("Enter Asset ID to search: ");
    scanf("%d", &id);

    for (i = 0; i < assetCount; i++) {

        if (assets[i].assetID == id) {

            printf("\nAsset Found!\n");
            printf("----------------------------------------\n");
            printf("Asset ID       : %d\n", assets[i].assetID);
            printf("Asset Name     : %s\n", assets[i].assetName);
            printf("Asset Type     : %s\n", assets[i].assetType);
            printf("Purchase Value : %.2f\n", assets[i].purchaseValue);
            printf("Department     : %s\n", assets[i].department);
            printf("Condition      : %s\n", assets[i].condition);

            found = 1;
            break;
        }
    }

    if (found == 0) {
        printf("\nAsset with ID %d was not found.\n", id);
    }
}


// ================================
// ASSET MANAGEMENT MENU
// ================================
void assetManagement() {

    int choice;

    do {

        printf("\n========================================\n");
        printf("          ASSET MANAGEMENT\n");
        printf("========================================\n");

        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset\n");
        printf("4. Return to Main Menu\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                addAsset();
                break;

            case 2:
                displayAssets();
                break;

            case 3:
                searchAsset();
                break;

            case 4:
                printf("\nReturning to Main Menu...\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 4);
}


// ================================
// MAIN MENU
// ================================
int main() {

    int choice;

    do {

        printf("\n\n");
        printf("============================================\n");
        printf("   MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
        printf("============================================\n");

        printf("1. Employee Management\n");
        printf("2. Budget Management\n");
        printf("3. Supplier Management\n");
        printf("4. Asset Management\n");
        printf("5. Reports\n");
        printf("6. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("\nEmployee Management module selected.\n");
                break;

            case 2:
                printf("\nBudget Management module selected.\n");
                break;

            case 3:
                printf("\nSupplier Management module selected.\n");
                break;

            case 4:
                assetManagement();
                break;

            case 5:
                printf("\nReports module selected.\n");
                break;

            case 6:
                printf("\nThank you for using the Municipal Financial Management System.\n");
                break;

            default:
                printf("\nInvalid choice! Please enter 1-6.\n");
        }

    } while (choice != 6);

    return 0;
}
