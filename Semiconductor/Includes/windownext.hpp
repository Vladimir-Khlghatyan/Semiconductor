#ifndef WINDOWNEXT_HPP
# define WINDOWNEXT_HPP

# include <QDialog>
# include <QWidget>
# include <QScreen>
# include <QGroupBox>
# include <QLabel>
# include <QApplication>
# include <QVector>
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
        QToolButton *_buttonSave;
        QToolButton *_buttonPrint;
        QToolButton *_buttonResize;

        QLabel      *_title;

        QGroupBox   *_groupBoxGenerateButton;
        QToolButton *_buttonGenerate;
        QToolButton *_buttonDRC;
        QToolButton *_buttonHelp;

        QToolButton *_buttonConfig;
        QToolButton *_buttonTools;
        QLabel      *_blueLine;

        QGroupBox   *_groupBoxConfig;
        QGroupBox   *_groupBoxTools;
        QLabel      *_underConstraction;

        // Titles and groupboxes for four sections in 'Configuration' menu:
        //  0) DATA WITH CONFIGURATION
        //  1) ADDRESS CONFIGURATION
        //  2) ALLOCATE MEMORY SPACE TO COMBINED REGION SLAVE
        //  3) ENABLED APB SLAVE SLOTS
        QVector<QLabel*>    _sectionTitles;
        QVector<QGroupBox*> _groupBoxSections;

        QLabel      *_description0;
        QLabel      *_description1;
        QLabel      *_description2;
        QLabel      *_description3;
        QLabel      *_description4;
        QLabel      *_description5;

        bool        _configIsActive;
};

#endif // WINDOWNEXT_HPP

