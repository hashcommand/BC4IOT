#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <time.h>
#include <QStringListModel>
#include "ui_mainwindow.h"
#include "blockchain.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow , private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void    setLogo(QString imageFileName) ;
    int32_t FromQStringToUint8(u_int8_t * bytes, int32_t bytesLen, const QString& strArray) ;
    void    Print_uint8 (const char * title, u_int8_t * data, int32_t dataLen) ;

private slots:
    void on_commandLinkButton_clicked();

private:
    Blockchain * blockchain ;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
