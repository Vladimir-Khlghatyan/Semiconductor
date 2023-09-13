#include "windownext.hpp"
#include <QDebug>
#include <QPixmap>
# include <QLayout>

#include "styles.hpp"

WindowNext::WindowNext(MainWindow *parent)
    : QDialog(parent)
{

    // init values
    _configIsActive = true;

    _texts.push_back({"12", "16", "20", "24", "28", "32"});
    _texts.push_back({"[27:24] (Ignored if master address width >= 32 bits)", \
                      "[23:20] (Ignored if master address width >= 28 bits)", \
                      "[19:16] (Ignored if master address width >= 24 bits)", \
                      "[15:12] (Ignored if master address width >= 20 bits)", \
                       "[11:8] (Ignored if master address width >= 16 bits)"});
    _texts.push_back({"Not in use", \
                      "Indirect address sourced from IADDR input port", \
                      "Indirect address sourced from register(s) in slot 0 space", \
                      "Indirect address sourced from register(s) in slot 1 space", \
                      "Indirect address sourced from register(s) in slot 2 space", \
                      "Indirect address sourced from register(s) in slot 3 space", \
                      "Indirect address sourced from register(s) in slot 4 space", \
                      "Indirect address sourced from register(s) in slot 5 space", \
                      "Indirect address sourced from register(s) in slot 6 space", \
                      "Indirect address sourced from register(s) in slot 7 space", \
                      "Indirect address sourced from register(s) in slot 8 space", \
                      "Indirect address sourced from register(s) in slot 9 space", \
                      "Indirect address sourced from register(s) in slot 10 space", \
                      "Indirect address sourced from register(s) in slot 11 space", \
                      "Indirect address sourced from register(s) in slot 12 space", \
                      "Indirect address sourced from register(s) in slot 13 space", \
                      "Indirect address sourced from register(s) in slot 14 space", \
                      "Indirect address sourced from register(s) in slot 15 space"});
    _texts.push_back({"User", "Option1", "Option2", "Option3"});



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


    // create blue line to switch from Configuration to Tools
    this->_blueLine = new QLabel("", this);
    this->_blueLine->setStyleSheet(CUSTOM_STYLE8);
    int ax = _configIsActive ? 20 : 150;
    this->_blueLine->setGeometry(ax, 151, 130, 2);


    // create groupBox for Configuration/Tools menu
    this->_groupBoxConfig = new QGroupBox("", this);
    this->_groupBoxConfig->setGeometry(5, 154, 790, 541);
    this->_groupBoxConfig->setStyleSheet(CUSTOM_STYLE9);

    this->_groupBoxTools = new QGroupBox("", this);
    this->_groupBoxTools->setGeometry(5, 154, 790, 541);
    this->_groupBoxTools->setStyleSheet(CUSTOM_STYLE9);
    if (_configIsActive == true)
    {
        _groupBoxConfig->show();
        _groupBoxTools->hide();
    }
    else
    {
        _groupBoxConfig->hide();
        _groupBoxTools->show();
    }


    // put underConstraction.png on Tools menu groupBox
    this->_underConstraction = new QLabel("", _groupBoxTools);
    this->_underConstraction->setGeometry(270, 145, 250, 250);
    this->_underConstraction->setStyleSheet("border: none;");
    QPixmap pixmap(":/Imgs/underConstraction.png");
    _underConstraction->setPixmap(pixmap);


    // create buttons "Configuration" and "Tools" with appropriate parameters
    this->_buttonConfig = this->createButton(this, "", 20, 120, 130, 30, "configuration", CUSTOM_STYLE10, &WindowNext::buttonConfigAction);
    _buttonConfig->setText("Configuration");
    this->_buttonTools = this->createButton(this, "", 150, 120, 130, 30, "tools", CUSTOM_STYLE10, &WindowNext::buttonTollsAction);
    _buttonTools->setText("Tools");


    // create section titles for 'Configuration' menu
    const QStringList title1 = {"DATA WITH CONFIGURATION", \
                                "ADDRESS CONFIGURATION", \
                                "ALLOCATE MEMORY SPACE TO COMBINED REGION SLAVE", \
                                "ENABLED APB SLAVE SLOTS"};
    const int coor1[4][4] = {{20,   1, 400, 25}, \
                             {20,  58, 400, 25}, \
                             {20, 175, 400, 25}, \
                             {20, 322, 400, 25}};
    for (int i{}; i < 4; ++i)
    {
        this->_sectionTitles.push_back(new QLabel(title1[i], _groupBoxConfig));
        this->_sectionTitles[i]->setGeometry(coor1[i][0], coor1[i][1], coor1[i][2], coor1[i][3]);
        this->_sectionTitles[i]->setStyleSheet(CUSTOM_STYLE11);
    }


    // create 4 groupBoxes for 'Configuration' menu
    // coordinates of groupBoxes on _groupBoxConfig
    const int coor2[4][4] = {{1,  27, 787,  30}, \
                             {1,  84, 787,  90}, \
                             {1, 201, 787, 120}, \
                             {1, 348, 787, 191}};
    for (int i{}; i < 4; ++i)
    {
        this->_groupBoxSections.push_back(new QGroupBox("", _groupBoxConfig));
        this->_groupBoxSections[i]->setGeometry(coor2[i][0], coor2[i][1], coor2[i][2], coor2[i][3]);
        this->_groupBoxSections[i]->setStyleSheet(CUSTOM_STYLE12);
    }


    // create description texts for sections in 'Configuration' menu
    const QStringList title2 = {"APB Master Data Bug Width", \
                                "Number of address bits driven by master:", \
                                "Position in slave address of upper 4 bits of master address:", \
                                "Indirect Addressing:", "Testbench:", "License:"};
    const int coor3[6][4] = {{30,   2, 180, 26}, \
                             {30,   2, 365, 26}, \
                             {30,  32, 365, 26}, \
                             {30,  62, 365, 26}, \
                             {30, 127,  70, 26}, \
                             {30, 155,  70, 26}};
    const int boxID1[6] = {0, 1, 1, 1, 3, 3};
    for (int i{}; i < 6; ++i)
    {
        this->_descriptions.push_back(new QLabel(title2[i], _groupBoxSections[boxID1[i]]));
        this->_descriptions[i]->setGeometry(coor3[i][0], coor3[i][1], coor3[i][2], coor3[i][3]);
        this->_descriptions[i]->setStyleSheet(CUSTOM_STYLE13);
    }


    // create radiobuttons
    const QStringList title3 = {"32-bit", "16-bit", "8-bit", "Obfuscated", "RTL"};
    const int coor4[5][4] = {{220,   2,  60, 26}, \
                             {300,   2,  60, 26}, \
                             {380,   2,  60, 26}, \
                             {110, 155, 100, 26}, \
                             {230, 155, 100, 26}};
    const int boxID2[5] = {0, 0, 0, 3, 3};
    for (int i{}; i < 5; ++i)
    {
        this->_radiobuttons.push_back(new QRadioButton(title3[i], _groupBoxSections[boxID2[i]]));
        this->_radiobuttons[i]->setGeometry(coor4[i][0], coor4[i][1], coor4[i][2], coor4[i][3]);
        this->_radiobuttons[i]->setStyleSheet(CUSTOM_STYLE13);
        connect(_radiobuttons[i], &QRadioButton::clicked, this,
                [=](void)
                {
                    qDebug() << _radiobuttons[i]->text();
                });
    }


    //create comboboxes
    const int coor5[4][4] = {{410,   2, 350, 26}, \
                             {410,  32, 350, 26}, \
                             {410,  62, 350, 26}, \
                             {120, 127, 100, 26}};
    const int boxID3[4] = {1, 1, 1, 3};
    for (int i{}; i < 4; ++i)
    {
        this->_comboboxes.push_back(new QComboBox(_groupBoxSections[boxID3[i]]));
        this->_comboboxes[i]->addItems(_texts[i]);
        this->_comboboxes[i]->setGeometry(coor5[i][0], coor5[i][1], coor5[i][2], coor5[i][3]);
//        this->_comboboxes[i]->setStyleSheet();
        connect(this->_comboboxes[i], &QComboBox::currentTextChanged, this,
                [=](void)
                {
                    qDebug() << _comboboxes[i]->currentText();
                });
    }
}

WindowNext::~WindowNext()
{
    delete _groupBoxSaveButton;
    delete _groupBoxGenerateButton;
    delete _buttonSave;
    delete _buttonPrint;
    delete _buttonResize;
    delete _title;
    delete _buttonGenerate;
    delete _buttonDRC;
    delete _buttonHelp;
    delete _blueLine;
    delete _groupBoxConfig;
    delete _groupBoxTools;
    delete _underConstraction;
    delete _buttonConfig;
    delete _buttonTools;

    for (auto title : _sectionTitles)
        delete title;

    for (auto groupBox : _groupBoxSections)
        delete groupBox;

    for (auto _description : _descriptions)
        delete _description;

    for (auto _radiobutton : _radiobuttons)
        delete _radiobutton;

    for (auto _combobox : _comboboxes)
        delete _combobox;
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
        _groupBoxConfig->show();
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
        _groupBoxConfig->hide();
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


