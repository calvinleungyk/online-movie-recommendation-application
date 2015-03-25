#include <QtGui>
#include "netflix.h"
#ifndef MAINMENU_H
 #define MAINMENU_H

 #include <QDialog>

class QAction;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class Loginmenu;
class Warningmenu;

 class Mainmenu : public QDialog
 {
     Q_OBJECT

 public:
     Mainmenu(Netflix *a, Loginmenu *b);
     void clearLogin();

protected:
     void closeEvent(QCloseEvent *event);

private slots:
     void on_newUserButton_clicked();
     void on_cancelButton_clicked();
     void on_quitButton_clicked();
     void on_confirmButton_clicked();
     void on_loginButton_clicked();


 private:
     void createHorizontalGroupBox();

     Netflix *netflix;
     Loginmenu *loginmenu;
     Warningmenu *warningmenu;

     QLabel *welcome;

     QGroupBox *loginGroupBox;
     QHBoxLayout *loginLayout;
     QLabel *login;
     QLabel *wrongLogin;
     QLineEdit *login_name;
     
     QGroupBox *nameGroupBox;
     QHBoxLayout *nameLayout;
     QLabel *name;
     QLineEdit *name_name;

     QGroupBox *passwordGroupBox;
     QHBoxLayout *passwordLayout;
     QLabel *password;
     QLineEdit *password_name;

     QGroupBox *addressGroupBox;
     QHBoxLayout *addressLayout;
     QLabel *address;
     QLineEdit *address_name;

     QGroupBox *creditGroupBox;
     QHBoxLayout *creditLayout;
     QLabel *credit;
     QLineEdit *credit_name;
     
     QHBoxLayout *layout;
     QVBoxLayout *mainLayout;
     QGroupBox *horizontalGroupBox;
     
     QPushButton *loginButton;
     QPushButton *newUserButton;
     QPushButton *quitButton;
     QPushButton *confirmButton;
     QPushButton *cancelButton;

 };

 #endif