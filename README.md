**MoKoffe — Coffee Chain Management System**

MoKoffe is a modular C++17 application for managing products and employees across a coffee shop chain.
It demonstrates strong object-oriented design, templates, exception safety, and modern C++ architecture.

Features:
	•	Manage products and employees (add, remove, list)
	•	Read and write data from CSV files
	•	Clear and modular class structure
	•	Extensible architecture for future components (e.g. locations, sales)
	•	Fully object-oriented implementation

Key C++ Concepts:
| Concept | Example in Code MoKoffe |

| Classes & Objects | Produs, Angajat, GestionareProduse, GestionareAngajati |
| Constructors / Destructors | Parameterized constructors, virtual destructors |
| Encapsulation | Private data + public getters/setters |
| Inheritance | Barista, Manager, Ospatar inherit from Angajat |
| Polymorphism | Virtual afiseazaDetalii() overridden in derived classes |
| Abstraction | Clean public interfaces hiding implementation details |
| Templates | std::vector<Produs>, std::unique_ptr<Angajat> |
| Exceptions | throw invalid_argument() in factory method |
| Design Patterns | Factory Method, RAII (smart pointers), SRP / SOLID principles |

Technologies Used:
	•	C++17
	•	STL Containers (vector, unordered_map)
	•	Smart Pointers (unique_ptr)
	•	CSV File I/O
	•	UML Architecture Design

MoKoffe is built as a learning and demonstration project to showcase:
	•	Correct and modern OOP design in C++
	•	Clean architecture and separation of concerns
	•	Safe memory management (RAII)
	•	Extensible and maintainable code structure
