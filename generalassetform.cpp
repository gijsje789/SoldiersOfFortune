#include "generalassetform.h"
#include "ui_generalassetform.h"

#include <QDebug>

GeneralAssetForm::GeneralAssetForm(QWidget *parent)
{
    AssetConstructor(parent);
}

GeneralAssetForm::GeneralAssetForm(QWidget *parent, QString weapon, QJsonObject* obj, int current, int pending):
    m_assetString(weapon),
    m_assetObject(obj)
{
    AssetConstructor(parent);

    ui->weaponLabel->setToolTip(ConvertAssetToText());
    ui->weaponLabel->setText(weapon);
    ui->currentLabel->setText(QString::number(current));
    ui->pendingLabel->setText(QString::number(pending));
    ui->priceLabel->setText("$" + QString::number(m_assetObject->value("price").toDouble()));
}



GeneralAssetForm::~GeneralAssetForm()
{
    delete ui;
}

void GeneralAssetForm::on_acquireButton_pressed()
{

}

void GeneralAssetForm::AssetConstructor(QWidget *parent)
{
    this->setParent(parent);
    ui = new Ui::GeneralAssetForm;
    ui->setupUi(this);
}

QString GeneralAssetForm::ConvertAssetToText()
{
    QString assetInfo = "";
    if(m_assetObject->value("type").toString() == "weapon")
    {
        assetInfo = ConvertWeaponToText();
    }
    else
    {
        qDebug() << "Unknown type: " << m_assetObject->value("type").toString();
    }
    return assetInfo;
}

QString GeneralAssetForm::ConvertWeaponToText()
{
    QString weaponInfo = "";
    foreach(auto element, m_assetObject->keys())
    {
        if(element == "type")
        {
            continue;
        }

        if(element == "ammo")
        {
            weaponInfo += "Ammo:\t\t" + m_assetObject->value(element).toString();
        }
        else if(element == "weight")
        {
            weaponInfo += "Weight:\t\t" + QString::number(m_assetObject->value(element).toDouble()) + " kg";
        }
        else if(element == "velocity")
        {
            weaponInfo += "Muzzle velocity:\t" + QString::number(m_assetObject->value(element).toDouble()) + " m/s";
        }
        else if(element == "firing_rate")
        {
            weaponInfo += "Firing rate:\t" + QString::number(m_assetObject->value(element).toDouble()) + " rpm";
        }
        else if(element == "effective")
        {
            weaponInfo += "Effective range:\t" + QString::number(m_assetObject->value(element).toDouble()) + " m";
        }
        weaponInfo += "\n";
    }
    return weaponInfo;
}

