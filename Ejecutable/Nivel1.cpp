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

Nivel1::Nivel1(QGraphicsScene *&Fondo)
{
    Nivel = Fondo;
    Cantidad_Soldados_Franceses = 4;
    Cantidad_Cañones_Alemanes = 5;
    Cantidad_Soldados_Alemanes = 10;
    Inicializar_Franceses();
    Inicializar_Soldados_Alemanes();
    Inicializar_Cañones();
    Inicializar_Explosiones();
    Inicializar_Proyectiles();
    Inicializar_Colisiones();
    Inicializar_Barrido_De_Gas();
    Inicializar_Efecto_Gas();
    Inicializar_Ejecucion();
    Termino_Nivel = false;
    Ganar = false;
    Agachado = false;
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

bool Nivel1::get_Ganar()
{
    return Ganar;
}

bool Nivel1::get_TerminoNivel()
{
    return Termino_Nivel;
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
        item->setPos(-100, (i + 1) * 100);
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
            delete animTimer;
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
    delete Movimiento_Enemigos;
    delete Ejecucion_Nivel;
    Proyectiles_Ronda.clear();
    Soldados_Alemanes_EnEscena.clear();
    Soldados_Franceses_EnEscena.clear();
    Explosiones.clear();
    Fumigacion_Gas.clear();
    Efecto_Gas_Mostaza.clear();
    Cañones_Alemanes_EnEscena.clear();
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
                    if (tipoObjeto == "Explosion") {
                    Muerte_Pierre(100);
                } else if (tipoObjeto == "Gas_Mostaza") {
                    Muerte_Pierre(50);
                } else if (tipoObjeto == "Bala") {
                    Muerte_Pierre(100);
                }
                Colisiones->stop();
                QTimer::singleShot(500, this, [this]() {
                    Colisiones->start(100);
                });
                break;
            }
        }
        itemsColisionados.clear();
    }
}

void Nivel1::Muerte_Pierre(int Daño)
{
    int Vida_Actual = Pierre_De_Gaulle->Get_Vida();
    int Nueva_Vida = Vida_Actual - Daño;
    if (!Agachado){
        Pierre_De_Gaulle->Set_Vida(Vida_Actual-Daño);
    if (Nueva_Vida <= 0){
            Secuencia_Animaciones(Pierre_De_Gaulle->get_Objeto_En_La_Pantalla(), 3, Pierre_De_Gaulle->get_Secuencia_Muerte(),300);
            Pierre_De_Gaulle->Set_Vivo(false);
        }
    }
}

void Nivel1::Inicializar_Colisiones()
{
    Colisiones = new QTimer(this);
    Colisiones_Aliados = new QTimer(this);
    Colisiones_Enemigos = new QTimer(this);
    connect(Colisiones, &QTimer::timeout, this, &Nivel1::Colisiones_PersonajePrincipal);
    connect(Colisiones_Aliados, &QTimer::timeout, this, &Nivel1::Colisiones_SoldadosFranceses);
    connect(Colisiones_Enemigos, &QTimer::timeout, this, &Nivel1::Colisiones_SoldadosAlemanes);
    Colisiones_Aliados->start(50);
    Colisiones_Enemigos->start(50);
    Colisiones->start(50);

}

void Nivel1::Muerte_Soldados_Grupo(Soldados *&Soldado, int Daño)
{
    int Vida_Actual = Soldado->Get_Vida();
    int Nueva_Vida = Vida_Actual - Daño;
    Soldado->Set_Vida(Nueva_Vida);

    if (Nueva_Vida <= 0){
        Secuencia_Animaciones(Soldado->get_Objeto_En_La_Pantalla(), 3, Soldado->get_Secuencia_Muerte(), 300);
        Soldado->Set_Vivo(false);
    }
}

void Nivel1::Colisiones_SoldadosFranceses()
{
    for (size_t i = 1; i < Soldados_Franceses_EnEscena.size(); ++i) {
        Soldados *soldadoFrances = &Soldados_Franceses_EnEscena[i];
        if (soldadoFrances->Get_Vivo()){
            QGraphicsPixmapItem* Soldado = soldadoFrances->get_Objeto_En_La_Pantalla();
            const auto& itemsColisionados = Soldado->collidingItems();
            if (!itemsColisionados.isEmpty()) {
                for (auto* item : itemsColisionados) {
                    auto* Imagen_Colision = dynamic_cast<QGraphicsPixmapItem*>(item);
                    if (Imagen_Colision) {
                        const QString& tipoObjeto = Imagen_Colision->data(Qt::UserRole).toString();
                        if (tipoObjeto == "Explosion" || tipoObjeto == "Gas_Mostaza") {
                            Muerte_Soldados_Grupo(soldadoFrances, 100);
                            Colisiones_Aliados->stop();
                            QTimer::singleShot(500, this, [this]() {
                                Colisiones_Aliados->start(100);
                            });
                            break;
                        }
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
        item->setPos(-300, (i+1) * 50);
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
        QTimer* timer = new QTimer(this);
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
        double t = 0;
        connect(timer, &QTimer::timeout, this, [=]() mutable {
            Movimiento_Parabolico(item, timer, x0, y0, vx, vy, t, Limite_, Explosion, 2, 1.2);
            t += 0.05;
        });
        timer->start(5);
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
                Inicializar_Dinamicas_Enemigos();
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
        double t = 0;

        connect(timer, &QTimer::timeout, this, [=]() mutable {
            Movimiento_Parabolico(item, timer, x0, y0, vx, vy, t, Limite_, Explosion, 1, 0.7);
            t += 0.05;
        });
        timer->start(5);
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
        timer->stop();
        delete timer;
    }
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
    QTimer *Timer_ = new QTimer();
    QGraphicsPixmapItem *item;
    item = Bala.Get_Objeto();
    item->setScale(0.1);
    item->setPos(Pierre_De_Gaulle->get_Objeto_En_La_Pantalla()->x()-20, Pierre_De_Gaulle->get_Objeto_En_La_Pantalla()->y()+20);
    item->setData(Qt::UserRole, "Bala");
    Nivel->addItem(item);
    double vx = -Bala.Velocidad_X();
    double x0 = item->x();
    double t = 0;

    connect(Timer_, &QTimer::timeout, this, [=]() mutable {
        Movimiento_Rectilineo_Disparos(item, Timer_, vx, x0, t);
        t += 0.005;
    });
    Timer_->start(5);
}

void Nivel1::Disparos_Enemigos()
{
    Soldados *Actual;
    for (int i = 0; i < Cantidad_Soldados_Alemanes; i++){
        Actual = &Soldados_Alemanes_EnEscena[i];
        if (Actual->Get_Vivo()){
            if(Probabilidadi_Para_Disparos_Enemigos()){
                Objetos Bala(Tipo::Balas);
                QTimer *Timer_Disparo = new QTimer();
                QGraphicsPixmapItem *item;
                item = Bala.Get_Objeto();
                item->setScale(0.1);
                item->setPos(Soldados_Alemanes_EnEscena[i].get_Objeto_En_La_Pantalla()->x()+40, Soldados_Alemanes_EnEscena[i].get_Objeto_En_La_Pantalla()->y() +20);
                item->setData(Qt::UserRole, "Bala");
                Nivel->addItem(item);
                double vx = Bala.Velocidad_X();
                double x0 = item->x();
                double t = 0;
                connect(Timer_Disparo, &QTimer::timeout, this, [=]() mutable {
                    Movimiento_Rectilineo_Disparos(item, Timer_Disparo, vx, x0, t);
                    t += 0.005;
                });
                Timer_Disparo->start(1);
            }
        }
    }
}

void Nivel1::Avance_Enemigos()
{
    int Avance;
    Soldados *Actual;
    for (int i = 0; i < Cantidad_Soldados_Alemanes; i++){
        Actual = &Soldados_Alemanes_EnEscena[i];
        if (Actual->Get_Vivo()){
            item = Actual->get_Objeto_En_La_Pantalla();
            Avance = Probabilidadi_Para_Disparos_Enemigos();
            item->setPos(item->x()+Avance*1.5,item->y());
        }
    }
}

void Nivel1::Inicializar_Dinamicas_Enemigos()
{
    DisparosEnemigos = new QTimer();
    Movimiento_Enemigos = new QTimer();
    connect(DisparosEnemigos, &QTimer::timeout, this, &Nivel1::Disparos_Enemigos);
    connect(Movimiento_Enemigos, &QTimer::timeout, this, &Nivel1::Avance_Enemigos);
    DisparosEnemigos->start(1000);
    Movimiento_Enemigos->start(100);
}

bool Nivel1::Probabilidadi_Para_Disparos_Enemigos()
{
    double probabilityTrue = 0.5;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    if (dis(gen) > probabilityTrue) {
        return true;
    } else {
        return false;
    }
}

void Nivel1::Colisiones_SoldadosAlemanes()
{
    for (size_t i = 0; i < Soldados_Alemanes_EnEscena.size(); ++i) {
        Soldados *Aleman = &Soldados_Alemanes_EnEscena[i];
        if (Aleman->Get_Vivo()){
            QGraphicsPixmapItem* Soldado = Aleman->get_Objeto_En_La_Pantalla();
            const auto& itemsColisionados = Soldado->collidingItems();
            if (!itemsColisionados.isEmpty()) {
                for (auto* item : itemsColisionados) {
                    auto* Imagen_Colision = dynamic_cast<QGraphicsPixmapItem*>(item);
                    if (Imagen_Colision) {
                        const QString& tipoObjeto = Imagen_Colision->data(Qt::UserRole).toString();
                        if (tipoObjeto == "Bala") {
                            Muerte_Soldados_Grupo(Aleman, 100);
                            Colisiones_Enemigos->stop();
                            QTimer::singleShot(500, this, [this]() {
                                Colisiones_Enemigos->start(100);
                            });
                            break;
                        }
                    }
                }
            }
        }
    }
}

void Nivel1::Movimiento_Rectilineo_Disparos(QGraphicsPixmapItem *Objeto, QTimer *timer, double v0, double x0, double t)
{
    double newX = x0 + v0 * t;
    Objeto->setPos(newX, Objeto->y());
    if (newX > Nivel->width() || newX < 0) {
        timer->stop();
        Nivel->removeItem(Objeto);
        delete Objeto;
        timer->deleteLater();
    }
}

void Nivel1::Inicializar_Ejecucion()
{
    Ejecucion_Nivel = new QTimer();
    connect(Ejecucion_Nivel, &QTimer::timeout, this, &Nivel1::Terminar_Nivel);
    Ejecucion_Nivel->start(3000);
}

void Nivel1::Terminar_Nivel()
{
    int Enemigos_Muertos = 0;
    for (int i = 0; i < Cantidad_Soldados_Alemanes; i++){
        if (!Soldados_Alemanes_EnEscena[i].Get_Vivo()){
            Enemigos_Muertos++;
        }
        if(Soldados_Alemanes_EnEscena[i].get_Objeto_En_La_Pantalla()->x() >= LIMITE_IZQUIERDO || Pierre_De_Gaulle->Get_Vivo() == false){
            Termino_Nivel = true;
        }
    }
    if (Enemigos_Muertos == Cantidad_Soldados_Alemanes){
        Ganar = true;
        Termino_Nivel = true;
    }
}
