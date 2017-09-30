/*

Davices - u30
David Rodríguez Marco - 2ºB
David Tanarro de las Heras - 2ºB

*/
#include <iostream>
#include <string>
#include <stdlib.h>

#include "TreeMap.h"

using namespace std;

struct Nada {};

// Parseamos el texto del quijote y lo insertamos en el "TreeMap<string, Nada> tmap"
TreeMap<string, int> parseaTexto(string texto) {
	TreeMap<string, int> tmap;
	int posIni = 0, posFin = 0, finalizacion = texto.length(); int valor = 0;

	while (posFin <= finalizacion) {
		if (texto[posFin] == ' ') {
			//cout << "Muestra: " << texto.substr(posIni, posFin-posIni) << "FinDeLinea" << endl;
			tmap.insert(texto.substr(posIni, posFin - posIni), valor);
			posIni = posFin + 1;
		}
		posFin++;
	}
	//cout << "Muestra: " << texto.substr(posIni, (int)texto.length()) << "FinDeLinea" << endl;
	tmap.insert(texto.substr(posIni, finalizacion), valor);

	return tmap;
}

bool contieneTodas(const TreeMap<string, int>& pajar, const TreeMap<string, int>& agujas) {
	TreeMap<string, int>::ConstIterator iter = agujas.cbegin();
	
	while (iter != agujas.cend()) {
		if (!pajar.contains(iter.key()))
			return false;
		iter++;
	}

	return true;
}

int main() {
	TreeMap<string, int> pajar, agujas;

	int nCasos;
	cin >> nCasos;
	cin.get(); // cin.sync();
	for (int i = 0; i < nCasos; i++) {
		string texto;
		getline(cin, texto); // Leemos el texto del quijote 
		
		pajar = parseaTexto(texto);
		
		int q;
		cin >> q;
		cin.get(); // cin.sync();
		for (int j = 0; j < q; j++) {
			string linea;
			getline(cin, linea); // Leemos la linea a analizar

			agujas = parseaTexto(linea);

			if (contieneTodas(pajar, agujas))
				cout << "YES" << endl;
			else
				cout << "NO" << endl;

		}
	}

	//system("pause");
	return 0;
}
