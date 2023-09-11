#include "mainwindow.hpp"
#include "../ui_mainwindow.h"

#include "windownext.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->_buttonAbout = nullptr;
    this->_buttonNext = nullptr;
    this->_windowNext = nullptr;

    this->putWindowOnScreen(700, 350);
    this->createButtonAbout(420, 230);
    this->createButtonNext(530, 230);
}

MainWindow::~MainWindow()
{
    delete ui;

    delete _buttonAbout;
    _buttonAbout = nullptr;

    delete _buttonNext;
    _buttonNext = nullptr;

    delete _windowNext;
    _windowNext = nullptr;
}

void    MainWindow::putWindowOnScreen(int windowWidth, int windowHeight)
{
    // put window to the center of the screen
    QScreen *screen = QApplication::primaryScreen();
    QSize screenSize = screen->size();
    int screenWidth = screenSize.width();
    int screenHeight = screenSize.height();
    this->setGeometry((screenWidth - windowWidth) / 2, \
                    (screenHeight - windowHeight) / 2, \
                      windowWidth, windowHeight);

    // set window fixed size
    this->setFixedSize(windowWidth, windowHeight);

    // set title, icon, and background of window
    this->setWindowTitle("Instigate Semiconductor");
    this->setWindowIcon(QIcon(":/Imgs/logo.ico"));
    this->setStyleSheet("background-image: url(:/Imgs/background.png); font-size: 20px");
}

// creating button "about"
void    MainWindow::createButtonAbout(int ax, int ay)
{
    this->_buttonAbout = new QToolButton(this);
    this->_buttonAbout->setIcon(QIcon(":/Imgs/about.png"));
    this->_buttonAbout->setIconSize(QSize(50, 25));
    this->_buttonAbout->setCursor(Qt::PointingHandCursor);
    this->_buttonAbout->setToolTip("about the application");
    this->_buttonAbout->setStyleSheet(MY_BUTTON_STYLE);
    this->_buttonAbout->setGeometry(ax, ay, 80, 40);
    this->_buttonAbout->show();
    connect(this->_buttonAbout, &QToolButton::clicked, this, [=](void) {this->buttonAboutAction(); });
}

// creating button "next"
void    MainWindow::createButtonNext(int ax, int ay)
{
    this->_buttonNext = new QToolButton(this);
    this->_buttonNext->setIcon(QIcon(":/Imgs/next.png"));
    this->_buttonNext->setIconSize(QSize(50, 25));
    this->_buttonNext->setCursor(Qt::PointingHandCursor);
    this->_buttonNext->setToolTip("go to CoreAPB3_C0*");
    this->_buttonNext->setStyleSheet(MY_BUTTON_STYLE);
    this->_buttonNext->setGeometry(ax, ay, 80, 40);
    this->_buttonNext->show();
    connect(this->_buttonNext, &QToolButton::clicked, this, [=](void) {this->buttonNextAction(); });
}

// action for button "about"
void    MainWindow::buttonAboutAction(void)
{
    QString about = "<b>IS Beta version 1.0</b> \
                        <br> <br> This application was created \
                        <br> as a requirement for joining the \
                        <br> <b>Instigate Semiconductor</b> team.  \
                        <br> <br>Author: <b>Vladimir Khlghatyan</b> \
                        <br> <br> ©2023. All rights reserved.";

    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("About the application"));
    msgBox.setText(about);
    msgBox.setIconPixmap(QPixmap(":/Imgs/info.png"));
    msgBox.addButton(QMessageBox::Ok);
    msgBox.setWindowIcon(QIcon(":/Imgs/logo.ico"));
    msgBox.exec();
}

// action for button "about"
void    MainWindow::buttonNextAction(void)
{
    try
    {
        this->_windowNext = new WindowNext(this);
        this->_windowNext->exec();
    }
    catch (...) {    }
}

