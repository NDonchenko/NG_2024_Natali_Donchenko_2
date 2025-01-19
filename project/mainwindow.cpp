#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_dbWorker = new DbWorker();
    m_dbWorker->initDb();
    creationDate = QDate::currentDate();
    ui->stackedWidget->setCurrentIndex(0);
    ui->tw_records->setEditTriggers(QAbstractItemView::AllEditTriggers);

    ui->te_companyInfo->setReadOnly(true);
    createToolTips();
    displayListCompanyNames();
    connect (ui->b_enter, &QPushButton::clicked, this, &MainWindow::b_enter);
    connect (ui->b_exit, &QPushButton::clicked, this, &MainWindow::b_exit);
    connect (ui->b_exitCC, &QPushButton::clicked, this, &MainWindow::b_exitCC);
    connect (ui->b_exit_8, &QPushButton::clicked, this, &MainWindow::b_exit_8);
    connect (ui->b_exitTU, &QPushButton::clicked, this, &MainWindow::b_exitTU);
    connect (ui->b_exit_company, &QPushButton::clicked, this, &MainWindow::b_exit_company);
    connect (ui->b_exit_report, &QPushButton::clicked, this, &MainWindow::b_exit_report);
    connect (ui->b_create, &QPushButton::clicked, this, &MainWindow::b_createUser);
    connect (ui->b_UserList, &QPushButton::clicked, this, &MainWindow::b_userList);
    connect (ui->b_delete_user, &QPushButton::clicked, this, &MainWindow::b_deleteUser);
    connect (ui->b_delete_company, &QPushButton::clicked, this, &MainWindow::b_delete_company);
    connect (ui->b_UpdateUsers, &QPushButton::clicked, this, &MainWindow::b_userList);
    connect (ui->b_Update_Company, &QPushButton::clicked, this, &MainWindow::b_Update_Company);
    connect (ui->b_create_company, &QPushButton::clicked, this, &MainWindow::b_create_company);
    connect (ui->b_create_company2, &QPushButton::clicked, this, &MainWindow::b_create_company2);
    connect (ui->lw_companies, &QListWidget::currentTextChanged, this, &MainWindow::displayCompanyInfo);
    connect (ui->cbox_company, &QComboBox::currentTextChanged, this, &MainWindow::cbox_company);
    connect (m_dbWorker, &DbWorker::newStatusMessage, this, &MainWindow::newStatusMessage);
    connect (ui->b_add_exp_inc,&QPushButton::clicked, this, &MainWindow::b_add_exp_inc);
    connect (ui->tw_records, &QTableWidget::cellChanged, this, &MainWindow::onWorkerTableWidgetItemChanged);
    connect (ui->b_showReport, &QPushButton::clicked, this, &MainWindow::b_showReport);
    connect (ui->b_exporToPDF, &QPushButton::clicked, this, &MainWindow::b_exporToPDF);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::b_exit()
{
    m_user.id = -1;
    m_user.login.clear();
    m_user.name.clear();
    m_user.isAdmin = false;
    ui->l_greetings->clear();
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::b_exitTU()
{
    ui->stackedWidget->setCurrentIndex(4);
}
void MainWindow::b_exitCC()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::b_exit_company()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::b_exit_8()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::b_exporToPDF()
{

    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");
    if (!filePath.isEmpty()) {
        exportDataToPDF(ui->tw_expense, ui->tw_income, filePath);
    }
}
void MainWindow::b_createUser()
{
    m_dbWorker->createUser(
        ui->e_cname->text(),
        ui->e_clogin->text(),
        ui->e_cpassword->text(),
        ui->cb_cIsAdmin->isChecked(),
        ui->cb_Role->currentText());

    ui->e_cname->clear();
    ui->e_clogin->clear();
    ui->e_cpassword->clear();
    ui->cb_cIsAdmin->setChecked(false);
    ui->cb_Role->clear();
}
void MainWindow::b_create_company(){

    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::b_create_company2(){

    m_dbWorker->createCompany(
        ui->e_cName->text(),
        ui->e_cDirector->text(),
        ui->e_cDescription->toPlainText(),
        m_user.id,
        creationDate);

    ui->e_cName->clear();
    ui->e_cDirector->clear();
    ui->e_cDescription->clear();
    ui->stackedWidget->setCurrentIndex(1);
    ui->lw_companies->clear();
    displayListCompanyNames();
}
void MainWindow::b_enter()
{
    m_user = m_dbWorker->loginUser(ui->e_login->text(), ui->e_password->text());
    qDebug () << m_user.id;
    if (m_user.id != -1) {
        ui->l_greetings->setText("Greetings, " + m_user.name + "!");
        if (m_user.role == "Manager"){
            ui->stackedWidget->setCurrentIndex(1);
        } else if (m_user.role == "admin"){
            ui->stackedWidget->setCurrentIndex(4);
        } else if (m_user.role == "Worker"){
            ui->stackedWidget->setCurrentIndex(5);
            initWorkerForm();
        } else if (m_user.role == "Director"){
            ui->stackedWidget->setCurrentIndex(6);
        };
        if (m_user.isAdmin == false)
            ui->gb_admin->setVisible(false);
        else
            ui->gb_admin->setVisible(true);
    }
}
void MainWindow::b_userList(){

    ui->stackedWidget->setCurrentIndex(3);
    m_dbWorker->printUsersTable(ui->tableWidgetUser);

}
void MainWindow::b_deleteUser(){
    bool ok;
    QString login = QInputDialog::getText(this, "Enter Login",
                                          "Login:", QLineEdit::Normal,
                                          QString(""), &ok);

    if(ok){
        qDebug() << "Entered login:" << login;
        m_dbWorker->DeleteUsers(login);
    }
}
void MainWindow::b_delete_company(){
    bool ok;
    QString id = QInputDialog::getText(this, "Enter id company",
                                          "id:", QLineEdit::Normal,
                                          QString(""), &ok);

    if(ok){
        m_dbWorker->DeleteСompany(id);
        ui->lw_companies->clear();
        displayListCompanyNames();
    }
}
void MainWindow::b_Update_Company(){
    ui->lw_companies->clear();
    displayListCompanyNames();
}

void MainWindow::b_add_exp_inc()
{
    for (int row = 0; row < ui->tw_records->rowCount(); row++) {
        QStringList rowData;

        for (int col = 0; col < ui->tw_records->columnCount(); col++) {
            QTableWidgetItem *item = ui->tw_records->item(row, col);
            QString cellData = item ? item->text() : "";
            rowData << cellData;
        }
        QString TypeRecord = ui->cbox_records->currentText();
        if(TypeRecord == "expense"){
            m_dbWorker->createExpense();
            m_dbWorker->FillIncomeExpenses(rowData,TypeRecord);
        } else if(TypeRecord == "income"){
            m_dbWorker->createIncome();
            m_dbWorker->FillIncomeExpenses(rowData,TypeRecord);
        }
    }
}
void MainWindow::cbox_company(const QString &selectedCompany)
{
    int rowsAmount = ui->tw_records->rowCount() - 1;
    for (int row = 0; row < rowsAmount; row++) {

        QTableWidgetItem *item = ui->tw_records->item(row,0);
        if (!item) {
            item = new QTableWidgetItem();
            ui->tw_records->setItem(row, 0, item);
        }
        item->setText(selectedCompany);

    }
}
void MainWindow::displayCompanyInfo(const QString &companyList){

    QStringList companyInfo = m_dbWorker->getCompanyInfo(companyList);

    QString infoText = companyInfo.join("\n");

    ui->te_companyInfo->setText(infoText);

}
void MainWindow::displayListCompanyNames(){

    ui->stackedWidget->widget(1);

    QStringList companyList = m_dbWorker->DisplayCompanyList();

    ui->lw_companies->addItems(companyList);

    ui->cbox_company->addItems(companyList);

    ui->comb_company->addItems(companyList);

}

void MainWindow::b_showReport()
{
    showReportExp_Inc(ui->tw_expense);
    showReportExp_Inc(ui->tw_income);
    calculateProfit();
}

void MainWindow::showReportExp_Inc(QTableWidget*TableReport)
{
    QString Company = ui->comb_company->currentText();
    QString startDate = ui->le_date->text();
    QString endDate = ui->le_date_2->text();
    QString tableName = TableReport->objectName();
    QStringList DataList = m_dbWorker->getReportsFromDatabase(Company,startDate,endDate,tableName);

    TableReport->clear();
    TableReport->setRowCount(0);

    int columnCount = 5;
    TableReport->setColumnCount(columnCount);
    QStringList headers = {"Company","Category","Nomenclature", "Amount", "Date"};
    TableReport->setHorizontalHeaderLabels(headers);
    double totalAmount = 0.0;
    for (int index = 0; index < DataList.size(); index++)
    {
        int row = TableReport->rowCount();
        TableReport->insertRow(row);
        QStringList columns = DataList[index].split(",");
        for (int col = 0; col < columns.size(); col++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(columns[col].trimmed());
            TableReport->setItem(row, col, item);
            if (col == 3)
            {
                bool ok;
                double amount = columns[col].toDouble(&ok);
                if (ok)
                {
                    totalAmount += amount;
                }
            }
        }
    }
    int totalRow = TableReport->rowCount();
    TableReport->insertRow(totalRow);

    QTableWidgetItem *totalTextItem = new QTableWidgetItem("Total");
    TableReport->setItem(totalRow, 0, totalTextItem);

    QTableWidgetItem *totalAmountItem = new QTableWidgetItem(QString::number(totalAmount, 'f', 2));
    TableReport->setItem(totalRow, 3, totalAmountItem);
}

void MainWindow::calculateProfit()
{
    double totalExpense = 0.0;
    for (int row = 0; row < ui->tw_expense->rowCount(); row++) {
        QTableWidgetItem* item = ui->tw_expense->item(row, 3);
        if (item) {
            totalExpense += item->text().toDouble();
        }
    }

    double totalIncome = 0.0;
    for (int row = 0; row < ui->tw_income->rowCount(); ++row) {
        QTableWidgetItem* item = ui->tw_income->item(row, 3);
        if (item) {
            totalIncome += item->text().toDouble();
        }
    }
    double netProfit = totalIncome - totalExpense;
    ui->label_24->setText(ui->label_24->text()+(QString::number(netProfit, 'f', 2)));

    ui->label_23->setText(ui->label_23->text()+ m_user.name);
}

void MainWindow::exportDataToPDF(QTableWidget* TableExpense, QTableWidget* TableIncome, QString filePath)
{
    QString Company = ui->comb_company->currentText();
    QString startDate = ui->le_date->text();
    QString endDate = ui->le_date_2->text();
    //QString tableName = TableReport->objectName();
    QString expenseTableName = TableExpense->objectName();
    QString incomeTableName = TableIncome->objectName();
    QStringList expenseData = m_dbWorker->getReportsFromDatabase(Company, startDate, endDate, expenseTableName);
    QStringList incomeData = m_dbWorker->getReportsFromDatabase(Company, startDate, endDate, incomeTableName);

    if (expenseData.isEmpty() && incomeData.isEmpty()) {
        qDebug() << "No data to export.";
        return;
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    printer.setPageSize(QPageSize(QPageSize::A4));

    QPainter painter;
    if (!painter.begin(&printer)) {
        qDebug() << "Failed to begin painting on printer";
        return;
    }

    int yOffset = 1500;

    if (!expenseData.isEmpty()) {
        drawTableOnPDF(expenseData, "Expenses Report", painter, printer, yOffset);
       // yOffset += 4000;
    }

    if (!incomeData.isEmpty()) {
        yOffset = 1500;
        drawTableOnPDF(incomeData, "Income Report", painter, printer, yOffset);
    }

    painter.end();
    qDebug() << "PDF exported to:" << filePath;
}

void MainWindow::drawTableOnPDF( QStringList DataList, QString title, QPainter& painter, QPrinter& printer, int &yOffset)
{



    QFont font = painter.font();
    font.setPointSize(10);
    font.setFamily("Arial");
    painter.setFont(font);

    int xOffset = 500;
    //int yOffset = 150;
    int rowHeight = 200;
    int colWidth = 2000;
    painter.drawText(100, 100, "Company Report");
    painter.drawLine(xOffset, yOffset + rowHeight / 2 - 50, xOffset + 5 * colWidth, yOffset + rowHeight / 2 - 50);
    QStringList headers = {"Company", "Category", "Nomenclature", "Amount", "Date"};
    painter.drawText(xOffset, yOffset - rowHeight, title);
    painter.drawLine(xOffset, yOffset - rowHeight + 10, 10000, yOffset - rowHeight + 10);
    int startX = xOffset;
    int startY = yOffset - rowHeight;
    int endY = startY + (rowHeight * (DataList.size() + 1)+350);

    for (int col = 0; col <= headers.size(); col++) {
        painter.drawLine(startX + col * colWidth, startY, startX + col * colWidth, endY);
    }

    for (int col = 0; col < headers.size(); col++) {
        painter.drawText(xOffset + col * colWidth, yOffset, headers[col]);
    }


    yOffset += rowHeight;


    double totalAmount = 0.0;


    for (int index = 0; index < DataList.size(); index++) {
        QStringList columns = DataList[index].split(",");
        painter.drawLine(xOffset, yOffset + rowHeight/2 - 50, xOffset + colWidth * columns.size(), yOffset + rowHeight/2 - 50);
        for (int col = 0; col < columns.size(); col++) {
            painter.drawText(xOffset + col * colWidth, yOffset, columns[col].trimmed());
            if (col == 3) {
                bool ok;
                double amount = columns[col].toDouble(&ok);
                if (ok) {
                    totalAmount += amount;
                }
            }
        }
        yOffset += rowHeight;
    }

    painter.drawText(xOffset, yOffset, "Total Amount: ");
    painter.drawText(xOffset + 6000, yOffset, QString::number(totalAmount, 'f', 2));
    int totalLineYOffset = yOffset + rowHeight-70;

    painter.drawLine(xOffset, totalLineYOffset, xOffset + colWidth * headers.size(), totalLineYOffset);
    if (yOffset > printer.pageLayout().fullRect(QPageLayout::Point).height() - rowHeight) {
        printer.newPage();
        yOffset = 150;
    }
}


void MainWindow::initWorkerForm()
{
    ui->tw_records->clear();
    ui->tw_records->setHorizontalHeaderLabels(m_workerTableWidgetItems);
    ui->tw_records->setRowCount(1);
}

void MainWindow::onWorkerTableWidgetItemChanged()
{
    checkWorkerTableWidgetNeedNewRow();
    checkWorkerTableWidgetRowCleanup();
}

void MainWindow::checkWorkerTableWidgetNeedNewRow()
{
    int latestRowNumber = ui->tw_records->rowCount() - 1;

    // Check for new row required
    //

    for (int index = 0; index < m_workerTableWidgetItems.size(); index++) {
        QTableWidgetItem *item = ui->tw_records->item(latestRowNumber, index);
        if (item != nullptr) {
            QString cellText = item->text();
            if (cellText.isEmpty() == false) {
                ui->tw_records->setRowCount(ui->tw_records->rowCount() + 1);
                return;
            }
        }
    }
}

void MainWindow::checkWorkerTableWidgetRowCleanup()
{
    // Check for row to be deleted
    //

    if (ui->tw_records->rowCount() < 2)
        return;

    int emptyItemsCount = 0;
    int checkRowForDeletion = ui->tw_records->rowCount() - 2;
    for (int index = 0; index < m_workerTableWidgetItems.size(); index++) {
        QTableWidgetItem *item = ui->tw_records->item(checkRowForDeletion, index);
        if (item != nullptr) {
            QString cellText = item->text();
            if (cellText.isEmpty() == true) {
                emptyItemsCount++;
            }
        } else {
            emptyItemsCount++;
        }
    }

    if (emptyItemsCount == m_workerTableWidgetItems.size())
        ui->tw_records->setRowCount(ui->tw_records->rowCount() - 1);
}

void MainWindow::newStatusMessage(QString text)
{
    ui->statusbar->showMessage(text);
}
void MainWindow::createToolTips()
{
    ui->e_cName->setToolTip("Here you can provide your company name");
}

void MainWindow::b_exit_report()
{
    ui->stackedWidget->setCurrentIndex(0);
}

