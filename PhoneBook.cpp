#include <iostream>

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

    // save data in file
    void saveToFile() {

    }

    void readFromFile() {

    }

};


int main()
{
    PhoneBook phoneBook = PhoneBook();

    //TODO:
    //read data from file
    //in loop:
    //get command from user 
    // - display data 
    // - add new record 
    // - delete selected record 
    // - save data in file
    // - quit app

    phoneBook.addRecord("Jan Kowal", "321654987");
    phoneBook.addRecord("Michal Kowal", "123456789");
    phoneBook.addRecord("Ola Gwozdz", "918273645");
    phoneBook.printRecords();

    phoneBook.deleteRecord(2);
    phoneBook.printRecords();

}