#ifndef GAMEINFO_H
#define GAMEINFO_H


class GameInfo
{
public:
    GameInfo(const GameInfo& obj) = delete;

    static GameInfo* getInstance();

private:
    GameInfo();
    static GameInfo* m_instancePtr;

};

#endif // GAMEINFO_H
