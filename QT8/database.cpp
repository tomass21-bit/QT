#include "database.h"


DataBase::DataBase(QObject *parent)
    : QObject{parent}
{
    dataBase = new QSqlDatabase();
    tableWidget= new QTableWidget();
    secondQuery = new QSqlQueryModel();
    query=new QSqlQuery();

}

DataBase::~DataBase()
{
    delete dataBase, tableWidget, allQuery, secondQuery;
}

/*!
 * \brief Метод добавляет БД к экземпляру класса QSqlDataBase
 * \param driver драйвер БД
 * \param nameDB имя БД (Если отсутствует Qt задает имя по умолчанию)
 */
void DataBase::AddDataBase(QString driver, QString nameDB)
{

    *dataBase = QSqlDatabase::addDatabase(driver, nameDB);

}


/*!
 * \brief Метод подключается к БД
 * \param для удобства передаем контейнер с данными необходимыми для подключения
 * \return возвращает тип ошибки
 */
void DataBase::ConnectToDataBase(QVector<QString> data)
{

    dataBase->setHostName(data[hostName]);
    dataBase->setDatabaseName(data[dbName]);
    dataBase->setUserName(data[login]);
    dataBase->setPassword(data[pass]);
    dataBase->setPort(data[port].toInt());

    bool status;
    status = dataBase->open( );

    emit sig_SendStatusConnection(status);

}
/*!
 * \brief Метод производит отключение от БД
 * \param Имя БД
 */
void DataBase::DisconnectFromDataBase(QString nameDb)
{

    *dataBase = QSqlDatabase::database(nameDb);
    dataBase->close();

}
/*!
 * \brief Метод формирует запрос к БД.
 * \param request - SQL запрос
 * \return
 */
void DataBase::RequestToDB(QString request, int requestType)
{

    if(dataBase->open()){
        if(requestType==1){
            allQuery = new QSqlTableModel(this, *dataBase);
            allQuery->setEditStrategy(QSqlTableModel::OnFieldChange);
            allQuery->setTable("film");
            allQuery->removeColumn(0);
            allQuery->setHeaderData(0, Qt::Horizontal, tr("Название Фильма"));
            allQuery->setHeaderData(1, Qt::Horizontal, tr("Описание фильма"));
            allQuery->removeColumns(2,11);
            allQuery->select();

            emit sig_SendDataFromTable( allQuery, requestAllFilms);
        }
        else if(requestType==2|| requestType==3){


            secondQuery->setQuery(request,*dataBase);
            secondQuery->setHeaderData(0, Qt::Horizontal, tr("Название Фильма"));
            secondQuery->setHeaderData(1, Qt::Horizontal, tr("Описание фильма"));
            emit sig_SendDataFromQuery(secondQuery , requestType);
        }

    }


}

/*!
 * @brief Метод возвращает последнюю ошибку БД
 */
QSqlError DataBase::GetLastError()
{
    return dataBase->lastError();
}



