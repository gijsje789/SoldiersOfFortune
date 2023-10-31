#include "organizationstorage.h"
#include "ui_organizationstorage.h"

#include <QJsonDocument>
#include <QJsonObject>

#include <QFile>
#include <QMap>

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

    for(auto& weaponName: keys)
    {
        QJsonObject weapon = root.value(weaponName).toObject();
        m_assets.insert(weaponName, new GeneralAssetForm(this,
                                                    weaponName,
                                                    &weapon));
        connect(AssetManagement::getInstance(), &AssetManagement::assetsChanged, m_assets[weaponName], &GeneralAssetForm::updateContents);
        ui->verticalLayout->addWidget(m_assets[weaponName]);
    }
    ui->verticalLayout->addSpacerItem(new QSpacerItem(10,10, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

OrganizationStorage::~OrganizationStorage()
{
    delete ui;
}

void OrganizationStorage::updatePendingToolTips()
{
    for(auto& asset : m_assets)
    {
        asset->updatePendingToolTip();
    }
}
