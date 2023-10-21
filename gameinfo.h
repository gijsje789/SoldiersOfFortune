#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <QMap>

class GameInfo
{
public:
    GameInfo(const GameInfo& obj) = delete;

    static GameInfo* getInstance();
    void addweaponAsset(QString name, int number);
    int getWeaponAssetCurrent(QString name);
    void quit();
    void saveGame(QString dir);
    bool loadGame(QString dir);
private:
    GameInfo();
    static GameInfo* m_instancePtr;

    QMap<QString, double> m_weaponAssets;
    void saveWeaponAssetsToFile(QString dir);
    void loadWeaponAssetsFromFile(QString dir);
};

#endif // GAMEINFO_H
