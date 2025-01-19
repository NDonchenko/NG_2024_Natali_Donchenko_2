#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbworker.h"
#include "QDate"
#include <QInputDialog>
#include <QListWidget>
#include <QWidget>
#include <QLabel>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //buttoms
    void b_enter();
    void b_exit();
    void b_exitTU();
    void b_exitCC();
    void b_exit_company();
    void b_createUser();
    void b_create_company();
    void b_create_company2();
    void b_userList();
    void b_deleteUser();
    void b_delete_company();
    void b_Update_Company();
    void b_add_exp_inc();
    void cbox_company(const QString &selectedCompany);
    void b_exit_8();
    void b_exporToPDF();
    void displayCompanyInfo(const QString &companyList);
    void displayListCompanyNames();
    void b_showReport();
    void showReportExp_Inc(QTableWidget*TableReport);
    void calculateProfit();
    // export data to PDF
    void exportDataToPDF(QTableWidget*TableExpense, QTableWidget *TableIncome, QString filePath);
    void drawTableOnPDF(QStringList DataList, QString title, QPainter &painter, QPrinter &printer, int &yOffset);
    // Worker Table Widget
    //
    void initWorkerForm();
    void onWorkerTableWidgetItemChanged();
    void checkWorkerTableWidgetNeedNewRow();
    void checkWorkerTableWidgetRowCleanup(); 
    void newStatusMessage(QString text);
    void b_exit_report();

private:
    Ui::MainWindow *ui;
    DbWorker *m_dbWorker;
    strCompany m_sCompany;
    User m_user;
    QDate creationDate;

    QStringList m_workerTableWidgetItems = {
        "Company",
        "Category",
        "Nomenclature",
        "Amount",
        "Date"
    };

    void createToolTips();
};
#endif // MAINWINDOW_H
