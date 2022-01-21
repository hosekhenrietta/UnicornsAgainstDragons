#include "unicornsagainstdragons.h"
//#include "ui_unicornsagainstdragons.h"
#include <QMessageBox>
#include <iostream>


UnicornsAgainstDragons::UnicornsAgainstDragons(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(400, 400);
    setBaseSize(400,400);
    setWindowTitle(tr("Unicorns Against Dragons"));


    QString newGameColor = "QPushButton { background-color: rgb(" + QString::number(165) + "," + QString::number(216) + "," + QString::number(193) + ") }";
    QString currentColor = "QPushButton { color: black; background-color: rgb(" + QString::number(212) + "," + QString::number(196) + "," + QString::number(185) + ")}";
    QString tableColor = "QPushButton { background-color: rgb(" + QString::number(212) + "," + QString::number(223) + "," + QString::number(239) + ") }";

    _newGameButton = new QPushButton(tr("NEW GAME"));
    _newGameButton->setStyleSheet(( tableColor));
    connect(_newGameButton, SIGNAL(clicked()), this, SLOT(newGameButtonClicked()));

    _currentText = new QPushButton(tr("🦄 Current Player: Unicorn 🦄"));
    _currentText->setStyleSheet(( currentColor));
    _currentText->setEnabled(false);

    _mainLayout = new QVBoxLayout();
    _mainLayout->addWidget(_newGameButton);
    _mainLayout->addWidget(_currentText);


    _tableLayout = new QGridLayout();
    generateTable();

    _mainLayout->addLayout(_tableLayout);
    setLayout(_mainLayout);

    newGame();
}

void UnicornsAgainstDragons::newGame()
{
    QString tableColor = "QPushButton { background-color: rgb(" + QString::number(212) + "," + QString::number(223) + "," + QString::number(239) + ") }";
    _currentText->setText(" 🦄 Current Player: Unicorn 🦄");
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
        {
            _buttonTable[i][j]->setStyleSheet(( tableColor));
            _gameTable[i][j] = 0;
            _buttonTable[i][j]->setText("");
            _buttonTable[i][j]->setEnabled(false);
            if(i == 0 || i == 1){
                _gameTable[i][j] = 2;
                _buttonTable[i][j]->setText("🐲");
                //_buttonTable[i][j]->setEnabled(true); //mert ugyis az unikornis kezd
            }

            if(i == 7 || i == 6 ){
                _gameTable[i][j] = 1;
                _buttonTable[i][j]->setText("🦄");
                if ( i==6 ){
                    _buttonTable[i][j]->setEnabled(true);
                }
            }
        }

    _isAttack = 0;
    _unicornCount = 16;
    _dragonCount = 16;
    tmp = 0;
    _uniOrDrag = 1;
    _currentPlayer = 1; // először az unikornis lép
}

void UnicornsAgainstDragons::stepGame(int x, int y)
{

    QString unicornColor = "QPushButton { background-color: rgb(" + QString::number(242) + "," + QString::number(180) + "," + QString::number(180) + ") }";
    QString dragonColor = "QPushButton { background-color: rgb(" + QString::number(191) + "," + QString::number(242) + "," + QString::number(157) + ") }";
    QString tableColor = "QPushButton { background-color: rgb(" + QString::number(212) + "," + QString::number(223) + "," + QString::number(239) + ") }";

    if (_gameTable[x][y] > 0 && _isAttack == 0){

        tmp = 1;

// ha van rajta állatka akkor beállitjuk merre lehet lépni
{
        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                _buttonTable[i][j]->setEnabled(false);
            }
        }

//If unikornis
        if (_gameTable[x][y] == 1 ){
            _buttonTable[x][y]->setStyleSheet(( unicornColor));
            if (_gameTable[x-1][y] == 0 ) {
            _buttonTable[x-1][y]->setStyleSheet(( unicornColor));
            _buttonTable[x-1][y]->setEnabled(true);
            _uniOrDrag = 1;
            tmp = 1;
            }

// le tud utni valakit az unikornis?
            if (y !=0 && _gameTable[x-1][y-1] == 2){
                _buttonTable[x-1][y-1]->setStyleSheet(( unicornColor));
                _buttonTable[x-1][y-1]->setEnabled(true);
            }
            if (y != 7 && _gameTable[x-1][y+1] == 2){
                _buttonTable[x-1][y+1]->setStyleSheet(( unicornColor));
                _buttonTable[x-1][y+1]->setEnabled(true);
            }

        }

//If sarkany
        if (_gameTable[x][y] == 2){
            _buttonTable[x][y]->setStyleSheet(( dragonColor));
           if (_gameTable[x+1][y] == 0) {
                _buttonTable[x+1][y]->setStyleSheet(( dragonColor));
                _buttonTable[x+1][y]->setEnabled(true);
                _uniOrDrag = 0;
                tmp = 1;
           }

// le tud utni valakit a sarkany?
            if (y != 0 && _gameTable[x+1][y-1] == 1){
                _buttonTable[x+1][y-1]->setStyleSheet(( dragonColor));
                _buttonTable[x+1][y-1]->setEnabled(true);
            }

            if (y != 7 && _gameTable[x+1][y+1] == 1){
                _buttonTable[x+1][y+1]->setStyleSheet(( dragonColor));
                _buttonTable[x+1][y+1]->setEnabled(true);
            }
         }

}
}

// itt jön a lépés -> ez a masodik kattintásnál jön

    // ha csak elore lép
        if (_gameTable[x][y] == 0){

            if (_uniOrDrag == 1){
                _buttonTable[x][y]->setText("🦄");
                _buttonTable[x][y]->setStyleSheet((tableColor));
                _buttonTable[x][y]->setEnabled(false);
                _gameTable[x][y] = 1;
                _buttonTable[x+1][y]->setText("");
                _buttonTable[x+1][y]->setStyleSheet((tableColor));
                _gameTable[x+1][y] = 0;
                if (y != 0)
                _buttonTable[x][y-1]->setStyleSheet((tableColor));
                if (y != 7)
                _buttonTable[x][y+1]->setStyleSheet((tableColor));

                _currentPlayer = 0;
                tmp = 2;

            }
            if (_uniOrDrag == 0){
                _buttonTable[x][y]->setText("🐲");
                _buttonTable[x][y]->setStyleSheet((tableColor));
                _buttonTable[x][y]->setEnabled(false);
                _gameTable[x][y] = 2;
                _buttonTable[x-1][y]->setText("");
                _buttonTable[x-1][y]->setStyleSheet((tableColor));
                _gameTable[x-1][y] = 0;
                if (y != 0)
                _buttonTable[x][y-1]->setStyleSheet((tableColor));
                if (y != 7)
                _buttonTable[x][y+1]->setStyleSheet((tableColor));
                _currentPlayer = 1;
                tmp = 2;

            }

        }

    // unikornis támad
        if (_currentPlayer == 1 && _gameTable[x][y] == 2 && tmp == 1 )
        {
            _buttonTable[x][y]->setText("🦄");
            _buttonTable[x][y]->setStyleSheet((tableColor));
            _buttonTable[x][y]->setEnabled(false);
            _gameTable[x][y] = 1;

            if(y != 7 && _gameTable[x+1][y+1] == 1) {
                _buttonTable[x+1][y+1]->setText("");
                _gameTable[x+1][y+1] = 0;
                _buttonTable[x+1][y+1]->setStyleSheet((tableColor));
                _buttonTable[x+1][y+1]->setEnabled(false);

                _buttonTable[x][y+1]->setStyleSheet((tableColor));
                _buttonTable[x][y+1]->setEnabled(false);
                if( y != 6){
                    _buttonTable[x][y+2]->setStyleSheet((tableColor));
                    _buttonTable[x][y+2]->setEnabled(false);
                }

                _dragonCount--;

              }
            if(y != 0 && _gameTable[x+1][y-1] == 1) {
                _buttonTable[x+1][y-1]->setText("");
                _gameTable[x+1][y-1] = 0;
                _buttonTable[x+1][y-1]->setStyleSheet((tableColor));
                _buttonTable[x+1][y-1]->setEnabled(false);

                _buttonTable[x][y-1]->setStyleSheet((tableColor));
                _buttonTable[x][y-1]->setEnabled(false);
                if( y != 1){
                    _buttonTable[x][y-2]->setStyleSheet((tableColor));
                    _buttonTable[x][y-2]->setEnabled(false);
                }

                _dragonCount--;

              }
            _currentPlayer = 0;
            _isAttack = 0;
            tmp = 2;
        }


    // sarkany tamad
        if (_currentPlayer == 0 && _gameTable[x][y] == 1 && tmp ==1 )
        {
            _buttonTable[x][y]->setText("🐲");
            _buttonTable[x][y]->setStyleSheet((tableColor));
            _buttonTable[x][y]->setEnabled(false);
            _gameTable[x][y] = 2;

            if(y != 0 && _gameTable[x-1][y-1] == 2) {
                _buttonTable[x-1][y-1]->setText("");
                _gameTable[x-1][y-1] = 0;
                _buttonTable[x-1][y-1]->setStyleSheet((tableColor));
                _buttonTable[x-1][y-1]->setEnabled(false);

                _buttonTable[x][y-1]->setStyleSheet((tableColor));
                _buttonTable[x][y-1]->setEnabled(false);
                if( y != 6){
                _buttonTable[x][y-2]->setStyleSheet((tableColor));
                _buttonTable[x][y-2]->setEnabled(false);
                }

                _unicornCount--;

              }
            if(y != 7 && _gameTable[x-1][y+1] == 2) {
                _buttonTable[x-1][y+1]->setText("");
                _gameTable[x-1][y+1] = 0;
                _buttonTable[x-1][y+1]->setStyleSheet((tableColor));
                _buttonTable[x-1][y+1]->setEnabled(false);

                _buttonTable[x][y+1]->setStyleSheet((tableColor));
                _buttonTable[x][y+1]->setEnabled(false);
                if( y != 1){
                _buttonTable[x][y+2]->setStyleSheet((tableColor));
                _buttonTable[x][y+2]->setEnabled(false);
                }

                _unicornCount--;

              }
            _currentPlayer = 1;
            _isAttack = 0;
            tmp = 2;
        }

  checkGame();


// visszaallitom a gombokat amiket lehet nyomni
    if (tmp == 2) {
        for (int x = 0; x < 8; ++x)
        {
            for (int y = 0; y < 8; ++y)
            {
                if (_currentPlayer == 1){
                    if (_gameTable[x][y] == 1 && (_gameTable[x-1][y] == 0 || _gameTable[x-1][y-1] == 2 || _gameTable[x-1][y+1] == 2)){
                        _buttonTable[x][y]->setEnabled(true);

                    }
                } else {
                    if (_gameTable[x][y] == 2 && (_gameTable[x+1][y] == 0 || _gameTable[x+1][y-1] == 1 || _gameTable[x+1][y+1] == 1)){
                        _buttonTable[x][y]->setEnabled(true);

                    }
                }
            }
        }
        tmp = 0;
    }


}

void UnicornsAgainstDragons::generateTable()
{
    _gameTable = new int*[8];
    _buttonTable.resize(8);

    for (int i = 0; i < 8; ++i)
    {
        _gameTable[i] = new int[8];
        _buttonTable[i].resize(8);
        for (int j = 0; j < 8; ++j)
        {
            _buttonTable[i][j]= new QPushButton(this);
            _buttonTable[i][j]->setFont(QFont("Comic Sans MS",10, QFont::Bold));
            _buttonTable[i][j]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
            _tableLayout->addWidget(_buttonTable[i][j], i, j);

            connect(_buttonTable[i][j], SIGNAL(clicked()), this, SLOT(buttonClicked()));
        }
    }
}


void UnicornsAgainstDragons::buttonClicked()
{
    QPushButton* senderButton = dynamic_cast <QPushButton*> (QObject::sender());
    int location = _tableLayout->indexOf(senderButton);

    if ((_currentPlayer == 1 && _gameTable[location / 8][location % 8] == 2) || (_currentPlayer == 0 && _gameTable[location / 8][location % 8] == 1) ) { _isAttack = 1;}


    stepGame(location / 8, location % 8);
}

void UnicornsAgainstDragons::newGameButtonClicked()
{
    //QMessageBox::information(this, tr("New Game"), tr("Let the game begin!"));
    newGame();
}

void UnicornsAgainstDragons::checkGame()
{
    int won = 0;

    if(_currentPlayer == 1) {_currentText->setText(" 🦄 Current Player: Unicorn 🦄");}
    if(_currentPlayer == 0) {_currentText->setText(" 🐲 Current Player: Dragon 🐲");}

//ellenorzesek

    for (int i = 0; i < 8; ++i)
    {
        if (_gameTable[0][i] == 1 || _dragonCount == 0 )
        {
            won = 1;
        }
    }
    for (int j = 0; j < 8; ++j)
    {
        if (_gameTable[7][j] == 2 || _unicornCount == 0)
        {
            won = 2;
        }
    }

// ha nyert valaki kiírom

    if (won == 1)
    {
        QMessageBox::information(this, tr("The game is over!"), tr("The unicorns defeated the dragons!"));
        newGame();
    }
    else if (won == 2)
    {
        QMessageBox::information(this, tr("The game is over!"), tr("The dragons defeated the unicorns!"));
        newGame();
    }
}
