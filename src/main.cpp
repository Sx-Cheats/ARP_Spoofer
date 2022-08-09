#include "../headers/window.moc"
#include<windows.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->setWindowFlag(Qt::FramelessWindowHint); // no border (parend redefine Winproc of window)
    this->setAttribute(Qt::WA_TranslucentBackground); // Widgets is Translucide
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
    w->show();
    return a->exec();
}
