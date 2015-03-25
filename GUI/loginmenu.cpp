#include "loginmenu.h"
#include "mainmenu.h"
#include "warningmenu.h"
#include <iostream>
#include <sstream>
#include <string>
#include "EmptyQueueException.h"
#include "NoSuchElementException.h"

using namespace std;

 Loginmenu::Loginmenu(Netflix *a)
 {  
    netflix = a;

    createCurrentMovieBox();
    createQueueBox();
    createSearchBox();
    createInfoBox();

    appLayout = new QVBoxLayout;

    logoutButton = new QPushButton(tr("Logout"));
    QObject::connect(logoutButton, SIGNAL(clicked()), this, SLOT(on_logoutButton_clicked()));

    user = new QLabel(tr("Welcome to CSCI 104-Flix!"));
    
    appLayout->addWidget(user);
    appLayout->addWidget(currentMovieBox);
    appLayout->addWidget(queueBox);
    appLayout->addWidget(searchBox);
    appLayout->addWidget(infoBox);
    appLayout->addWidget(logoutButton);

    setLayout(appLayout);
    setWindowTitle(tr("104-Flix"));
    
 }

void Loginmenu::closeEvent(QCloseEvent *event)
 {
  netflix->saveFile();
  mainmenu->show();
 }

void Loginmenu::setCurrentMovie()
{
  currentMovieName->setText(QString::fromStdString(netflix->printCurrentMovie()));
}

void Loginmenu::setName()
{
  user->setText(QString::fromStdString( "Welcome to CSCI 104-Flix! "+ netflix->getCurrentUser()->getName() + " (" + netflix->getCurrentUser()->getID() + ")") );
}

void Loginmenu::setCurrentQueue()
{
  if (netflix->getCurrentUser()->movieQueue()->size() != 0)
  {
    front->setText(QString::fromStdString("Front of Queue: " + netflix->getCurrentUser()->movieQueue()->peekFront()->getTitle()));
  }
  else
  {
    front->setText(QString::fromStdString("Front of Queue: No Movie" ));
  }
  
}

 void Loginmenu::createCurrentMovieBox()
 {  
    currentMovieBox = new QGroupBox(tr("Your Current Movie"));
    movieLayout = new QVBoxLayout;
    currentMovieName = new QLabel(tr("Current Movie"));
    returnMovieButton = new QPushButton(tr("Return Movie"));
    fiveButtons = new QHBoxLayout;
    onebutton = new QPushButton(tr("1"));
    twobutton = new QPushButton(tr("2"));
    threebutton = new QPushButton(tr("3"));
    fourbutton = new QPushButton(tr("4"));
    fivebutton = new QPushButton(tr("5"));
    skipbutton = new QPushButton(tr("skip"));

    fiveBox = new QGroupBox();
    fiveButtons->addWidget(onebutton);
    fiveButtons->addWidget(twobutton);
    fiveButtons->addWidget(threebutton);
    fiveButtons->addWidget(fourbutton);
    fiveButtons->addWidget(fivebutton);
    fiveButtons->addWidget(skipbutton);

    fiveBox->setLayout(fiveButtons);

    movieLayout->addWidget(currentMovieName);
    movieLayout->addWidget(returnMovieButton);
    movieLayout->addWidget(fiveBox);

    QObject::connect(onebutton, SIGNAL(clicked()), this, SLOT(on_onebutton_clicked()));
    QObject::connect(twobutton, SIGNAL(clicked()), this, SLOT(on_twobutton_clicked()));
    QObject::connect(threebutton, SIGNAL(clicked()), this, SLOT(on_threebutton_clicked()));
    QObject::connect(fourbutton, SIGNAL(clicked()), this, SLOT(on_fourbutton_clicked()));
    QObject::connect(fivebutton, SIGNAL(clicked()), this, SLOT(on_fivebutton_clicked()));
    QObject::connect(skipbutton, SIGNAL(clicked()), this, SLOT(on_skipbutton_clicked()));

    onebutton->setVisible(false);
    twobutton->setVisible(false);
    threebutton->setVisible(false);
    fourbutton->setVisible(false);
    fivebutton->setVisible(false);
    skipbutton->setVisible(false);

    QObject::connect(returnMovieButton, SIGNAL(clicked()), this, SLOT(on_returnMovieButton_clicked()));

    currentMovieBox->setLayout(movieLayout);
 }

 void Loginmenu::on_returnMovieButton_clicked()
 {
  if (netflix->getCurrentUser()->currentMovie()!=NULL)
  {
    if ( netflix->containsRatings( netflix->getCurrentUser()->currentMovie()->getTitle() ) )
    {
      currentMovieName->setText(tr("Do you want to rerate your movie? You could skip this option if you don't"));
    }
    else
    {
      currentMovieName->setText(tr("Please give this movie a rating"));
    }
    warn->setVisible(false);
    onebutton->setVisible(true);
    twobutton->setVisible(true);
    threebutton->setVisible(true);
    fourbutton->setVisible(true);
    fivebutton->setVisible(true);
    skipbutton->setVisible(true);
  }
  
 }

void Loginmenu::on_skipbutton_clicked()
 {
  returnMovieButton->setVisible(true);
  currentMovieName->setText(tr("No Movie Rented!"));
  onebutton->setVisible(false);
  twobutton->setVisible(false);
  threebutton->setVisible(false);
  fourbutton->setVisible(false);
  fivebutton->setVisible(false);
  skipbutton->setVisible(false);

  netflix->returnCurrentMovie();
 }

 void Loginmenu::on_onebutton_clicked()
 {
  returnMovieButton->setVisible(true);
  currentMovieName->setText(tr("No Movie Rented!"));
  onebutton->setVisible(false);
  twobutton->setVisible(false);
  threebutton->setVisible(false);
  fourbutton->setVisible(false);
  fivebutton->setVisible(false);
  skipbutton->setVisible(false);
  netflix->addRatings(1);
  netflix->returnCurrentMovie();
 }

 void Loginmenu::on_twobutton_clicked()
 {
  returnMovieButton->setVisible(true);
  currentMovieName->setText(tr("No Movie Rented!"));
  onebutton->setVisible(false);
  twobutton->setVisible(false);
  threebutton->setVisible(false);
  fourbutton->setVisible(false);
  fivebutton->setVisible(false);
  netflix->addRatings(2);
  skipbutton->setVisible(false);
  netflix->returnCurrentMovie();
 }

 void Loginmenu::on_threebutton_clicked()
 {
  returnMovieButton->setVisible(true);
  currentMovieName->setText(tr("No Movie Rented!"));
  onebutton->setVisible(false);
  twobutton->setVisible(false);
  threebutton->setVisible(false);
  fourbutton->setVisible(false);
  fivebutton->setVisible(false);
  netflix->addRatings(3);
  skipbutton->setVisible(false);
  netflix->returnCurrentMovie();
 }

 void Loginmenu::on_fourbutton_clicked()
 {
  returnMovieButton->setVisible(true);
  currentMovieName->setText(tr("No Movie Rented!"));
  onebutton->setVisible(false);
  twobutton->setVisible(false);
  threebutton->setVisible(false);
  fourbutton->setVisible(false);
  fivebutton->setVisible(false);
  netflix->addRatings(4);
  skipbutton->setVisible(false);
  netflix->returnCurrentMovie();
 }

 void Loginmenu::on_fivebutton_clicked()
 {
  returnMovieButton->setVisible(true);
  currentMovieName->setText(tr("No Movie Rented!"));
  onebutton->setVisible(false);
  twobutton->setVisible(false);
  threebutton->setVisible(false);
  fourbutton->setVisible(false);
  fivebutton->setVisible(false);
  netflix->addRatings(5);
  skipbutton->setVisible(false);
  netflix->returnCurrentMovie();
 }

void Loginmenu::createQueueBox()
 {  
    queueBox = new QGroupBox(tr("Your Movie Queue"));
    queueLayout = new QVBoxLayout;
    queueButtonLayout = new QHBoxLayout;
    queueButtonBox = new QGroupBox();
    front = new QLabel(tr("Front of Queue:"));
    warn = new QLabel(tr("Queue is empty!"));
    rentButton = new QPushButton(tr("Rent Movie"));
    deleteButton = new QPushButton(tr("Delete from Queue"));
    moveButton = new QPushButton(tr("Move to Back of Queue"));

    QObject::connect(rentButton, SIGNAL(clicked()), this, SLOT(on_rentButton_clicked()));
    QObject::connect(deleteButton, SIGNAL(clicked()), this, SLOT(on_deleteButton_clicked()));
    QObject::connect(moveButton, SIGNAL(clicked()), this, SLOT(on_moveButton_clicked()));


    queueButtonLayout->addWidget(rentButton);
    queueButtonLayout->addWidget(deleteButton);
    queueButtonLayout->addWidget(moveButton);
    queueButtonBox->setLayout(queueButtonLayout);

    queueLayout->addWidget(front);
    queueLayout->addWidget(warn);
    queueLayout->addWidget(queueButtonBox);

    warn->setVisible(false);

    queueBox->setLayout(queueLayout);
 }

void Loginmenu::on_rentButton_clicked()
{
  try
  {
    if (netflix->getCurrentUser()->currentMovie() == NULL)
    {
      stringstream ss;
      std::ostringstream oss;
      string price;
      string total;
      ss << netflix->getCurrentUser()->movieQueue()->peekFront()->getPrice();
      ss >> price;
      netflix->rentMovies();

      int temp = netflix->getCurrentUser()->returnTotalCharge();
      oss << temp;
      string text = price + " dollars charged to credit card " + ((netflix->getCurrentUser()->returnCredit())[0]).first + "\nYour total charges is " + oss.str() + " dollars";
      infoName->setText(QString::fromStdString(text));
      infoKeywords->setVisible(false);
      setCurrentQueue();
      setCurrentMovie();
    }
    else if (netflix->getCurrentUser()->movieQueue()->size()==0)
    {
      warn->setText(QString::fromStdString("Queue is empty!"));
      warn->setVisible(true);
    }
    else
    {
      warn->setText(QString::fromStdString("You currently have a movie rented! Return the movie to rent a new one"));
      warn->setVisible(true);
    }
  }
  catch (EmptyQueueException &e)
  {}
}

void Loginmenu::on_deleteButton_clicked()
{

  warn->setVisible(false);
  if (netflix->getCurrentUser()->movieQueue()->size()==0)
  {
    warn->setText(QString::fromStdString("Queue is empty!"));
    warn->setVisible(true);
  }
  else
  {
   netflix->deleteMovie();
   setCurrentQueue(); 
  }
}

void Loginmenu::on_moveButton_clicked()
{
  warn->setVisible(false);
  if (netflix->getCurrentUser()->movieQueue()->size()==0)
  {
    warn->setText(QString::fromStdString("Queue is empty!"));
    warn->setVisible(true);
  }
  else
  {
    netflix->moveMovie();
    setCurrentQueue(); 
  }
}

void Loginmenu::on_actorButton_clicked()
{
  try
  {
    netflix->actoriter_empty = false;
    netflix->iter_empty = true;
    ratingsText->setVisible(false);
    nextRatingsButton->setVisible(false);
    changeRatingsButton->setVisible(false);
    string actor = (searchEdit->text()).toStdString();
    if (netflix->checkActorValid(actor))
    {
      b_title = false;
      netflix->actorIter( netflix->getActor(actor) );
      infoName->setText(QString::fromStdString( netflix->printMovie( *(netflix->actoriter) )));
      
      infoKeywords->setText(QString::fromStdString( netflix->printKeywords(*(netflix->actoriter)) ));
      infoName->setVisible(true);
      infoKeywords->setVisible(true);
      addButton->setVisible(true);
      nextButton->setVisible(true);
    }
    searchEdit->clear();
  }
  catch (NoSuchElementException &e)
  {
    infoKeywords->setVisible(false);
    infoName->setText(QString::fromStdString("No movie found!"));
    infoName->setVisible(true);
    addButton->setVisible(false);
    nextButton->setVisible(false);

  }
  searchEdit->clear();
}

void Loginmenu::createSearchBox()
 {  
    searchBox = new QGroupBox(tr("Search for a Movie"));
    searchLayout = new QVBoxLayout;
    searchTextLayout = new QHBoxLayout;
    searchButtonLayout = new QHBoxLayout;
    search = new QLabel(tr("Search:"));
    searchEdit = new QLineEdit;
    //QObject::connect(searchEdit, SIGNAL(returnPressed()),titleButton,SIGNAL(clicked()));
    searchTextBox = new QGroupBox();
    searchButtonBox = new QGroupBox();

    titleButton = new QPushButton(tr("Search by Title"));
    keywordButton = new QPushButton(tr("Search by Keywords"));
    actorButton = new QPushButton(tr("Search by Actors"));

    searchTextLayout->addWidget(search);
    searchTextLayout->addWidget(searchEdit);
    searchTextBox->setLayout(searchTextLayout);

    QObject::connect(titleButton, SIGNAL(clicked()), this, SLOT(on_titleButton_clicked()));
    QObject::connect(keywordButton, SIGNAL(clicked()), this, SLOT(on_keywordButton_clicked()));
    QObject::connect(actorButton, SIGNAL(clicked()), this, SLOT(on_actorButton_clicked()));

    searchButtonLayout->addWidget(titleButton);
    searchButtonLayout->addWidget(keywordButton);
    searchButtonLayout->addWidget(actorButton);
    searchButtonBox->setLayout(searchButtonLayout);

    searchLayout->addWidget(searchTextBox);
    searchLayout->addWidget(searchButtonBox);

    searchBox->setLayout(searchLayout);
 }

void Loginmenu::on_titleButton_clicked()
{
  try
  {
    nextRatingsButton->setVisible(false);
    changeRatingsButton->setVisible(false);
    ratingsText->setVisible(false);

    string title = (searchEdit->text()).toStdString();
    a_title = (searchEdit->text()).toStdString();
    if (netflix->checkTitleValid(title))
    {
      infoName->setText(QString::fromStdString( netflix->printMovie(title) ));
      infoKeywords->setText(QString::fromStdString( netflix->printKeywords(title) ));
      infoName->setVisible(true);
      infoKeywords->setVisible(true);
      addButton->setVisible(true);
      b_title = true;
    }
    searchEdit->clear();
  }
  catch (NoSuchElementException &e)
  {
    infoKeywords->setVisible(false);
    infoName->setText(QString::fromStdString("No movie found!"));
    infoName->setVisible(true);
    addButton->setVisible(false);
    nextButton->setVisible(false);
  }
  searchEdit->clear();
  nextButton->setVisible(false);
}

void Loginmenu::on_keywordButton_clicked()
{
  try
  {
    netflix->actoriter_empty = true;
    netflix->iter_empty = false;
    ratingsText->setVisible(false);
    nextRatingsButton->setVisible(false);
    changeRatingsButton->setVisible(false);
    string keyword = (searchEdit->text()).toStdString();
    if (netflix->checkKeywordValid(keyword))
    {
      b_title = false;
      netflix->setIter( netflix->getSet(keyword) );
      infoName->setText(QString::fromStdString( netflix->printMovie( *(netflix->iter) )));
      
      infoKeywords->setText(QString::fromStdString( netflix->printKeywords(*(netflix->iter)) ));
      infoName->setVisible(true);
      infoKeywords->setVisible(true);
      addButton->setVisible(true);
      nextButton->setVisible(true);
    }
    searchEdit->clear();
  }
  catch (NoSuchElementException &e)
  {
    infoKeywords->setVisible(false);
    infoName->setText(QString::fromStdString("No movie found!"));
    infoName->setVisible(true);
    addButton->setVisible(false);
    nextButton->setVisible(false);

  }
  searchEdit->clear();
}

 void Loginmenu::on_ratingsbutton_clicked()
 {  
    stringstream ss;
    netflix->mapIter(netflix->getCurrentRatings());
    if ( netflix->mapiter_empty )
    {
      ratingsText->setText(QString::fromStdString("You have no ratings"));
      ratingsText->setVisible(true);
      infoName->setVisible(false);
      infoKeywords->setVisible(false);
      nextButton->setVisible(false);
      addButton->setVisible(false);
    }
    else
    {
      netflix->mapIter(netflix->getCurrentRatings());
      std::string num;
      ss << (*(netflix->mapiter)).second;
      ss >> num;
      std::string text = (*(netflix->mapiter)).first + " " + num;
      ratingsText->setText(QString::fromStdString(text));
      nextRatingsButton->setVisible(true);
      changeRatingsButton->setVisible(true);
      ratingsText->setVisible(true);
      infoName->setVisible(false);
      infoKeywords->setVisible(false);
      nextButton->setVisible(false);
      addButton->setVisible(false);
    }
    
 }

  void Loginmenu::on_nextRatingsButton_clicked()
 {
    stringstream ss;
    ++(netflix->mapiter);
    if ( (netflix->mapiter)==(netflix->getCurrentRatings()->end()) )
    {
      ratingsText->setText(QString::fromStdString("End of Ratings"));
      infoName->setVisible(false);
      infoKeywords->setVisible(false);
      nextButton->setVisible(false);
      addButton->setVisible(false);
      nextRatingsButton->setVisible(false);
      changeRatingsButton->setVisible(false);

    }
    else
    {
      std::string num;
      ss << (*(netflix->mapiter)).second;
      ss >> num;
      std::string text = (*(netflix->mapiter)).first + " " + num;
      ratingsText->setText(QString::fromStdString(text));
      nextRatingsButton->setVisible(true);
      changeRatingsButton->setVisible(true);
      ratingsText->setVisible(true);
      infoName->setVisible(false);
      infoKeywords->setVisible(false);
      nextButton->setVisible(false);
      addButton->setVisible(false);
    }
 }

  void Loginmenu::on_changeRatingsButton_clicked()
 {
  ratingsEdit->setVisible(true);
  changeRatingsButton->setVisible(false);
  changeButton->setVisible(true);
  nextRatingsButton->setVisible(false);
  ratingsbutton->setVisible(false);
 }

 void Loginmenu::on_changeButton_clicked()
 {
  stringstream ss;
  int num;
  string temp = (ratingsEdit->text()).toStdString();
  ss << temp;
  ss >> num;
  cout << num;
  if ( ss.fail()|| num > 5 || num < 1)
  {
    ratingsText->setText(QString::fromStdString("Please enter an integer between 1-5"));
  }
  else
  {
    ratingsEdit->setVisible(false);
    changeRatingsButton->setVisible(false);
    changeButton->setVisible(false);
    netflix->getCurrentRatings()->ratings( (*(netflix->mapiter) ).first, num);
    ratingsText->setText(QString::fromStdString("Ratings Changed"));
    ratingsbutton->setVisible(true);
  }
  ratingsEdit->clear();
 }

void Loginmenu::createInfoBox()
 {  
    ratingsbutton = new QPushButton(tr("Check Movie Ratings"));
    infoBox = new QGroupBox(tr("Movie Info"));
    infoLayout = new QVBoxLayout;
    infoButtonLayout = new QHBoxLayout;
    infoButtonBox = new QGroupBox();
    ratingsText = new QLabel(tr("Ratings here"));
    infoName = new QLabel(tr("Movie name here"));
    infoKeywords = new QLabel(tr("Movie keywords here"));
    infoName->setVisible(false);
    infoKeywords->setVisible(false);
    ratingsbutton->setVisible(true);
    ratingsText->setVisible(false);
    ratingsButtonBox = new QGroupBox();
    ratingsButtonLayout = new QHBoxLayout;
    ratingsEdit = new QLineEdit;
    ratingsEdit->setVisible(false);
    changeButton = new QPushButton(tr("Change"));
    nextRatingsButton = new QPushButton(tr("Next Rating"));
    changeRatingsButton = new QPushButton (tr("Change Rating"));
    nextRatingsButton->setVisible(false);
    changeRatingsButton->setVisible(false);
    changeButton->setVisible(false);
    nextButton = new QPushButton(tr("Next Movie"));
    addButton = new QPushButton(tr("Add to my Queue"));
    nextButton->setVisible(false);
    addButton->setVisible(false);

QObject::connect(ratingsbutton, SIGNAL(clicked()), this, SLOT(on_ratingsbutton_clicked()));
    QObject::connect(nextRatingsButton, SIGNAL(clicked()), this, SLOT(on_nextRatingsButton_clicked()));
    QObject::connect(changeRatingsButton, SIGNAL(clicked()), this, SLOT(on_changeRatingsButton_clicked()));
    QObject::connect(changeButton, SIGNAL(clicked()), this, SLOT(on_changeButton_clicked()));
    QObject::connect(nextButton, SIGNAL(clicked()), this, SLOT(on_nextButton_clicked()));
    QObject::connect(addButton, SIGNAL(clicked()), this, SLOT(on_addButton_clicked()));

    changeButton->setVisible(false);
    ratingsButtonLayout->addWidget(ratingsbutton);
    ratingsButtonLayout->addWidget(nextRatingsButton);
    ratingsButtonLayout->addWidget(changeRatingsButton);
    ratingsButtonLayout->addWidget(changeButton);
    infoButtonLayout->addWidget(nextButton);
    infoButtonLayout->addWidget(addButton);
    infoButtonBox->setLayout(infoButtonLayout);
    ratingsButtonBox->setLayout(ratingsButtonLayout);

    infoLayout->addWidget(ratingsButtonBox);
    infoLayout->addWidget(ratingsText);
    infoLayout->addWidget(ratingsEdit);
    infoLayout->addWidget(infoName);
    infoLayout->addWidget(infoKeywords);
    infoLayout->addWidget(infoButtonBox);

    infoBox->setLayout(infoLayout);
 }

 void Loginmenu::on_nextButton_clicked()
 {
  if (netflix->actoriter_empty)
  {
    ++netflix->iter;
    if ( ( netflix->iter) == (netflix->iter.returnWhoIBelongTo()->end()) )
    {
      netflix->iter = (netflix->iter.returnWhoIBelongTo())->begin();
    }
    infoName->setText(QString::fromStdString( netflix->printMovie( *(netflix->iter) )));
    infoKeywords->setText(QString::fromStdString( netflix->printKeywords(*(netflix->iter)) ));
  }
  else if (netflix->iter_empty)
  {
    ++netflix->actoriter;
    if ( ( netflix->actoriter) == (netflix->actoriter.returnWhoIBelongTo()->end()) )
    {
      netflix->actoriter = (netflix->actoriter.returnWhoIBelongTo())->begin();
    }
    infoName->setText(QString::fromStdString( netflix->printMovie( *(netflix->actoriter) )));
    infoKeywords->setText(QString::fromStdString( netflix->printKeywords(*(netflix->actoriter)) ));
  }
  
  infoName->setVisible(true);
  infoKeywords->setVisible(true);
  addButton->setVisible(true);
 }

void Loginmenu::on_addButton_clicked()
{
  if (b_title == true)
  {
    netflix->addMovie(a_title);
  }
  else
  {
    if (netflix->actoriter_empty)
    {
      netflix->addMovie(*(netflix->iter));
    }
    else if (netflix->iter_empty)
    {
      netflix->addMovie(*(netflix->actoriter));
    }
    
  }
  
  if (netflix->getCurrentUser()->movieQueue()->size() == 1)
  {
    setCurrentQueue();
  }
  warn->setVisible(false);
}

void Loginmenu::addMenu(Mainmenu *b)
{
    mainmenu = b;
}

void Loginmenu::on_logoutButton_clicked()
{
  mainmenu->clearLogin();
  this->hide();
  mainmenu->show();
}

void Loginmenu::setLogin()
{
  infoName->setVisible(false);
  infoKeywords->setVisible(false);
}