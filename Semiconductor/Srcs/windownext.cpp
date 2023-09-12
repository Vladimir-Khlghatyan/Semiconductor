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

    // create buttons "save", "print" and "resize" with appropriate parameters
    this->_buttonSave = this->createButton(_groupBox1, ":/Imgs/save.png", 10, 3, 24, 24, "save", CUSTOM_STYLE3, &WindowNext::buttonSaveAction);
    this->_buttonPrint = this->createButton(_groupBox1, ":/Imgs/print.png", 50, 3, 24, 24, "print", CUSTOM_STYLE3, &WindowNext::actionlessButton);
    this->_buttonResize = this->createButton(_groupBox1, ":/Imgs/resize.png", 90, 3, 24, 24, "resize", CUSTOM_STYLE3, &WindowNext::actionlessButton);

    // disable button "print
    _buttonPrint->setEnabled(false);

    // create first label with appropriate parameters and style
    this->_title = new QLabel("COREAPB3:4.2.100", this);
    this->_title->setGeometry(10, 40, 300, 30);
    this->_title->setStyleSheet(CUSTOM_STYLE4);

    // create second group box with appropriate parameters and style
    this->_groupBox2 = new QGroupBox("", this);
    this->_groupBox2->setGeometry(10, 80, 780, 36);
    this->_groupBox2->setStyleSheet(CUSTOM_STYLE5);

    this->_buttonGenerate = this->createButton(_groupBox2, ":/Imgs/generate.png", 10, 3, 120, 30, "generate", CUSTOM_STYLE7, &WindowNext::actionlessButton);
    this->_buttonDRC = this->createButton(_groupBox2, ":/Imgs/drc.png", 140, 3, 81, 30, "drc", CUSTOM_STYLE7, &WindowNext::actionlessButton);
    this->_buttonHelp = this->createButton(_groupBox2, ":/Imgs/help.png", 230, 3, 81, 30, "help", CUSTOM_STYLE7, &WindowNext::actionlessButton);

}

WindowNext::~WindowNext()
{
    delete _groupBox1;
    _groupBox1 = nullptr;

    delete _buttonSave;
    _buttonSave = nullptr;

    delete _buttonPrint;
    _buttonPrint = nullptr;

    delete _buttonResize;
    _buttonResize = nullptr;

    delete _title;
    _title = nullptr;

    delete _buttonGenerate;
    _buttonGenerate = nullptr;

    delete _buttonDRC;
    _buttonDRC = nullptr;

    delete _buttonHelp;
    _buttonHelp = nullptr;
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
    this->setStyleSheet(CUSTOM_STYLE6);
}

// create new button
QToolButton*    WindowNext::createButton(QWidget *parent, const QString& iconPath, \
                                      int ax, int ay, int aw, int ah, const QString& toolTip, \
                                      const QString& style, void (WindowNext::*action)(void))
{
    QToolButton *button = new QToolButton(parent);
    button->setIcon(QIcon(iconPath));
    button->setIconSize(QSize(aw, ah));
    button->setCursor(Qt::PointingHandCursor);
    button->setToolTip(toolTip);
    button->setStyleSheet(style);
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

// actionless button
void    WindowNext::actionlessButton(void)
{

    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Actionless button"));
    msgBox.setText("<br>The button is<br>currently actionless.");
    msgBox.setIconPixmap(QPixmap(":/Imgs/actionless.png"));
    msgBox.addButton(QMessageBox::Ok);
    msgBox.setWindowIcon(QIcon(":/Imgs/logo.ico"));
    msgBox.exec();
}


