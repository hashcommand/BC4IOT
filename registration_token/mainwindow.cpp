#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QCryptographicHash>
#include <iostream>
#include <QTimer>
#include <sstream>
#include <QElapsedTimer>

#define FAIL_TRANSAC "/home/umair/Documents/BC4IOT/img/token_fail.png"
#define SUCC_TRANSAC "/home/umair/Documents/BC4IOT/img/token_succ.png"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ecc (NULL)
{
    setupUi(this);
    setLogo("/home/umair/Documents/BC4IOT/img/token.png");
    //labelPicture->setPixmap(QPixmap("/home/umair/Documents/BC4IOT/img/token.png"));

    ecc = new ECC (uECC_secp256k1()) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setLogo(QString imageFileName)
{
    labelPicture->setPixmap(QPixmap(imageFileName));
}

void MainWindow::on_commandLinkButton_clicked()
{

    QString signature ;

    blockchain = new Blockchain(lineEdit->text(), lineEdit_6->text());
    blockchain->setMyExternalAddress(lineEdit_5->text());

    QString message = blockchain->EncodeUint8(lineEdit_2->text().toUInt(0, 16)); //+ lineEdit_4->text();
    QString message1 = QString(QCryptographicHash::hash((lineEdit_2->text().toUtf8()),QCryptographicHash::Sha3_256).toHex());
    //QString messgae0 = "12345";
    //QString message1 = QString(QCryptographicHash::hash(("0x39"),QCryptographicHash::Keccak_256));
    QString message2 = "0x" + message1;
    //std::cout<<message2.toStdString()<<std::endl;
    //std::cout<<message.toStdString()<<std::endl;
    //std::cout<<message1.toStdString()<<std::endl;
    //std::cout<<message2.toStdString()<<std::endl;

    //Getting Time of Execution
            QElapsedTimer timer;
            timer.start();

    signature = blockchain->getSignature(lineEdit_5->text(), message2);

    qDebug() << "Function Execution Time:" << timer.elapsed();

    QString final_Signature = signature;
    //qDebug() << signature;
    textEdit->setText(final_Signature);

    if  (final_Signature !=0) {
        labelPicture->setPixmap(QPixmap(SUCC_TRANSAC)) ;
        this->setMinimumHeight(480) ;
    } else {
        labelPicture->setPixmap(QPixmap(FAIL_TRANSAC)) ;
    }
}
