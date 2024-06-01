#include "nivel1.h"

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

Nivel1::Nivel1(QGraphicsScene *&Fondo, int Cant_Franceses, int Cant_Cañones_Alemanes, int Cant_Soldados_Alemanes)
{
    Nivel = Fondo;
    Cantidad_Soldados_Franceses = Cant_Franceses;
    Cantidad_Cañones_Alemanes = Cant_Cañones_Alemanes;
    Cantidad_Soldados_Alemanes = Cant_Soldados_Alemanes;

    Inicializar_Franceses();
    Inicializar_Soldados_Alemanes();
    Inicializar_Cañones();
    Inicializar_Explosiones();
    Inicializar_Proyectiles();
    Inicializar_Colisiones();
    Inicializar_Barrido_De_Gas();
    Inicializar_Efecto_Gas();

    Agachado = false;
    Numero_Bomba = 0;
}

void Nivel1::Primer_Modulo()
{
    Añadir_Soldados_FrancesesEscena();
    Añadir_Cañones();
    Ubicar_Cañones();
}

void Nivel1::Segundo_Modulo()
{
    Añadir_SoldadosAlemanes_EnEscena();
    Ubicar_Soldados_Alemanes();
}

void Nivel1::Añadir_Soldados_FrancesesEscena()
{
    double factor_escala = 0.5;
    for (int i = 0; i < Cantidad_Soldados_Franceses; i++){
        item = Soldados_Franceses_EnEscena[i].get_Objeto_En_La_Pantalla();
        item->setScale(factor_escala);
        item->setPos(640, (i+1) * 130);
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
    connect(Timer, &QTimer::timeout, this, [=]() { Posicionar_Enemigos(1, 50, Timer);
    });
    Timer->start(100);
}

void Nivel1::Lanzamiento_Proyectiles()
{
    //Numero_Ronda++;
    Ubicar_Proyectiles();
    Ejecutar_Movimiento_Parabolico_Bombas();
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

void Nivel1::Secuencia_Animaciones(QGraphicsPixmapItem* Imagen, int frame, vector<QGraphicsPixmapItem*> Secuencia_Animacion, int Timer)
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
    animTimer->start(Timer);
}

void Nivel1::Inicializar_Explosiones()
{
    for (int i = 0; i < Cantidad_Cañones_Alemanes; i++){
        Explosiones.push_back(Objetos(Tipo::Explosion));
        Explosiones[i].Get_Objeto()->setData(Qt::UserRole, "Explosion");
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
    delete Colisiones;
    delete Colisiones_Aliados;
    delete Llegada_Alemanes;
    delete DisparosEnemigos;
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
        case Qt::Key_L:
            if(!Agachado) Disparo_Personaje_Principal();
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
            nuevaImagen = Pierre_De_Gaulle->Get_Imagen_Agachado_Izquierda();
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
            nuevaImagen = Pierre_De_Gaulle->Get_Imagen_Parado_Izquierda();
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
                    Muerte_Pierre(50);
                }else if(tipoObjeto == "Gas_Mostaza"){
                    Muerte_Pierre(20);
                }
                    Colisiones->stop();
                    QTimer::singleShot(500, this, [this]() {
                    Colisiones->start(100);
                    });
                    break;
            }
        }
    }
}

void Nivel1::Muerte_Pierre(int Daño)
{
    int Vida_Actual = Pierre_De_Gaulle->Get_Vida();
    if (!Agachado)Pierre_De_Gaulle->Set_Vida(Vida_Actual-Daño);

    if (Vida_Actual <= 0){
        Secuencia_Animaciones(Pierre_De_Gaulle->get_Objeto_En_La_Pantalla(), 3, Pierre_De_Gaulle->get_Secuencia_Muerte(),100);
    }
}

void Nivel1::Inicializar_Colisiones()
{
    Colisiones = new QTimer(this);
    Colisiones_Aliados = new QTimer(this);
    connect(Colisiones, &QTimer::timeout, this, &Nivel1::Colisiones_PersonajePrincipal);
    connect(Colisiones_Aliados, &QTimer::timeout, this, &Nivel1::Colisiones_SoldadosFranceses);
    Colisiones_Aliados->start(100);
    Colisiones->start(100);
}

void Nivel1::Muerte_Soldado_Frances(int indice, int Daño)
{
    int Vida_Actual = Soldados_Franceses_EnEscena[indice].Get_Vida();
    Soldados_Franceses_EnEscena[indice].Set_Vida(Vida_Actual-Daño);
    if (Vida_Actual < 0 or Vida_Actual == 0){
        Secuencia_Animaciones(Soldados_Franceses_EnEscena[indice].get_Objeto_En_La_Pantalla(), 3, Soldados_Franceses_EnEscena[indice].get_Secuencia_Muerte(), 100);
    }
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
                    if (tipoObjeto == "Explosion" || tipoObjeto == "Gas_Mostaza") {
                        Muerte_Soldado_Frances(i,100);
                        break;
                    }
                }
            }
        }
    }
}

void Nivel1::Inicializar_Soldados_Alemanes()
{
    for (int i = 0; i < Cantidad_Soldados_Alemanes; i++){
        Soldados_Alemanes_EnEscena.push_back(Soldados(Nacionalidad::Aleman));
    }
}

void Nivel1::Añadir_SoldadosAlemanes_EnEscena()
{
    double factor_escala = 0.6;
    for (int i = 0; i < Cantidad_Soldados_Alemanes; i++){
        item = Soldados_Alemanes_EnEscena[i].get_Objeto_En_La_Pantalla();
        item->setScale(factor_escala);
        item->setPos(0, (i+1) * 50);
        Nivel->addItem(item);
    }
}

void Nivel1::Ubicar_Soldados_Alemanes()
{
    Llegada_Alemanes = new QTimer(this);
    connect(Llegada_Alemanes, &QTimer::timeout, this, [=]() {
        Posicionar_Enemigos(2, 100, Llegada_Alemanes);
    });
    Llegada_Alemanes->start(50);
}

void Nivel1::Inicializar_Efecto_Gas()
{
    for (int i = 0; i < int(Fumigacion_Gas.size()); i++){
        Efecto_Gas_Mostaza.push_back(Objetos(Tipo::Gas_Mostaza));
        Efecto_Gas_Mostaza[i].Get_Objeto()->setData(Qt::UserRole, "Gas_Mostaza");
    }
}

void Nivel1::Inicializar_Barrido_De_Gas()
{
    for (int i = 0; i < Cantidad_Soldados_Alemanes; i++){
        Fumigacion_Gas.push_back(Objetos(Tipo::Gas));
    }
}

void Nivel1::Lanzamiento_Gas()
{
    Ubicar_Gas();
    Ejecutar_Movimiento_Circular();
}

void Nivel1::Ubicar_Gas()
{
    int Pos_x;
    int Pos_y;
    for (int k = 0; k < 10; k++){
        item = Fumigacion_Gas[k].Get_Objeto();
        item->setScale(0.03);
        Pos_x = Soldados_Alemanes_EnEscena[k].get_Objeto_En_La_Pantalla()->x()+20;
        Pos_y = Soldados_Alemanes_EnEscena[k].get_Objeto_En_La_Pantalla()->y()+20;
        item->setPos(Pos_x, Pos_y);
        Nivel->addItem(item);
    }
}

void Nivel1::Ejecutar_Movimiento_Parabolico_Gas()
{
    for (int i = 0; i < int(Fumigacion_Gas.size()); ++i) {
        QTimer* timer = new QTimer(this); // Declara el temporizador dentro del bucle
        QGraphicsPixmapItem* item = nullptr;
        QGraphicsPixmapItem* Explosion = nullptr;
        int Limite_ = 0;
        double vx = 0;
        double vy = 0;
        item = Fumigacion_Gas[i].Get_Objeto(); // Ronda
        Limite_ = Fumigacion_Gas[i].Get_Punto_Explosion();
        vx = Fumigacion_Gas[i].Velocidad_X();
        vy = Fumigacion_Gas[i].Velocidad_Y();
        Explosion = Efecto_Gas_Mostaza[i].Get_Objeto(); // PARA EL EFECTO
        double x0 = item->x();
        double y0 = item->y();
        connect(timer, &QTimer::timeout, this, [=]() mutable {
            static double t = 0;
            Movimiento_Parabolico(item, timer, x0, y0, vx, vy, t, Limite_, Explosion, 2, 1.2);
            t += 0.0005;
        });
        timer->start(1);
    }
}

void Nivel1::Ejecutar_Movimiento_Circular()
{
    QTimer* timer = new QTimer(this);
    int vueltas_completadas = 0;
    connect(timer, &QTimer::timeout, this, [=]() mutable {
        static double t = 0;
        double x_centro, y_centro, r, omega, num_vueltas;
        for (int k = 0; k < 10; k++) {
            item = Fumigacion_Gas[k].Get_Objeto();
            x_centro = Fumigacion_Gas[k].Get_Objeto()->x();
            y_centro = Fumigacion_Gas[k].Get_Objeto()->y();
            r = Fumigacion_Gas[k].get_Radio();
            omega = Fumigacion_Gas[k].get_Velocidad_Angular();
            num_vueltas = Fumigacion_Gas[k].get_NumVueltas();
            double newX = x_centro + r * cos(omega * t);
            double newY = y_centro + r * sin(omega * t);
            item->setPos(newX, newY);
        }
        t += 0.05;
        if (t >= 2 * M_PI / omega) {
            vueltas_completadas++;
            if (vueltas_completadas == num_vueltas) {
                timer->stop();
                timer->deleteLater();
                Ejecutar_Movimiento_Parabolico_Gas();
                Inicializar_Disparos_Enemigos();
            }
        }
    });
    timer->start(50);
}

void Nivel1::Ejecutar_Movimiento_Parabolico_Bombas()
{
    for (int i = 0; i < int(Proyectiles_Ronda.size()); ++i) {
        QTimer* timer = new QTimer(this); // Declara el temporizador dentro del bucle
        QGraphicsPixmapItem* item = nullptr;
        QGraphicsPixmapItem* Explosion = nullptr;
        int Limite_ = 0;
        double vx = 0;
        double vy = 0;
        item = Proyectiles_Ronda[i].Get_Objeto(); // Ronda
        Limite_ = Proyectiles_Ronda[i].Get_Punto_Explosion();
        vx = Proyectiles_Ronda[i].Velocidad_X();
        vy = Proyectiles_Ronda[i].Velocidad_Y();
        Explosion = Explosiones[i].Get_Objeto(); // PARA EL EFECTO
        double x0 = item->x();
        double y0 = item->y();
        connect(timer, &QTimer::timeout, this, [=]() mutable {
            static double t = 0;
            Movimiento_Parabolico(item, timer, x0, y0, vx, vy, t, Limite_, Explosion, 1, 0.7);
            t += 0.05;
        });
        timer->start(20);
    }
}

void Nivel1::Movimiento_Parabolico(QGraphicsPixmapItem* Objeto, QTimer* timer, double x0, double y0, double vx, double vy, double t, int Limite, QGraphicsPixmapItem* Efecto, int Case, double Escala)
{
    double g = 9.8;
    double newX = x0 + vx * t;
    double newY = y0 + vy * t + 0.5 * g * t * t;
    Objeto->setPos(newX, newY);

    if (newY > y0 + Limite) {
        Efecto->setPos(newX, newY);
        Efecto->setScale(Escala);
        if (Case == 1){
            Secuencia_Animaciones(Efecto, 4, Explosiones[0].Get_Secuencia_Explosiones(),100);
        }else if (Case == 2){
            Secuencia_Animaciones(Efecto, 4, Efecto_Gas_Mostaza[0].Get_Secuencia_Explosiones(),500);
        }
        Objeto->scene()->removeItem(Objeto);
        timer->stop();    }
}

void Nivel1::Posicionar_Enemigos(int Repeticiones, int Posicion_Final, QTimer* Timer)
{
    bool todosAlcanzaronPosicionFinal = true;
    int Posicion_X = 0;
    int totalItems = Repeticiones * 5;
    for (int i = 0; i < totalItems; i++) {
        if (Repeticiones == 2) {
            item = Soldados_Alemanes_EnEscena[i].get_Objeto_En_La_Pantalla();
        } else if (Repeticiones == 1) {
            item = Cañones_Alemanes_EnEscena[i].Get_Objeto();
        }
        Posicion_X = item->x();
        if (Posicion_X < Posicion_Final) {
            item->setX(Posicion_X + 1);
            todosAlcanzaronPosicionFinal = false;
        }
    } if (todosAlcanzaronPosicionFinal) {
        Timer->stop();
        if (Repeticiones == 2) {
            Lanzamiento_Gas();
        } else if (Repeticiones == 1) {
            Lanzamiento_Proyectiles();
        }
    }
}

void Nivel1::Disparo_Personaje_Principal()
{
    Objetos Bala(Tipo::Balas);
    QTimer *Timer_Disparo = new QTimer();
    QGraphicsPixmapItem *item;
    item = Bala.Get_Objeto();
    item->setScale(0.1);
    item->setPos(Pierre_De_Gaulle->get_Objeto_En_La_Pantalla()->x() - 60, Pierre_De_Gaulle->get_Objeto_En_La_Pantalla()->y() - 38);
    Nivel->addItem(item);
    double vx = -Bala.Velocidad_X();
    double x0 = item->x();
    double t = 0;

    connect(Timer_Disparo, &QTimer::timeout, this, [=]() mutable {
        Movimiento_Rectilineo_Disparos(item, Timer_Disparo, vx, x0, t);
        t += 0.005;
    });
    Timer_Disparo->start(5);
}

void Nivel1::Disparos_Enemigos()
{
    for (int i = 0; i < Cantidad_Soldados_Alemanes; i++){
        if(Probabilidadi_Para_Disparos_Enemigos()){
            Objetos Bala(Tipo::Balas);
            QTimer *Timer_Disparo = new QTimer();
            QGraphicsPixmapItem *item;
            item = Bala.Get_Objeto();
            item->setScale(0.1);
            item->setPos(Soldados_Alemanes_EnEscena[i].get_Objeto_En_La_Pantalla()->x() - 60, Soldados_Alemanes_EnEscena[i].get_Objeto_En_La_Pantalla()->y() - 38);
            Nivel->addItem(item);
            double vx = Bala.Velocidad_X();
            double x0 = item->x();
            double t = 0;
            connect(Timer_Disparo, &QTimer::timeout, this, [=]() mutable {
                Movimiento_Rectilineo_Disparos(item, Timer_Disparo, vx, x0, t);
                t += 0.005;
            });
            Timer_Disparo->start(5);
        }
    }
}

void Nivel1::Inicializar_Disparos_Enemigos()
{
    DisparosEnemigos = new QTimer();
    connect(DisparosEnemigos, &QTimer::timeout, this, &Nivel1::Disparos_Enemigos);
    DisparosEnemigos->start(1000);
}

bool Nivel1::Probabilidadi_Para_Disparos_Enemigos()
{
    double probabilityTrue = 0.7;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    if (dis(gen) < probabilityTrue) {
        return true;
    } else {
        return false;
    }
}

void Nivel1::Movimiento_Rectilineo_Disparos(QGraphicsPixmapItem *Bala, QTimer *timer, double v0, double x0, double t)
{
    double newX = x0 + v0 * t;
    Bala->setPos(newX, Bala->y());
    if (newX > Nivel->width() || newX < 0) {
        timer->stop();
        Nivel->removeItem(Bala);
        delete Bala;
    }
}
