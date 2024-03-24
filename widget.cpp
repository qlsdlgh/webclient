#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //socket_.connected();
    //socket_.readyRead();
    connect(ui->TCPcheck, &QCheckBox::stateChanged,this, &Widget::on_TCPcheck_stateChanged);
    connect(ui->TCPcheck, &QCheckBox::stateChanged,this, &Widget::on_TCPcheck_stateChanged);

    QObject::connect(&ssocket_,&QAbstractSocket::connected,this,&Widget::doConnected);
    QObject::connect(&ssocket_,&QAbstractSocket::disconnected,this,&Widget::doDisconnected);
    QObject::connect(&ssocket_,&QAbstractSocket::readyRead,this,&Widget::doReadyread);

    QObject::connect(&tsocket_,&QAbstractSocket::connected,this,&Widget::doConnected);
    QObject::connect(&tsocket_,&QAbstractSocket::disconnected,this,&Widget::doDisconnected);
    QObject::connect(&tsocket_,&QAbstractSocket::readyRead,this,&Widget::doReadyread);
}

Widget::~Widget()
{
    delete ui;

}
void Widget::doConnected()
{
    ui->pteMessage->insertPlainText("Conneted\n");

}
void Widget::doDisconnected()
{
    ui->pteMessage->insertPlainText("Disconneted\n");

}

void Widget::doReadyread()
{
    if (ui->TCPcheck->isChecked()){
    ui->pteMessage->insertPlainText(tsocket_.readAll());
    }
    else if (ui->SSLcheck->isChecked()){
    ui->pteMessage->insertPlainText(ssocket_.readAll());
    }
    else{
        ui->pteMessage->insertPlainText("Please check CheckBox\n");
    }
}
void Widget::on_pbConnect_clicked()
{
    if (ui->TCPcheck->isChecked()){
        tsocket_.connectToHost(ui->leHost->text(),ui->lePort->text().toUShort());
    }
    else if (ui->SSLcheck->isChecked()){
        ssocket_.connectToHostEncrypted(ui->leHost->text(),ui->lePort->text().toUShort());
    }
    else{
        ui->pteMessage->insertPlainText("Please check CheckBox\n");
    }
}


void Widget::on_pbDisconnet_clicked()
{
    if (ui->TCPcheck->isChecked()){
        tsocket_.close();
    }
    else if (ui->SSLcheck->isChecked()){
        ssocket_.close();
    }
    else{
        ui->pteMessage->insertPlainText("Please check CheckBox\n");
    }
}


void Widget::on_pbSend_clicked()
{
    if (ui->TCPcheck->isChecked()){
        tsocket_.write(ui->pteSend->toPlainText().toUtf8());
    }
    else if (ui->SSLcheck->isChecked()){
        ssocket_.write(ui->pteSend->toPlainText().toUtf8());
    }
    else{
        ui->pteMessage->insertPlainText("Please check CheckBox\n");
    }
}


void Widget::on_TCPcheck_stateChanged(int state)
{
    bool isChecked = state != Qt::Unchecked;
    ui->SSLcheck->setEnabled(!isChecked);
}


void Widget::on_SSLcheck_stateChanged(int state)
{
    bool isChecked = state != Qt::Unchecked;
    ui->TCPcheck->setEnabled(!isChecked);
}


void Widget::on_pbClear_clicked()
{
    ui->pteMessage->clear();
}

