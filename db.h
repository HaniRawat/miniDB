#pragma once
#include<string>
#include<map>

using namespace std;

struct Record {
    int id;
    char name[50];
    int age;
};

extern map<int, streampos> indexMap;
extern const string DB_FILE;

void insertRecord();
void deleteRecord(int id);
void searchRecordById(int id);
void showAllRecords();
void loadIndex();