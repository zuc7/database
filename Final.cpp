#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <filesystem>

using namespace std;

#include "Gestione.cpp"

int main() {
   
    DataStore ds;

    bool running = true;
    while (running) {
        stampaMenu();
        int scelta = readIntSafe("Seleziona un'opzione: ");
        switch (scelta) {
            case 1: { // Squadra CRUD
                cout << "\n=== MENU SQUADRA ===\n1. Inserimento\n2. Modifica\n3. Rimozione\n";
                int s = readIntSafe("Scelta: ");
                if (s==1) {
                    SquadraRec sr;
                    sr.id = readIntSafe("Inserisci ID Squadra: ");
                    sr.nome = readLine("Inserisci nome Squadra: ");
                    do {
                        string L = readLine("Inserisci Lega (A,B,C): ");
                        if (!L.empty()) sr.lega = toupper(L[0]);
                        else sr.lega = ' ';
                    } while (sr.lega!='A' && sr.lega!='B' && sr.lega!='C');
                    sr.anno = readIntSafe("Inserisci anno (es. 2025): ");
                    sr.indirizzo = readLine("Inserisci indirizzo sede: ");
                    sr.budget = readDoubleSafe("Inserisci budget annuale (€): ");
                    sr.nAbbonati = readIntSafe("Inserisci numero di abbonati: ");
                    sr.idCapitano = 0;
                    string msg;
                    if (ds.addSquadra(sr, msg)) cout << "✅ Squadra inserita correttamente!\n";
                    else cout << "Errore: " << msg << "\n";
                } else if (s==2) {
                    int id = readIntSafe("Inserisci ID Squadra da modificare: ");
                    auto it = ds.idxSquadre.find(id);
                    if (it==ds.idxSquadre.end()) { cout << "Squadra non trovata.\n"; break; }
                    SquadraRec sr = ds.squadre[it->second];
                    cout << "Lascia vuoto per non modificare.\n";
                    string tmp = readLine("Nome ["+sr.nome+"]: "); if (!tmp.empty()) sr.nome = tmp;
                    tmp = readLine(string("Lega [")+sr.lega+"]: "); if (!tmp.empty()) sr.lega = toupper(tmp[0]);
                    tmp = readLine("Anno ["+to_string(sr.anno)+"]: "); if (!tmp.empty()) sr.anno = stoi(tmp);
                    tmp = readLine("Indirizzo ["+sr.indirizzo+"]: "); if (!tmp.empty()) sr.indirizzo = tmp;
                    tmp = readLine("Budget ["+to_string(sr.budget)+"]: "); if (!tmp.empty()) sr.budget = stod(tmp);
                    tmp = readLine("nAbbonati ["+to_string(sr.nAbbonati)+"]: "); if (!tmp.empty()) sr.nAbbonati = stoi(tmp);
                    string msg;
                    if (ds.updateSquadra(sr, msg)) cout << "✅ Squadra aggiornata.\n"; else cout << "Errore: " << msg << "\n";
                } else if (s==3) {
                    int id = readIntSafe("Inserisci ID squadra da eliminare: ");
                    string msg;
                    if (ds.deleteSquadra(id, msg)) cout << "✅ Squadra eliminata.\n"; else cout << "Errore: " << msg << "\n";
                } else cout << "Opzione non valida.\n";
            } break;
            case 2: { // Calciatore CRUD
                cout << "\n=== MENU CALCIATORE ===\n1. Inserimento\n2. Modifica\n3. Rimozione\n";
                int s = readIntSafe("Scelta: ");
                if (s==1) {
                    CalciatoreRec c;
                    c.id = readIntSafe("Inserisci ID Calciatore: ");
                    c.nome = readLine("Inserisci nome: ");
                    c.cognome = readLine("Inserisci cognome: ");
                    c.dataNascita = readIntSafe("Inserisci data di nascita (YYYYMMDD): ");
                    c.nazionalita = readLine("Inserisci nazionalità: ");
                    c.valore = readDoubleSafe("Inserisci valore di mercato (€): ");
                    c.ingaggio = readDoubleSafe("Inserisci ingaggio annuale (€): ");
                    c.idSquadra = readIntSafe("Inserisci ID squadra (0 se nessuna): ");
                    c.idProcuratore = readIntSafe("Inserisci ID procuratore (0 se nessuno): ");
                    string msg;
                    if (ds.addCalciatore(c, msg)) cout << "✅ Calciatore inserito correttamente!\n"; else cout << "Errore: "<<msg<<"\n";
                } else if (s==2) {
                    int id = readIntSafe("Inserisci ID calciatore da modificare: ");
                    auto it = ds.idxCalciatori.find(id);
                    if (it==ds.idxCalciatori.end()) { cout << "Calciatore non trovato.\n"; break; }
                    CalciatoreRec c = ds.calciatori[it->second];
                    cout << "Lascia vuoto per non modificare.\n";
                    string tmp = readLine("Nome ["+c.nome+"]: "); if (!tmp.empty()) c.nome = tmp;
                    tmp = readLine("Cognome ["+c.cognome+"]: "); if (!tmp.empty()) c.cognome = tmp;
                    tmp = readLine("DataNascita ["+to_string(c.dataNascita)+"]: "); if (!tmp.empty()) c.dataNascita = stoi(tmp);
                    tmp = readLine("Nazionalità ["+c.nazionalita+"]: "); if (!tmp.empty()) c.nazionalita = tmp;
                    tmp = readLine("Valore ["+to_string(c.valore)+"]: "); if (!tmp.empty()) c.valore = stod(tmp);
                    tmp = readLine("Ingaggio ["+to_string(c.ingaggio)+"]: "); if (!tmp.empty()) c.ingaggio = stod(tmp);
                    tmp = readLine("ID Squadra ["+to_string(c.idSquadra)+"]: "); if (!tmp.empty()) c.idSquadra = stoi(tmp);
                    tmp = readLine("ID Procuratore ["+to_string(c.idProcuratore)+"]: "); if (!tmp.empty()) c.idProcuratore = stoi(tmp);
                    string msg;
                    if (ds.updateCalciatore(c, msg)) cout << "✅ Calciatore aggiornato.\n"; else cout << "Errore: "<<msg<<"\n";
                } else if (s==3) {
                    int id = readIntSafe("Inserisci ID calciatore da eliminare: ");
                    string msg;
                    if (ds.deleteCalciatore(id, msg)) cout << "✅ Calciatore eliminato.\n"; else cout << "Errore: "<<msg<<"\n";
                } else cout << "Opzione non valida.\n";
            } break;
            case 3: { // Procuratore CRUD
                cout << "\n=== MENU PROCURATORE ===\n1. Inserimento\n2. Modifica\n3. Rimozione\n";
                int s = readIntSafe("Scelta: ");
                if (s==1) {
                    ProcuratoreRec p;
                    p.id = readIntSafe("Inserisci ID Procuratore: ");
                    p.nome = readLine("Inserisci nome: ");
                    p.cognome = readLine("Inserisci cognome: ");
                    p.piva = readLine("Inserisci P.IVA / CF: ");
                    string msg;
                    if (ds.addProcuratore(p, msg)) cout << "✅ Procuratore inserito correttamente!\n"; else cout << "Errore: "<<msg<<"\n";
                } else if (s==2) {
                    int id = readIntSafe("Inserisci ID procuratore da modificare: ");
                    auto it = ds.idxProcuratori.find(id);
                    if (it==ds.idxProcuratori.end()) { cout << "Procuratore non trovato.\n"; break; }
                    ProcuratoreRec p = ds.procuratori[it->second];
                    cout << "Lascia vuoto per non modificare.\n";
                    string tmp = readLine("Nome ["+p.nome+"]: "); if (!tmp.empty()) p.nome = tmp;
                    tmp = readLine("Cognome ["+p.cognome+"]: "); if (!tmp.empty()) p.cognome = tmp;
                    tmp = readLine("P.IVA/CF ["+p.piva+"]: "); if (!tmp.empty()) p.piva = tmp;
                    string msg;
                    if (ds.updateProcuratore(p, msg)) cout << "✅ Procuratore aggiornato.\n"; else cout << "Errore: "<<msg<<"\n";
                } else if (s==3) {
                    int id = readIntSafe("Inserisci ID procuratore da eliminare: ");
                    string msg;
                    if (ds.deleteProcuratore(id, msg)) cout << "✅ Procuratore eliminato (eventuali calciatori aggiornati a idProcuratore=0).\n"; else cout << "Errore: "<<msg<<"\n";
                } else cout << "Opzione non valida.\n";
            } break;
            case 4: { // Capitano
                cout << "\n=== MENU CAPITANO ===\n1. Imposta Capitano\n2. Rimuovi Capitano\n";
                int s = readIntSafe("Scelta: ");
                if (s==1) {
                    int idS = readIntSafe("Inserisci ID squadra: ");
                    int idC = readIntSafe("Inserisci ID calciatore da impostare come capitano: ");
                    string msg;
                    if (ds.setCapitano(idS, idC, msg)) cout << "✅ Capitano impostato.\n"; else cout << "Errore: " << msg << "\n";
                } else if (s==2) {
                    int idS = readIntSafe("Inserisci ID squadra: ");
                    string msg;
                    if (ds.removeCapitano(idS, msg)) cout << "✅ Capitano rimosso.\n"; else cout << "Errore: " << msg << "\n";
                } else cout << "Opzione non valida.\n";
            } break;
            case 5: { // Stampa riepilogo squadra
                int id = readIntSafe("Inserisci ID squadra: ");
                auto its = ds.idxSquadre.find(id);
                if (its==ds.idxSquadre.end()) { cout << "Squadra non trovata.\n"; break; }
                auto &s = ds.squadre[its->second];
                cout << "\n==== RIEPILOGO SQUADRA ====\n";
                cout << "ID: " << s.id << "  Nome: " << s.nome << "  Lega: " << s.lega << "  Anno: " << s.anno << "\n";
                cout << "Indirizzo: " << s.indirizzo << "\n";
                cout << "Budget: " << fixed << setprecision(2) << s.budget << "  Abbonati: " << s.nAbbonati << "\n";
                if (s.idCapitano != 0) cout << "Capitano ID: " << s.idCapitano << "\n"; else cout << "Capitano: non impostato\n";
                cout << "\nElenco calciatori:\n";
                vector<CalciatoreRec> list;
                for (auto &c : ds.calciatori) if (c.idSquadra == s.id) list.push_back(c);
                ds.printCalciatoriList(list, cout);
            } break;
            case 6: { // Ricerca per ID
                int id = readIntSafe("Inserisci ID da cercare: ");
                string ris = ds.ricercaId(id);
                if (ris != "No") cout << ris << "\n"; else cout << "ID non trovato.\n";
            } break;
            case 7: { // Ricerca per nome
                string q = readLine("Inserisci stringa da cercare (nome/cognome/squadra): ");
                auto res = ds.ricercaNome(q);
                if (res.empty()) cout << "Nessun risultato.\n";
                else for (auto &r : res) cout << r << "\n";
            } break;
            case 8: { // Interrogazioni 3a-3c
                cout << "\n=== INTERROGAZIONI ===\n1. Elencare tutti i calciatori (3a)\n2. Calciatori di una squadra (3b)\n3. Calciatori in squadre con >=10000 abbonati (3c)\n";
                int q = readIntSafe("Scelta: ");
                if (q==1) ds.query3a_printAllCalciatori(cout);
                else if (q==2) {
                    string team = readLine("Inserisci nome squadra (parziale accettato): ");
                    // trovo quante squadre con quel nome -> se più anni chiedo anno
                    vector<int> matches;
                    for (auto &s : ds.squadre) if (DataStore::toLower(s.nome).find(DataStore::toLower(team)) != string::npos) matches.push_back(s.id);
                    if (matches.empty()) { cout << "Nessuna squadra trovata.\n"; break; }
                    if (matches.size() > 1) {
                        cout << "Trovate più squadre con quel nome (anni/lega):\n";
                        for (auto id : matches) {
                            auto &s = ds.squadre[ds.idxSquadre[id]];
                            cout << "ID="<<s.id<< " Nome="<<s.nome<<" Lega="<<s.lega<<" Anno="<<s.anno<<"\n";
                        }
                        int anno = readIntSafe("Inserisci anno da filtrare (0 per tutte): ");
                        vector<CalciatoreRec> res = ds.query3b_byTeamName(team, anno);
                        ds.printCalciatoriList(res, cout);
                    } else {
                        vector<CalciatoreRec> res = ds.query3b_byTeamName(team, 0);
                        ds.printCalciatoriList(res, cout);
                    }
                } else if (q==3) {
                    vector<CalciatoreRec> res = ds.query3c_minAbbonati(10000);
                    ds.printCalciatoriList(res, cout);
                } else cout << "Opzione non valida.\n";
            } break;
            case 9: { // Esporta risultato in CSV (esempio esporta 3a o 3c)
                cout << "Esporta quale query? 1=3a (tutti i calciatori), 2=3c (calciatori in squadre con >=10000 abbonati)\n";
                int which = readIntSafe("Scelta: ");
                string outFile = readLine("Nome file di destinazione (es. export.csv): ");
                ofstream f(outFile);
                if (!f.is_open()) { cout << "Impossibile creare file.\n"; break; }
                // header
                f << "id;nome;cognome;squadra;lega;valore;ingaggio;procuratore\n";
                if (which == 1) {
                    for (auto &c : ds.calciatori) {
                        string squadraName="-"; char lega='-';
                        auto its = ds.idxSquadre.find(c.idSquadra);
                        if (its!=ds.idxSquadre.end()) { squadraName = ds.squadre[its->second].nome; lega = ds.squadre[its->second].lega; }
                        string procur="-";
                        auto itp = ds.idxProcuratori.find(c.idProcuratore);
                        if (itp!=ds.idxProcuratori.end()) procur = ds.procuratori[itp->second].cognome;
                        f << c.id << ';' << escape_csv_field(c.nome) << ';' << escape_csv_field(c.cognome) << ';'
                          << escape_csv_field(squadraName) << ';' << lega << ';'
                          << c.valore << ';' << c.ingaggio << ';' << escape_csv_field(procur) << '\n';
                    }
                } else if (which==2) {
                    auto list = ds.query3c_minAbbonati(10000);
                    for (auto &c : list) {
                        string squadraName="-"; char lega='-';
                        auto its = ds.idxSquadre.find(c.idSquadra);
                        if (its!=ds.idxSquadre.end()) { squadraName = ds.squadre[its->second].nome; lega = ds.squadre[its->second].lega; }
                        string procur="-";
                        auto itp = ds.idxProcuratori.find(c.idProcuratore);
                        if (itp!=ds.idxProcuratori.end()) procur = ds.procuratori[itp->second].cognome;
                        f << c.id << ';' << escape_csv_field(c.nome) << ';' << escape_csv_field(c.cognome) << ';'
                          << escape_csv_field(squadraName) << ';' << lega << ';'
                          << c.valore << ';' << c.ingaggio << ';' << escape_csv_field(procur) << '\n';
                    }
                } else cout << "Opzione non valida.\n";
                f.close();
                cout << "Export completato su " << outFile << "\n";
            } break;
            case 0: {
                ds.saveAll();
                cout << "Dati salvati. Uscita...\n";
                running = false;
            } break;
            default:
                cout << "Opzione non valida!\n";
        }
    }

    return 0;
}
