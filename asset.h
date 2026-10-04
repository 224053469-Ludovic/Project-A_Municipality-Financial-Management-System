#ifndef ASSETS_H
#define ASSETS_H

#define MAX_ASSETS 200
#define ASSET_NAME_LEN 50
#define ASSET_TYPE_LEN 30
#define ASSET_DEPT_LEN 30
#define ASSET_COND_LEN 20

typedef struct {
    int id;
    char name[ASSET_NAME_LEN];
    char type[ASSET_TYPE_LEN];
    double purchaseValue;
    char department[ASSET_DEPT_LEN];
    char condition[ASSET_COND_LEN];
} Asset;

extern Asset assets[MAX_ASSETS];
extern int assetCount;

void addAsset(void);
void displayAssets(void);
void searchAsset(void);
int findAssetById(int id);

#endif
