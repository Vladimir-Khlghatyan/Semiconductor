#include "windownext.hpp"
#include <QDebug>

#include "styles.hpp"

WindowNext::WindowNext(MainWindow *parent)
    : QDialog(parent)
{
    // create window and put it on the screan
    this->putWindowOnScreen(800, 700);
    this->setModal(true);

    // create first group box with appropriate parameters and style
    this->_groupBox1 = new QGroupBox("", this);
    this->_groupBox1->setGeometry(5, 5, 790, 30);
    this->_groupBox1->setStyleSheet(CUSTOM_STYLE2);

    // create first label with appropriate parameters and style
    this->_label1 = new QLabel("COREAPB3:4.2.100", this);
    this->_label1->setGeometry(10, 40, 300, 30);
    this->_label1->setStyleSheet(CUSTOM_STYLE3);

    // create buttons "save", "print" and "resize" with appropriate parameters
    this->_buttonSave = this->createButton(_groupBox1, ":/Imgs/save.png", 5, 3, 24, 24, "save", &WindowNext::buttonSaveAction);
    this->_buttonPrint = this->createButton(_groupBox1, ":/Imgs/print.png", 45, 3, 24, 24, "print", nullptr);
    this->_buttonResize = this->createButton(_groupBox1, ":/Imgs/resize.png", 85, 3, 24, 24, "resize", nullptr);

    // disable button "print
    _buttonPrint->setEnabled(false);
}

WindowNext::~WindowNext()
{
    delete _groupBox1;
    _groupBox1 = nullptr;

    delete _label1;
    _label1 = nullptr;

    delete _buttonSave;
    _buttonSave = nullptr;

    delete _buttonPrint;
    _buttonPrint = nullptr;

    delete _buttonResize;
    _buttonResize = nullptr;
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

    // set window fixed size
    this->setFixedSize(windowWidth, windowHeight);

    // set title, icon, and background of window
    this->setWindowTitle("CoreAPB3_C0* [active]");
    this->setWindowIcon(QIcon(":/Imgs/logo.ico"));
    this->setStyleSheet(CUSTOM_STYLE4);
}

// create new button
QToolButton*    WindowNext::createButton(QWidget *parent, const QString& iconPath, \
                                      int ax, int ay, int aw, int ah, \
                                      const QString& toolTip, void (WindowNext::*action)(void))
{
    QToolButton *button = new QToolButton(parent);
    button->setIcon(QIcon(iconPath));
    button->setIconSize(QSize(aw, ah));
    button->setCursor(Qt::PointingHandCursor);
    button->setToolTip(toolTip);
    button->setStyleSheet(CUSTOM_STYLE5);
    button->setGeometry(ax, ay, aw, ah);
    button->show();
    connect(button, &QToolButton::clicked, this,
            [=](void) {
                if (action != nullptr)
                    (this->*action)();
            });
    return button;
}

void    WindowNext::buttonSaveAction(void)
{
    // write code here
}


