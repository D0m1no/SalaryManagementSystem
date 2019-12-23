#include "widget.h"
#include "ui_widget.h"

#include <iostream>
#include <QDebug>

#include <QSqlQuery>
#include <QSqlError>
#include <QTextCodec>
#include <QString>
#include <QHeaderView>
#include <QMessageBox>
#include <QRegExp>

Widget::Widget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    createMenuBar();
    addItemToBox();
    connectSql();
    init();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::createMenuBar() {
    //实例化动作
    addRecordAction = new QAction(tr("添加记录"), this);
    deleteRecordAction = new QAction(tr("删除记录"), this);
    updateRecordAction = new QAction(tr("修改记录"), this);
    quitAction = new QAction(tr("退出"), this);
    sortAction = new QAction(tr("排序"), this);
    searchAction = new QAction(tr("查询"), this);
    statisticAction = new QAction(tr("统计"), this);

    //菜单绑定快捷键
    addRecordAction->setShortcut(tr("Ctrl+A"));
    deleteRecordAction->setShortcut(tr("Ctrl+D"));
    updateRecordAction->setShortcut(tr("Ctrl+U"));
    quitAction->setShortcut(tr("Ctrl+Q"));
    sortAction->setShortcut(tr("Ctrl+S"));
    searchAction->setShortcut(tr("Ctrl+Alt+S"));
    statisticAction->setShortcut(tr("Ctrl+Shift+S"));

    //菜单绑定动作
    manageMenu = menuBar()->addMenu(tr("管理"));
    manageMenu->addAction(addRecordAction);
    manageMenu->addAction(deleteRecordAction);
    manageMenu->addAction(updateRecordAction);
    manageMenu->addSeparator();
    manageMenu->addAction(quitAction);

    checkinfoMenu = menuBar()->addMenu(tr("查看"));
    checkinfoMenu->addAction(sortAction);
    checkinfoMenu->addAction(searchAction);
    checkinfoMenu->addAction(statisticAction);

    //为功能函数添加事件关联
    connect(addRecordAction,SIGNAL(triggered()),this,SLOT(on_add_clicked()));
    connect(deleteRecordAction,SIGNAL(triggered()),this,SLOT(on_delete_clicked()));
    connect(updateRecordAction,SIGNAL(triggered()),this,SLOT(on_update_clicked()));
    connect(quitAction,SIGNAL(triggered()),this,SLOT(on_quit_clicked()));
    connect(sortAction,SIGNAL(triggered()),this,SLOT(on_sort_clicked()));
    connect(searchAction,SIGNAL(triggered()),this,SLOT(on_search_clicked()));
    connect(statisticAction,SIGNAL(triggered()),this,SLOT(on_statistic_clicked()));
}

void Widget::on_add_clicked() {
    ui->toolBox->setCurrentIndex(0);
}

void Widget::on_delete_clicked() {
    ui->toolBox->setCurrentIndex(1);
}

void Widget::on_update_clicked() {
    ui->toolBox->setCurrentIndex(2);
}

void Widget::on_quit_clicked() {
    this->close();
}

void Widget::on_sort_clicked() {
    ui->toolBox->setCurrentIndex(3);
}

void Widget::on_search_clicked() {
    ui->toolBox->setCurrentIndex(4);
}

void Widget::on_statistic_clicked() {
    ui->toolBox->setCurrentIndex(5);
}

void Widget::addItemToBox() {

    //修改页面
    QWidget *updatePage = new QWidget;
    QGridLayout *updateLayout = new QGridLayout(updatePage);

    //设置宽度高度
    updateLineeditId->setFixedWidth(50);
    updateLineeditName->setFixedWidth(100);
    updateLineeditDepartment->setFixedWidth(100);
    updateLineeditBaseSalary->setFixedWidth(50);
    updateLineeditReward->setFixedWidth(50);
    updateLineeditSubsidy->setFixedWidth(100);
    updateLineeditSubsidyAmount->setFixedWidth(50);
    updateLineeditDeduction->setFixedWidth(100);
    updateLineeditDeductionAmount->setFixedWidth(50);
    updateButton->setFixedHeight(30);
    updateButton->setFixedWidth(50);

    //绑定控件
    updateLayout->addWidget(updateLabelId,0,0,1,1);
    updateLayout->addWidget(updateLineeditId,0,1,1,3);
    updateLayout->addWidget(updateLabelName,1,0,1,1);
    updateLayout->addWidget(updateLineeditName,1,1,1,3);
    updateLayout->addWidget(updateLabelDepartment,2,0,1,1);
    updateLayout->addWidget(updateLineeditDepartment,2,1,1,3);
    updateLayout->addWidget(updateLabelBaseSalary,3,0,1,1);
    updateLayout->addWidget(updateLineeditBaseSalary,3,1,1,3);
    updateLayout->addWidget(updateLabelReward,4,0,1,1);
    updateLayout->addWidget(updateLineeditReward,4,1,1,3);
    updateLayout->addWidget(updateLabelSubsidy,5,0,1,1);
    updateLayout->addWidget(updateLineeditSubsidy,5,1,1,3);
    updateLayout->addWidget(updateLabelSubsidyAmount,6,0,1,1);
    updateLayout->addWidget(updateLineeditSubsidyAmount,6,1,1,3);
    updateLayout->addWidget(updateLabelDeduction,7,0,1,1);
    updateLayout->addWidget(updateLineeditDeduction,7,1,1,3);
    updateLayout->addWidget(updateLabelDeductionAmount,8,0,1,1);
    updateLayout->addWidget(updateLineeditDeductionAmount,8,1,1,3);
    updateLayout->addWidget(updateButton,9,3,1,1);

    updateLayout->setHorizontalSpacing(1);             // 设置水平间距
    updateLayout->setVerticalSpacing(1);               // 设置垂直间距
    updateLayout->setContentsMargins(5,5,5,5);         // 设置外间距

    updatePage->setLayout(updateLayout);
    ui->toolBox->addItem(updatePage, "修改记录");

    connect(updateButton,SIGNAL(clicked()),this,SLOT(on_updateButton_clicked()));

    //排序页面
    QWidget *sortPage = new QWidget;
    QGridLayout *sortLayout = new QGridLayout(sortPage);

    //设置宽度高度
    sortByIdButton->setFixedHeight(60);
    sortByIdButton->setFixedWidth(150);
    sortByNameAscButton->setFixedHeight(60);
    sortByNameAscButton->setFixedWidth(150);
    sortByNameDescButton->setFixedHeight(60);
    sortByNameDescButton->setFixedWidth(150);

    //绑定控件
    sortLayout->addWidget(sortByIdButton);
    sortLayout->addWidget(sortByNameAscButton);
    sortLayout->addWidget(sortByNameDescButton);

    sortLayout->setHorizontalSpacing(1);             // 设置水平间距
    sortLayout->setVerticalSpacing(1);               // 设置垂直间距
    sortLayout->setContentsMargins(5,5,5,5);         // 设置外间距

    sortPage->setLayout(sortLayout);
    ui->toolBox->addItem(sortPage, "排序");

    connect(sortByIdButton,SIGNAL(clicked()),this,SLOT(on_sortByIdButton_clicked()));
    connect(sortByNameAscButton,SIGNAL(clicked()),this,SLOT(on_sortByNameAscButton_clicked()));
    connect(sortByNameDescButton,SIGNAL(clicked()),this,SLOT(on_sortByNameDescButton_clicked()));

    //查询页面
    QWidget *searchPage = new QWidget;
    QGridLayout *searchLayout = new QGridLayout(searchPage);

    //设置宽度高度
    searchByNameButton->setFixedHeight(30);
    searchByNameButton->setFixedWidth(100);
    searchBySalaryButton->setFixedHeight(30);
    searchBySalaryButton->setFixedWidth(100);
    searchLineeditName->setFixedWidth(100);

    //绑定控件
    searchLayout->addWidget(searchLabelName,0,0,1,1);
    searchLayout->addWidget(searchLineeditName,0,1,1,3);
    searchLayout->addWidget(searchByNameButton,3,2,1,1);
    searchLayout->addWidget(searchLabelSalaryFloor,4,0,1,1);
    searchLayout->addWidget(searchLineeditSalaryFloor,4,1,1,3);
    searchLayout->addWidget(searchLabelSalaryCeil,5,0,1,1);
    searchLayout->addWidget(searchLineeditSalaryCeil,5,1,1,3);
    searchLayout->addWidget(searchBySalaryButton,8,2,1,1);

    sortLayout->setHorizontalSpacing(1);             // 设置水平间距
    sortLayout->setVerticalSpacing(1);               // 设置垂直间距
    sortLayout->setContentsMargins(5,5,5,5);         // 设置外间距

    searchPage->setLayout(searchLayout);
    ui->toolBox->addItem(searchPage, "查询");

    connect(searchByNameButton,SIGNAL(clicked()),this,SLOT(on_searchByNameButton_clicked()));
    connect(searchBySalaryButton,SIGNAL(clicked()),this,SLOT(on_searchBySalaryButton_clicked()));

    //统计页面
    QWidget *statisticPage = new QWidget;
    QGridLayout *statisticLayout = new QGridLayout(statisticPage);

    //设置宽度高度
    statisticLabelResult->setFixedHeight(30);
    statisticLabelResult->setFixedWidth(180);
    statisticBySalaryButton->setFixedHeight(30);
    statisticBySalaryButton->setFixedWidth(80);
    statisticByDepartmentButton->setFixedHeight(30);
    statisticByDepartmentButton->setFixedWidth(80);

    //绑定控件
    statisticLayout->addWidget(statisticLabelResult,0,0,1,3);
    statisticLayout->addWidget(statisticLabelSalaryFloor,1,0,1,1);
    statisticLayout->addWidget(statisticLineeditSalaryFloor,1,1,1,3);
    statisticLayout->addWidget(statisticLabelSalaryCeil,2,0,1,1);
    statisticLayout->addWidget(statisticLineeditSalaryCeil,2,1,1,3);
    statisticLayout->addWidget(statisticBySalaryButton,4,1,1,1);
    statisticLayout->addWidget(statisticByDepartmentButton,5,1,1,1);

    statisticLayout->setHorizontalSpacing(1);             // 设置水平间距
    statisticLayout->setVerticalSpacing(1);               // 设置垂直间距
    statisticLayout->setContentsMargins(3,3,3,3);         // 设置外间距

    statisticPage->setLayout(statisticLayout);
    ui->toolBox->addItem(statisticPage, "统计");

    connect(statisticBySalaryButton,SIGNAL(clicked()),this,SLOT(on_statisticBySalaryButton_clicked()));
    connect(statisticByDepartmentButton,SIGNAL(clicked()),this,SLOT(on_statisticByDepartmentButton_clicked()));

    ui->toolBox->setCurrentIndex(0);
}

void Widget::connectSql() {
    if (QSqlDatabase::contains("testConnect")) {         //判断testConnect连接是否存在并连接
        database = QSqlDatabase::database("testConnect");
    } else {                                             //未连接则新建数据库连接
        database = QSqlDatabase::addDatabase("QMYSQL","testConnect");//创建数据库连接，并为其命名testConnect
        database.setHostName("120.79.214.233");      //连接数据库主机名
        database.setPort(3306);                      //连接数据库端口号，与设置一致
        database.setDatabaseName("CourseDesign");
        database.setUserName("root");                //数据库用户名，与设置一致
        database.setPassword("1024");                //数据库密码，与设置一致
    }
    if(!database.open()) {
        qDebug() << "connect mysql fail:";
        return;
    } else {
        qDebug() << "connect mysql success\n";
    }
}

void Widget::showRecord(QString sql) {

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //将表格变为禁止编辑
    ui->tableWidget->verticalHeader()->setVisible(false);                 //隐藏列表头
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);       //不能选择

    QTableWidgetItem *headerItem;
    QStringList headerText;
    headerText << "职工号" << "姓名" << "部门" << "基本工资" << "奖励工资" << "补贴项目" << "补贴金额" << "扣款项目" << "扣款金额" << "总工资";
    ui->tableWidget->setColumnCount(headerText.count());                  //列数设置为与 headerText的行数相等
    for(int i = 0; i < ui->tableWidget->columnCount(); i++) {
        headerItem = new QTableWidgetItem(headerText.at(i));              //新建一个QTableWidgetItem， headerText.at(i)获取headerText的i行字符串
        QFont font = headerItem->font();                                  //获取原有字体设置
        font.setBold(true);                                               //设置为粗体
        font.setPointSize(10);                                            //字体大小
        headerItem->setFont(font);                                        //设置字体
        headerItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);  //设置对齐方式
        ui->tableWidget->setHorizontalHeaderItem(i, headerItem);          //设置表头单元格的Item
    }

    ui->tableWidget->clearContents();                                     //清除表格数据区的所有内容

    QSqlQuery query(database);
    query.exec(sql);
    ui->tableWidget->setRowCount(query.size());

    uint rowNo = 0;
    while(query.next()) {
        for(int colNo = 0; colNo < ui->tableWidget->columnCount(); colNo++) {
            QTableWidgetItem *item = new QTableWidgetItem();
            if(colNo == ui->tableWidget->columnCount()-1) {
                int salary_all = query.value(3).toInt() + query.value(4).toInt() + query.value(6).toInt() - query.value(8).toInt();
                item->setText(QString::number(salary_all));
            } else {
                item->setText(query.value(colNo).toString());
            }
            item->setBackground(QBrush(QColor(Qt::lightGray)));            //设置背景色
            item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);     //设置对齐方式
            ui->tableWidget->setItem(rowNo,colNo,item);
        }
        rowNo += 1;
    }

    ui->tableWidget->resizeColumnsToContents();                            //自适应调整列宽
}

void Widget::init() {
    QString sql = "SELECT * FROM Employee";
    showRecord(sql);
}

void Widget::on_addButton_clicked() {

    bool okToAdd = true;

    QString add_name = ui->add_name->text();
    QString add_department = ui->add_department->text();
    QString add_basesalary = ui->add_basesalary->text();
    QString add_rewardsalary = ui->add_rewardsalary->text();
    QString add_subsidy = ui->add_subsidy->text();
    QString add_subsidyamount = ui->add_subsidyamount->text();
    QString add_deduction = ui->add_deduction->text();
    QString add_deductionamount = ui->add_deductionamount->text();



    QSqlQuery query(database);
    QString sql_head = "INSERT INTO Employee (employee_name, department, base_salary";
    QString sql_tail = "VALUES (";
    //qDebug() << sql;

    //输入判断
    QRegExp rx;
    rx.setPattern("^[A-Za-z ]+$");
    if(!rx.exactMatch(add_name)) {
        QMessageBox::critical(NULL, "消息", "姓名格式有误！请重新输入！");
        okToAdd = false;
    } else {
        sql_tail += "\"" + add_name + "\"";
        if(!rx.exactMatch(add_department)) {
            QMessageBox::critical(NULL, "消息", "部门格式有误！请重新输入！");
            okToAdd = false;
        } else {
            sql_tail += ",\"" + add_department + "\"";
            rx.setPattern("^[0-9]*[1-9][0-9]*$");
            if(!rx.exactMatch(add_basesalary)) {
                QMessageBox::critical(NULL, "消息", "基础工资格式有误！请重新输入！");
                okToAdd = false;
            } else {
                sql_tail += "," + add_basesalary;
                //std::cout << sql_head.toStdString() << std::endl;
                //std::cout << sql_tail.toStdString() << std::endl;
            }
        }
    }

    if(add_rewardsalary != "") {
        if(!rx.exactMatch(add_rewardsalary)) {
            QMessageBox::critical(NULL, "消息", "奖励工资格式有误！请重新输入！");
            okToAdd = false;
        } else {
            sql_head += ", reward_salary";
            sql_tail += "," + add_rewardsalary;
        }
    }

    if(add_subsidy != "" && add_subsidyamount == "") {
        okToAdd = false;
        QMessageBox::critical(NULL, "消息", "请补充补贴金额！");
    }

    if(add_subsidy == "" && add_subsidyamount != "") {
        okToAdd = false;
        QMessageBox::critical(NULL, "消息", "请补充补贴项目！");
    }

    if(add_subsidy!= "" && add_subsidyamount != "") {
        rx.setPattern("^[A-Za-z ]+$");
        if(!rx.exactMatch(add_subsidy)) {
            QMessageBox::critical(NULL, "消息", "补贴项目格式有误！请重新输入！");
            okToAdd = false;
        } else {
            rx.setPattern("^[0-9]*[1-9][0-9]*$");
            if(!rx.exactMatch(add_subsidyamount)) {
                QMessageBox::critical(NULL, "消息", "补贴金额格式有误！请重新输入！");
                okToAdd = false;
            } else {
                sql_head += ", subsidy_project, subsidy_amount";
                sql_tail += ",\"" + add_subsidy + "\"," + add_subsidyamount;
                //std::cout << sql_head.toStdString() << std::endl;
                //std::cout << sql_tail.toStdString() << std::endl;
            }
        }
    }

    if(add_deduction != "" && add_deductionamount == "") {
        okToAdd = false;
        QMessageBox::critical(NULL, "消息", "请补充扣款金额！");
    }

    if(add_deduction == "" && add_deductionamount != "") {
        okToAdd = false;
        QMessageBox::critical(NULL, "消息", "请补充扣款项目！");
    }

    if(add_deduction!= "" && add_deductionamount != "") {
        rx.setPattern("^[A-Za-z ]+$");
        if(!rx.exactMatch(add_deduction)) {
            QMessageBox::critical(NULL, "消息", "扣款项目格式有误！请重新输入！");
            okToAdd = false;
        } else {
            rx.setPattern("^[0-9]*[1-9][0-9]*$");
            if(!rx.exactMatch(add_deductionamount)) {
                QMessageBox::critical(NULL, "消息", "扣款金额格式有误！请重新输入！");
                okToAdd = false;
            } else {
                sql_head += ", deduction_project, deduction_amount";
                sql_tail += ",\"" + add_deduction + "\"," + add_deductionamount;
                //std::cout << sql_head.toStdString() << std::endl;
                //std::cout << sql_tail.toStdString() << std::endl;
            }
        }
    }

    sql_tail += ")";
    sql_head += ") " + sql_tail;

    //std::cout << sql_head.toStdString() << std::endl;

    if(okToAdd) {
        bool insertOk = query.exec(sql_head);
        if(!insertOk) {
            qDebug() << "Error: Fail to insert ." << query.lastError();
            QMessageBox::critical(NULL, "消息", "添加记录失败");
            return;
        } else {
            init();
            QMessageBox::information(NULL, "消息", "添加记录成功！");
        }
    }

    //清空输入框
    if(okToAdd) {
        ui->add_name->clear();
        ui->add_department->clear();
        ui->add_basesalary->clear();
        ui->add_rewardsalary->clear();
        ui->add_subsidy->clear();
        ui->add_subsidyamount->clear();
        ui->add_deduction->clear();
        ui->add_deductionamount->clear();
    }

}

void Widget::on_deleteButton_clicked() {
    bool okToDelete = true;
    bool hasId = false;

    QString delete_id = ui->deleteId->text();
    QString delete_name = ui->deleteName->text();

    QSqlQuery query(database);
    QString sql = "DELETE FROM Employee WHERE ";

    //输入判断
    QRegExp rx;
    if(delete_id == "" && delete_name == "") {
        QMessageBox::critical(NULL, "消息", "请输入职工号或者姓名！");
        okToDelete = false;
    }

    if(delete_id != "") {
        rx.setPattern("^[0-9]*[1-9][0-9]*$");
        if(!rx.exactMatch(delete_id)) {
            QMessageBox::critical(NULL, "消息", "职工号格式有误！请重新输入！");
            okToDelete = false;
        } else {
            hasId = true;
            sql += "employee_id = " + delete_id;
        }
    }

    if(delete_name != "") {
        rx.setPattern("^[A-Za-z ]+$");
        if(!rx.exactMatch(delete_name)) {
            QMessageBox::critical(NULL, "消息", "姓名格式有误！请重新输入！");
            okToDelete = false;
        } else {
            if(hasId) {
                sql += " AND employee_name = \"" + delete_name + "\"";
            } else {
                sql += "employee_name = \"" + delete_name + "\"";
            }
        }
    }

    std::cout << sql.toStdString() << std::endl;

    if(okToDelete) {
        bool deleteOk = query.exec(sql);
        if(!deleteOk) {
            qDebug() << "Error: Fail to insert ." << query.lastError();
            QMessageBox::critical(NULL, "消息", "删除记录失败");
            return;
        } else {
            init();
            QMessageBox::information(NULL, "消息", "删除记录成功！");
        }
    }

    //清空输入框
    if(okToDelete) {
        ui->deleteName->clear();
        ui->deleteId->clear();
    }
}

void Widget::on_updateButton_clicked() {
    //QMessageBox::information(NULL, "消息", "修改记录成功！");

    bool okToUpdate = true;
    bool hasComma = false;
    bool allEmpty = true;

    QString update_id = updateLineeditId->text();
    QString update_name = updateLineeditName->text();
    QString update_department = updateLineeditDepartment->text();
    QString update_basesalary = updateLineeditBaseSalary->text();
    QString update_reward = updateLineeditReward->text();
    QString update_subsidy = updateLineeditSubsidy->text();
    QString update_subsidyamount = updateLineeditSubsidyAmount->text();
    QString update_deduction = updateLineeditDeduction->text();
    QString update_deductionamount = updateLineeditDeductionAmount->text();


    QSqlQuery query(database);
    QString sql_head = "UPDATE Employee SET ";
    QString sql_tail = " WHERE employee_id = ";
    //qDebug() << sql;

    //输入判断
    QRegExp rx;
    rx.setPattern("^[0-9]*[1-9][0-9]*$");
    if(!rx.exactMatch(update_id)) {
        QMessageBox::critical(NULL, "消息", "职工号格式有误！请重新输入！");
        okToUpdate = false;
    } else {
        sql_tail += update_id;
        //std::cout << sql_head.toStdString() << std::endl;
        //std::cout << sql_tail.toStdString() << std::endl;
    }

    if(update_name != "") {
        rx.setPattern("^[A-Za-z ]+$");
        if(!rx.exactMatch(update_name)) {
            QMessageBox::critical(NULL, "消息", "姓名格式有误！请重新输入！");
            okToUpdate = false;
        } else {
            hasComma = true;
            allEmpty = false;
            sql_head += "employee_name = \"" + update_name + "\"";
        }
    }

    if(update_department != "") {
        rx.setPattern("^[A-Za-z ]+$");
        if(!rx.exactMatch(update_department)) {
            QMessageBox::critical(NULL, "消息", "部门格式有误！请重新输入！");
            okToUpdate = false;
        } else {
            allEmpty = false;
            if(hasComma) {
              sql_head += ", ";
            }
            sql_head += "department = \"" + update_department + "\"";
            hasComma = true;
        }
    }

    if(update_basesalary != "") {
        rx.setPattern("^[0-9]*[1-9][0-9]*$");
        if(!rx.exactMatch(update_basesalary)) {
            QMessageBox::critical(NULL, "消息", "基础工资格式有误！请重新输入！");
            okToUpdate = false;
        } else {
            allEmpty = false;
            if(hasComma) {
              sql_head += ", ";
            }
            sql_head += "base_salary = " + update_basesalary;
            hasComma = true;
        }
    }

    if(update_reward != "") {
        rx.setPattern("^[0-9]*[1-9][0-9]*$");
        if(!rx.exactMatch(update_reward)) {
            QMessageBox::critical(NULL, "消息", "奖励工资格式有误！请重新输入！");
            okToUpdate = false;
        } else {
            allEmpty = false;
            if(hasComma) {
              sql_head += ", ";
            }
            sql_head += "reward_salary = " + update_reward;
            hasComma = true;
        }
    }

    if(update_subsidy != "" && update_subsidyamount == "") {
        okToUpdate = false;
        QMessageBox::critical(NULL, "消息", "请补充补贴金额！");
    }

    if(update_subsidy == "" && update_subsidyamount != "") {
        okToUpdate = false;
        QMessageBox::critical(NULL, "消息", "请补充补贴项目！");
    }

    if(update_subsidy!= "" && update_subsidyamount != "") {
        rx.setPattern("^[A-Za-z ]+$");
        if(!rx.exactMatch(update_subsidy)) {
            QMessageBox::critical(NULL, "消息", "补贴项目格式有误！请重新输入！");
            okToUpdate = false;
        } else {
            rx.setPattern("^[0-9]*[1-9][0-9]*$");
            if(!rx.exactMatch(update_subsidyamount)) {
                QMessageBox::critical(NULL, "消息", "补贴金额格式有误！请重新输入！");
                okToUpdate = false;
            } else {
                allEmpty = false;
                if(hasComma) {
                  sql_head += ", ";
                }
                sql_head += "subsidy_project = \"" + update_subsidy + "\", " + "subsidy_amount = " + update_subsidyamount;
                hasComma = true;
                //std::cout << sql_head.toStdString() << std::endl;
                //std::cout << sql_tail.toStdString() << std::endl;
            }
        }
    }

    if(update_deduction != "" && update_deductionamount == "") {
        okToUpdate = false;
        QMessageBox::critical(NULL, "消息", "请补充扣款金额！");
    }

    if(update_deduction == "" && update_deductionamount != "") {
        okToUpdate = false;
        QMessageBox::critical(NULL, "消息", "请补充扣款项目！");
    }

    if(update_deduction!= "" && update_deductionamount != "") {
        rx.setPattern("^[A-Za-z ]+$");
        if(!rx.exactMatch(update_deduction)) {
            QMessageBox::critical(NULL, "消息", "扣款项目格式有误！请重新输入！");
            okToUpdate = false;
        } else {
            rx.setPattern("^[0-9]*[1-9][0-9]*$");
            if(!rx.exactMatch(update_deductionamount)) {
                QMessageBox::critical(NULL, "消息", "扣款金额格式有误！请重新输入！");
                okToUpdate = false;
            } else {
                allEmpty = false;
                if(hasComma) {
                  sql_head += ", ";
                }
                sql_head += "deduction_project = \"" + update_deduction + "\", " + "deduction_amount = " + update_deductionamount;
                hasComma = true;
                //std::cout << sql_head.toStdString() << std::endl;
                //std::cout << sql_tail.toStdString() << std::endl;
            }
        }
    }

    sql_head += sql_tail;

    //std::cout << sql_head.toStdString() << std::endl;

    if(allEmpty) {
        QMessageBox::critical(NULL, "消息", "请至少输入一项数据！");
    }

    if(okToUpdate && !allEmpty) {
        bool updateOk = query.exec(sql_head);
        if(!updateOk) {
            qDebug() << "Error: Fail to insert ." << query.lastError();
            QMessageBox::critical(NULL, "消息", "修改记录失败");
            return;
        } else {
            init();
            QMessageBox::information(NULL, "消息", "修改记录成功！");
        }
    }

    //清空输入框
    if(okToUpdate) {
        updateLineeditId->clear();
        updateLineeditName->clear();
        updateLineeditDepartment->clear();
        updateLineeditBaseSalary->clear();
        updateLineeditReward->clear();
        updateLineeditSubsidy->clear();
        updateLineeditSubsidyAmount->clear();
        updateLineeditDeduction->clear();
        updateLineeditDeductionAmount->clear();
    }
}

void Widget::on_sortByIdButton_clicked() {
    init();
}

void Widget::on_sortByNameAscButton_clicked() {
    QString sql = "SELECT * FROM Employee ORDER BY CONVERT(employee_name USING UTF8) ASC";
    showRecord(sql);
}

void Widget::on_sortByNameDescButton_clicked() {
    QString sql = "SELECT * FROM Employee ORDER BY CONVERT(employee_name USING UTF8) DESC";
    showRecord(sql);
}

void Widget::on_searchByNameButton_clicked() {

    bool okToSearch = true;

    QString search_name = searchLineeditName->text();

    QSqlQuery query(database);
    QString sql = "SELECT * FROM Employee WHERE employee_name = ";
    //qDebug() << sql;

    //输入判断
    QRegExp rx;
    rx.setPattern("^[A-Za-z ]+$");
    if(search_name != "") {
        if(!rx.exactMatch(search_name)) {
            QMessageBox::critical(NULL, "消息", "姓名格式有误！请重新输入！");
            okToSearch = false;
        } else {
            sql += "\"" + search_name + "\"";
            //std::cout << sql.toStdString() << std::endl;
        }
    } else {
        QMessageBox::critical(NULL, "消息", "姓名为空！请输入姓名！");
        init();
        okToSearch = false;
    }

    if(okToSearch) {
        bool searchOk = query.exec(sql);
        if(!searchOk) {
            qDebug() << "Error: Fail to insert ." << query.lastError();
            return;
        } else {
            if(query.size() != 0) {
                showRecord(sql);
            } else {
                QMessageBox::critical(NULL, "消息", "查无此人！");
                init();
            }
        }
    }
}

void Widget::on_searchBySalaryButton_clicked() {
    bool okToSearch = true;

    QString search_floor = searchLineeditSalaryFloor->text();
    QString search_ceil = searchLineeditSalaryCeil->text();
    int floor = -1;
    int ceil = -1;

    QSqlQuery query(database);
    QString sql = "SELECT * FROM Employee";
    //qDebug() << sql;

    //输入判断
    if(search_floor == "" && search_ceil == "") {
        QMessageBox::critical(NULL, "消息", "请至少输入其中一项！");
        okToSearch = false;
        init();
    }

    QRegExp rx;
    rx.setPattern("^[0-9]*[1-9][0-9]*$");
    if(search_floor != "") {
        if(!rx.exactMatch(search_floor)) {
            QMessageBox::critical(NULL, "消息", "工资下限格式有误！请重新输入！");
            okToSearch = false;
            init();
        } else {
            floor = search_floor.toInt();
        }
    }

    if(search_ceil != "") {
        if(!rx.exactMatch(search_ceil)) {
            QMessageBox::critical(NULL, "消息", "工资上限格式有误！请重新输入！");
            okToSearch = false;
            init();
        } else {
            ceil = search_ceil.toInt();
        }
    }

    if(floor == -1) {floor = -maxn;}
    if(ceil == -1) {ceil = maxn;}

    if(okToSearch) {
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //将表格变为禁止编辑
        ui->tableWidget->verticalHeader()->setVisible(false);                 //隐藏列表头
        ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);       //不能选择

        QTableWidgetItem *headerItem;
        QStringList headerText;
        headerText << "职工号" << "姓名" << "部门" << "基本工资" << "奖励工资" << "补贴项目" << "补贴金额" << "扣款项目" << "扣款金额" << "总工资";
        ui->tableWidget->setColumnCount(headerText.count());                  //列数设置为与 headerText的行数相等
        for(int i = 0; i < ui->tableWidget->columnCount(); i++) {
            headerItem = new QTableWidgetItem(headerText.at(i));              //新建一个QTableWidgetItem， headerText.at(i)获取headerText的i行字符串
            QFont font = headerItem->font();                                  //获取原有字体设置
            font.setBold(true);                                               //设置为粗体
            font.setPointSize(10);                                            //字体大小
            headerItem->setFont(font);                                        //设置字体
            headerItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);  //设置对齐方式
            ui->tableWidget->setHorizontalHeaderItem(i, headerItem);          //设置表头单元格的Item
        }

        ui->tableWidget->clearContents();                                     //清除表格数据区的所有内容

        QSqlQuery query(database);
        query.exec(sql);
        ui->tableWidget->setRowCount(query.size());

        uint rowNo = 0;
        while(query.next()) {
            int salary_all = query.value(3).toInt() + query.value(4).toInt() + query.value(6).toInt() - query.value(8).toInt();
            if(salary_all >= floor && salary_all <= ceil) {
                for(int colNo = 0; colNo < ui->tableWidget->columnCount(); colNo++) {
                    QTableWidgetItem *item = new QTableWidgetItem();
                    if(colNo == ui->tableWidget->columnCount()-1) {
                        int salary_all = query.value(3).toInt() + query.value(4).toInt() + query.value(6).toInt() - query.value(8).toInt();
                        item->setText(QString::number(salary_all));
                    } else {
                        item->setText(query.value(colNo).toString());
                    }
                    item->setBackground(QBrush(QColor(Qt::lightGray)));            //设置背景色
                    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);     //设置对齐方式
                    ui->tableWidget->setItem(rowNo,colNo,item);
                }
                rowNo += 1;
            }
        }
    }
}

void Widget::on_statisticBySalaryButton_clicked() {
    bool okToSearch = true;

    QString search_floor = statisticLineeditSalaryFloor->text();
    QString search_ceil = statisticLineeditSalaryCeil->text();
    int floor = -1;
    int ceil = -1;

    QSqlQuery query(database);
    QString sql = "SELECT * FROM Employee";
    //qDebug() << sql;

    //输入判断
    if(search_floor == "" && search_ceil == "") {
        QMessageBox::critical(NULL, "消息", "请至少输入其中一项！");
        okToSearch = false;
    }

    QRegExp rx;
    rx.setPattern("^[0-9]*[1-9][0-9]*$");
    if(search_floor != "") {
        if(!rx.exactMatch(search_floor)) {
            QMessageBox::critical(NULL, "消息", "工资下限格式有误！请重新输入！");
            okToSearch = false;
        } else {
            floor = search_floor.toInt();
        }
    }

    if(search_ceil != "") {
        if(!rx.exactMatch(search_ceil)) {
            QMessageBox::critical(NULL, "消息", "工资上限格式有误！请重新输入！");
            okToSearch = false;
        } else {
            ceil = search_ceil.toInt();
        }
    }

    if(floor == -1) {floor = -maxn;}
    if(ceil == -1) {ceil = maxn;}

    if(okToSearch) {
        QSqlQuery query(database);
        query.exec(sql);

        int count = 0;

        while(query.next()) {
            int salary_all = query.value(3).toInt() + query.value(4).toInt() + query.value(6).toInt() - query.value(8).toInt();
            if(salary_all >= floor && salary_all <= ceil) {count++;}
        }

        QString result = "工资在该区间的有";
        result += QString::number(count) + "人";

        statisticLabelResult->setText(result);
        //qDebug() << result;
    }
}

void Widget::on_statisticByDepartmentButton_clicked() {

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //将表格变为禁止编辑
    ui->tableWidget->verticalHeader()->setVisible(false);                 //隐藏列表头
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);       //不能选择

    QTableWidgetItem *headerItem;
    QStringList headerText;
    headerText << "部门" << "总工资";
    ui->tableWidget->setColumnCount(headerText.count());                  //列数设置为与 headerText的行数相等

    for(int i = 0; i < ui->tableWidget->columnCount(); i++) {
        headerItem = new QTableWidgetItem(headerText.at(i));              //新建一个QTableWidgetItem， headerText.at(i)获取headerText的i行字符串
        QFont font = headerItem->font();                                  //获取原有字体设置
        font.setBold(true);                                               //设置为粗体
        font.setPointSize(10);                                            //字体大小
        headerItem->setFont(font);                                        //设置字体
        headerItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);  //设置对齐方式
        ui->tableWidget->setHorizontalHeaderItem(i, headerItem);          //设置表头单元格的Item
    }

    ui->tableWidget->clearContents();                                     //清除表格数据区的所有内容

    QSqlQuery query(database);
    QString sql = "SELECT department, SUM(base_salary) + SUM(reward_salary) + SUM(subsidy_amount) - SUM(deduction_amount) AS salary_sum FROM Employee GROUP BY department WITH ROLLUP";
    query.exec(sql);
    ui->tableWidget->setRowCount(query.size() - 1);
    //qDebug() << query.size();

    uint rowNo = 0;
    while(query.next()) {
        for(int colNo = 0; colNo < ui->tableWidget->columnCount(); colNo++) {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(query.value(colNo).toString());
            item->setBackground(QBrush(QColor(Qt::lightGray)));            //设置背景色
            item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);     //设置对齐方式
            ui->tableWidget->setItem(rowNo,colNo,item);
        }
        rowNo += 1;
        if(rowNo == query.size() - 1) {break;}
    }

    ui->tableWidget->resizeColumnsToContents();                            //自适应调整列宽
}
