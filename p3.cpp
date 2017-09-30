/*
Pareja: Davices
David Tanarro de las Heras
David Rodriguez Marco
*/

#include <iostream>
#include <string>
#include "Stack.h"
#include "Queue.h"
#include "Deque.h"

using namespace std;

const int MAX_BILLETES = 1000;
const int MAX_VILLANOS = 10;

struct tSuma{
	int sumaTotal;
	int sumandos[MAX_BILLETES];
	int numSumandos;
};

int main() {
	Deque <int> dobleCola;

	int numBilletes, numVillanos, billete;
	
	while (cin >> numBilletes >> numVillanos) {
		if ((1 <= numBilletes && numBilletes <= MAX_BILLETES) && (1 <= numVillanos && numVillanos <= MAX_VILLANOS)) {
			string tipo;
			cin >> tipo;

			// Se insertan los billetes
			for (int i = 0; i < numBilletes; i++) {
				cin >> billete;
				dobleCola.push_back(billete);
			}

			tSuma v[MAX_VILLANOS];
			// Se inicializa a cero la suma de todos los villanos
			for (int i = 0; i < numVillanos; i++) {
				v[i].sumaTotal = 0;
				v[i].numSumandos = 0;
			}

			//----------------------------------------------------------------------------------------------------------------------------------
			// Caso para la pila
			//----------------------------------------------------------------------------------------------------------------------------------
			if (tipo == "pila") {
				int i = (numBilletes - 1) % numVillanos;
				while (!dobleCola.empty()) { // Mientras halla billetes por repartir
					// Guardo el elemento cima de la pila en el array de sumandos del villano correspondiente, la posicion donde lo guardo sera en numSumandos
					v[i].sumandos[v[i].numSumandos] = dobleCola.back();
					// Se lo sumo a la suma total acumulada
					v[i].sumaTotal += v[i].sumandos[v[i].numSumandos];
					// Aumento el contador de sumandos
					v[i].numSumandos++;
					// Extraigo el elemento cima de la pila
					dobleCola.pop_back();
					// Paso al siguiendo villano
					i--;
					if (i < 0)
						i = numVillanos - 1;
				}
			}
			//----------------------------------------------------------------------------------------------------------------------------------
			// Caso para la cola
			//----------------------------------------------------------------------------------------------------------------------------------
			else if (tipo == "cola") {
				int i = 0; //(numBilletes - 1) % numVillanos;
				while (!dobleCola.empty()) { // Mientras halla billetes por repartir
					// Guardo el primer elemento de la cola en el array de sumandos del villano correspondiente, la posicion donde lo guardo sera en numSumandos
					v[i].sumandos[v[i].numSumandos] = dobleCola.front();
					// Se lo sumo a la suma total acumulada
					v[i].sumaTotal += v[i].sumandos[v[i].numSumandos];
					// Aumento el contador de sumandos
					v[i].numSumandos++;
					// Elimino el primer elemento de la cola
					dobleCola.pop_front();
					// Paso al siguiendo villano
					i++;
					if (i > numVillanos-1)
						i = 0;
				}
			}
			// Muestro por pantalla el resultado final
			for (int i = 0; i < numVillanos; i++) {
				cout << v[i].sumaTotal << ":";
				for (int j = 0; j < v[i].numSumandos; j++)
					cout << " " << v[i].sumandos[j];
				cout << endl;
			}
			cout << "---" << endl;
		}
	}

	// system("pause");
	
	return 0;
}