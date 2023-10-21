#include "gameinfo.h"

#include <QDir>
#include <QJsonDocument>

GameInfo* GameInfo::m_instancePtr = nullptr;

GameInfo::GameInfo()
{

}

void GameInfo::saveWeaponAssetsToFile(QString dir)
{
    QString file = QDir(dir).filePath("weapons.csv");

    QFile output = QFile(file);
    output.open(QIODeviceBase::WriteOnly);
    if(output.isOpen())
    {
        foreach(auto element, m_weaponAssets.keys())
        {
            QString temp1 = QString(element);
            QString temp2 = QString::number(m_weaponAssets.value(element), 'f', 0);
            QString temp3 = QString('\n');
            output.write((temp1 + ',' + temp2 + temp3).toStdString().c_str());
        }
    }
}

void GameInfo::loadWeaponAssetsFromFile(QString dir)
{
    QString file = QDir(dir).filePath("weapons.csv");

    QFile input = QFile(file);
    input.open(QIODeviceBase::ReadOnly);
    if(input.isOpen())
    {
        qDebug() << "File opened: " << file;

        QString line = "";
        while(!input.atEnd())
        {
            line = input.readLine().trimmed();
            QStringList list =  line.split(',');
            addweaponAsset(list[0], list[1].toInt());
        }
    }
    else
    {
        qDebug() << "File not open: " << file;
    }
}

GameInfo* GameInfo::getInstance()
{
    if (m_instancePtr == nullptr)
    {
        m_instancePtr = new GameInfo();
    }

    return m_instancePtr;
}

void GameInfo::addweaponAsset(QString name, int number)
{
    if(m_weaponAssets.contains(name))
    {
        m_weaponAssets[name] += number;
    }
    else
    {
        m_weaponAssets.insert(name, number);
    }
    qDebug() << "Added: " << name << ", " << m_weaponAssets[name];
}

int GameInfo::getWeaponAssetCurrent(QString name)
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

void GameInfo::saveGame(QString dir)
{
    if(!QDir(dir).exists())
    {
        QDir().mkdir(dir);
    }
    saveWeaponAssetsToFile(dir);
}

bool GameInfo::loadGame(QString dir)
{
    bool rval = false;
    if(QDir(dir).exists())
    {
        loadWeaponAssetsFromFile(dir);
        rval = true;
    }
    return rval;
}
