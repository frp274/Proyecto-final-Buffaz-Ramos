#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <functional> //chequear libreria
#include <filesystem> //Libreria para poder leer el archivo csv
#include "Pila/Pila.h"
#include <chrono> //Para medir el tiempo de ejecucion de tu programa

using namespace std::chrono; // para medir el tiempo de ejecucion

int long long ifs = 0;
using namespace std;

struct Venta
{
    int id;
    string fecha;
    string pais;
    string ciudad;
    string cliente;
    string producto;
    string categoria;
    int cantidad;
    int precio_unitario;
    int monto_total;
    string medio_envio;
    string estado_envio;
};

vector<Venta> leerArchivoCSV(const string &nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    vector<Venta> ventas;
    string linea;

    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo!" << endl;
        return ventas;
    }
    ifs++;

    getline(archivo, linea); // Leer cabecera
    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        Venta venta;
        string dato;
        ifs++;
        getline(ss, dato, ',');
        venta.id = stoi(dato);
        getline(ss, venta.fecha, ',');
        getline(ss, venta.pais, ',');
        getline(ss, venta.ciudad, ',');
        getline(ss, venta.cliente, ',');
        getline(ss, venta.producto, ',');
        getline(ss, venta.categoria, ',');
        getline(ss, dato, ',');
        venta.cantidad = stoi(dato);
        getline(ss, dato, ',');
        venta.precio_unitario = stoi(dato); // Convertir a entero
        getline(ss, dato, ',');
        venta.monto_total = stoi(dato); // Convertir a entero
        getline(ss, venta.medio_envio, ',');
        getline(ss, venta.estado_envio, ',');

        ventas.push_back(venta);
    }

    archivo.close();
    return ventas;
}

Pila<string> soloPaises(const vector<Venta> ventas)
{
    bool primero = false;
    Pila<string> PilaDePaises;
    Pila<string> pilaAux;

    for (size_t i = 0; i < ventas.size(); i++)
    {
        ifs++;
        bool repetido = false;

        string datoVentas = ventas[i].pais;
        if (!primero)
        {
            PilaDePaises.push(datoVentas);
            primero = true;
        }
        else
        {
            ifs++;
            while (!PilaDePaises.esVacia())
            {
                ifs++;
                string datoPila = PilaDePaises.pop();
                pilaAux.push(datoPila);
                if (datoVentas == datoPila)
                {
                    repetido = true;
                    break;
                }
            }
            ifs++;
            if (!repetido)
            {
                pilaAux.push(datoVentas);
            }
            while (!pilaAux.esVacia())
            {
                ifs++;
                PilaDePaises.push(pilaAux.pop());
            }
        }
    }
    return PilaDePaises;
}

// void imprimirVentas(const vector<Venta> &ventas)
// {
//     for (const auto &venta : ventas)
//     {
//         cout << venta.id << " | " << venta.fecha << " | " << venta.pais
//              << " | " << venta.ciudad << " | " << venta.cliente << " | "
//              << venta.producto << " | " << venta.categoria << " | " << venta.cantidad << " | " << venta.precio_unitario << " | " << venta.monto_total << " | " << venta.medio_envio << " | " << venta.estado_envio << endl;
//     }
// }

void top5ciudades(const vector<Venta> &ventas)
{
    using namespace std::chrono;
    auto inicio = high_resolution_clock::now();
    int ifs_local = 0;

    struct pais5ciudades
    {
        string pais;
        string ciudad1;
        float monto1;
        string ciudad2;
        float monto2;
        string ciudad3;
        float monto3;
        string ciudad4;
        float monto4;
        string ciudad5;
        float monto5;
    };

    vector<pais5ciudades> vectorTop5;

    // Recorrer ventas y acumular monto por ciudad y pais
    for (size_t i = 0; i < ventas.size(); i++)
    {
        ifs++;
        ifs_local++;
        bool paisExiste = false;

        for (size_t j = 0; j < vectorTop5.size(); j++)
        {
            ifs++;
            ifs_local++;
            if (ventas[i].pais == vectorTop5[j].pais)
            {
                ifs++;
                ifs_local++;
                paisExiste = true;
                bool ciudadEncontrada = false;

                // Buscar si la ciudad ya esta cargada

                if (ventas[i].ciudad == vectorTop5[j].ciudad1)
                {
                    ifs++;
                    ifs_local++;
                    vectorTop5[j].monto1 += ventas[i].monto_total;
                    ciudadEncontrada = true;
                }
                else if (ventas[i].ciudad == vectorTop5[j].ciudad2)
                {
                    ifs++;
                    ifs_local++;
                    vectorTop5[j].monto2 += ventas[i].monto_total;
                    ciudadEncontrada = true;
                }
                else if (ventas[i].ciudad == vectorTop5[j].ciudad3)
                {
                    ifs++;
                    ifs_local++;
                    vectorTop5[j].monto3 += ventas[i].monto_total;
                    ciudadEncontrada = true;
                }
                else if (ventas[i].ciudad == vectorTop5[j].ciudad4)
                {
                    ifs++;
                    ifs_local++;
                    vectorTop5[j].monto4 += ventas[i].monto_total;
                    ciudadEncontrada = true;
                }
                else if (ventas[i].ciudad == vectorTop5[j].ciudad5)
                {
                    ifs++;
                    ifs_local++;
                    vectorTop5[j].monto5 += ventas[i].monto_total;
                    ciudadEncontrada = true;
                }

                // Si la ciudad no estaba en las 5, la agrego si hay espacio
                if (!ciudadEncontrada)
                {
                    ifs++;
                    ifs_local++;
                    if (vectorTop5[j].ciudad2.empty())
                    {
                        ifs++;
                        ifs_local++;
                        vectorTop5[j].ciudad2 = ventas[i].ciudad;
                        vectorTop5[j].monto2 = ventas[i].monto_total;
                    }
                    else if (vectorTop5[j].ciudad3.empty())
                    {
                        ifs++;
                        ifs_local++;
                        vectorTop5[j].ciudad3 = ventas[i].ciudad;
                        vectorTop5[j].monto3 = ventas[i].monto_total;
                    }
                    else if (vectorTop5[j].ciudad4.empty())
                    {
                        ifs++;
                        ifs_local++;
                        vectorTop5[j].ciudad4 = ventas[i].ciudad;
                        vectorTop5[j].monto4 = ventas[i].monto_total;
                    }
                    else if (vectorTop5[j].ciudad5.empty())
                    {
                        ifs++;
                        ifs_local++;
                        vectorTop5[j].ciudad5 = ventas[i].ciudad;
                        vectorTop5[j].monto5 = ventas[i].monto_total;
                    }
                    // Si ya hay 5 ciudades, ignorar (no entra en el top)
                }

                break; // ya trabaje con este pais
            }
        }

        // Si el pais no estaba en el vector, lo agrego con la primera ciudad
        if (!paisExiste)
        {
            ifs++;
            ifs_local++;
            pais5ciudades nuevo;
            nuevo.pais = ventas[i].pais;
            nuevo.ciudad1 = ventas[i].ciudad;
            nuevo.monto1 = ventas[i].monto_total;
            nuevo.ciudad2 = "";
            nuevo.ciudad3 = "";
            nuevo.ciudad4 = "";
            nuevo.ciudad5 = "";
            nuevo.monto2 = 0;
            nuevo.monto3 = 0;
            nuevo.monto4 = 0;
            nuevo.monto5 = 0;
            vectorTop5.push_back(nuevo);
        }
    }

    // Ordenar las ciudades dentro de cada pais segun su monto (metodo simple)
    for (size_t i = 0; i < vectorTop5.size(); i++)
    {
        string ciudades[5] = {
            vectorTop5[i].ciudad1,
            vectorTop5[i].ciudad2,
            vectorTop5[i].ciudad3,
            vectorTop5[i].ciudad4,
            vectorTop5[i].ciudad5};

        float montos[5] = {
            vectorTop5[i].monto1,
            vectorTop5[i].monto2,
            vectorTop5[i].monto3,
            vectorTop5[i].monto4,
            vectorTop5[i].monto5};

        // Ordenar las 5 ciudades manualmente (burbuja)
        for (int a = 0; a < 5; a++)
        {
            for (int b = 0; b < 4; b++)
            {
                ifs++;
                ifs_local++;
                if (montos[b] < montos[b + 1])
                {
                    ifs++;
                    ifs_local++;
                    float tempMonto = montos[b];
                    string tempCiudad = ciudades[b];
                    montos[b] = montos[b + 1];
                    ciudades[b] = ciudades[b + 1];
                    montos[b + 1] = tempMonto;
                    ciudades[b + 1] = tempCiudad;
                }
            }
        }

        // Actualizar el struct con las ciudades ordenadas
        vectorTop5[i].ciudad1 = ciudades[0];
        vectorTop5[i].monto1 = montos[0];
        vectorTop5[i].ciudad2 = ciudades[1];
        vectorTop5[i].monto2 = montos[1];
        vectorTop5[i].ciudad3 = ciudades[2];
        vectorTop5[i].monto3 = montos[2];
        vectorTop5[i].ciudad4 = ciudades[3];
        vectorTop5[i].monto4 = montos[3];
        vectorTop5[i].ciudad5 = ciudades[4];
        vectorTop5[i].monto5 = montos[4];
    }

    // Mostrar el top 5 por pais
    cout << "TOP 5 CIUDADES CON MAYOR MONTO POR PAIS:" << endl;
    for (const auto &p : vectorTop5)
    {
        cout << "- - -" << p.pais << "- - -" << endl;
        if (!p.ciudad1.empty())
        {
            ifs++;
            ifs_local++;
            cout << p.ciudad1 << " ($" << p.monto1 << ")" << endl;
        }
        if (!p.ciudad2.empty())
        {
            ifs++;
            ifs_local++;
            cout << p.ciudad2 << " ($" << p.monto2 << ")" << endl;
        }
        if (!p.ciudad3.empty())
        {
            ifs++;
            ifs_local++;
            cout << p.ciudad3 << " ($" << p.monto3 << ")" << endl;
        }
        if (!p.ciudad4.empty())
        {
            ifs++;
            ifs_local++;
            cout << p.ciudad4 << " ($" << p.monto4 << ")" << endl;
        }
        if (!p.ciudad5.empty())
        {
            ifs++;
            ifs_local++;
            cout << p.ciudad5 << " ($" << p.monto5 << ")" << endl;
        }
        cout << endl;
    }

    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;
    cout << endl;
    cout << "Tiempo de ejecucion: " << duracion.count() << " segundos" << endl;
    cout << endl;
    cout << "IFs ejecutados en esta funcion: " << ifs_local << endl;
    cout << endl;
}

// Funcion: Monto total vendido por producto, discriminado por pais, acumula los montos vendidos por producto y pais

void montoTotalPorProductoYPais(vector<Venta> &ventas, Pila<string> &pilaPaises)
{
    using namespace std::chrono;
    auto inicio = high_resolution_clock::now();
    int ifs_local = 0;

    // Estructura auxiliar para guardar producto, pais y monto total acumulado
    struct ProductoPaisMonto
    {
        string producto;
        string pais;
        float monto_total;
    };
    vector<ProductoPaisMonto> resumen;
    // Recorremos cada venta del archivo
    for (size_t i = 0; i < ventas.size(); i++)
    {
        string prod = ventas[i].producto;
        string pais = ventas[i].pais;
        float monto = ventas[i].monto_total;

        bool encontrado = false;

        // Buscamos si ya existe en el vector resumen
        for (size_t j = 0; j < resumen.size(); j++)
        {
            ifs++; // if de busqueda
            ifs_local++;
            if (resumen[j].producto == prod && resumen[j].pais == pais)
            {
                ifs++;
                ifs_local++;
                resumen[j].monto_total += monto; // acumulamos monto
                encontrado = true;
                break;
            }
        }

        ifs++; // if de control
        ifs_local++;
        if (!encontrado)
        {
            ifs++;
            ifs_local++;
            // Si no estaba, lo agregamos
            ProductoPaisMonto nuevo;
            nuevo.producto = prod;
            nuevo.pais = pais;
            nuevo.monto_total = monto;
            resumen.push_back(nuevo);
        }
    }
    Pila<string> pilaPaisesAux;

    // Mostramos el resultado
    cout << "\n- - - MONTO TOTAL POR PRODUCTO Y PAIS - - -" << endl;
    while (!pilaPaises.esVacia())
    {
        ifs++;

        string paisActual = pilaPaises.pop();
        pilaPaisesAux.push(paisActual);
        cout << "+--------------------------------------------+" << endl;
        cout << "             Pais: " << paisActual << endl;
        cout << "+--------------------------------------------+" << endl;
        for (size_t i = 0; i < resumen.size(); i++)
        {
            ifs++;
            if (paisActual == resumen[i].pais)
            {
                ifs++;
                ifs_local++;
                cout << "Producto: " << resumen[i].producto << " | Monto Total: $" << resumen[i].monto_total << endl;
            }
        }
        cout << "+--------------------------------------------+" << endl;
        cout << endl;
    }
    while (!pilaPaisesAux.esVacia())
    {
        string paispila = pilaPaisesAux.pop();
        ifs++;
        pilaPaises.push(paispila);
    }

    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;
    cout << endl;
    cout << "Tiempo de ejecucion: " << duracion.count() << " segundos" << endl;
    cout << endl;
    cout << "IFs ejecutados en esta funcion: " << ifs_local << endl;
    cout << endl;
}

void PromVentasCatPais(const vector<Venta> &ventas)
{
    using namespace std::chrono;
    auto inicio = high_resolution_clock::now();
    int ifs_local = 0;

    struct PaisCatNum
    {
        string pais;
        string categoria;
        int long numVentas = 0;
    };
    struct CantVentPais
    {
        string paisCantidad;
        size_t NumVentasDePais = 0;
    };

    vector<PaisCatNum> vectorCategoria;
    vector<CantVentPais> vectorPais;

    for (size_t i = 0; i < ventas.size(); i++)
    {
        bool encontradaCat = false;
        bool encontradoPais = false;
        string paisV = ventas[i].pais;
        string catV = ventas[i].categoria;

        for (size_t j = 0; j < vectorCategoria.size(); j++)
        {
            if (vectorCategoria[j].pais == paisV && vectorCategoria[j].categoria == catV)
            {
                ifs++;
                ifs_local++;
                vectorCategoria[j].numVentas += 1;
                encontradaCat = true;
            }
        }

        for (int k = 0; k < vectorPais.size(); k++)
        {
            if (vectorPais[k].paisCantidad == paisV)
            {
                ifs++;
                ifs_local++;
                vectorPais[k].NumVentasDePais += 1;
                encontradoPais = true;
            }
        }

        ifs++; // if de control
        if (!encontradaCat)
        {
            ifs++;
            ifs_local++;
            // Si no estaba, lo agregamos
            PaisCatNum nuevo;
            nuevo.pais = paisV;
            nuevo.categoria = catV;
            nuevo.numVentas = 1;
            vectorCategoria.push_back(nuevo);
        }
        if (!encontradoPais)
        {
            ifs++;
            ifs_local++;
            CantVentPais nuevoPais;
            nuevoPais.paisCantidad = paisV;
            nuevoPais.NumVentasDePais = 1;
            vectorPais.push_back(nuevoPais);
        }
    }

    cout << "NUMERO, PROMEDIO Y PORCENTAJE DE VENTAS POR CATEGORIA (del total de ventas) DE CADA PAIS:" << endl;

    for (const auto &CantVentPais : vectorPais)
    {
        string paisVec = CantVentPais.paisCantidad;
        double numVentasPais = CantVentPais.NumVentasDePais;
        cout << "+----------------------------------------------------------------------------------------------------------------------------+" << endl;
        cout << "Pais: " << paisVec << " // " << "Cantidad de ventas totales (100%): " << numVentasPais << endl;
        cout << endl;
        for (size_t i = 0; i < vectorCategoria.size(); i++)
        {
            if (vectorCategoria[i].pais == paisVec)
            {
                ifs++;
                ifs_local++;
                float numVentasCat = vectorCategoria[i].numVentas;
                float promedio = (numVentasCat / numVentasPais);
                float porcentaje = promedio * 100;
                cout << "Categoria: " << vectorCategoria[i].categoria << " // " << "Num. ventas: " << numVentasCat << " // " << "promedio del total: " << promedio << " // " << "Porcentaje de la categoria: " << porcentaje << "%" << endl;
            }
        }
    }

    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;
    cout << endl;
    cout << "Tiempo de ejecucion: " << duracion.count() << " segundos" << endl;
    cout << endl;
    cout << "IFs ejecutados en esta funcion: " << ifs_local << endl;
    cout << endl;
}

void MedioEnvioMasUsadoPorPaisYCategoria(const vector<Venta> &ventas, Pila<string> &pilaPaises)
{
    using namespace std::chrono;
    auto inicio = high_resolution_clock::now();
    int ifs_local = 0;

    Pila<string> pilaAux;

    struct MedioEnvioContador
    {
        string clave; // puede ser pais o categoria
        string medio;
        int cantidad = 0;
    };

    vector<MedioEnvioContador> VecPaisMedio;
    vector<MedioEnvioContador> VecCategoriaMedio;

    // Recorremos las ventas para llenar los vectores
    for (size_t i = 0; i < ventas.size(); i++)
    {
        string pais = ventas[i].pais;
        string categoria = ventas[i].categoria;
        string medio = ventas[i].medio_envio;

        bool encontradoPais = false;
        bool encontradoCat = false;

        // Buscar en VecPaisMedio si ya existe esa combinacion pais-medio
        for (int j = 0; j < VecPaisMedio.size(); j++)
        {
            if (VecPaisMedio[j].clave == pais && VecPaisMedio[j].medio == medio)
            {
                ifs++;
                ifs_local++;
                VecPaisMedio[j].cantidad++;
                encontradoPais = true;
                ifs++;
                break;
            }
            ifs++;
            ifs_local++;
        }

        if (!encontradoPais)
        {
            ifs++;
            ifs_local++;
            MedioEnvioContador nuevo;
            nuevo.clave = pais;
            nuevo.medio = medio;
            nuevo.cantidad = 1;
            VecPaisMedio.push_back(nuevo);
        }

        // Buscar en VecCategoriaMedio si ya existe esa combinacion categoria-medio
        for (int j = 0; j < VecCategoriaMedio.size(); j++)
        {
            if (VecCategoriaMedio[j].clave == categoria && VecCategoriaMedio[j].medio == medio)
            {
                ifs++;
                ifs_local++;
                VecCategoriaMedio[j].cantidad++;
                encontradoCat = true;
                ifs++;
                break;
            }
            ifs++;
            ifs_local++;
        }

        if (!encontradoCat)
        {
            ifs++;
            ifs_local++;
            MedioEnvioContador nuevo;
            nuevo.clave = categoria;
            nuevo.medio = medio;
            nuevo.cantidad = 1;
            VecCategoriaMedio.push_back(nuevo);
        }
    }

    cout << "---------- MEDIO DE ENVIO MAS UTILIZADO POR PAIS ----------" << endl;

    // Procesamos por pais
    while (!pilaPaises.esVacia())
    {
        string paisActual = pilaPaises.pop();
        pilaAux.push(paisActual);

        string medioMax = "";
        int maxCantidad = 0;

        for (int i = 0; i < VecPaisMedio.size(); i++)
        {
            if (VecPaisMedio[i].clave == paisActual)
            {
                ifs++;
                ifs_local++;
                if (VecPaisMedio[i].cantidad > maxCantidad)
                {
                    ifs++;
                    ifs_local++;
                    maxCantidad = VecPaisMedio[i].cantidad;
                    medioMax = VecPaisMedio[i].medio;
                }
                ifs++;
                ifs_local++;
            }
        }

        cout << "Pais: " << paisActual << " // Medio mas usado: " << medioMax << " con " << maxCantidad << " ventas" << endl;
    }

    while (!pilaAux.esVacia())
    {
        ifs++;
        pilaPaises.push(pilaAux.pop());
    }

    cout << endl;
    cout << "---------- MEDIO DE ENVIO MAS UTILIZADO POR CATEGORIA ----------" << endl;

    // Usamos vector auxiliar para ordenar por categoria y obtener el mas usado
    vector<string> categorias;

    // Primero obtenemos todas las categorias unicas
    for (int i = 0; i < VecCategoriaMedio.size(); i++)
    {
        bool existe = false;
        for (int j = 0; j < categorias.size(); j++)
        {
            if (categorias[j] == VecCategoriaMedio[i].clave)
            {
                ifs++;
                ifs_local++;
                existe = true;
                ifs++;
                break;
            }
            ifs++;
            ifs_local++;
        }
        if (!existe)
        {
            ifs++;
            ifs_local++;
            categorias.push_back(VecCategoriaMedio[i].clave);
        }
    }

    // Para cada categoria buscamos el medio mas usado
    for (int i = 0; i < categorias.size(); i++)
    {
        string cat = categorias[i];
        string medioMax = "";
        int maxCantidad = 0;

        for (int j = 0; j < VecCategoriaMedio.size(); j++)
        {
            if (VecCategoriaMedio[j].clave == cat)
            {
                ifs++;
                ifs_local++;
                if (VecCategoriaMedio[j].cantidad > maxCantidad)
                {
                    ifs++;
                    ifs_local++;
                    maxCantidad = VecCategoriaMedio[j].cantidad;
                    medioMax = VecCategoriaMedio[j].medio;
                }
            }
        }

        cout << "Categoria: " << cat << " // Medio mas usado: " << medioMax << " con " << maxCantidad << " ventas" << endl;
    }

    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;
    cout << endl;
    cout << "Tiempo de ejecucion: " << duracion.count() << " segundos" << endl;
    cout << endl;
    cout << "IFs ejecutados en esta funcion: " << ifs_local << endl;
    cout << endl;
}

void DiaConMayorMontoVentas(const vector<Venta> &ventas)
{
    using namespace std::chrono;
    auto inicio = high_resolution_clock::now();
    int ifs_local = 0;

    struct FechaMonto
    {
        string fecha;
        float montoAcumulado = 0;
    };

    vector<FechaMonto> fechas;
    int ifs = 0; // contador de ifs

    // Recorrido de todas las ventas
    for (size_t i = 0; i < ventas.size(); i++)
    {
        string fechaActual = ventas[i].fecha;
        float monto = ventas[i].monto_total;
        bool encontrada = false;

        // Verificamos si ya existe esa fecha en el vector
        for (size_t j = 0; j < fechas.size(); j++)
        {
            ifs++;
            ifs_local++;
            if (fechas[j].fecha == fechaActual)
            {
                ifs++;
                ifs_local++;
                fechas[j].montoAcumulado += monto;
                encontrada = true;
                break;
            }
        }

        // Si no estaba, la agregamos
        ifs++;
        ifs_local++;
        if (!encontrada)
        {
            ifs++;
            ifs_local++;
            FechaMonto nueva;
            nueva.fecha = fechaActual;
            nueva.montoAcumulado = monto;
            fechas.push_back(nueva);
        }
    }

    // Ordenamos el vector de fechas por monto usando Shell Sort (descendente)
    for (int gap = fechas.size() / 2; gap > 0; gap /= 2)
    {
        for (size_t i = gap; i < fechas.size(); i++)
        {
            FechaMonto temp = fechas[i];
            size_t j = i;

            // Insertamos temp en su posicion correcta en el subarray actual
            while (j >= gap && fechas[j - gap].montoAcumulado < temp.montoAcumulado)
            {
                ifs++; // solo un if por comparacion real
                fechas[j] = fechas[j - gap];
                j -= gap;
            }

            fechas[j] = temp;
        }
    }

    // Mostramos el dia con mayor monto de ventas
    if (!fechas.empty())
    {
        ifs++;
        ifs_local++;
        cout << "\n- - - DIA CON MAYOR MONTO TOTAL DE VENTAS - - -\n";
        cout << "Fecha: " << fechas[0].fecha << " // Monto total vendido: $" << fechas[0].montoAcumulado << endl;
    }

    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;
    cout << endl;
    cout << "Tiempo de ejecucion: " << duracion.count() << " segundos" << endl;
    cout << endl;
    cout << "IFs ejecutados en esta funcion: " << ifs_local << endl;
    cout << endl;
}

void EstadoEnvioMasFrecuentePorPais(const vector<Venta> &ventas, Pila<string> &pilaPaises)
{
    using namespace std::chrono;
    auto inicio = high_resolution_clock::now();
    int ifs_local = 0;

    // Estructura para almacenar el estado y cuantas veces se repite en un pais
    struct EstadoPorPais
    {
        string estado;
        int cantidad = 0;
    };
    Pila<string> pilaAux;

    cout << "- - - - - ESTADO DE ENVIO MAS FRECUENTE POR PAIS: - - - - -" << endl;

    // Recorrer todos los paises de la pila
    while (!pilaPaises.esVacia())
    {
        string paisActual = pilaPaises.pop(); // vamos consumiendo la pila
        pilaAux.push(paisActual);
        vector<EstadoPorPais> estadosPais; // almacena estados por pais

        // Recorremos todas las ventas buscando coincidencias con el pais actual
        for (size_t i = 0; i < ventas.size(); i++)
        {
            // Verificamos si la venta corresponde al pais actual
            ifs++;
            ifs_local++;
            if (ventas[i].pais == paisActual)
            {
                string estado = ventas[i].estado_envio;
                bool encontrado = false;

                // Buscamos si ya se ha contado este estado en este pais
                for (size_t j = 0; j < estadosPais.size(); j++)
                {
                    ifs++;
                    ifs_local++;
                    if (estadosPais[j].estado == estado)
                    {
                        ifs++;
                        ifs_local++;
                        estadosPais[j].cantidad++;
                        encontrado = true;
                        break; // lo encontramos, no hace falta seguir buscando
                    }
                }

                // Si el estado no estaba registrado, lo agregamos
                ifs++;
                ifs_local++;
                if (!encontrado)
                {
                    EstadoPorPais nuevo;
                    nuevo.estado = estado;
                    nuevo.cantidad = 1;
                    estadosPais.push_back(nuevo);
                }
            }
        }

        // Ahora determinamos el estado mas frecuente para ese pais
        string estadoMax = "";
        int cantMax = -1;
        for (size_t i = 0; i < estadosPais.size(); i++)
        {
            ifs++;
            ifs_local++;
            if (estadosPais[i].cantidad > cantMax)
            {
                ifs++;
                ifs_local++;
                estadoMax = estadosPais[i].estado;
                cantMax = estadosPais[i].cantidad;
            }
        }

        // Mostramos el resultado para el pais actual
        cout << "\nPais: " << paisActual << " => Estado de envio mas frecuente: " << estadoMax
             << " (Cantidad: " << cantMax << ")" << endl;
    }

    while (!pilaAux.esVacia())
    {
        string paispila = pilaAux.pop();
        pilaPaises.push(paispila);
    }

    // El contador ifs sigue acumulando de funciones anteriores

    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;
    cout << endl;
    cout << "Tiempo de ejecucion: " << duracion.count() << " segundos" << endl;
    cout << endl;
    cout << "IFs ejecutados en esta funcion: " << ifs_local << endl;
    cout << endl;
}

void productoMasYMenosVendido(const vector<Venta> &ventas)
{

    using namespace std::chrono;
    auto inicio = high_resolution_clock::now();
    int ifs_local = 0;

    struct ProductoCantidad
    {
        string nombre;
        int cantidadVendida = 0;
    };

    vector<ProductoCantidad> vectorProd;

    // Recorremos todas las ventas y acumulamos por nombre de producto
    for (size_t i = 0; i < ventas.size(); i++)
    {
        string nombreProd = ventas[i].producto;
        bool encontrado = false;

        for (size_t j = 0; j < vectorProd.size(); j++)
        {
            if (vectorProd[j].nombre == nombreProd)
            {
                vectorProd[j].cantidadVendida += ventas[i].cantidad;
                ifs++;
                ifs_local++; // if que verifica coincidencia de producto
                encontrado = true;
                break; // ya lo encontramos, no hace falta seguir
            }
        }

        ifs++;
        ifs_local++; // if para verificar si no estaba
        if (!encontrado)
        {
            ifs++;
            ifs_local++;
            ProductoCantidad nuevo;
            nuevo.nombre = nombreProd;
            nuevo.cantidadVendida = ventas[i].cantidad;
            vectorProd.push_back(nuevo);
        }
    }

    // Si no hay productos, salimos
    if (vectorProd.empty())
    {
        ifs++;
        ifs_local++;
        cout << "No hay productos en la base de datos." << endl;
        return;
    }

    // Buscamos el producto con mayor y menor cantidad vendida
    ProductoCantidad masVendido = vectorProd[0];
    ProductoCantidad menosVendido = vectorProd[0];

    for (size_t i = 1; i < vectorProd.size(); i++)
    {
        ifs++; // if para maximo
        ifs_local++;
        if (vectorProd[i].cantidadVendida > masVendido.cantidadVendida)
        {
            ifs++;
            ifs_local++;
            masVendido = vectorProd[i];
        }

        ifs++; // if para minimo
        ifs_local++;
        if (vectorProd[i].cantidadVendida < menosVendido.cantidadVendida)
        {
            ifs++;
            ifs_local++;
            menosVendido = vectorProd[i];
        }
    }

    cout << endl;
    cout << "- - - PRODUCTO MAS Y MENOS VENDIDO (por unidades) - - -" << endl;
    cout << "Producto MAS vendido: " << masVendido.nombre << " // Cantidad total: " << masVendido.cantidadVendida << endl;
    cout << "Producto MENOS vendido: " << menosVendido.nombre << " // Cantidad total: " << menosVendido.cantidadVendida << endl;
    cout << "------------------------------------------------------" << endl;

    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;
    cout << endl;
    cout << "Tiempo de ejecucion: " << duracion.count() << " segundos" << endl;
    cout << endl;
    cout << "IFs ejecutados en esta funcion: " << ifs_local << endl;
    cout << endl;
}

// ID_Venta,Fecha,Pais,Ciudad,Cliente,Producto,Categoria,Cantidad,Precio_Unitario,Monto_Total,Medio_Envio,Estado_Envio
// 1,29/12/2024,Venezuela,Caracas,Ana Perez,Escritorio,Muebles,4,66.74,266.96,Aereo,Cancelado
// 2,5/9/2024,Bolivia,Cochabamba,Pedro Sanchez,Teclado,Accesorios,1,1176.02,1176.02,Aereo,Entregado
// 3,26/10/2024,Argentina,Buenos Aires,Pedro Garcia,Auriculares,Accesorios,4,   1137.66,4550.64,Maritimo,En transito
// 4,4/3/2024,Argentina,Cordoba,Carlos Garcia,Silla ergonomica,Muebles,5,   438.93,2194.65,Maritimo,Cancelado
// 5,13/8/2024,Colombia,Bogota,Pedro Sanchez,Impresora,Oficina,1,   426.22,426.22,Maritimo,Pendiente
// 6,21/7/2024,Uruguay,Montevideo,Pedro Perez,Monitor,Electronica,1,   543.34,543.34,Maritimo,Pendiente

// Guardar el vector de ventas en el archivo CSV
void guardarVentasCSV(const string &nombreArchivo, const vector<Venta> &ventas)
{
    ofstream archivo(nombreArchivo);
    archivo << "ID_Venta,Fecha,Pais,Ciudad,Cliente,Producto,Categoria,Cantidad,Precio_Unitario,Monto_Total,Medio_Envio,Estado_Envio\n";
    for (const auto &v : ventas)
    {
        archivo << v.id << "," << v.fecha << "," << v.pais << "," << v.ciudad << "," << v.cliente << "," << v.producto << "," << v.categoria << "," << v.cantidad << "," << v.precio_unitario << "," << v.monto_total << "," << v.medio_envio << "," << v.estado_envio << "\n";
    }
    archivo.close();
}

// Agregar una venta
void agregarVenta(vector<Venta> &ventas, const string &nombreArchivo)
{
    // Buscar el mayor ID actual
    using namespace std::chrono;
    auto inicio = high_resolution_clock::now();
    int ifs_local = 0;

    int maxId = 0;
    for (size_t i = 0; i < ventas.size(); i++)
    {
        if (ventas[i].id > maxId)
        {
            ifs++;
            ifs_local++;
            maxId = ventas[i].id;
        }
    }

    Venta nueva;
    nueva.id = maxId + 1; // Asignar el siguiente ID disponible
    cout << "ID: " << nueva.id << endl;
    cout << endl;
    cout << "Fecha (ej: 5/6/2025): ";
    cin.ignore();
    getline(cin, nueva.fecha);
    cout << "Pais: ";
    getline(cin, nueva.pais);
    cout << "Ciudad: ";
    getline(cin, nueva.ciudad);
    cout << "Cliente: ";
    getline(cin, nueva.cliente);
    cout << "Producto: ";
    getline(cin, nueva.producto);
    cout << "Categoria: ";
    getline(cin, nueva.categoria);
    cout << "Cantidad: ";
    cin >> nueva.cantidad;
    cout << "Precio unitario: ";
    cin >> nueva.precio_unitario;
    cout << "Monto total: ";
    cin >> nueva.monto_total;
    cin.ignore();
    cout << "Medio de envio: ";
    getline(cin, nueva.medio_envio);
    cout << "Estado de envio: ";
    getline(cin, nueva.estado_envio);

    ventas.push_back(nueva); // Agrega todos los datos de la venta al ultimo id correspondiente
    guardarVentasCSV(nombreArchivo, ventas);
    cout << "Venta agregada correctamente.\n";

    auto fin = high_resolution_clock::now(); // Finaliza el reloj
    duration<double> duracion = fin - inicio;
    cout << endl;
    cout << "Tiempo de ejecucion: " << duracion.count() << " segundos" << endl;
    cout << endl;
    cout << "IFs ejecutados en esta funcion: " << ifs_local << endl;
    cout << "*" << endl;
}

// Eliminar una venta por pais o ciudad
void eliminarVenta(vector<Venta> &ventas, const string &nombreArchivo)
{

    using namespace std::chrono;
    auto inicio = high_resolution_clock::now(); // Comienza a contabilizar el tiempo del proceso
    int ifs_local = 0;

    string filtro;
    cout << "Ingrese el pais o ciudad para filtrar ventas a eliminar: ";
    cin.ignore();
    getline(cin, filtro);

    // Mostrar ventas filtradas
    vector<int> indices;
    for (size_t i = 0; i < ventas.size(); i++)
    {
        if (ventas[i].pais == filtro || ventas[i].ciudad == filtro)
        {
            ifs++;
            ifs_local++;
            cout << "ID: " << ventas[i].id << " | " << ventas[i].pais << " | " << ventas[i].ciudad << " | " << ventas[i].producto << endl;
            indices.push_back(i);
        }
    }
    if (indices.empty())
    {
        ifs++;
        ifs_local++;
        cout << "No se encontraron ventas con ese filtro.\n";
        return;
    }
    cout << "Ingrese el ID de la venta a eliminar: ";
    int idEliminar;
    cin >> idEliminar;

    // Buscar y eliminar segun el id que le proporcionemos
    bool eliminado = false;
    for (auto it = ventas.begin(); it != ventas.end(); ++it)
    {
        if (it->id == idEliminar)
        {
            ifs++;
            ifs_local++;
            ventas.erase(it);
            eliminado = true;
            break;
        }
    }
    if (eliminado)
    {
        ifs++;
        ifs_local++;
        guardarVentasCSV(nombreArchivo, ventas);
        cout << "Venta eliminada correctamente.\n";
    }
    else
    {
        ifs++;
        ifs_local++;
        cout << "No se encontro la venta con ese ID.\n";
    }

    auto fin = high_resolution_clock::now(); // Finaliza el tiempo de ejecucion del proceso
    duration<double> duracion = fin - inicio;
    cout << endl;
    cout << "Tiempo de ejecucion: " << duracion.count() << " segundos" << endl;
    cout << endl;
    cout << "IFs ejecutados en esta funcion: " << ifs_local << endl;
    cout << "*" << endl;
}

// Modificar una venta por ID
void modificarVenta(vector<Venta> &ventas, const string &nombreArchivo)
{
    using namespace std::chrono;
    auto inicio = high_resolution_clock::now(); // Inicia el reloj
    int ifs_local = 0;

    cout << "Ingrese el ID de la venta a modificar: ";
    int idMod;
    cin >> idMod;
    cin.ignore();
    bool encontrado = false;
    for (auto &v : ventas)
    { // Recorre el vector ventas en busca del id a modificar
        if (v.id == idMod)
        {
            ifs++;
            ifs_local++;
            encontrado = true;
            cout << "Modificando venta ID: " << v.id << endl;
            cout << "Campo actual (Fecha): " << v.fecha << ". Nuevo valor (ENTER para dejar igual): ";
            string input;
            getline(cin, input);
            if (!input.empty())
                v.fecha = input;
            cout << "Campo actual (Pais): " << v.pais << ". Nuevo valor: ";
            getline(cin, input);
            if (!input.empty())
                v.pais = input;
            cout << "Campo actual (Ciudad): " << v.ciudad << ". Nuevo valor: ";
            getline(cin, input);
            if (!input.empty())
                v.ciudad = input;
            cout << "Campo actual (Cliente): " << v.cliente << ". Nuevo valor: ";
            getline(cin, input);
            if (!input.empty())
                v.cliente = input;
            cout << "Campo actual (Producto): " << v.producto << ". Nuevo valor: ";
            getline(cin, input);
            if (!input.empty())
                v.producto = input;
            cout << "Campo actual (Categoria): " << v.categoria << ". Nuevo valor: ";
            getline(cin, input);
            if (!input.empty())
                v.categoria = input;
            cout << "Campo actual (Cantidad): " << v.cantidad << ". Nuevo valor: ";
            getline(cin, input);
            if (!input.empty())
                v.cantidad = stoi(input);
            cout << "Campo actual (Precio unitario): " << v.precio_unitario << ". Nuevo valor: ";
            getline(cin, input);
            if (!input.empty())
                v.precio_unitario = stoi(input);
            cout << "Campo actual (Monto total): " << v.monto_total << ". Nuevo valor: ";
            getline(cin, input);
            if (!input.empty())
                v.monto_total = stoi(input);
            cout << "Campo actual (Medio envio): " << v.medio_envio << ". Nuevo valor: ";
            getline(cin, input);
            if (!input.empty())
                v.medio_envio = input;
            cout << "Campo actual (Estado envio): " << v.estado_envio << ". Nuevo valor: ";
            getline(cin, input);
            if (!input.empty())
                v.estado_envio = input;
            break;
        } // Modifica campo por campo, los valores de la venta a modificar
    }
    if (encontrado)
    {
        ifs++;
        ifs_local++;
        guardarVentasCSV(nombreArchivo, ventas);
        cout << "Venta modificada correctamente.\n";
    }
    else
    {
        ifs++;
        ifs_local++;
        cout << "No se encontro la venta con ese ID.\n";
    }

    auto fin = high_resolution_clock::now(); // Finaliza el reloj
    duration<double> duracion = fin - inicio;
    cout << endl;
    cout << "Tiempo de ejecucion: " << duracion.count() << " segundos" << endl;
    cout << endl;
    cout << "IFs ejecutados en esta funcion: " << ifs_local << endl;
    cout << "*" << endl;
}

void listarVentasPorCiudad(const vector<Venta> &ventas)
{
    using namespace std::chrono;
    auto inicio = high_resolution_clock::now(); // Inicia el reloj
    int ifs_local = 0;

    string ciudadBuscada;
    cout << "Ingrese el nombre de la ciudad para listar ventas: ";
    cin.ignore();
    getline(cin, ciudadBuscada);

    bool hayResultados = false;
    cout << "\n--- Ventas en la ciudad de " << ciudadBuscada << " ---" << endl;

    for (size_t i = 0; i < ventas.size(); i++)
    { // Este bucle recorre el vector ventas, en busca de las ventas que coincidan con la ciudad a buscar
        ifs++;
        ifs_local++; // filtro por ciudad
        if (ventas[i].ciudad == ciudadBuscada)
        {
            ifs++;
            ifs_local++;
            hayResultados = true;
            cout << "ID: " << ventas[i].id << " | Cliente: " << ventas[i].cliente
                 << " | Producto: " << ventas[i].producto << " | Monto: $" << ventas[i].monto_total
                 << " | Fecha: " << ventas[i].fecha << " | Medio de envio: " << ventas[i].medio_envio << endl;
        }
    }

    if (!hayResultados)
    {
        ifs++;
        ifs_local++;
        cout << "No se encontraron ventas en esa ciudad." << endl;
    }

    auto fin = high_resolution_clock::now(); // Finaliza el reloj
    duration<double> duracion = fin - inicio;
    cout << endl;
    cout << "Tiempo de ejecucion: " << duracion.count() << " segundos" << endl;
    cout << endl;
    cout << "IFs ejecutados en esta funcion: " << ifs_local << endl;
    cout << "*" << endl;
}

void listarVentasPorPaisYFechas(const vector<Venta> &ventas)
{

    using namespace std::chrono;
    auto inicio = high_resolution_clock::now(); // Inicia el reloj
    int ifs_local = 0;

    string paisBuscado, fechaInicio, fechaFin;
    cout << "Ingrese el pais: ";
    cin.ignore();
    getline(cin, paisBuscado);
    cout << "Ingrese fecha de inicio (formato: d/m/yyyy): ";
    getline(cin, fechaInicio);
    cout << "Ingrese fecha de fin (formato: d/m/yyyy): ";
    getline(cin, fechaFin);

    bool hayResultados = false;
    cout << "\n--- Ventas en " << paisBuscado << " entre " << fechaInicio << " y " << fechaFin << " ---\n";

    for (size_t i = 0; i < ventas.size(); i++)
    { // Primero en este bucle busca en el vector ventas que coincidan los paises
        ifs++;
        ifs_local++; // filtro por pais
        if (ventas[i].pais == paisBuscado)
        {
            ifs++;
            ifs_local++; // filtro por fechas
            if (ventas[i].fecha >= fechaInicio && ventas[i].fecha <= fechaFin)
            { // Luego busco entre el rango de fechas
                ifs++;
                ifs_local++;
                hayResultados = true;
                cout << "ID: " << ventas[i].id << " | Fecha: " << ventas[i].fecha
                     << " | Cliente: " << ventas[i].cliente << " | Producto: " << ventas[i].producto
                     << " | Monto: $" << ventas[i].monto_total << endl;
            }
        }
    }

    if (!hayResultados)
    {
        ifs++;
        ifs_local++;
        cout << "No se encontraron ventas para ese rango y pais." << endl;
    }

    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;
    cout << endl;
    cout << "Tiempo de ejecucion: " << duracion.count() << " segundos" << endl;
    cout << endl;
    cout << "IFs ejecutados en esta funcion: " << ifs_local << endl;
    cout << "*" << endl;
}

void compararDosPaises(const vector<Venta> &ventas, string pais1, string pais2)
{
    // Acumuladores para el monto total, productos vendidos, cantidades y medios de envio por pais
    int monto1 = 0, monto2 = 0;
    vector<string> productos1, productos2;
    vector<int> cantidades1, cantidades2;
    vector<string> medios1, medios2;
    vector<int> veces1, veces2;

    using namespace std::chrono;
    auto inicio = high_resolution_clock::now();
    int ifs_local = 0;

    // Recorre todas las ventas
    for (size_t i = 0; i < ventas.size(); i++)
    {
        ifs++;
        ifs_local++;
        // Si la venta corresponde al primer pais
        if (ventas[i].pais == pais1)
        {
            ifs++;
            ifs_local++;
            monto1 += ventas[i].monto_total;

            // Se actualiza cantidad vendida por producto
            string prod = ventas[i].producto;
            int cant = ventas[i].cantidad;
            bool encontrado = false;
            for (int j = 0; j < productos1.size(); j++)
            {
                ifs++;
                ifs_local++;
                if (productos1[j] == prod)
                {
                    ifs++;
                    ifs_local++;
                    cantidades1[j] += cant;
                    encontrado = true;
                    break;
                }
            }
            // Si el producto no fue registrado, se agrega
            if (!encontrado)
            {
                ifs++;
                ifs_local++;
                productos1.push_back(prod);
                cantidades1.push_back(cant);
            }

            // Se actualiza conteo del medio de envio usado
            string medio = ventas[i].medio_envio;
            encontrado = false;
            for (int j = 0; j < medios1.size(); j++)
            {
                ifs++;
                ifs_local++;
                if (medios1[j] == medio)
                {
                    ifs++;
                    ifs_local++;
                    veces1[j]++;
                    encontrado = true;
                    break;
                }
            }
            // Si el medio no fue registrado, se agrega
            if (!encontrado)
            {
                ifs++;
                ifs_local++;
                medios1.push_back(medio);
                veces1.push_back(1);
            }
        }
        else if (ventas[i].pais == pais2)
        {
            // Repite el mismo proceso para el segundo pais
            ifs++;
            ifs_local++;
            monto2 += ventas[i].monto_total;

            string prod = ventas[i].producto;
            int cant = ventas[i].cantidad;
            bool encontrado = false;
            for (int j = 0; j < productos2.size(); j++)
            {
                ifs++;
                ifs_local++;
                if (productos2[j] == prod)
                {
                    ifs++;
                    ifs_local++;
                    cantidades2[j] += cant;
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado)
            {
                ifs++;
                ifs_local++;
                productos2.push_back(prod);
                cantidades2.push_back(cant);
            }

            string medio = ventas[i].medio_envio;
            encontrado = false;
            for (int j = 0; j < medios2.size(); j++)
            {
                ifs++;
                ifs_local++;
                if (medios2[j] == medio)
                {
                    ifs++;
                    ifs_local++;
                    veces2[j]++;
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado)
            {
                ifs++;
                ifs_local++;
                medios2.push_back(medio);
                veces2.push_back(1);
            }
        }
    }

    // Muestra monto total acumulado por pais
    cout << "\nComparacion entre " << pais1 << " y " << pais2 << ":\n";
    cout << "Monto total de ventas:\n";
    cout << " - " << pais1 << ": $" << monto1 << endl;
    cout << " - " << pais2 << ": $" << monto2 << endl;

    // Determina el producto mas vendido por pais (mayor cantidad)
    int max1 = 0, max2 = 0;
    string topProd1 = "", topProd2 = "";

    for (int i = 0; i < productos1.size(); i++)
    {
        ifs++;
        ifs_local++;
        if (cantidades1[i] > max1)
        {
            ifs++;
            ifs_local++;
            max1 = cantidades1[i];
            topProd1 = productos1[i];
        }
    }

    for (int i = 0; i < productos2.size(); i++)
    {
        ifs++;
        ifs_local++;
        if (cantidades2[i] > max2)
        {
            ifs++;
            ifs_local++;
            max2 = cantidades2[i];
            topProd2 = productos2[i];
        }
    }

    // Muestra productos mas vendidos por pais
    cout << "\nProducto mas vendido:\n";
    cout << " - " << pais1 << ": " << topProd1 << " (" << max1 << " unidades)\n";
    cout << " - " << pais2 << ": " << topProd2 << " (" << max2 << " unidades)\n";

    // Determina el medio de envio mas utilizado por pais
    int maxEnvio1 = 0, maxEnvio2 = 0;
    string envioTop1 = "", envioTop2 = "";

    for (int i = 0; i < medios1.size(); i++)
    {
        ifs++;
        ifs_local++;
        if (veces1[i] > maxEnvio1)
        {
            ifs++;
            ifs_local++;
            maxEnvio1 = veces1[i];
            envioTop1 = medios1[i];
        }
    }

    for (int i = 0; i < medios2.size(); i++)
    {
        ifs++;
        ifs_local++;
        if (veces2[i] > maxEnvio2)
        {
            ifs++;
            ifs_local++;
            maxEnvio2 = veces2[i];
            envioTop2 = medios2[i];
        }
    }

    // Muestra el medio mas usado por pais
    cout << "\nMedio de envio mas utilizado:\n";
    cout << " - " << pais1 << ": " << envioTop1 << " (" << maxEnvio1 << " veces)\n";
    cout << " - " << pais2 << ": " << envioTop2 << " (" << maxEnvio2 << " veces)\n";

    // Calcula y muestra duracion de la funcion
    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;
    cout << endl;
    cout << "Tiempo de ejecucion: " << duracion.count() << " segundos" << endl;
    cout << endl;
    cout << "IFs ejecutados en esta funcion: " << ifs_local << endl;
    cout << "*" << endl;
}

void compararDosProductos(const vector<Venta> &ventas, string prod1, string prod2)
{
    // Acumuladores por pais: cantidades y montos para cada producto
    vector<string> paises;
    vector<int> cant1, cant2;
    vector<int> monto1, monto2;

    using namespace std::chrono;
    auto inicio = high_resolution_clock::now();
    int ifs_local = 0;

    // Recorremos todas las ventas
    for (int i = 0; i < ventas.size(); i++)
    {
        ifs++;
        ifs_local++;
        if (ventas[i].producto == prod1 || ventas[i].producto == prod2)
        {
            ifs++;
            ifs_local++;
            string pais = ventas[i].pais;
            int pos = -1;

            // Buscamos si ya registramos ese pais
            for (int j = 0; j < paises.size(); j++)
            {
                ifs++;
                ifs_local++;
                if (paises[j] == pais)
                {
                    ifs++;
                    ifs_local++;
                    pos = j;
                    break;
                }
            }

            // Si es la primera vez que aparece el pais, lo agregamos
            if (pos == -1)
            {
                ifs++;
                ifs_local++;
                paises.push_back(pais);
                cant1.push_back(0);
                cant2.push_back(0);
                monto1.push_back(0);
                monto2.push_back(0);
                pos = paises.size() - 1;
            }

            // Acumulamos cantidades y montos segun producto
            int cantidad = ventas[i].cantidad;
            int monto = ventas[i].monto_total;

            if (ventas[i].producto == prod1)
            {
                ifs++;
                ifs_local++;
                cant1[pos] += cantidad;
                monto1[pos] += monto;
            }
            else
            {
                ifs++;
                ifs_local++;
                cant2[pos] += cantidad;
                monto2[pos] += monto;
            }
        }
    }

    // Mostramos resultados por pais
    cout << "\nComparacion entre productos: " << prod1 << " y " << prod2 << ":\n";
    for (int i = 0; i < paises.size(); i++)
    {
        cout << "\nPais: " << paises[i] << endl;
        cout << " - " << prod1 << ": " << cant1[i] << " unidades, $" << monto1[i] << endl;
        cout << " - " << prod2 << ": " << cant2[i] << " unidades, $" << monto2[i] << endl;
    }

    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;
    cout << endl;
    cout << "Tiempo de ejecucion: " << duracion.count() << " segundos" << endl;
    cout << endl;
    cout << "IFs ejecutados en esta funcion: " << ifs_local << endl;
    cout << "*" << endl;
}

void productosPromedioDebajo(const vector<Venta> &ventas, string pais, float umbral)
{
    // Acumuladores por producto en ese pais
    vector<string> productos;
    vector<int> cantidadTotal;
    vector<int> montoTotal;

    using namespace std::chrono;
    auto inicio = high_resolution_clock::now();
    int ifs_local = 0;

    // Recorremos todas las ventas
    for (int i = 0; i < ventas.size(); i++)
    {
        ifs++;
        ifs_local++;
        if (ventas[i].pais == pais)
        { // Solo consideramos ventas del pais especificado
            ifs++;
            ifs_local++;
            string prod = ventas[i].producto;
            int cant = ventas[i].cantidad;
            int monto = ventas[i].monto_total;

            int pos = -1;

            // Buscamos si el producto ya esta en la lista
            for (int j = 0; j < productos.size(); j++)
            {
                ifs++;
                ifs_local++;
                if (productos[j] == prod)
                {
                    ifs++;
                    ifs_local++;
                    pos = j;
                    break; // Ya lo encontramos
                }
            }

            // Si no lo encontramos, lo agregamos a los vectores
            if (pos == -1)
            {
                ifs++;
                ifs_local++;
                productos.push_back(prod);
                cantidadTotal.push_back(cant);
                montoTotal.push_back(monto);
            }
            else
            {
                // Si ya estaba, acumulamos cantidades y montos
                cantidadTotal[pos] += cant;
                montoTotal[pos] += monto;
            }
        }
    }

    // Mostrar los productos cuyo promedio esta por debajo del umbral
    cout << "\nProductos con monto promedio menor a $" << umbral << " por unidad vendidos en " << pais << ":\n";

    for (int i = 0; i < productos.size(); i++)
    {
        ifs++;
        ifs_local++;
        if (cantidadTotal[i] > 0)
        { // Evitamos division por cero
            ifs++;
            ifs_local++;
            float promedio = (float)montoTotal[i] / cantidadTotal[i];

            // Solo mostramos si el promedio es menor al umbral
            if (promedio < umbral)
            {
                ifs++;
                ifs_local++;
                cout << " - " << productos[i] << " (promedio: $" << promedio << ")\n";
            }
        }
    }

    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;
    cout << endl;
    cout << "Tiempo de ejecucion: " << duracion.count() << " segundos" << endl;
    cout << endl;
    cout << "IFs ejecutados en esta funcion: " << ifs_local << endl;
    cout << "*" << endl;
}

void productosPromedioEncima(const vector<Venta> &ventas, string pais, float umbral)
{
    // Acumuladores por producto en ese pais
    vector<string> productos;
    vector<int> cantidadTotal;
    vector<int> montoTotal;

    using namespace std::chrono;
    auto inicio = high_resolution_clock::now();
    int ifs_local = 0;

    // Recorremos todas las ventas
    for (int i = 0; i < ventas.size(); i++)
    {
        ifs++;
        ifs_local++;
        if (ventas[i].pais == pais)
        { // Solo consideramos ventas del pais especificado
            ifs++;
            ifs_local++;
            string prod = ventas[i].producto;
            int cant = ventas[i].cantidad;
            int monto = ventas[i].monto_total;

            int pos = -1;

            // Buscamos si el producto ya esta en la lista
            for (int j = 0; j < productos.size(); j++)
            {
                ifs++;
                ifs_local++;
                if (productos[j] == prod)
                {
                    ifs++;
                    ifs_local++;
                    pos = j;
                    break; // Ya lo encontramos
                }
            }

            // Si no lo encontramos, lo agregamos a los vectores
            if (pos == -1)
            {
                ifs++;
                ifs_local++;
                productos.push_back(prod);
                cantidadTotal.push_back(cant);
                montoTotal.push_back(monto);
            }
            else
            {
                // Si ya estaba, acumulamos cantidades y montos
                cantidadTotal[pos] += cant;
                montoTotal[pos] += monto;
            }
        }
    }

    // Mostrar los productos cuyo promedio esta por encima del umbral
    cout << "\nProductos con monto promedio mayor a $" << umbral << " por unidad vendidos en " << pais << ":\n";

    for (int i = 0; i < productos.size(); i++)
    {
        ifs++;
        ifs_local++;
        if (cantidadTotal[i] > 0)
        { // Evitamos division por cero
            ifs++;
            ifs_local++;
            float promedio = (float)montoTotal[i] / cantidadTotal[i];

            // Solo mostramos si el promedio es mayor al umbral
            if (promedio > umbral)
            {
                ifs++;
                ifs_local++;
                cout << " - " << productos[i] << " (promedio: $" << promedio << ")\n";
            }
        }
    }

    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;
    cout << endl;
    cout << "Tiempo de ejecucion: " << duracion.count() << " segundos" << endl;
    cout << endl;
    cout << "IFs ejecutados en esta funcion: " << ifs_local << endl;
    cout << "*" << endl;
}

int main()
{
    auto inicio = high_resolution_clock::now(); // Marca el inicio del reloj
    int opcion;
    ifstream file("ventas_sudamerica_limpio.csv");
    vector<Venta> ventas = leerArchivoCSV("ventas_sudamerica_limpio.csv");
    string archivoVentas = "ventas_sudamerica_limpio.csv";
    Pila<string> pilaPaises = soloPaises(ventas);

    // imprimirVentas(ventas);
    top5ciudades(ventas);
    montoTotalPorProductoYPais(ventas, pilaPaises);
    PromVentasCatPais(ventas);
    MedioEnvioMasUsadoPorPaisYCategoria(ventas, pilaPaises);
    DiaConMayorMontoVentas(ventas);
    EstadoEnvioMasFrecuentePorPais(ventas, pilaPaises);
    productoMasYMenosVendido(ventas);

    auto fin = high_resolution_clock::now(); // Marca de fin del reloj

    duration<double> duracion = fin - inicio;

    cout << "\nTiempo de ejecucion: " << duracion.count() << " segundos" << endl;
    cout << endl;

    cout << "\nCantidad de ifs: " << ifs << " ifs " << endl;
    cout << endl;
    cout << endl;

    cout << "Procesos (funciones) que se llevaron a cabo junto con sus algoritmos y estructuras usadas: " << endl;
    cout << endl;
    cout << endl;

    cout << "top5ciudades(ventas), estructura de datos: Struct, algoritmo de ordenamiento: Burbuja" << endl;
    cout << endl;
    cout << "montoTotalPorProductoYPais(ventas, pilaPaises), estructura de datos: Struct y pilas." << endl;
    cout << endl;
    cout << "PromVentasCatPais(ventas), estructura de datos: Struct" << endl;
    cout << endl;
    cout << "MedioEnvioMasUsadoPorPaisYCategoria(ventas, pilaPaises), estructura de datos: Struct y pilas" << endl;
    cout << endl;
    cout << "DiaConMayorMontoVentas(ventas), estructura de datos: struct, algoritmo de ordenamiento: Shellsort" << endl;
    cout << endl;
    cout << "EstadoEnvioMasFrecuentePorPais(ventas, pilaPaises), estructura de datos: Struct y pilas." << endl;
    cout << endl;
    cout << "productoMasYMenosVendido(ventas), estructura de datos: Struct" << endl;
    cout << endl;

    do
    {
        cout << "\n+-----------------------------------------------+\n";
        cout << "|               MENU DE OPCIONES                |\n";
        cout << "+-----------------------------------------------+\n";
        cout << "| 1. Administrador de VENTAS                    |\n";
        cout << "| 2. Consultas dinamicas                        |\n";
        cout << "| 3. Procesamiento de datos del CSV             |\n";
        cout << "| 4. Salir                                      |\n";
        cout << "+-----------------------------------------------+\n";
        cout << "| Conteo actual de 'if': " << ifs <<endl;;
        cout << "+-----------------------------------------------+\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cout << endl;

        switch (opcion)
        {
        case 1:
        {
            int subop;
            do
            {
                cout<<endl;
                ifs++;
                cout << "+--------------------------------------------+\n";
                cout << "|       ADMINISTRADOR DE VENTAS              |\n";
                cout << "+--------------------------------------------+\n";
                cout << "| 1. Agregar venta                           |\n";
                cout << "| 2. Eliminar venta                          |\n";
                cout << "| 3. Modificar venta                         |\n";
                cout << "| 4. Volver al menu principal                |\n";
                cout << "+--------------------------------------------+\n";
                cout << "Seleccione una opcion: ";
                cin >> subop;
                cout << endl;

                switch (subop)
                {
                case 1:
                    ifs++;
                    agregarVenta(ventas, archivoVentas);
                    ventas = leerArchivoCSV(archivoVentas);
                    break;
                case 2:
                    ifs++;
                    eliminarVenta(ventas, archivoVentas);
                    ventas = leerArchivoCSV(archivoVentas);
                    break;
                case 3:
                    ifs++;
                    modificarVenta(ventas, archivoVentas);
                    ventas = leerArchivoCSV(archivoVentas);
                    break;
                case 4:
                    ifs++;
                    cout << "\nVolviendo...\n";
                    break;
                default:
                    break;
                }
            } while (subop != 4);
            break;
        }
        case 2:
        {
            int subopp;
            do
            {
                ifs++;
                cout << "\n+--------------------------------------------------------------------------+\n";
                cout << "|                  MENU DE CONSULTAS DINAMICAS                             |\n";
                cout << "+--------------------------------------------------------------------------+\n";
                cout << "| 1. Lista de ventas en una ciudad especifica                              |\n";
                cout << "| 2. Lista de ventas en un rango de fechas por pais                        |\n";
                cout << "| 3. Comparacion entre 2 paises                                            |\n";
                cout << "| 4. Comparacion entre 2 productos                                         |\n";
                cout << "| 5. Productos con promedio de venta por debajo de un monto especifico     |\n";
                cout << "| 6. Productos con promedio de venta por encima de un monto especifico     |\n";
                cout << "| 7. Volver al menu principal                                              |\n";
                cout << "+--------------------------------------------------------------------------+\n";
                cout << "Seleccione una opcion: ";
                cin >> subopp;
                cout << endl;

                switch (subopp)
                {
                case 1:
                    ifs++;
                    listarVentasPorCiudad(ventas);
                    break;
                case 2:
                    ifs++;
                    listarVentasPorPaisYFechas(ventas);
                    break;
                case 3:
                {
                    ifs++;
                    string paisA, paisB;
                    cout << "Ingrese el primer pais a comparar: ";
                    cin.ignore();
                    getline(cin, paisA);
                    cout << "Ingrese el segundo pais a comparar: ";
                    getline(cin, paisB);
                    compararDosPaises(ventas, paisA, paisB);
                    break;
                }
                case 4:
                {
                    ifs++;
                    string productoA, productoB;
                    cout << "Ingrese el primer producto a comparar: ";
                    cin.ignore();
                    getline(cin, productoA);
                    cout << "Ingrese el segundo producto a comparar: ";
                    getline(cin, productoB);
                    compararDosProductos(ventas, productoA, productoB);
                    break;
                }
                case 5:
                {
                    ifs++;
                    string pais;
                    float monto;
                    cout << "Ingrese el pais: ";
                    cin.ignore();
                    getline(cin, pais);
                    cout << "Ingrese el monto: ";
                    cin >> monto;
                    productosPromedioDebajo(ventas, pais, monto);
                    break;
                }
                case 6:
                {
                    ifs++;
                    string pais;
                    float monto;
                    cout << "Ingrese el pais: ";
                    cin.ignore();
                    getline(cin, pais);
                    cout << "Ingrese el monto: ";
                    cin >> monto;
                    productosPromedioEncima(ventas, pais, monto);
                    break;
                }
                case 7:
                    ifs++;
                    cout << endl;
                    cout << "\nVolviendo....\n";
                    cout << endl;
                    break;
                default:
                    break;
                }
            } while (subopp != 7);
            break;
        }
        case 3:
            ifs++;
            int suboppp;
            do
            {
                ifs++;
                cout << "\n+--------------------------------------------------------------+\n";
                cout << "|       MENU DE PROCESAMIENTO DE DATOS DEL ARCHIVO CSV         |\n";
                cout << "+--------------------------------------------------------------+\n";
                cout << "| 1. Top 5 de ciudades con mayor monto de ventas por pais      |\n";
                cout << "| 2. Monto total vendido por producto, discriminado por pais   |\n";
                cout << "| 3. Promedio de ventas por categoria en cada pais             |\n";
                cout << "| 4. Medio de envio mas utilizado por pais y por categoria     |\n";
                cout << "| 5. Dia con mayor cantidad de ventas                          |\n";
                cout << "| 6. Estado de envio mas frecuente por pais                    |\n";
                cout << "| 7. Producto mas y menos vendido (por unidades)               |\n";
                cout << "| 8. Volver al menu                                            |\n";
                cout << "+--------------------------------------------------------------+\n";
                cout << "Seleccione una opcion: ";
                cin >> suboppp;
                cout << endl;

                switch (suboppp)
                {
                case 1:
                    ifs++;
                    top5ciudades(ventas);

                    break;
                case 2:
                    ifs++;
                    montoTotalPorProductoYPais(ventas, pilaPaises);

                    break;
                case 3:
                    ifs++;
                    PromVentasCatPais(ventas);

                    break;
                case 4:
                    ifs++;
                    MedioEnvioMasUsadoPorPaisYCategoria(ventas, pilaPaises);

                    break;
                case 5:
                    ifs++;
                    DiaConMayorMontoVentas(ventas);

                    break;
                case 6:
                    ifs++;
                    EstadoEnvioMasFrecuentePorPais(ventas, pilaPaises);

                    break;
                case 7:
                    ifs++;
                    productoMasYMenosVendido(ventas);

                    break;
                case 8:
                    ifs++;
                    cout << "\nVolviendo...\n";
                    break;
                default:
                    break;
                }
            } while (suboppp != 8);
            break;

        case 4:
            ifs++;
            cout << endl;
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            ifs++;
            cout << endl;
            cout << "Opcion invalida. Intentelo de nuevo.(HELL NAHH....)" << endl;
            break;
        }
    } while (opcion != 4);
}
