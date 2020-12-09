#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H




#include "http_client.h"
#include <QDataStream>
#include "QFile"
#include <QCryptographicHash>
#include <QTextCodec>
#include <qdebug.h>





class Blockchain
{
public:
    Blockchain(const QString& ipAddr, const QString& p) ;
    ~Blockchain () ;

    QString   EncodeFunctionSelector(const QString& functionSelector) ;

    QString   EncodeUint64  (u_int64_t      value) ;
    u_int64_t DecodeUint64  (const QString& value) ;
    QString   EncodeInt64   (int64_t        value) ;
    int64_t   DecodeInt64   (const QString& value) ;
    QString   EncodeUint8   (u_int8_t       value) ;
    u_int8_t  DecodeUint8   (const QString& value) ;
    QString   EncodeBoolean (bool           value) ;
    bool      DecodeBoolean (const QString& value) ;
    QString   EncodeString  (const QString& value) ;
    QString   DecodeString  (const QString& value) ;
    QString   EncodeAddress (const QString& value) ;
    QString   DecodeAddress (const QString& value) ;

    QString   EncodeUint8Array   (u_int8_t * value, int64_t valueLen)   ;
    /*not implemented*/
    int32_t   DecodeUint8Array   (u_int8_t * decValue, int64_t decValueLen, const QString&   value) ;
    /*end*/
    QStringList DecodeAddressArray (const QString& value) ;
    /*this implementation check just the size*/
    QString EncodeUint256 (const QString & value) ;
    /**/
    QString   DecodeChunkString (const QString& value) ;
    bool      IsDynamicType     (const QString& type)      ;
    QString   EncodeFunction    (const QString& functionSelector,
                                 const QString& paramsTypes,
                                 QStringList    paramsValues) ;
    QString   getGasEstimate    (const QString& from,
                                 const QString& to,
                                 const QString& data
                                 );
    QString   CallFunction      (const QString& from,
                                 const QString& to,
                                 const QString& data,
                                 const QString& eth_methodName
                                 ) ;
    QString   getSignature      (const QString& from,
                                 const QString& data);

    QString   getCoinbaseFromTheBlockChain() ;
    QString   getCoinbase                 () ;

    QString   getContractAddress          () ;
    void      setContractAddress (const QString& _contractAddress) ;

    QString   getMyExternalAddress        () ;
    void      setMyExternalAddress (const QString& _myExternalAddress) ;

private:
    QString         ipAddress            ;
    QString         port                 ;

    HttpClient    * client               ;
    QString         coinbase             ;
    QString         contractAddress      ;
    QString         myExternalAddress    ;
};

#endif // BLOCKCHAIN_H
