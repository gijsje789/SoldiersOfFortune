#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void UpdateMoney(double value);

private slots:
    void on_actionStorage_triggered();

private:
    Ui::MainWindow *ui;

    QWidget* centralWidget;
    QLabel* moneyLabel;

    QString ConvertNumberToDollarString(double value);
};
#endif // MAINWINDOW_H
