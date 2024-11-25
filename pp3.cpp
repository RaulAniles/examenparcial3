//Raúl Esteban Aniles Macias 222802
#include <iostream>
#include <string>
#include "inventario.h"

using namespace std;

int main() { 
    string nombres[MAX_PRODUCTOS];
    float precios[MAX_PRODUCTOS];
    int cantidades[MAX_PRODUCTOS] = {0};  // Inicializamos las cantidades a 0
    int cantidadInv[MAX_PRODUCTOS];
    //Utilizo la función fill() para rellenar los valores del inventario a su máxima cantidad
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

                    if (cantidad <= 0) {
                        cout << "Cantidad no válida. Intente de nuevo.\n";
                        continue;  // Saltamos si la cantidad no es válida
                    }

                    if (cantidad > cantidadInv[numProducto-1]){
                        cout << "No hay stock suficiente.\n";
                        continue;
                    }

                    // Guardamos el producto seleccionado
                    nombres[cont] = productos[numProducto - 1][0];
                    /* En esta parte utilizo la función stof() que sirve para  
                    convertir los datos string a float */
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
