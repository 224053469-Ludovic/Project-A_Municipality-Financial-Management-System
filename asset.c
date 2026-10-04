#include <stdio.h>
#include <string.h>
#include "assets.h"

static Asset assets[MAX_ASSETS];
static int assetCount = 0;

void clearInputBuffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

int findAssetByID(int id)
{
    int i;

    for (i = 0; i < assetCount; i++)
    {
        if (assets[i].assetID == id)
        {
            return i;
        }
    }

    return -1;
}

void addAsset(void)
{
    int id;
    int result;

    if (assetCount >= MAX_ASSETS)
    {
        printf("\nAsset register is full.\n");
        return;
    }

    while (1)
    {
        printf("\nEnter Asset ID: ");
        result = scanf("%d", &id);

        if (result != 1)
        {
            printf("Invalid Asset ID.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (id <= 0)
        {
            printf("Asset ID must be greater than 0.\n");
            continue;
        }

        if (findAssetByID(id) != -1)
        {
            printf("Asset ID already exists.\n");
            continue;
        }

        break;
    }

    assets[assetCount].assetID = id;

    while (1)
    {
        printf("Enter Asset Name: ");

        fgets(
            assets[assetCount].assetName,
            sizeof(assets[assetCount].assetName),
            stdin
        );

        assets[assetCount].assetName[
            strcspn(assets[assetCount].assetName, "\n")
        ] = '\0';

        if (strlen(assets[assetCount].assetName) == 0)
        {
            printf("Asset name cannot be empty.\n");
            continue;
        }

        break;
    }

    while (1)
    {
        printf("Enter Asset Type: ");

        fgets(
            assets[assetCount].assetType,
            sizeof(assets[assetCount].assetType),
            stdin
        );

        assets[assetCount].assetType[
            strcspn(assets[assetCount].assetType, "\n")
        ] = '\0';

        if (strlen(assets[assetCount].assetType) == 0)
        {
            printf("Asset type cannot be empty.\n");
            continue;
        }

        break;
    }

    while (1)
    {
        printf("Enter Purchase Value (N$): ");

        result = scanf(
            "%lf",
            &assets[assetCount].purchaseValue
        );

        if (result != 1)
        {
            printf("Invalid purchase value.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (assets[assetCount].purchaseValue < 0)
        {
            printf("Purchase value cannot be negative.\n");
            continue;
        }

        break;
    }

    while (1)
    {
        printf("Enter Department: ");

        fgets(
            assets[assetCount].department,
            sizeof(assets[assetCount].department),
            stdin
        );

        assets[assetCount].department[
            strcspn(assets[assetCount].department, "\n")
        ] = '\0';

        if (strlen(assets[assetCount].department) == 0)
        {
            printf("Department cannot be empty.\n");
            continue;
        }

        break;
    }

    while (1)
    {
        printf("Enter Condition: ");

        fgets(
            assets[assetCount].condition,
            sizeof(assets[assetCount].condition),
            stdin
        );

        assets[assetCount].condition[
            strcspn(assets[assetCount].condition, "\n")
        ] = '\0';

        if (strlen(assets[assetCount].condition) == 0)
        {
            printf("Condition cannot be empty.\n");
            continue;
        }

        break;
    }

    assetCount++;

    printf("\nAsset added successfully.\n");
}

void displayAssets(void)
{
    int i;

    if (assetCount == 0)
    {
        printf("\nNo assets registered.\n");
        return;
    }

    printf("\n");
    printf("===============================================================\n");
    printf("                    ASSET REGISTER\n");
    printf("===============================================================\n");

    for (i = 0; i < assetCount; i++)
    {
        printf("\nAsset ID       : %d\n", assets[i].assetID);
        printf("Asset Name     : %s\n", assets[i].assetName);
        printf("Asset Type     : %s\n", assets[i].assetType);
        printf("Purchase Value : N$%.2f\n", assets[i].purchaseValue);
        printf("Department     : %s\n", assets[i].department);
        printf("Condition      : %s\n", assets[i].condition);
        printf("---------------------------------------------------------------\n");
    }

    printf("Total Assets: %d\n", assetCount);
}

void searchAsset(void)
{
    int id;
    int position;
    int result;

    if (assetCount == 0)
    {
        printf("\nNo assets registered.\n");
        return;
    }

    printf("\nEnter Asset ID to search: ");

    result = scanf("%d", &id);

    if (result != 1)
    {
        printf("Invalid Asset ID.\n");
        clearInputBuffer();
        return;
    }

    clearInputBuffer();

    position = findAssetByID(id);

    if (position == -1)
    {
        printf("\nAsset not found.\n");
        return;
    }

    printf("\nAsset Found\n");
    printf("========================================\n");
    printf("Asset ID       : %d\n", assets[position].assetID);
    printf("Asset Name     : %s\n", assets[position].assetName);
    printf("Asset Type     : %s\n", assets[position].assetType);
    printf("Purchase Value : N$%.2f\n", assets[position].purchaseValue);
    printf("Department     : %s\n", assets[position].department);
    printf("Condition      : %s\n", assets[position].condition);
    printf("========================================\n");
}

void assetMenu(void)
{
    int choice;
    int result;

    do
    {
        printf("\n");
        printf("========================================\n");
        printf("          ASSET MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset\n");
        printf("4. Return to Main Menu\n");
        printf("========================================\n");
        printf("Enter your choice: ");

        result = scanf("%d", &choice);

        if (result != 1)
        {
            printf("Invalid choice.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        switch (choice)
        {
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
                break;

            default:
                printf("Invalid choice. Please choose 1-4.\n");
        }

    } while (choice != 4);
}