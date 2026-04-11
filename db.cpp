#include <fstream>
#include <iostream>
#include "db.h"
#include <cstdio>
#include <map>

using namespace std;
map<int, streampos> indexMap;

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

    if(indexMap.find(r.id) != indexMap.end()) {
        cout<<"Error: ID already exists\n";
        return;
    }

    cout<<"Enter name: ";
    cin>>r.name;
    cout<<"Enter age: ";
    cin>>r.age;

    ofstream outFile(DB_FILE, ios::binary | ios::app | ios::ate);

    if(!outFile) {
        cout<<"Unable to open file\n";
        return;
    }

    streampos pos = outFile.tellp();


    outFile.write((char*)&r, sizeof(r));
    outFile.close();

    indexMap[r.id] = pos;

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

    loadIndex();

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
 *  It will first check if the id exists in the index map. If it does, it will seek to the position of the record in the database file and read it.
 * It will then print the record to the console.
 *
 * @param id The id of the record to be searched.
 */
void searchRecordById(int id) {

    if(indexMap.find(id) == indexMap.end()) {
        cout<<"No such record exist\n";
        return;
    }
    ifstream inFile(DB_FILE, ios::binary);

    if(!inFile) {
        cout<<"Unable to open file\n";
        return;
    }
    streampos pos = indexMap[id];
    inFile.seekg(pos);

    Record r;

    if(inFile.read((char*)&r, sizeof(r))) {
        cout<<"Id: "<<r.id<<" | Name: "<<r.name<<" | Age: "<<r.age<<"\n";
    } else {
        cout<<"Error reading record\n";
    }

    inFile.close();
}

void loadIndex() {
    indexMap.clear();
    
    ifstream inFile(DB_FILE, ios::binary);

    if(!inFile) {
        cout<<"Unable to open file\n";
        return;
    }

    Record r;
    streampos pos = 0;

    while(inFile.read((char*)&r, sizeof(r))) {
        indexMap[r.id] = pos;
        pos += sizeof(r);
    }

    inFile.close();
}

void updateRecord(int id) {
    if(indexMap.find(id) == indexMap.end()) {
        cout << "No such record exist\n";
        return;
    }
    
    fstream file(DB_FILE, ios::binary | ios::in | ios::out);

    if(!file) {
        cout<<"Error opening file\n";
        return;
    }

    streampos pos = indexMap[id];
    file.seekp(pos);

    Record r;
    r.id = id;

    cout<<"Enter new name: ";
    cin >> r.name;

    cout<<"Enter your age: ";
    cin>>r.age;

    file.write((char*)&r, sizeof(r));
    file.close();

    cout<<"Record updated successfully";
}

