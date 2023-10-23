#include "udpworker.h"

UDPworker::UDPworker(QObject *parent) : QObject(parent)
{



}


/*!
 * @brief Метод инициализирует UDP сервер
 */
void UDPworker::InitSocket()
{

    serviceUdpSocket = new QUdpSocket(this);
    /*
     * Соединяем присваиваем адрес и порт серверу и соединяем функцию
     * обраотчик принятых пакетов с сокетом
     */
    serviceUdpSocket->bind(QHostAddress::LocalHost, BIND_PORT);

    connect(serviceUdpSocket, &QUdpSocket::readyRead, this, &UDPworker::readPendingDatagrams);

}

/*!
 * @brief Метод осуществляет обработку принятой датаграммы
 */
void UDPworker::ReadDatagram(QNetworkDatagram datagram)
{
    QByteArray data;
    data = datagram.data();
    QString datain;
    QDateTime dateTime;

    if(data.back()=='$'){ //Проверяем передается строка пользователя или время
        QHostAddress adress;
        adress = datagram.destinationAddress();
        long size= data.size();
        QString size_c=QString::number(size);
        QDataStream inStr1(&data, QIODevice::ReadOnly);
        inStr1 >> datain;
        datain.remove(datain.size()-1,1); //Убираем спецсимвол для определения данных пользователя
        datain+=" Адрес получателя "+adress.toString()+" Размер " +size_c;
        emit sig_sentDataToGUI(datain);
    }
    else{
        QDataStream inStr(&data, QIODevice::ReadOnly);
        inStr >> dateTime;
        emit sig_sendTimeToGUI(dateTime);
    }

}
/*!
 * @brief Метод осуществляет передачу датаграммы
 */
void UDPworker::SendDatagram(QByteArray data)
{
    /*
     *  Отправляем данные на localhost и задефайненный порт
     */
    serviceUdpSocket->writeDatagram(data, QHostAddress::LocalHost, BIND_PORT);
}


/*!
 * @brief Метод осуществляет чтение датаграм из сокета
 */
void UDPworker::readPendingDatagrams( void )
{
    /*
     *  Производим чтение принятых датаграмм
     */
    while(serviceUdpSocket->hasPendingDatagrams()){

        QNetworkDatagram datagram = serviceUdpSocket->receiveDatagram();

        ReadDatagram(datagram);
    }

}
