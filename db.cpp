#include <fstream>
#include <iostream>
#include "db.h"
#include <cstdio>

using namespace std;

const string DB_FILE = "data.db";


/**
 * @brief Insert a record into the database
 *
 * This function will ask the user to input the id, name and age of a record.
 * It will then write this record to the database file.
 *
 * @details The function will open the database file in append mode and write the record to it.
 * It will then close the file and print a success message.
 */
void insertRecord() {
    Record r;
    cout<<"Enter id: ";
    cin>>r.id;
    cout<<"Enter name: ";
    cin>>r.name;
    cout<<"Enter age: ";
    cin>>r.age;

    ofstream outFile("data.db", ios::binary | ios::app);
    outFile.write((char*)&r, sizeof(r));
    outFile.close();

    cout<<"Record inserted successfully\n";
}

/**
 * @brief Delete a record from the database
 *
 * This function will delete a record from the database given its id.
 * It will read all the records from the database file and write them to a temporary file, except for the record to be deleted.
 * It will then replace the original database file with the temporary file.
 *
 * @param id The id of the record to be deleted.
 */
void deleteRecord(int id) {
    ifstream inFile(DB_FILE, ios::binary);
    ofstream tempFile("tempDB.db", ios::binary);


    if(!inFile || !tempFile) {
        cout << "Error opening file\n";
        exit(0);
    }

    Record r;
    bool found = false;

    while(inFile.read((char*)&r, sizeof(r))) {
        if(r.id == id) {
            found = true;
            continue;
        }
        
        tempFile.write((char*)&r, sizeof(r));
    }

    inFile.close();
    tempFile.close();

    remove("data.db");
    rename("tempDB.db", "data.db");

    if(found)
        cout<<"Record deleted successfully\n";
    else    
        cout<<"Record Not Found\n";

}

/**
 * @brief Show all records in the database
 *
 * This function will read all the records from the database file and print them to the console.
 *
 * @details The function will open the database file in binary mode and read all the records from it.
 * It will then print each record to the console.
 * If no records are found, it will print a message saying "No Records exist"
 */
void showAllRecords() {
    ifstream inFile(DB_FILE, ios::binary);

    if(!inFile) {
        cout<<"Unable to open file\n";
        return;
    }
    bool found = false;

    Record r;
    
    while(inFile.read((char*)&r, sizeof(r))) {
        found = 1;
        cout<<"Id: "<<r.id<<" | Name: "<<r.name<<" | Age: "<<r.age<<"\n";
    }

    inFile.close();
    if(!found) {
        cout<<"No Records exist\n";
    }
}

/**
 * @brief Search for a record by id in the database
 *
 * This function will search for a record by its id in the database.
 * It will read all the records from the database file and compare the id of each record with the given id.
 * If a record with the given id is found, it will print the record to the console and stop searching.
 * If no record with the given id is found, it will print a message saying "No such record exist".
 *
 * @param id The id of the record to be searched.
 */
void searchRecordById(int id) {
    ifstream inFile(DB_FILE, ios::binary);

    if(!inFile) {
        cout<<"Unable to open file\n";
        return;
    }
    bool found = false;
    Record r;

    while(inFile.read((char*)&r, sizeof(r))) {
        if(r.id == id) {
            found = true;
            cout<<"Id: "<<r.id<<" | Name: "<<r.name<<" | Age: "<<r.age<<"\n";
            return;
        }
    }
    inFile.close();
    if(!found) {
        cout<<"No such record exist\n";
    }
}



