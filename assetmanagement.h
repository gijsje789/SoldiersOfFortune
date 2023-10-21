#ifndef ASSETMANAGEMENT_H
#define ASSETMANAGEMENT_H

#include <QMap>

#include "gamecontrol.h"

class AssetManagement
{
public:
    AssetManagement(const AssetManagement& obj) = delete;

    static AssetManagement* getInstance();
    void addweaponAsset(QString name, int number);
    int getWeaponAssetCurrent(QString name);
    void quit();
    void saveGame(QString dir);
    bool loadGame(QString dir);
    bool takeMoney(double value);
    void addMoney(double value);
    double getMoney();
    void setMoney(double value);
    void setGameControl(GameControl* control);
private:
    AssetManagement();
    static AssetManagement* m_instancePtr;

    double m_money;
    GameControl* m_control;

    QMap<QString, double> m_weaponAssets;
    void saveWeaponAssetsToFile(QString dir);
    void loadWeaponAssetsFromFile(QString dir);
    void saveGameInfoToFile(QString dir);
    void loadGameInfoFromFile(QString dir);
};

#endif // ASSETMANAGEMENT_H
