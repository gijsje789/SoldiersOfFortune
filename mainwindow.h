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

    void updateMoney(double value);
    void newGame();

    void quit();
    void settings();
    void loadGame();
    void saveGame();
private slots:
    void on_actionStorage_triggered();

    void on_actionSave_game_triggered();

private:
    Ui::MainWindow *ui;

    QWidget* centralWidget;
    QLabel* moneyLabel;

    QString convertNumberToDollarString(double value);
    void enableMenuBar(bool value);
    void switchCentralWidget(QWidget* newWidget);
};
#endif // MAINWINDOW_H
