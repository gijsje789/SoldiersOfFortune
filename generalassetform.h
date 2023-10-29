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
    QString m_assetString;
    QString m_assetType;

    // Weapon specific
    QString m_ammo;
    double m_weight;
    int m_velocity;
    int m_firingRate;
    int m_effective;
    double m_price;
    int m_deliveryTime;

    void assetConstructor(QWidget *parent);
    QString convertAssetToText();
    QString convertWeaponToText();
    QString convertPendingAssetToText();
    QString convertPendingWeaponToText();
};

#endif // GENERALASSETFORM_H
