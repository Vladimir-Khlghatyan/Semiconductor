#ifndef WINDOWNEXT_HPP
# define WINDOWNEXT_HPP

# include <QDialog>
# include <QWidget>
# include <QScreen>
# include <QGroupBox>
# include <QLabel>
# include <QApplication>
# include "mainwindow.hpp"

# define MY_BUTTON_STYLE2 "QToolButton { border-radius: 40px; background: #1c4684;} \
                            QToolButton:hover { border-radius: 40px; background: solid green;}"

class MainWindow;

class WindowNext : public QDialog
{
    public:
        WindowNext(MainWindow *parent);
        ~WindowNext();

        void            putWindowOnScreen(int windowWidth, int windowHeight);
        QToolButton*    createButton(QWidget *parent, const QString& iconPath, \
                                    int ax, int ay, int aw, int ah, \
                                    const QString& toolTip, void (WindowNext::*action)(void));

    private slots:
        void            buttonSaveAction(void);

    private:
        QGroupBox   *_groupBox1;
        QGroupBox   *_groupBox2;
        QGroupBox   *_groupBox3;

        QLabel      *_label1;

        QToolButton *_buttonSave;
};

#endif // WINDOWNEXT_HPP

