#include "nivel1.h"
#include "qobjectdefs.h"


void Nivel1::Inicializar_Franceses()
{
    for (int i = 0; i < Cantidad_Soldados_Franceses; i++){
        Soldados_Franceses.push_back(Soldados(Nacionalidad::Frances));
    }
    Pierre_De_Gaulle = &Soldados_Franceses[2];
    Pierre_De_Gaulle_EnEscena = nullptr;
}

void Nivel1::Inicializar_Cañones()
{
    for (int i = 0; i < Cantidad_Cañones_Alemanes; i++){
        Cañones.push_back(Objetos(Tipo::Cañones));
    }
}

Nivel1::Nivel1(QGraphicsScene *&Fondo, int Cant_Franceses, int Cant_Cañones_Alemanes)
{
    Nivel = Fondo;
    Cantidad_Soldados_Franceses = Cant_Franceses;
    Cantidad_Cañones_Alemanes = Cant_Cañones_Alemanes;
    Inicializar_Franceses();
    Inicializar_Cañones();
    Timer = new QTimer(this);
}

void Nivel1::Primer_Modulo()
{
    Añadir_Soldados_FrancesesEscena();
    Añadir_Cañones();
    Ubicar_Cañones();

}

void Nivel1::Añadir_Soldados_FrancesesEscena()
{
    double factor_escala = 0.5;
    for (int i = 0; i < Cantidad_Soldados_Franceses; i++){
        QPixmap Direccion(Soldados_Franceses[i].Get_Direccion_Imagen());
        item = new  QGraphicsPixmapItem(Direccion);
        item->setScale(factor_escala);
        item->setPos(670, i*130);
        SoldadosFranceses_EnEscena.push_back(item);
        Nivel->addItem(item);
    }
    Pierre_De_Gaulle_EnEscena = SoldadosFranceses_EnEscena[2];
}

void Nivel1::Añadir_Cañones()
{
    double factor_escala = 0.5;

    for (int i = 0; i < Cantidad_Soldados_Franceses;i++){
        QPixmap Direccion(Cañones[i].get_Direcccion_Imagen());
        item = new  QGraphicsPixmapItem(Direccion);
        item->setScale(factor_escala);
        item->setPos(-100, (i+1)*100);
        Cañones_EnEscena.push_back(item);
        Nivel->addItem(item);
    }
}

void Nivel1::Ubicar_Cañones()
{
    connect(Timer, &QTimer::timeout, this, &Nivel1::Posicion_Canon);
    Timer->start(100);
}


void Nivel1::keyPressEvent(QKeyEvent *Tecla_Presionada)
{
    int Posicion_X = Pierre_De_Gaulle_EnEscena->x();
    int Posicion_Y = Pierre_De_Gaulle_EnEscena->y();

    switch(Tecla_Presionada->key()){

    case Qt::Key_A:
        Pierre_De_Gaulle_EnEscena->setX(Posicion_X-1);
        break;
    case Qt::Key_D:
        Pierre_De_Gaulle_EnEscena->setX(Posicion_X+1);
        break;
    default:
        break;
    }
}

void Nivel1::Posicion_Canon()
{
    bool todosAlcanzaronPosicionFinal = true;
    int Posicion_X = 0;
    QGraphicsPixmapItem* Cañon;

    for (int i = 0; i < Cantidad_Cañones_Alemanes; i++){
        Cañon = Cañones_EnEscena[i];
        Posicion_X = Cañon->x();
        Cañon->setX(Posicion_X+1);
        if (Posicion_X < 50) {
            Cañon->setX(Posicion_X + 1);
                todosAlcanzaronPosicionFinal = false;
        }
    }
    if (todosAlcanzaronPosicionFinal) {
        Timer->stop();
    }
}


Nivel1::~Nivel1()
{
    delete item;
    delete Timer;
    delete Pierre_De_Gaulle_EnEscena;
}
