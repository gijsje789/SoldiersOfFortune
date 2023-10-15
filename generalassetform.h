#ifndef GENERALASSETFORM_H
#define GENERALASSETFORM_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>

namespace Ui {
class GeneralAssetForm;
}

class GeneralAssetForm : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralAssetForm(QWidget *parent = nullptr);
    GeneralAssetForm(QWidget *parent, QString weapon, QJsonObject &obj, int current, int pending);
    ~GeneralAssetForm();

private slots:
    void on_acquireButton_pressed();

private:
    Ui::GeneralAssetForm *ui;
    void AssetConstructor(QWidget *parent);
    QString ConvertWeaponToText(QJsonObject &weapon);
};

#endif // GENERALASSETFORM_H