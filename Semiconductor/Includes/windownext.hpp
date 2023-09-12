#ifndef WINDOWNEXT_HPP
# define WINDOWNEXT_HPP

# include <QDialog>
# include <QWidget>
# include <QScreen>
# include <QGroupBox>
# include <QLabel>
# include <QApplication>
# include <QVector>>
# include "mainwindow.hpp"

class MainWindow;

class WindowNext : public QDialog
{
    public:
        WindowNext(MainWindow *parent);
        ~WindowNext();

        void            putWindowOnScreen(int windowWidth, int windowHeight);
        QToolButton*    createButton(QWidget *parent, const QString& iconPath, \
                                    int ax, int ay, int aw, int ah, const QString& toolTip, \
                                  const QString& style, void (WindowNext::*action)(void));

    private slots:
        void    buttonSaveAction(void);
        void    buttonConfigAction(void);
        void    buttonTollsAction(void);
        void    actionlessButton(void);

    private:
        QGroupBox   *_groupBoxSaveButton;
        QGroupBox   *_groupBoxGenerateButton;
        QGroupBox   *_groupBoxConfig;
        QGroupBox   *_groupBoxTools;

        QLabel      *_title;
        QLabel      *_blueLine;
        QLabel      *_underConstraction;


        // Titles and groupboxes for four sections in 'Configuration' menu:
        // 1) DATA WITH CONFIGURATION
        // 2) ADDRESS CONFIGURATION
        // 3) ALLOCATE MEMORY SPACE TO COMBINED REGION SLAVE
        // 4) ENABLED APB SLAVE SLOTS
        QVector<QLabel*>    _sectionTitles;
        QVector<QGroupBox*> _groupBoxSections;

        QToolButton *_buttonSave;
        QToolButton *_buttonPrint;
        QToolButton *_buttonResize;

        QToolButton *_buttonGenerate;
        QToolButton *_buttonDRC;
        QToolButton *_buttonHelp;        

        QToolButton *_buttonConfig;
        QToolButton *_buttonTools;

        bool        _configIsActive;
};

#endif // WINDOWNEXT_HPP

