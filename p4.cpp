/*

Davices - u30
David Rodríguez Marco - 2ºB
David Tanarro de las Heras - 2ºB

*/

#include <iostream>
#include <string>
#include "Arbin.h"


using namespace std;

void imprimirBonito(Arbin <string> &a, int prof);
bool esVacio(Arbin <string> &a);
long int stringToInteger(string num);

int main() {
			Arbin <string> aIz_aIz ("OP"); // Ramas de la izquierda
			Arbin <string> aIz_aDr("LOOP");
		Arbin <string> aIz(aIz_aIz, "LOOP", aIz_aDr); // Izquierda
			Arbin <string> aDr_aIz("OP");
				Arbin <string> aDr_aDr_aIz("OP"); // Ramas de la derecha
				Arbin <string> aDr_aDr_aDr("OP");
			Arbin <string> aDr_aDr(aDr_aDr_aIz, "LOOP", aDr_aDr_aDr);
		Arbin <string> aDr(aDr_aIz, "LOOP", aDr_aDr); // Derecha

	Arbin <string> a(aIz, "BEGIN", aDr); // Raiz

	imprimirBonito(a, 0);
	
	return 0;
}

void imprimirBonito(Arbin <string> &a, int prof) {

	// Mostraremos si la raiz no esta vacia y si su hijo izquierdo ó si su hijo derecho no estan "vacios" por sus respectivas ramas
	if (!a.esVacio()) {
		// Mostrar identacion
		for (int i = 0; i < prof * 2; i++)
			cout << ' ';
		cout << a.raiz() << "\n";

		if (a.raiz() != "OP" && !esVacio(a.hijoIz())) { // sigo por el hijo izquierdo
			imprimirBonito(a.hijoIz(), prof + 1);
		}
		if (a.raiz() != "OP" && !esVacio(a.hijoDr())) { // sigo por el hijo derecho
			imprimirBonito(a.hijoDr(), prof + 1);
		}
	}

}

bool esVacio(Arbin <string> &a) {
	if (a.esVacio())
		return true;
	else
		if (a.raiz() == "OP")
			return false;
		else {
			if (!esVacio(a.hijoIz()))
				return false;
			else if (!esVacio(a.hijoDr()))
				return false;
			else
				return true;
		}
}

long int stringToInteger(string num) {
	long int numero = 0;
	for (unsigned i = 0; i < num.length(); i++)
		numero = numero * 10 + (num[i] - 48);
	return numero;
}

