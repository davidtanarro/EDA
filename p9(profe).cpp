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

class Agenda
{
public:
	struct infoCitas
	{
		int comienzo;
		int fin;
		string nombre;
	};

	TreeMap<int, infoCitas> listadoCitas;
	int id;

	Agenda(){
		TreeMap<int, infoCitas> listadoCitas = TreeMap<int, infoCitas>();
		id = 0;
	}

	int cita(int comienzo, int fin, string nombre){
		if (fin - comienzo > 0){
			infoCitas citacion;
			citacion.comienzo = comienzo;
			citacion.fin = fin;
			citacion.nombre = nombre;
			listadoCitas.insert(id, citacion);
			id++;
		}
		return id - 1;
	}

	int encuentraCitas(int comienzo, int fin){
		int encontradas = 0;
		for (TreeMap<int, infoCitas>::Iterator i_cita = listadoCitas.begin(); i_cita != listadoCitas.end();i_cita++)
		{
			if (i_cita.value().comienzo < fin && i_cita.value().fin > comienzo)
				encontradas++;
		}
		return encontradas;
	}

	void muestra(int id){
		bool encontrado = false;
		TreeMap<int, infoCitas>::Iterator i_cita = listadoCitas.begin(); //Recorremos las citas segun el id que le pasemos.
		while (i_cita != listadoCitas.end() && !encontrado)
		{
			if (i_cita.key() == id){
				encontrado = true;
				cout << i_cita.value().comienzo << " " << i_cita.value().fin << i_cita.value().nombre << endl;
			}
			else i_cita++;
		}
		if (!encontrado) cout << "ERROR" << endl;
	}
	List<int> consulta(int hora){
		List<int> listaIds = List<int>();
		for (TreeMap<int, infoCitas>::Iterator i = listadoCitas.begin(); i != listadoCitas.end(); ++i){
			if (i.value().comienzo <= hora && i.value().fin > hora)
				listaIds.push_back(i.key());
		}

		return listaIds;
	}

	List<int> todas(){
		List<int> listaTodasConsultas = List<int>();
		for (TreeMap<int, infoCitas>::Iterator i = listadoCitas.begin(); i != listadoCitas.end(); ++i)
			listaTodasConsultas.push_back(i.key());

		return listaTodasConsultas;
	}
	void muestraLista(List<int> lista){
		while (!lista.empty()){
			cout << " " << lista.front();
			lista.pop_front();
		}
		cout << endl;
	}
	void borra(int id){
		if (listadoCitas.contains(id)){
			listadoCitas.erase(id); //Borramos la cita buscando por su id.
		}
	}
	bool libre(int comienzo, int fin){
		if (encuentraCitas(comienzo, fin) == 0){
			return true;
		}
		else {
			return false;
		}
	}
};

int main()
{
	int bloques;
	int num_linea = 1;
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
				cout << a.cita(comienzo, fin, nombre);
				cout << endl;
			}
			else if (instruccion == "consulta")
			{
				cin >> hora;
				cout << num_linea << ":";
				a.muestraLista(a.consulta(hora));
			}
			else if (instruccion == "muestra")
			{
				cin >> id;
				cout << num_linea << ": ";
				a.muestra(id);
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
				a.muestraLista(a.todas());
			}
			num_linea++;
			cin >> instruccion;
		}
		i++;
	}
	return 0;
}