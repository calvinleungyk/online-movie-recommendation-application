#include <QtGui>
#ifndef WARNINGMENU_H
#define WARNINGMENU_H

#include <string>
#include <QDialog>

class Loginmenu;
class Mainmenu;
class Netflix;

class Warningmenu : public QDialog
 {
     Q_OBJECT

 public:
  Warningmenu(Netflix *a, Mainmenu *b, Loginmenu *c);
  void setWarningMessage(std::string msg);
  void setupMain();
  void setupLogin();

private slots:
  void on_mainokButton_clicked();
  void on_loginokButton_clicked();

 private:
    Netflix *netflix;
    Mainmenu *mainmenu;
    Loginmenu *loginmenu;

    QGroupBox *warningBox;
    QVBoxLayout *appLayout;
    QHBoxLayout *appHLayout;
		QLabel *warningMessage;
    QPushButton *mainokButton;
    QPushButton *loginokButton;
 };

 #endif