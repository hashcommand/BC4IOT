#include "mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <sstream>
#include <QCryptographicHash>
#include <iostream>
#include <chrono>
#include <ctime>
#include "Rapl.h"

#define SYS_REG_IMG "/home/umair/Documents/BC4IOT/img/sys_reg.png"
#define FAIL_TRANSAC "/home/umair/Documents/BC4IOT/img/sys_reg_fail.png"
#define SUCC_TRANSAC "/home/umair/Documents/BC4IOT/img/sys_reg_succ.png"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), blockchain (nullptr), rapl (nullptr)
{
    setupUi(this) ;
    setLogo("/home/umair/Documents/BC4IOT/img/sys_reg.png") ;
}

MainWindow::~MainWindow()
{

}

void MainWindow::setLogo(QString imageFileName)
{
    labelPicture->setPixmap(QPixmap(imageFileName));
}

void MainWindow::on_pushButton_clicked()
{
    QCryptographicHash CalculateMd5 (QCryptographicHash::Md5);
    QByteArray input;
    input.append(lineEdit_5->text());
    CalculateMd5.addData(input);
    lineEdit_7->setText(lineEdit_6->text() + CalculateMd5.result().toHex().mid(27));
}

//Rapl r1;


void MainWindow::on_commandLinkButton_clicked()
{
        QString transactionHash ;
        QString warnings = "" ;
        QString gasEstimate;
        u_int64_t res = 0 ;

        blockchain = new Blockchain(lineEdit_1->text(), lineEdit_2->text());
        blockchain->setMyExternalAddress(lineEdit_4->text());
        blockchain->setContractAddress(lineEdit_3->text());

        QString     paramsType ("uint8") ;
        QStringList paramsValue ;

        paramsValue.append (blockchain->EncodeUint8(lineEdit_7->text().toUInt(0, 16))); //SID

        //double begin = r1.current_time();

        transactionHash = blockchain->CallFunction(blockchain->getMyExternalAddress(),
                                                   blockchain->getContractAddress(),
                                                   blockchain->EncodeFunction(blockchain->EncodeFunctionSelector("addSID(uint8)"),
                                                                                paramsType,
                                                                                paramsValue),
                                                   blockchain->getGasEstimate(
                                                       blockchain->getMyExternalAddress(),
                                                       blockchain->getContractAddress(),
                                                       blockchain->EncodeFunction(blockchain->EncodeFunctionSelector("addSID(uint8)"),paramsType,paramsValue)
                                                       ),
                                                   "eth_sendTransaction"
                                                   );
        //double end =r1.current_time();
        //double Total = end - begin;
        //std::cout << begin;

        //qDebug() << transactionHash;
        paramsValue.clear() ;
        paramsType = "" ;

    if  (transactionHash != "") {
        labelPicture->setPixmap(QPixmap(SUCC_TRANSAC)) ;
    } else {
        labelPicture->setPixmap(QPixmap(FAIL_TRANSAC)) ;
    }

}




