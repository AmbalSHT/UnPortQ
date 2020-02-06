// Родитель виджета не передается при использовании компоновщика

#include "TcpServer/tcpserver.h"

void TcpServer::GuiInit()
{
    // Main Window
    this->setGeometry(0, 0, 500, 500);

    // Главная разметка
    QGridLayout* layout = new QGridLayout(this);

    // tabMain
    QTabWidget* tabMain = new QTabWidget();
    layout->addWidget(tabMain, 0, 0);

        // Tab wgHostParameters
        QWidget* wgHostParameters = new QWidget();
        tabMain->addTab(wgHostParameters, "Параметры хоста");
        QGridLayout* layHostParameters = new QGridLayout(wgHostParameters);
        layHostParameters->setColumnStretch(1, 1);
            // IP addresses group box
            QGroupBox* gbIpAddresses = new QGroupBox("IP адреса хоста");
            layHostParameters->addWidget(gbIpAddresses, 0, 0, 1, 2);
                // IP addresses radio buttons
                QGridLayout* layIpAddresses = new QGridLayout(gbIpAddresses);
                QNetworkInterface* interfaces = new QNetworkInterface();
                QList<QHostAddress> listInterfaces = interfaces->allAddresses();
                QRadioButton* rbIpAddress[listInterfaces.length()];
                QLineEdit* linIpAddresses[listInterfaces.length()];
                for(int i = 0; i < (int)(sizeof(rbIpAddress)/sizeof(rbIpAddress[0])); ++i)
                {
                    rbIpAddress[i] = new QRadioButton("Адрес " + QString::number(i + 1));
                    rbIpAddress[i]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
                    layIpAddresses->addWidget(rbIpAddress[i], i, 0);
                    linIpAddresses[i] = new QLineEdit(listInterfaces[i].toString());
                    linIpAddresses[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
                    linIpAddresses[i]->setReadOnly(true);
                    layIpAddresses->addWidget(linIpAddresses[i], i, 1);
                }
                rbIpAddress[0]->setChecked(true);
            // Host Port group box
            QGroupBox* gbHostPort = new QGroupBox("Порт");
            gbHostPort->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            layHostParameters->addWidget(gbHostPort, 1, 0);
                // Host port labels
                QGridLayout* layHostPort = new QGridLayout(gbHostPort);
                QLabel* lblPort = new QLabel("Номер порта");
                lblPort->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
                layHostPort->addWidget(lblPort, 0, 0);
                QLineEdit* linHostPort = new QLineEdit("1585");
                linHostPort->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
                linHostPort->setInputMask("00000");
                layHostPort->addWidget(linHostPort, 0, 1);

            // Host start
            QGroupBox* gbHostState = new QGroupBox("Статус сервера");
            gbHostState->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            layHostParameters->addWidget(gbHostState, 1, 1);
                // Host start widgets
                QGridLayout* layHostState = new QGridLayout(gbHostState);
                layHostState->setHorizontalSpacing(20);
                QPushButton* butHostStart = new QPushButton("Запуск");
                butHostStart->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
                connect(butHostStart, SIGNAL(released()), this, SLOT(butHostStart_Click()));
                layHostState->addWidget(butHostStart, 0, 0);
                QLabel* lblHostStatus = new QLabel("Остановлен");
                layHostState->addWidget(lblHostStatus, 0, 1);

            // Filler
            QLabel* lblFiller1 = new QLabel("");
            lblFiller1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            layHostParameters->addWidget(lblFiller1, 2, 0);

        // Tab Client
        QWidget* wgClient = new QWidget();
        tabMain->addTab(wgClient, "Обмен данными");
        QGridLayout* layClient = new QGridLayout(wgClient);
            // Group box Client parameters
            QGroupBox* gbClientParameters = new QGroupBox("Параметры клиента");
            gbClientParameters->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            layClient->addWidget(gbClientParameters, 0, 0);
                // Client parameters info
                QGridLayout* layClientParameters = new QGridLayout(gbClientParameters);
                QLabel* lblClientHostName = new QLabel("Имя");
                layClientParameters->addWidget(lblClientHostName, 0, 0);
                QLineEdit* linClientHostName = new QLineEdit("Nothing");
                linClientHostName->setReadOnly(true);
                layClientParameters->addWidget(linClientHostName, 0, 1, 1, 3);
                QLabel* lblClientIpAddress = new QLabel("IP адрес");
                layClientParameters->addWidget(lblClientIpAddress, 1, 0);
                QLineEdit* linClientIpAddress = new QLineEdit("Nothing");
                linClientIpAddress->setReadOnly(true);
                layClientParameters->addWidget(linClientIpAddress, 1, 1);
                QLabel* lblClientPort = new QLabel("Порт");
                layClientParameters->addWidget(lblClientPort, 1, 2);
                QLineEdit* linClientPort = new QLineEdit("Noting");
                linClientPort->setReadOnly(true);
                layClientParameters->addWidget(linClientPort, 1, 3);
            // Group box Data
            QGroupBox* gbData = new QGroupBox("Обмен данными");
            layClient->addWidget(gbData, 1, 0);
                // Table
                QGridLayout* layDataTable = new QGridLayout(gbData);
                QTableWidget* tblDataTable = new QTableWidget(0, 3);
                tblDataTable->setHorizontalHeaderLabels(QStringList() << "Время" << "Направление" << "Данные");
                tblDataTable->setColumnWidth(1, 120);
                tblDataTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
                layDataTable->addWidget(tblDataTable);

            // Group box SendData
            QGroupBox* gbSendData = new QGroupBox("Отправка данных");
            gbSendData->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            layClient->addWidget(gbSendData, 2, 0);
                // Send Data controls
                QGridLayout* laySendData = new QGridLayout(gbSendData);
                QLineEdit* linSendData = new QLineEdit();
                laySendData->addWidget(linSendData, 0, 0, 1, 4);
                QLineEdit* lineSendCRC = new QLineEdit();
                lineSendCRC->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
                lineSendCRC->setReadOnly(true);
                laySendData->addWidget(lineSendCRC, 0, 4);
                QLabel* lblSendDataFormat = new QLabel("Формат данных");
                lblSendDataFormat->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
                laySendData->addWidget(lblSendDataFormat, 1, 0);
                QComboBox* cmbSendDataFormat = new QComboBox();
                cmbSendDataFormat->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
                cmbSendDataFormat->setEnabled(false);
                    cmbSendDataFormat->addItem("ASCII");
                    cmbSendDataFormat->addItem("HEX");
                laySendData->addWidget(cmbSendDataFormat, 1, 1);
                QLabel* lblFiller2 = new QLabel("");
                laySendData->addWidget(lblFiller2, 1, 2);
                QPushButton *butSend = new QPushButton("Отправить");
                butSend->setEnabled(false);
                connect(butSend, SIGNAL(released()), this, SLOT(butSend_Click()));
                laySendData->addWidget(butSend, 1, 3);
                QComboBox* cmbSendCRC = new QComboBox();
                cmbSendCRC->setEnabled(false);
                    cmbSendCRC->addItem("CRC: None");
                    cmbSendCRC->addItem("CRC-8");
                    cmbSendCRC->addItem("CRC-16");
                laySendData->addWidget(cmbSendCRC, 1, 4);
}
