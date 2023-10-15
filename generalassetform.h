#ifndef GENERALASSETFORM_H
#define GENERALASSETFORM_H

#include <QWidget>

namespace Ui {
class GeneralAssetForm;
}

class GeneralAssetForm : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralAssetForm(QWidget *parent = nullptr);
    ~GeneralAssetForm();

private slots:
    void on_acquireButton_pressed();

private:
    Ui::GeneralAssetForm *ui;
};

#endif // GENERALASSETFORM_H
