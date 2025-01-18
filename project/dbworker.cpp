#include "dbworker.h"

DbWorker::DbWorker(QObject *parent)
    : QObject{parent}
{

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("./users.db");
    if (m_db.open())
        log("Database connected!");
    else {
        log("Database connection error!");
        log(m_db.lastError().databaseText());
    }

}

void DbWorker::initDb()
{
    QSqlQuery query;
    QString sql;
    sql = "CREATE TABLE IF NOT EXISTS users(";
    sql += "id INTEGER PRIMARY KEY AUTOINCREMENT,";
    sql += "name TEXT,";
    sql += "login TEXT UNIQUE,";
    sql += "password TEXT,";
    sql += "isAdmin BOOLEAN),";
    sql += "role TEXT;";

    if (query.exec(sql)) {
        log ("Successfully executed CREATE TABLE for Users");
    } else {
        log ("Error executting query");
    }
    if (checkAdminExist() == false) {
        log ("No admin user found! Creating new one");
        createUser("Admin", "admin", "admin", true, "admin");
    }
}

bool DbWorker::createUser(QString name, QString login, QString password, bool isAdmin,QString role)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users(name, login, password, isAdmin, role) VALUES (:name, :login, :password, :isAdmin, :role)");
    query.bindValue(":name", name);
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    query.bindValue(":isAdmin", isAdmin);
    query.bindValue(":role", role);

    bool ok = query.exec();
    qDebug() << "Error executing query:" << query.lastError().text();
    if (ok) {
        log ("Successfully added user");
    } else {
        log ("Error executting query");
    }
    return ok;
}

User DbWorker::loginUser(QString login, QString password)
{
    User user;
    user.id = -1;
    QSqlQuery query(QString("SELECT * FROM users WHERE login='%1' AND password='%2';")
                    .arg(login)
                    .arg(password));
    if (query.exec()) {
        log ("Successfully executed user login");
    } else {
        log ("Error executting query");
    }
    while (query.next()) {
        user.id = query.value("id").toInt();
        user.login = query.value("login").toString();
        user.name = query.value("name").toString();
        user.isAdmin = query.value("isAdmin").toBool();
        user.role = query.value("role").toString();
    }

    return user;
}

void DbWorker::log(QString message)
{
    qDebug() << "[DBWORKER]: " << message;
}

bool DbWorker::checkAdminExist()
{
    QSqlQuery query("SELECT * FROM users WHERE login='admin';");
    if (query.exec()) {
        log ("Successfully executed admin check");
    } else {
        log ("Error executting query");
    }
    while (query.next())
        return true;
    return false;
}

void DbWorker:: printUsersTable(QTableWidget*tableWidget){
    QSqlQuery query;
    if (!query.exec("SELECT * FROM users")) {
        qDebug() << "SQL Error:" << query.lastError().text();
        return;
    }

    if (query.exec()) {
        log ("The users are registered in the database.");
        tableWidget->clearContents();
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(6);
        tableWidget->setHorizontalHeaderLabels( QStringList() << "ID"<< "Name" << "Login"<< "password"<< "isAdmin"<<"role");
        int row =0;
        while(query.next()){
            tableWidget->insertRow(row);

            tableWidget->setItem(row,0,new QTableWidgetItem(query.value("ID").toString()));
            tableWidget->setItem(row,1,new QTableWidgetItem(query.value("name").toString()));
            tableWidget->setItem(row,2,new QTableWidgetItem(query.value("login").toString()));
            tableWidget->setItem(row,3,new QTableWidgetItem(query.value("password").toString()));
            tableWidget->setItem(row,4,new QTableWidgetItem(query.value("isAdmin").toString()));
            tableWidget->setItem(row,5,new QTableWidgetItem(query.value("role").toString()));
            row++;
        }
    }
}
void DbWorker:: DeleteUsers(QString login ){

    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE login = :login");
    query.bindValue(":login",login);

    if(!query.exec()){
        emit newStatusMessage("Error deleting user: " + query.lastError().text());
        return;
    }
    if (query.numRowsAffected()>0){

        emit newStatusMessage("User with login '" + login + "' was successfully deleted.");

    }else{

        emit newStatusMessage("No user found with login: '" + login + "'");
    }
}

void DbWorker::createExpense(){

    QSqlQuery query;
    QString sql;
    sql = "CREATE TABLE IF NOT EXISTS expense(";
    sql += "id INTEGER PRIMARY KEY AUTOINCREMENT,";
    sql += "company TEXT,";
    sql += "category TEXT,";
    sql += "nomenclature TEXT,";
    sql += "amount TEXT,";
    sql += "date DATETIME DEFAULT CURRENT_TIMESTAMP)";

    if (query.exec(sql)) {
        qDebug() <<"Successfully executed CREATE TABLE for expense";
    } else {
        qDebug() <<"Error executting query"<< query.lastError().text();
    }
}
void DbWorker::createIncome(){

    QSqlQuery query;
    QString sql;
    sql = "CREATE TABLE IF NOT EXISTS income(";
    sql += "id INTEGER PRIMARY KEY AUTOINCREMENT,";
    sql += "company TEXT,";
    sql += "category TEXT,";
    sql += "nomenclature TEXT,";
    sql += "amount TEXT,";
    sql += "date DATETIME DEFAULT CURRENT_TIMESTAMP)";

    if (query.exec(sql)) {
        qDebug() <<"Successfully executed CREATE TABLE for income";
    } else {
        qDebug() <<"Error executting query"<< query.lastError().text();
    }
}
void DbWorker::FillIncomeExpenses(QStringList rowData,QString TypeRecord)
{
    QSqlQuery query;
    QString sql;
    if (TypeRecord=="expense"){
        query.prepare("INSERT INTO expense(company, category, nomenclature, amount, date) "
                      "VALUES (:company, :category, :nomenclature, :amount, :date)");
    }else if (TypeRecord=="income") {
        query.prepare("INSERT INTO income(company, category, nomenclature, amount, date) "
                      "VALUES (:company, :category, :nomenclature, :amount, :date)");
    }
    query.bindValue(":company", rowData.value(0));
    query.bindValue(":category", rowData.value(1));
    query.bindValue(":nomenclature", rowData.value(2));
    query.bindValue(":amount", rowData.value(3));
    query.bindValue(":date", rowData.value(4));

    bool ok = query.exec();
    if (ok) {
        qDebug() << "Successfully added expense";
    } else {
        qDebug() <<"Error executting query";
    }
}

void DbWorker::createCompany(QString name, QString director, QString description,
                             int created_by,QDate CreationData){

    QSqlQuery query;
    QString sql;
    sql = "CREATE TABLE IF NOT EXISTS company(";
    sql += "id INTEGER PRIMARY KEY AUTOINCREMENT,";
    sql += "name TEXT,";
    sql += "director TEXT,";
    sql += "description TEXT,";
    sql += "created_by INTEGER,";
    sql += "created_at DATETIME DEFAULT CURRENT_TIMESTAMP)";

    if (query.exec(sql)) {
        qDebug() <<"Successfully executed CREATE TABLE for company";
    } else {
        qDebug() <<"Error executting query"<< query.lastError().text();
    }

    query.prepare("INSERT INTO company(name, director, description, created_by, created_at) "
                  "VALUES (:name, :director, :description, :created_by, :created_at)");
    query.bindValue(":name", name);
    query.bindValue(":director", director);
    query.bindValue(":description", description);
    query.bindValue(":created_by", created_by);
    query.bindValue(":created_at", CreationData);

    bool ok = query.exec();
    if (ok) {
        qDebug() << "Successfully added company";
    } else {
        qDebug() <<"Error executting query";
    }
    qDebug() << "name: "<<name<< "director:"<<director<<":description"
             <<description<<"created_by"<<created_by<<":CreationData"<<CreationData;
}
void DbWorker:: DeleteСompany(QString id ){

    QSqlQuery query;
    query.prepare("DELETE FROM company WHERE id = :id");
    query.bindValue(":id",id);

    if(!query.exec()){

        emit newStatusMessage("Error deleting company: " + query.lastError().text());
        return;
    }
    if (query.numRowsAffected()>0){

        emit newStatusMessage("Company with name '" + id + "' was successfully deleted.");

    }else{

        emit newStatusMessage("No company found with name: '" + id + "'");
    }
}
QStringList DbWorker::DisplayCompanyList(){

    QStringList companyList;
    QSqlQuery query;
    QString sql;
    if(query.exec("SELECT name FROM company")){
        while(query.next()){

            companyList.append(query.value("name").toString());
        }
    }else{
        qDebug() << "Query failed:" << query.lastError().text();
    }
    return companyList;
}
QStringList DbWorker::getCompanyInfo(const QString &companyName){
    QStringList companyInfo;

    QSqlQuery query;
    QString sql;
    query.prepare("SELECT * FROM company WHERE name = :name");
    query.bindValue(":name", companyName);

    if (query.exec() && query.next()) {

        companyInfo.append("id: " + query.value("id").toString());
        companyInfo.append("Name: " + query.value("name").toString());
        companyInfo.append("Director: " + query.value("director").toString() );
        companyInfo .append( "Description: " + query.value("description").toString() );
        companyInfo.append( "created_by: " + query.value("created_by").toString() );
        companyInfo.append("created_at: " + query.value("created_at").toString() );
    } else {
        companyInfo.append("No information about the company was found..");
    }

    return companyInfo;
}

QStringList DbWorker::getReportsFromDatabase(const QString &company, const QString &startDate,QString &endDate,QString &tableName)
{
    QStringList report;

    QSqlQuery query;
    QString sql;
    if(tableName == "tw_expense"){
        query.prepare("SELECT * FROM expense WHERE company = :company AND date BETWEEN :startDate AND :endDate");
    }else if(tableName == "tw_income"){
        query.prepare("SELECT * FROM income WHERE company = :company AND date BETWEEN :startDate AND :endDate");
    }
    query.bindValue(":company", company);
    query.bindValue(":startDate", startDate);
    query.bindValue(":endDate", endDate);
    if (query.exec()) {
        while (query.next()) {
            QString row = query.value("company").toString() + "," +
                          query.value("category").toString() + "," +
                          query.value("nomenclature").toString() + "," +
                          query.value("amount").toString() + "," +
                          query.value("date").toString();
            report.append(row);
        }
    } else {
        report.append("No information about the company was found..");
    }

    return report;
}
