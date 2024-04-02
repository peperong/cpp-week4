#include "database.h"
#include <string>
#include <cstdlib>
#include <iostream>
Entry *create(Type type, std::string key, void *value) {
    Entry *entry = new Entry;
    entry->type = type;
    entry->key = key;
    entry->value = value;
    return entry;
}
void init(Database &database) {
    database.entries = nullptr;
    database.size = 0;
    database.capacity = 0;
}


void list(Database &database) {
    for (int i = 0; i < database.size; ++i) {
        std::cout << database.entries[i]->key << ": ";
        if (database.entries[i]->type == INT) {
            std::cout << *(int*)(database.entries[i]->value) << std::endl;
        } else if (database.entries[i]->type == DOUBLE) {
            std::cout << *(double*)(database.entries[i]->value) << std::endl;
        } else if (database.entries[i]->type == STRING) {
            std::cout << *(std::string*)(database.entries[i]->value) << std::endl;
        } else if (database.entries[i]->type == ARRAY) {
            std::cout << *((std::string*)database.entries[i]->value);
            }
        }
    }

void add(Database &database, Entry *entry) {
    if (database.size == database.capacity) {
        database.capacity *= 2;
        database.entries = (Entry **)realloc(database.entries, database.capacity * sizeof(Entry *));
    }
    database.entries[database.size++] = entry;
    
}
Entry *get(Database &database, std::string &key) {
    for (int i = 0; i < database.size; ++i) {
        if (database.entries[i]->key == key) {
            return database.entries[i];
        }

    }
    return nullptr;
}
void remove(Database &database, std::string &key) {

    for (int i = 0; i < database.size; i++) {
        if (database.entries[i]->key == key) {
            delete database.entries[i];
            for (int j = i; j < database.size - 1; j++) {
                database.entries[j] = database.entries[j + 1];
            }
            database.size--;
            break;
        }
    }
}

void destroy(Database &database) {
    for (int i = 0; i < database.size; i++) {
        delete database.entries[i];
    }
    free(database.entries);
    database.entries = nullptr;
    database.size = 0;
    database.capacity = 0;
}
