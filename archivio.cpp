#include <iostream>
#include <fstream>

using namespace std;

class Squadra{
    private:
        int idSquadra;
        string nome;
        char Lega;
        int anno;
        string indirizzoSede;
        double budgetAnnuale;
        int nAbbonati;

    public:
        Squadra ();
        ~Squadra ();

        void write(){
            ofstream myFile("squadre.csv");
        }

};
class Calciatore {
    private:
        int idGiocatore;
        string nome;
        string cognome;
        int dataNascita;
        double valoreMercato;
        double ingaggioAnnuale;
        int idSquadra;
        int idProcuratore;
    public:
        Calciatore();
        ~Calciatore();
        void write(){
            ofstream myFile("calciatori.csv");
        }
    };
class Procuratore {
    private:
        int idProcuratore;
        string nome;
        string cognome;
        string pIVA_CF;
    public:
        Procuratore();
        ~Procuratore();
        void write(){
            ofstream myFile("procuratori.csv");
        }

};


int main(){
    int scelta;
    do {
        cout << "\n=== MENU PRINCIPALE ===\n";
        cout << "1 .Operazioni su squadra\n";
        cout << "2. Operazioni su Calciatore\n";
        cout << "3. Operazioni su Procuratore\n";
        cout << "4. Operazioni su Capitano di una Squadra\n";
        cout << "5. Stampa riepilogo di una Squadra\n";
        cout << "6. Ricerca per ID\n";
        cout << "7. Ricerca per nome (case-insensitive)\n";
        cout << "8. Interrogazioni\n";
        cout << "9. Esporta risultati in CSV\n";
        cout << "0. Esci\n";
        cout << "Seleziona un'opzione: ";
        cin >> scelta;

        switch(scelta) {
            case 1: 
                cout << "\n=== MENU SQUADRA ===\n";
                cout << "1. Inserimento\n";
                cout << "2. Modifica\n";
                cout << "3. Rimozione\n";
                cin>>scelta;
                switch(scelta){
                    case 1: /* inserisci squadra */ break;
                    case 2: /* modifica squadra */ break;
                    case 3: /* elimina squadra */ break;
                    default: cout << "Opzione non valida!\n";
                }               
                break;
            case 2:
                cout << "\n=== MENU GIOCATORE ===\n";
                cout << "1. Inserimento\n";
                cout << "2. Modifica\n";
                cout << "3. Rimozione\n";
                cin>>scelta;
                switch(scelta){
                    case 1: /* inserisci calciatore */ break;
                    case 2: /* modifica calciatore */ break;
                    case 3: /* elimina calciatore */ break;
                    default: cout << "Opzione non valida!\n";
                }
                break;
            case 3:
                cout << "\n=== MENU PROCURATORE ===\n";
                cout << "1. Inserimento\n";
                cout << "2. Modifica\n";
                cout << "3. Rimozione\n";
                cin>>scelta;
                switch(scelta){
                    case 1: /* inserisci procuratore */ break;
                    case 2: /* modifica procuratore */ break;
                    case 3: /* elimina procuratore */ break;
                    default: cout << "Opzione non valida!\n";
                }
                break;
            case 4: 
                cout << "\n=== MENU CAPITANO ===\n";
                cout << "1. Imposta Capitano\n";
                cout << "2. Rimuovi Capitano\n";
                cin>>scelta;
                switch(scelta){
                    case 1: /* imposta capitano */ break;
                    case 2: /* rimuovi capitano */ break;
                    default: cout << "Opzione non valida!\n";
                }
                break;
            case 5: /* stampa riepilogo */ 
                
            
            
            
                break;
            case 6: /* ricerca per ID */ 
            
            
            
            
            
                break;
            case 7: /* ricerca per nome */
            
            
            
            
                break;
            case 8: /* interrogazioni */ 
                cout << "\n=== MENU INTERROGAZIONI ===\n";
                cout << "1. Elencare tutti i calciatori presenti nell’archivio\n";
                cout << "2. Elencare tutti i calciatori che militano in una squadra fornita in input\n";
                cout << "3. Elencare tutti i calciatori che militano in squadre con almeno 10 000 abbonati\n";
                cin>>scelta;
                switch(scelta){
                    case 1: /* elenca tutti i calciatori */ break;
                    case 2: /* elenca calciatori per squadra */ break;
                    case 3: /* elenca calciatori per nAbbonati */ break;
                    default: cout << "Opzione non valida!\n";
                }
                break;
            case 9: /* esporta in CSV */ break;
            case 0: cout << "Uscita...\n"; break;
            default: cout << "Opzione non valida!\n";
        }
    } while(scelta != 0);

    
    return 0;
}
