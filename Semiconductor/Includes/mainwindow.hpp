#ifndef MAINWINDOW_HPP
# define MAINWINDOW_HPP

# include <QMainWindow>
# include <QScreen>
# include <QToolButton>
# include <QMessageBox>

# define MY_BUTTON_STYLE "QToolButton { border-radius: 20px; border: 3px solid #a0f436; background: #001127;} \
                        QToolButton:hover { border-radius: 20px; border: 3px solid blue; background: #00377d;}"

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
        void    buttonAboutAction(void);
        void    buttonNextAction(void);

    private:
        Ui::MainWindow *ui;

        QToolButton *_buttonAbout;
        QToolButton *_buttonNext;

        WindowNext  *_windowNext;
};
#endif // MAINWINDOW_HPP
