#include <iostream>
#include <string>
#include "database.h"
#include <cstdlib>
int main() {
    Database db;
    init(db);
    std::string command;
    while (true) {
        std::cout << "command (list, add, get, del, exit): ";
        std::cin >> command;
        std::string key;
        if (command.find("list") != std::string::npos) {
            list(db);
        }
        else if (command.find("add") != std::string::npos) {
        std::string key;
        std::cout << "key: ";
        std::cin >> key;

        std::string typestr;
        std::cout << "type: (int, double, string, array): ";
        std::cin >> typestr;

        Type type;
        if (typestr == "int") {
            type = INT;
        } else if (typestr == "double") {
            type = DOUBLE;
        } else if (typestr == "string") {
            type = STRING;
        } else if (typestr == "array") {
            type = ARRAY;
        } else {
            std::cerr << "invalid command" << std::endl;
            return 0;
        }

        void* value = nullptr;
        if (type == INT) {
            int intValue;
            std::cout << "value: ";
            std::cin >> intValue;
            value = new int(intValue);
        } else if (type == DOUBLE) {
            double doubleValue;
            std::cout << "value: ";
            std::cin >> doubleValue;
            value = new double(doubleValue);
        } else if (type == STRING) {
            std::string stringValue;
            std::cout << "value: ";
            std::cin >> stringValue;
            value = new std::string(stringValue);
        } else if (type == ARRAY) {
            std::cout << "size: ";
            int size; 
            std::cin >> size;
            int* arrayValue = new int[size];
            for (int i = 0; i < size; ++i) {
                std::cout << "item[" << i << "]: ";
                std::cin >> arrayValue[i];
            }
            value = new int[size+1];
            *(static_cast<int*>(value)) = size;
            for (int i = 0; i < size; ++i) {
                (static_cast<int*>(value))[i+1] = arrayValue[i];
            }
            delete[] arrayValue;
        }

            Entry *entry = create(type, key, value);
            add(db, entry);

        }
        else if (command.find("get") != std::string::npos) {
            std::cout << "key: ";
            std::cin >> key;
            Entry *result = get(db, key);
            if (result == nullptr) {
                std::cout << "not found" << std::endl;
            }else {
                if (result->type == INT) {
                    std::cout << key << ": " << *static_cast<int*>(result->value) << std::endl;
                } else if (result->type == DOUBLE) {
                    std::cout << key << ": " <<  *static_cast<double*>(result->value) << std::endl;
                } else if (result->type == STRING) {
                    std::cout << key << ": " << *static_cast<std::string*>(result->value) << std::endl;
                } else if (result->type == ARRAY) {
                    std::cout << key<< ": [";
                    int* arr = static_cast<int*>(result->value);
                    int size = *static_cast<int*>(result->value);
                    for (int j = 0; j < size; ++j) {
                        std::cout << arr[j+1];
                        if (j < size - 1) {
                            std::cout << ", ";
                        }
                    }
                    std::cout << "]" << std::endl;
                }
}
        }
        else if (command.find("del") != std::string::npos) {
            std::cout << "key: ";
            std::cin >> key;
            remove(db, key);
        }
        else if (command.find("exit") != std::string::npos) {
            destroy(db);
            break;
        }
    }
    return 0;
}