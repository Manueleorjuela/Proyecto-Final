#ifndef ESCENAS_NIVELES_H
#define ESCENAS_NIVELES_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

class Escenas_Niveles : public QObject
{
    Q_OBJECT;
private:

    QGraphicsScene *Escena;
    QPixmap Direccion_Fondo;
    QGraphicsPixmapItem *Fondo;
    QGraphicsView *Vista;

public:
    Escenas_Niveles(QObject *parent = nullptr);
    void Mostrar_Nivel_1();
    void Mostrar_Nivel_2();
    ~Escenas_Niveles();
};

#endif // ESCENAS_NIVELES_H
