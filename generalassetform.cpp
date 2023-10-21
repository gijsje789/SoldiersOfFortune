#include "generalassetform.h"
#include "ui_generalassetform.h"

#include <QDebug>

#include "assetmanagement.h"


GeneralAssetForm::GeneralAssetForm(QWidget *parent)
{
    assetConstructor(parent);
}

GeneralAssetForm::GeneralAssetForm(QWidget *parent, QString weapon, QJsonObject* obj):
    m_assetString(weapon)
{
    assetConstructor(parent);

    m_ammo = obj->value("ammo").toString();
    m_weight = obj->value("weight").toDouble();
    m_velocity = obj->value("velocity").toInt();
    m_firingRate = obj->value("firing_rate").toInt();
    m_effective = obj->value("effective").toInt();
    m_price = obj->value("price").toDouble();

    ui->weaponLabel->setToolTip(convertAssetToText());
    ui->weaponLabel->setText(weapon);
    ui->currentLabel->setText(QString::number(AssetManagement::getInstance()->getWeaponAssetCurrent(m_assetString), 'f', 0));
    ui->pendingLabel->setText(QString::number(0, 'f', 0));
    ui->priceLabel->setText("$" + QString::number(m_price));
    qDebug() << "Constructed asset form: " << weapon;
}

GeneralAssetForm::~GeneralAssetForm()
{
    delete ui;
}

void GeneralAssetForm::on_acquireButton_pressed()
{
    // TODO: add pending functionality.
    AssetManagement::getInstance()->addweaponAsset(m_assetString, ui->amountSpinBox->value());
    ui->currentLabel->setText(QString::number(AssetManagement::getInstance()->getWeaponAssetCurrent(m_assetString), 'f', 0));
    qDebug() << "Amount: " << ui->amountSpinBox->value();
    qDebug() << "AssetObject: " << m_price;
    AssetManagement::getInstance()->takeMoney(ui->amountSpinBox->value() * m_price);
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
    if(m_assetType == "weapon")
    {
        assetInfo = convertWeaponToText();
    }
    else
    {
        qDebug() << "Unknown type: " << m_assetType;
    }
    return assetInfo;
}

QString GeneralAssetForm::convertWeaponToText()
{
    QString weaponInfo = "";
    weaponInfo += "Ammo:\t\t" + m_ammo + "\n";
    weaponInfo += "Weight:\t\t" + QString::number(m_weight, 'f', 2) + " kg\n";
    weaponInfo += "Muzzle velocity:\t" + QString::number(m_velocity) + " m/s\n";
    weaponInfo += "Firing rate:\t" + QString::number(m_firingRate) + " rpm\n";
    weaponInfo += "Effective range:\t" + QString::number(m_effective) + " m\n";
    return weaponInfo;
}

