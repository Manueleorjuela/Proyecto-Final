#ifndef JUGADOR_H
#define JUGADOR_H
#include <string.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <QDebug>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

class jugador
{
private:
    string Fecha;
    string Informacion_Guardada;
    bool Estado_Primer_Nivel;
    bool Estado_Segundo_Nivel;
    int Tiempo_Inicial;
    int Tiempo_Final;

    //Para los metodos
    string Cargar_Informacion_Guardada(string Nombre_Archivo);
    void Asignar_Fecha();
    unsigned long long Tamano_Archivo(string Nombre_Archivo);
    string Calculo_Tiempo();
    string Determinar_Estado(bool Estado);
    void Guardar_Informacion();

public:

    jugador();

    string Mostrar_Mejor_Marca();
    void Almacenar_NuevaMarca();

    void Asignar_Tiempo(bool Case);
    string Mejor_Tiempo_Registrado();

    void set_Estado_Nivel1(bool Estado);
    void set_Estado_Nivel2(bool Estado);
};

#endif // JUGADOR_H
