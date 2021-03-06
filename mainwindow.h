#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "readtext.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_decodeFileButton_clicked();
    void on_readButton_clicked();
    void on_sendTextButton_clicked();

private:
    Ui::MainWindow *ui;

    ReadText *m_readText;
    QVector<ReadText::Component> data;
};

#endif // MAINWINDOW_H
