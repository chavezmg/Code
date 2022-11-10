#include "mainwindow.h"
#include "ui_mainwindow.h"

bool percentagelcd4 = false;
bool percentagelcd3 = false;
bool percentagelcd2 = false;
bool percentagelcd1 = false;
char salidas[9]={'0','0','0','0','0','0','0','0', 'n'};
char salidas2[8];
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort();
    serial_disponible = false;
    serialBuffer = "";

    foreach(const QSerialPortInfo &serial_info, QSerialPortInfo::availablePorts()){
        qDebug()<<"Puerto: "<<serial_info.portName();
        portname = serial_info.portName();
        qDebug()<<"Vendor Id: " <<serial_info.vendorIdentifier();
        vendorId = serial_info.vendorIdentifier();
        qDebug()<<"Product Id:" <<serial_info.productIdentifier();
        productId = serial_info.productIdentifier();
        serial_disponible = true;
    }
    if(serial_disponible){
        bluepill_init();
        ui->label_16->setText("Conectado");
    }
    else{
        ui->label_16->setText("No conectado");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::bluepill_init()
{
    serial->setPortName(portname);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadWrite);
    connect(serial, SIGNAL(readyRead()), this, SLOT(serial_read()));
}


void MainWindow::on_pushButton_ON_clicked()
{
    if(serial->isWritable()){
        serial->write("1");
        qDebug()<<"Encender";
    }
}


void MainWindow::on_pushButton_OFF_clicked()
{
    if(serial->isWritable()){
        serial->write("2");
        qDebug()<<"Apagar";
    }
}

void MainWindow::serial_read()
{
    //QStringList bufferSplit =
    if(serial->isWritable()&&serial_disponible){
        QByteArray serialData = serial->readAll();
        serialBuffer += QString::fromStdString(serialData.toStdString());
        QStringList bufferSplit = serialBuffer.split("\n\r");
        if(bufferSplit.length()<3){
            serialData = serial->readAll();
            serialBuffer += QString::fromStdString(serialData.toStdString());
        }
        else{
            QStringList dataIn = bufferSplit[1].split(',');
            qDebug() << bufferSplit;

            double conversion1 = 0.014648437;
            double conversion3 = 0.002441406;
            double conversion4 = 0.001220703;
            double vlcd4 = (dataIn[8].toFloat() * conversion4) - 2.5;
            double vlcd3 = dataIn[9].toFloat() * conversion3;
            double vlcd2 = dataIn[10].toFloat() * conversion3;
            double vlcd1 = dataIn[11].toFloat() * conversion1;
            ui->lcdNumber_13->display(dataIn[7]);
            ui->lcdNumber_12->display(dataIn[6]);
            ui->lcdNumber_11->display(dataIn[5]);
            ui->lcdNumber_10->display(dataIn[4]);
            ui->lcdNumber_9->display(dataIn[3]);
            ui->lcdNumber_8->display(dataIn[2]);
            ui->lcdNumber_7->display(dataIn[1]);
            ui->lcdNumber_6->display(dataIn[0]);
            ui->lcdNumber_5->display(bufferSplit[1]);//string que llega al qt
            ui->lcdNumber_4->display((percentagelcd4 == true? ((dataIn[8].toFloat()*100)/4096):vlcd4));    //-2,5-2.5
            ui->lcdNumber_3->display((percentagelcd3 == true? ((dataIn[9].toFloat()*100)/4096):vlcd3));    //0-10 b
            ui->lcdNumber_2->display((percentagelcd2 == true? ((dataIn[10].toFloat()*100)/4096):vlcd2));    //0-10 a
            ui->lcdNumber->display((percentagelcd1 == true? (dataIn[11].toFloat()):vlcd1));      //lm35

            ui->lcdNumber_21->display(dataIn[19]);
            ui->lcdNumber_20->display(dataIn[18]);
            ui->lcdNumber_19->display(dataIn[17]);
            ui->lcdNumber_18->display(dataIn[16]);
            ui->lcdNumber_17->display(dataIn[15]);
            ui->lcdNumber_16->display(dataIn[14]);
            ui->lcdNumber_15->display(dataIn[13]);
            ui->lcdNumber_14->display(dataIn[12]);


            serialBuffer = "";
        }
    }

}


void MainWindow::on_checkBox_toggled(bool checked)
{
    if(ui->checkBox->isChecked()){
            salidas[0] = '1';
        }
        else{
            salidas[0] = '0';
        }
    qDebug()<<"Salidas: "<<salidas[0]<<salidas[1]<<salidas[2]<<salidas[3]<<salidas[4]<<salidas[5]<<salidas[6]<<salidas[7];
}


void MainWindow::on_checkBox_2_toggled(bool checked)
{
    if(ui->checkBox_2->isChecked()){
            salidas[1] = '1';
        }
        else{
            salidas[1] = '0';
        }
    qDebug()<<"Salidas: "<<salidas[0]<<salidas[1]<<salidas[2]<<salidas[3]<<salidas[4]<<salidas[5]<<salidas[6]<<salidas[7];
}


void MainWindow::on_checkBox_3_toggled(bool checked)
{
    if(ui->checkBox_3->isChecked()){
            salidas[2] = '1';
        }
        else{
            salidas[2] = '0';
        }
    qDebug()<<"Salidas: "<<salidas[0]<<salidas[1]<<salidas[2]<<salidas[3]<<salidas[4]<<salidas[5]<<salidas[6]<<salidas[7];
}


void MainWindow::on_checkBox_4_toggled(bool checked)
{
    if(ui->checkBox_4->isChecked()){
            salidas[3] = '1';
        }
        else{
            salidas[3] = '0';
        }
    qDebug()<<"Salidas: "<<salidas[0]<<salidas[1]<<salidas[2]<<salidas[3]<<salidas[4]<<salidas[5]<<salidas[6]<<salidas[7];
}


void MainWindow::on_checkBox_5_toggled(bool checked)
{
    if(ui->checkBox_5->isChecked()){
            salidas[4] = '1';
        }
        else{
            salidas[4] = '0';
        }
    qDebug()<<"Salidas: "<<salidas[0]<<salidas[1]<<salidas[2]<<salidas[3]<<salidas[4]<<salidas[5]<<salidas[6]<<salidas[7];
}


void MainWindow::on_checkBox_6_toggled(bool checked)
{
    if(ui->checkBox_6->isChecked()){
            salidas[5] = '1';
        }
        else{
            salidas[5] = '0';
        }
    qDebug()<<"Salidas: "<<salidas[0]<<salidas[1]<<salidas[2]<<salidas[3]<<salidas[4]<<salidas[5]<<salidas[6]<<salidas[7];
}


void MainWindow::on_checkBox_7_toggled(bool checked)
{
    if(ui->checkBox_7->isChecked()){
            salidas[6] = '1';
        }
        else{
            salidas[6] = '0';
        }
    qDebug()<<"Salidas: "<<salidas[0]<<salidas[1]<<salidas[2]<<salidas[3]<<salidas[4]<<salidas[5]<<salidas[6]<<salidas[7];
}


void MainWindow::on_checkBox_8_toggled(bool checked)
{
    if(ui->checkBox_8->isChecked()){
            salidas[7] = '1';
        }
        else{
            salidas[7] = '0';
        }
    qDebug()<<"Salidas: "<<salidas[0]<<salidas[1]<<salidas[2]<<salidas[3]<<salidas[4]<<salidas[5]<<salidas[6]<<salidas[7];
}




void MainWindow::on_pushButton_clicked()
{
        serial->write(salidas);
        qDebug()<<salidas;
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->checkBox->setChecked(true);
    ui->checkBox_2->setChecked(true);
    ui->checkBox_3->setChecked(true);
    ui->checkBox_4->setChecked(true);
    ui->checkBox_5->setChecked(true);
    ui->checkBox_6->setChecked(true);
    ui->checkBox_7->setChecked(true);
    ui->checkBox_8->setChecked(true);
}


void MainWindow::on_pushButton_2_pressed()
{
    ui->checkBox->setChecked(true);
    ui->checkBox_2->setChecked(true);
    ui->checkBox_3->setChecked(true);
    ui->checkBox_4->setChecked(true);
    ui->checkBox_5->setChecked(true);
    ui->checkBox_6->setChecked(true);
    ui->checkBox_7->setChecked(true);
    ui->checkBox_8->setChecked(true);
}


void MainWindow::on_pushButton_3_pressed()
{
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->checkBox_4->setChecked(false);
    ui->checkBox_5->setChecked(false);
    ui->checkBox_6->setChecked(false);
    ui->checkBox_7->setChecked(false);
    ui->checkBox_8->setChecked(false);
}


void MainWindow::on_checkBox_9_pressed()
{
    if (ui->checkBox_9->isChecked())
        percentagelcd1 = false;
    else
        percentagelcd1 = true;

}


void MainWindow::on_checkBox_10_pressed()
{
    if (ui->checkBox_10->isChecked())
        percentagelcd2 = false;
    else
        percentagelcd2 = true;
}


void MainWindow::on_checkBox_11_pressed()
{
    if (ui->checkBox_11->isChecked())
        percentagelcd3 = false;
    else
        percentagelcd3 = true;
}


void MainWindow::on_checkBox_12_pressed()
{
    if (ui->checkBox_12->isChecked())
        percentagelcd4 = false;
    else
        percentagelcd4 = true;
}


void MainWindow::on_pushButton_4_clicked()
{
    if(ui->lcdNumber_6->value() == 1)
        ui->checkBox->setChecked(true);
    else
        ui->checkBox->setChecked(false);

    if(ui->lcdNumber_7->value() == 1)
        ui->checkBox_2->setChecked(true);
    else
        ui->checkBox_2->setChecked(false);

    if(ui->lcdNumber_8->value() == 1)
        ui->checkBox_3->setChecked(true);
    else
        ui->checkBox_3->setChecked(false);

    if(ui->lcdNumber_9->value() == 1)
        ui->checkBox_4->setChecked(true);
    else
        ui->checkBox_4->setChecked(false);

    if(ui->lcdNumber_10->value() == 1)
        ui->checkBox_5->setChecked(true);
    else
        ui->checkBox_5->setChecked(false);

    if(ui->lcdNumber_11->value() == 1)
        ui->checkBox_6->setChecked(true);
    else
        ui->checkBox_6->setChecked(false);

    if(ui->lcdNumber_12->value() == 1)
        ui->checkBox_7->setChecked(true);
    else
        ui->checkBox_7->setChecked(false);

    if(ui->lcdNumber_13->value() == 1)
        ui->checkBox_8->setChecked(true);
    else
        ui->checkBox_8->setChecked(false);
}


void MainWindow::on_pushButton_5_clicked()
{
    serial = new QSerialPort();
    serial_disponible = false;
    serialBuffer = "";

    foreach(const QSerialPortInfo &serial_info, QSerialPortInfo::availablePorts()){
        qDebug()<<"Puerto: "<<serial_info.portName();
        portname = serial_info.portName();
        qDebug()<<"Vendor Id: " <<serial_info.vendorIdentifier();
        vendorId = serial_info.vendorIdentifier();
        qDebug()<<"Product Id:" <<serial_info.productIdentifier();
        productId = serial_info.productIdentifier();
        serial_disponible = true;
    }
    if(serial_disponible){
        bluepill_init();
        ui->label_16->setText("Conectado");
    }
    else{
        ui->label_16->setText("No conectado");
    }
}

