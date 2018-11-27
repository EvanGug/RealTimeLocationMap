#include "mymapview.h"
#include "ui_mymapview.h"
#include <QDir>
#include <QDebug>

MyMapView::MyMapView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyMapView)
    , m_webView(new QWebEngineView(this))
    , m_webPage(new QWebEnginePage(this))
    , m_webChannel(new QWebChannel(this))
{
    ui->setupUi(this);

    m_webView->setPage(m_webPage);

    m_webChannel->registerObject(QString("content"), this);
    m_webPage->setWebChannel(m_webChannel);
    qDebug() << QDir::currentPath();
    m_webView->load(QUrl(QDir::currentPath() + "/demo.html"));

    m_webView->show();
}

MyMapView::~MyMapView()
{
    m_webChannel->deregisterObject(this);
    delete ui;
}

void MyMapView::onSendTextButtonClicked()
{
    emit sendText(121.47709, 31.234694);
}

void MyMapView::resizeEvent(QResizeEvent *event)
{
    m_webView->resize(this->size());
}

void MyMapView::receiveText(const QString receiveText)

{

    qDebug()<<(QObject::tr("Received message: %1").arg(receiveText));

}
