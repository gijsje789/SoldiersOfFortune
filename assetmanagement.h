#ifndef ASSETMANAGEMENT_H
#define ASSETMANAGEMENT_H

#include <QMap>

#include "gamecontrol.h"
#include "date.h"


struct pendingAsset {
    QString name;
    int amount;
    QString arrivalTime;
};

class AssetManagement : public QObject
{
    Q_OBJECT
public:
    AssetManagement(const AssetManagement& obj) = delete;

    static AssetManagement* getInstance();
    void orderWeaponAsset(QString name, int number, int delayInDays);
    void addWeaponAsset(QString name, int number);
    int getWeaponAssetCurrent(QString name);
    int getWeaponAssetPending(QString name);
    QStringList getWeaponAssetPendingDates(QString name);
    void quit();
    void saveGame(QString dir);
    bool loadGame(QString dir);
    bool takeMoney(double value);
    void addMoney(double value);
    double getMoney();
    void setMoney(double value);
    void setStartingDate(QString date);

private:
    AssetManagement();
    static AssetManagement* m_instancePtr;

    double m_money;
    Date m_curDate;
    Date m_startDate;

    QMap<QString, double> m_weaponAssets;
    QList<pendingAsset> m_pendingWeapons;
    void saveWeaponAssetsToFile(QString dir);
    void loadWeaponAssetsFromFile(QString dir);
    void savePendingWeaponAssetsToFile(QString dir);
    void loadPendingWeaponAssetsFromFile(QString dir);
    void saveGameInfoToFile(QString dir);
    void loadGameInfoFromFile(QString dir);
    void checkPendingAssets();
    void checkPendingWeapons();

signals:
    void dateChanged(QString newDate);
    void moneyChanged(double value);

public slots:
    void advanceTime(int days, int months = 0, int years = 0);

};

#endif // ASSETMANAGEMENT_H
