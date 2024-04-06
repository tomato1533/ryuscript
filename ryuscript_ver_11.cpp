#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

vector<string> splitString(const string& str) {
    vector<string> tokens;
    stringstream iss(str);
    string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

vector<string> split(const string& s, const string& com) {
    vector<string> tokens;
    size_t start = 0, end = 0;
    while ((end = s.find(com, start)) != string::npos) {
        tokens.push_back(s.substr(start, end - start));
        start = end + com.length();
    }
    tokens.push_back(s.substr(start));
    return tokens;
}

int write_file(string date) {
    ofstream file("run.py");

    if (file.is_open()) {
        file << date;
        file.close();
        cout << "write file\n";
    } else {
        cerr << "file not found\n";
        return 0;
    }
    return 0;
}

string process(string line) {
    char com;
    string content;
    string output;
    string e;
    int value = 0;
    string out;
    string date_var; string var_name;
    vector<string> date = splitString(line);
    for (string DATE : date) {
        if (value == 0) {
            if (DATE == "print") {
                value = 1;
                output = "print";
            }
            if (DATE == "var") {
                value = 1;
                output = "var";
            }
        }
        if (value == 1 && DATE != output) {
            if (output == "print") {
                content += "print('" + DATE + "')\n";
                value = 0;
            }
            /*if (output == "var") {
                value = 2;
                if (DATE == "string") {
                    string var_date;
                    e = "string";
                }
                if (DATE == "int") {
                    string var_date;
                    e = "int";
                }
                if (DATE == "float") {
                    string var_date;
                    e = "float";
                }
            }*/
        }
        if (value == 2 && date_var != DATE) {
            if (e == "string") {
                content += DATE + "=";
                value = 3;
            }
        }
    }
    return content;
}

int main(void) {
    ifstream file("sample.txt");
    string content, date;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            content += line += "\n"; 
        }
        date = process(content);
        file.close();
    } else {
        cerr << "file not found";
        return 0;
    }

    cout << "file in\n" << content << endl;
    cout << "file in\n" << date << endl;
    write_file(date);
    system("python run.py");
    return 0;
}
