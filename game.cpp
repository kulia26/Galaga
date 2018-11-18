#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Game)
{
  ui->setupUi(this);
  this->setFixedSize(800,600);
  this->setPalette(QPalette(QColor(255,255,255,0)));
  this->setWindowTitle("Galaga");
}

Game::~Game()
{
  delete ui;
}
