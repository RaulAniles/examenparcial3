//Raúl Esteban Aniles Macias 222802
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>
using namespace std;

// Definimos constantes
const int MAX_PRODUCTOS = 5;
const int MAX_CANTIDAD = 20;
const string productos[MAX_PRODUCTOS][2] = {{"Pan", "1.50"},
    {"Leche", "2.00"}, 
    {"Huevos", "3.00"},
    {"Fruta", "0.75"}, 
    {"Verdura", "0.50"}};

// Declaración de funciones
void productosDisponibles();
float calcularTotalVentas(float precios[], int cantidades[], int cantidad);
void realizarPago(float totalVentas, string nombres[], float precios[], int cantidades[], int cantidad);
void mostrarInventario(int inv[]);

int main() { 
    string nombres[MAX_PRODUCTOS];
    float precios[MAX_PRODUCTOS];
    int cantidades[MAX_PRODUCTOS] = {0};  // Inicializamos las cantidades a 0
    int cantidadInv[MAX_PRODUCTOS];
    fill(cantidadInv, cantidadInv + MAX_PRODUCTOS, MAX_CANTIDAD);
    int numProducto, cantidad, cont = 0, menup;
    char seleccion;

    cout << "Bienvenido al sistema de ventas del supermercado\n";

    do{
        cout << "\nMenu de opciones\n";
        cout << "1 Inventario" << endl;
        cout << "2 Comprar" << endl;
        cout << "3 Salir" << endl;
        cin >> menup;
        
        switch(menup){
            case 1:
                mostrarInventario(cantidadInv);
                break;
            case 2:
            {
                do {
                    seleccion = 's';
                    productosDisponibles();
                    cout << "Seleccione el número del producto que desea agregar: ";
                    cin >> numProducto;

                    if(numProducto == MAX_PRODUCTOS + 1) break;

                    if (numProducto < 1 || numProducto > MAX_PRODUCTOS) {
                        cout << "Número de producto no válido. Intente de nuevo.\n";
                        continue;  // Saltamos a la siguiente iteración si el número no es válido
                    }

                    cout << "Ingrese la cantidad del producto: ";
                    cin >> cantidad;

                    if (cantidad <= 0  || cantidad > cantidadInv[numProducto-1]) {
                        cout << "Cantidad no válida. Intente de nuevo.\n";
                        continue;  // Saltamos si la cantidad no es válida
                    }

                    // Guardamos el producto seleccionado
                    nombres[cont] = productos[numProducto - 1][0];
                    precios[cont] = stof(productos[numProducto - 1][1]);
                    cantidades[cont] = cantidad;
                    cantidadInv[numProducto-1] = cantidadInv[numProducto-1] - cantidad;
                    cont += 1;

                    cout << "¿Desea agregar otro producto? (s/n): ";
                    cin >> seleccion;

                } while (seleccion == 's' && cont < MAX_PRODUCTOS);

                // Calcular total de ventas
                float totalVentas = calcularTotalVentas(precios, cantidades, cont); 

                // Realizar el pago y mostrar el recibo final
                realizarPago(totalVentas, nombres, precios, cantidades, cont);

                cont = 0;
            }
            break;
            case 3:
                cout << "Muchas gracias por visitarnos, hasta la proxima!";
            break;
            default:
                cout << "Opción no válida";
            break;
        }
    }while(menup != 3);
    return 0;
}

// Función que muestra los productos disponibles
void productosDisponibles(){
    cout << "\nProductos disponibles:\n";
    size_t i;
    for(i = 0; i < MAX_PRODUCTOS; i++){
        cout << i+1 << ". " << productos[i][0];
        cout << " ($" << productos[i][1] << ")\n";
    }
    cout << i+1 <<". Salir\n";
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
    float iva = 0.16;
    cout << "\nSeleccione el método de pago (t para tarjeta / e para efectivo): ";
    cin >> metodoPago;

    ofstream archivo("recibos.txt", ios::app);
    if (!archivo) {
        cout << "Error al abrir el archivo de recibos.\n";
        return;
    }
    do{
        switch(metodoPago){
            case 't':{
                // Pago con tarjeta: obtener fecha y hora actual
                time_t now = time(0);
                char sel;
                tm *ltm = localtime(&now);

                cout << "\n--- Recibo Final ---\n";
                archivo << "\n--- Recibo Final ---\n";
                for (int i = 0; i < cantidad; i++) {
                    cout << nombres[i] << " x" << cantidades[i] << " - $"
                        << fixed << setprecision(2) << precios[i] * cantidades[i] << endl;
                    archivo << nombres[i] << " x" << cantidades[i] << " - $"
                            << fixed << setprecision(2) << precios[i] * cantidades[i] << endl;
                }
                cout << "Subtotal: $" << fixed << setprecision(2) << totalVentas << endl;
                cout << "IVA (16%): $" << fixed << setprecision(2) << totalVentas * iva << endl;
                cout << "TOTAL: $" << fixed << setprecision(2) << totalVentas * (1+iva) << endl << endl;
                archivo << "Subtotal: $" << fixed << setprecision(2) << totalVentas << endl;
                archivo << "IVA (16%): $" << fixed << setprecision(2) << totalVentas * iva << endl;
                archivo << "TOTAL: $" << fixed << setprecision(2) << totalVentas * (1 + iva) << endl;
                cout << "Deseas realizar el pago a meses sin intereses? [s/n] ";
                cin >> sel;
                do{
                    switch(sel){
                        case 'n':
                            cout << "Fecha y hora del pago: " 
                                << 1900 + ltm->tm_year << "-" 
                                << 1 + ltm->tm_mon << "-" 
                                << ltm->tm_mday << " "
                                << ltm->tm_hour << ":" 
                                << ltm->tm_min << ":" 
                                << ltm->tm_sec << endl;
                            cout << "------------------------\n";
                            archivo << "Fecha y hora del pago: "
                                    << 1900 + ltm->tm_year << "-" 
                                    << 1 + ltm->tm_mon << "-" 
                                    << ltm->tm_mday << " "
                                    << ltm->tm_hour << ":" 
                                    << ltm->tm_min << ":" 
                                    << ltm->tm_sec << endl;
                            archivo << "------------------------\n";
                        break;
                        case 's':
                            int mes;
                            cout << "Selecciona los meses:\n";
                            cout << "1 - 3 meses sin intereses\n";
                            cout << "2 - 6 meses sin intereses\n";
                            cout << "3 - 9 meses sin intereses\n";
                            cin >> mes;
                            float pagar = ((totalVentas * (1+iva)) / (mes*3));
                            cout << "Pagaras " << pagar << " al mes" << endl;
                            archivo << "Pagaras " << pagar << " al mes" << endl;
                    }
                }while(sel != 's' && sel != 'n');
            }
            break;
            case 'e': {
                // Pago en efectivo
                float efectivo;
                cout << "TOTAL: $" << fixed << setprecision(2) << totalVentas * (1+iva) << endl;
                do {
                    cout << "Ingrese la cantidad en efectivo: ";
                    cin >> efectivo;
                    if (efectivo < totalVentas) {
                        cout << "Cantidad insuficiente. Faltan $" << fixed << setprecision(2) << (totalVentas - efectivo) << endl;
                    }
                } while (efectivo < totalVentas);

                float cambio = efectivo - totalVentas * (1 + iva);

                cout << "\n--- Recibo Final ---\n";
                archivo << "\n--- Recibo Final ---\n";
                for (int i = 0; i < cantidad; i++) {
                    cout << nombres[i] << " x" << cantidades[i] << " - $"
                        << fixed << setprecision(2) << precios[i] * cantidades[i] << endl;
                }
                cout << "Subtotal: $" << fixed << setprecision(2) << totalVentas << endl;
                cout << "IVA (16%): $" << fixed << setprecision(2) << totalVentas * iva << endl;
                cout << "TOTAL: $" << fixed << setprecision(2) << totalVentas * (1+iva) << endl;
                cout << "Efectivo recibido: $" << fixed << setprecision(2) << efectivo << endl;
                cout << "Cambio: $" << fixed << setprecision(2) << cambio << endl;
                cout << "------------------------\n";
                archivo << "Subtotal: $" << fixed << setprecision(2) << totalVentas << endl;
                archivo << "IVA (16%): $" << fixed << setprecision(2) << totalVentas * iva << endl;
                archivo << "TOTAL: $" << fixed << setprecision(2) << totalVentas * (1+iva) << endl;
                archivo << "Efectivo recibido: $" << fixed << setprecision(2) << efectivo << endl;
                archivo << "Cambio: $" << fixed << setprecision(2) << cambio << endl;
                archivo << "------------------------\n";
            }
            break;
            default:
                cout << "Método de pago no válido.\n";
            break;
        }
    }while(metodoPago != 't' && metodoPago != 'e');
}

void mostrarInventario(int inv[]){
    char opc;
    for(int i = 0; i < MAX_PRODUCTOS; i++){
        cout << i+1 << ". " << productos[i][0];
        cout << " ($" << productos[i][1] << ") ";
        cout << "Cantidad: " << inv[i] << endl;

        if(inv[i] <= 5){
            cout << "No cuenta con suficientes artículos" << endl;
            do{
                cout << "Deseas rellenar? [s/n]\n";
                cin >> opc;
                switch(opc){
                    case 's':
                        inv[i] = MAX_CANTIDAD;
                        i = -1;
                        break;
                    case 'n':
                        cout << "No se rellenaron los artículos" << endl;
                        break;
                    default:
                        cout << "Opcion no valida\n";
                        break;
                }
            }while(opc != 's' && opc != 'n');
            
        }
    }
}