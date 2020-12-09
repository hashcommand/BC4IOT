#include "mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <sstream>
#include <QCryptographicHash>
#include <string.h>

#define SYS_REG_IMG "/home/umair/Documents/BC4IOT/img/auth.png"
#define FAIL_TRANSAC "/home/umair/Documents/BC4IOT/img/auth_fail.png"
#define SUCC_TRANSAC "/home/umair/Documents/BC4IOT/img/auth_succ.png"

MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent), blockchain (nullptr)
{
    setupUi(this) ;
    setLogo("/home/umair/Documents/BC4IOT/img/auth.png") ;
}

void MainWindow::setLogo(QString imageFileName)
{
    labelPicture->setPixmap(QPixmap(imageFileName));
}

MainWindow::~MainWindow()
{
    delete ui;
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

    QString     paramsTypes ("deviceAuth(uint8,uint8,uint256,uint256,uint256)");
    QStringList paramsValues;

    //Calculating Message Hash
    QString message00 = blockchain->EncodeUint8(lineEdit_5->text().toUInt(0, 16)); // SID
    QString message01 = blockchain->EncodeUint8(lineEdit_4->text().toUInt(0, 16)); // EID
    QString message02 = message00 + message01 ; // SID + EID
    QString message1 = QString(QCryptographicHash::hash((message02.toUtf8()),QCryptographicHash::Sha3_256).toHex());
    QString message2 = message1;

    QString token = textEdit_1->toPlainText();

    QString const r = token.mid(0,64);
    QString const s = token.mid(64,128).mid(0,64);
    QString const v = token.mid(128,130);

    qDebug() << r;
    qDebug() << s;
    qDebug() << v;
    qDebug() << message2;

    paramsValues.append (blockchain->EncodeUint8(lineEdit_4->text().toUInt(0, 16))); //EID (uint8)
    paramsValues.append (blockchain->EncodeUint8(lineEdit_5->text().toUInt(0, 16))); //SID (uint8)
    paramsValues.append (blockchain->EncodeUint256((const QString) message2)); //HASH (uint256)
    paramsValues.append (blockchain->EncodeUint256((const QString) r)); //r (uint256)
    paramsValues.append (blockchain->EncodeUint256((const QString) s)); //s (uint256)

    transactionHash = blockchain->CallFunction(blockchain->getMyExternalAddress(),
                                               blockchain->getContractAddress(),
                                               blockchain->EncodeFunction(blockchain->EncodeFunctionSelector("deviceAuth(uint8,uint8,uint256,uint256,uint256)"),
                                                                            paramsTypes,
                                                                            paramsValues),
                                               blockchain->getGasEstimate(
                                                   blockchain->getMyExternalAddress(),
                                                   blockchain->getContractAddress(),
                                                   blockchain->EncodeFunction(blockchain->EncodeFunctionSelector("deviceAuth(uint8,uint8,uint256,uint256,uint256)"),paramsTypes,paramsValues)
                                                   ),
                                               "eth_sendTransaction"
                                               );
    qDebug() << transactionHash ;
    paramsValues.clear() ;
    paramsTypes = "" ;

    if  (transactionHash != "") {
        labelPicture->setPixmap(QPixmap(SUCC_TRANSAC)) ;
        this->setMinimumHeight(600) ;
    } else {
        labelPicture->setPixmap(QPixmap(FAIL_TRANSAC)) ;
    }
}

void MainWindow::on_commandLinkButton_2_clicked()
{
    //Send Button
    QString     transactionHash ;
    QString     paramsTypes ("uint8,uint8,string") ;
    QStringList paramsValues ;

    QString     msg = lineEdit_4->text() + ": " + textEdit_2->toPlainText() ;

    paramsValues.append (blockchain->EncodeUint8 (lineEdit_4->text().toUInt(0, 16))) ; // EID of the Sender
    paramsValues.append (blockchain->EncodeUint8 (lineEdit_6->text().toUInt(0, 16))) ; // EID of the Receiver
    paramsValues.append (blockchain->EncodeString(msg));


     transactionHash = blockchain->CallFunction(blockchain->getMyExternalAddress(),
                                                blockchain->getContractAddress(),
                                                blockchain->EncodeFunction(blockchain->EncodeFunctionSelector("sendMessage(uint8,uint8,string)"),
                                                                           paramsTypes,
                                                                           paramsValues),
                                                blockchain->getGasEstimate(
                                                    blockchain->getMyExternalAddress(),
                                                    blockchain->getContractAddress(),
                                                    blockchain->EncodeFunction(blockchain->EncodeFunctionSelector("sendMessage(uint8,uint8,string)"),paramsTypes,paramsValues)
                                                    ),
                                                "eth_sendTransaction"
                                                );
    qDebug() << transactionHash ;

    paramsValues.clear() ;
}

void MainWindow::on_commandLinkButton_3_clicked()
{
    //Receive Button
    QString     res = "" ;
    QString     paramsTypes ("uint8") ;
    QStringList paramsValues ;

    paramsValues.append (blockchain->EncodeUint8 (lineEdit_4->text().toUInt(0, 16))) ; // EID of the Sender

    res = blockchain->DecodeString(blockchain->CallFunction(blockchain->getMyExternalAddress(),
                                                            blockchain->getContractAddress(),
                                                            blockchain->EncodeFunction(blockchain->EncodeFunctionSelector("readMessage(uint8)"),
                                                                                       paramsTypes,
                                                                                       paramsValues),
                                                            blockchain->getGasEstimate(
                                                                blockchain->getMyExternalAddress(),
                                                                blockchain->getContractAddress(),
                                                                blockchain->EncodeFunction(blockchain->EncodeFunctionSelector("readMessage(uint8)"),paramsTypes,paramsValues)
                                                                ),
                                                            "eth_call"
                                                            )
                                   ) ;
    if (res != "") {
        textEdit_2->append(res) ;
    }
    paramsValues.clear() ;
}
