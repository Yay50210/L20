#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string& filename, vector<string>& names, vector<int>& scores, vector<char>& grades) {
    ifstream file(filename);
    char format[] = "%[^:]: %d %d %d";

    string s;

    while (getline(file, s)) {
        char name[200];
        int score1, score2, score3;
    
        sscanf(s.c_str(), format, name, &score1, &score2, &score3);

        names.push_back(name);
        scores.push_back(score1 + score2 + score3);  
       
        char grade = score2grade(score1 + score2 + score3);
        grades.push_back(grade);
    }
}

void getCommand(string &command, string &key){
    cout << "Please input your command: ";
    cin >> command;
    cin.ignore();
    getline(cin, key);
}

void searchName(vector<string>& names, vector<int>& scores, vector<char>& grades, string  key){
        cout << "---------------------------------\n";
        for(unsigned int i = 0; i < names.size();i++){
        if(toUpperStr(names[i]) == key){
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------\n";
            return;
        } 
        }
        cout << "Cannot found." << endl;
    cout << "---------------------------------\n";
    


}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    cout << "---------------------------------\n";
    bool found = false;
    for(unsigned int i = 0 ; i < names.size();i++){
        if(grades[i] == key.c_str()[0]){
            cout << names[i] << " (" << scores[i] << ")" << endl;
            found = true;
        }
    }
    if(found == false){
        cout << "Cannot found." << endl;    
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
