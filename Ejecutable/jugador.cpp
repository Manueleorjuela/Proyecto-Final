#include "jugador.h"


string jugador::Cargar_Informacion_Guardada(string Nombre_Archivo)
{
    fstream file;
    string Contenido;
    file.open(Nombre_Archivo, ios_base::in | ios_base::ate | ios_base::binary );
    file.seekg(0);
    unsigned long long Tamano = Tamano_Archivo(Nombre_Archivo);

    for (unsigned long long i=0; i< Tamano ;i++){
        Contenido += file.get();
    }
    file.close();
    return Contenido;
}

unsigned long long jugador:: Tamano_Archivo(string NombreArchivo)
{
    fstream Archivo;
    unsigned long long Tamano;
    Archivo.open(NombreArchivo, ios_base::in | ios_base::ate | ios_base::binary );
    Tamano = Archivo.tellg();
    Archivo.close();
    return Tamano;
}

string jugador::Calculo_Tiempo()
{
    string Tiempo = to_string(Tiempo_Final - Tiempo_Inicial);
    return Tiempo;
}

string jugador::Determinar_Estado(bool Estado)
{
    string Nivel;
    if (Estado) Nivel = "Completado";
    else Nivel = "Incompleto";
    return Nivel;
}

void jugador::Almacenar_NuevaMarca()
{
    Informacion_Guardada = Cargar_Informacion_Guardada("Registros.txt");
    Informacion_Guardada+="\n\n";
    Informacion_Guardada += "Fecha: " + Fecha +"\n";
    Informacion_Guardada += "Primer nivel: " + Determinar_Estado(Estado_Primer_Nivel)+"\n";;
    Informacion_Guardada += "Segundo nivel: " + Determinar_Estado(Estado_Segundo_Nivel)+"\n";
    Informacion_Guardada += "Tiempo: " + Calculo_Tiempo() +" minutos";
    Guardar_Informacion();
}

void jugador::Asignar_Fecha()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    tm now_tm = *std::localtime(&now_time_t);
    std::stringstream ss;
    ss << std::put_time(&now_tm, "%d/%m/%Y");
    Fecha = ss.str();
}

jugador::jugador()
{
    Asignar_Fecha();
}

void jugador::Guardar_Informacion()
{
    fstream Archivo;
    Archivo.open("Registros.txt", ios_base::out | ios_base::binary);
    Archivo.write(Informacion_Guardada.c_str(), Informacion_Guardada.size());
    Archivo.close();
}

void jugador::Asignar_Tiempo(bool Case)
{

    auto now = chrono::system_clock::now();
    time_t now_time_t = chrono::system_clock::to_time_t(now);
    tm now_tm = *localtime(&now_time_t);
    int minutos = now_tm.tm_min;
    if (Case == 1){
        Tiempo_Inicial = minutos;
    }else if (Case == 0){
        Tiempo_Final = minutos;
    }

}

string jugador::Mejor_Tiempo_Registrado()
{
    string Contenido = Cargar_Informacion_Guardada("Registros.txt");
    istringstream stream(Contenido);
    string linea;
    vector<string> lineas;
    while (getline(stream, linea)) {
        lineas.push_back(linea);
    }

    int Numero_Menor = numeric_limits<int>::max();
    int Numero_Actual = 0;

    for (int i = 0; i < int(lineas.size()); i++){
        string Palabra;
        for(int j = 0; j < 6; j++){
            Palabra += lineas[i][j];
        }
        if (Palabra == "Tiempo"){
            string Num(1, lineas[i][8]);
            Numero_Actual = stoi(Num);
        }
        if(Numero_Actual < Numero_Menor){
            Numero_Menor = Numero_Actual;
        }
    }
    string Menor = to_string(Numero_Menor);
    return Menor;
}

void jugador::set_Estado_Nivel1(bool Estado)
{
    Estado_Primer_Nivel = Estado;
}

void jugador::set_Estado_Nivel2(bool Estado)
{
    Estado_Segundo_Nivel = Estado;
}
