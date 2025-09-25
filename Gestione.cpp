#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <filesystem>

#include "Util.cpp"

using namespace std;

struct SquadraRec {
    int id;
    string nome;
    char lega; // 'A','B','C'
    int anno;
    string indirizzo;
    double budget;
    int nAbbonati;
    int idCapitano; // 0 = non valorizzato
};

struct CalciatoreRec {
    int id;
    string nome;
    string cognome;
    int dataNascita; // YYYYMMDD
    string nazionalita;
    double valore;
    double ingaggio;
    int idSquadra; // FK (0 = nessuna)
    int idProcuratore; // FK (0 = nessuno)
};

struct ProcuratoreRec {
    int id;
    string nome;
    string cognome;
    string piva;
};

class DataStore {
public:
    vector<SquadraRec> squadre;
    vector<CalciatoreRec> calciatori;
    vector<ProcuratoreRec> procuratori;

    unordered_map<int, size_t> idxSquadre;
    unordered_map<int, size_t> idxCalciatori;
    unordered_map<int, size_t> idxProcuratori;

    const string fileSquadre = "squadre.csv";
    const string fileCalciatori = "calciatori.csv";
    const string fileProcuratori = "procuratori.csv";

    DataStore() {
        loadAll();
    }

    // ---------- Indici ----------
    void rebuildIndexes() {
        idxSquadre.clear();
        for (size_t i=0;i<squadre.size();++i) idxSquadre[squadre[i].id] = i;
        idxCalciatori.clear();
        for (size_t i=0;i<calciatori.size();++i) idxCalciatori[calciatori[i].id] = i;
        idxProcuratori.clear();
        for (size_t i=0;i<procuratori.size();++i) idxProcuratori[procuratori[i].id] = i;
    }
    // ---------- Saving ----------
    void saveSquadre() {
        ofstream f(fileSquadre, ios::trunc);
        if (!f.is_open()) { cerr << "Impossibile aprire " << fileSquadre << " per scrittura\n"; return; }
        for (auto &s : squadre) {
            f << s.id << ';'
              << escape_csv_field(s.nome) << ';'
              << s.lega << ';'
              << s.anno << ';'
              << escape_csv_field(s.indirizzo) << ';'
              << s.budget << ';'
              << s.nAbbonati << ';'
              << s.idCapitano << '\n';
        }
        f.close();
    }
    void saveCalciatori() {
        ofstream f(fileCalciatori, ios::trunc);
        if (!f.is_open()) { cerr << "Impossibile aprire " << fileCalciatori << " per scrittura\n"; return; }
        for (auto &c : calciatori) {
            f << c.id << ';'
              << escape_csv_field(c.nome) << ';'
              << escape_csv_field(c.cognome) << ';'
              << c.dataNascita << ';'
              << escape_csv_field(c.nazionalita) << ';'
              << c.valore << ';'
              << c.ingaggio << ';'
              << c.idSquadra << ';'
              << c.idProcuratore << '\n';
        }
        f.close();
    }
    void saveProcuratori() {
        ofstream f(fileProcuratori, ios::trunc);
        if (!f.is_open()) { cerr << "Impossibile aprire " << fileProcuratori << " per scrittura\n"; return; }
        for (auto &p : procuratori) {
            f << p.id << ';'
              << escape_csv_field(p.nome) << ';'
              << escape_csv_field(p.cognome) << ';'
              << escape_csv_field(p.piva) << '\n';
        }
        f.close();
    }
    void saveAll() {
        saveSquadre();
        saveCalciatori();
        saveProcuratori();
    }

    // ---------- Loading ----------
    static vector<string> split_csv_semicolon(string line) {
        vector<string> fields;
        string cur;
        for (size_t i=0;i<line.size();++i) {
            if (line[i] == ';') {
                fields.push_back(cur); cur.clear();
            } else if (line[i] == '\\' && i+1 < line.size()) {
                // keep as-is; unescape later
                cur.push_back(line[i]);
                cur.push_back(line[i+1]);
                ++i;
            } else cur.push_back(line[i]);
        }
        fields.push_back(cur);
        return fields;
    }

    void loadAll() {
        squadre.clear(); calciatori.clear(); procuratori.clear();
        // load squads
        if (filesystem::exists(fileSquadre)) {
            ifstream f(fileSquadre);
            string line;
            while (getline(f, line)) {
                if (line.empty()) continue;
                auto fields = split_csv_semicolon(line);
                if (fields.size() < 8) continue;
                SquadraRec s;
                try {
                    s.id = stoi(fields[0]);
                    s.nome = unescape_csv_field(fields[1]);
                    s.lega = fields[2].empty() ? ' ' : fields[2][0];
                    s.anno = stoi(fields[3]);
                    s.indirizzo = unescape_csv_field(fields[4]);
                    s.budget = stod(fields[5]);
                    s.nAbbonati = stoi(fields[6]);
                    s.idCapitano = stoi(fields[7]);
                    squadre.push_back(s);
                } catch (...) { cerr << "Formato riga errato in " << fileSquadre << ": " << line << '\n'; }
            }
            f.close();
        }
        // load calciatori
        if (filesystem::exists(fileCalciatori)) {
            ifstream f(fileCalciatori);
            string line;
            while (getline(f, line)) {
                if (line.empty()) continue;
                auto fields = split_csv_semicolon(line);
                if (fields.size() < 9) continue;
                CalciatoreRec c;
                try {
                    c.id = stoi(fields[0]);
                    c.nome = unescape_csv_field(fields[1]);
                    c.cognome = unescape_csv_field(fields[2]);
                    c.dataNascita = stoi(fields[3]);
                    c.nazionalita = unescape_csv_field(fields[4]);
                    c.valore = stod(fields[5]);
                    c.ingaggio = stod(fields[6]);
                    c.idSquadra = stoi(fields[7]);
                    c.idProcuratore = stoi(fields[8]);
                    calciatori.push_back(c);
                } catch (...) { cerr << "Formato riga errato in " << fileCalciatori << ": " << line << '\n'; }
            }
            f.close();
        }
        // load procuratori
        if (filesystem::exists(fileProcuratori)) {
            ifstream f(fileProcuratori);
            string line;
            while (getline(f, line)) {
                if (line.empty()) continue;
                auto fields = split_csv_semicolon(line);
                if (fields.size() < 4) continue;
                ProcuratoreRec p;
                try {
                    p.id = stoi(fields[0]);
                    p.nome = unescape_csv_field(fields[1]);
                    p.cognome = unescape_csv_field(fields[2]);
                    p.piva = unescape_csv_field(fields[3]);
                    procuratori.push_back(p);
                } catch (...) { cerr << "Formato riga errato in " << fileProcuratori << ": " << line << '\n'; }
            }
            f.close();
        }

        rebuildIndexes();

        // se i file non esistono (primo avvio), creiamo dati di test minimi:
        if (!filesystem::exists(fileSquadre) && !filesystem::exists(fileCalciatori) && !filesystem::exists(fileProcuratori)) {
            createSampleData();
            saveAll();
        } else {
            // in caso i file esistano ma non rispettano test minimi, non auto-creiamo
        }
    }

    // ---------- Check Vincoli (V1-V6) ----------
    // V1. Squadra: id univoco e nome univoco per (lega, anno).
    bool checkV1_newSquadra(SquadraRec s, string msg) {
        if (idxSquadre.find(s.id) != idxSquadre.end()) {
            msg = "ID squadra già esistente.";
            return false;
        }
        for (auto &ex : squadre) {
            if (ex.nome == s.nome && ex.lega == s.lega && ex.anno == s.anno) {
                msg = "Nome squadra già usato per la stessa lega e anno.";
                return false;
            }
        }
        msg.clear(); return true;
    }
    bool checkV1_updateSquadra(SquadraRec s, string msg) {
        // allow same id; ensure no other squad with same (nome,lega,anno)
        for (auto &ex : squadre) {
            if (ex.id != s.id && ex.nome == s.nome && ex.lega == s.lega && ex.anno == s.anno) {
                msg = "Nome squadra già usato per la stessa lega e anno (da altra squadra).";
                return false;
            }
        }
        msg.clear(); return true;
    }
    // V2. Ogni calciatore ha id univoco.
    bool checkV2_newCalciatore(int id, string msg) {
        if (idxCalciatori.find(id) != idxCalciatori.end()) {
            msg = "ID calciatore già esistente.";
            return false;
        }
        msg.clear(); return true;
    }
    // V3. Ogni squadra deve avere almeno 5 calciatori.
    // We'll enforce this on deletion: do not allow deletion of squadre that still hanno calciatori.
    bool checkV3_squadraHasEnoughPlayers(int idSquadra) {
        int cnt = 0;
        for (auto &c : calciatori) if (c.idSquadra == idSquadra) ++cnt;
        return cnt >= 5;
    }
    // V4. Capitano deve appartenere alla squadra (se valorizzato).
    bool checkV4_captainForSquadra(int idCapitano, int idSquadra, string msg) {
        if (idCapitano == 0) { msg.clear(); return true; }
        auto it = idxCalciatori.find(idCapitano);
        if (it == idxCalciatori.end()) { msg = "Capitano non trovato fra i calciatori."; return false; }
        if (calciatori[it->second].idSquadra != idSquadra) { msg = "Il capitano non appartiene alla squadra indicata."; return false; }
        msg.clear(); return true;
    }
    // V5. più calciatori possono condividere lo stesso procuratore -> no constraint
    // V6. tutti i campi monetari >= 0; nAbbonati >= 0
    bool checkV6_money_nonNegative(double budget, int nAbbonati, string msg) {
        if (budget < 0) { msg = "Budget non può essere negativo."; return false; }
        if (nAbbonati < 0) { msg = "nAbbonati non può essere negativo."; return false; }
        msg.clear(); return true;
    }

    // ---------- CRUD Squadre ----------
    bool addSquadra(SquadraRec s_in, string &msg) {
        string localMsg;
        if (!checkV1_newSquadra(s_in, localMsg)) { msg = localMsg; return false; }
        if (!checkV6_money_nonNegative(s_in.budget, s_in.nAbbonati, localMsg)) { msg = localMsg; return false; }
        SquadraRec s = s_in;
        squadre.push_back(s);
        rebuildIndexes();
        saveSquadre();
        return true;
    }
    bool updateSquadra( SquadraRec s_in, string &msg) {
        auto it = idxSquadre.find(s_in.id);
        if (it == idxSquadre.end()) { msg = "Squadra non trovata."; return false; }
        string localMsg;
        if (!checkV1_updateSquadra(s_in, localMsg)) { msg = localMsg; return false; }
        if (!checkV6_money_nonNegative(s_in.budget, s_in.nAbbonati, localMsg)) { msg = localMsg; return false; }
        squadre[it->second] = s_in;
        rebuildIndexes();
        saveSquadre();
        return true;
    }
    bool deleteSquadra(int id, string &msg) {
        auto it = idxSquadre.find(id);
        if (it == idxSquadre.end()) { msg = "Squadra non trovata."; return false; }
        // Deletion policy: forbid if any calciatori assigned (to avoid violating V3)
        for (auto c : calciatori) if (c.idSquadra == id) {
            msg = "Impossibile eliminare la squadra: esistono calciatori assegnati. Rimuovere o riassegnare i calciatori prima.";
            return false;
        }
        squadre.erase(squadre.begin() + it->second);
        rebuildIndexes();
        saveSquadre();
        return true;
    }

    // ---------- CRUD Calciatori ----------
    bool addCalciatore(CalciatoreRec c_in, string &msg) {
        if (!checkV2_newCalciatore(c_in.id, msg)) return false;
        if (c_in.valore < 0 || c_in.ingaggio < 0) { msg = "Valore o ingaggio non possono essere negativi."; return false; }
        // idSquadra may be 0 (nessuna)
        // idProcuratore may be 0 (nessuno)
        CalciatoreRec c = c_in;
        calciatori.push_back(c);
        rebuildIndexes();
        saveCalciatori();
        return true;
    }
    bool updateCalciatore(CalciatoreRec c_in, string &msg) {
        auto it = idxCalciatori.find(c_in.id);
        if (it == idxCalciatori.end()) { msg = "Calciatore non trovato."; return false; }
        if (c_in.valore < 0 || c_in.ingaggio < 0) { msg = "Valore o ingaggio non possono essere negativi."; return false; }
        calciatori[it->second] = c_in;
        rebuildIndexes();
        saveCalciatori();
        return true;
    }
    bool deleteCalciatore(int id, string &msg) {
        auto it = idxCalciatori.find(id);
        if (it == idxCalciatori.end()) { msg = "Calciatore non trovato."; return false; }
        // If calciatore is captain of a squadra, clear that idCapitano
        for (auto &s : squadre) if (s.idCapitano == id) s.idCapitano = 0;
        calciatori.erase(calciatori.begin() + it->second);
        rebuildIndexes();
        saveCalciatori();
        saveSquadre();
        return true;
    }

    // ---------- CRUD Procuratori ----------
    // Deletion policy: when deleting a procuratore, set idProcuratore = 0 for referenced calciatori.
    bool addProcuratore(const ProcuratoreRec p_in, string &msg) {
        if (idxProcuratori.find(p_in.id) != idxProcuratori.end()) { msg = "ID procuratore già esistente."; return false; }
        procuratori.push_back(p_in);
        rebuildIndexes();
        saveProcuratori();
        return true;
    }
    bool updateProcuratore(const ProcuratoreRec p_in, string &msg) {
        auto it = idxProcuratori.find(p_in.id);
        if (it == idxProcuratori.end()) { msg = "Procuratore non trovato."; return false; }
        procuratori[it->second] = p_in;
        rebuildIndexes();
        saveProcuratori();
        return true;
    }
    bool deleteProcuratore(int id, string &msg) {
        auto it = idxProcuratori.find(id);
        if (it == idxProcuratori.end()) { msg = "Procuratore non trovato."; return false; }
        // Our chosen policy: aggiornare i calciatori che lo referenziano impostando idProcuratore=0
        for (auto &c : calciatori) {
            if (c.idProcuratore == id) c.idProcuratore = 0;
        }
        procuratori.erase(procuratori.begin() + it->second);
        rebuildIndexes();
        saveProcuratori();
        saveCalciatori();
        return true;
    }

    // ---------- Capitano ----------
    bool setCapitano(int idSquadra, int idCapitano, string &msg) {
        auto it = idxSquadre.find(idSquadra);
        if (it == idxSquadre.end()) { msg = "Squadra non trovata."; return false; }
        // V4: check capitano appartiene alla squadra
        string local;
        if (!checkV4_captainForSquadra(idCapitano, idSquadra, local)) { msg = local; return false; }
        squadre[it->second].idCapitano = idCapitano;
        saveSquadre();
        return true;
    }
    bool removeCapitano(int idSquadra, string &msg) {
        auto it = idxSquadre.find(idSquadra);
        if (it == idxSquadre.end()) { msg = "Squadra non trovata."; return false; }
        squadre[it->second].idCapitano = 0;
        saveSquadre();
        return true;
    }

    // ---------- Ricerche ----------
    string ricercaId(int id) {
        // Cerca in calciatori, procuratori, squadre e ritorna la riga raw (come prima, ma qui forniamo formattato)
        auto itc = idxCalciatori.find(id);
        if (itc != idxCalciatori.end()) {
            auto &c = calciatori[itc->second];
            ostringstream ss;
            ss << "Calciatore: " << c.id << " - " << c.cognome << " " << c.nome;
            return ss.str();
        }
        auto itp = idxProcuratori.find(id);
        if (itp != idxProcuratori.end()) {
            auto &p = procuratori[itp->second];
            ostringstream ss; ss << "Procuratore: " << p.id << " - " << p.cognome << " " << p.nome; return ss.str();
        }
        auto its = idxSquadre.find(id);
        if (its != idxSquadre.end()) {
            auto &s = squadre[its->second];
            ostringstream ss; ss << "Squadra: " << s.id << " - " << s.nome; return ss.str();
        }
        return "No";
    }

    // Ricerca per nome (case-insensitive) su calciatori/procuratori/squadre -> ritorna vettore di stringhe per risultato
    static string toLower(string s) {
        transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
            return tolower(c);
        });
        return s;
    }

    vector<string> ricercaNome(string q) {
        vector<string> res;
        string ql = toLower(q);
        for (auto &c : calciatori) {
            if (toLower(c.nome).find(ql) != string::npos || toLower(c.cognome).find(ql) != string::npos) {
                ostringstream ss; ss << "Calciatore: " << c.id << " - " << c.cognome << " " << c.nome;
                res.push_back(ss.str());
            }
        }
        for (auto &p : procuratori) {
            if (toLower(p.nome).find(ql) != string::npos || toLower(p.cognome).find(ql) != string::npos) {
                ostringstream ss; ss << "Procuratore: " << p.id << " - " << p.cognome << " " << p.nome;
                res.push_back(ss.str());
            }
        }
        for (auto &s : squadre) {
            if (toLower(s.nome).find(ql) != string::npos) {
                ostringstream ss; ss << "Squadra: " << s.id << " - " << s.nome << " (" << s.lega << " " << s.anno << ")";
                res.push_back(ss.str());
            }
        }
        return res;
    }

    // ---------- Interrogazioni obbligatorie ----------
    // 3a) Elencare tutti i calciatori (id; Cognome Nome; Squadra (nome); Lega; Valore; Ingaggio; Procuratore (cognome))
    void query3a_printAllCalciatori(ostream &out) {
        out << left << setw(6) << "ID" << setw(22) << "Cognome Nome" << setw(18) << "Squadra" << setw(6) << "Lega" << setw(12) << "Valore" << setw(12) << "Ingaggio" << setw(18) << "Procuratore" << '\n';
        out << string(100,'-') << '\n';
        for (auto &c : calciatori) {
            string squadraName = "-";
            char lega='-';
            auto its = idxSquadre.find(c.idSquadra);
            if (its != idxSquadre.end()) { squadraName = squadre[its->second].nome; lega = squadre[its->second].lega; }
            string procur = "-";
            auto itp = idxProcuratori.find(c.idProcuratore);
            if (itp != idxProcuratori.end()) procur = procuratori[itp->second].cognome;
            out << setw(6) << c.id
                << setw(22) << (c.cognome + " " + c.nome)
                << setw(18) << squadraName
                << setw(6) << lega
                << setw(12) << fixed << setprecision(2) << c.valore
                << setw(12) << fixed << setprecision(2) << c.ingaggio
                << setw(18) << procur
                << '\n';
        }
    }

    // 3b) Elencare calciatori che militano in una squadra fornita in input (ricerca per nome squadra case-insensitive; se più anni esistono, mostro tutte e chiedo l'anno)
    vector<CalciatoreRec> query3b_byTeamName(string teamName, int anno_filter = 0) {
        vector<CalciatoreRec> res;
        // trova squadre che matchano
        string q = toLower(teamName);
        vector<int> matchingSquadreIds;
        for (auto &s : squadre) {
            if (toLower(s.nome).find(q) != string::npos) {
                if (anno_filter == 0 || s.anno == anno_filter) matchingSquadreIds.push_back(s.id);
            }
        }
        if (matchingSquadreIds.empty()) return res;
        for (auto &c : calciatori) {
            if (find(matchingSquadreIds.begin(), matchingSquadreIds.end(), c.idSquadra) != matchingSquadreIds.end()) res.push_back(c);
        }
        return res;
    }

    // 3c) Elencare calciatori che militano in squadre con almeno 10000 abbonati
    vector<CalciatoreRec> query3c_minAbbonati(int minAbbonati=10000) {
        vector<int> squadreOk;
        for (auto &s : squadre) if (s.nAbbonati >= minAbbonati) squadreOk.push_back(s.id);
        vector<CalciatoreRec> res;
        for (auto &c : calciatori) if (find(squadreOk.begin(), squadreOk.end(), c.idSquadra) != squadreOk.end()) res.push_back(c);
        return res;
    }

    // ---------- Utility for sample data ----------
    void createSampleData() {
        // create 3 teams (A,B,C) for year 2025 each with >=5 players, 2 procuratori used by multiple players, set captain of 1 team
        procuratori.clear();
        ProcuratoreRec p1{1,"Mario","Rossi","PIVA1"};
        ProcuratoreRec p2{2,"Luca","Bianchi","PIVA2"};
        procuratori.push_back(p1);
        procuratori.push_back(p2);

        squadre.clear();
        squadre.push_back({1,"Juvenus",'A',2025,"Via A 1", 500000.0, 25000, 11});
        squadre.push_back({3,"Reggina",'C',2025,"Via C 3", 100000.0, 12000, 0});

        calciatori.clear();
        int cid = 1;
        // squadra 1 (>=5)
        for (int i=0;i<6;i++) {
            CalciatoreRec c;
            c.id = cid++;
            c.nome = "Nome"+to_string(c.id);
            c.cognome = "Cognome"+to_string(c.id);
            c.dataNascita = 19900101 + i;
            c.nazionalita = "ITA";
            c.valore = 1000000.0 - i*10000;
            c.ingaggio = 20000 + i*1000;
            c.idSquadra = 1;
            c.idProcuratore = (i%2==0) ? 1 : 2;
            calciatori.push_back(c);
        }
        // squadra 2
        for (int i=0;i<5;i++) {
            CalciatoreRec c;
            c.id = cid++;
            c.nome = "Nome"+to_string(c.id);
            c.cognome = "Cognome"+to_string(c.id);
            c.dataNascita = 19910101 + i;
            c.nazionalita = "ARG";
            c.valore = 200000.0 - i*5000;
            c.ingaggio = 15000 + i*500;
            c.idSquadra = 2;
            c.idProcuratore = (i%2==0) ? 1 : 2;
            calciatori.push_back(c);
        }
        // squadra 3
        for (int i=0;i<5;i++) {
            CalciatoreRec c;
            c.id = cid++;
            c.nome = "Nome"+to_string(c.id);
            c.cognome = "Cognome"+to_string(c.id);
            c.dataNascita = 19920101 + i;
            c.nazionalita = "BRA";
            c.valore = 120000.0 - i*3000;
            c.ingaggio = 10000 + i*400;
            c.idSquadra = 3;
            c.idProcuratore = (i%2==0) ? 1 : 2;
            calciatori.push_back(c);
        }
        // set captain of team 1 to first calciatore
        squadre[0].idCapitano = 1;

        rebuildIndexes();
    }

    // helper to pretty-print a calciatore vector (for queries)
    void printCalciatoriList(vector<CalciatoreRec> list, ostream &out) {
        out << left << setw(6) << "ID" << setw(22) << "Cognome Nome" << setw(18) << "Squadra" << setw(6) << "Lega" << setw(12) << "Valore" << setw(12) << "Ingaggio" << setw(18) << "Procuratore" << '\n';
        out << string(100,'-') << '\n';
        for (auto &c : list) {
            string squadraName = "-";
            char lega='-';
            auto its = idxSquadre.find(c.idSquadra);
            if (its != idxSquadre.end()) { squadraName = squadre[its->second].nome; lega = squadre[its->second].lega; }
            string procur = "-";
            auto itp = idxProcuratori.find(c.idProcuratore);
            if (itp != idxProcuratori.end()) procur = procuratori[itp->second].cognome;
            out << setw(6) << c.id
                << setw(22) << (c.cognome + " " + c.nome)
                << setw(18) << squadraName
                << setw(6) << lega
                << setw(12) << fixed << setprecision(2) << c.valore
                << setw(12) << fixed << setprecision(2) << c.ingaggio
                << setw(18) << procur
                << '\n';
        }
    }
};
