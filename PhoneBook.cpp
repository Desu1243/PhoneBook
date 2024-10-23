#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*  
*   Mateusz Luboñski
*   Implementation of linked list as a phone book
*/

struct Cell {
    string name;
    string number;
    Cell* next;
};

class PhoneBook {
    Cell* mainCell;

public:
    PhoneBook() {
        mainCell = nullptr;
    }

    void addRecord(string newName, string newNumber) {
        // creation of new data cell
        Cell* newCell = new Cell();
        newCell->name = newName;
        newCell->number = newNumber;
        newCell->next = nullptr;

        // adding new cell at the end of the list
        if (mainCell == nullptr) {
            mainCell = newCell;
        }
        else {
            Cell* temp = mainCell;
            while (temp->next != nullptr) {
                temp = temp->next;
            }

            temp->next = newCell;
        }
    }

    void deleteRecord(int index) {
        Cell* toDelete = mainCell;
        Cell* temp = nullptr;
        int count = 0;

        // finding cell to delete
        while (toDelete->next != nullptr) {
            count++;

            if (count == index)
                break;

            temp = toDelete;
            toDelete = toDelete->next;
        }

        // deleting first record if index = 0
        if (toDelete == mainCell) {
            if (mainCell->next == nullptr) {
                temp = mainCell;
                delete temp;
                mainCell = nullptr;
            }
            else {
                temp = mainCell->next;
                delete mainCell;
                mainCell = temp;
            }
            return;
        }

        // deleting cell on selected index
        temp->next = toDelete->next;
        delete toDelete;
    }

    void printRecords() {
        if (mainCell == nullptr) {
            cout << "Lista kontakow jest pusta \n";
        }
        else {
            //TODO
            // format printing so it will show a nice table with the same width for every cell

            int count = 1;
            Cell* temp = mainCell;
            cout << count << ". " << temp->name << " " << temp->number << endl;

            while (temp->next != nullptr) {
                temp = temp->next;
                count++;
                cout << count << ". " << temp->name << " " << temp->number << endl;
            }
        }
    }

    int count() {
        int count = 0;
        if (mainCell != nullptr) {
            count = 1;
            Cell* temp = mainCell;

            while (temp->next != nullptr) {
                temp = temp->next;
                count++;
            }
        }
        return count;
    }

    // save contacts in file
    void saveToFile() {
        ofstream outputFile("kontakty.txt");
        Cell* temp = mainCell;
        string contact;

        while (temp != nullptr) {
            contact = temp->name + ";" + temp->number + "\n";
            outputFile << contact;
            temp = temp->next;
        }
        
        outputFile.close();
    }

    // read contacts from file
    void readFromFile() {
        string contact, name, number;
        bool numberSection;

        ifstream inputFile("kontakty.txt");

        while (getline(inputFile, contact)) {
            name = "";
            number = "";
            numberSection = false;
            for (int i = 0; i < contact.length(); i++) {
                if (contact[i] == ';') {
                    numberSection = true;
                    continue;
                }

                if (numberSection) {
                    number += contact[i];
                }
                else {
                    name += contact[i];
                }

            }
            addRecord(name, number);
        }
    }

};

void printCommands() {
    cout << endl << "Dostepne komendy: w - wypisz kontakty; d - dodaj kontakt; u - usun kontakt; z - zamknij program." << endl;
    cout << "Wybrana komenda: ";
}

int main()
{
    PhoneBook phoneBook = PhoneBook();
    
    // z - exit; w - print records; d - add new record; u - delete record
    char command = '0';
    string name, lastname, number;
    int toRemove;

    phoneBook.readFromFile();
    cout << "Kasiazka telefoniczna" << endl;
    
    do {
        printCommands();
        cin >> command;

        switch (command) {
        case 'W':
        case 'w':
            // print records from phone book
            phoneBook.printRecords();
            break;

        case 'D':
        case 'd':
            // add new record to the phone book
            cout << "Dodawanie nowego kontaktu.\nImie: ";
            cin >> name;
            cout << "Nazwisko: ";
            cin >> lastname;
            cout << "Numer telefonu: ";
            cin >> number;
            name = name + " " + lastname;
            phoneBook.addRecord(name, number);

            phoneBook.saveToFile();
            break;

        case 'U':
        case 'u':
            // remove selected record from the phone book
            cout << "Wybierz kontakt do usuniecia: ";
            cin >> toRemove;
            if (phoneBook.count() >= toRemove && toRemove > 0) {
                phoneBook.deleteRecord(toRemove);
                phoneBook.saveToFile();
                cout << "Usunieto kontakt nr " << toRemove << endl;
            }
            else {
                cout << "Wybrano niepoprawny numer kontaktu.";
            }
            break;
        case 'Z':
        case 'z':
            cout << "Zamykanie programu.";
            break;
        default:
            cout << "Niepoprawna komenda.";
        }

    } while (command != 'z');
    
    return 0;
}