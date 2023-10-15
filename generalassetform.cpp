#include "generalassetform.h"
#include "ui_generalassetform.h"

GeneralAssetForm::GeneralAssetForm(QWidget *parent)
{
    AssetConstructor(parent);
}

GeneralAssetForm::GeneralAssetForm(QWidget *parent, QString weapon, QJsonObject &obj, int current, int pending)
{
    AssetConstructor(parent);

    ui->weaponLabel->setToolTip(ConvertWeaponToText(obj));
    ui->weaponLabel->setText(weapon);
    ui->currentLabel->setText(QString::number(current));
    ui->pendingLabel->setText(QString::number(pending));
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

QString GeneralAssetForm::ConvertWeaponToText(QJsonObject &weapon)
{
    QString weaponInfo = "";
    foreach(auto element, weapon.keys())
    {
        if(element == "ammo")
        {
            weaponInfo += "Ammo:\t" + weapon[element].toString();
        }
        else if(element == "weight")
        {
            weaponInfo += "Weight:\t" + QString::number(weapon[element].toDouble()) + " kg";
        }
        else if(element == "velocity")
        {
            weaponInfo += "Muzzle velocity:\t" + QString::number(weapon[element].toDouble()) + " m/s";

        }
        else if(element == "firing_rate")
        {
            weaponInfo += "Firing rate:\t" + QString::number(weapon[element].toDouble()) + " rpm";

        }
        else if(element == "effective")
        {
            weaponInfo += "Effective range:\t" + QString::number(weapon[element].toDouble()) + " m";

        }
        weaponInfo += "\n";
    }
    //QString ammo = QString("ammo:\t") + weapon.value("ammo").toString() + "\n";
    //QString mass = QString("Weight: ") + weapon.value("weight")
    //qDebug() << weaponInfo;
    return weaponInfo;
}

