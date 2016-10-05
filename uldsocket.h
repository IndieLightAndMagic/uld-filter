#ifndef ULDSOCKET_H
#define ULDSOCKET_H

#include <QQueue>
#include <QImage>
#include <QThread>
#include <QTcpSocket>
#include <QTimer>
#include "qobject__.h"

typedef struct {

    QMetaObject::Connection errorNotify;
    QMetaObject::Connection stateNotitfy;
    QMetaObject::Connection bytesWrittenNotify;
    

}ConnectionHandlers;

class UldWorker:public QObject{
    Q_OBJECT
public:
    UldWorker(QObject * parent = 0);
    ~UldWorker(){}
    int msRetryTime;

signals:
    void connectionErrorCheckConnectivity();
    void dataOnTheQueue();
    
    
public slots:
    void setAlive(bool alive);
    void testSlot();
    void setHostPortNumber(QString hostName, quint16 portNumber);
    void pushImage(QByteArray i);
    
    
    void sendData();
    void bytesWritten(qint64 bytes);
    void errorNotify(QAbstractSocket::SocketError error);
    void socketStateDisplay(QAbstractSocket::SocketState state);
    void dotDisplay();


private:
    void uploadStartSetup();
    void uploadFinished();    
    
    QQueue<QByteArray> m_qi;
    bool m_alive;
    QTimer * m_tmr;
    
    typedef enum {
        WAIT,
        GO,
        UPLOADING,
        RESUME,
    }WORKERSTATE;
    
    WORKERSTATE m_workerState;
    
    
    struct {
        qint64 tx_size;
        qint64 tx_done;
    }txStatus;
    
    
    QTcpSocket * m_s;
    QTcpSocket _m_s;
    ConnectionHandlers ch;
    
    QString hostName;
    quint16 portNumber;
};



#endif // ULDSOCKET_H
