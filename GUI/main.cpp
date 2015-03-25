#include <QApplication>

#include "mainmenu.h"
#include "loginmenu.h"
#include "warningmenu.h"
#include "netflix.h"

void readFile();

int main(int argc, char *argv[])
{
	Netflix *netflix = new Netflix;
	QApplication app(argc, argv);

	Loginmenu *loginmenu = new Loginmenu (netflix);
	Mainmenu *mainmenu = new Mainmenu(netflix, loginmenu);
	loginmenu->addMenu(mainmenu);
	
	Warningmenu *warningmenu = new Warningmenu(netflix, mainmenu, loginmenu);

	warningmenu->hide();
	loginmenu->hide();
	mainmenu->show();
	
	return app.exec();
}