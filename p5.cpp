/*

Davices - u30
David Rodríguez Marco - 2ºB
David Tanarro de las Heras - 2ºB

*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <sstream>

#include "Arbin.h"

using namespace std;

// lee a un arbol un texto que cumple la gramatica 
// ARBOL ::= ("VBOX"|"HBOX") ARBOL{0,2} END | RECT
// RECT  ::= INT{1,4} "x" INT{1,4}
// INT   ::= "0"|..."9"
Arbin<string> procesa(string actual) {
    Arbin<string> iz, dr;
    string siguiente;   
    if (actual[0] > '9') { // VBOX o HBOX
        while (cin >> siguiente) {
            if (siguiente == "END") {
                break;
            }                       
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

struct Rect {
	int width, high;

	Rect(int w, int h) : width(w), high(h) {}

	Rect(string s) {
		int i = 0;
		while (s[i] != 'x')
			i++;

		string coef1 = s.substr(0, i), coef2 = s.substr(i + 1, s.size() - i);
		width = atoi(coef1.c_str());
		high = atoi(coef2.c_str());
	}

	void sumaW(const Rect &rect){
		high += rect.high;
		(width > rect.width) ? width = width : width = rect.width;
	}

	void sumaH(const Rect &rect){
		width += rect.width;
		(high > rect.high) ? high = high : high = rect.high;
	}

	void mostrarTamanio() {
		cout << width << "x" << high << endl;
	}
};

Rect calcula(const Arbin<string> a) {
	if (!a.esVacio()) {
		if ((a.raiz()[0] == 'V') || a.raiz()[0] == 'H') {
			Rect izq = calcula(a.hijoIz());
			Rect dr = calcula(a.hijoDr());
			Rect marco(0, 0);
			if (a.raiz()[0] == 'V') {
				marco.sumaW(izq);
				marco.sumaW(dr);
			}
			else {
				marco.sumaH(izq);
				marco.sumaH(dr);
			}

			return marco;
		}
		else {
			Rect nodo(a.raiz());
			return nodo;
		}
	}

	Rect vacio(0, 0);
	return vacio;
}

int main() {
    int n;
    cin >> n;
    for (int i=0; i<n; i++) {
        string s;
        cin >> s;
        Arbin<string> a = procesa(s);
        // 
        // y aqui usas recursion sobre 'a' para 
        // calcular su ancho y alto finales, y los muestras
        //
		calcula(a).mostrarTamanio();

    }
    return 0;
}
