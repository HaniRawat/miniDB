#pragma once
#include<string>

using namespace std;

struct Record {
    int id;
    char name[50];
    int age;
};

void insertRecord();
void deleteRecord(int id);
void searchRecordById(int id);
void showAllRecords();