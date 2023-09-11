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

        void    putWindowOnScreen(int windowWidth, int windowHeight);

    private:
        QGroupBox   *_groupBox1;
        QGroupBox   *_groupBox2;
        QGroupBox   *_groupBox3;

        QLabel      *_label1;
};

#endif // WINDOWNEXT_HPP

