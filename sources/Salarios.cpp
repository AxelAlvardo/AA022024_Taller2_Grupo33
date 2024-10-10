#include <iostream>
#include <fstream>
using namespace std;

struct Empleado
{
    int id;
    string nombre;
    string apellido;
    int salario;
};

void cambio_empleado(Empleado &empelado_1, Empleado &Empleado_2)
{
    Empleado temporal = empelado_1;
    empelado_1 = Empleado_2;
    Empleado_2 = temporal;
}

int padre(int i)
{
    return (i - 1) / 2;
}

void insertar_maxHeap(Empleado empleados[], int &contador, Empleado empleado)
{
    empleados[contador] = empleado;
    int i = contador;
    contador++;

    while (i > 0 && empleados[padre(i)].salario < empleados[i].salario)
    {
        cambio_empleado(empleados[i], empleados[padre(i)]);
        i = padre(i);
    }
}

void formar_monticulo(Empleado empleados[], int n, int i)
{
    int mayorSalario = i;
    int izquierda = 2 * i + 1;
    int derecha = 2 * i + 2;

    if (izquierda < n && empleados[izquierda].salario > empleados[mayorSalario].salario)
    {
        mayorSalario = izquierda;
    }

    if (derecha < n && empleados[derecha].salario > empleados[mayorSalario].salario)
    {
        mayorSalario = derecha;
    }

    if (mayorSalario != i)
    {
        cambio_empleado(empleados[i], empleados[mayorSalario]);
        formar_monticulo(empleados, n, mayorSalario);
    }
};

void heapSort_Salarios(Empleado empleados[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        formar_monticulo(empleados, n, i);
    }

    for (int i = n - 1; i > 0; i--)
    {
        cambio_empleado(empleados[0], empleados[i]);
        formar_monticulo(empleados, i, 0);
    }
};

void leer_empleados(Empleado empleados[], int &contador)
{
    string texto;
    ifstream archivo("Empleados.txt");

    while (getline(archivo, texto))
    {
        Empleado empleado;
        size_t posicion;

        posicion = texto.find(": ");
        empleado.id = stoi(texto.substr(posicion + 2));
        texto = texto.substr(texto.find(",") + 2);

        posicion = texto.find(' ');
        empleado.nombre = texto.substr(0, posicion);
        texto = texto.substr(posicion + 1);

        posicion = texto.find(',');
        empleado.apellido = texto.substr(0, posicion);
        texto = texto.substr(posicion + 2);

        empleado.salario = stoi(texto);
        
        insertar_maxHeap(empleados, contador, empleado);
    }

    archivo.close();
}

void mostrar_salarios(Empleado empleados[], int contador)
{
    heapSort_Salarios(empleados, contador);

    for (int i = contador - 1; i >= 0; i--)
    {
        cout << "ID: " << empleados[i].id << ", "
             << empleados[i].nombre << ", "
             << empleados[i].apellido << ", Salario: $"
             << empleados[i].salario << endl;
    }
}

int main()
{

    Empleado empleados[1100];
    int opcion;
    int contador = 0;

    leer_empleados(empleados, contador);

    do
    {
        cout << "---------------------------\n";
        cout << "Menu:\n";
        cout << "1. Ver salarios\n";
        cout << "2. Salir de la aplicacion\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cout << "---------------------------\n";

        switch (opcion)
        {
        case 1:
            mostrar_salarios(empleados, contador);
            break;
        case 2:
            cout << "Saliendo del sistema\n";
            break;
        default:
            cout << "Opcion no valida, pruebe nuevamente\n";
        }

    } while (opcion != 2);

    return 0;
}
