#ifndef WINDOWNEXT_HPP
# define WINDOWNEXT_HPP

# include <QDialog>
# include <QWidget>
# include <QScreen>
# include <QGroupBox>
# include <QLabel>
# include <QApplication>
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

        QLabel      *_sectionTitle1; // first section in 'Configuration' menu (DATA WITH CONFIGURATION)
        QLabel      *_sectionTitle2; // second section in 'Configuration' menu (ADDRESS CONFIGURATION)
        QLabel      *_sectionTitle3; // third section in 'Configuration' menu (ALLOCATE MEMORY SPACE TO COMBINED REGION SLAVE)
        QLabel      *_sectionTitle4; // fourth section in 'Configuration' menu (ENABLED APB SLAVE SLOTS)

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

