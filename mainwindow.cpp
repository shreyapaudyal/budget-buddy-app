#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->statusbar->setStatusTip("Signed Up Successfully !");

    qputenv("QT_PLUGIN_PATH", "C:/Qt/6.9.0/mingw_64/plugins");

    qDebug() << "QT_PLUGIN_PATH set to: " << qgetenv("QT_PLUGIN_PATH");

    QStringList drivers = QSqlDatabase::drivers();
    qDebug() << "Available drivers: " << drivers;
    QSqlDatabase sqlitedb = QSqlDatabase:: addDatabase ("QSQLITE");

    sqlitedb.setDatabaseName("C:\\Users\\DELL\\login.db");


    QString fullname = ui->fullname->toPlainText();
    QString dob = ui->dob->toPlainText();
    QString email = ui->email->toPlainText();
    QString password = ui->password->toPlainText();
    QString confirmpassword = ui->confirm_password->toPlainText();

    qDebug() << "Available fullname: " << fullname;
    qDebug() << "Available dob: " << dob;
    qDebug() << "Available email: " << email;
    qDebug() << "Available password: " << password;
    qDebug() << "Available confirmpassword: " << confirmpassword;





    if (sqlitedb.open() && password == confirmpassword) {
        QSqlQuery query(sqlitedb);
        query.prepare("INSERT INTO logindetails(full_name, dob, email, password, confirm_password) "
                      "VALUES(:fullname, :dob, :email, :password, :confirmpassword)");

        query.bindValue(":fullname", fullname);
        query.bindValue(":dob", dob);
        query.bindValue(":email", email);
        query.bindValue(":password", password);
        query.bindValue(":confirmpassword", confirmpassword);

        if (query.exec()) {
            qDebug() << "Signed in successfully!";
        } else {
            qDebug() << "Error saving data:" << query.lastError().text();
        }
    }
    else{
        qDebug() << "Please check your password..";
    }



}

