#ifndef ASSETS_H
#define ASSETS_H

#define MAX_ASSETS 100

typedef struct
{
    int assetID;
    char assetName[100];
    char assetType[50];
    double purchaseValue;
    char department[100];
    char condition[50];
} Asset;

void assetMenu(void);
void addAsset(void);
void displayAssets(void);
void searchAsset(void);
int findAssetByID(int id);
void clearInputBuffer(void);

#endif