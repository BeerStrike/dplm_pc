#ifndef SCANER_H
#define SCANER_H
#include <QHostAddress>

class Scaner
{
private:
    float xPos;
    float yPos;
    float zPos;
    QHostAddress IP;
public:
    Scaner(QHostAddress IPAdress);
    QHostAddress getIP();
};

#endif // SCANER_H
