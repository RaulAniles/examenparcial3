#ifndef VENTAS_H
#define VENTAS_H
#endif

#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <string>
using namespace std;

const int MAX_PRODUCTOS = 5;
const int MAX_CANTIDAD = 20;
string oal;
const string productos[MAX_PRODUCTOS][2] = {{"Pan", "1.50"},
    {"Leche", "2.00"}, 
    {"Huevos", "3.00"},
    {"Fruta", "0.75"}, 
    {"Verdura", "0.50"}};

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
                            cout << "------------------------\n";
                            archivo << "Pagaras " << pagar << " al mes" << endl;
                            archivo << "------------------------\n";
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
