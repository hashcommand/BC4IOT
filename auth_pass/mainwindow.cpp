#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QCryptographicHash>
#include <iostream>
#include <QTimer>
#include <sstream>

#define FAIL_TRANSAC "/home/umair/Documents/BC4IOT/img/pass_fail.png"
#define SUCC_TRANSAC "/home/umair/Documents/BC4IOT/img/pass_succ.png"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ecc (NULL)
{
    setupUi(this);
    setLogo("/home/umair/Documents/BC4IOT/img/pass.png");

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

    blockchain = new Blockchain(lineEdit_5->text(), lineEdit_6->text());
    blockchain->setMyExternalAddress(lineEdit->text());

    QString message00 = blockchain->EncodeUint8(lineEdit_2->text().toUInt(0, 16)); // SID
    QString message01 = blockchain->EncodeUint8(lineEdit_3->text().toUInt(0, 16)); // EID
    QString message02 = message00 + message01 ; // SID + EID
    QString message1 = QString(QCryptographicHash::hash((message02.toUtf8()),QCryptographicHash::Sha3_256).toHex());
    //QString messgae0 = "12345";
    //QString message1 = QString(QCryptographicHash::hash(("0x39"),QCryptographicHash::Keccak_256));
    QString message2 = "0x" + message1;
    //std::cout<<message2.toStdString()<<std::endl;
    //std::cout<<message.toStdString()<<std::endl;
    //std::cout<<message1.toStdString()<<std::endl;
    std::cout<<message2.toStdString()<<std::endl;
    signature = blockchain->getSignature(lineEdit->text(), message2);
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
