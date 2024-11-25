#ifndef INVENTARIO_H
#define INVENTARIO_H
#endif

#include <iostream>
#include "ventas.h"
using namespace std;

void mostrarInventario(int inv[]){
    char opc;

    ofstream arrinv("inventario.txt", ios::app);
    if (!arrinv) {
        cout << "Error al abrir el archivo de inventario.\n";
        return;
    }

    cout << "-----------------------------" << endl;
    arrinv << "-----------------------------" << endl;

    for(int i = 0; i < MAX_PRODUCTOS; i++){
        cout << i+1 << ". " << productos[i][0];
        cout << " ($" << productos[i][1] << ") ";
        cout << "Cantidad: " << inv[i] << endl;

        arrinv << i+1 << ". " << productos[i][0];
        arrinv << " ($" << productos[i][1] << ") ";
        arrinv << "Cantidad: " << inv[i] << endl;

        if(inv[i] <= 5){
            cout << endl;
            cout << "No cuenta con suficientes artículos" << endl;
            do{
                cout << "Deseas rellenar? [s/n]\n";
                cin >> opc;
                switch(opc){
                    case 's':{
                        inv[i] = MAX_CANTIDAD;
                        arrinv << endl;
                        cout << "Se rellenó el inventario para " << productos[i][0] << endl;
                        arrinv << "Se rellenó el inventario para " << productos[i][0] << endl;
                        i = -1;
                        break;
                    }
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
    cout << "-----------------------------" << endl;
    arrinv << "-----------------------------" << endl;
}