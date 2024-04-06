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

int write_file(string date, string lang) {
    string file_name;
    if (lang == "py"){
        file_name = "run.py";
    }
    if (lang == "c") {
        file_name = "run.c";
    }
    ofstream file(file_name);

    if (file.is_open()) {
        file << date;
        file.close();
    } else {
        cerr << "file not found\n";
        return 0;
    }
    return 0;
}
/*
# lang python
# lang python
*/
string process_py(string line) {
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
            if (DATE == "printf") {
                value = 1;
                output = "printf";
            }
            if (DATE == "int") {
                value = 1;
                output = "int";
            }
            if (DATE == "float") {
                value = 1;
                output = "float";
            }
            if (DATE == "str") {
                value = 1;
                output = "str";
            }
        }
        // var int and string , float
        if (value == 3 && DATE != output) {
            if (output == "int") {
                content += e + out + DATE + "\n";
                value = 0;
            }
            if (output == "float") {
                content += e + out + DATE + "\n";
                value = 0;
            }
            if (output == "str") {
                content += e + out + "'" + DATE + "'\n";
                value = 0;
            }
        }
        if (value == 2 && DATE != output) {
            if (output == "int"){
                out = DATE;
                value = 3;
            }
            if (output == "float"){
                out = DATE;
                value = 3;
            }
            if (output == "str"){
                out = DATE;
                value = 3;
            }
        }
        //var
        if (value == 1 && DATE != output) {
            if (output == "print") {
                content += "print('" + DATE + "')\n";
                value = 0;
            }
            if (output == "printf") {
                content += "print(" + DATE + ")\n";
                value = 2;
                value = 0;
            }
            // var
            if (output == "int") {
                e = DATE;
                value = 2;
            }
            if (output == "float") {
                e = DATE;
                value = 2;
            }
            if (output == "str") {
                e = DATE;
                value = 2;
            }
        }
    }
    return content;
}

string process_c(string line) {
    char com;
    string content;
    content += "#include <stdio.h>\n";
    content += "int main() {\n";
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
            if (DATE == "printf") {
                value = 1;
                output = "printf";
            }
            if (DATE == "int") {
                value = 1;
                output = "int";
            }
            if (DATE == "float") {
                value = 1;
                output = "float";
            }
            if (DATE == "str") {
                value = 1;
                output = "str";
            }
        }
        // var int and string , float
        if (value == 3 && DATE != output) {
            if (output == "int") {
                content += "int " + e + out + DATE + ";\n";
                value = 0;
            }
            if (output == "float") {
                content += "float " + e + out + DATE + ";\n";
                value = 0;
            }
            if (output == "str") {
                content += "char " + e + out + "'" + DATE + "';\n";
                value = 0;
            }
        }
        if (value == 2 && DATE != output) {
            if (output == "int"){
                out = DATE;
                value = 3;
            }
            if (output == "float"){
                out = DATE;
                value = 3;
            }
            if (output == "str"){
                out = DATE;
                value = 3;
            }
        }
        //var
        if (value == 1 && DATE != output) {
            if (output == "print") {
                content += "printf('" + DATE + "');\n";
                value = 0;
            }
            if (output == "printf") {
                content += "printf(" + DATE + ");\n";
                value = 2;
                value = 0;
            }
            // var
            if (output == "int") {
                e = DATE;
                value = 2;
            }
            if (output == "float") {
                e = DATE;
                value = 2;
            }
            if (output == "str") {
                e = DATE;
                value = 2;
            }
        }
    }
    content += "return 0;\n";
    content += "}";
    return content;
}

int main(void) {
    string file_name;
    cout << "file name:";
    cin >> file_name;
    ifstream file(file_name);
    string content, date;
    cout << "lang:";
    string lang;
    cin >> lang;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            content += line += "\n"; 
        }
        file.close();
    } else {
        cerr << "file not found";
        return 0;
    }
    if (lang == "c") {
        date = process_c(content);
    }
    if (lang == "py") {
        date = process_py(content);
    }
    write_file(date, lang);
    string f;
    cout << "command";
    cin >> f;
    if (f == "py"){
        system("python run.py");
    }
    if (f == "c"){
        system("gcc -o run run.c && ./run");
    }
    return 0;
}
