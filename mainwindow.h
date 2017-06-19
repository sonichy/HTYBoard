#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QToolButton *TBForegroundColor,*TBBackgroundColor;    
    QTimer *timer;
    QString path;

private slots:
    void on_actionQuit_triggered();
    void on_actionAbout_triggered();
    void on_actionRun_triggered();
    void on_actionFont_triggered();
    void on_actionImage_triggered();
    void setForegroundColor();
    void setBackgroundColor();
    void exitRun();
    void updateString();
};

#endif // MAINWINDOW_H
