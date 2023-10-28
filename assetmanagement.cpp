#include "assetmanagement.h"

#include <QDir>
#include <QJsonDocument>

AssetManagement* AssetManagement::m_instancePtr = nullptr;

AssetManagement::AssetManagement()
{

}

void AssetManagement::saveWeaponAssetsToFile(QString dir)
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

void AssetManagement::loadWeaponAssetsFromFile(QString dir)
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

void AssetManagement::saveGameInfoToFile(QString dir)
{
    QString file = QDir(dir).filePath("gameinfo.csv");

    QFile output = QFile(file);
    output.open(QIODeviceBase::WriteOnly);
    if(output.isOpen())
    {
        QString par = "money,";
        QString val = QString::number(m_money, 'f', 2);
        QString endline = "\n";
        output.write((par + val + endline).toStdString().c_str());

        par = "curDate,";
        val = m_curDate.getDate();
        output.write((par + val + endline).toStdString().c_str());

        par = "startDate,";
        val = m_startDate.getDate();
        output.write((par + val + endline).toStdString().c_str());
    }
}

void AssetManagement::loadGameInfoFromFile(QString dir)
{
    QString file = QDir(dir).filePath("gameinfo.csv");

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
            if(list[0] == "money")
            {
                setMoney(list[1].toDouble());
            }
            else if(list[0] == "curDate")
            {
                m_curDate.setDate(list[1]);
                m_control->updateDateLabel(m_curDate.getDate());
            }
            else if(list[0] == "startDate")
            {
                m_startDate.setDate(list[1]);
            }
        }
    }
    else
    {
        qDebug() << "File not open: " << file;
    }
}

AssetManagement* AssetManagement::getInstance()
{
    if (m_instancePtr == nullptr)
    {
        m_instancePtr = new AssetManagement();
    }

    return m_instancePtr;
}

void AssetManagement::addweaponAsset(QString name, int number)
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

int AssetManagement::getWeaponAssetCurrent(QString name)
{
    int rval = 0;
    if(m_weaponAssets.contains(name))
    {
        rval = m_weaponAssets[name];
    }
    return rval;
}

void AssetManagement::quit()
{

}

void AssetManagement::saveGame(QString dir)
{
    if(!QDir(dir).exists())
    {
        QDir().mkdir(dir);
    }
    saveWeaponAssetsToFile(dir);
    saveGameInfoToFile(dir);
}

bool AssetManagement::loadGame(QString dir)
{
    bool rval = false;
    if(QDir(dir).exists())
    {
        loadWeaponAssetsFromFile(dir);
        loadGameInfoFromFile(dir);
        rval = true;
    }
    return rval;
}

bool AssetManagement::takeMoney(double value)
{
    bool rval = false;
    if(value > m_money)
    {
        // TODO: debt control
    }
    else
    {
        m_money -= value;
        rval = true;
    }
    m_control->updateMoneyLabel(m_money);
    return rval;
}

void AssetManagement::addMoney(double value)
{
    m_money += value;
    m_control->updateMoneyLabel(m_money);
}

double AssetManagement::getMoney()
{
    return m_money;
}

void AssetManagement::setMoney(double value)
{
    m_money = value;
    m_control->updateMoneyLabel(m_money);
}

void AssetManagement::setStartingDate(QString date)
{
    m_curDate.setDate(date);
    m_startDate.setDate(date);
    m_control->updateDateLabel(m_curDate.getDate());
}

void AssetManagement::setGameControl(GameControl *control)
{
    m_control = control;
}

void AssetManagement::advanceTime(int days, int months, int years)
{
    qDebug() << "AssetManagement: adding time: " << days << ", " << months << ", " << years;
    m_curDate.addTime(days, months, years);
    m_control->updateDateLabel(m_curDate.getDate());
}
