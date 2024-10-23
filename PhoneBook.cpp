#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*  Mateusz Luboñski
*   Console phone book aplication with linked list
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
                delete mainCell;
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

    }

    // read contacts from file
    void readFromFile() {

    }

};


void printCommands() {
    cout << endl << "w - wypisz kontakty; d - dodaj kontakt; u - usun kontakt; z - zamknij program" << endl;
    cout << "Wybrana operacja: ";
}

int main()
{
    PhoneBook phoneBook = PhoneBook();
    char command = '0'; // z - exit; w - print records; d - add new record; u - delete record
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
            }
            else {
                cout << "Wybrano niepoprawny numer kontaktu.";
            }
            break;
        default:
            cout << "Niepoprawna komenda.";
        }

    } while (command != 'z');
    
    return 0;
}