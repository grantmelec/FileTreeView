#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDirModel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setup tree file view and bind to data model
    model = new QFileSystemModel();
    model->setRootPath("C:");

    //model->setFilter( QDir::NoDotAndDotDot | QDir::Files ) ;
    proxy = new QSortFilterProxyModel();
    proxy->setDynamicSortFilter(true);
    proxy->setSourceModel(model);
    proxy->setFilterKeyColumn(0);
    ui->treeView->setModel(model);
    ui->treeView->resizeColumnToContents(0);

    connect(ui->Add, SIGNAL(clicked()),this,SLOT(AddFolder()));
    connect(ui->Delete,SIGNAL(clicked()),this,SLOT(DeleteFolder()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::AddFolder()
{
    qDebug()<<"System Initiated";
    QModelIndex indexes = ui->treeView->currentIndex();
    QString FilePath = ui->FilePath->text();
    model->mkdir(indexes,FilePath);
    ui->FilePath->text().clear();

}


void MainWindow::DeleteFolder()
{

    qDebug()<<"...............";
    QModelIndex indexes = ui->treeView->currentIndex();
    model->remove(indexes);
}
