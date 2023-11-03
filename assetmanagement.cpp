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
        for(auto& element: m_weaponAssets.keys())
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
        QString line = "";
        while(!input.atEnd())
        {
            line = input.readLine().trimmed();
            QStringList list =  line.split(',');
            addWeaponAsset(list[0], list[1].toInt());
        }
    }
    else
    {
        qDebug() << "File not open: " << file;
    }
}

void AssetManagement::savePendingWeaponAssetsToFile(QString dir)
{
    QString file = QDir(dir).filePath("pendingWeapons.csv");

    QFile output = QFile(file);
    output.open(QIODeviceBase::WriteOnly);
    if(output.isOpen())
    {
        for(auto& element: m_pendingWeapons)
        {
            QString temp1 = element.name;
            QString temp2 = QString::number(element.amount, 'f', 0);
            QString temp3 = element.arrivalTime;
            QString temp4 = QString('\n');
            output.write((temp1 + ',' + temp2 + ',' + temp3 + temp4).toStdString().c_str());
        }
    }
}

void AssetManagement::loadPendingWeaponAssetsFromFile(QString dir)
{
    QString file = QDir(dir).filePath("pendingWeapons.csv");

    QFile input = QFile(file);
    input.open(QIODeviceBase::ReadOnly);
    if(input.isOpen())
    {
        QString line = "";
        while(!input.atEnd())
        {
            line = input.readLine().trimmed();
            QStringList list =  line.split(',');
            pendingAsset asset = {list[0], list[1].toInt(), list[2]};
            m_pendingWeapons.append(asset);
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
                emit dateChanged(m_curDate.getDate());
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

void AssetManagement::orderWeaponAsset(QString name, int number, int delayInDays)
{
    Date arrivalTime = m_curDate + delayInDays;
    for(pendingAsset& element: m_pendingWeapons)
    {
        if(element.name == name)
        {
            // Found an element with the same name
            if(element.arrivalTime == arrivalTime.getDate())
            {
                // found an element with the same arrival date, so can be combined.
                element.amount += number;
                return;
            }
            else
            {
                continue;
            }
        }
    }
    pendingAsset data = {name, number, arrivalTime.getDate()};
    m_pendingWeapons.append(data);
}

void AssetManagement::addWeaponAsset(QString name, int number)
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

int AssetManagement::getWeaponAssetCurrent(QString name)
{
    int rval = 0;
    if(m_weaponAssets.contains(name))
    {
        rval = m_weaponAssets[name];
    }
    return rval;
}

int AssetManagement::getWeaponAssetPending(QString name)
{
    int rval = 0;
    for(auto& element: m_pendingWeapons)
    {
        if(element.name == name)
        {
            rval += element.amount;
        }
    }
    return rval;
}

QStringList AssetManagement::getWeaponAssetPendingDates(QString name)
{
    QStringList rval = {};
    for(auto& element: m_pendingWeapons)
    {
        if(element.name == name)
        {
            rval.append(element.arrivalTime + ": " + QString::number(element.amount));
        }
    }
    return rval;
}

void AssetManagement::checkPendingAssets()
{
    checkPendingWeapons();
}

void AssetManagement::checkPendingWeapons()
{
    int i = 0;
    for(auto& order : m_pendingWeapons)
    {
        if(m_curDate > order.arrivalTime)
        {
            addWeaponAsset(order.name, order.amount);
            m_pendingWeapons.removeAt(i);
            // do not increment i here, when asset is removed the list shifts.
            // e.g. asset[1] is removed, then asset[2] is shifted to asset[1] position
            // which still needs to be checked in the next iteration of the loop.
        }
        else
        {
            i++;
        }
    }
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
    savePendingWeaponAssetsToFile(dir);
    saveGameInfoToFile(dir);
}

bool AssetManagement::loadGame(QString dir)
{
    bool rval = false;
    if(QDir(dir).exists())
    {
        loadWeaponAssetsFromFile(dir);
        loadPendingWeaponAssetsFromFile(dir);
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
    emit moneyChanged(m_money);
    return rval;
}

void AssetManagement::addMoney(double value)
{
    m_money += value;
    emit moneyChanged(m_money);
}

double AssetManagement::getMoney()
{
    return m_money;
}

void AssetManagement::setMoney(double value)
{
    m_money = value;
    emit moneyChanged(m_money);
}

void AssetManagement::setStartingDate(QString date)
{
    m_curDate.setDate(date);
    m_startDate.setDate(date);
    emit dateChanged(m_curDate.getDate());
}

void AssetManagement::advanceGameTime(int days, int months, int years)
{
    m_curDate.addTime(days, months, years);
    emit dateChanged(m_curDate.getDate());
    checkPendingAssets();
    emit assetsChanged();
}
