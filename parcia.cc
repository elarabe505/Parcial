#include <iostream>
#include <malloc.h>
using namespace std;

struct clientes {
    int num_cuenta;
    int tipo_cuenta;
    int turno = 1;
    clientes *sig;
};

clientes *cabeza_preferencial = NULL, *cabeza_tradicional = NULL;

void registro();
void ver_fila();
void gestion_filas();
void reasignar_turnos();

int contador_turno = 1;

void registro() {
    clientes *nuevo_cliente = (clientes *)malloc(sizeof(clientes));
    nuevo_cliente->sig = NULL;

    cout << "Ingrese su tipo de cuenta, 1 preferencial y 2 tradicional: " << endl;
    cin >> nuevo_cliente->tipo_cuenta;

    if (nuevo_cliente->tipo_cuenta == 1) {
        cout << "Se agrego a la fila preferencial" << endl << endl;
    } else if (nuevo_cliente->tipo_cuenta == 2) {
        cout << "Se agrego a la fila tradicional" << endl << endl;
    } else {
        cout << "Tipo de cuenta no válida" << endl;
        free(nuevo_cliente);
        return;
    }

    cout << "Ingrese su numero de cuenta:" << endl;
    cin >> nuevo_cliente->num_cuenta;

    
    nuevo_cliente->turno = contador_turno++;

   
    if (nuevo_cliente->tipo_cuenta == 1) {
        if (!cabeza_preferencial) {
            cabeza_preferencial = nuevo_cliente;
        } else {
            clientes *temp = cabeza_preferencial;
            while (temp->sig) {
                temp = temp->sig;
            }
            temp->sig = nuevo_cliente;
        }
    } else {
        if (!cabeza_tradicional) {
            cabeza_tradicional = nuevo_cliente;
        } else {
            clientes *temp = cabeza_tradicional;
            while (temp->sig) {
                temp = temp->sig;
            }
            temp->sig = nuevo_cliente;
        }
    }
}

void ver_fila() {
    int numero_cliente = 1;

    cout << "Fila Preferencial:" << endl;
    for (clientes *temp = cabeza_preferencial; temp; temp = temp->sig) {
        cout << "Cliente " << numero_cliente++ << ": ";
        cout << "Número de cuenta: " << temp->num_cuenta << ", Tipo de cuenta: Preferencial, Turno: " << temp->turno << endl;
    }

    cout << endl;

    numero_cliente = 1;

    cout << "Fila Tradicional:" << endl;
    for (clientes *temp = cabeza_tradicional; temp; temp = temp->sig) {
        cout << "Cliente " << numero_cliente++ << ": ";
        cout << "Número de cuenta: " << temp->num_cuenta << ", Tipo de cuenta: Tradicional, Turno: " << temp->turno << endl;
    }
}

void gestion_filas() {
    int num_clientes_tradicional = 0;
    int num_clientes_preferencial = 0;
    
    for (clientes *temp = cabeza_preferencial; temp; temp = temp->sig) {
        num_clientes_preferencial++;
    }

    for (clientes *temp = cabeza_tradicional; temp; temp = temp->sig) {
        num_clientes_tradicional++;
    }
    
    if (num_clientes_tradicional >= 5 && num_clientes_preferencial <= 2) {
        int contador = 0;
        clientes *anterior_tradicional = NULL;
        clientes *anterior_preferencial = NULL;
    
        for (clientes *temp = cabeza_tradicional; temp; temp = temp->sig) {
            contador++;
            if (contador == 3) {
                
                clientes *cliente_mover = temp;
                if (anterior_tradicional) {
                    anterior_tradicional->sig = temp->sig; 
                } else {
                    cabeza_tradicional = temp->sig;
                }
                
                if (!cabeza_preferencial) {
                    cabeza_preferencial = cliente_mover;
                    cliente_mover->sig = NULL;
                } else {
                    cliente_mover->sig = cabeza_preferencial;
                    cabeza_preferencial = cliente_mover;
                }

                cout << "El cliente " << cliente_mover->num_cuenta << " ha sido movido a la fila preferencial." << endl;
                break;
            }
            anterior_tradicional = temp;
        }
    }
}

void reasignar_turnos() {
    int nuevo_turno = 1;

    for (clientes *temp = cabeza_preferencial; temp; temp = temp->sig) {
        temp->turno = nuevo_turno++;
    }
    
    for (clientes *temp = cabeza_tradicional; temp; temp = temp->sig) {
        temp->turno = nuevo_turno++;
    }
}

int main() {
    int op = 0;

    do {
        cout << "MENU PRINCIPAL" << endl;
        cout << "1. Registro de cliente" << endl;
        cout << "2. Ver registro" << endl;
        cout << "3. Gestionar filas" << endl;
        cout << "4. Salir" << endl;
        cin >> op;

        switch (op) {
            case 1:
                registro();
                break;
            case 2:
                ver_fila();
                break;
            case 3:
                gestion_filas();
                break;
            case 4:
                cout << "Chao vro" << endl;
                break;
            default:
                cout << "Opcion no valida vro" << endl;
                break;
        }

    } while (op != 4);

    return 0;
}