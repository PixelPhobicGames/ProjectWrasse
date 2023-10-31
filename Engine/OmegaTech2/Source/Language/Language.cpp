
#include "Language.hpp"

// Language Pack Management

int LineCount(const char *filename) {
    ifstream file(filename);
    int lineCount = 0;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            lineCount++;
        }

        file.close();
    } else {
        cerr << "Error: Unable to open the file." << endl;
    }

    return lineCount;
}

string LoadLine(const char *filename, int index) {
    ifstream file(filename);
    vector<string> lines;

    if (file.is_open()) {
        string tempLine;
        while (getline(file, tempLine)) {
            lines.push_back(tempLine);
        }

        file.close();

        if (index >= 0 && index < lines.size()) {
            return lines[index];
        } else {
            cerr << "Error: Index is out of range." << endl;
        }
    } else {
        cerr << "Error: Unable to open the file." << endl;
    }

    return ""; 
}


void LoadLanguagePack(int Type, Pack* PackData){
    int Lines;

    switch (Type)
    {
        case 0: // Eng
            LineCount("GameData/Global/LanguagePacks/English.lg");
            PackData->Size = Lines;
            PackData->Type = 0;

            if (Lines <= MaxPackSize){
                for (int i = 0 ; i <= Lines; i++){
                    PackData->Lines[i] = LoadLine("GameData/Global/LanguagePacks/English.lg" , i);
                }
            }

            break;
        case 1: // Russ
            Lines = LineCount("GameData/Global/LanguagePacks/Russian.lg");
            PackData->Size = Lines;
            PackData->Type = 1;

            if (Lines <= MaxPackSize){
                for (int i = 0 ; i <= Lines; i++){
                    PackData->Lines[i] = LoadLine("GameData/Global/LanguagePacks/Russian.lg" , i);
                }
            }

            break;
        case 2: // Span
            Lines = LineCount("GameData/Global/LanguagePacks/Spanish.lg");
            PackData->Size = Lines;
            PackData->Type = 2;

            if (Lines <= MaxPackSize){
                for (int i = 0 ; i <= Lines; i++){
                    PackData->Lines[i] = LoadLine("GameData/Global/LanguagePacks/Spanish.lg" , i);
                }
            }

            break;
        case 3: // Port
            Lines = LineCount("GameData/Global/LanguagePacks/Portuguese.lg");
            PackData->Size = Lines;
            PackData->Type = 3;

            if (Lines <= MaxPackSize){
                for (int i = 0 ; i <= Lines; i++){
                    PackData->Lines[i] = LoadLine("GameData/Global/LanguagePacks/Portuguese.lg" , i);
                }
            }

            break;
    }
}

