#include "mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <sstream>
#include <QCryptographicHash>
#include <string.h>
#include <iostream>
#include <QElapsedTimer>

#define SYS_REG_IMG "/home/umair/Documents/BC4IOT/img/device.png"
#define FAIL_TRANSAC "/home/umair/Documents/BC4IOT/img/device_fail.png"
#define SUCC_TRANSAC "/home/umair/Documents/BC4IOT/img/device_succ.png"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), blockchain (nullptr)
{
    setupUi(this) ;
    setLogo("/home/umair/Documents/BC4IOT/img/device.png") ;
}

void MainWindow::setLogo(QString imageFileName)
{
    labelPicture->setPixmap(QPixmap(imageFileName));
}

MainWindow::~MainWindow()
{

}

void MainWindow::on_commandLinkButton_clicked()
{

    QString transactionHash ;
    QString transactionHash1 ;
    QString warnings = "" ;
    //u_int64_t res = 0 ;



    blockchain = new Blockchain(lineEdit_1->text(), lineEdit_2->text());
    blockchain->setMyExternalAddress(lineEdit_7->text());
    blockchain->setContractAddress(lineEdit_3->text());



    QString     paramsTypes ("addEID(uint8,uint8,uint256,uint256,uint256)");
    QStringList paramsValues;

    //Calculating Message Hash
    QString message1 = QString(QCryptographicHash::hash((lineEdit_5->text().toUtf8()),QCryptographicHash::Sha3_256).toHex());
    QString message2 = message1;

    QString token = textEdit_1->toPlainText();

    QString const r = token.mid(0,64);
    QString const s = token.mid(64,128).mid(0,64);
    QString const v = token.mid(128,130);


    paramsValues.append (blockchain->EncodeUint8(lineEdit_4->text().toUInt(0, 16))); //EID (uint8)
    paramsValues.append (blockchain->EncodeUint8(lineEdit_5->text().toUInt(0, 16))); //SID (uint8)
    paramsValues.append (blockchain->EncodeUint256((const QString) message2)); //HASH (uint256)
    paramsValues.append (blockchain->EncodeUint256((const QString) r)); //r (uint256)
    paramsValues.append (blockchain->EncodeUint256((const QString) s)); //s (uint256)



    //Getting Time of Execution
            QElapsedTimer timer1;
            timer1.start();

    transactionHash = blockchain->CallFunction(blockchain->getMyExternalAddress(),
                                               blockchain->getContractAddress(),
                                               blockchain->EncodeFunction(blockchain->EncodeFunctionSelector("addEID(uint8,uint8,uint256,uint256,uint256)"),
                                                                            paramsTypes,
                                                                            paramsValues),
                                               "eth_sendTransaction"
                                               );

    qDebug() << "Function Execution Time:" << timer1.elapsed();

    qDebug() << transactionHash ;
    paramsValues.clear() ;
    paramsTypes = "" ;

    if  (transactionHash != "") {
        labelPicture->setPixmap(QPixmap(SUCC_TRANSAC)) ;
        this->setMinimumHeight(480) ;
    } else {
        labelPicture->setPixmap(QPixmap(FAIL_TRANSAC)) ;
    }

}
