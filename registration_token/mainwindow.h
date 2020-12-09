#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "ECC.h"
#include "blockchain.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void    setLogo(QString imageFileName) ;
private slots:
    void on_commandLinkButton_clicked();

private:
    ECC * ecc ;
    Blockchain * blockchain ;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
