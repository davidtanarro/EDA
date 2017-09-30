#include "List.h"
#include "Arbin.h"
#include "HashMap.h"
#include "TreeMap.h"

using namespace std;

//EJERCICIO 2
void camAux(const Arbin<string> &a, int &corto, string &mejor, int dragones){
    if(a.esVacio())
        return ;
    if(a.raiz()[0]=='P'){
        if( mejor=="" || dragones<corto){
            corto=dragones;
            mejor=a.raiz();
        }
        return ;
    }
    if(a.raiz()[0]=='D')
        dragones++;
    camAux(a.hijoIz(),corto,mejor,dragones);
    camAux(a.hijoDr(),corto,mejor,dragones);
}

string camino(const Arbin<string> &a){
    string ret="";
    int dist;
    camAux(a,dist,ret,0);
    return ret;
}

//EJERCICIO 3
class EspacioMatic{
public:
    EspacioMatic(){}
    void nuevaNave(int id){
        if(naves.contains(id))
            throw ENaveYaExistente();
        naves.insert(id,TreeMap<string, int>());
    }
    void equipaNave(int id, string mod, int nivel){
        if(!naves.at(id).contains(mod))
            naves[id].insert(mod,nivel);
        else{
            int &aux=naves[id][mod];
            if(aux==0){
                if(estro.at(id)==1)
                    estro.erase(id);
                else
                    estro[id]--;
            }
            aux+=nivel;
        }
    }
    bool estropeaNave(int id, string mod){
        if(!naves.at(id).contains(mod) || naves.at(id).at(mod)==0)
            return false;
        if((naves[id][mod]--)==0)
            estro[id]++;
    }
    List<int> navesDefectuosas() const{
        if(estro.empty())
            return List<int>();
        List<int> lista;
        HashMap<int, int>::ConstIterator it = estro.cbegin();
        while(it!=estro.cend()){
            lista.push_back(it.key());
            it.next();
        }
        return lista;
    }
    List<string> modulosNave(int id) const{
        const TreeMap<string, int> &arbol=naves.at(id);
        if(arbol.empty())
            return List<string>();
        List<string> lista;
        TreeMap<string, int>::ConstIterator it=arbol.cbegin();
        while(it!=arbol.cend()){
            lista.push_back(it.key());
            it.next();
        }
        return lista;
    }
private:
    class ENaveYaExistente{};
    HashMap<int, TreeMap<string, int> > naves;
    HashMap<int, int> estro;
};

int main(){ return 0; }
