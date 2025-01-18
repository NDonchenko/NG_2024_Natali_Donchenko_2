#ifndef DBWORKER_H
#define DBWORKER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlResult>
#include <QDebug>
#include <QTableWidget>
#include <QLabel>
#include <QDate>

struct User {
    int id;
    QString name;
    QString login;
    bool isAdmin;
    QString role;
};
struct strCompany {
    int id;
    QString name;
    QString director;
    QString description;
    QString CreationData;

};
class DbWorker : public QObject
{
    Q_OBJECT
public:
    explicit DbWorker(QObject *parent = nullptr);
    void initDb();

    bool createUser(QString name, QString login, QString password, bool isAdmin,QString role);
    User loginUser(QString login, QString password);
    void printUsersTable(QTableWidget*tableWidget);
    void  DeleteUsers(QString login);
    void createCompany(QString name, QString director, QString description,
                       int created_by,QDate CreationData);
    void createExpense( );
    void createIncome();
    void FillIncomeExpenses(QStringList rowData,QString TypeRecord);
    void  DeleteСompany(QString name );
    static QStringList DisplayCompanyList();
    static QStringList getCompanyInfo(const QString &companyName);
    static QStringList getReportsFromDatabase(const QString &company, const QString &startDate,QString &endDate,QString &tableName);
signals:
    void newStatusMessage(QString message);
private:
    QSqlDatabase m_db;

    void log(QString message);
    bool checkAdminExist();
    QDate CreationData;
};

#endif // DBWORKER_H
