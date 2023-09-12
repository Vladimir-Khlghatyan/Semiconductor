#include "windownext.hpp"
#include <QDebug>
#include <QPixmap>
# include <QLayout>

#include "styles.hpp"

WindowNext::WindowNext(MainWindow *parent)
    : QDialog(parent)
{
    // create window and put it on the screan
    this->putWindowOnScreen(800, 700);
    this->setModal(true);

    // create first group box with appropriate parameters and style
    this->_groupBoxSaveButton = new QGroupBox("", this);
    this->_groupBoxSaveButton->setGeometry(5, 5, 790, 30);
    this->_groupBoxSaveButton->setStyleSheet(CUSTOM_STYLE2);


    // create buttons "save", "print" and "resize" with appropriate parameters
    this->_buttonSave = this->createButton(_groupBoxSaveButton, ":/Imgs/save.png", 10, 3, 24, 24, "save", CUSTOM_STYLE3, &WindowNext::buttonSaveAction);
    this->_buttonPrint = this->createButton(_groupBoxSaveButton, ":/Imgs/print.png", 50, 3, 24, 24, "print", CUSTOM_STYLE3, &WindowNext::actionlessButton);
    this->_buttonResize = this->createButton(_groupBoxSaveButton, ":/Imgs/resize.png", 90, 3, 24, 24, "resize", CUSTOM_STYLE3, &WindowNext::actionlessButton);


    // disable button "print
    _buttonPrint->setEnabled(false);

    // create first label with appropriate parameters and style
    this->_title = new QLabel("COREAPB3:4.2.100", this);
    this->_title->setGeometry(10, 40, 300, 30);
    this->_title->setStyleSheet(CUSTOM_STYLE4);


    // create second group box with appropriate parameters and style
    this->_groupBoxGenerateButton = new QGroupBox("", this);
    this->_groupBoxGenerateButton->setGeometry(10, 80, 780, 30);
    this->_groupBoxGenerateButton->setStyleSheet(CUSTOM_STYLE5);


    // create buttons "Generate", "DRC" and "Help" with appropriate parameters
    this->_buttonGenerate = this->createButton(_groupBoxGenerateButton, ":/Imgs/generate.png", 10, 3, 96, 24, "generate", CUSTOM_STYLE7, &WindowNext::actionlessButton);
    this->_buttonDRC = this->createButton(_groupBoxGenerateButton, ":/Imgs/drc.png", 120, 3, 65, 24, "drc", CUSTOM_STYLE7, &WindowNext::actionlessButton);
    this->_buttonHelp = this->createButton(_groupBoxGenerateButton, ":/Imgs/help.png", 200, 3, 65, 24, "help", CUSTOM_STYLE7, &WindowNext::actionlessButton);

    _configIsActive = true;

    // create blue line to switch from Configuration to Tools
    this->_blueLine = new QLabel("", this);
    this->_blueLine->setStyleSheet(CUSTOM_STYLE8);
    int ax = _configIsActive ? 20 : 150;
    this->_blueLine->setGeometry(ax, 151, 130, 2);


    // create groupBox for Tools menu
    this->_groupBoxTools = new QGroupBox("", this);
    this->_groupBoxTools->setGeometry(5, 154, 790, 541);
    this->_groupBoxTools->setStyleSheet(CUSTOM_STYLE9);
    if (_configIsActive == true)
        _groupBoxTools->hide();
    else
        _groupBoxTools->show();


    // put underConstraction.png on Tools menu groupBox
    this->_underConstraction = new QLabel("Temp", _groupBoxTools);
    this->_underConstraction->setGeometry(270, 145, 250, 250);
    this->_underConstraction->setStyleSheet("border: none;");
    QPixmap pixmap(":/Imgs/underConstraction.png");
    _underConstraction->setPixmap(pixmap);


    // create buttons "Configuration" and "Tools" with appropriate parameters
    this->_buttonConfig = this->createButton(this, "", 20, 120, 130, 30, "configuration", CUSTOM_STYLE10, &WindowNext::buttonConfigAction);
    _buttonConfig->setText("Configuration");
    this->_buttonTools = this->createButton(this, "", 150, 120, 130, 30, "tools", CUSTOM_STYLE10, &WindowNext::buttonTollsAction);
    _buttonTools->setText("Tools");

}

WindowNext::~WindowNext()
{
    delete _groupBoxSaveButton;
    _groupBoxSaveButton = nullptr;

    delete _groupBoxGenerateButton;
    _groupBoxGenerateButton = nullptr;

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

    delete _blueLine;
    _blueLine = nullptr;

    delete _groupBoxTools;
    _groupBoxTools = nullptr;

    delete _underConstraction;
    _underConstraction = nullptr;

    delete _buttonConfig;
    _buttonConfig = nullptr;

    delete _buttonTools;
    _buttonTools = nullptr;
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
    if (iconPath != "")
    {
        button->setIcon(QIcon(iconPath));
        button->setIconSize(QSize(aw, ah));
    }
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

// action for 'save' button
void    WindowNext::buttonSaveAction(void)
{
    // write code here
}

// action for 'Configuration' button
void    WindowNext::buttonConfigAction(void)
{
    if (_configIsActive == false)
    {
        _configIsActive = true;
        _blueLine->setGeometry(20, 151, 130, 2);
        _groupBoxTools->hide();
    }
}

// action for 'Tools' button
void    WindowNext::buttonTollsAction(void)
{
    if (_configIsActive == true)
    {
        _configIsActive = false;
        _blueLine->setGeometry(150, 151, 130, 2);
        _groupBoxTools->show();
    }
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


