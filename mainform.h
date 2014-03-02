#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include <string>
using namespace std;

namespace Ui {
class MainForm;
}

class MainForm : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();
    
private slots:

    void on_iconBtn_clicked();

    void on_execBtn_clicked();

    void on_okBtn_clicked();

    void on_quitBtn_clicked();

    void on_previewBtn_clicked();

private:
    Ui::MainForm *ui;
    string generateFile();
};

#endif // MAINFORM_H
