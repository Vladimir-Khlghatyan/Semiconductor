#ifndef WINDOWNEXT_HPP
# define WINDOWNEXT_HPP

# include <QDialog>
# include <QWidget>
# include <QScreen>
# include <QGridLayout>
# include <QGroupBox>
# include <QLabel>
# include <QApplication>
# include <QRadioButton>
# include <QComboBox>
# include <QCloseEvent>
# include <QCheckBox>
# include <QVector>
# include "mainwindow.hpp"

class MainWindow;

class WindowNext : public QDialog
{
    public:
        WindowNext(MainWindow *parent);
        ~WindowNext();

    private:
        inline void     initValues(void);
        void            putWindowOnScreen(int windowWidth, int windowHeight);
        void            saveStateToJSON(void);
        void            readStateFromJSON(void);
        QString         getExecutableGrandparentDirPath(void);

        QToolButton*    createButton(const QString& iconPath, \
                                    int aw, int ah, const QString& toolTip, \
                                  const QString& style, void (WindowNext::*action)(void));        

    private slots:
        void    buttonSaveAction(void);
        void    buttonConfigAction(void);
        void    buttonTollsAction(void);
        void    actionlessButton(void);

    private:
        // variables to store open state defaults
        QString         _JSONfilePath;
        bool            _configIsActive;
        QVector<bool>   _radioBoxState;
        QVector<int>    _comboBoxState;
        QVector<bool>   _slots1State;
        QVector<bool>   _slots2State;

        // initial groupbox with buttons 'Save', 'Print' and 'Resize'
        QGridLayout *_mainGridLayout;
        QLabel      *_bg1;
        QLabel      *_bg2;

        QToolButton *_buttonSave;
        QToolButton *_buttonPrint;
        QToolButton *_buttonResize;

        // window title
        QLabel      *_title;

        // groupbox with buttons 'Generate', 'DRC' and 'Help'
        QToolButton *_buttonGenerate;
        QToolButton *_buttonDRC;
        QToolButton *_buttonHelp;

        // Configuration / Tools menu buttons and groupboxes
        QToolButton *_buttonConfig;
        QToolButton *_buttonTools;
        QLabel      *_blueLine;
        QGroupBox   *_groupBoxConfig;
        QGroupBox   *_groupBoxTools;
        QLabel      *_underConstraction;

        // Titles and subgroupboxes for 4 sections in 'Configuration' menu:
        //  0) DATA WITH CONFIGURATION
        //  1) ADDRESS CONFIGURATION
        //  2) ALLOCATE MEMORY SPACE TO COMBINED REGION SLAVE
        //  3) ENABLED APB SLAVE SLOTS
        QVector<QLabel*>    _sectionTitles;
        QVector<QGroupBox*> _groupBoxSections;

        // description texts in groupboxes
        QVector<QLabel*>        _descriptions;

        // radiobuttons, comboboxes and checkboxes
        QVector<QRadioButton*>  _radiobuttons;
        QVector<QComboBox*>     _comboboxes;
        QVector<QCheckBox*>     _slots1;
        QVector<QCheckBox*>     _slots2;

        // additional variables to store information needed to initialize QT objects
        QVector<QStringList>            _titles;
        QVector<QStringList>            _comboTexts;
        QVector<QVector<QVector<int>>>  _coord;
        QVector<QVector<int>>           _boxID;
};

#endif // WINDOWNEXT_HPP
