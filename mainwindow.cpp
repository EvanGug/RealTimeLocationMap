#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_readText(new ReadText)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_readText;
}

void MainWindow::on_decodeFileButton_clicked()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("Select File"));
    fileDialog->setDirectory(".");
    QStringList filters;
    filters << tr("Supported Formats(*.txt)");
    fileDialog->setNameFilters(filters);
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::Detail);
    if (fileDialog->exec())
    {
        QStringList fileNameList = fileDialog->selectedFiles();
        m_readText->decodeFile(fileNameList);
    }
    delete fileDialog;
}

void MainWindow::on_readButton_clicked()
{
    m_readText->readSql();
    QVector<ReadText::Component> data = m_readText->getData();

    ui->tableWidget->setRowCount(data.size());
    for(int i = 0; i < data.size(); i++)
    {
        QString templocation = "(" + QString::number(data.at(i).m_coordinate.x()) + "," + QString::number(data.at(i).m_coordinate.y()) + ")";

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(data.at(i).m_id)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(data.at(i).m_firstItem));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(data.at(i).m_uploadDateTime.toString()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(data.at(i).m_locationDateTime.toString()));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(data.at(i).m_information));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(data.at(i).m_tempNumber));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(templocation));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(data.at(i).m_frequence));
    }
}

void MainWindow::on_sendTextButton_clicked()
{
    ui->mapTab->onSendTextButtonClicked();
}
