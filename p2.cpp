/*
Pareja: Davices
David Tanarro de las Heras
David Rodriguez Marco
*/

#include <iostream>
#include <string>
#include "Stack.h"

using namespace std;

int main() {
	Stack <string> pila;
	char c = '1';
	string cad = "";

    int n; 
    cin >> n;    
    for (int i=0; i<n; i++) {
        Stack<string> p;
        int errors = 0;        
        
        int k;
        cin >> k;
        for (int j=0; j<k; j++) {
            string s;
            cin >> s;
            
            // si s es 
            //    - una etiqueta de apertura, la apila
            //    - una etiqueta de cierre, 
            //         si cierra bien con la última apilada, desapila la última
            //         y si no, apunta 1 error
            //    - otra cosa, lo ignora.
			

			if (s[0] == '<' && s[1] != '/') {
				string a = "";
				a = s.substr(1, s.length() - 1);
				pila.push(a);
			}
			else if (s[0] == '<' && s[1] == '/') {
				string a = "";
				a = s.substr(2, s.length() - 1);
					
				if (!pila.empty() && pila.top() == a)
						pila.pop();
				else
					errors++;
			}
			

        }  
		if (errors == 0 && pila.empty())
			cout << "YES" << endl;
		else
			cout << "NO" << endl;

		errors = 0;
		while (!pila.empty())
			pila.pop();
		
        // muestra YES\n o NO\n, según toque
    }
        
    return 0;
}
