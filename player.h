#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QWidget>

class player : public QWidget
{
  Q_OBJECT
public:
  explicit player(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // PLAYER_H