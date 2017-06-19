#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QFontDialog>
#include <QDesktopWidget>
#include <QShortcut>
#include <QColorDialog>
#include <QColor>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->hide();
    move((QApplication::desktop()->width() - width())/2, (QApplication::desktop()->height() - height())/2);
    TBForegroundColor = new QToolButton(this);
    TBForegroundColor->setText("字");
    TBForegroundColor->setToolTip("文字颜色");
    ui->mainToolBar->addWidget(TBForegroundColor);
    TBBackgroundColor = new QToolButton(this);
    TBBackgroundColor->setText("■");
    TBBackgroundColor->setToolTip("背景颜色");
    ui->mainToolBar->addWidget(TBBackgroundColor);
    ui->actionFont->setText(ui->textEdit->font().family()+","+QString::number(ui->textEdit->font().pointSize()));
    //ui->textEdit->setText("海天鹰电子黑板");
    ui->textEdit->setText("冰冰冰冰我爱你，就像老鼠爱大米！");
    QPixmap pixmap;
    path="bg.jpg";
    pixmap.load(path);
    ui->labelImage->setPixmap(QPixmap(path));
    ui->labelImage->resize(pixmap.size());
    QPalette plt;
    plt.setColor(QPalette::WindowText, Qt::white);
    //ui->textEdit->setPalette(plt);
    ui->label->setPalette(plt);
    plt.setColor(QPalette::Background, Qt::black);
    ui->centralWidget->setPalette(plt);
    //ui->textEdit->setPalette(plt);
    connect(new QShortcut(QKeySequence(Qt::Key_Escape),this), SIGNAL(activated()),this, SLOT(exitRun()));
    connect(TBForegroundColor,SIGNAL(clicked()),this,SLOT(setForegroundColor()));
    connect(TBBackgroundColor,SIGNAL(clicked()),this,SLOT(setBackgroundColor()));
    timer=new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateString()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox aboutMB(QMessageBox::NoIcon, "关于", "海天鹰电子黑板 1.0\n一款基于 Qt 的电子黑板。\n作者：黄颖\nE-mail: sonichy@163.com\n主页：sonichy.96.lt");
    aboutMB.setIconPixmap(QPixmap(":/icon.png"));
    aboutMB.exec();
}

void MainWindow::on_actionRun_triggered()
{
    showFullScreen();
    setCursor(Qt::BlankCursor);
    ui->menuBar->hide();
    ui->mainToolBar->hide();
    ui->textEdit->hide();    
    ui->label->show();    
    ui->label->setText(ui->textEdit->toPlainText());
    ui->label->adjustSize();
    ui->label->move(QApplication::desktop()->width(),0);
    timer->start();
}

void MainWindow::exitRun()
{
    showNormal();
    setCursor(Qt::ArrowCursor);
    ui->menuBar->show();
    ui->mainToolBar->show();
    ui->textEdit->show();
    ui->label->hide();
    timer->stop();
}

void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, ui->textEdit->font(), this, "选择字体");
    if(ok)
    {
       ui->textEdit->setFont(font);
       ui->actionFont->setText(ui->textEdit->font().family() + "," + QString::number(ui->textEdit->font().pointSize()));
       ui->label->setText(ui->textEdit->toPlainText());
       ui->label->setFont(font);
       ui->label->adjustSize();
    }
}

void MainWindow::setForegroundColor()
{
    QPalette plt= TBForegroundColor->palette();
    QBrush brush = plt.color(QPalette::ButtonText);
    QColor color = QColorDialog::getColor(brush.color(), this);
    plt.setColor(QPalette::ButtonText, color);
    TBForegroundColor->setPalette(plt);
    //plt = ui->textEdit->palette();
    plt.setColor(QPalette::Text, color);
    ui->textEdit->setPalette(plt);
    //QPalette pl;
    plt.setColor(QPalette::WindowText, color);
    ui->label->setPalette(plt);
}

void MainWindow::setBackgroundColor()
{
    QPalette plt = TBBackgroundColor->palette();
    QBrush brush = plt.color(QPalette::ButtonText);
    QColor color = QColorDialog::getColor(brush.color(), this);
    plt.setColor(QPalette::ButtonText, color);
    TBBackgroundColor->setPalette(plt);
    plt.setColor(QPalette::Background, color);
    ui->textEdit->setPalette(plt);
    ui->centralWidget->setPalette(plt);
}

void MainWindow::on_actionImage_triggered()
{
    if(path==""){
        path = QFileDialog::getOpenFileName(this,"导入图片", ".", "图片文件(*.jpg *.png *.bmp)");
    }else{
        path = QFileDialog::getOpenFileName(this,"导入图片", path, "图片文件(*.jpg *.png *.bmp)");
    }
    QPixmap pixmap;
    pixmap.load(path);
    ui->labelImage->setPixmap(QPixmap(path));
    ui->labelImage->resize(pixmap.size());
}

void MainWindow::updateString()
{
    if(ui->label->x()+ui->label->width()>0){
        ui->label->move(ui->label->x()-5,ui->label->y());
    }else{
        ui->label->move(QApplication::desktop()->width(),ui->label->y()+ui->label->height());
    }
    if(ui->label->y()>QApplication::desktop()->height()){
        ui->label->move(ui->label->x(),0);
    }
//    if(ui->label->isVisible()){
//        ui->label->setVisible(false);
//    }else{
//        ui->label->setVisible(true);
//    }
}

