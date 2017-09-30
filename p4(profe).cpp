/*

Davices - u30
David Rodríguez Marco - 2ºB
David Tanarro de las Heras - 2ºB

*/
#include <iostream>
#include <cstdlib>
#include "Arbin.h"
#include "Exceptions.h"
#include "List.h" // Tipo devuelto por los recorridos
#include "Queue.h" 

using namespace std;

bool esVacio(const Arbin <string> &a);
void imprimirBonito(const Arbin <string> &a, int prof);

// muestra un arbol en notacion prefija y usando 2 espacios por nivel
//   OJO: no vas a poder, modificando solo este codigo, resolver
//   el problema - necesitas:
//     - o pasar mas parametros 
//        un stringstream para que el hijo se vaya mostrando, 
//        y devolver un bool si realmente debia mostrarse
//     - o una funcion recursiva auxiliar 
//        para saber si una rama se debe o no mostrar
//        (mas sencillo y recomendado, aunque menos eficiente, porque
//        evalua nodos varias veces)
void pre(int prof, const Arbin<string> &a) {
    if ( ! a.esVacio()) {

		if (!esVacio(a) || a.raiz() == "BEGIN") {
			cout << string(prof * 2, ' ') << a.raiz() << "\n";
			if (a.raiz()[0] != 'O') {
				pre(prof + 1, a.hijoIz());
				pre(prof + 1, a.hijoDr());
				// en nodos no-OP, inserta un END 
				if (a.raiz()[0] != 'O')
					cout << string(prof * 2, ' ') << "END\n";
			}
		}
    }
}

// lee un programa a un arbol
//    asume que actual == "BEGIN" en primera llamada
//    y que nodos BEGIN y LOOP se cierran con END (mientras que OP no)
Arbin<string> procesa(string actual) {
    Arbin<string> iz, dr;
    string siguiente;
    
    if (actual[0] != 'O') {
        while (cin >> siguiente) {
            if (siguiente == "END") {
                break;
            }
            
            // nodos LOOP y OP tienen una <ENE> detras
            string ene;
            cin >> ene;
            siguiente = siguiente + " " + ene;
            
            if (iz.esVacio()) {            
                iz = procesa(siguiente);
            } else if (dr.esVacio()) {
                dr = procesa(siguiente);
            } else {
                cerr << "ERROR : tercer hijo " + siguiente << endl;
            }
        }
    }
    return Arbin<string>(iz, actual, dr);
}

// TUS FUNCIONES AUXILIARES AQUI
bool esVacio(const Arbin <string> &a) {
	if (a.esVacio())
		return true;
	else
		if (a.raiz()[0] == 'O')
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

void imprimirBonito(const Arbin <string> &a, int prof) {
	if (!esVacio(a))
		pre(0, a);
}


int main() {
    int n;
    cin >> n;
    for (int i=0; i<n; i++) {
        string s;
        cin >> s;
        Arbin<string> a = procesa(s);
        // TU CODIGO AQUI
		pre(0, a);
    }
    return 0;
}
