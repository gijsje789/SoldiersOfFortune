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
    foreach(auto element, keys)
    {
        QJsonObject weapon = root.value(element).toObject();
        assets.insert(element, new GeneralAssetForm(this,
                                                    element,
                                                    weapon,
                                                    0,
                                                    0));
        ui->verticalLayout->addWidget(assets[element]);
    }
}

OrganizationStorage::~OrganizationStorage()
{
    delete ui;
}
