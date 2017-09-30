/*

David Tanarro
David Rodriguez
Davices - u30

*/

#include <iostream>
#include <cstdlib>

#include "List.h"
#include "HashMap.h"

using namespace std;

class Nada {};

class Puzle {
    int c[9];  // contenido de las 9 casillas
    int z;     // indice del cero
    
    // funcion auxiliar para mover el cero de la casilla z a la casilla nextz
    // devuelve 'false' si no lo consigue
    // 0 1 2   - 2, 5, 8 no pueden moverse al este
    // 3 4 5     0, 3, 6 no pueden moverse al oeste
    // 6 7 8     nadie puede acabar > 8 ó < 0
    bool mueveZero(int nextz) {  
        if (nextz < 0 || nextz > 8
            || (z == 2 && nextz == 3) 
            || (z == 5 && nextz == 6) 
            || (z == 3 && nextz == 2) 
            || (z == 6 && nextz == 5) 
        ) {
            return false;
        }
        c[z] = c[nextz];
        c[nextz] = 0;
        z = nextz;
        return true;
    }
    
    //
    // funcion auxiliar para resolver el 8-puzle, llamada desde resuelve()
    // p - puzle actual
    // prof - profundidad maxima a la que buscar
    // vistos - variantes comprobadas o vistas de un puzle
	// sol - lista de chars con la solucion del puzle
	// mejor - lista de chars con la mejor solucion del puzle
	// fin - fin de la busqueda, ya hemos encontrado la mejor sol
    //
    static void resuelve(Puzle &p, int prof, HashMap<Puzle, bool> &vistos,
		List<char> &sol, List<char> &mejor, bool &fin) { // O (n)
        // si resuelto
		if (p.resuelto()){
			// si solucion mas corta que la mejor
			// if (sol.size() < mejor.size()) // No hace falta hacer la comprobacion ya que la mejor sol va a ser siempre la primera
			mejor = sol;
			fin = true;
			// y luego salgo, porque no tiene sentido seguir buscando
			return;
		}

        // si prof == 0 o hayamos terminado, salgo
		if (prof == 0 || fin)
			return;

        // para cada direccion
		for (int i = 0; i < 4; i++) {
			// intento mover en esa direccion
			if (p.mueve("seno"[i])) {
				// si lo consigo
				// y el resultado no esta en vistos
				if (!vistos.contains(p)) {
					// meto p en vistos / marco
					vistos[p] = true;
					// apilo la direccion de desplazamiento en sol / profundizo
					sol.push_back("seno"[i]);
					// me llamo recursivamente, con prof-1
					resuelve(p, prof - 1, vistos, sol, mejor, fin);
					// desapilo la ultima direccion de sol
					sol.pop_back();
					// desmarco p en vistos
					vistos.erase(p);
				}
				// deshago el movimiento
				p.mueve("nose"[i]);
			}
		}
    }
    
public:

    // otras funciones aqui: carga, mueve, ...
	void carga(int leido[]) { // O(n)
		for (int i = 0; i < 9; i++) {
			c[i] = leido[i];
			if (leido[i] == 0)
				z = i;
		}
	}

	bool mueve(char dir) { // O(1)
		switch (dir){
		case 'n':
			return mueveZero(z - 3);
			
		case 's':
			return mueveZero(z + 3);
			
		case 'e':
			return mueveZero(z + 1);
			
		case 'o':
			return mueveZero(z - 1);
			
		default:
			return false;
		}
	}

	void muestra() const { // O(n) 
		for (int i = 0; i < 9; i++)
			cout << c[i] << " ";
		cout << endl;
	}

	bool resuelto() const { // O(n)
		for (int i = 1; i < 9; i++){
			if (c[i-1] != i)
				return false;
		}
		if (c[8] == 0)
			return true;
		else
			return false;
	}

    // O((d*d) !) , aunque generalmente mucho mucho menos
    List<char> resuelve() const { // O(n)
        List<char> mejor;
        if (!resuelto()) {
            List<char> sol;
            HashMap<Puzle, bool> vistos;
			Puzle p = *this;
			bool fin = false;
            for (int prof = 1; mejor.empty(); prof++) {
				Puzle::resuelve(p, prof, vistos, sol, mejor, fin);
            }
        }
        return mejor;
    }
    
    // necesario para que Puzle pueda ser clave de hashmap
    unsigned int hash() const { // O(n)
        unsigned int r=0;
        for (int i=0; i<9; i++) r = r*10 + c[i];
        return r;
    }
    // necesario para que Puzle pueda ser clave de hashmap
    bool operator==(const Puzle &o) const {
        for (int i=0; i<9; i++) if (o.c[i] != c[i]) return false;
        return true;
    }
};

int main() {
    int n;
    int linea = 1;
    cin >> n;
    for (int i=0; i<n; i++) {
        cout << "bloque #" << (i+1) << '\n';
        Puzle p;
        string op, dir;
        while (cin >> op && op != "fin") {
            linea ++;
            if (op == "carga") {
                int leido[9];
                for (int j=0; j<9; j++) cin >> leido[j];
                // asume que esperas un array de 9 ints
                p.carga(leido);            
            } else if (op == "muestra") { 
                cout << linea << ": ";
                p.muestra();
            } else if (op == "resuelto") { 
                cout << linea << ": ";
                cout << (p.resuelto() ? "true\n" : "false\n");
            } else if (op == "mueve") { 
                cin >> dir; 
                cout << linea << ": ";
                cout << (p.mueve(dir[0]) ? "true\n" : "false\n");
            } else if (op == "resuelve") { 
                cout << linea << ": ";
                List<char> solucion = p.resuelve();
                for (List<char>::ConstIterator it=solucion.cbegin();
					it != solucion.cend(); it++) {
					cout << *it << " ";
                }
                cout << "\n";
            } else {
                cerr << "ERROR: ??OP " << op << '\n';
            }
        }
        linea ++;
    }
    return 0;
}