#ifndef ORGANIZATIONSTORAGE_H
#define ORGANIZATIONSTORAGE_H

#include <QWidget>

namespace Ui {
class OrganizationStorage;
}

class OrganizationStorage : public QWidget
{
    Q_OBJECT

public:
    explicit OrganizationStorage(QWidget *parent = nullptr);
    ~OrganizationStorage();

private:
    Ui::OrganizationStorage *ui;
};

#endif // ORGANIZATIONSTORAGE_H
