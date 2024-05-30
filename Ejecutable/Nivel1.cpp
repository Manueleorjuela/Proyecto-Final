#include "nivel1.h"
#include <algorithm>
#include <thread>
#include <chrono>

void Nivel1::Inicializar_Franceses()
{
    for (int i = 0; i < Cantidad_Soldados_Franceses; i++){
        Soldados_Franceses_EnEscena.push_back(Soldados(Nacionalidad::Frances));
    }
    Pierre_De_Gaulle = nullptr;
}

void Nivel1::Inicializar_Cañones()
{
    for (int i = 0; i < Cantidad_Cañones_Alemanes; i++){
        Cañones_Alemanes_EnEscena.push_back(Objetos(Tipo::Cañones));
    }
}

Nivel1::Nivel1(QGraphicsScene *&Fondo, int Cant_Franceses, int Cant_Cañones_Alemanes)
{
    Nivel = Fondo;
    Cantidad_Soldados_Franceses = Cant_Franceses;
    Cantidad_Cañones_Alemanes = Cant_Cañones_Alemanes;
    Inicializar_Franceses();
    Inicializar_Cañones();
    Inicializar_Explosiones();
    Inicializar_Proyectiles();
    Inicializar_Colisiones();
    Agachado = false;
    Numero_Bomba = 0;
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
        item = Soldados_Franceses_EnEscena[i].get_Objeto_En_La_Pantalla();
        item->setScale(factor_escala);
        item->setPos(670, (i+1) * 130);
        Nivel->addItem(item);
    }
    Pierre_De_Gaulle = &Soldados_Franceses_EnEscena[0];
}

void Nivel1::Añadir_Cañones()
{
    double factor_escala = 0.5;

    for (int i = 0; i < Cantidad_Cañones_Alemanes; i++){
        item = Cañones_Alemanes_EnEscena[i].Get_Objeto();
        item->setScale(factor_escala);
        item->setPos(20/*-100*/, (i + 1) * 100);
        Nivel->addItem(item);
    }
}

void Nivel1::Ubicar_Cañones()
{
    Timer = new QTimer(this);
    connect(Timer, &QTimer::timeout, this, &Nivel1::Posicion_Canon);
    Timer->start(100);
}

void Nivel1::Lanzamiento_Proyectiles()
{
    //Numero_Ronda++;
    Ubicar_Proyectiles();
    Ejecutar_Movimiento_Parabolico();
    Proyectiles_Ronda.clear();
}

void Nivel1::Ubicar_Proyectiles()
{
    for (int k = 0; k < int(Proyectiles_Ronda.size()); k++){
    item = Proyectiles_Ronda[k].Get_Objeto();
    item->setScale(0.05);
    item->setPos(Cañones_Alemanes_EnEscena[k].Get_Objeto()->x()+40, Cañones_Alemanes_EnEscena[k].Get_Objeto()->y()-10);
    Nivel->addItem(item);
    }
}

void Nivel1::Ejecutar_Movimiento_Parabolico()
{
    QTimer* timer;
    QGraphicsPixmapItem* item;
    QGraphicsPixmapItem* Explosion;
    int Limite_;
    double x0;
    double y0;
    double vx;
    double vy;

    for (int i = 0; i < int(Proyectiles_Ronda.size()); ++i) {
        timer = new QTimer(this);
        item = Proyectiles_Ronda[i].Get_Objeto();
        Explosion = Explosiones[i].Get_Objeto();
        Limite_ = Limite();
        x0 = item->x();
        y0 = item->y();
        vx = Proyectiles_Ronda[i].Velocidad_X();
        vy = Proyectiles_Ronda[i].Velocidad_Y();

        connect(timer, &QTimer::timeout, this, [=]() mutable {
        static double t = 0;
        Movimiento_Parabolico(item, timer, x0, y0, vx, vy, t, Limite_, Explosion);
        t += 0.05; });
        timer->start(20);
    }
}

void Nivel1::Movimiento_Parabolico(QGraphicsPixmapItem* Proyectil, QTimer* timer, double x0, double y0, double vx, double vy, double t, int Limite, QGraphicsPixmapItem* Explosion)
{
    double g = 9.8;
    double newX = x0 + vx * t;
    double newY = y0 + vy * t + 0.5 * g * t * t;
    Proyectil->setPos(newX, newY);

    if (newY > y0 + Limite) {
        Explosion->setPos(newX, newY);
        Explosion->setScale(0.6);
        Secuencia_Animaciones(Explosion, 5, Explosiones[0].Get_Secuencia_Explosiones());
        Proyectil->scene()->removeItem(Proyectil);
        timer->stop();
        timer->deleteLater();
    }
}

void Nivel1::Secuencia_Animaciones(QGraphicsPixmapItem* Imagen, int frame, vector<QGraphicsPixmapItem*> Secuencia_Animacion)
{
    Nivel->addItem(Imagen);
    QTimer* animTimer = new QTimer(this);
    connect(animTimer, &QTimer::timeout, this, [=]() mutable {

        if (frame > -1) {
            Imagen->setPixmap(Secuencia_Animacion[frame]->pixmap());
            frame--;
        } else {
            animTimer->stop();
            animTimer->deleteLater();
            Nivel->removeItem(Imagen);
        }
    });
    animTimer->start(100);
}

int Nivel1::Limite()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,10);
    return dis(gen);
}

void Nivel1::Inicializar_Explosiones()
{
    for (int i = 0; i < Cantidad_Cañones_Alemanes; i++){
        Explosiones.push_back(Objetos(Tipo::Explosion));
        Explosiones[i].Get_Objeto()->setData(Qt::UserRole, "Explosion");
    }
}

void Nivel1::Posicion_Canon()
{
    bool todosAlcanzaronPosicionFinal = true;
    int Posicion_X = 0;

    for (int i = 0; i < Cantidad_Cañones_Alemanes; i++){
        item = Cañones_Alemanes_EnEscena[i].Get_Objeto();
        Posicion_X = item->x();
        if (Posicion_X < 50) {
            item->setX(Posicion_X + 1);
            todosAlcanzaronPosicionFinal = false;
        }
    }
    if (todosAlcanzaronPosicionFinal) {
        Timer->stop();
        Lanzamiento_Proyectiles();
    }
}

void Nivel1::Inicializar_Proyectiles()
{
    for (int k = 0; k < Cantidad_Cañones_Alemanes; k++){
        Proyectiles_Ronda.push_back(Objetos(Tipo::Granadas));
    }
}

Nivel1::~Nivel1()
{
    delete item;
    delete Timer;
    delete parabolicTimer;
    delete Colisiones;
}

void Nivel1::keyPressEvent(QKeyEvent *event)
{

        switch (event->key()) {
        case Qt::Key_A:
            MoverPersonaje(-2,0);
            Ubicar_Personaje_Izquierda();
            Pierre_De_Gaulle->Set_Direccion(Direccion::Izquierda);
            break;
        case Qt::Key_D:
            MoverPersonaje(2, 0);
            Ubicar_Personaje_Derecha();
            Pierre_De_Gaulle->Set_Direccion(Direccion::Derecha);
            break;
        case Qt::Key_W:
            Pierre_De_Gaulle->Set_Direccion(Direccion::Arriba);
            MoverPersonaje(0, -2);
            break;
        case Qt::Key_S:
            Pierre_De_Gaulle->Set_Direccion(Direccion::Abajo);
            MoverPersonaje(0, 2);
            break;
        case Qt::Key_C:
            Agachar_Personaje();
            break;
        }
}

void Nivel1::MoverPersonaje(int deltaX, int deltaY)
{
    QGraphicsPixmapItem *Pierre_De_Gaulle_EnEscena = Pierre_De_Gaulle->get_Objeto_En_La_Pantalla();
    int Posicion_X = Pierre_De_Gaulle_EnEscena->x() + deltaX;
    int Posicion_Y = Pierre_De_Gaulle_EnEscena->y() + deltaY;
    Posicion_X = clamp(Posicion_X, LIMITE_IZQUIERDO, LIMITE_DERECHO);
    Posicion_Y = clamp(Posicion_Y, LIMITE_ARRIBA, LIMITE_ABAJO);
    Pierre_De_Gaulle_EnEscena->setX(Posicion_X);
    Pierre_De_Gaulle_EnEscena->setY(Posicion_Y);
}

void Nivel1::Ubicar_Personaje_Izquierda()
{
    if (!Agachado){
            Pierre_De_Gaulle->setIamgen(Pierre_De_Gaulle->Get_Imagen_Parado_Izquierda());
    }else{
            Pierre_De_Gaulle->setIamgen(Pierre_De_Gaulle->Get_Imagen_Agachado_Izquierda());
    }
    Pierre_De_Gaulle->get_Objeto_En_La_Pantalla()->setPixmap(Pierre_De_Gaulle->Get_Imagen());
}

void Nivel1::Ubicar_Personaje_Derecha()
{
    if (!Agachado){
        Pierre_De_Gaulle->setIamgen(Pierre_De_Gaulle->Get_Imagen_Parado_Derecha());
    }else{
        Pierre_De_Gaulle->setIamgen(Pierre_De_Gaulle->Get_Imagen_Agachado_Derecha());
    }
    Pierre_De_Gaulle->get_Objeto_En_La_Pantalla()->setPixmap(Pierre_De_Gaulle->Get_Imagen());
}

void Nivel1::Agachar_Personaje()
{
    Direccion Orientacion = Pierre_De_Gaulle->Get_Direccion();
    QPixmap nuevaImagen;
    if (!Agachado) {
        switch (Orientacion) {
        case Direccion::Izquierda:
        case Direccion::Arriba:
            nuevaImagen = Pierre_De_Gaulle->Get_Imagen_Agachado_Izquierda();
            break;
        case Direccion::Derecha:
        case Direccion::Abajo:
            nuevaImagen = Pierre_De_Gaulle->Get_Imagen_Agachado_Derecha();
            break;
        default:
            break;
        }
    } else {
        switch (Orientacion) {
        case Direccion::Izquierda:
        case Direccion::Arriba:
            nuevaImagen = Pierre_De_Gaulle->Get_Imagen_Parado_Izquierda();
            break;
        case Direccion::Derecha:
        case Direccion::Abajo:
            nuevaImagen = Pierre_De_Gaulle->Get_Imagen_Parado_Derecha();
            break;
        default:
            break;
        }
    }
    Pierre_De_Gaulle->setIamgen(nuevaImagen);
    Agachado = !Agachado;
    Pierre_De_Gaulle->get_Objeto_En_La_Pantalla()->setPixmap(nuevaImagen);
}

void Nivel1::Colisiones_PersonajePrincipal()
{
    QGraphicsPixmapItem* Pantalla = Pierre_De_Gaulle->get_Objeto_En_La_Pantalla();
    QList<QGraphicsItem*> itemsColisionados = Pantalla->collidingItems();
    QString tipoObjeto;
    QGraphicsPixmapItem* Imagen_Colision;
    if (!itemsColisionados.isEmpty()) {
        for (QGraphicsItem* item : itemsColisionados) {
            Imagen_Colision = dynamic_cast<QGraphicsPixmapItem*>(item);
            if (Imagen_Colision) {
                tipoObjeto = Imagen_Colision->data(Qt::UserRole).toString();
                if (tipoObjeto == "Explosion"){
                    Colisiones->stop();
                    Muerte_Pierre(20);
                    QTimer::singleShot(1000, this, [this]() {
                        Colisiones->start(100);
                    });
                    break;
                }
            }
        }
    }
}

void Nivel1::Muerte_Pierre(int Daño)
{
    int Vida_Actual = Pierre_De_Gaulle->Get_Vida();
    if (Vida_Actual == 0){
        Secuencia_Animaciones(Pierre_De_Gaulle->get_Objeto_En_La_Pantalla(), 3, Pierre_De_Gaulle->get_Secuencia_Muerte());
    }else{
        Pierre_De_Gaulle->Set_Vida(Vida_Actual-Daño);
    }
}

void Nivel1::Inicializar_Colisiones()
{
    Colisiones = new QTimer(this);
    connect(Colisiones, &QTimer::timeout, this, &Nivel1::Colisiones_PersonajePrincipal);
    connect(Colisiones, &QTimer::timeout, this, &Nivel1::Colisiones_SoldadosFranceses);
    Colisiones->start(100);
}

void Nivel1::Muerte_Soldado_Frances(int indice)
{
    Secuencia_Animaciones(Soldados_Franceses_EnEscena[indice].get_Objeto_En_La_Pantalla(), 3, Soldados_Franceses_EnEscena[indice].get_Secuencia_Muerte());
}

void Nivel1::Colisiones_SoldadosFranceses()
{
    for (int i = 1; i < int(Soldados_Franceses_EnEscena.size()); i++) {
        QGraphicsPixmapItem* Soldado = Soldados_Franceses_EnEscena[i].get_Objeto_En_La_Pantalla();
        QList<QGraphicsItem*> itemsColisionados = Soldado->collidingItems();
        QString tipoObjeto;
        QGraphicsPixmapItem* Imagen_Colision;
        if (!itemsColisionados.isEmpty()) {
            for (QGraphicsItem* item : itemsColisionados) {
                Imagen_Colision = dynamic_cast<QGraphicsPixmapItem*>(item);
                if (Imagen_Colision) {
                    tipoObjeto = Imagen_Colision->data(Qt::UserRole).toString();
                    if (tipoObjeto == "Explosion") {
                        Muerte_Soldado_Frances(i);
                        break;
                    }
                }
            }
        }
    }
}
