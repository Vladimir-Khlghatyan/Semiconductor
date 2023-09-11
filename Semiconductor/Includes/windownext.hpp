#ifndef WINDOWNEXT_HPP
#define WINDOWNEXT_HPP

#include <QDialog>
#include <QWidget>
#include "mainwindow.hpp"

class MainWindow;

class WindowNext : public QDialog
{
    public:
        WindowNext(MainWindow *parent);
        ~WindowNext();
};

#endif // WINDOWNEXT_HPP

