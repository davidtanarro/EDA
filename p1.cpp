#include <iostream>
#include "Stack.h"

using namespace std;

/*
	Davices - u30
	David Rodríguez Marco
	David Tanarro de las Heras
*/

int main() {

	Stack <char> pila;
	string cad = "";

	while (!cin.eof()) {
		getline(cin, cad);
		bool correcto = true;
		size_t i = 0;

		while (correcto && i < cad.length()) {
			if (cad[i] == '(' || cad[i] == '[' || cad[i] == '{' || cad[i] == '<')
				pila.push(cad[i]);
			else if (cad[i] == ')' || cad[i] == ']' || cad[i] == '}' || cad[i] == '>') {

				if (!pila.empty() && pila.top() == '(' && cad[i] == ')')
					pila.pop();
				else if (!pila.empty() && pila.top() == '[' && cad[i] == ']')
					pila.pop();
				else if (!pila.empty() && pila.top() == '{' && cad[i] == '}')
					pila.pop();
				else if (!pila.empty() && pila.top() == '<' && cad[i] == '>')
					pila.pop();
				else
					correcto = false;
			}
			i++;
		}
		if (!pila.empty()) // Pregunta si la pila no esta vacia, es decir, si queda algun simbolo abierto pendiente de cerrar
			correcto = false;

		while (!pila.empty()) // Vaciamos la pila
			pila.pop();

		
		if (!cin.eof()){
			if (correcto)
				cout << "YES" << endl;
			else
				cout << "NO" << endl;
		}

	}

	// system("pause");

    return 0;
}

/*
// pila vacia, 0 errores: listos para empezar
Stack<char> s;
int errors = 0;

while (!cin.eof()) {
char c = cin.get();

// si c es
//    - un paréntesis, llave, mayor-que o corchete de apertura, lo apila
//    - un paréntesis, llave, menor-que o corchete de cierre,
//         si cierra bien con el último apilado, desapila el último
//         y si no, apunta 1 error
//    - un fin-de-línea, y
//         si la pila está vacía y hay 0 errores, muestra YES
//         y si no, muestra NO
//         (y en ambos casos vacía la pila y hace errores=0, para la siguiente vuelta)
//    - todo lo demás, lo ignora
}

// en los casos de prueba, siempre hay un '\n' como último caracter
*/
