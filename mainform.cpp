#include "mainform.h"
#include "ui_mainform.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
using namespace std;

/** Helper method */

QString toQString(string str)
{
    return QString::fromStdString(str);
}

string toString(QString str)
{
    return str.toUtf8().constData();
}

////////////////////////////////////////

MainForm::MainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    //connect(ui->quitBtn, SIGNAL(clicked()),QCoreApplication::instance(), SLOT(close()));
    // QObject::connect(ui->qui, &QPushButton::clicked, this, &QWidget::close());

}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::on_iconBtn_clicked()
{
    // get default location if does not exist link to folder yet
    QString location = "";
    if (ui->execTxt->text().size() > 0) location = ui->execTxt->text();
    else location = "/home";

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Executable File"), location, tr("All Files (*.*)"));
    ui->iconTxt->setText(fileName);
}

void MainForm::on_execBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Executable File"), "/home", tr("All Files (*.*)"));
   ui->execTxt->setText(fileName);
}

void MainForm::on_okBtn_clicked()
{
    // get filename should be saved
    string filename = toString(ui->fileNameTxt->text());
    filename += ".desktop";
    filename = "/usr/share/applications/" + filename;

    ofstream file(filename.c_str());
    //file.open(filename);
    string content = generateFile();
    file << content;
    file.close();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Succeed");
    msgBox.setText("successfully created file");
    msgBox.exec();
}

string MainForm::generateFile()
{
    // prepare data
    string execLink = ui->execTxt->text().toUtf8().constData();
    bool isRoot = ui->isRootChkBox->isChecked();
    bool isTerminal = ui->isTerminalChkBox->isChecked();

    ostringstream ss;
    ss << "[Desktop Entry]" << endl;
    ss << "Type=Application" << endl;
    ss << "Encoding=UTF-8" << endl;
    ss << "Version=1.0" << endl;
    ss << "NoDisplay=false" << endl;
    ss << "Name=" << toString(ui->appNameTxt->text()) << endl;
    ss << "Comment=" << toString(ui->appNoteTxt->text()) << endl;
    ss << "Icon=" << toString(ui->iconTxt->text()) << endl;
    ss << "Categories=" << toString(ui->categoriesTxt->text()) << endl;

    // terminal parameter : should show terminal or not
    if (isTerminal) ss << "Terminal=true" << endl;
    else ss << "Terminal=false" << endl;

    // exec parameter : depend on is root or not
    if (isRoot) ss << "Exec=gksudo -k -u root " << execLink << endl;
    else ss <<"Exec=" << execLink << endl;

    // set other parameters

    return ss.str();
}

void MainForm::on_quitBtn_clicked()
{

}

void MainForm::on_previewBtn_clicked()
{
    string generate = generateFile();
    QMessageBox msgBox;
    msgBox.setWindowTitle("Generated Content");
    msgBox.setText(toQString(generate));
    msgBox.exec();
}

