#include <QtWidgets>
#include <QtSql>

#include "createConnection.h"
#include <memory> //内存标准头
#pragma execution_character_set("utf-8")

//为单个数据库表提供了一个可编辑的数据模型，并提供了外键支持
void initializeModel(QSqlRelationalTableModel *model){

    //设置要操作的数据库表名
    //model->setTable("employee");
    model->setTable("newtable");
    //将编辑数据库中的值的策略设置为策略。：所有的更改都将缓存到模型中
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //让指定的列是由参数2指定的外部索引。QSqlRelation类存储有关SQL外键的信息
//    model->setRelation(2,QSqlRelation("city","id","name"));
//    model->setRelation(3,QSqlRelation("country","id","name"));

    //设置水平标题
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("姓名"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("城市"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("国家"));

    //使用指定的过滤器和排序条件，使用通过setTable()设置的表中的数据填充模型，
    model->select();
}

//unique_ptr指向对象的不可复制指针。
std::unique_ptr<QTableView> createView(const QString &title, QSqlTableModel *model){

    std::unique_ptr<QTableView> view{new QTableView};
    view->setModel(model);
    //将此视图及其模型的项委托设置为委托。想要完全控制项的编辑和显示，这是很有用的。QSqlRelationalDelegate提供了一个用于显示和编辑数据的委托
    view->setItemDelegate(new QSqlRelationalDelegate(view.get()));
    view->setWindowTitle(title); //窗口标题
    return view;
}

//创建关系表
void createRelationalTables(){

    QSqlQuery query; //执行sql语句
    //创建表
    query.exec("create table employee(id int primary key, name varchar(20), city int, country int)");
    query.exec("insert into employee values(1, '山姆', 5000, 47)");
    query.exec("insert into employee values(2, '汤姆', 8000, 49)");
    query.exec("insert into employee values(3, '英格姆', 100, 1)");
    query.exec("insert into employee values(4, '英格姆', 100, 1)");
    query.exec("insert into employee values(5, '英格姆', 100, 1)");

    query.exec("create table city(id int, name varchar(20))");
    query.exec("insert into city values(100, '大洋洲')");
    query.exec("insert into city values(5000, '海尔洲')");
    query.exec("insert into city values(8000, '手套洲')");

    query.exec("create table country(id int, name varchar(20))");
    query.exec("insert into country values(1, 'Y国')");
    query.exec("insert into country values(47, 'H国')");
    query.exec("insert into country values(49, 'M国')");
}

int main(int argc, char *argv[]){

    QApplication app(argc,argv);

    //使用驱动程序类型和连接名称将数据库添加到数据库连接列表中
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost"); //主机名
    //db.setPort(3306);
    db.setDatabaseName("figure"); //数据库名
    db.setUserName("root"); //用户名
    db.setPassword("111");
    bool ok = db.open();
    if(!ok){
        return EXIT_FAILURE;
    }

//    if(!createConnection()) //数据库连接失败，这里连接QSQLITE数据库
//        return EXIT_FAILURE;

    createRelationalTables(); //创建数据库表

    //提供了一个可编辑的数据模型为一个数据库表,与外键的支持
    QSqlRelationalTableModel model; 
    initializeModel(&model); //设置模型中的数据

    //设置视图
    std::unique_ptr<QTableView> view = createView(QObject::tr("关系表模型"),&model);
    view->show();

    return app.exec();
}
