# Archivio “Campionati di Calcio” – Progetto C++

<h2 style="color:blue;">Scelte Progettuali</h2>


- **Linguaggio:** C++
- **Persistenza:** File CSV ([`squadre.csv`](squadre.csv), [`calciatori.csv`](calciatori.csv), [`procuratori.csv`](procuratori.csv)) con separatore `;` e escaping minimo per caratteri speciali.
- **Struttura dati:**  
  - Le entità principali (`Squadra`, `Calciatore`, `Procuratore`) sono rappresentate da struct (`SquadraRec`, `CalciatoreRec`, `ProcuratoreRec`).
  - I dati sono gestiti in memoria tramite `std::vector` per i record e `std::unordered_map` per accesso rapido per ID.
- **Modularità:**  
  - La logica di gestione (CRUD, vincoli, query) è centralizzata nella classe [`DataStore`](https://github.com/zuc7/database/blob/main/Gestione.cpp#L45) in `Gestione.cpp`.
  - Le funzioni di utilità e input sicuro sono in [`Util.cpp`](Util.cpp).
- **Vincoli di business:**  
  - Validazione centralizzata: unicità degli ID, nome squadra unico per lega/anno, campi monetari non negativi, almeno 5 calciatori per squadra, capitano appartenente alla squadra, ecc.
- **CLI:**  
  - Interfaccia a menu testuale, input validato, messaggi d’errore chiari.

---

## Formato dei File CSV

- **squadre.csv**  
  `id;nome;lega;anno;indirizzo;budget;nAbbonati;idCapitano`
- **calciatori.csv**  
  `id;nome;cognome;dataNascita;nazionalità;valore;ingaggio;idSquadra;idProcuratore`
- **procuratori.csv**  
  `id;nome;cognome;piva`

**Nota:**  
I campi sono separati da `;`.  
Caratteri speciali nei campi sono gestiti tramite escaping (ad esempio `\;` per il punto e virgola, `\n` per newline).

---

## Come eseguire le query 3a–3c

Dopo aver avviato il programma (`calcioDB.exe`):

**3a) Elenco di tutti i calciatori**  
- Dal menu principale, scegli l’opzione "Interrogazioni" e poi "Elencare tutti i calciatori (3a)".
- Verrà mostrata una tabella con: idCalciatore, Cognome Nome, Squadra, Lega, Valore (€), Ingaggio (€), Procuratore.

**3b) Elenco calciatori di una squadra**  
- Scegli l’opzione "Interrogazioni" e poi "Calciatori di una squadra (3b)".
- Inserisci il nome della squadra (case-insensitive).
- Se la squadra esiste in più anni, scegli l’anno desiderato.
- Verrà mostrato l’elenco dei calciatori corrispondenti.

**3c) Elenco calciatori in squadre con almeno 10.000 abbonati**  
- Scegli l’opzione "Interrogazioni" e poi "Calciatori in squadre con ≥10.000 abbonati (3c)".
- Verrà mostrato l’elenco filtrato.

**Esportazione CSV:**  
- Dopo ogni query, puoi scegliere di esportare il risultato in un file CSV tramite l’apposita opzione del menu.

---

## Come riprodurre i test minimi

- Al primo avvio, se i file CSV non esistono, il programma genera automaticamente:
  - **3 squadre** (una per lega) nell’anno scelto, ciascuna con almeno 5 calciatori.
  - **Almeno 2 procuratori** usati da più calciatori.
  - **Capitano** impostato per almeno una squadra.
- Puoi verificare la correttezza dei dati stampando i riepiloghi dal menu e provando le interrogazioni.

---

## File principali

### [**Final.cpp**](final.cpp)
Questo file rappresenta il punto di ingresso del programma.  
Gestisce il ciclo principale dell’applicazione, mostrando il menu CLI all’utente e gestendo tutte le interazioni.  
Le operazioni disponibili includono:
- Inserimento, modifica e rimozione di squadre, calciatori e procuratori (CRUD)
- Impostazione e rimozione del capitano di una squadra
- Stampa riepilogo dettagliato di una squadra con elenco calciatori
- Ricerca per ID e per nome (case-insensitive) su tutte le entità
- Esecuzione delle interrogazioni richieste (3a: elenco calciatori, 3b: calciatori di una squadra, 3c: calciatori in squadre con almeno 10.000 abbonati)
- Esportazione dei risultati delle query in file CSV
- Salvataggio automatico dei dati all’uscita

Il file si appoggia alle funzioni e ai dati gestiti dalla classe `DataStore` (in `Gestione.cpp`) e alle utility di input/output definite in `Util.cpp`.

---

### [**Gestione.cpp**](Gestione.cpp)
Questo file contiene la logica centrale del database:
- Definisce le struct delle entità principali: `SquadraRec`, `CalciatoreRec`, `ProcuratoreRec`
- Implementa la classe `DataStore`, che gestisce:
  - I dati in memoria tramite `std::vector` e accesso rapido tramite `std::unordered_map`
  - Le operazioni CRUD per tutte le entità
  - La validazione dei vincoli di business (unicità, referenzialità, campi monetari, numero minimo calciatori, ecc.)
  - Il caricamento e salvataggio dei dati su file CSV
  - Le interrogazioni richieste dalla consegna (3a, 3b, 3c)
  - La generazione automatica dei dati di test minimi al primo avvio, se i file non esistono

`Gestione.cpp` è il cuore della logica applicativa e si occupa di mantenere la coerenza dei dati e di fornire tutte le funzionalità richieste dal menu.

---

### [**Util.cpp**](Util.cpp)
Questo file raccoglie tutte le funzioni di utilità comuni:
- Funzioni per l’input sicuro da console (`readIntSafe`, `readDoubleSafe`, `readLine`)
- Funzioni per l’escaping e l’unescaping dei campi CSV, per gestire correttamente caratteri speciali come `;` e newline
- Funzione per la stampa del menu principale

Le funzioni di `Util.cpp` sono utilizzate sia nel ciclo principale (`final.cpp`) che nella logica di gestione (`Gestione.cpp`) per garantire robustezza nell’input e correttezza nella gestione dei file CSV.

---

**In sintesi:**  
Questa suddivisione permette di mantenere il codice organizzato, modulare e facilmente estendibile.  
Ogni file ha una responsabilità chiara:  
- `final.cpp` gestisce l’interfaccia utente e il flusso principale  
- `Gestione.cpp` gestisce i dati, la logica e i vincoli  
- `Util.cpp` fornisce strumenti di supporto per input e gestione dei file CSV


