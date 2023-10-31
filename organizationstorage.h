#ifndef ORGANIZATIONSTORAGE_H
#define ORGANIZATIONSTORAGE_H

#include <QWidget>

#include "generalassetform.h"
#include "assetmanagement.h"

namespace Ui {
class OrganizationStorage;
}

class OrganizationStorage : public QWidget
{
    Q_OBJECT

public:
    explicit OrganizationStorage(QWidget *parent = nullptr);
    ~OrganizationStorage();
    void updatePendingToolTips();

private:
    Ui::OrganizationStorage *ui;

    QMap<QString, GeneralAssetForm*> m_assets;
};

#endif // ORGANIZATIONSTORAGE_H
