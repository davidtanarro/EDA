#include "List.h"
#include "Arbin.h"
#include "HashMap.h"
#include "TreeMap.h"

using namespace std;

//EJERCICIO 1
bool genealogico(const Arbin<int> &a, int &gener){
    if(a.esVacio()){
        gener=0;
        return true;
    }
    int genIz, genDr;
    if(!genealogico(a.hijoIz(),genIz) || !genealogico(a.hijoDr(),genDr))
        return false;
    if(genIz==0){
        gener=1;
        return true;
    }
    if(genDr==0){
        gener=genIz+1;
        return a.raiz()-a.hijoIz().raiz() >=18;
    }
    if( a.raiz()-a.hijoIz().raiz()<18 || a.raiz()-a.hijoDr().raiz()<20 || a.hijoIz().raiz()-a.hijoDr().raiz()<2)
        return false;
    gener=1+(genIz>genDr? genIz : genDr);
    return true;
}

//EJERCICIO 3
class CiudadMatic{
public:
    CiudadMatic(int ini) : dinero(ini), cont(0) {}
    void nuevoTipo(string tipo, int coste, int imp, int cal){
        tipos.insert(tipo, {coste,imp,cal,TreeMap<int, string>()} );
    }
    void insertaEdificio(string nombre, string tipo){
        if(tipos.at(tipo).coste<=dinero){
            Tipo *t=&(tipos[tipo]);
            ciudad.insert(nombre,{t->calidad,t,cont});
            dinero-=t->coste;
            t->hist.insert(cont,nombre);
            cont++;
        }
    }
    void reparaEdificio(string nombre){
        if(ciudad.at(nombre).tipo->coste/10 <= dinero){
            edificio &e= ciudad[nombre];
            e.estado= e.tipo->calidad;
            dinero-= e.tipo->calidad/10;
        }
    }
    int finTurno(){
        typename HashMap<string, edificio>::Iterator it=ciudad.begin();
        while(it!=ciudad.end()){
            dinero+=it.value().tipo->impuestos;
            if(it.value().estado<1){
                it.value().tipo->hist.erase(it.value().id);
                string aux=it.key();
                it.next();
                ciudad.erase(aux);
            }
            else{
                it.value().estado--;
                it.next();
            }
        }
        return dinero;
    }
    List<string> listaEdificios(string t)const{
        const TreeMap<int, string> &arbol=ciudad.at(t).tipo->hist;
        if(arbol.empty())
            return List<string>();
        List<string>lista;
        TreeMap<int, string>::ConstIterator it=arbol.cbegin();
        while(it!=arbol.cend()){
            lista.push_back(it.value());
            it.next();
        }
        return lista;
    }
private:
    struct Tipo{
        int coste;
        int impuestos;
        int calidad;
        TreeMap<int, string> hist;
    };
    struct edificio{
        int estado;
        Tipo *tipo;
        int id;
    };
    int dinero;
    int cont;
    HashMap<string, Tipo> tipos;
    HashMap<string, edificio> ciudad;
};

int main(){ return 0; }
