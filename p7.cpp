/*

Davices - u30
David Rodríguez Marco - 2ºB
David Tanarro de las Heras - 2ºB

*/
#include <iostream>
#include "TreeMap.h"

using namespace std;

bool realizaTransaccion(TreeMap<string, int>& clientes, string origen, string destino, int cantidad) {
	bool transaccionRealizada;
	int nuevaCantidadOrig, nuevaCantidadDest;

	if (origen != "*")
		nuevaCantidadOrig = clientes.at(origen) - cantidad;
	else
		nuevaCantidadOrig = 0; // La nueva cantidad de * sera 0

	if (destino != "*")
		nuevaCantidadDest = clientes.at(destino) + cantidad;
	else
		nuevaCantidadDest = 0; // La nueva cantidad de * sera 0

	if (nuevaCantidadOrig < 0 || nuevaCantidadDest < 0)
		transaccionRealizada = false;
	else {
		transaccionRealizada = true;
		if (origen != destino) {
			clientes[origen] = nuevaCantidadOrig;
			clientes[destino] = nuevaCantidadDest;
		}
	}

	return transaccionRealizada;
}

int main() {
	int lineas;

	while (cin >> lineas && lineas > 0) {

		TreeMap<string, int> clientes; // Nombre, cantidad

		for (int j = 0; j < lineas; j++) {
			string origen, destino;
			int cantidad;

			// cin >> origen >> destino >> cantidad; // Leemos la linea a analizar

			if (cin >> origen && cin >> destino && cin >> cantidad && cantidad >= 1) {
				if (!clientes.contains(origen))
					clientes.insert(origen, 0);
				if (!clientes.contains(destino))
					clientes.insert(destino, 0);

				bool transaccionRealizada = realizaTransaccion(clientes, origen, destino, cantidad);

				if (!transaccionRealizada) {
					cout << j + 1 << " " << origen << " necesita " << cantidad - clientes.at(origen) << " de " << cantidad; /*Cantidad menos lo que tenga Luis*/
					if (cantidad > 1)
						cout << " Euros";
					else
						cout << " Euro";
					cout << endl;
				}
			}
		}

		// Mostrar clientes
		for (TreeMap<string, int>::ConstIterator cli = clientes.cbegin(); cli != clientes.cend(); cli++){
			if (cli.key() != "*" && cli.value() > 0)
				cout << cli.key() << " " << cli.value() << endl;
		}
		cout << endl;
		
		/*
		// Borrar clientes
		while (!clientes.empty())
			clientes.erase(clientes.cbegin().key());
		*/
	}

	//system("pause");
	return 0;
}
