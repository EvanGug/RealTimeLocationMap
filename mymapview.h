#ifndef MYMAPVIEW_H
#define MYMAPVIEW_H

#include "readtext.h"
#include <QWidget>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebChannel>

namespace Ui {
class MyMapView;
}

class MyMapView : public QWidget
{
    Q_OBJECT

public:
    explicit MyMapView(QWidget *parent = 0);
    ~MyMapView();

    void onSendTextButtonClicked(const QVector<ReadText::Component> &data);

private:
    void resizeEvent(QResizeEvent *event);

public slots:

    Q_INVOKABLE void receiveText(const QString receiveText);

signals:

    Q_INVOKABLE void sendText(const double X, const double Y);

private:
    Ui::MyMapView *ui;
    QWebEngineView *m_webView;
    QWebEnginePage *m_webPage;
    QWebChannel *m_webChannel;

    int index = 0;
};

#endif // MYMAPVIEW_H
