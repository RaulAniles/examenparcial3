#ifndef INVENTARIO_H
#define INVENTARIO_H
#endif

#include <iostream>
#include "ventas.h"
using namespace std;

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