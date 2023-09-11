#include "windownext.hpp"

WindowNext::WindowNext(MainWindow *parent)
    : QDialog(parent)
{
    this->putWindowOnScreen(800, 700);
    this->setModal(true);

    this->_groupBox1 = new QGroupBox("", this);
    this->_groupBox1->setGeometry(5, 5, 790, 30);
    this->_groupBox1->setStyleSheet("border: 1px #1c4684; background: #1c4684;");

    this->_label1 = new QLabel("COREAPB3:4.2.100", this);
    this->_label1->setGeometry(10, 40, 300, 30);
    this->_label1->setStyleSheet("color: black; font-size: 20px; font-weight: bold;");
}

WindowNext::~WindowNext()
{
    delete _groupBox1;
    _groupBox1 = nullptr;

    delete _label1;
    _label1 = nullptr;
}

void    WindowNext::putWindowOnScreen(int windowWidth, int windowHeight)
{
    // put window to the center of the screen
    QScreen *screen = QApplication::primaryScreen();
    QSize screenSize = screen->size();
    int screenWidth = screenSize.width();
    int screenHeight = screenSize.height();
    this->setGeometry((screenWidth - windowWidth) / 2, \
                    (screenHeight - windowHeight) / 2, \
                      windowWidth, windowHeight);
    this->setMinimumSize(windowWidth, windowHeight);
    this->setMaximumSize(windowWidth, windowHeight);

    // set title, icon, and background of window
    this->setWindowTitle("CoreAPB3_C0* [active]");
    this->setWindowIcon(QIcon(":/Imgs/logo.ico"));
    this->setStyleSheet("background: #f7f8fb;");
}
