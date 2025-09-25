#include <string>       // Per string
#include <iostream>     // Per cout, cin
#include <limits>       // Per numeric_limits
using namespace std;

//Preparare un campo di testo da salvare in CSV, evitando problemi con i caratteri riservati
static string escape_csv_field(string s) {
    string out;
    for (char c : s) {
        if (c == ';') { out += "\\;"; }
        else if (c == '\n') { out += "\\n"; }
        else if (c == '\\') { out += "\\\\"; }
        else out += c;
    }
    return out;
}

//Legge un campo dal CSV e lo riporta al formato originale
static string unescape_csv_field(string s) {
    string out;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '\\' && i + 1 < s.size()) {
            char next = s[i+1];
            if (next == ';') { out += ';'; ++i; }
            else if (next == 'n') { out += '\n'; ++i; }
            else if (next == '\\') { out += '\\'; ++i; }
            else out += next;
        } else out += s[i];
    }
    return out;
}

/* =========================
   === CLI / Main loop ===
   ========================= */

static int readIntSafe(const string &prompt) {
    int v;
    while (true) {
        cout << prompt;
        if (cin >> v) { cin.ignore(numeric_limits<streamsize>::max(), '\n'); return v; }
        else { cout << "Input non valido, riprova.\n"; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
    }
}
static double readDoubleSafe(const string &prompt) {
    double v;
    while (true) {
        cout << prompt;
        if (cin >> v) { cin.ignore(numeric_limits<streamsize>::max(), '\n'); return v; }
        else { cout << "Input non valido, riprova.\n"; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
    }
}
static string readLine(const string &prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

void stampaMenu() {
    cout << "\n=== MENU PRINCIPALE ===\n";
    cout << "1. Operazioni su Squadra\n";
    cout << "2. Operazioni su Calciatore\n";
    cout << "3. Operazioni su Procuratore\n";
    cout << "4. Imposta/Rimuovi Capitano di una Squadra\n";
    cout << "5. Stampa riepilogo di una Squadra\n";
    cout << "6. Ricerca per ID\n";
    cout << "7. Ricerca per nome (case-insensitive)\n";
    cout << "8. Interrogazioni (3a-3c)\n";
    cout << "9. Esporta risultati in CSV\n";
    cout << "0. Salva e Esci\n";
}