#ifndef NIVELES_H
#define NIVELES_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QString>

class Niveles : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:

    QString Direccion_Fondo;
    QGraphicsScene *Escena;
    QPixmap *Pixmap;

public:
    Niveles();
    void Cargar_PantallaInicial();
    void Cargar_Primer_Nivel();
    void Cargar_Segundo_Nivel();
    void Remover_Fondo();

    QGraphicsScene *Get_Escena();
    ~Niveles();
};

#endif // NIVELES_H
