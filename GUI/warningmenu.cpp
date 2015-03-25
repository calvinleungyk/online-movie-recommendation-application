#include "warningmenu.h"
#include "mainmenu.h"
#include "loginmenu.h"
#include <string>

Warningmenu::Warningmenu(Netflix *a, Mainmenu *b, Loginmenu *c)
{
	netflix = a;
	mainmenu = b;
	loginmenu = c;

	appLayout = new QVBoxLayout;
	
	warningMessage = new QLabel(tr("Warning"));
	mainokButton = new QPushButton(tr("OK"));
	loginokButton = new QPushButton(tr("OK"));

	warningBox = new QGroupBox();
  appHLayout = new QHBoxLayout;
  
  appHLayout->addWidget(mainokButton);
  appHLayout->addWidget(loginokButton);

  warningBox->setLayout(appHLayout);

	appLayout->addWidget(warningMessage);
	appLayout->addWidget(warningBox);

	QObject::connect(mainokButton, SIGNAL(clicked()), this, SLOT(on_mainokButton_clicked()));
	QObject::connect(loginokButton, SIGNAL(clicked()), this, SLOT(on_loginokButton_clicked()));

	setLayout(appLayout);
  setWindowTitle(tr("Warning"));
}

void Warningmenu::setWarningMessage(string msg)
{
	warningMessage->setText(QString::fromStdString(msg));
}

void Warningmenu::on_mainokButton_clicked()
{
	this->hide();
	mainmenu->show();
}

void Warningmenu::on_loginokButton_clicked()
{
	this->hide();
	loginmenu->show();
}

void Warningmenu::setupMain()
{
	mainokButton->setVisible(true);
	loginokButton->setVisible(false);
}

void Warningmenu::setupLogin()
{
	mainokButton->setVisible(false);
	loginokButton->setVisible(true);
}