#include "mainmenu.h"
#include "loginmenu.h"
#include "warningmenu.h"
#include <iostream>

using namespace std;

 Mainmenu::Mainmenu(Netflix *a, Loginmenu *b)
 {  
    netflix = a;
    loginmenu = b;

    wrongLogin = new QLabel(tr("Please enter a valid ID."));
    wrongLogin->setVisible(false);

    createHorizontalGroupBox();
    welcome = new QLabel(tr("Welcome to CSCI 104-Flix"));
    
    loginGroupBox = new QGroupBox();
    loginLayout = new QHBoxLayout;
    login = new QLabel(tr("Login:"));
    login_name = new QLineEdit;

    nameGroupBox = new QGroupBox();
    nameLayout = new QHBoxLayout;
    name = new QLabel(tr("Name:"));
    name_name = new QLineEdit;

    passwordGroupBox = new QGroupBox();
    passwordLayout = new QHBoxLayout;
    password = new QLabel(tr("Password:"));
    password_name = new QLineEdit;

    addressGroupBox = new QGroupBox();
    addressLayout = new QHBoxLayout;
    address = new QLabel(tr("Address:"));
    address_name = new QLineEdit;

    creditGroupBox = new QGroupBox();
    creditLayout = new QHBoxLayout;
    credit = new QLabel(tr("Credit Card:"));
    credit_name = new QLineEdit;

    loginLayout->addWidget(login);
    loginLayout->addWidget(login_name);
    loginGroupBox->setLayout(loginLayout);

    nameLayout->addWidget(name);
    nameLayout->addWidget(name_name);
    nameGroupBox->setLayout(nameLayout);

    passwordLayout->addWidget(password);
    passwordLayout->addWidget(password_name);
    passwordGroupBox->setLayout(passwordLayout);

    addressLayout->addWidget(address);
    addressLayout->addWidget(address_name);
    addressGroupBox->setLayout(addressLayout);

    creditLayout->addWidget(credit);
    creditLayout->addWidget(credit_name);
    creditGroupBox->setLayout(creditLayout);
    QObject::connect(credit_name, SIGNAL(returnPressed()),confirmButton,SIGNAL(clicked()));

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(welcome);
    mainLayout->addWidget(loginGroupBox);
    mainLayout->addWidget(nameGroupBox);
    mainLayout->addWidget(passwordGroupBox);
    mainLayout->addWidget(addressGroupBox);
    mainLayout->addWidget(creditGroupBox);
    mainLayout->addWidget(wrongLogin);
    mainLayout->addWidget(horizontalGroupBox);

    nameGroupBox->setVisible(false);
    passwordGroupBox->setVisible(true);
    addressGroupBox->setVisible(false);
    creditGroupBox->setVisible(false);

    setLayout(mainLayout);
    setWindowTitle(tr("104-Flix"));
 }

 void Mainmenu::createHorizontalGroupBox()
 {  

    horizontalGroupBox = new QGroupBox();
    layout = new QHBoxLayout;

    loginButton = new QPushButton(tr("Login"));
    newUserButton = new QPushButton(tr("New User"));
    quitButton = new QPushButton(tr("Quit"));
    confirmButton = new QPushButton(tr("Confirm"));
    cancelButton = new QPushButton(tr("Cancel"));

    QObject::connect(quitButton, SIGNAL(clicked()), this, SLOT(on_quitButton_clicked()));
    QObject::connect(newUserButton, SIGNAL(clicked()), this, SLOT(on_newUserButton_clicked()));
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_cancelButton_clicked()));
    QObject::connect(loginButton, SIGNAL(clicked()), this, SLOT(on_loginButton_clicked()));
    QObject::connect(confirmButton, SIGNAL(clicked()), this, SLOT(on_confirmButton_clicked()));

    layout->addWidget(loginButton);
    layout->addWidget(newUserButton);
    layout->addWidget(quitButton);
    layout->addWidget(confirmButton);
    layout->addWidget(cancelButton);

    confirmButton->setVisible(false);
    cancelButton->setVisible(false);
    horizontalGroupBox->setLayout(layout);
 }

void Mainmenu::closeEvent(QCloseEvent *event)
 {
  netflix->saveFile();
 }

 void Mainmenu::on_newUserButton_clicked()
 {
    nameGroupBox->setVisible(true);
    addressGroupBox->setVisible(true);
    creditGroupBox->setVisible(true);
    loginButton->setVisible(false);
    newUserButton->setVisible(false);
    quitButton->setVisible(false);
    confirmButton->setVisible(true);
    cancelButton->setVisible(true);
    welcome->setText(tr("Please sign up for CSCI 104 Flix"));
    wrongLogin->setVisible(false);
    login_name->clear();
    name_name->clear();
    password_name->clear();
    address_name->clear();
    credit_name->clear();
    QObject::connect(credit_name, SIGNAL(returnPressed()),confirmButton,SIGNAL(clicked()));
 }

 void Mainmenu::on_cancelButton_clicked()
 {
    nameGroupBox->setVisible(false);
    loginButton->setVisible(true);
    newUserButton->setVisible(true);
    quitButton->setVisible(true);
    confirmButton->setVisible(false);
    cancelButton->setVisible(false);
    welcome->setText(tr("Welcome to CSCI 104 Flix"));
    login_name->clear();
    name_name->clear();
    QObject::connect(login_name, SIGNAL(returnPressed()),loginButton,SIGNAL(clicked()));
 }

 void Mainmenu::on_quitButton_clicked()
 {
  netflix->saveFile();
  this->close();
 }

 void Mainmenu::on_confirmButton_clicked()
 {
  netflix->saveFile();
  wrongLogin->setVisible(false);
  string loginInput = (login_name->text()).toStdString();
  string nameInput = (name_name->text()).toStdString();
  string passwordInput = (password_name->text()).toStdString();
  string addressInput = (address_name->text()).toStdString();
  string creditInput = (credit_name->text()).toStdString();

  if ( (loginInput == "") || (nameInput == "") || (passwordInput == "") || (addressInput == "") || (creditInput == ""))
  {
    wrongLogin->setText(tr("Please enter valid information."));
    wrongLogin->setVisible(true);
  }
  else if (netflix->checkIDValid(loginInput))
  {
    netflix->createNewUser(loginInput, nameInput, passwordInput, addressInput, creditInput);
    wrongLogin->setVisible(false);
    wrongLogin->setText(tr("Please enter a valid ID."));
    nameGroupBox->setVisible(false);
    loginButton->setVisible(true);
    newUserButton->setVisible(true);
    quitButton->setVisible(true);
    confirmButton->setVisible(false);
    cancelButton->setVisible(false);
    welcome->setText(tr("Welcome to CSCI 104 Flix"));
    login_name->clear();
    name_name->clear();
  }
  else
  {
    wrongLogin->setText(tr("ID not valid. Try again."));
    wrongLogin->setVisible(true);
  }
 }

 void Mainmenu::on_loginButton_clicked()
 {
  string loginInput = (login_name->text()).toStdString();
  string passwordInput = (password_name->text()).toStdString();
  if (netflix->checkLoginValid(loginInput) && netflix->checkPasswordValid(loginInput, passwordInput))
  {
    netflix->setCurrentUser(loginInput);
    loginmenu->setName();
    wrongLogin->setVisible(false);
    this->hide();
    loginmenu->show();
    login_name->clear();
    name_name->clear();
    password_name->clear();
    loginmenu->setCurrentMovie();
    loginmenu->setCurrentQueue();
    loginmenu->setLogin();
  }
  else
  {
    wrongLogin->setText(tr("Please enter valid ID and Password"));
    wrongLogin->setVisible(true);
  }
 }

 void Mainmenu::clearLogin()
 {
  login_name->clear();
 }
