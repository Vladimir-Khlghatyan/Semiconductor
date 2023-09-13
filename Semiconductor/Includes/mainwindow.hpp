#ifndef MAINWINDOW_HPP
# define MAINWINDOW_HPP

# include <QMainWindow>
# include <QScreen>
# include <QToolButton>
# include <QMessageBox>
# include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class WindowNext;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        void    putWindowOnScreen(int windowWidth, int windowHeight);

        void    createButtonAbout(int ax, int ay);    // with coordinates (ax, ay)
        void    createButtonNext(int ax, int ay);     // with coordinates (ax, ay)

        QToolButton*    createButton(QWidget *parent, const QString& iconPath, \
                                  int ax, int ay, int aw, int ah, \
                                  const QString& toolTip, void (MainWindow::*action)(void));

    private slots:
        void    buttonAboutAction(void);
        void    buttonNextAction(void);

    private:
        Ui::MainWindow *ui;

        QToolButton *_buttonAbout;
        QToolButton *_buttonNext;
        WindowNext  *_windowNext;
};
#endif // MAINWINDOW_HPP
