#ifndef WINDOWNEXT_HPP
# define WINDOWNEXT_HPP

# include <QDialog>
# include <QWidget>
# include <QScreen>
# include <QApplication>
# include "mainwindow.hpp"

class MainWindow;

class WindowNext : public QDialog
{
    public:
        WindowNext(MainWindow *parent);
        ~WindowNext();

        void    putWindowOnScreen(int windowWidth, int windowHeight);
};

#endif // WINDOWNEXT_HPP

