#include "mymapview.h"
#include "ui_mymapview.h"
#include <QDir>
#include <QDebug>

MyMapView::MyMapView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyMapView)
    , webView(new QWebEngineView(this))
{
    ui->setupUi(this);

    qDebug() << QDir::currentPath();
    webView->load(QUrl(QDir::currentPath() + "/demo.html"));

    webView->show();
}

MyMapView::~MyMapView()
{
    delete ui;
}

void MyMapView::resizeEvent(QResizeEvent *event)
{

    webView->resize(this->size());

}
