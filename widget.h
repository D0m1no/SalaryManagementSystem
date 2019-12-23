#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QMenuBar>

#include <QSqlDatabase>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

namespace Ui {
class Widget;
}

class Widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    const int maxn = 0x3fffffff;

    QMenu *manageMenu;   //“管理”主菜单
    QAction *addRecordAction;
    QAction *deleteRecordAction;
    QAction *updateRecordAction;
    QAction *quitAction;

    QMenu *checkinfoMenu;   //“查看”主菜单
    QAction *sortAction;
    QAction *searchAction;
    QAction *statisticAction;

    QSqlDatabase database;

    //修改页面的控件
    QLabel *updateLabelId = new QLabel("职工号:");
    QLineEdit *updateLineeditId = new QLineEdit();
    QLabel *updateLabelName = new QLabel("姓名:");
    QLineEdit *updateLineeditName = new QLineEdit();
    QLabel *updateLabelDepartment = new QLabel("部门:");
    QLineEdit *updateLineeditDepartment = new QLineEdit();
    QLabel *updateLabelBaseSalary = new QLabel("基础工资:");
    QLineEdit *updateLineeditBaseSalary = new QLineEdit();
    QLabel *updateLabelReward = new QLabel("奖励工资:");
    QLineEdit *updateLineeditReward = new QLineEdit();
    QLabel *updateLabelSubsidy = new QLabel("补贴项目:");
    QLineEdit *updateLineeditSubsidy = new QLineEdit();
    QLabel *updateLabelSubsidyAmount = new QLabel("补贴金额:");
    QLineEdit *updateLineeditSubsidyAmount = new QLineEdit();
    QLabel *updateLabelDeduction = new QLabel("扣款项目:");
    QLineEdit *updateLineeditDeduction = new QLineEdit();
    QLabel *updateLabelDeductionAmount = new QLabel("扣款金额:");
    QLineEdit *updateLineeditDeductionAmount = new QLineEdit();
    QPushButton *updateButton = new QPushButton("修改");

    //排序页面的控件
    QPushButton *sortByIdButton = new QPushButton("按职工号排序");
    QPushButton *sortByNameAscButton = new QPushButton("按姓名字母排序(升序)");
    QPushButton *sortByNameDescButton = new QPushButton("按姓名字母排序(降序)");

    //查询页面的控件
    QLabel *searchLabelName = new QLabel("姓名:");
    QLineEdit *searchLineeditName = new QLineEdit();
    QPushButton *searchByNameButton = new QPushButton("按姓名查询");
    QLabel *searchLabelSalaryFloor = new QLabel("工资下限:");
    QLabel *searchLabelSalaryCeil = new QLabel("工资上限:");
    QLineEdit *searchLineeditSalaryFloor = new QLineEdit();
    QLineEdit *searchLineeditSalaryCeil = new QLineEdit();
    QPushButton *searchBySalaryButton = new QPushButton("按工资查询");

    //统计页面的控件
    QLabel *statisticLabelResult = new QLabel("统计结果");
    QLabel *statisticLabelSalaryFloor = new QLabel("工资下限:");
    QLabel *statisticLabelSalaryCeil = new QLabel("工资上限:");
    QLineEdit *statisticLineeditSalaryFloor = new QLineEdit();
    QLineEdit *statisticLineeditSalaryCeil = new QLineEdit();
    QPushButton *statisticBySalaryButton = new QPushButton("按工资统计");
    QPushButton *statisticByDepartmentButton = new QPushButton("按部门统计");

private slots:
    void on_add_clicked();      //实现“添加记录”子菜单功能函数
    void on_delete_clicked();   //实现“删除记录”子菜单功能函数
    void on_update_clicked();   //实现“修改记录”子菜单功能函数
    void on_quit_clicked();     //实现“退出”子菜单功能函数

    void on_sort_clicked();      //实现“排序”子菜单功能函数
    void on_search_clicked();    //实现“查询”子菜单功能函数
    void on_statistic_clicked(); //实现“统计”子菜单功能函数

    void on_addButton_clicked();     //添加记录按钮
    void on_deleteButton_clicked();  //删除记录按钮
    void on_updateButton_clicked();  //修改记录按钮
    void on_sortByIdButton_clicked(); //按姓名字母排序按钮
    //按姓名字母排序按钮
    void on_sortByNameAscButton_clicked();
    void on_sortByNameDescButton_clicked();
    void on_searchByNameButton_clicked();  //按姓名查询按钮
    void on_searchBySalaryButton_clicked();  //按工资查询按钮
    void on_statisticBySalaryButton_clicked();  //按工资统计按钮
    void on_statisticByDepartmentButton_clicked();    //按部门统计按钮

private:
    Ui::Widget *ui;
    void createMenuBar();       //用于生成菜单栏的函数
    void addItemToBox();        //用于给tooBox添加item的函数
    void connectSql();          //用于与数据库连接的函数
    void init();                //用于初始表格的函数
    void showRecord(QString sql);    //用于展示记录的函数
};

#endif // WIDGET_H
