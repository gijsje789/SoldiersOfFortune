#include "gameinfo.h"

GameInfo* GameInfo::m_instancePtr = nullptr;

GameInfo::GameInfo()
{

}

void GameInfo::saveAssetsToFile()
{

}

GameInfo* GameInfo::getInstance()
{
    if (m_instancePtr == nullptr)
    {
        m_instancePtr = new GameInfo();
    }

    return m_instancePtr;
}

void GameInfo::addAsset(QString name, int number)
{
    if(m_weaponAssets.contains(name))
    {
        m_weaponAssets[name] += number;
    }
    else
    {
        m_weaponAssets.insert(name, number);
    }
}

int GameInfo::getAsset(QString name)
{
    int rval = 0;
    if(m_weaponAssets.contains(name))
    {
        rval = m_weaponAssets[name];
    }
    return rval;
}

void GameInfo::quit()
{

}

void GameInfo::saveGame()
{

}

void GameInfo::loadGame(QString file)
{

}
