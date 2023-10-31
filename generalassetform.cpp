#include "generalassetform.h"
#include "ui_generalassetform.h"

#include <QDebug>

#include "assetmanagement.h"


GeneralAssetForm::GeneralAssetForm(QWidget *parent)
{
    assetConstructor(parent);
}

GeneralAssetForm::GeneralAssetForm(QWidget *parent, QString weapon, QJsonObject* obj)
{
    assetConstructor(parent);

    // TODO: ammo, velocity etc are specific to weapon, needs refactoring to be more general somehow
    m_assetString = weapon;
    m_ammo = obj->value("ammo").toString();
    m_weight = obj->value("weight").toDouble();
    m_velocity = obj->value("velocity").toInt();
    m_firingRate = obj->value("firing_rate").toInt();
    m_effective = obj->value("effective").toInt();
    m_price = obj->value("price").toDouble();
    m_assetType = obj->value("type").toString();
    m_deliveryTime = obj->value("deliveryTime").toInt();

    updateContents();

    qDebug() << "Constructed asset form: " << weapon;
}

GeneralAssetForm::~GeneralAssetForm()
{
    delete ui;
}

void GeneralAssetForm::updatePendingToolTip()
{
    ui->pendingLabel->setToolTip(convertPendingAssetToText());
}

void GeneralAssetForm::updateContents()
{
    ui->weaponLabel->setText(m_assetString);
    ui->currentLabel->setText(QString::number(AssetManagement::getInstance()->getWeaponAssetCurrent(m_assetString), 'f', 0));
    ui->pendingLabel->setText(QString::number(AssetManagement::getInstance()->getWeaponAssetPending(m_assetString), 'f', 0));
    ui->priceLabel->setText("$" + QString::number(m_price));
    ui->weaponLabel->setToolTip(convertAssetToText());
    ui->pendingLabel->setToolTip(convertPendingAssetToText());
}

void GeneralAssetForm::on_acquireButton_pressed()
{
    // TODO: add pending functionality.
    if(AssetManagement::getInstance()->takeMoney(ui->amountSpinBox->value() * m_price))
    {
        AssetManagement::getInstance()->orderWeaponAsset(m_assetString, ui->amountSpinBox->value(), m_deliveryTime);
        updateContents();
    }
    else
    {
        qDebug() << "Not enough money!";
        // TODO: give message
    }
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
        qDebug() << "Unknown current asset type: " << m_assetType;
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
    weaponInfo += "Delivery time:\t" + QString::number(m_deliveryTime) + " days\n";
    return weaponInfo;
}

QString GeneralAssetForm::convertPendingAssetToText()
{
    QString assetInfo = "";
    if(m_assetType == "weapon")
    {
        assetInfo = convertPendingWeaponToText();
    }
    else
    {
        qDebug() << "Unknown pending type: " << m_assetType;
    }
    return assetInfo;
}

QString GeneralAssetForm::convertPendingWeaponToText()
{
    QString assetPending = "";
    QStringList list = AssetManagement::getInstance()->getWeaponAssetPendingDates(m_assetString);
    for(auto& element: list)
    {
        assetPending += element + '\n';
    }
    return assetPending;
}

