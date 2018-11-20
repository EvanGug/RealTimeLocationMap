#ifndef MYMAPVIEW_H
#define MYMAPVIEW_H

#include <QWidget>
#include <QWebEngineView>

namespace Ui {
class MyMapView;
}

class MyMapView : public QWidget
{
    Q_OBJECT

public:
    explicit MyMapView(QWidget *parent = 0);
    ~MyMapView();

    void resizeEvent(QResizeEvent *event);

private:
    Ui::MyMapView *ui;
    QWebEngineView *webView;
};

#endif // MYMAPVIEW_H
