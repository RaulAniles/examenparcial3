#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Definimos constantes
const int MAX_PRODUCTOS = 5;
const string productos[MAX_PRODUCTOS][2] = {{"Pan", "1.50"},
    {"Leche", "2.00"}, 
    {"Huevos", "3.00"},
    {"Fruta", "0.75"}, 
    {"Verdura", "0.50"}};

// Declaración de funciones
void productosDisponibles();
float calcularTotalVentas(float precios[], int cantidades[], int cantidad);
void realizarPago(float totalVentas, string nombres[], float precios[], int cantidades[], int cantidad);
int main() { 
    string nombres[MAX_PRODUCTOS];
    float precios[MAX_PRODUCTOS];
    int cantidades[MAX_PRODUCTOS] = {0};  // Inicializamos las cantidades a 0
    int numProducto, cantidad, cont = 0;
    char seleccion;

    cout << "Bienvenido al sistema de ventas del supermercado\n";

    cout << "Menu de opciones\n";
    cout << "1 Inventario" << endl;
    cout << "2 Comprar" << endl;
    cout << "3 Salir" << endl;

    do {
        productosDisponibles();
        cout << "Seleccione el número del producto que desea agregar: ";
        cin >> numProducto;

        if (numProducto < 1 || numProducto > MAX_PRODUCTOS) {
            cout << "Número de producto no válido. Intente de nuevo.\n";
            continue;  // Saltamos a la siguiente iteración si el número no es válido
        }

        cout << "Ingrese la cantidad del producto: ";
        cin >> cantidad;

        if (cantidad <= 0) {
            cout << "Cantidad no válida. Intente de nuevo.\n";
            continue;  // Saltamos si la cantidad no es válida
        }

        // Guardamos el producto seleccionado
        nombres[cont] = productos[numProducto - 1][0];
        precios[cont] = stof(productos[numProducto - 1][1]);
        cantidades[cont] = cantidad;
        cont += 1;

        cout << "¿Desea agregar otro producto? (s/n): ";
        cin >> seleccion;

    } while (seleccion == 's');

    // Calcular total de ventas
    float totalVentas = calcularTotalVentas(precios, cantidades, cont); 

    // Realizar el pago y mostrar el recibo final
    realizarPago(totalVentas, nombres, precios, cantidades, cont);

    return 0;
}

// Función que muestra los productos disponibles
void productosDisponibles(){
    cout << "\nProductos disponibles:\n";
    for(size_t i = 0; i < MAX_PRODUCTOS; i++){
        cout << i+1 << ". " << productos[i][0];
        cout << " ($" << productos[i][1] << ")\n";
    }
}

// Función para calcular el total de ventas
float calcularTotalVentas(float precios[], int cantidades[], int cantidad) {
    float total = 0;
    for (int i = 0; i < cantidad; ++i) {
        total += precios[i] * cantidades[i]; 
    }
    return total;
}

// Función para realizar el pago y mostrar el recibo final
void realizarPago(float totalVentas, string nombres[], float precios[], int cantidades[], int cantidad) {
    char metodoPago;
    cout << "\nSeleccione el método de pago (t para tarjeta / e para efectivo): ";
    cin >> metodoPago;

    if (metodoPago == 't') {
        // Pago con tarjeta: obtener fecha y hora actual
        time_t now = time(0);
        tm *ltm = localtime(&now);

        cout << "\n--- Recibo Final ---\n";
        for (int i = 0; i < cantidad; i++) {
            cout << nombres[i] << " x" << cantidades[i] << " - $"
                 << fixed << setprecision(2) << precios[i] * cantidades[i] << endl;
        }
        cout << "Total: $" << fixed << setprecision(2) << totalVentas << endl;
        cout << "Fecha y hora del pago: " 
             << 1900 + ltm->tm_year << "-" 
             << 1 + ltm->tm_mon << "-" 
             << ltm->tm_mday << " "
             << ltm->tm_hour << ":" 
             << ltm->tm_min << ":" 
             << ltm->tm_sec << endl;
        cout << "------------------------\n";
    }
    else if (metodoPago == 'e') {
        // Pago en efectivo
        float efectivo;
        do {
            cout << "Ingrese la cantidad en efectivo: ";
            cin >> efectivo;
            if (efectivo < totalVentas) {
                cout << "Cantidad insuficiente. Faltan $" << fixed << setprecision(2) << (totalVentas - efectivo) << endl;
            }
        } while (efectivo < totalVentas);

        float cambio = efectivo - totalVentas;

        cout << "\n--- Recibo Final ---\n";
        for (int i = 0; i < cantidad; i++) {
            cout << nombres[i] << " x" << cantidades[i] << " - $"
                 << fixed << setprecision(2) << precios[i] * cantidades[i] << endl;
        }
        cout << "Total: $" << fixed << setprecision(2) << totalVentas << endl;
        cout << "Efectivo recibido: $" << fixed << setprecision(2) << efectivo << endl;
        cout << "Cambio: $" << fixed << setprecision(2) << cambio << endl;
        cout << "------------------------\n";
    }
    else {
        cout << "Método de pago no válido.\n";
    }
}

// Función para ingresar los datos de los productos
/*
void ingresarProductos(string nombres[], float precios[], int cantidades[], int &numProductos) {
    for (int i = 0; i <= numProductos; ++i) {  
        cout << "Ingrese el nombre del producto " << i + 1 << ": ";
        cin >> nombres[i];
        cout << "Ingrese el precio unitario de " << nombres[i] << ": ";
        cin >> precios[i];  

        // Validación de precio
        while (precios[i] <= 0) { 
            cout << "Precio no válido. Ingrese un valor positivo: ";
            cin >> precios[i];
        }

        cout << "Ingrese la cantidad vendida de " << nombres[i] << ": ";
        cin >> cantidades[i];  

        // Validación de cantidad
        while (cantidades[i] < 0) {
            cout << "Cantidad no válida. Ingrese un valor positivo: ";
            cin >> cantidades[i];
        }
    }
}
*/

// Función para obtener el índice del producto más vendido
/*
int obtenerProductoMasVendido(int cantidades[], int cantidad) {
    int indiceMasVendido = 0;
    for (int i = 1; i <= cantidad; ++i) {  
        if (cantidades[i] > cantidades[indiceMasVendido]) {
            indiceMasVendido = i;
        }
    }
    return indiceMasVendido;
}
*/

// Función para obtener el índice del producto más caro
/*
int obtenerProductoMasCaro(float precios[], int cantidad) {
    int indiceMasCaro = 0;
    for (int i = 1; i < cantidad; i++) { 
        if (precios[i] > precios[indiceMasCaro]) {
            indiceMasCaro = i;
        }
    }
    return indiceMasCaro;
}
*/

// Función para mostrar el resumen de ventas
/*
void mostrarResumenVentas(string nombres[], float precios[], int cantidades[], int cantidad, float totalVentas) {
    cout << "\nResumen de Ventas:\n";
    cout << "Total de ventas: $" << totalVentas << endl; 

    int indiceMasVendido = obtenerProductoMasVendido(cantidades, cantidad);
    cout << "Producto más vendido: " << nombres[indiceMasVendido]  
         << " (Cantidad vendida: " << cantidades[indiceMasVendido] << ")" << endl;

    int indiceMasCaro = obtenerProductoMasCaro(precios, cantidad);
    cout << "Producto más caro: " << nombres[indiceMasCaro]
         << " (Precio: $" << precios[indiceMasCaro] << ")" << endl; 

    cout << "\nDetalles de cada producto vendido:\n";
    for (int i = 0; i < cantidad; i++) {  
        cout << nombres[i] << " - Precio: $" << precios[i]
             << ", Cantidad vendida: " << cantidades[i]
             << ", Total: $" << precios[i] * cantidades[i] << endl;
    }
}
*/