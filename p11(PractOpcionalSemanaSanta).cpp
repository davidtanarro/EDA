/*

David Tanarro de las Heras - 2ºB

De los ejemplos de los archivos:
	sample.in: Son correctos todos los resultados.
	diez.in: Son correctos los 9 primeros resultados.
	mil.in: Obtiene 393 resultados pero no todos son correctos.

*/

#include <iostream>
#include <string>
#include "Stack.h"

using namespace std;

const int DIM = 10;
// Instruccion y numero del coste
struct cmd {
	string inst, num;
};

class polinomio {
public:
	// Coeficientes del polinomio, exponente con el que trabajamos actualmente
	long int coef[DIM], exp;

	void inicializaPolinomio() {
		exp = 0;
		for (int i = 0; i < DIM; i++)
			coef[i] = 0;
	}
	void mostrarPolinomio() {
		int maxExp = 0;
		// Busqueda lineal del maximo exponente
		for (int i = DIM - 1; i > 0 && maxExp == 0; i--)
			if (coef[i] != 0)
				maxExp = i;

		for (int i = maxExp; i >= 2; i--)
			if (coef[i] != 0) {
				(i == maxExp) ? cout << "" : cout << "+";
				(coef[i] == 1) ? cout << "n^" << i : cout << coef[i] << "*n^" << i;
			}
		if (coef[1] != 0) {
			(1 == maxExp) ? cout << "" : cout << "+";
			(coef[1] == 1) ? cout << "n" : cout << coef[1] << "*n";
		}
		if (0 == maxExp) cout << coef[0];
		else if (coef[0] != 0) cout << "+" << coef[0];
		cout << endl;
	}
};
long int stringToInteger(string num);
void sumaPol(polinomio& pol1, polinomio& pol2);
void multPol(polinomio& pol, long int num);

int main() {
	// Si se quisiera acceder a un dato de alguna pila y esta se encuentra vacia entonces falla el programa
	bool fallo = false;
	// Numero de casos de prueba
	int nBegin;
	// Comando leido y pila de comandos
	cmd aux;
	Stack <cmd> pila;
	/* Es una variable que indica si tiene sentido bajar de nivel de complejidad o no.
	Si a un "LOOP N" le precede un "LOOP CONSTANTE", entonces "LOOP CONSTANTE" trabaja al mismo nivel de complejidad que el "LOOP N" */
	bool c = false;
	// Polinomio con que actualmente trabajamos y pila de polinomios guardados
	polinomio pol;
	pol.inicializaPolinomio();
	Stack <polinomio> pilaPol;

	cin >> nBegin;
	int i = 0;
	while (i < nBegin && !fallo) {
		cin >> aux.inst;
		
		if (aux.inst == "BEGIN")
			pila.push(aux);
		else if (aux.inst == "OP") {
			cin >> aux.num;
			if (c)
				pol.coef[pol.exp-1] += stringToInteger(aux.num);
			else
				pol.coef[pol.exp] += stringToInteger(aux.num);
		}
		else if (aux.inst == "LOOP") {
			cin >> aux.num;
			pila.push(aux);
			if (aux.num == "n") // Caso "LOOP N"
				pol.exp++;
			else {	// Caso "LOOP CONSTANTE"
				// Guardo el resultado acumulado y dejo los coeficientes a cero pero mantengo el exponente (nivel de complijidad)
				pilaPol.push(pol);
				for (int i = 0; i < DIM; i++)
					pol.coef[i] = 0;
			}
		}
		else if (aux.inst == "END")
			if (!pila.empty()) {

				aux = pila.top();
				pila.pop();
				if (aux.inst == "BEGIN") {
					i++;
					cout << "Program #" << i << endl << "Runtime = ";
					pol.mostrarPolinomio();
					cout << endl;
					pol.inicializaPolinomio();
					c = false;
				}
				else if (aux.inst == "LOOP") {
					if (aux.num == "n") { //************** Caso "LOOP N" ***************************
						pol.exp--;
						if (pila.top().inst == "LOOP" && pila.top().num != "n") {
							pol.exp++;
							c = true;
						}
					}
					else { //************************** Caso "LOOP CONSTANTE" **********************
						multPol(pol, stringToInteger(aux.num));
						if (c) {
							pol.exp--;
							c = false;
							if (pila.top().inst == "LOOP" && pila.top().num != "n") {
								pol.exp++;
								c = true;
							}
						}
						if (!pilaPol.empty()) {
							polinomio polAux = pilaPol.top();
							sumaPol(pol, polAux);
							pilaPol.pop();
						}
						else
							fallo = true;
					} //*************************************************************************
				}

			}
			else
				fallo = true;
		else //	Comando desconocido
			fallo = true;
	}
	
	return 0;
}

long int stringToInteger(string num) {
	long int numero = 0;
	for (unsigned i = 0; i < num.length(); i++)
		numero = numero * 10 + (num[i] - 48);
	return numero;
}

void sumaPol(polinomio& pol1, polinomio& pol2) {
	for (int i = 0; i < DIM; i++)
		pol1.coef[i] += pol2.coef[i];
}

void multPol(polinomio& pol, long int num) {
	for (int i = 0; i <= pol.exp; i++)
		pol.coef[i] = pol.coef[i] * num;
}
