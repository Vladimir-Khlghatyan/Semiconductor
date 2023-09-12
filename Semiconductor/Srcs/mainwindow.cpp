#include "mainwindow.hpp"
#include "../ui_mainwindow.h"

#include "windownext.hpp"
#include "styles.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // put window to the center of the screen
    this->putWindowOnScreen(700, 350);

    // create buttons "about" and "next" with appropriate parameters
    this->_buttonAbout = this->createButton(this, ":/Imgs/about.png", 420, 230, 80, 40, "about the application", &MainWindow::buttonAboutAction);
    this->_buttonNext = this->createButton(this, ":/Imgs/next.png", 530, 230, 80, 40, "go to CoreAPB3_C0*", &MainWindow::buttonNextAction);
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

// create new button
QToolButton*    MainWindow::createButton(QWidget *parent, const QString& iconPath, \
                                      int ax, int ay, int aw, int ah, \
                                      const QString& toolTip, void (MainWindow::*action)(void))
{
    QToolButton *button = new QToolButton(parent);
    button->setIcon(QIcon(iconPath));
    button->setIconSize(QSize(aw / 1.5, ah / 1.5));
    button->setCursor(Qt::PointingHandCursor);
    button->setToolTip(toolTip);
    button->setStyleSheet(CUSTOM_STYLE1);
    button->setGeometry(ax, ay, aw, ah);
    button->show();
    connect(button, &QToolButton::clicked, this,
            [=](void) {
                if (action != nullptr)
                    (this->*action)();
            });
    return button;
}

// action for button "about"
void    MainWindow::buttonAboutAction(void)
{
    QString about = ABOUT;

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

