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
    GeneralAssetForm(QWidget *parent, QString weapon, QJsonObject* obj);
    ~GeneralAssetForm();

private slots:
    void on_acquireButton_pressed();

private:
    Ui::GeneralAssetForm *ui;
    QJsonObject* m_assetObject;
    QString m_assetString;


    void assetConstructor(QWidget *parent);
    QString convertAssetToText();
    QString convertWeaponToText();
};

#endif // GENERALASSETFORM_H
