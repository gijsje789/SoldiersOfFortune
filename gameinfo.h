#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <QMap>

class GameInfo
{
public:
    GameInfo(const GameInfo& obj) = delete;

    static GameInfo* getInstance();
    void addweaponAsset(QString name, int number);
    int getWeaponAsset(QString name);
    void quit();
    void saveGame(QString dir);
    void loadGame(QString dir);
private:
    GameInfo();
    static GameInfo* m_instancePtr;

    QMap<QString, double> m_weaponAssets;
    void saveAssetsToFile();
};

#endif // GAMEINFO_H
