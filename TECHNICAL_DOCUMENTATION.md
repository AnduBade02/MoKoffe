# Technical Documentation — MoKoffe

## 1. General Overview

**MoKoffe** is a console application written in **C++17** for managing a coffee shop chain. It allows administering employees, products, events, and finances across 5 locations (Bucharest, Cluj, Timișoara, Iași, Brașov). Data is persisted in CSV files organized in per-city directories.

---

## 2. Technologies and Tools Used

| Technology | Usage |
|---|---|
| **C++17** | Language standard used throughout the project |
| **CMake 3.31** | Build system for cross-platform compilation |
| **Ninja** | Build generator used by CLion (build.ninja) |
| **CLion / JetBrains** | IDE used for development (`.idea/` configuration) |
| **STL (Standard Template Library)** | Standard C++ containers and algorithms |
| **CSV** | File format for persistent data storage |

---

## 3. Project Structure

```
MoKoffe/
├── CMakeLists.txt              # Build configuration
├── main.cpp                    # Entry point, interactive menus
├── GestionareAngajati.h/.cpp   # Employee module (full OOP hierarchy)
├── GestionareProduse.h/.cpp    # Product module
├── GestionareFinante.h/.cpp    # Financial module (reports, calculations)
├── GestionareCSV.h/.cpp        # CSV header internationalization module
├── GestionareEvenimente.h/.cpp # Event management module
└── cmake-build-debug/
    └── Orase/
        ├── Bucuresti/          # angajati.csv, produse.csv, comenzi.csv,
        ├── Cluj/               # evenimente.csv, raport.csv
        ├── Timisoara/
        ├── Iasi/
        └── Brasov/
```

---

## 4. Object-Oriented Programming (OOP) Concepts

### 4.1 Classes and Objects

The application defines 7 main classes, each with a clearly defined responsibility:

| Class | Responsibility |
|---|---|
| `Angajat` | Base class for employees |
| `Barista`, `Manager`, `Ospatar` | Derived classes, concrete employee types |
| `GestionareAngajati` | Container + CRUD operations on employees |
| `Produs` | Data model for a menu product |
| `GestionareProduse` | Container + CRUD operations on products |
| `GestionareFinante` | Revenue/cost calculations and report generation |
| `GestionareCSV` | CSV header internationalization management |
| `GestionareEvenimente` | Event management per location |
| `Event` | Data model for an event |

In addition to classes, the application defines two **structs**:
- `GestionareFinante::Comanda` — stores an order (quantities per product + loyalty flag)
- `Eveniment` — stores event type and price (used internally in `GestionareFinante`)

---

### 4.2 Encapsulation

All class attributes are declared `private` or `protected`, with external access exclusively through public getter/setter methods.

**Concrete examples:**

```cpp
// GestionareAngajati.h
class Angajat {
protected:
    string nume;
    string functie;
    int oraInceput;
    int oraSfarsit;
    double salariu;
public:
    double getSalariu() const;
    string getNume() const;
    // ...
};
```

```cpp
// GestionareCSV.h
class GestionareCSV {
private:
    std::string limba;
    std::unordered_map<...> hartaHeadere;
public:
    std::vector<std::string> getHeadere(const std::string& numeFisier);
    // ...
};
```

Benefits applied:
- Attributes cannot be modified directly from outside the class
- Validation logic can be centralized in class methods
- Changing the internal implementation does not affect client code

---

### 4.3 Inheritance

Public single inheritance is used with a two-level hierarchy:

```
Angajat  (base class)
├── Barista   : public Angajat
├── Manager   : public Angajat
└── Ospatar   : public Angajat
```

**Implementation:**
```cpp
class Barista : public Angajat {
public:
    Barista(const string& nume, int oraInceput, int oraSfarsit, double salariu);
    void afiseazaDetalii() const override;
};
```

Derived class constructors explicitly call the base class constructor via the initialization list:
```cpp
Barista::Barista(const string& nume, int oraInceput, int oraSfarsit, double salariu)
    : Angajat(nume, "Barista", oraInceput, oraSfarsit, salariu) {}
```

---

### 4.4 Polymorphism

**Dynamic polymorphism** is used through virtual functions (`virtual`) and their overrides (`override`) in derived classes.

**Declaration in the base class:**
```cpp
class Angajat {
public:
    virtual void afiseazaDetalii() const;   // virtual method
    virtual ~Angajat() = default;           // virtual destructor
};
```

**Override in derived classes:**
```cpp
void Barista::afiseazaDetalii() const override {
    cout << "[Barista] ";
    Angajat::afiseazaDetalii();   // explicit call to parent method
}
```

**Polymorphic call:**
```cpp
// GestionareAngajati.cpp — iterates over vector<unique_ptr<Angajat>>
for (const auto& angajat : angajati) {
    angajat->afiseazaDetalii(); // dynamic dispatch, correct method per type
}
```

The **virtual destructor** is essential when derived objects are deleted through a base class pointer — it prevents memory leaks by ensuring the correct destructor is called.

---

### 4.5 Abstraction

Abstraction is achieved by exposing simple interfaces that hide implementation details:

- `citesteDinCSV(numeFisier)` — hides CSV parsing
- `scrieInCSV(numeFisier)` — hides CSV serialization
- `schimbaToateHeaderelePentruOrase(orase)` — single call to update all files across all cities
- `creeazaAngajat(tip, ...)` — Factory Method that hides concrete instantiation logic

---

## 5. Constructors and Destructors

### 5.1 Parameterized Constructors

All constructors use the **initialization list**, the preferred form in modern C++:

```cpp
Angajat::Angajat(const string& nume, const string& functie,
                 int oraInceput, int oraSfarsit, double salariu)
    : nume(nume), functie(functie),
      oraInceput(oraInceput), oraSfarsit(oraSfarsit),
      salariu(salariu) {}
```

### 5.2 Default Constructor

`Event` defines an explicit default constructor to allow initialization with default values:
```cpp
Event() : nume(""), pret(0.0) {}
```

### 5.3 Constructor with Default Parameter Value

`GestionareCSV` uses a parameter with a default value:
```cpp
GestionareCSV(const std::string& limba = "ro");
```

### 5.4 Virtual Destructor

```cpp
virtual ~Angajat() = default;
```

`= default` instructs the compiler to generate the default destructor, while `virtual` guarantees correct dispatch in a polymorphic context.

---

## 6. Design Patterns

### 6.1 Factory Method

`GestionareAngajati::creeazaAngajat` is a **static factory method** that creates concrete objects based on a string type parameter, returning a pointer to the base class:

```cpp
static unique_ptr<Angajat> creeazaAngajat(
    const string& tip, const string& nume,
    int oraInceput, int oraSfarsit, double salariu) {
    if (tip == "Barista")  return make_unique<Barista>(...);
    if (tip == "Manager")  return make_unique<Manager>(...);
    if (tip == "Ospatar")  return make_unique<Ospatar>(...);
    throw invalid_argument("Tipul de angajat nu este valid: " + tip);
}
```

Benefits:
- Decouples client code from concrete types
- Centralizes creation logic
- Enables easy extensibility (adding a new type does not affect client code)

### 6.2 RAII (Resource Acquisition Is Initialization)

All dynamic memory is managed through **smart pointers** (`std::unique_ptr`), not manual `new`/`delete`:

```cpp
vector<unique_ptr<Angajat>> angajati;
// ...
angajati.push_back(move(angajat));  // ownership transfer
```

Files are opened and closed within local scopes (`ifstream`/`ofstream` with limited lifetime), guaranteeing resource release even in the event of exceptions.

### 6.3 Single Responsibility Principle (SRP — from SOLID)

Each class has a single responsibility:
- `GestionareAngajati` — employee CRUD only
- `GestionareProduse` — product CRUD only
- `GestionareFinante` — financial calculations only
- `GestionareCSV` — CSV header internationalization only
- `GestionareEvenimente` — event CRUD only

---

## 7. Smart Pointers and Move Semantics

### 7.1 `std::unique_ptr`

Used for managing employees with exclusive ownership:
```cpp
vector<unique_ptr<Angajat>> angajati;
```

`unique_ptr` guarantees the object is automatically destroyed when it goes out of scope, eliminating the need for manual `delete`.

### 7.2 `std::make_unique`

Template function for constructing a `unique_ptr` without an explicit `new`:
```cpp
return make_unique<Barista>(nume, oraInceput, oraSfarsit, salariu);
```

### 7.3 `std::move`

`unique_ptr` cannot be copied (copy-constructor is deleted). Ownership transfer is done through `std::move`:
```cpp
angajati.push_back(move(angajat)); // transfers ownership
```

---

## 8. Templates

The project makes extensive use of STL templates without defining custom ones:

| Container / Template | Usage |
|---|---|
| `std::vector<Angajat>` | Employee list |
| `std::vector<unique_ptr<Angajat>>` | Employee list with exclusive ownership |
| `std::vector<Produs>` | Product list |
| `std::vector<Event>` | Event list |
| `std::vector<Eveniment>` | Event list inside the financial module |
| `std::vector<Comanda>` | Order list |
| `std::vector<string>` | CSV header lists, city lists |
| `std::unordered_map<string, unordered_map<string, vector<string>>>` | Nested header map per language and file type |
| `std::unique_ptr<Angajat>` | Polymorphic smart pointer |

---

## 9. STL — Algorithms and Iterators

### 9.1 `std::remove_if` with Lambda Expression

Used for predicate-based deletion from vectors:

```cpp
// GestionareAngajati.cpp
auto it = remove_if(angajati.begin(), angajati.end(),
    [&nume](const unique_ptr<Angajat>& angajat) {
        return angajat->getNume() == nume;
    });
if (it != angajati.end()) {
    angajati.erase(it, angajati.end()); // erase-remove idiom
}
```

The same pattern is used in `GestionareProduse::eliminaProdus` and `GestionareEvenimente::eliminaEvent`.

### 9.2 The Erase-Remove Idiom

`remove_if` does not actually delete elements; it moves them to the end of the container and returns an iterator to the first "removed" element. `erase` performs the actual deletion — this is the standard **erase-remove idiom** in C++.

### 9.3 Range-Based For Loop

```cpp
for (const auto& angajat : angajati) { ... }
for (const string& oras : orase) { ... }
```

### 9.4 `vector::emplace_back`

Constructs the object directly inside the container, avoiding an unnecessary copy:
```cpp
evenimente.emplace_back(nume, pret);
produse.emplace_back(nume, stoc, costAchizitie, costVanzare);
```

---

## 10. Lambda Expressions

Lambdas are used as predicates for `remove_if`:

```cpp
[&nume](const unique_ptr<Angajat>& angajat) {
    return angajat->getNume() == nume;
}
```

Syntax breakdown:
- `[&nume]` — capture by reference of the outer-scope variable `nume`
- Formal parameter: const reference to the vector element
- Body: the removal condition

---

## 11. Exception Handling

### 11.1 Exceptions Thrown

| Location | Exception Type | Condition |
|---|---|---|
| `GestionareAngajati::creeazaAngajat` | `invalid_argument` | Unknown employee type |
| `GestionareAngajati::stergeAngajat` | `invalid_argument` | Employee not found |
| `GestionareAngajati::citesteDinCSV` | `runtime_error` | CSV file inaccessible |
| `GestionareProduse::citesteDinCSV` | `runtime_error` | CSV file inaccessible |
| `GestionareProduse::eliminaProdus` | `invalid_argument` | Product not found |
| `GestionareFinante::citesteComenziDinCSV` | `runtime_error` | CSV file inaccessible |
| `GestionareFinante::citesteEvenimenteDinCSV` | `runtime_error` | CSV file inaccessible |
| `GestionareEvenimente::citesteDinCSV` | `runtime_error` | CSV file inaccessible |
| `GestionareEvenimente::eliminaEvent` | `invalid_argument` | Event not found |
| `main.cpp` | `invalid_argument` | Invalid language option |

### 11.2 Global Try-Catch Block

`main()` contains a hierarchical try-catch block catching all exception types:

```cpp
try {
    // ... entire application logic
} catch (const runtime_error& e) {
    cerr << "Eroare: " << e.what() << endl;
} catch (const invalid_argument& e) {
    cerr << "Argument invalid: " << e.what() << endl;
} catch (const exception& e) {
    cerr << "Eroare generala: " << e.what() << endl;
}
```

The catch order goes from specific to general — both `runtime_error` and `invalid_argument` are derived from `std::exception`.

---

## 12. File I/O Operations

### 12.1 CSV Reading (`ifstream` + `istringstream`)

```cpp
ifstream fisier(numeFisier);
string linie;
getline(fisier, linie); // skip header

while (getline(fisier, linie)) {
    istringstream stream(linie);
    getline(stream, field, ','); // text field
    stream >> numericValue;
    stream.ignore(1);            // skip ','
}
```

### 12.2 CSV Writing (`ofstream`)

Append mode for reports:
```cpp
ofstream fisier(numeFisier, ios::app); // appends to end of file
```

Truncate mode for updating lists:
```cpp
ofstream fisier(numeFisier); // overwrites existing file
```

### 12.3 Header Manipulation (`stringstream::rdbuf`)

`GestionareCSV` reads the entire file content into memory, replaces the first line, and rewrites it:
```cpp
stringstream buffer;
buffer << infile.rdbuf();           // read into buffer
string continut = buffer.str();
size_t poz = continut.find("\n");   // find first line
continut.replace(0, poz + 1, headerNou); // replace header
```

---

## 13. Internationalization (CSV Localization)

`GestionareCSV` implements support for two languages (Romanian / English) by mapping CSV headers:

```
hartaHeadere["ro"]["angajati.csv"] = {"Nume", "Functie", "OraInceput", "OraSfarsit", "Salariu"}
hartaHeadere["en"]["angajati.csv"] = {"Name", "Position", "StartHour", "EndHour", "Salary"}
```

The `unordered_map<string, unordered_map<string, vector<string>>>` structure is a **nested map** (language → file type → header list).

At startup, `schimbaToateHeaderelePentruOrase` updates **all files across all 5 cities** with the headers corresponding to the selected language.

---

## 14. Time Management (`<ctime>`)

`GestionareFinante` uses functions from `<ctime>` to timestamp reports:

```cpp
#include <ctime>
// ...
std::time_t timpCurent = std::time(nullptr);
std::tm* timpLocal = std::localtime(&timpCurent);
std::ostringstream buffer;
buffer << std::put_time(timpLocal, "%Y-%m-%d %H:%M:%S");
```

`put_time` comes from `<iomanip>` and formats the `std::tm` structure as a string.

---

## 15. Persistent Data Structure (CSV)

Each location has 5 CSV files with fixed schemas:

### `angajati.csv`
```
Nume,Functie,OraInceput,OraSfarsit,Salariu
Maria Ionescu,Manager,9,17,200
```

### `produse.csv`
```
produse,stoc,costAchizitie,costVanzare
Cafea Espresso,90,2,5
```

### `comenzi.csv`
```
CafeaEspresso,CafeaLatte,DesertBrownie,BaghetaCrispy,CiocolataCalda,CafeaAmericano,Fidelitate
3,2,1,0,1,0,1
```

### `evenimente.csv`
```
Eveniment,Pret
Concert Jazz,500
```

### `raport.csv` (append mode)
```
venituri,costuri,salarii,profit,dataora
1250.5,890.0,440,360.5,2025-01-09 19:30:00
```

---

## 16. Financial Logic

### 16.1 Order Price Calculation

Iterates through products in `GestionareProduse` and applies the sale cost per ordered quantity. If `fidelitate == true`, a **10% discount** is applied:

```cpp
double aplicaReducere(double pretTotal, bool fidelitate) const {
    if (fidelitate) return pretTotal * 0.90;
    return pretTotal;
}
```

### 16.2 Event Cost Calculation (Stochastic Element)

`calculeazaCostEvenimente()` implements a random component:
- The `rand()` generator is initialized once (`static bool initializat`)
- With a 1/7 probability, returns the average event cost
- Otherwise returns 0

### 16.3 Financial Report Generation

The report contains: `total revenue`, `total costs` (products + events), `salaries`, `profit`, `date and time`.

---

## 17. Header / Implementation Separation

The project follows the classic C++ separation between interface and implementation:

- `.h` files contain: class declarations, method prototypes, `#ifndef` guards
- `.cpp` files contain: method definitions, required includes

**Include guards** prevent multiple inclusion:
```cpp
#ifndef GESTIONARE_ANGAJATI_H
#define GESTIONARE_ANGAJATI_H
// ...
#endif
```

---

## 18. CMake Configuration

```cmake
cmake_minimum_required(VERSION 3.31)
project(MoKoffe)

set(CMAKE_CXX_STANDARD 17)

add_executable(MoKoffe
    main.cpp
    GestionareAngajati.h GestionareAngajati.cpp
    GestionareProduse.h  GestionareProduse.cpp
    GestionareFinante.h  GestionareFinante.cpp
    GestionareCSV.h      GestionareCSV.cpp
    GestionareEvenimente.h GestionareEvenimente.cpp
)
```

`CMAKE_CXX_STANDARD 17` enables all C++17 features (`if constexpr`, structured bindings, `std::filesystem`, etc., even if not all are explicitly used).

---

## 19. Application Main Flow

```
START
  │
  ├─ Language selection (ro/en)
  │   └─ Create GestionareCSV with selected language
  │       └─ Update CSV headers for all 5 cities
  │
  └─ Main loop (do-while): select coffee shop
       │
       ├─ Load data: angajati.csv, produse.csv, comenzi.csv, evenimente.csv
       │
       └─ Coffee shop menu (do-while):
            ├─ 1. Employee Management
            │     └─ Add/Modify/Delete/Display (full CRUD)
            ├─ 2. Product Management
            │     └─ Add/Modify/Delete/Display (full CRUD)
            ├─ 3. Finance Management
            │     └─ Generate report / Display report
            ├─ 4. Event Management
            │     └─ Add/Modify/Delete/Display (full CRUD)
            └─ 5. Exit coffee shop
```

---

## 20. Concept Summary Table

| Category | Concept | Present in Project |
|---|---|---|
| **OOP** | Classes and Objects | Yes |
| **OOP** | Encapsulation | Yes |
| **OOP** | Single Inheritance | Yes |
| **OOP** | Dynamic Polymorphism | Yes |
| **OOP** | Abstraction | Yes |
| **Modern C++** | Constructors with initialization list | Yes |
| **Modern C++** | Virtual destructor | Yes |
| **Modern C++** | Default / default-parameter constructors | Yes |
| **Modern C++** | `unique_ptr` (smart pointer) | Yes |
| **Modern C++** | `make_unique` | Yes |
| **Modern C++** | `std::move` (move semantics) | Yes |
| **Modern C++** | Lambda expressions | Yes |
| **Modern C++** | Explicit `override` | Yes |
| **Modern C++** | `= default` | Yes |
| **Modern C++** | Range-based for | Yes |
| **Modern C++** | `auto` | Yes |
| **Design Patterns** | Factory Method | Yes |
| **Design Patterns** | RAII | Yes |
| **Design Patterns** | Single Responsibility Principle | Yes |
| **STL** | `std::vector` | Yes |
| **STL** | `std::unordered_map` | Yes |
| **STL** | `std::remove_if` (erase-remove idiom) | Yes |
| **STL** | `emplace_back` | Yes |
| **STL** | Iterators | Yes |
| **Exceptions** | `throw` / `try` / `catch` | Yes |
| **Exceptions** | `runtime_error` | Yes |
| **Exceptions** | `invalid_argument` | Yes |
| **Exceptions** | `std::exception` (general catch) | Yes |
| **I/O** | `ifstream` / `ofstream` | Yes |
| **I/O** | `istringstream` / `ostringstream` | Yes |
| **I/O** | `stringstream::rdbuf` | Yes |
| **I/O** | `ios::app` (append mode) | Yes |
| **I/O** | `getline` | Yes |
| **Time** | `std::time`, `std::localtime`, `std::put_time` | Yes |
| **Structs** | `struct` (Comanda, Eveniment) | Yes |
| **Preprocessor** | Include guards (`#ifndef`) | Yes |
| **Build** | CMake | Yes |
| **Build** | Ninja | Yes |
| **Storage** | Per-location CSV files | Yes |
| **Internationalization** | Bilingual headers (ro/en) | Yes |
