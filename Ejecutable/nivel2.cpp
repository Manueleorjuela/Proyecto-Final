#include "nivel2.h"

Nivel2::Nivel2(QGraphicsScene *&Fondo)
{
    Nivel = Fondo;
    Inicializar_Ametralladoras();
    Adolfo = Nacionalidad::Aleman;
    Agachado = false;
}

//Personaje principal
void Nivel2::Ubicar_PersonajePrincipal()
{
    item = Adolfo.get_Objeto_En_La_Pantalla();
    item->setScale(0.6);
    item->setPos(60,350);
    Nivel->addItem(item);
}

void Nivel2::MoverPersonaje(int deltaX, int deltaY)
{
    QGraphicsPixmapItem *Adolfo_EnEscena = Adolfo.get_Objeto_En_La_Pantalla();
    int Posicion_X = Adolfo_EnEscena->x() + deltaX;
    int Posicion_Y = Adolfo_EnEscena->y() + deltaY;
    Posicion_X = clamp(Posicion_X, LIMITE_IZQUIERDO, LIMITE_DERECHO);
    Posicion_Y = clamp(Posicion_Y, LIMITE_ARRIBA, LIMITE_ABAJO);
    Adolfo_EnEscena->setX(Posicion_X);
    Adolfo_EnEscena->setY(Posicion_Y);
}

void Nivel2::Ubicar_Personaje_Izquierda()
{
    if (!Agachado){
        Adolfo.setIamgen(Adolfo.Get_Imagen_Parado_Izquierda());
    }else{
        Adolfo.setIamgen(Adolfo.Get_Imagen_Agachado_Izquierda());
    }
    Adolfo.get_Objeto_En_La_Pantalla()->setPixmap(Adolfo.Get_Imagen());
}

void Nivel2::Ubicar_Personaje_Derecha()
{
    if (!Agachado){
        Adolfo.setIamgen(Adolfo.Get_Imagen_Parado_Derecha());
    }else{
        Adolfo.setIamgen(Adolfo.Get_Imagen_Agachado_Derecha());
    }
    Adolfo.get_Objeto_En_La_Pantalla()->setPixmap(Adolfo.Get_Imagen());
}

void Nivel2::Agachar_Personaje()
{
    Direccion Orientacion = Adolfo.Get_Direccion();
    QPixmap nuevaImagen;
    if (!Agachado) {
        switch (Orientacion) {
        case Direccion::Izquierda:
        case Direccion::Arriba:
            nuevaImagen = Adolfo.Get_Imagen_Agachado_Derecha();
            break;
        case Direccion::Derecha:
        case Direccion::Abajo:
            nuevaImagen = Adolfo.Get_Imagen_Agachado_Derecha();
            break;
        default:
            break;
        }
    } else {
        switch (Orientacion) {
        case Direccion::Izquierda:
        case Direccion::Arriba:
            nuevaImagen = Adolfo.Get_Imagen_Parado_Derecha();
            break;
        case Direccion::Derecha:
        case Direccion::Abajo:
            nuevaImagen = Adolfo.Get_Imagen_Parado_Derecha();
            break;
        default:
            break;
        }
    }
    Adolfo.setIamgen(nuevaImagen);
    Agachado = !Agachado;
    Adolfo.get_Objeto_En_La_Pantalla()->setPixmap(nuevaImagen);
}

void Nivel2::Lanzar_Bengalas()
{
    Objetos Bengala(Tipo::Bengala);
    //QTimer *Timer_ = new QTimer(this);
    QGraphicsPixmapItem *item;
    item = Bengala.Get_Objeto();
    item->setScale(0.08);
    item->setPos(300, 300);
    Nivel->addItem(item);

    /*
    double vx = Bengala.Velocidad_X();
    double vy = Bengala.Velocidad_Y();
    double x0 = item->x();
    double y0 = item->y();
    double Limite_ = Bengala.Get_Punto_Explosion();

    double t = 0;
    connect(Timer_, &QTimer::timeout, this, [=]() mutable {
        Movimiento_Parabolico(item, Timer_, x0, y0, vx, vy, t, Limite_);
        t += 0.05;
    });

    Timer_->start(50);*/
}

void Nivel2::Movimiento_Parabolico(QGraphicsPixmapItem *Objeto, QTimer *timer, double x0, double y0, double vx, double vy, double t, double Limite)
{
    double g = 9.8;
    double newX = x0 + vx * t;
    double newY = y0 + vy * t + 0.5 * g * t * t;

    qDebug() << "Posición actual de la bengala: " << newY;
    Objeto->setPos(newX, newY);

    if (newY > (y0 + Limite)) {
        qDebug() << "Se destruyó la bengala";
        Objeto->scene()->removeItem(Objeto);
        timer->stop();
        timer->deleteLater();
    }
}

void Nivel2::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A:
        MoverPersonaje(-2,0);
        Ubicar_Personaje_Izquierda();
        Adolfo.Set_Direccion(Direccion::Izquierda);
        break;
    case Qt::Key_D:
        MoverPersonaje(2, 0);
        Ubicar_Personaje_Derecha();
        Adolfo.Set_Direccion(Direccion::Derecha);
        break;
    case Qt::Key_W:
        Adolfo.Set_Direccion(Direccion::Arriba);
        MoverPersonaje(0, -2);
        break;
    case Qt::Key_S:
        Adolfo.Set_Direccion(Direccion::Abajo);
        MoverPersonaje(0, 2);
        break;
    case Qt::Key_C:
        Agachar_Personaje();
        break;
    case Qt::Key_L:
        if(!Agachado) Lanzar_Bengalas();
        break;
    }
}

//Ametralladoras
void Nivel2::Inicializar_Ametralladoras()
{
    for (int i = 0; i < 3; i++){
        Ametralladoras_EnEscena.push_back(Objetos(Tipo::Ametralladoras));
    }
}

void Nivel2::Ubicar_Ametralladoras()
{
    for (int i = 0; i < int(Ametralladoras_EnEscena.size()); i++){
        item = Ametralladoras_EnEscena[i].Get_Objeto();
        item->setScale(0.15);
        if (i < 2){
            item->setPos(710, (i+1)*120);
        }else{
            item->setPos(710, (i+2)*120);
        }
        Nivel->addItem(item);
    }
}

void Nivel2::Modulo()
{
    Ubicar_Ametralladoras();
    Ubicar_PersonajePrincipal();
}

Nivel2::~Nivel2()
{
    delete item;
}

