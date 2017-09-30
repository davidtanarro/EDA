#include <iostream>

using namespace std;

const int TAM = 100;

void cima(int v[], int n, bool &existe, int &p);
bool sube(int v[], int s, int t);
bool baja(int v[], int s, int t);

int main(){
	int numCasos, numDatos, p = -1;
	int v[TAM];
	bool existe;

	cin >> numCasos;
	for (int i = 0; i < numCasos; i++) {
		existe = false;
		cout << "  ";
		cin >> numDatos;
		for (int j = 0; j < numDatos; j++)
			cin >> v[j];
		cima(v, numDatos, existe, p);
		if (existe)
			cout << "Si " << p << endl;
		else
			cout << "No" << endl;
	}

	return 0;
}

void cima(int v[], int n, bool &existe, int &p) {
	int i = 0;

	while (i < n) {
		if (sube(v, 0, i) && baja(v, i, n) && i != 0 && i != n-1) {
			existe = true;
			p = i;
		}
		i++;
	}
}

bool sube(int v[], int s, int t) {
	bool sube = true;

	for (int j = s; j < t; j++)
		if (v[j] >= v[j + 1])
			sube = false;

	return sube;
}

bool baja(int v[], int s, int t) {
	bool baja = true;

	for (int j = s; j < t; j++)
		if (v[j] <= v[j + 1])
			baja = false;

	return baja;
}