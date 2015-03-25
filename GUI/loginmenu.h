#include <QtGui>
#include "netflix.h"
#include "Set.h"
#include <QCloseEvent>
#ifndef LOGINMENU_H
 #define LOGINMENU_H

 #include <QDialog>

 class QAction;
 class QGroupBox;
 class QLabel;
 class QLineEdit;
 class QPushButton;
 class Mainmenu;
 class Warningmenu;

 class Loginmenu : public QDialog
 {
     Q_OBJECT

 public:
     Loginmenu(Netflix *a);
     void addMenu(Mainmenu *b);
     void setName();
     void setCurrentMovie();
     void setCurrentQueue();
     void setLogin();

protected:
     void closeEvent(QCloseEvent *event);


private slots:
     void on_returnMovieButton_clicked();
     void on_rentButton_clicked();
     void on_deleteButton_clicked();
     void on_moveButton_clicked();
     void on_titleButton_clicked();
     void on_keywordButton_clicked();
     void on_nextButton_clicked();
     void on_addButton_clicked();
     void on_logoutButton_clicked();
     void on_onebutton_clicked();
     void on_twobutton_clicked();
     void on_threebutton_clicked();
     void on_fourbutton_clicked();
     void on_fivebutton_clicked();
     void on_skipbutton_clicked();
     void on_ratingsbutton_clicked();
     void on_nextRatingsButton_clicked();
     void on_changeRatingsButton_clicked();
     void on_changeButton_clicked();
     void on_actorButton_clicked();



 private:
     void createCurrentMovieBox();
     void createQueueBox();
     void createSearchBox();
     void createInfoBox();

     QHBoxLayout *fiveButtons;
     QGroupBox *fiveBox;
     QPushButton *onebutton;
     QPushButton *twobutton;
     QPushButton *threebutton;
     QPushButton *fourbutton;
     QPushButton *fivebutton;
     QPushButton *skipbutton;
     QPushButton *ratingsbutton;

     bool b_title;
     string a_title;
     Netflix *netflix;
     Mainmenu *mainmenu;
     Warningmenu *warningmenu;

     QVBoxLayout *appLayout;

     QLabel *user;

     QGroupBox *currentMovieBox;
     QVBoxLayout *movieLayout;
     QLabel *currentMovieName;
     QPushButton *returnMovieButton;

     QGroupBox *queueBox;
     QGroupBox *queueButtonBox;
     QVBoxLayout *queueLayout;
     QHBoxLayout *queueButtonLayout;
     QLabel *front;
     QLabel *warn;
     QPushButton *rentButton;
     QPushButton *deleteButton;
     QPushButton *moveButton;

     QGroupBox *searchBox;
     QGroupBox *searchTextBox;
     QGroupBox *searchButtonBox;
     QVBoxLayout *searchLayout;
     QHBoxLayout *searchTextLayout;
     QHBoxLayout *searchButtonLayout;
     QLabel *search;
     QLineEdit *searchEdit;
     QPushButton *titleButton;
     QPushButton *keywordButton;
     QPushButton *actorButton;
     
     QGroupBox *infoBox;
     QLineEdit *ratingsEdit;
     QGroupBox *infoButtonBox;
     QGroupBox *ratingsButtonBox;
     QVBoxLayout *infoLayout;
     QHBoxLayout *infoButtonLayout;
     QHBoxLayout *ratingsButtonLayout;
     QLabel *ratingsText;
     QLabel *infoName;
     QLabel *infoKeywords;
     QPushButton *nextButton;
     QPushButton *addButton;
     QPushButton *nextRatingsButton;
     QPushButton *changeRatingsButton;
     QPushButton *changeButton;

     QPushButton *logoutButton;
    
 };

 #endif