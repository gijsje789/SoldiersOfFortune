#include "gameinfo.h"

GameInfo* GameInfo::m_instancePtr = nullptr;

GameInfo::GameInfo()
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
    if(m_assets.contains(name))
    {
        m_assets[name] += number;
    }
    else
    {
        m_assets.insert(name, number);
    }
}

int GameInfo::getAsset(QString name)
{
    int rval = 0;
    if(m_assets.contains(name))
    {
        rval = m_assets[name];
    }
    return rval;
}
