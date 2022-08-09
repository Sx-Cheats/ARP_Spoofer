#include "../headers/window.moc"
#include<windows.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground); 
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void CloseApp()
{
    Spoof.Started=false;
    ResetGateway();
    a->exit();
}

void MinimizeApp()
{
    w->showMinimized();
}


int main(int argc, char *argv[])
{
    a = new QApplication(argc, argv);
    w =  new MainWindow;
    w->setWindowTitle("ARP Spoofer");
    w->show();
    return a->exec();
}
