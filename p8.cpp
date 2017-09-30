/*
	David Tanarro
	David Rodriguez
	u30 "Davices"

*/

#include <iostream>
#include "Deque.h"
#include "HashMap.h"

using namespace std;

class Consulta {
private:
	HashMap<string, Deque<string> > medicos; // nombreMedico y una cola doble de pacientes
	HashMap<string, int> pacientes; // nombrePacientes y numDeCitas
public:
	void nuevoMedico(string nombreMedico) {  // Complejidad O(1)
		if (!medicos.contains(nombreMedico)) {
			medicos.insert(nombreMedico, Deque<string>());
		}
	}

	void pideConsulta(string nombrePaciente, string nombreMedico) {  // Complejidad O(1)
		if (medicos.contains(nombreMedico)) { // && si el paciente no esta en la cola
			medicos[nombreMedico].push_back(nombrePaciente);
			pacientes[nombrePaciente]++;
		}
	}

	void pideConEnchufe(string nombrePaciente, string nombreMedico) {  // Complejidad O(1)
		if (medicos.contains(nombreMedico)) {
			medicos[nombreMedico].push_front(nombrePaciente);
			pacientes[nombrePaciente]++;
		}
	}

	bool tienePacientes(string nombreMedico) { // Complejidad O(1)
		return medicos.contains(nombreMedico) && !medicos[nombreMedico].empty();
	}

	string siguientePaciente(string nombreMedico) { // Complejidad O(1)
		if (tienePacientes(nombreMedico))
			return medicos[nombreMedico].front();
		else
			return "NADIE";
	}

	void atiendePaciente(string nombreMedico) { // Complejidad O(1)
		if (tienePacientes(nombreMedico)) {
			pacientes[siguientePaciente(nombreMedico)]--;
			medicos[nombreMedico].pop_front();
		}
	}

	int numConsultas(string nombrePaciente) {  // Complejidad O(1)
		if (!pacientes.contains(nombrePaciente))
			pacientes.insert(nombrePaciente, 0);
		return pacientes[nombrePaciente];
	}
};

int main() {
	Consulta c;
	int bloques;
	int i = 0;

	cin >> bloques;
	if (bloques > 0)
		cout << "bloque #" << i + 1 << endl;
	while (i < bloques) {
		string instruc;
		cin >> instruc;

		if (instruc == "nuevoMedico") {
			string nombreMedico;
			cin >> nombreMedico;
			c.nuevoMedico(nombreMedico);
		}
		else if (instruc == "pideConsulta") {
			string nombrePaciente, nombreMedico;
			cin >> nombrePaciente >> nombreMedico;
			c.pideConsulta(nombrePaciente, nombreMedico);
		}
		else if (instruc == "pideConEnchufe") {
			string nombrePaciente, nombreMedico;
			cin >> nombrePaciente >> nombreMedico;
			c.pideConEnchufe(nombrePaciente, nombreMedico);
		}
		else if (instruc == "siguientePaciente") {
			string nombreMedico;
			cin >> nombreMedico;
			cout << c.siguientePaciente(nombreMedico) << endl;
		}
		else if (instruc == "tienePacientes") {
			string nombreMedico;
			cin >> nombreMedico;
			if (c.tienePacientes(nombreMedico))
				cout << "true" << endl;
			else
				cout << "false" << endl;
		}
		else if (instruc == "atiendeConsulta") {
			string nombreMedico;
			cin >> nombreMedico;
			c.atiendePaciente(nombreMedico);
		}
		else if (instruc == "numCitas") {
			string nombrePaciente;
			cin >> nombrePaciente;
			cout << c.numConsultas(nombrePaciente) << endl;
		}
		else if (instruc == "fin") {
			i++;
			Consulta nueva;
			c = nueva;
			if (i < bloques)
				cout << "bloque #" << i + 1 << endl;		
		}
	}



	return 0;
}