#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <QMap>

class GameInfo
{
public:
    GameInfo(const GameInfo& obj) = delete;

    static GameInfo* getInstance();
    void addAsset(QString name, int number);
    int getAsset(QString name);

private:
    GameInfo();
    static GameInfo* m_instancePtr;

    QMap<QString, double> m_assets;

};

#endif // GAMEINFO_H
