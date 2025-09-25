#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Persona{
    private:
        int id;
        string nome;
        string cognome;
    public:
        Persona() {
            id = 666;
            nome = "negro";
            cognome = "negroni";
        }
        Persona(int id, string nome, string cognome) {
            this->id = id;
            this->nome = nome;
            this->cognome = cognome;
        }
        void write(ofstream& myFile) {
            myFile << id << "," << nome << "," << cognome << ",";
        }

};

class Calciatore: public Persona{
    private:
        int dataNascita;
        double valoreMercato;
        double ingaggioAnnuale;
        int idSquadra;
        int idProcuratore;
    public:
        Calciatore() : Persona() {
            dataNascita = 101010;
            valoreMercato = 500.69;
            ingaggioAnnuale = 8000;
            idSquadra = 222;
            idProcuratore = 333;
        }
        Calciatore(int id, string nome, string cognome, int dataNascita,
                    double valoreMercato, double ingaggioAnnuale, 
                    int idSquadra, int idProcuratore) : Persona(id, nome, cognome) {
                this->dataNascita = dataNascita;
                this->valoreMercato = valoreMercato;
                this->ingaggioAnnuale = ingaggioAnnuale;
                this->idSquadra = idSquadra;
                this->idProcuratore = idProcuratore;
         }

        void write() {
            ofstream myFile("calciatori.csv", ios::app); // Apre il file in modalità append
            if (myFile.is_open()) {
                // Scrittura dei dati nel formato CSV
                Persona::write(myFile);
                myFile << dataNascita << ","
                    << valoreMercato << ","
                    << ingaggioAnnuale << ","
                    << idSquadra << ","
                    << idProcuratore << "\n";
                myFile.close();
            } else {
                cerr << "Errore nell'apertura del file.\n";
            }
        }

    };
class Procuratore: public Persona{
    private:
        string pIVA_CF;

    public:
        Procuratore() : Persona() {
            pIVA_CF = "101010";
        }
        Procuratore(int id, string nome, string cognome, string pIVA_CF) : Persona(id, nome, cognome){
            this->pIVA_CF=pIVA_CF;
        }
        void write() {
            string file="procuratori.csv";
            ofstream myFile(file, ios::app); // Apre il file in modalità append
            if (myFile.is_open()) {
                // Scrittura dei dati nel formato CSV
                Persona::write(myFile);
                myFile << pIVA_CF;
                myFile.close();
            } else {
                cerr << "Errore nell'apertura del file.\n";
            }
        }

};

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
        Squadra() {
            this->idSquadra = 0;
            this->nome = "";
            this->Lega = ' ';
            this->anno = 0;
            this->indirizzoSede = "";
            this->budgetAnnuale = 0.0;
            this->nAbbonati = 0;
        }

    // Costruttore parametrizzato
    Squadra(int idSquadra, string nome, char Lega, int anno, string indirizzoSede,
            double budgetAnnuale, int nAbbonati) {
            this->idSquadra = idSquadra;
            this->nome = nome;
            this->Lega = Lega;
            this->anno = anno;
            this->indirizzoSede = indirizzoSede;
            this->budgetAnnuale = budgetAnnuale;
            this->nAbbonati = nAbbonati;
        }
    void write() {
        ofstream myFile("squadre.csv", ios::app);  // Apre in modalità append per non sovrascrivere
        if (myFile.is_open()) {
            // Scrivo i dati separati da virgole, con una nuova riga finale
            myFile << this->idSquadra << ","
                << this->nome << ","
                << this->Lega << ","
                << this->anno << ","
                << this->indirizzoSede << ","
                << this->budgetAnnuale << ","
                << this->nAbbonati << "\n";
            myFile.close();
        } else {
            cerr << "Errore nell'apertura del file squadre.csv\n";
        }
    }
    
};

class Gestione{
    public:
        Gestione();
        void deleteFile(string name) {
            ofstream myFile(name, ios::trunc);  // trunc tronca il file (lo svuota) 
            if (myFile.is_open()) {
                myFile.close();
            } else {
                cerr << "Errore nell'apertura del file.\n";
            }
        }
        void inserimento(int n) {
            switch (n) {
                case 1: {
                    int id, dataNascita, idSquadra, idProcuratore;
                    string nome, cognome;
                    double valoreMercato, ingaggioAnnuale;

                    cout << "Inserisci ID Calciatore: ";
                    cin >> id;

                    cout << "Inserisci nome: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, nome);

                    cout << "Inserisci cognome: ";
                    getline(cin, cognome);

                    cout << "Inserisci data di nascita (formato YYYYMMDD, es. 19901231): ";
                    cin >> dataNascita;

                    cout << "Inserisci valore di mercato (€): ";
                    cin >> valoreMercato;
                    if (valoreMercato < 0) {
                        cout << "Errore: valore di mercato non può essere negativo. Impostato a 0.\n";
                        valoreMercato = 0;
                    }

                    cout << "Inserisci ingaggio annuale (€): ";
                    cin >> ingaggioAnnuale;
                    if (ingaggioAnnuale < 0) {
                        cout << "Errore: ingaggio annuale non può essere negativo. Impostato a 0.\n";
                        ingaggioAnnuale = 0;
                    }

                    cout << "Inserisci ID squadra: ";
                    cin >> idSquadra;

                    cout << "Inserisci ID procuratore (0 se nessuno): ";
                    cin >> idProcuratore;

                    Calciatore nuovoCalciatore(id, nome, cognome, dataNascita, valoreMercato, ingaggioAnnuale, idSquadra, idProcuratore);
                    nuovoCalciatore.write();

                    cout << "✅ Calciatore inserito correttamente!\n"; }
                    break;
                
                case 2:{
                    int id;
                    string nome, cognome, pIVA_CF;

                    cout << "Inserisci ID Procuratore: ";
                    cin >> id;

                    cout << "Inserisci nome: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, nome);

                    cout << "Inserisci cognome: ";
                    getline(cin, cognome);


                    cout << "Inserisci valore di mercato (€): ";
                    cin >> pIVA_CF;

                    Procuratore nuovoProcuratore(id,nome,cognome,pIVA_CF);
                    nuovoProcuratore.write();

                    cout << "✅ Calciatore inserito correttamente!\n"; }
                    break;
                case 3:{
                    int idSquadra;
                    string nome;
                    char Lega;
                    int anno;
                    string indirizzoSede;
                    double budgetAnnuale;
                    int nAbbonati;

                    // Pulizia buffer e input
                    cout << "Inserisci ID Squadra: ";
                    cin >> idSquadra;

                    cout << "Inserisci nome Squadra: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, nome);

                    do {
                        cout << "Inserisci Lega (A, B, C): ";
                        cin >> Lega;
                        Lega = toupper(Lega); // forza maiuscolo
                        if (Lega != 'A' && Lega != 'B' && Lega != 'C') {
                            cout << "Errore: lega deve essere A, B o C.\n";
                        }
                    } while (Lega != 'A' && Lega != 'B' && Lega != 'C');

                    cout << "Inserisci anno (es. 2025): ";
                    cin >> anno;

                    cout << "Inserisci indirizzo sede: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, indirizzoSede);

                    cout << "Inserisci budget annuale (€): ";
                    cin >> budgetAnnuale;

                    if (budgetAnnuale < 0) {
                        cout << "Errore: il budget non può essere negativo. Impostato a 0.\n";
                        budgetAnnuale = 0;
                    }

                    cout << "Inserisci numero di abbonati: ";
                    cin >> nAbbonati;

                    if (nAbbonati < 0) {
                        cout << "Errore: il numero di abbonati non può essere negativo. Impostato a 0.\n";
                        nAbbonati = 0;
                    }

                    // Costruisci la squadra
                    Squadra nuovaSquadra=Squadra(idSquadra, nome, Lega, anno, indirizzoSede, budgetAnnuale, nAbbonati);

                    // Salva su CSV (supponendo tu abbia il metodo write() nella classe)
                    nuovaSquadra.write();

                    cout << "✅ Squadra inserita correttamente!\n"; }
                    break;
                default:
                    break;
                }
            }
        void deleteInstance(int iD, string file){
            ifstream fileInput(file);
            if (!fileInput.is_open()) {
                cerr << "Errore nell'apertura del file: " << file << endl;
                return;
            }

            string tempfile = "temp.csv";
            ofstream fileOutput(tempfile);
            if (!fileOutput.is_open()) {
                cerr << "Errore nella creazione del file temporaneo." << endl;
                return;
            }

            string riga;
            while (getline(fileInput, riga)) {
                stringstream ss(riga);
                int primoCampo;
                char delim;
                if (ss >> primoCampo >> delim && delim == ',') {
                    if (primoCampo != iD) {
                        fileOutput << riga << '\n';
                    } else {
                        cout << "Riga eliminata: " << riga << endl;
                    }
                }
            }

            fileInput.close();
            fileOutput.close();
            // Sostituire il file originale con il file temporaneo
            if (remove(file.c_str()) != 0) {
                cerr << "Errore nell'eliminazione del file originale." << endl;
                return;
            }
            if (rename(tempfile.c_str(), file.c_str()) != 0) {
                cerr << "Errore nella rinomina del file temporaneo." << endl;
                return;
            }
        }
        string ricercaId(int iD) {
            string file[] = { "calciatori.csv", "procuratori.csv", "squadre.csv" };

            for (string n : file) {
                ifstream f(n);
                if (!f.is_open()) {
                    cerr << "Errore apertura file: " << n << endl;
                    continue;
                }

                string riga;
                while (getline(f, riga)) {
                    stringstream ss(riga);
                    int primoCampoInt;
                    char delim;

                    if (ss >> primoCampoInt >> delim && delim == ',') {
                        if (primoCampoInt == iD) {
                            f.close();
                            return riga;
                        }
                    }
                }

                f.close();
            }

            return "No"; 
        }
};

int main(){
    Gestione g= Gestione();
    g.deleteFile("calciatori.csv");
    Calciatore c=Calciatore();
    c.write();
    Squadra s=Squadra();
    s.write();
    Procuratore p=Procuratore();
    p.write();
    int scelta, id;
    string ris;
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
                    case 1: 
                        g.inserimento(3);
                        break;
                    case 2: /* modifica squadra */ break;
                    case 3:
                        cout<<"Inserisci Id squadra:";
                        cin>>id;
                        g.deleteInstance(id,"squadre.csv");
                    break;
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
                    case 1:    
                        g.inserimento(1);
                        break;
                    case 2: /* modifica calciatore */ break;
                    case 3:
                        cout<<"Inserisci Id calciatore:";
                        cin>>id;
                        g.deleteInstance(id,"calciatori.csv");
                        break;
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
                    case 1: 
                        g.inserimento(2);
                        break;
                    case 2: /* modifica procuratore */ break;
                    case 3: 
                        cout<<"Inserisci Id procuuratore:";
                        cin>>id;
                        g.deleteInstance(id,"procuratori.csv");
                        break;
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
            case 6:
                cout<<"Inserisci Id da cercare:";
                cin>>id;
                ris=g.ricercaId(id);
                if(ris!="No"){
                    cout << ris <<"/n";
                }
                else 
                    cout<<"Id not found";
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


