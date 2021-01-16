#ifndef CREATECONNECTION_H
#define CREATECONNECTION_H

/*
这个文件定义了一个helper函数来打开到
内存中的SQLITE数据库并创建一个测试表。
如果您想使用另一个数据库，只需修改代码
在下面。这个目录中的所有示例都使用这个函数
连接到数据库。
*/

#include <QMessageBox> //模态对话框
#include <QSqlDatabase> //处理数据库的连接
#include <QSqlError> //sql数据库错误信息
#include <QSqlQuery> //执行和操作sql语句的方法
#pragma execution_character_set("utf-8")

//连接数据库和执行sql
static bool createConnection(){
    //使用驱动程序类型和连接名称将数据库添加到数据库连接列表中
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //设置连接的数据库名称
    db.setDatabaseName(":memory:"); 
    if(!db.open()){ //数据库无法打开
        QMessageBox::critical(nullptr,QObject::tr("无法打开数据库"),QObject::tr("无法建立数据库连接\n"
                                                                         "这个例子需要SQLite支持。"
                                                                         "Qt的SQL驱动程序文档提供了怎样的信息"
                                                                         "构建它\n\n"
                                                                         "单击取消退出."),QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query; //执行和操作sql语句
    //exec执行sql
    query.exec("create table person (id int primary key, firstname varchar(20), lastname varchar(20))"); //创建表
    //插入
    query.exec("insert into person values(101, '张日葵', '辽宁')");
    query.exec("insert into person values(102, '向日葵', '北京')");
    query.exec("insert into person values(103, '王花花', '乌鲁木齐')");
    query.exec("insert into person values(104, '陈水水', '撒哈拉')");
    query.exec("insert into person values(105, '白冰冰', '黑龙江')");

    //创建表
    query.exec("create table items (id int primary key,"
                                             "imagefile int,"
                                             "itemtype varchar(20),"
                                             "description varchar(100))");
    query.exec("insert into items values(0, 0, 'Qt','很好,很强大.')");
    query.exec("insert into items values(1, 1, 'Qa','很好,很强大.')");
    query.exec("insert into items values(2, 2, 'Qb','很好,很强大.')");
    query.exec("insert into items values(3, 3, 'Qf','很好,很强大.')");

    //创建表
    query.exec("create table images (itemid int, file varchar(20))");
    query.exec("insert into images values(0, 'images/qt-logo.png')");
    query.exec("insert into images values(1, 'images/qt-quick.png')");
    query.exec("insert into images values(2, 'images/qt-creator.png')");
    query.exec("insert into images values(3, 'images/qt-project.png')");

    return true;

}


#endif // CREATECONNECTION_H
