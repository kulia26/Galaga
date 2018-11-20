#include "game.h"
#include "ui_game.h"
#include <QPainter>

Game::Game(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Game)
{
  ui->setupUi(this);
  this->setFixedSize(800,600);
  this->setPalette(QPalette(QColor(255,255,255,0)));
  this->setWindowTitle("Galaga");

  for(int i = 0; i < 500; i++){
    sky.push_back(new SkyStar);
  }
}

Game::~Game()
{
  delete ui;
}

void Game::paintEvent(QPaintEvent *event)
{
  //Встановлюємо колір вікна в зелений
  setPalette(QPalette(QPalette::Window,Qt::black));
  QPainter painter(this);
  painter.setPen(Qt::NoPen);
  for(int i = 0; i < sky.size(); i++){
      QBrush brush(sky[i]->color);
      painter.setBrush(brush);
      painter.drawRect(sky[i]->star);
  }

}
