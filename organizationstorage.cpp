#include "organizationstorage.h"
#include "ui_organizationstorage.h"

#include <QJsonDocument>
#include <QJsonObject>

#include <QFile>
#include <QMap>

#include "generalassetform.h"

OrganizationStorage::OrganizationStorage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrganizationStorage)
{
    ui->setupUi(this);

    QFile file(":/resources/weapon_info");
    if(!file.open(QFile::ReadOnly)){
        qDebug()<< "Error, Cannot open the file.";
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject root = doc.object();

    auto keys = root.keys();
    QMap<QString, GeneralAssetForm*> assets;
    foreach(auto weaponName, keys)
    {
        QJsonObject weapon = root.value(weaponName).toObject();
        assets.insert(weaponName, new GeneralAssetForm(this,
                                                    weaponName,
                                                    &weapon));
        ui->verticalLayout->addWidget(assets[weaponName]);
    }
    ui->verticalLayout->addSpacerItem(new QSpacerItem(10,10, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

OrganizationStorage::~OrganizationStorage()
{
    delete ui;
}
