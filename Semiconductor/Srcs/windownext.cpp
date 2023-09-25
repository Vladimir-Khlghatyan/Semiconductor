#include "windownext.hpp"
#include <QDebug>
#include <QPixmap>
#include <QLayout>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStandardPaths>
#include <QDir>

#include "styles.hpp"

WindowNext::WindowNext(MainWindow *parent)
    : QDialog(parent)
{
    // init values
    this->initValues();

    // try to read state variables from the JSON file
    this->readStateFromJSON();

    // create window and put it on the screan
    this->putWindowOnScreen(800, 710);
    this->setModal(true);


//     create buttons "save", "print" and "resize" with appropriate parameters
    this->_buttonSave = this->createButton(":/Imgs/save.png", 24, 24, "save", CUSTOM_STYLE3, &WindowNext::buttonSaveAction);
    this->_buttonPrint = this->createButton(":/Imgs/print.png", 24, 24, "print", CUSTOM_STYLE3, &WindowNext::actionlessButton);
    this->_buttonResize = this->createButton(":/Imgs/resize.png", 24, 24, "resize", CUSTOM_STYLE3, &WindowNext::actionlessButton);

//     disable button "print
    _buttonPrint->setEnabled(false);


    // create first label with appropriate parameters and style
    this->_title = new QLabel("COREAPB3:4.2.100", this);
    this->_title->setStyleSheet(CUSTOM_STYLE4);


    // create buttons "Generate", "DRC" and "Help" with appropriate parameters
    this->_buttonGenerate = this->createButton(":/Imgs/generate.png", 96, 22, "generate", CUSTOM_STYLE7, &WindowNext::actionlessButton);
    this->_buttonDRC = this->createButton(":/Imgs/drc.png", 65, 22,  "drc", CUSTOM_STYLE7, &WindowNext::actionlessButton);
    this->_buttonHelp = this->createButton(":/Imgs/help.png", 65, 22, "help", CUSTOM_STYLE7, &WindowNext::actionlessButton);


    // create blue line to switch from Configuration to Tools
    this->_blueLine = new QLabel("", this);
    this->_blueLine->setStyleSheet(CUSTOM_STYLE8);
    int ax = _configIsActive ? 20 : 150;
    int ay = _configIsActive ? 149 : 153;
    this->_blueLine->setGeometry(ax, ay, 130, 2);


    // create groupBoxes for Configuration/Tools menu
    this->_groupBoxConfig = new QGroupBox("", this);
    this->_groupBoxTools  = new QGroupBox("", this);
    this->_groupBoxConfig->setStyleSheet(CUSTOM_STYLE9);
    this->_groupBoxTools->setStyleSheet(CUSTOM_STYLE9);


    // put underConstraction.png on Tools menu groupBox
    this->_underConstraction = new QLabel("", _groupBoxTools);
    this->_underConstraction->setGeometry(270, 145, 250, 250);
    this->_underConstraction->setStyleSheet("border: none;");
    QPixmap pixmap(":/Imgs/underConstraction.png");
    _underConstraction->setPixmap(pixmap);


    // create buttons "Configuration" and "Tools" with appropriate parameters
    this->_buttonConfig = this->createButton("", 130, 30, "    Configuration", CUSTOM_STYLE10, &WindowNext::buttonConfigAction);
    this->_buttonTools = this->createButton("", 130, 30, "\u00A0\u00A0\u00A0\u00A0\u00A0Tools", CUSTOM_STYLE10, &WindowNext::buttonTollsAction);


    // create section titles for 'Configuration' menu
    for (int i{}; i < 4; ++i)
    {
        this->_sectionTitles.push_back(new QLabel(_titles[0][i], _groupBoxConfig));
        this->_sectionTitles[i]->setGeometry(_coord[0][i][0], _coord[0][i][1], _coord[0][i][2], _coord[0][i][3]);
        this->_sectionTitles[i]->setStyleSheet(CUSTOM_STYLE11);
    }


    // create 4 groupBoxes for 'Configuration' menu
    for (int i{}; i < 4; ++i)
    {
        this->_groupBoxSections.push_back(new QGroupBox("", _groupBoxConfig));
        this->_groupBoxSections[i]->setGeometry(_coord[1][i][0], _coord[1][i][1], _coord[1][i][2], _coord[1][i][3]);
        this->_groupBoxSections[i]->setStyleSheet(CUSTOM_STYLE12);
    }


    // create description texts for sections in 'Configuration' menu
    for (int i{}; i < 6; ++i)
    {
        this->_descriptions.push_back(new QLabel(_titles[1][i], _groupBoxSections[_boxID[0][i]]));
        this->_descriptions[i]->setGeometry(_coord[2][i][0], _coord[2][i][1], _coord[2][i][2], _coord[2][i][3]);
        this->_descriptions[i]->setStyleSheet(CUSTOM_STYLE13);
    }


    // create radiobuttons
    for (int i{}; i < 5; ++i)
    {
        this->_radiobuttons.push_back(new QRadioButton(_titles[2][i], _groupBoxSections[_boxID[1][i]]));
        this->_radiobuttons[i]->setGeometry(_coord[3][i][0], _coord[3][i][1], _coord[3][i][2], _coord[3][i][3]);
        this->_radiobuttons[i]->setStyleSheet(CUSTOM_STYLE13);
        this->_radiobuttons[i]->setChecked(_radioBoxState[i]);
        connect(_radiobuttons[i], &QRadioButton::clicked, this,
                [=](void)
                {
                    qDebug() << _radiobuttons[i]->text();
                });
    }


    // create comboboxes
    for (int i{}; i < 4; ++i)
    {
        this->_comboboxes.push_back(new QComboBox(_groupBoxSections[_boxID[2][i]]));
        this->_comboboxes[i]->addItems(_comboTexts[i]);
        this->_comboboxes[i]->setGeometry(_coord[4][i][0], _coord[4][i][1], _coord[4][i][2], _coord[4][i][3]);
        this->_comboboxes[i]->setStyleSheet(CUSTOM_STYLE14);
        this->_comboboxes[i]->setCurrentIndex(_comboBoxState[i]);
        connect(this->_comboboxes[i], &QComboBox::currentTextChanged, this,
                [=](void)
                {
                    qDebug() << _comboboxes[i]->currentText();
                });
    }


    // create checkboxes for sections N2 and N3 (_slots1 and _slots2)
    for (int i{}; i < 16; ++i)
    {
        QString name = "Slot " + QString::number(i) + ((i > 9) ? ":" : ":\u00A0\u00A0"); // the Unicode non-breaking space character (\u00A0)

        _slots1.push_back(new QCheckBox(name, _groupBoxSections[2]));
        _slots2.push_back(new QCheckBox(name, _groupBoxSections[3]));

        _slots1[i]->setLayoutDirection(Qt::RightToLeft);
        _slots2[i]->setLayoutDirection(Qt::RightToLeft);


        _slots1[i]->setStyleSheet(CUSTOM_STYLE13);
        _slots2[i]->setStyleSheet(CUSTOM_STYLE13);

        _slots1[i]->setGeometry(20 + 120 * (i % 4), 2 + 30 * (i / 4), 70, 26);
        _slots2[i]->setGeometry(20 + 120 * (i % 4), 2 + 30 * (i / 4), 70, 26);

        _slots1[i]->setChecked(_slots1State[i]);
        _slots2[i]->setChecked(_slots2State[i]);

        _slots2[i]->setEnabled(!_slots1[i]->isChecked());

        connect(_slots1[i], &QCheckBox::stateChanged, this,
                [=](void)
                {
                    _slots2[i]->setEnabled(!_slots1[i]->isChecked());
                    qDebug() << name + (_slots1[i]->isChecked() ? " [v]" : " [ ]");
                });

        connect(_slots2[i], &QCheckBox::stateChanged, this,
                [=](void)
                {
                    qDebug() << name + (_slots2[i]->isChecked() ? " [v]" : " [ ]");
                });
    }

    // create QGridLayout and put on the window
    this->_mainGridLayout = new QGridLayout;
    this->setLayout(_mainGridLayout);

    // create special backgrounds
    _bg1 = new QLabel;
    _bg2 = new QLabel;
    _bg1->setStyleSheet(CUSTOM_STYLE2);
    _bg2->setStyleSheet(CUSTOM_STYLE5);

    _mainGridLayout->setRowMinimumHeight(0, 40);
    _mainGridLayout->setRowMinimumHeight(1, 30);
    _mainGridLayout->setRowMinimumHeight(2, 30);
    _mainGridLayout->setRowMinimumHeight(3, 35);
    _mainGridLayout->setRowMinimumHeight(4, 550);

    _mainGridLayout->addWidget(_bg1, 0, 0, 1, 20);
    _mainGridLayout->setRowMinimumHeight(0, 30);
    _mainGridLayout->addWidget(_buttonSave, 0, 0, 1, 1, Qt::AlignCenter);
    _mainGridLayout->addWidget(_buttonPrint, 0, 1, 1, 1, Qt::AlignCenter);
    _mainGridLayout->addWidget(_buttonResize, 0, 2, 1, 1, Qt::AlignCenter);
    _buttonSave->raise();
    _buttonPrint->raise();
    _buttonResize->raise();

    _mainGridLayout->addWidget(_title, 1, 0, 1, 20, Qt::AlignLeft);

    _mainGridLayout->addWidget(_bg2, 2, 0, 1, 20);
    _mainGridLayout->addWidget(_buttonGenerate, 2, 0, 1, 3, Qt::AlignCenter);
    _mainGridLayout->addWidget(_buttonDRC, 2, 3, 1, 2, Qt::AlignCenter);
    _mainGridLayout->addWidget(_buttonHelp, 2, 5, 1, 2, Qt::AlignCenter);
    _buttonGenerate->raise();
    _buttonDRC->raise();
    _buttonHelp->raise();

    _mainGridLayout->addWidget(_buttonConfig, 3, 0, 1, 3, Qt::AlignCenter);
    _mainGridLayout->addWidget(_buttonTools, 3, 3, 1, 3, Qt::AlignCenter);

    _mainGridLayout->addWidget(_groupBoxConfig, 4, 0, 1, 20);
    _mainGridLayout->addWidget(_groupBoxTools, 4, 0, 1, 20);
    if (_configIsActive) {
        _groupBoxConfig->show();
        _groupBoxTools->hide();
    }
    else {
        _groupBoxConfig->hide();
        _groupBoxTools->show();
    }
}

WindowNext::~WindowNext()
{
    delete _buttonSave;
    delete _buttonPrint;
    delete _buttonResize;

    delete _title;
    delete _buttonGenerate;
    delete _buttonDRC;
    delete _buttonHelp;
    delete _buttonConfig;
    delete _buttonTools;
    delete _blueLine;
    delete _underConstraction;

    for (auto title : _sectionTitles)
        delete title;

    for (auto _description : _descriptions)
        delete _description;

    for (auto _radiobutton : _radiobuttons)
        delete _radiobutton;

    for (auto _combobox : _comboboxes)
        delete _combobox;

    for (auto _slot : _slots1)
        delete _slot;

    for (auto _slot : _slots2)
        delete _slot;

    for (auto groupBox : _groupBoxSections)
        delete groupBox;

    delete _groupBoxConfig;
    delete _groupBoxTools;
    delete _bg1;
    delete _bg2;
    delete _mainGridLayout;

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
QToolButton*    WindowNext::createButton(const QString& iconPath, \
                                      int aw, int ah, const QString& toolTip, \
                                      const QString& style, void (WindowNext::*action)(void))
{
    QToolButton *button = new QToolButton(this);
    if (iconPath != "")
    {
        button->setIcon(QIcon(iconPath));
        button->setIconSize(QSize(aw, ah));
    }
    button->setCursor(Qt::PointingHandCursor);
    button->setText(toolTip);
    button->setToolTip(toolTip);
    button->setStyleSheet(style);
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
    this->saveStateToJSON();
}

// action for 'Configuration' button
void    WindowNext::buttonConfigAction(void)
{
    if (_configIsActive == false)
    {
        _configIsActive = true;
        _blueLine->setGeometry(20, 149, 130, 2);
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
        _blueLine->setGeometry(150, 153, 130, 2);
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

inline void    WindowNext::initValues(void)
{

    _JSONfilePath = this->getExecutableGrandparentDirPath() + "/JSON/state.json";

    // ################################# COMBOBOX TEXTS ######################################

    // values for combobox "Number of address bits driven by master:"
    _comboTexts.push_back({"12", "16", "20", "24", "28", "32"});

    // values for combobox "Position in slave address of upper 4 bits of master address:"
    _comboTexts.push_back({"[27:24] (Ignored if master address width >= 32 bits)", \
                           "[23:20] (Ignored if master address width >= 28 bits)", \
                           "[19:16] (Ignored if master address width >= 24 bits)", \
                           "[15:12] (Ignored if master address width >= 20 bits)", \
                            "[11:8] (Ignored if master address width >= 16 bits)"});
        
    // values for combobox "Indirect Addressing:"
    _comboTexts.push_back({"Not in use", \
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
    
    // values for combobox "Testbench:"
    _comboTexts.push_back({"User", "Option1", "Option2", "Option3"});
    
    
    // ###################################### TITLES ###########################################

    // titles for sections in "Configuration" menu
    _titles.push_back({"DATA WITH CONFIGURATION", \
                       "ADDRESS CONFIGURATION", \
                       "ALLOCATE MEMORY SPACE TO COMBINED REGION SLAVE", \
                       "ENABLED APB SLAVE SLOTS"});
    
    // titles for descriptions in sections of "Configuration" manue
    _titles.push_back({"APB Master Data Bug Width", \
                       "Number of address bits driven by master:", \
                       "Position in slave address of upper 4 bits of master address:", \
                       "Indirect Addressing:", "Testbench:", "License:"});
    
    // titles for radiobuttons
    _titles.push_back({"32-bit", "16-bit", "8-bit", "Obfuscated", "RTL"});
    
    
    // ###################################### COORDINATES ###################################### 
    
    // coordinates for section titles in "Configuration" manue
    _coord.push_back({{20,   1, 400, 25}, \
                      {20,  58, 400, 25}, \
                      {20, 175, 400, 25}, \
                      {20, 322, 400, 25}});
    
    // coordinates for groupBoxes in "Configuration" manue
    _coord.push_back({{1,  27, 776,  30}, \
                      {1,  84, 776,  90}, \
                      {1, 201, 776, 120}, \
                      {1, 348, 776, 191}});
    
    // coordinates for description texts in 'Configuration' menu
    _coord.push_back({{30,   2, 180, 26}, \
                      {30,   2, 365, 26}, \
                      {30,  32, 365, 26}, \
                      {30,  62, 365, 26}, \
                      {30, 127,  70, 26}, \
                      {30, 155,  70, 26}});
    
    // coordinates for radiobuttons
    _coord.push_back({{220,   2,  60, 26}, \
                      {300,   2,  60, 26}, \
                      {380,   2,  60, 26}, \
                      {110, 155, 100, 26}, \
                      {230, 155, 100, 26}});
    
    // coordinates for comboboxes
    _coord.push_back({{410,   2, 350, 26}, \
                      {410,  32, 350, 26}, \
                      {410,  62, 350, 26}, \
                      {110, 127, 140, 26}});
    
    
    // ###################################### BOX IDs ######################################
    
    // groupbox IDs for _descriptions
    _boxID.push_back({0, 1, 1, 1, 3, 3});
    
    // groupbox IDs for _radiobuttons
    _boxID.push_back({0, 0, 0, 3, 3});
    
    // groupbox IDs for _comboboxes
    _boxID.push_back({1, 1, 1, 3});


    // ############################### Open State Defaults ###############################
    _configIsActive = true;

    for (int i{}; i < 5; ++i)
        _radioBoxState.push_back(false);
    _radioBoxState[0] = true;   // 32-bit
    _radioBoxState[4] = true;   // RTL

    _comboBoxState.push_back(4);    // 28
    _comboBoxState.push_back(0);    // [27:24] (Ignored if master address width >= 32 bits)
    _comboBoxState.push_back(0);    // Not in use
    _comboBoxState.push_back(0);    // User

    for (int i{}; i < 16; ++i)
        _slots1State.push_back(false);
    _slots1State[9] = true;
    _slots1State[10] = true;
    _slots1State[13] = true;

    for (int i{}; i < 16; ++i)
        _slots2State.push_back(false);
    _slots2State[3] = true;
    _slots2State[7] = true;
    _slots2State[9] = true;
    _slots2State[11] = true;
    _slots2State[13] = true;
    _slots2State[15] = true;

}

void    WindowNext::saveStateToJSON(void)
{
    // get the path of the directory containing the JSON file
    QString JSONdirectoryPath = _JSONfilePath.left(_JSONfilePath.lastIndexOf('/'));
    QDir    JSONdirectory(JSONdirectoryPath);

    // if the directory does not exist, we create it
    if (!JSONdirectory.exists())
        if (JSONdirectory.mkpath(JSONdirectoryPath) == false)
            qDebug() << "Failed to create directory.";


    // create a JSON object
    QJsonObject jsonObj;

    // set values in JSON object
    jsonObj["_configIsActive"] = _configIsActive;

    for (int i{}; i < 5; ++i)
        jsonObj["_radioBoxState" + QString::number(i)] = this->_radiobuttons[i]->isChecked();

    for (int i{}; i < 4; ++i)
        jsonObj["_comboBoxState" + QString::number(i)] = this->_comboboxes[i]->currentIndex();

    for (int i{}; i < 16; ++i)
    {
        jsonObj["_slots1State" + QString::number(i)] = _slots1[i]->isChecked();
        jsonObj["_slots2State" + QString::number(i)] = _slots2[i]->isChecked();
    }    


    // create a JSON document from the object
    QJsonDocument jsonDoc(jsonObj);

    // open a file for writing
    QFile file(_JSONfilePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // write the JSON document to the file
        file.write(jsonDoc.toJson());
        file.close();
        qDebug() << "JSON file saved successfully!";
    }
    else
        qDebug() << "Failed to open JSON file for writing.";
}

void    WindowNext::readStateFromJSON(void)
{
    // check if the JSON file exists
    QFile jsonFile(_JSONfilePath);
    if(!jsonFile.exists())
    {
        qDebug() << "JSON file does not exist. The window will open with default values.";
        return;
    }

    // open the JSON file for reading
    if (jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // read the JSON document from the file
        QByteArray jsonData = jsonFile.readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);

        // check if the JSON document is valid
        if (!jsonDoc.isNull())
        {
            // convert the JSON document to a JSON object
            QJsonObject jsonObj = jsonDoc.object();

            // extract the values from the JSON object
            _configIsActive = jsonObj["_configIsActive"].toBool();

            for (int i{}; i < 5; ++i)
                _radioBoxState[i] = jsonObj["_radioBoxState" + QString::number(i)].toBool();

            for (int i{}; i < 4; ++i)
                _comboBoxState[i] = jsonObj["_comboBoxState" + QString::number(i)].toInt();

            for (int i{}; i < 16; ++i)
            {
                _slots1State[i] = jsonObj["_slots1State" + QString::number(i)].toBool();
                _slots2State[i] = jsonObj["_slots2State" + QString::number(i)].toBool();
            }

            qDebug() << "Open state values successfully read from JSON file.";
        }
        else
            qDebug() << "Failed to parse JSON document. The window will open with default values.";

        // close the file
        jsonFile.close();
    }
    else
        qDebug() << "Failed to open JSON file for reading. The window will open with default values.";
}

QString WindowNext::getExecutableGrandparentDirPath(void)
{
    QString executableDirPath = QCoreApplication::applicationDirPath();
    QDir parentDir(executableDirPath);

    int up{1};
    #ifdef Q_OS_MAC
    up += 3;
    #endif

    while (up--)
        parentDir.cdUp();
    QString grandparentDirPath = parentDir.absolutePath();
    return grandparentDirPath;
}
