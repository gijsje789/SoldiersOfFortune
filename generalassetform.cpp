#include "generalassetform.h"
#include "ui_generalassetform.h"

#include <QDebug>

#include "assetmanagement.h"


GeneralAssetForm::GeneralAssetForm(QWidget *parent)
{
    assetConstructor(parent);
}

GeneralAssetForm::GeneralAssetForm(QWidget *parent, QString weapon, QJsonObject* obj):
    m_assetString(weapon),
    m_assetObject(obj)
{
    assetConstructor(parent);

    ui->weaponLabel->setToolTip(convertAssetToText());
    ui->weaponLabel->setText(weapon);
    ui->currentLabel->setText(QString::number(AssetManagement::getInstance()->getWeaponAssetCurrent(m_assetString), 'f', 0));
    ui->pendingLabel->setText(QString::number(0, 'f', 0));
    ui->priceLabel->setText("$" + QString::number(m_assetObject->value("price").toDouble()));
}



GeneralAssetForm::~GeneralAssetForm()
{
    delete ui;
}

void GeneralAssetForm::on_acquireButton_pressed()
{
    AssetManagement::getInstance()->addweaponAsset(m_assetString, ui->amountSpinBox->value());
    ui->currentLabel->setText(QString::number(AssetManagement::getInstance()->getWeaponAssetCurrent(m_assetString), 'f', 0));
}

void GeneralAssetForm::assetConstructor(QWidget *parent)
{
    this->setParent(parent);
    ui = new Ui::GeneralAssetForm;
    ui->setupUi(this);
}

QString GeneralAssetForm::convertAssetToText()
{
    QString assetInfo = "";
    if(m_assetObject->value("type").toString() == "weapon")
    {
        assetInfo = convertWeaponToText();
    }
    else
    {
        qDebug() << "Unknown type: " << m_assetObject->value("type").toString();
    }
    return assetInfo;
}

QString GeneralAssetForm::convertWeaponToText()
{
    QString weaponInfo = "";
    foreach(auto element, m_assetObject->keys())
    {
        if(element == "ammo")
        {
            weaponInfo += "Ammo:\t\t" + m_assetObject->value(element).toString() + "\n";
        }
        else if(element == "weight")
        {
            weaponInfo += "Weight:\t\t" + QString::number(m_assetObject->value(element).toDouble()) + " kg\n";
        }
        else if(element == "velocity")
        {
            weaponInfo += "Muzzle velocity:\t" + QString::number(m_assetObject->value(element).toDouble()) + " m/s\n";
        }
        else if(element == "firing_rate")
        {
            weaponInfo += "Firing rate:\t" + QString::number(m_assetObject->value(element).toDouble()) + " rpm\n";
        }
        else if(element == "effective")
        {
            weaponInfo += "Effective range:\t" + QString::number(m_assetObject->value(element).toDouble()) + " m\n";
        }
    }
    return weaponInfo;
}

