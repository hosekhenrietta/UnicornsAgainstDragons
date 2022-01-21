#ifndef UNICORNSAGAINSTDRAGONS_H
#define UNICORNSAGAINSTDRAGONS_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

class UnicornsAgainstDragons : public QWidget
{
    Q_OBJECT

public:
    UnicornsAgainstDragons(QWidget *parent = nullptr);

private slots:
    void buttonClicked();
    void newGameButtonClicked();

private:
    void newGame(); // új játék kezdése
    void stepGame(int x, int y); // játék léptetése
    void generateTable(); // tábla létrehozása
    void checkGame(); // vége van-e a játéknak ha igen, ki nyert

    int _currentPlayer; // 1 - unikornis 0 - sarkany
    int _uniOrDrag; // 1 - unikornis 0 - sarkany
    int _isAttack;
    int _unicornCount;
    int _dragonCount;
    int tmp;
    QGridLayout* _tableLayout;
    QVBoxLayout* _mainLayout;
    QPushButton* _newGameButton;
    QPushButton* _currentText;
    QVector<QVector<QPushButton*> > _buttonTable;
    int** _gameTable; // Milyen állatka van rajta 0- üres 1-unikornis 2-sarkany
};
#endif // UNICORNSAGAINSTDRAGONS_H
