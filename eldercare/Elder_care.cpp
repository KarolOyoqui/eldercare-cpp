#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

// Limpiar pantalla
#ifdef _WIN32
#define CLEAR "cls"
#elif defined(unix)||defined(__unix__)||defined(__unix)||defined(__APPLE__)||defined(__MACH__)
#define CLEAR "clear"
#else
#error "Sistema no pudo limpiar la pantalla."
#endif

using namespace std;

class menu
{
private:
    string codigo; // Variable agregada para manejar el ID/Código de registros
    string nombre;
    string apellido;
    string fecha_nacimiento;
    string direccion;
    string estado;
    string ciudad;
    string codigo_postal;
    string telefono;
    string emergencyPhoneNumber;
    string currentDate; // Corregido: error de sintaxis previo
    string idUserAdmin; 
    string idRole;
    
public:
    void registrarCliente();
    void registrarEmpleado();
    void bajaCliente();
    void bajaEmpleado();
    void modificarCliente();
    void listarClientes();
    void menuPrincipal();
    void mostrarRegistros(string cod);
    void buscarCliente();
};

// Declaración de funciones globales/auxiliares
void pausa();
void error();
void comprobarArchivo();

int main()
{
    comprobarArchivo(); // Crea los archivos si no existen
    menu sistema;
    sistema.menuPrincipal();
    return 0;
}

void menu::menuPrincipal()
{
    int opcion;
    do
    {
        system(CLEAR);
        cout << "=================================================" << endl;
        cout << "   Bienvenido al sistema de cuidado de ancianos  " << endl;
        cout << "=================================================" << endl;
        cout << "1. Registrar cliente" << endl;
        cout << "2. Registrar empleado" << endl;
        cout << "3. Baja cliente" << endl;
        cout << "4. Baja empleado" << endl;
        cout << "5. Modificar cliente" << endl;
        cout << "6. Listar clientes" << endl;
        cout << "7. Buscar cliente" << endl;
        cout << "8. Salir" << endl;
        cout << "Select an option please: ";
        cin >> opcion;
        cin.ignore(); // Limpia el buffer para que no afecte a los getline posteriores

        switch (opcion)
        {
        case 1:
            registrarCliente();
            break;
        case 2:
            registrarEmpleado();
            break;
        case 3:
            bajaCliente();
            break;
        case 4:
            bajaEmpleado();
            break;
        case 5:
            modificarCliente();
            break;
        case 6:
            listarClientes();
            break;
        case 7:
            buscarCliente();
            break;
        case 8:
            cout << "Saliendo del sistema..." << endl;
            break;
        default:
            error();
            pausa();
            break;
        }
    } while (opcion != 8);
}

void menu::registrarCliente()
{
    ofstream escritura;
    ifstream verificador;
    string auxCodigo;
    bool coincidencia = false;

    escritura.open("clientes.txt", ios::app);
    verificador.open("clientes.txt", ios::in);

    if (escritura.is_open() && verificador.is_open())
    {
        system(CLEAR);
        cout << "\t\t\t\t*** Registrar un Cliente ***\t\t\t\t\n\n";
        cout << "Ingresa el código del cliente: ";
        getline(cin, auxCodigo);

        if (auxCodigo == "") {
            do {
                cout << "¡Código de cliente no válido!, inténtalo nuevamente: ";
                getline(cin, auxCodigo);
            } while (auxCodigo == "");
        }

        // Bucle para evitar códigos duplicados
        do {
            verificador.seekg(0, ios::beg);
            coincidencia = false;
            while (getline(verificador, codigo))
            {
                getline(verificador, nombre);
                getline(verificador, apellido);
                getline(verificador, fecha_nacimiento);
                getline(verificador, direccion);
                getline(verificador, estado);
                getline(verificador, ciudad);
                getline(verificador, codigo_postal);
                getline(verificador, telefono);
                getline(verificador, emergencyPhoneNumber);
                getline(verificador, currentDate);

                if (codigo == auxCodigo)
                {
                    coincidencia = true;
                    cout << "\n\n¡Ya existe un cliente con ese código!\n\n";
                    cout << "El cliente asociado es: " << nombre << " " << apellido << "\n\n";
                    cout << "Ingresa un código válido: ";
                    getline(cin, auxCodigo);
                    
                    if (auxCodigo == "") {
                        do {
                            cout << "\n¡Código no válido!, inténtalo nuevamente: ";
                            getline(cin, auxCodigo);
                        } while (auxCodigo == "");
                    }
                    break;
                }
            }
        } while (coincidencia == true);

        codigo = auxCodigo;
        system(CLEAR);
        cout << "\t\t\t\t*** Registrar un Cliente ***\t\t\t\t\n\n";
        cout << "Código del cliente: " << codigo << "\n\n";

        cout << "Ingresa el nombre del cliente: "; getline(cin, nombre);
        cout << "Ingresa el apellido del cliente: "; getline(cin, apellido);
        cout << "Ingresa la fecha de nacimiento (DD/MM/AAAA): "; getline(cin, fecha_nacimiento);
        cout << "Ingresa la dirección/domicilio: "; getline(cin, direccion);
        cout << "Ingresa el Estado: "; getline(cin, estado);
        cout << "Ingresa la Ciudad: "; getline(cin, ciudad);
        cout << "Ingresa el código postal: "; getline(cin, codigo_postal);
        cout << "Ingresa el número de teléfono: "; getline(cin, telefono);
        cout << "Ingresa el teléfono de emergencia: "; getline(cin, emergencyPhoneNumber);
        cout << "Ingresa la fecha de inscripción (DD/MM/AAAA): "; getline(cin, currentDate);

        // Escritura estructurada en el archivo txt
        escritura << codigo << endl << nombre << endl << apellido << endl << fecha_nacimiento << endl 
                  << direccion << endl << estado << endl << ciudad << endl << codigo_postal << endl 
                  << telefono << endl << emergencyPhoneNumber << endl << currentDate << endl;

        cout << "\nEl registro se ha completado correctamente.\n\n";
    }
    else
    {
        error();
    }

    escritura.close();
    verificador.close();
    pausa();
}

void menu::registrarEmpleado()
{
    ofstream escritura;
    ifstream verificador;
    string auxCodigo;
    bool coincidencia = false;

    escritura.open("empleados.txt", ios::app);
    verificador.open("empleados.txt", ios::in);

    if (escritura.is_open() && verificador.is_open())
    {
        system(CLEAR);
        cout << "\t\t\t\t*** Registrar un Empleado ***\t\t\t\t\n\n";
        cout << "Ingresa el código del empleado: ";
        getline(cin, auxCodigo);

        if (auxCodigo == "") {
            do {
                cout << "¡Código no válido!, inténtalo nuevamente: ";
                getline(cin, auxCodigo);
            } while (auxCodigo == "");
        }

        do {
            verificador.seekg(0, ios::beg);
            coincidencia = false;
            while (getline(verificador, codigo))
            {
                getline(verificador, nombre);
                getline(verificador, apellido);
                getline(verificador, fecha_nacimiento);
                getline(verificador, direccion);
                getline(verificador, estado);
                getline(verificador, ciudad);
                getline(verificador, codigo_postal);
                getline(verificador, telefono);
                getline(verificador, idUserAdmin);
                getline(verificador, idRole);

                if (codigo == auxCodigo)
                {
                    coincidencia = true;
                    cout << "\n\n¡Ya existe un empleado con ese código!\n\n";
                    cout << "El empleado asociado es: " << nombre << " " << apellido << "\n\n";
                    cout << "Ingresa un código válido: ";
                    getline(cin, auxCodigo);
                    if (auxCodigo == "") {
                        do {
                            cout << "\n¡Código no válido!, inténtalo nuevamente: ";
                            getline(cin, auxCodigo);
                        } while (auxCodigo == "");
                    }
                    break;
                }
            }
        } while (coincidencia == true);

        codigo = auxCodigo;
        system(CLEAR);
        cout << "\t\t\t\t*** Registrar un Empleado ***\t\t\t\t\n\n";
        cout << "Código del empleado: " << codigo << "\n\n";

        cout << "Ingresa el nombre del empleado: "; getline(cin, nombre);
        cout << "Ingresa el apellido del empleado: "; getline(cin, apellido);
        cout << "Ingresa la fecha de nacimiento (DD/MM/AAAA): "; getline(cin, fecha_nacimiento);
        cout << "Ingresa la dirección/domicilio: "; getline(cin, direccion);
        cout << "Ingresa el Estado: "; getline(cin, estado);
        cout << "Ingresa la Ciudad: "; getline(cin, ciudad);
        cout << "Ingresa el código postal: "; getline(cin, codigo_postal);
        cout << "Ingresa el número de teléfono: "; getline(cin, telefono);
        cout << "Ingresa el ID de Administrador a cargo: "; getline(cin, idUserAdmin);
        cout << "Ingresa el ID de Rol asignado: "; getline(cin, idRole);

        escritura << codigo << endl << nombre << endl << apellido << endl << fecha_nacimiento << endl 
                  << direccion << endl << estado << endl << ciudad << endl << codigo_postal << endl 
                  << telefono << endl << idUserAdmin << endl << idRole << endl;

        cout << "\nEl registro se ha completado correctamente.\n\n";
    }
    else
    {
        error();
    }

    escritura.close();
    verificador.close();
    pausa();
}

void menu::bajaCliente()
{
    ifstream lectura;
    ofstream auxiliar;
    bool encontrado = false;
    string auxCodigo, respuesta;

    lectura.open("clientes.txt", ios::in);
    if (lectura.is_open())
    {
        system(CLEAR);
        cout << "\t\t\t\t*** Dar de baja un cliente ***\t\t\t\t\n\n";
        
        // Comprobar si el archivo está vacío
        if (lectura.peek() == ifstream::traits_type::eof()) {
            cout << "No hay ningún cliente registrado en el sistema.\n";
            lectura.close();
            pausa();
            return;
        }

        auxiliar.open("auxiliar.txt", ios::out);
        cout << "Ingresa el código del cliente que deseas dar de baja: ";
        getline(cin, auxCodigo);

        while (getline(lectura, codigo))
        {
            getline(lectura, nombre);
            getline(lectura, apellido);
            getline(lectura, fecha_nacimiento);
            getline(lectura, direccion);
            getline(lectura, estado);
            getline(lectura, ciudad);
            getline(lectura, codigo_postal);
            getline(lectura, telefono);
            getline(lectura, emergencyPhoneNumber);
            getline(lectura, currentDate);

            if (auxCodigo == codigo)
            {
                encontrado = true;
                cout << "\n\n¡Registro Encontrado!\n\n";
                mostrarRegistros(codigo);
                cout << "¿Realmente deseas dar de baja a este cliente (s/n)?: ";
                getline(cin, respuesta);

                if (respuesta == "s" || respuesta == "S" || respuesta == "si" || respuesta == "SI") {
                    cout << "\nEl cliente se ha dado de baja correctamente.\n";
                } else {
                    cout << "\nCliente conservado.\n";
                    auxiliar << codigo << endl << nombre << endl << apellido << endl << fecha_nacimiento << endl 
                             << direccion << endl << estado << endl << ciudad << endl << codigo_postal << endl 
                             << telefono << endl << emergencyPhoneNumber << endl << currentDate << endl;
                }
            }
            else
            {
                auxiliar << codigo << endl << nombre << endl << apellido << endl << fecha_nacimiento << endl 
                         << direccion << endl << estado << endl << ciudad << endl << codigo_postal << endl 
                         << telefono << endl << emergencyPhoneNumber << endl << currentDate << endl;
            }
        }
        
        lectura.close();
        auxiliar.close();
        
        remove("clientes.txt");
        rename("auxiliar.txt", "clientes.txt");

        if (!encontrado) {
            cout << "\nNo se encontró el código de cliente: " << auxCodigo << "\n";
        }
    }
    else
    {
        error();
    }
    pausa();
}

void menu::bajaEmpleado()
{
    ifstream lectura;
    ofstream auxiliar;
    bool encontrado = false;
    string auxCodigo, respuesta;

    lectura.open("empleados.txt", ios::in);
    if (lectura.is_open())
    {
        system(CLEAR);
        cout << "\t\t\t\t*** Dar de baja un empleado ***\t\t\t\t\n\n";

        if (lectura.peek() == ifstream::traits_type::eof()) {
            cout << "No hay ningún empleado registrado en el sistema.\n";
            lectura.close();
            pausa();
            return;
        }

        auxiliar.open("auxiliar.txt", ios::out);
        cout << "Ingresa el código del empleado que deseas dar de baja: ";
        getline(cin, auxCodigo);

        while (getline(lectura, codigo))
        {
            getline(lectura, nombre);
            getline(lectura, apellido);
            getline(lectura, fecha_nacimiento);
            getline(lectura, direccion);
            getline(lectura, estado);
            getline(lectura, ciudad);
            getline(lectura, codigo_postal);
            getline(lectura, telefono);
            getline(lectura, idUserAdmin);
            getline(lectura, idRole);

            if (auxCodigo == codigo)
            {
                encontrado = true;
                cout << "¡Registro Encontrado!\n";
                cout << "Código: " << codigo << " | Nombre: " << nombre << " " << apellido << endl;
                cout << "¿Realmente deseas dar de baja a este empleado (s/n)?: ";
                getline(cin, respuesta);

                if (respuesta == "s" || respuesta == "S" || respuesta == "si" || respuesta == "SI") {
                    cout << "\nEl empleado se ha dado de baja correctamente.\n";
                } else {
                    cout << "\nEmpleado conservado.\n";
                    auxiliar << codigo << endl << nombre << endl << apellido << endl << fecha_nacimiento << endl 
                             << direccion << endl << estado << endl << ciudad << endl << codigo_postal << endl 
                             << telefono << endl << idUserAdmin << endl << idRole << endl;
                }
            }
            else
            {
                auxiliar << codigo << endl << nombre << endl << apellido << endl << fecha_nacimiento << endl 
                         << direccion << endl << estado << endl << ciudad << endl << codigo_postal << endl 
                         << telefono << endl << idUserAdmin << endl << idRole << endl;
            }
        }
        
        lectura.close();
        auxiliar.close();
        
        remove("empleados.txt");
        rename("auxiliar.txt", "empleados.txt");

        if (!encontrado) {
            cout << "\nNo se encontró el código de empleado: " << auxCodigo << "\n";
        }
    }
    else
    {
        error();
    }
    pausa();
}

void menu::modificarCliente()
{
    ifstream lectura;
    ofstream auxiliar;
    bool encontrado = false;
    string auxCodigo;

    lectura.open("clientes.txt", ios::in);
    if (lectura.is_open())
    {
        system(CLEAR);
        cout << "\t\t\t\t*** Modificar Cliente ***\t\t\t\t\n\n";

        if (lectura.peek() == ifstream::traits_type::eof()) {
            cout << "No hay clientes registrados para modificar.\n";
            lectura.close();
            pausa();
            return;
        }

        auxiliar.open("auxiliar.txt", ios::out);
        cout << "Ingresa el código del cliente que deseas modificar: ";
        getline(cin, auxCodigo);

        while (getline(lectura, codigo))
        {
            getline(lectura, nombre);
            getline(lectura, apellido);
            getline(lectura, fecha_nacimiento);
            getline(lectura, direccion);
            getline(lectura, estado);
            getline(lectura, ciudad);
            getline(lectura, codigo_postal);
            getline(lectura, telefono);
            getline(lectura, emergencyPhoneNumber);
            getline(lectura, currentDate);

            if (auxCodigo == codigo)
            {
                encontrado = true;
                cout << "\n--- Datos Actuales ---\n";
                mostrarRegistros(codigo);
                cout << "\n--- Ingrese los Nuevos Datos ---\n";
                cout << "Nuevo Nombre: "; getline(cin, nombre);
                cout << "Nuevo Apellido: "; getline(cin, apellido);
                cout << "Nueva Fecha de Nacimiento: "; getline(cin, fecha_nacimiento);
                cout << "Nueva Dirección: "; getline(cin, direccion);
                cout << "Nuevo Estado: "; getline(cin, estado);
                cout << "Nueva Ciudad: "; getline(cin, ciudad);
                cout << "Nuevo Código Postal: "; getline(cin, codigo_postal);
                cout << "Nuevo Teléfono: "; getline(cin, telefono);
                cout << "Nuevo Teléfono de Emergencia: "; getline(cin, emergencyPhoneNumber);
                cout << "Nueva Fecha de Inscripción: "; getline(cin, currentDate);
                cout << "\n¡Registro modificado con éxito!\n";
            }

            auxiliar << codigo << endl << nombre << endl << apellido << endl << fecha_nacimiento << endl 
                     << direccion << endl << estado << endl << ciudad << endl << codigo_postal << endl 
                     << telefono << endl << emergencyPhoneNumber << endl << currentDate << endl;
        }

        lectura.close();
        auxiliar.close();

        remove("clientes.txt");
        rename("auxiliar.txt", "clientes.txt");

        if (!encontrado) {
            cout << "\nNo se encontró ningún cliente con el código: " << auxCodigo << "\n";
        }
    }
    else
    {
        error();
    }
    pausa();
}

void menu::listarClientes()
{
    ifstream lectura;
    lectura.open("clientes.txt", ios::in);

    if (lectura.is_open())
    {
        system(CLEAR);
        cout << "\t\t\t\t*** Lista de Clientes Registrados ***\t\t\t\t\n\n";

        if (lectura.peek() == ifstream::traits_type::eof()) {
            cout << "No hay clientes en la base de datos actualmente.\n";
        }
        else {
            while (getline(lectura, codigo))
            {
                getline(lectura, nombre);
                getline(lectura, apellido);
                getline(lectura, fecha_nacimiento);
                getline(lectura, direccion);
                getline(lectura, estado);
                getline(lectura, ciudad);
                getline(lectura, codigo_postal);
                getline(lectura, telefono);
                getline(lectura, emergencyPhoneNumber);
                getline(lectura, currentDate);

                mostrarRegistros(codigo);
            }
        }
        lectura.close();
    }
    else
    {
        error();
    }
    pausa();
}

void menu::buscarCliente()
{
    ifstream lectura;
    string auxCodigo;
    bool encontrado = false;

    lectura.open("clientes.txt", ios::in);
    if (lectura.is_open())
    {
        system(CLEAR);
        cout << "\t\t\t\t*** Buscar un Cliente ***\t\t\t\t\n\n";
        cout << "Ingresa el código del cliente a buscar: ";
        getline(cin, auxCodigo);

        while (getline(lectura, codigo))
        {
            getline(lectura, nombre);
            getline(lectura, apellido);
            getline(lectura, fecha_nacimiento);
            getline(lectura, direccion);
            getline(lectura, estado);
            getline(lectura, ciudad);
            getline(lectura, codigo_postal);
            getline(lectura, telefono);
            getline(lectura, emergencyPhoneNumber);
            getline(lectura, currentDate);

            if (auxCodigo == codigo)
            {
                encontrado = true;
                system(CLEAR);
                cout << "\t\t\t\t*** Cliente Encontrado ***\t\t\t\t\n\n";
                mostrarRegistros(codigo);
                break;
            }
        }
        if (!encontrado) {
            cout << "\nNo se encontró ningún cliente con el código: " << auxCodigo << "\n";
        }
        lectura.close();
    }
    else
    {
        error();
    }
    pausa();
}

void menu::mostrarRegistros(string cod)
{
    cout << "=========================================================" << endl;
    cout << "Código: " << cod << endl;
    cout << "Nombre Completo: " << nombre << " " << apellido << endl;
    cout << "Fecha de Nacimiento: " << fecha_nacimiento << endl;
    cout << "Dirección: " << direccion << ", " << ciudad << ", " << estado << " (CP: " << codigo_postal << ")" << endl;
    cout << "Teléfono: " << telefono << endl;
    cout << "Contacto de Emergencia: " << emergencyPhoneNumber << endl;
    cout << "Fecha de Registro/Inscripción: " << currentDate << endl;
    cout << "=========================================================" << endl;
}

// Implementación de funciones globales auxiliares
void pausa()
{
    cout << "\nPresione Enter para continuar...";
    cin.get();
}

void error()
{
    cout << "\nError: Operación no válida o problema con los archivos de datos.\n";
}

void comprobarArchivo()
{
    // Esta función asegura la existencia física de los archivos .txt para que no fallen las lecturas iniciales
    ofstream archivoClientes("clientes.txt", ios::app);
    archivoClientes.close();
    
    ofstream archivoEmpleados("empleados.txt", ios::app);
    archivoEmpleados.close();
}