#include <iostream>
#include <cstdlib>
#include <utility> // pair<A,B>


#ifdef __unix__
#include <sys/time.h> // requiere uso de UNIX
#else
#include <windows.h>
#endif

#include "List.h"
#include "Queue.h"
#include "HashMap.h"

using namespace std;

// codigo para pruebas -- no entra en temario -->

// numero de expansiones
unsigned long estadosExplorados = 0;

// milisegundos
long long timestamp() {
    long long milliseconds = 0;
    #ifdef __unix__ 
    // version unixera
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    milliseconds = te.tv_sec*1000LL + te.tv_usec/1000;
    #else 
    // version windows; MALA RESOLUCION (~ 15 ms) - mejor = mucho mas codigo
    SYSTEMTIME st;
    ::GetSystemTime(&st);
    milliseconds = st.wMilliseconds 
        + 1000LL*(st.wSecond + (60LL*st.wMinute + (60LL*st.wHour)));
    #endif
    return milliseconds;
}

// <-- fin de codigo para pruebas -- no entra en temario

class Puzle {
    int c[9];
    int z;
        
    bool mueveZero(int nextz) {
        if (nextz < 0 
            || nextz > 8
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
    
    static void resuelve(Puzle &p, int prof, HashMap<Puzle, bool> &vistos,
                  List<char> &sol, List<char> &mejor, bool &fin) {                
        estadosExplorados ++;
        if (p.resuelto()) {
            mejor = sol;
            fin = true;
            return;
        }
        
        //cout << "evaluando a profundidad " << prof << "; vistos " <<
        //    vistos.size() << ": ";
        // p.muestra();
        
        if (prof == 0 || fin) {
            return;
        }
            
        for (int i=0; i<4; i++) {
            if (p.mueve("enos"[i])) {
                if ( ! vistos.contains(p)) {
                    // marco
                    vistos[p] = true;
                    // profundizo
                    sol.push_back("enos"[i]);
                    resuelve(p, prof-1, vistos, sol, mejor, fin);
                    sol.pop_back();
                    // desmarco
                    vistos.erase(p);
                }
                // deshago el movimiento
                p.mueve("osen"[i]);
            }
        }
    }
    

    
public:        
    // O(d*d)
    void carga(int *cs) {
        for (int i=0; i<9; i++) {
            c[i] = cs[i];
            if (c[i] == 0) z = i;
        }
    }
    // O(d*d)
    // resuelto: 1 2 3 -> 1 2 3 4 5 6 7 8 9 0
    // en 2d     4 5 6    en 1d
    //           7 8 0
    bool resuelto() const { 
        for (int i=0; i<8; i++) {
            if (c[i] != i+1) return false;
        }
        return c[8] == 0;
    }
    // O(d*d)
    void muestra() const {
        for (int i=0; i<9; i++) {
            cout << c[i] << " ";
        }
        cout << "\n";
    }
    // O(1)
    // indices: 0 1 2
    //          3 4 5  n: -3; s: +3; e: +1; o: -1
    //          6 7 8
    bool mueve(char d) {
        switch (d) {
            case 's': return mueveZero(z+3);
            case 'n': return mueveZero(z-3);
            case 'e': return mueveZero(z+1);
            case 'o': return mueveZero(z-1);
        }
        cerr << "ERROR - imposible mover en direccion " << d << "\n";
        return false;
    }
    List<char> resuelveProfundidad() const {
        List<char> mejor;
        if ( ! resuelto()) {
            List<char> sol;
            HashMap<Puzle, bool> vistos;
            Puzle p = *this;
            bool fin = false;
            for (int prof=1; mejor.empty(); prof ++) {
                Puzle::resuelve(p, prof, vistos, sol, mejor, fin); 
            }
        }
        return mejor;
    }
    
    List<char> resuelveAnchura() const {
        Queue<pair<Puzle, List<char> > > estados;
        pair<Puzle, List<char> > inicial(*this, List<char>());
        estados.push_back(inicial);
        HashMap<Puzle, bool> vistos;

        while ( ! estados.empty()) {
            estadosExplorados ++;
            pair<Puzle, List<char> > actual = estados.front();
            estados.pop_front();

            if (actual.first.resuelto()) {
                return actual.second;
            }

            for (int i=0; i<4; i++) {
                pair<Puzle, List<char> > siguiente = actual;
                if (siguiente.first.mueve("enos"[i]) && ! vistos[siguiente.first]) {
                    // profundizo
                    vistos[siguiente.first] = true;
                    siguiente.second.push_back("enos"[i]);
                    estados.push_back(siguiente);
                }
            }                    
        }
        return List<char>(); // ERROR - no deberia llegar nunca
    }
    
    // codigo para pruebas -- no entra en temario -->
    void resuelveMidiendoTiempos(string name, List<char> (Puzle::*f)(void) const) const {
        unsigned long explorados = estadosExplorados;
        long long tiempo = timestamp();
        
        List<char> resultado = (this->*f)(); // notacion de llamada-a-puntero-a-funcion-miembro
        
        explorados = estadosExplorados - explorados;
        tiempo = timestamp() - tiempo;                
        cout << name << ": " << tiempo << "ms, " << explorados << " estados\n";
        
        for (List<char>::ConstIterator it=resultado.cbegin();
             it != resultado.cend(); it++) {
            cout << *it << " ";
        }
        cout << "\n";
    }
    
    void resuelve() const {
        resuelveMidiendoTiempos("profundidad", &Puzle::resuelveProfundidad);
        resuelveMidiendoTiempos("anchura", &Puzle::resuelveAnchura);
    }
    // <-- fin de codigo para pruebas -- no entra en temario
    
    unsigned int hash() const {
        unsigned int r=0;
        for (int i=0; i<9; i++) r = r*10 + c[i];
        return r;
    }
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
                cout << linea << ": \n";
                p.resuelve();
                cout << "\n";
            } else {
                cerr << "ERROR: ??OP " << op << '\n';
            }
        }
        linea ++;
    }
    return 0;
}