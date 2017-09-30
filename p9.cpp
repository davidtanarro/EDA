/*
	David Tanarro
	David Rodriguez
	u30 "Davices"
*/

#include <iostream>
#include <string>
#include "Arbin.h"
#include "List.h"
#include "TreeMap.h"

using namespace std;

int num_linea = 1;

class Agenda
{
public:
	struct Cita
	{
		int comienzo;
		int fin;
		string nombre;
	} infoCitas;
	TreeMap<int, infoCitas> listadoCitas;
	int id;

	Agenda(){
		TreeMap<int, infoCitas> listadoCitas = TreeMap<int, infoCitas>();
		id = 0;
	}

	int cita(int comienzo, int fin, string nombre){
		if (fin - comienzo > 0){
			infoCita citacion;
			citacion.comienzo = comienzo;
			citacion.fin = fin;
			citacion.nombre = nombre;
			listadoCitas.insert(id, citacion);
			id++;
		}
	}

	void muestra(int id){
		bool encontrado = false;
		TreeMap<int, infor_cita>::Iterator i = listaCitas.begin();
		while (i != listaCitas.end() && !encontrado){
			if (i.key() == id){
				encontrado = true;
				cout << i.value().comienzo << " " << i.value().final << " " << i.value().nombre << endl;
			}
			else i++;
		}
		if (!encontrado) cout << "ERROR" << endl;
	}
	List<int> consulta(int hora){
		List<int> listaIds = List<int>();
		for (TreeMap<int, infor_cita>::Iterator i = listaCitas.begin(); i != listaCitas.end(); ++i){
			if (i.value().comienzo <= hora && i.value().final > hora)
				listaIds.push_back(i.key());
		}

		return listaIds;
	}

	List<int> todas(){
		List<int> listaTodasConsultas = List<int>();
		for (TreeMap<int, infor_cita>::Iterator i = listaCitas.begin(); i != listaCitas.end(); ++i)
			listaTodasConsultas.push_back(i.key());

		return listaTodasConsultas;
	}
	void muestraLista(List<int> lista){
		while (!lista.empty()){
			cout << lista.front() << " ";
			lista.pop_front();
		}
		cout << endl;
	}
	

private:

	
}

int main()
{
	int bloques;
	int i = 0;
	cin >> bloques;
	cin.ignore();

	while (i<bloques)
	{
		Agenda a;
		num_linea++;
		cout << "bloque #" << i + 1 << endl;
		string instruccion;
		cin >> instruccion;

		while (instruccion != "fin")
		{
			int comienzo, fin, hora, id;
			string nombre;

			if (instruccion == "cita")
			{
				cin >> comienzo >> fin;
				cout << num_linea << ": ";
				getline(cin, nombre);
				a.cita(comienzo, fin, nombre);
			}
			else if (instruccion == "consulta")
			{
				cin >> hora;
				cout << num_linea << ":";
				mostrar(a.consulta(hora));
			}
			else if (instruccion == "muestra")
			{
				cin >> id;
				cout << num_linea << ": ";
				cout << a.muestra(id) << endl;
			}
			else if (instruccion == "libre")
			{
				cin >> comienzo >> fin;
				cout << num_linea << ": ";
				if (a.libre(comienzo, fin))
					cout << "true" << endl;
				else
					cout << "false" << endl;
			}
			else if (instruccion == "borra")
			{
				cin >> id;
				a.borra(id);
			}
			else if (instruccion == "todas")
			{
				cout << num_linea << ":";
				mostrar(a.todas());
			}

			num_linea++;
			cin >> instruccion;
		}
		i++;
	}
	return 0;
}