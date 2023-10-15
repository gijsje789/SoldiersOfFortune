#include "generalassetform.h"
#include "ui_generalassetform.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>

GeneralAssetForm::GeneralAssetForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneralAssetForm)
{
    ui->setupUi(this);
}

GeneralAssetForm::~GeneralAssetForm()
{
    delete ui;
}

void GeneralAssetForm::on_acquireButton_pressed()
{
    QFile file(":/resources/weapon_info");
    if(!file.open(QFile::ReadOnly)){
        qDebug()<< "Error, Cannot open the file.";
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject root = doc.object();
    qDebug() << "weapon: " << root.value("m4");
    qDebug() << "ammo: " << root.value("m4").toObject().value("ammo").toString();
//    foreach(QJsonValue element, root["CELLS"].toArray()){
//        QJsonObject node = element.toObject();
//        node["whatEver"];

//    }
}

