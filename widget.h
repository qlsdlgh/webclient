#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QSslSocket>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QSslSocket ssocket_;
    QTcpSocket tsocket_;
public slots:
    void doConnected();
    void doDisconnected();
    void doReadyread();
private slots:
    void on_pbConnect_clicked();

    void on_pbDisconnet_clicked();

    void on_pbSend_clicked();

    void on_TCPcheck_stateChanged(int state);

    void on_SSLcheck_stateChanged(int state);

    void on_pbClear_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
