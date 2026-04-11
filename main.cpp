#include<iostream>
#include<cstdlib>
#include "db.h"

using namespace std;

int main() {

    loadIndex();

    int choice;

    while(1) {
        cout<<"1. Insert Record\n";
        cout<<"2. Delete Record\n";
        cout<<"3. Search Record\n";
        cout<<"4. Show All Records\n";
        cout<<"5. Update a Record\n";
        cout<<"6. Exit\n";

        cout<<"Enter your choice: ";
        cin>>choice;

        if(choice == 1) {
            insertRecord();
        }
        else if(choice == 2) {
            int id;
            cout<<"Enter id to delete: ";
            cin>>id;
            deleteRecord(id);
        }
        else if(choice == 3) {
            int id;
            cout<<"Enter id to search: ";
            cin>>id;
            searchRecordById(id);
        }
        else if(choice == 4) {
            showAllRecords();
        }
        else if(choice == 5) {
            int id;
            cout<<"Enter id to update: ";
            cin>>id;
            updateRecord(id);
        }
        else if(choice == 6) {
            exit(0);
        }
        else {
            cout<<"Invalid choice\n";
        }
    }

    return 0;
}