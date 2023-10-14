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
