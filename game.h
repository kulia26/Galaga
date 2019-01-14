#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QVector>
#include "skystar.h"
#include "player.h"
#include "enemy.h"
#include "explosion.h"
#include "wave.h"
#include <memory>

namespace Ui {
  class Game;
}

class Game : public QWidget
{
  Q_OBJECT

public:
  enum class State{Play, PlayerHurt, GameOver, GetReady};
  void changeState(State state);
  static Game& getInstance();
  QVector<std::shared_ptr<Shot>>& getShots();
  long int& getCounter();
  void executePlay();
  void executePlayerHurt();
  void executeGetReady();
  void executeGameOver();
  void resolveCollisions();
  void nextWave();
  void makeDemage(std::shared_ptr<PhysicalObject> object1, std::shared_ptr<PhysicalObject> object2);
  std::shared_ptr<Explosion> makeExplosion(std::shared_ptr<PhysicalObject> object1, std::shared_ptr<PhysicalObject> object2);
  void paintEvent(QPaintEvent *event);
  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);


  bool loadGame();
  bool saveGame() const;
  void newGame();
  void read(const QJsonObject &json);
  void write(QJsonObject &json) const;
private:
  Ui::Game *ui;
  explicit Game(QWidget *parent = nullptr);
  Game(Game const&) = delete;
  ~Game();
  Game& operator= (Game const&) = delete;
  long int COUNTER;
  unsigned int GETREADY;

  QTimer *timer;
  QFont emulogic;
  std::shared_ptr<Player> player;
  QVector<std::shared_ptr<Player>> players;
  QVector<std::shared_ptr<SkyStar>> sky;
  QVector<std::shared_ptr<Wave>> waves;
  QVector<std::shared_ptr<Enemy>> enemies;
  QVector<std::shared_ptr<Explosion>> explosions;
  QVector<std::shared_ptr<Shot>> shots;

  QVector<std::shared_ptr<Drawed>> drawable;
  QVector<std::shared_ptr<PhysicalObject>> physical;
  State state;
};

#endif // GAME_H
