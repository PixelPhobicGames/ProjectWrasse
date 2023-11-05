#include "ParasiteScriptData.hpp"
#include "../Encoder/Encoder.hpp"

#define RedText "\033[4;31m"
#define GreenText "\033[1;32m"
#define BlueText "\033[1;34m"
#define FadeColorText "\033[1;37m"



string PMemKey = "9876543210zyxwvutsrqponmlkjihgfedcbaZYXWVUTSRQPONMLKJIHGFEDCBA";



auto ParasiteScriptLoadFile(const char* Path){
    std::ifstream Input(Path);
    std::stringstream sstr;

    while(Input >> sstr.rdbuf());

    return sstr.str();
}

void ParasiteScriptTFlagWipe(){
    for (int i = 0 ; i <= MaxTFlag - 1; i++){
        ToggleFlags[i].Value = 0;
    }
}

void ParasiteScriptInit(){ 
    ParasiteScriptCoreData.LesserFlag = false;
    ParasiteScriptCoreData.GreaterFlag = false;
    ParasiteScriptCoreData.EqualFlag = false;
    ParasiteScriptCoreData.NotEqualFlag = false;

    ParasiteScriptCoreData.CompareFlag = false;
    ParasiteScriptCoreData.ContinueFlag = true;
    ParasiteScriptCoreData.ErrorFlag = false;

    ParasiteScriptCoreData.ReturnLine = 0;
    ParasiteScriptCoreData.Line[0] = '\0';

    for (int i = 0; i <= ParasiteScriptCoreData.ProgramSize; i ++){
        ParasiteScriptCoreData.Line[i] = "";
    }
    
    ParasiteScriptCoreData.ProgramSize = 0;
    ParasiteScriptCoreData.TextSize = 20;


    VaribleCounter = 0;
    TextureCounter = 0;
    PMemCounter = 0;
    JumpPointCounter = 0;
    ArrayCounter = 0;

    for (int i = 0 ; i <= MaxVaribles - 1; i++){
        VaribleMemory[i].IValue = 0;
    }
    for (int i = 0 ; i <= MaxPermanentVaribles - 1; i++){
        PermanentMemory[i].IValue = 0;
    }
}

auto SplitValue(string Data , int Place ){ 
    string Out;
    int PlaceCounter = 0; 

    int Start = 0;
    int End = 0;
    
    if (Place == 0){
        for (int i = 0 ; i <= Data.size() ; i ++){
            if (Data[i] == ' ' || i == Data.size()){
                End = i - 1;
                break;
            }
        }
    }
    else {
        Place = Place;
        PlaceCounter = 1;
        for (int i = 0 ; i <= Data.size() ; i ++){
            if (PlaceCounter == Place){
                Start = i + 1;
                for (int x = i+1 ; x <= Data.size(); x++){
                    if (Data[x] == ' ' || x == Data.size()){
                        End = x - 1;
                        break;
                    }
                }
            }
            if (Data[i] == ' '){
                PlaceCounter ++;
            }
        }
    }

    Out = ReadValue(Data , Start , End);

    return Out;
}


int StringToInt(const std::string& Data) {
    int Out = 0;
    int Place = 1;
    int i = Data.size() - 1;  // Start from the end of the string

    while (i >= 0) {
        char c = Data[i];
        if (c == '-') {
            Out = -Out;  // Handle negative sign
        } else if (c >= '0' && c <= '9') {
            int digit = c - '0';
            Out += digit * Place;
            Place *= 10;
        }
        i--;
    }

    return Out;
}

auto StringToChar(string Data){
    char Out[] = ""; 
    for (int i = 0 ; i <= Data.size(); i++){
        switch (Data[i]){
            case '1':
                memcpy(Out , "1" , 1);
                break;
        }
    }
    
    return Out;
}

auto ScanVaribleMemory(string VaribleName){
    bool Found = false;
    for (int x = 0 ; x <= VaribleCounter; x++){
        if (VaribleMemory[x].Name == VaribleName){
            Found = true;
        }
    }
    for (int x = 0 ; x <= PMemCounter; x++){
        if (PermanentMemory[x].Name == VaribleName){
            Found = true;
        }
    }
    return Found;
}

int PullIntFromMemory(string VaribleName){
    bool Found = false;
    for (int x = 0 ; x <= VaribleCounter; x++){
        if (VaribleMemory[x].Name == VaribleName){
            Found = true;
            return VaribleMemory[x].IValue;
        }
    }
    for (int x = 0 ; x <= PMemCounter; x++){
        if (PermanentMemory[x].Name == VaribleName){
            Found = true;
            return PermanentMemory[x].IValue;
        }
    }
    if (!Found){
        cout << "Error Varible Not Declared: " << VaribleName << "\n";
        ParasiteScriptCoreData.ErrorFlag = true;
        return 0;
    }
}

Texture2D PullTextureFromMemory(string VaribleName){
    bool Found = false;

    for (int x = 0 ; x <= TextureCounter; x++){
        if (TextureMemory[x].Name == VaribleName){
            Found = true;
            return TextureMemory[x].TextureValue;
        }
    }

    if (!Found){
        cout << "Error Varible Not Declared: " << VaribleName << "\n";
        ParasiteScriptCoreData.ErrorFlag = true;
        Texture2D New;
        return New;
    }
}


string PullStrFromMemory(string VaribleName){
    bool Found = false;
    for (int x = 0 ; x <= VaribleCounter; x++){
        if (VaribleMemory[x].Name == VaribleName){
            Found = true;
            return VaribleMemory[x].Value;
        }
    }

    if (!Found){
        ParasiteScriptCoreData.ErrorFlag = true;
        return "";
    }
}

void StoreIntToMemory(string VaribleName, int Value){
    if (ScanVaribleMemory(VaribleName)){
        for (int x = 0 ; x <= VaribleCounter; x++){
            if (VaribleMemory[x].Name == VaribleName){
                VaribleMemory[x].IValue = Value;
            }
        }
    }
}

void StoreIntToPMemory(string VaribleName, int Value){
    if (ScanVaribleMemory(VaribleName)){
        for (int x = 0 ; x <= PMemCounter; x++){
            if (PermanentMemory[x].Name == VaribleName){
                PermanentMemory[x].IValue = Value;
            }
        }
    }
}

void StoreStrToMemory(string VaribleName, string Value){
    for (int x = 0 ; x <= VaribleCounter; x++){
        if (VaribleMemory[x].Name == VaribleName){
            VaribleMemory[x].Value = Value;
        }
    }
}

string RemoveSpaces(string Data)
{
    string OutData = "";

    for (int i = 0 ; i <= Data.size() ; i ++){
        if (Data[i] != ' '){
            OutData[i] = Data[i];
        }
    }

    return OutData;
}

int ScanSpaces(string Data){
    int Spaces = 0;

    for (int i = 0 ; i <= Data.size() ; i ++){
        if (Data[i] != ' '){
            Spaces ++;
        }
    }

    return Spaces;
}

bool IsNumber(const string& s)
{
    for (char const &ch : s) {
        if (isdigit(ch) == 0) 
            return false;
    }
    return true;
 }


void LoadScript(const char *ScriptPath){ // Loads Script
    istringstream ProgramData(ParasiteScriptLoadFile(ScriptPath));
    string CurrentLine;

    while (getline(ProgramData, CurrentLine)) {

        if (ReadValue(CurrentLine, 0 , 0) == ":"){            
            JumpPoints[JumpPointCounter].Name = ReadValue(CurrentLine, 1 , CurrentLine.size() - 1);
            JumpPoints[JumpPointCounter].LineNumber = ParasiteScriptCoreData.LineCounter;
            JumpPointCounter ++;
        }
        if (ReadValue(CurrentLine, 0 , 0) == " "){
            int SpaceCounter = 0;
            for (int i = 0 ; i <= CurrentLine.size() ; i ++){
                if (ReadValue(CurrentLine, i , i) == " ")SpaceCounter ++;
                else {
                    break;
                }
            }
            string Temp = ReadValue(CurrentLine, SpaceCounter , CurrentLine.size() - 1);
            CurrentLine = Temp;
        }
        ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] = CurrentLine;
        ParasiteScriptCoreData.LineCounter ++;
        

    } 
    ParasiteScriptCoreData.ProgramSize = ParasiteScriptCoreData.LineCounter;

    ParasiteScriptCoreData.LineCounter = 0;

} 


void ReplaceValue(int start, int end, std::string &original, const std::string &newValue) {
    original.replace(start, end - start + 1, newValue);
}

string ReadLineByIndex(const std::string& filename, int index) {
    std::ifstream inputFile(filename); // Open the file for reading

    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return ""; // Return an empty string on failure
    }

    std::string line;
    int currentLineIndex = 0;

    while (currentLineIndex < index && std::getline(inputFile, line)) {
        currentLineIndex++; // Keep track of the current line index
    }

    inputFile.close(); // Close the file when done

    if (currentLineIndex == index) {
        return line; // Return the line at the specified index
    } else {
        return ""; // Line index not found
    }
}

void WritePMemPage(){
    ofstream PmemFile("GameData/Saves/PMEM");

    PmemFile << NEncode(to_string(PMemCounter), PMemKey) << endl;

    for (int i = 0; i <= PMemCounter - 1; i ++){
        PmemFile << NEncode(PermanentMemory[i].Name, PMemKey) << " " << NEncode(to_string(PermanentMemory[i].IValue), PMemKey) << endl;
    }

    PmemFile.close();
}

void RestorePMemPage(){
    PMemCounter = StringToInt(NEncode(ReadLineByIndex("GameData/Saves/PMEM" , 1), PMemKey));

    for (int i = 0; i <= PMemCounter - 1; i ++){
        string PmemValue = NEncode(ReadLineByIndex("GameData/Saves/PMEM" , 2 + i), PMemKey);
    }
}


void SearchMacroOperation(string &Instruction){ // Macro OP
    int Start = 0;
    int End = 0;

    bool Found = false;

    for (int i = 0; i <= Instruction.size() ; i ++){
        if (Instruction[i] == '('){
            Start = i;
        }
        if (Instruction[i] == ')'){
            End = i;
            if (Start != 0){
                Found = true;
            }
            break;
        }
    }

    if (Found){
        string *MacroOperation = NULL; 
        MacroOperation = new string;   
        *MacroOperation = ReadValue(Instruction, Start , End);
        

        cout << "Found Macro Operation -->" << *MacroOperation << endl;

        cout << SplitValue(*MacroOperation , 1) << endl;

        if (SplitValue(*MacroOperation , 1) == "TFlag" && SplitValue(*MacroOperation , 2) == "-->"){
            int *TValue = NULL;
            TValue = new int;
            *TValue = ToggleFlags[StringToInt(SplitValue(Instruction, 3 ))].Value;

            ReplaceValue(Start, End, Instruction , to_string(*TValue) );

            delete TValue;
            
        }
        

        delete MacroOperation;
    }
}

static int TimeDelay = 0;

auto CycleInstruction(){
    if (TimeDelay == 0){
        if (ParasiteScriptCoreData.LineCounter != ParasiteScriptCoreData.ProgramSize){

            bool FoundInstruction = false;
            
            string Instruction = ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter];

            if (ParasiteScriptCoreData.ErrorFlag){
                cout << "Error Command: -->" << ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter - 1] << "<--\n";
                exit(0);
            }

            if (SplitValue(Instruction, 0 ) == "end"){
                FoundInstruction = true;
                ParasiteScriptCoreData.ContinueFlag = true;
            }

            if (ParasiteScriptCoreData.ContinueFlag && SplitValue(Instruction, 0) != "//"){
                for (int i = 0 ; i <= ScanSpaces(Instruction); i ++){
                    if (SplitValue(Instruction, i) == "+"){
                        string Part1 = "";
                        string Part2 = "";
                        bool Found = false;
                        int SpaceCounter = 0 ;
                        if (!IsNumber(SplitValue(Instruction, i-1))){
                            if (IsNumber(SplitValue(Instruction, i+1))){
                                int Value = StringToInt(SplitValue(Instruction, i+1));
                                int Value1 = PullIntFromMemory(SplitValue(Instruction, i-1));
                                StoreIntToMemory(SplitValue(Instruction, i-1) , Value1 + Value);
                            }
                            else{
                                int Value = PullIntFromMemory(SplitValue(Instruction, i+1));
                                StoreIntToMemory(SplitValue(Instruction, i-1) , PullIntFromMemory(SplitValue(Instruction, i-1)) + Value);
                            }

                            for (int i = 0 ; i <= Instruction.size(); i++){
                                if (Instruction[i] == '+'){
                                    Part1 = ReadValue(Instruction , 0 , i - 1);
                                    Found = true;
                                }
                                if (Found){
                                    if (Instruction[i] == ' '){
                                        SpaceCounter ++;
                                        if (SpaceCounter == 2){
                                            Part2 = ReadValue(Instruction , i + 1, Instruction.size() - 1);
                                            Part2 += " ";
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            int Value = StringToInt(SplitValue(Instruction, i-1)) + StringToInt(SplitValue(Instruction, i+1));

                            for (int i = 0 ; i <= Instruction.size(); i++){
                                if (Instruction[i] == '+'){
                                    Part1 = ReadValue(Instruction , 0 , i - 3);
                                    stringstream ss;
                                    ss << Value;
                                    Part1 += ss.str();
                                    Part1 += " ";
                                    Found = true;
                                }
                                if (Found){
                                    if (Instruction[i] == ' '){
                                        SpaceCounter ++;
                                        if (SpaceCounter == 2){
                                            Part2 = ReadValue(Instruction , i + 1, Instruction.size());
                                            Part2 += " ";
                                        }
                                    }
                                }
                            }
                        }

                    
                        Instruction = '\0';
                        Instruction = Part1 + Part2;
                        ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] = Instruction;
                         
                    }
                    if (SplitValue(Instruction, i) == "-"){
                        string Part1 = "";
                        string Part2 = "";
                        bool Found = false;
                        int SpaceCounter = 0 ;
                        if (!IsNumber(SplitValue(Instruction, i-1))){
                            if (IsNumber(SplitValue(Instruction, i+1))){
                                int Value = StringToInt(SplitValue(Instruction, i+1));
                                int Value1 = PullIntFromMemory(SplitValue(Instruction, i-1));
                                StoreIntToMemory(SplitValue(Instruction, i-1) , Value1 - Value);
                            }
                            else{
                                int Value = PullIntFromMemory(SplitValue(Instruction, i+1));
                                StoreIntToMemory(SplitValue(Instruction, i-1) , PullIntFromMemory(SplitValue(Instruction, i-1)) - Value);
                            }

                            for (int i = 0 ; i <= Instruction.size(); i++){
                                if (Instruction[i] == '-'){
                                    Part1 = ReadValue(Instruction , 0 , i - 1);
                                    Found = true;
                                }
                                if (Found){
                                    if (Instruction[i] == ' '){
                                        SpaceCounter ++;
                                        if (SpaceCounter == 2){
                                            Part2 = ReadValue(Instruction , i + 1, Instruction.size() - 1);
                                            Part2 += " ";
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            int Value = StringToInt(SplitValue(Instruction, i-1)) - StringToInt(SplitValue(Instruction, i+1));

                            for (int i = 0 ; i <= Instruction.size(); i++){
                                if (Instruction[i] == '-'){
                                    Part1 = ReadValue(Instruction , 0 , i - 3);
                                    stringstream ss;
                                    ss << Value;
                                    Part1 += ss.str();
                                    Part1 += " ";
                                    Found = true;
                                }
                                if (Found){
                                    if (Instruction[i] == ' '){
                                        SpaceCounter ++;
                                        if (SpaceCounter == 2){
                                            Part2 = ReadValue(Instruction , i + 1, Instruction.size());
                                            Part2 += " ";
                                        }
                                    }
                                }
                            }
                        }

                    
                        Instruction = '\0';
                        Instruction = Part1 + Part2;
                        ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] = Instruction;
                    }
                    if (SplitValue(Instruction, i) == "*"){
                        string Part1 = "";
                        string Part2 = "";
                        bool Found = false;
                        int SpaceCounter = 0 ;
                        if (!IsNumber(SplitValue(Instruction, i-1))){
                            if (IsNumber(SplitValue(Instruction, i+1))){
                                int Value = StringToInt(SplitValue(Instruction, i+1));
                                int Value1 = PullIntFromMemory(SplitValue(Instruction, i-1));
                                StoreIntToMemory(SplitValue(Instruction, i-1) , Value1 * Value);
                            }
                            else{
                                int Value = PullIntFromMemory(SplitValue(Instruction, i+1));
                                StoreIntToMemory(SplitValue(Instruction, i-1) , PullIntFromMemory(SplitValue(Instruction, i-1)) * Value);
                            }

                            for (int i = 0 ; i <= Instruction.size(); i++){
                                if (Instruction[i] == '*'){
                                    Part1 = ReadValue(Instruction , 0 , i - 1);
                                    Found = true;
                                }
                                if (Found){
                                    if (Instruction[i] == ' '){
                                        SpaceCounter ++;
                                        if (SpaceCounter == 2){
                                            Part2 = ReadValue(Instruction , i + 1, Instruction.size() - 1);
                                            Part2 += " ";
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            int Value = StringToInt(SplitValue(Instruction, i-1)) * StringToInt(SplitValue(Instruction, i+1));

                            for (int i = 0 ; i <= Instruction.size(); i++){
                                if (Instruction[i] == '*'){
                                    Part1 = ReadValue(Instruction , 0 , i - 3);
                                    stringstream ss;
                                    ss << Value;
                                    Part1 += ss.str();
                                    Part1 += " ";
                                    cout << Part1 << "\n";
                                    Found = true;
                                }
                                if (Found){
                                    if (Instruction[i] == ' '){
                                        SpaceCounter ++;
                                        if (SpaceCounter == 2){
                                            Part2 = ReadValue(Instruction , i + 1, Instruction.size());
                                            Part2 += " ";
                                        }
                                    }
                                }
                            }
                        }

                    
                        Instruction = '\0';
                        Instruction = Part1 + Part2;
                        ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] = Instruction;
                         
                    }
                    if (SplitValue(Instruction, i) == "/"){
                        string Part1 = "";
                        string Part2 = "";
                        bool Found = false;
                        int SpaceCounter = 0 ;
                        if (!IsNumber(SplitValue(Instruction, i-1))){
                            if (IsNumber(SplitValue(Instruction, i+1))){
                                int Value = StringToInt(SplitValue(Instruction, i+1));
                                int Value1 = PullIntFromMemory(SplitValue(Instruction, i-1));
                                StoreIntToMemory(SplitValue(Instruction, i-1) , Value1 / Value);
                            }
                            else{
                                int Value = PullIntFromMemory(SplitValue(Instruction, i+1));
                                StoreIntToMemory(SplitValue(Instruction, i-1) , PullIntFromMemory(SplitValue(Instruction, i-1)) / Value);
                            }

                            for (int i = 0 ; i <= Instruction.size(); i++){
                                if (Instruction[i] == '/'){
                                    Part1 = ReadValue(Instruction , 0 , i - 1);
                                    Found = true;
                                }
                                if (Found){
                                    if (Instruction[i] == ' '){
                                        SpaceCounter ++;
                                        if (SpaceCounter == 2){
                                            Part2 = ReadValue(Instruction , i + 1, Instruction.size() - 1);
                                            Part2 += " ";
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            int Value = StringToInt(SplitValue(Instruction, i-1)) / StringToInt(SplitValue(Instruction, i+1));

                            for (int i = 0 ; i <= Instruction.size(); i++){
                                if (Instruction[i] == '/'){
                                    Part1 = ReadValue(Instruction , 0 , i - 3);
                                    stringstream ss;
                                    ss << Value;
                                    Part1 += ss.str();
                                    Part1 += " ";
                                    cout << Part1 << "\n";
                                    Found = true;
                                }
                                if (Found){
                                    if (Instruction[i] == ' '){
                                        SpaceCounter ++;
                                        if (SpaceCounter == 2){
                                            Part2 = ReadValue(Instruction , i + 1, Instruction.size());
                                            Part2 += " ";
                                        }
                                    }
                                }
                            }
                        }

                    
                        Instruction = '\0';
                        Instruction = Part1 + Part2;
                        ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] = Instruction;
                         
                    }
                }

                if (SplitValue(Instruction, 1) == "="){
                    FoundInstruction = true;
                    if (IsNumber(SplitValue(Instruction, 2))){
                        StoreIntToMemory(SplitValue(Instruction, 0) , StringToInt(SplitValue(Instruction, 2)));
                    }
                    else {
                        int Value = PullIntFromMemory(SplitValue(Instruction, 2));
                        StoreIntToMemory(SplitValue(Instruction, 0) , Value);
                    }
                }

                if (SplitValue(Instruction, 1) == "+="){
                    FoundInstruction = true;
                    if (IsNumber(SplitValue(Instruction, 2))){
                        int Value = StringToInt(SplitValue(Instruction, 2));
                        StoreIntToMemory(SplitValue(Instruction, 0) , PullIntFromMemory(SplitValue(Instruction, 0)) + Value);
                    }
                    else{
                        int Value = PullIntFromMemory(SplitValue(Instruction, 2));
                        StoreIntToMemory(SplitValue(Instruction, 0) , PullIntFromMemory(SplitValue(Instruction, 0)) + Value);
                    }
                }

                if (SplitValue(Instruction, 1) == "-="){
                    FoundInstruction = true;
                    if (IsNumber(SplitValue(Instruction, 2))){
                        int Value = StringToInt(SplitValue(Instruction, 2));
                        StoreIntToMemory(SplitValue(Instruction, 0) , PullIntFromMemory(SplitValue(Instruction, 0)) - Value);
                    }
                    else{
                        int Value = PullIntFromMemory(SplitValue(Instruction, 2));
                        StoreIntToMemory(SplitValue(Instruction, 0) , PullIntFromMemory(SplitValue(Instruction, 0)) - Value);
                    }
                }

                if (SplitValue(Instruction, 1) == "*="){
                    FoundInstruction = true;
                    if (IsNumber(SplitValue(Instruction, 2))){
                        int Value = StringToInt(SplitValue(Instruction, 2));
                        StoreIntToMemory(SplitValue(Instruction, 0) , PullIntFromMemory(SplitValue(Instruction, 0)) * Value);
                    }
                    else{
                        int Value = PullIntFromMemory(SplitValue(Instruction, 2));
                        StoreIntToMemory(SplitValue(Instruction, 0) , PullIntFromMemory(SplitValue(Instruction, 0)) * Value);
                    }
                }

                if (SplitValue(Instruction, 1) == "/="){
                    FoundInstruction = true;
                    if (IsNumber(SplitValue(Instruction, 2))){
                        int Value = StringToInt(SplitValue(Instruction, 2));
                        StoreIntToMemory(SplitValue(Instruction, 0) , PullIntFromMemory(SplitValue(Instruction, 0)) / Value);
                    }
                    else{
                        int Value = PullIntFromMemory(SplitValue(Instruction, 2));
                        StoreIntToMemory(SplitValue(Instruction, 0) , PullIntFromMemory(SplitValue(Instruction, 0)) / Value);
                    }
                }

                SearchMacroOperation(Instruction);

                if (SplitValue(Instruction, 0 ) == "if"){
                    FoundInstruction = true;

                    ParasiteScriptCoreData.ContinueFlag = true;
                    ParasiteScriptCoreData.ElseFlag = false;

                    string Operator = SplitValue(Instruction, 2 );
                    int Value1 = 0;
                    int Value2 = 0;

                    if (IsNumber(SplitValue(Instruction, 1))){
                        Value1 = StringToInt(SplitValue(Instruction, 1 ));
                    }
                    else {
                        Value1 = PullIntFromMemory(SplitValue(Instruction, 1 ));
                    }

                    if (IsNumber(SplitValue(Instruction, 3))){
                        Value2 = StringToInt(SplitValue(Instruction, 3 ));
                    }
                    else {
                        Value2 = PullIntFromMemory(SplitValue(Instruction, 3 ));
                    }

                    if (Operator == "=="){
                        if (Value1 == Value2){
                            ParasiteScriptCoreData.ContinueFlag = true;
                        }
                        else {
                            ParasiteScriptCoreData.ContinueFlag = false;
                            ParasiteScriptCoreData.ElseFlag = true;
                        }
                    }

                    if (Operator == ">"){
                        if (Value1 > Value2){
                            ParasiteScriptCoreData.ContinueFlag = true;
                        }
                        else {
                            ParasiteScriptCoreData.ContinueFlag = false;
                            ParasiteScriptCoreData.ElseFlag = true;
                        }
                    }

                    if (Operator == "<"){
                        if (Value1 < Value2){
                            ParasiteScriptCoreData.ContinueFlag = true;
                        }
                        else {
                            ParasiteScriptCoreData.ContinueFlag = false;
                            ParasiteScriptCoreData.ElseFlag = true;
                        }
                    }

                    if (Operator == ">="){
                        if (Value1 >= Value2){
                            ParasiteScriptCoreData.ContinueFlag = true;
                        }
                        else {
                            ParasiteScriptCoreData.ContinueFlag = false;
                            ParasiteScriptCoreData.ElseFlag = true;
                        }
                    }

                    if (Operator == "<="){
                        if (Value1 >= Value2){
                            ParasiteScriptCoreData.ContinueFlag = true;
                        }
                        else {
                            ParasiteScriptCoreData.ContinueFlag = false;
                            ParasiteScriptCoreData.ElseFlag = true;
                        }
                    }

                    if (Operator == "!="){
                        if (Value1 != Value2){
                            ParasiteScriptCoreData.ContinueFlag = true;
                        }
                        else {
                            ParasiteScriptCoreData.ContinueFlag = false;
                            ParasiteScriptCoreData.ElseFlag = true;
                        }
                    }
                }

                if (SplitValue(Instruction, 0 ) == "else"){
                    FoundInstruction = true;
                    if (!ParasiteScriptCoreData.ElseFlag){
                        ParasiteScriptCoreData.ContinueFlag = false;
                    }
                }

                if (SplitValue(Instruction, 0 ) == "stop"){
                    FoundInstruction = true;
                    exit(0);
                }

                if (SplitValue(Instruction, 0 ) == "jumpl"){   
                    FoundInstruction = true;
                    for (int i = 0 ; i <= JumpPointCounter ; i ++){
                        if (JumpPoints[i].Name == SplitValue(Instruction, 1)){
                            ParasiteScriptCoreData.ReturnLine = ParasiteScriptCoreData.LineCounter;
                            ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                        }
                    }
                }

                if (SplitValue(Instruction, 0 ) == "var"){
                    FoundInstruction = true;
                    VaribleMemory[VaribleCounter].Name = SplitValue(Instruction, 1 );

                    string VaribleData = SplitValue(Instruction, 2 );
                    int VaribleType = 0;

                    if (ReadValue(VaribleData , 0 , 0) == "'"){
                        VaribleType = 1;
                    }
                    else {
                        VaribleType = 0;
                    }
                    
                    if (VaribleType == 1){
                        string StoredData = "";
                        for (int i = 0 ; i <= VaribleData.size() ; i ++){
                            if (ReadValue(VaribleData , i , i) != "'"){
                                StoredData += ReadValue(VaribleData , i , i);
                            }
                        }
                        VaribleMemory[VaribleCounter].Value = StoredData;
                        VaribleMemory[VaribleCounter].IValue = 0;
                    }
                    else {
                        VaribleMemory[VaribleCounter].IValue = StringToInt(VaribleData);
                        VaribleMemory[VaribleCounter].Value = " ";
                    }

                    VaribleCounter++;   

                }

                if (SplitValue(Instruction, 0 ) == "PMem"){
                    FoundInstruction = true;

                    PermanentMemory[PMemCounter].Name = SplitValue(Instruction, 1 );

                    string VaribleData = SplitValue(Instruction, 2 );

                    if (IsNumber(VaribleData)){
                        PermanentMemory[PMemCounter].IValue = StringToInt(VaribleData);

                        PMemCounter++;   
                    }

                    else {
                        cout << "Error Cannot Load Strings Into PMEM" << endl;
                        ParasiteScriptCoreData.ErrorFlag = true;
                    }
                }

                if (SplitValue(Instruction, 0 ) == "Texture"){
                    FoundInstruction = true;

                    TextureMemory[TextureCounter].Name = SplitValue(Instruction, 1 );

                    if (IsPathFile(TextFormat("GameData/Worlds/World%i/Scripts/Textures/%s.png", SceneIDMirror , SplitValue(Instruction, 2 ).c_str() ))){
                        TextureMemory[TextureCounter].TextureValue = LoadTexture(TextFormat("GameData/Worlds/World%i/Scripts/Textures/%s.png", SceneIDMirror , SplitValue(Instruction, 2 ).c_str() ));
                        TextureCounter ++;
                    }

                    else {
                        cout << "Texture Does Not Exist:" << TextFormat("GameData/Worlds/World%i/Scripts/Textures/%s.png", SceneIDMirror , SplitValue(Instruction, 2 ).c_str() ) << endl;
                        ParasiteScriptCoreData.ErrorFlag = true;
                    }


    
                }

                if (SplitValue(Instruction, 0 ) == "WriteTFlag"){
                    ToggleFlags[StringToInt(SplitValue(Instruction, 1 ))].Value = StringToInt(SplitValue(Instruction, 2));
                    FoundInstruction = true;
                }


                if (SplitValue(Instruction, 0 ) == "ReadTFlag"){
                    int Value = ToggleFlags[StringToInt(SplitValue(Instruction, 1 ))].Value;
                    StoreIntToMemory(SplitValue(Instruction, 2), Value);
                    FoundInstruction = true;
                }

                if (SplitValue(Instruction, 0 ) == "WriteDialogue"){
                    string Arg = ReadValue(Instruction , 14, Instruction.size() - 1);

                    if (IsNumber(Arg)){ // Pull from LG Langauge Pack
                        OmegaTechTextSystem.Write(GlobalPackData.Lines[StringToInt(SplitValue(Instruction, 1))]);
                    }
                    else {
                        OmegaTechTextSystem.Write(Arg);
                    }
                    FoundInstruction = true;
                }

                if (SplitValue(Instruction, 0 ) == "AddWDLInstruction"){
                    string WDLString = SplitValue(Instruction, 1 );
                    wstring ws(WDLString.begin(), WDLString.end());
                    ExtraWDLInstructions += ws;
                    FoundInstruction = true;
                }

                if (SplitValue(Instruction, 0 ) == "WipeExtraWDL"){
                    ExtraWDLInstructions = L"";
                    FoundInstruction = true;
                }

                if (SplitValue(Instruction, 0 ) == "ClaimOBJ"){
                    int ObjectId = StringToInt(SplitValue(Instruction, 1));

                    switch (ObjectId){
                        case 1:
                            OmegaTechGameObjects.Object1Owned = true;
                            break;
                        case 2:
                            OmegaTechGameObjects.Object2Owned = true;
                            break;
                        case 3:
                            OmegaTechGameObjects.Object3Owned = true;
                            break;
                        case 4:
                            OmegaTechGameObjects.Object4Owned = true;
                            break;
                        case 5:
                            OmegaTechGameObjects.Object5Owned = true;
                            break;
                    }

                    FoundInstruction = true;
                }
                

                if (SplitValue(Instruction, 0 ) == "SetScene"){
                    SetSceneFlag = true;
                    SetSceneId = StringToInt(SplitValue(Instruction, 1 ));
                    FoundInstruction = true;
                }

                if (SplitValue(Instruction, 0 ) == "Kill"){
                    ParasiteRunning = false;
                    FoundInstruction = true;
                }
                if (SplitValue(Instruction, 0 ) == "SetCameraPosition"){
                    SetCameraFlag = true;

                    int X = StringToInt(SplitValue(Instruction, 1 ));
                    int Y = StringToInt(SplitValue(Instruction, 2 ));
                    int Z = StringToInt(SplitValue(Instruction, 3 ));

                    SetCameraPos = {float(X),float(Y),float(Z)};

                    FoundInstruction = true;
                }

                if (SplitValue(Instruction, 0 ) == "SetMainLightPosition"){

                    int X = StringToInt(SplitValue(Instruction, 1 ));
                    int Y = StringToInt(SplitValue(Instruction, 2 ));
                    int Z = StringToInt(SplitValue(Instruction, 3 ));

                    SunPos = {float(X) ,float(Y),float(Z)};
                    
                    FoundInstruction = true;
                }

                if (SplitValue(Instruction, 0 ) == "PullMouse"){
                    FoundInstruction = true;

                    StoreIntToMemory( SplitValue(Instruction, 1 ), GetMouseX());
                    StoreIntToMemory( SplitValue(Instruction, 2 ), GetMouseY());
                }

                if (SplitValue(Instruction, 0 ) == "PullInputs "){
                    FoundInstruction = true;

                    int InpValue = 0;

                    if (!IsGamepadAvailable(0)){
                        if (IsKeyDown(KEY_LEFT)){
                            InpValue = 4;
                        }
                        if (IsKeyDown(KEY_RIGHT)){
                            InpValue = 2;
                        }
                        if (IsKeyDown(KEY_UP)){
                            InpValue = 1;
                        }
                        if (IsKeyDown(KEY_DOWN)){
                            InpValue = 3;
                        }    
                        if (IsKeyDown(KEY_SPACE)){
                            InpValue = 5;
                        }
                        if (IsKeyDown(KEY_A)){
                            InpValue = 6;
                        }
                        if (IsKeyDown(KEY_S)){
                            InpValue = 7;
                        }
                    }
                    else {
                        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) >= 0.5f){
                            InpValue = 2;
                        }
                        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) <= -0.5f){
                            InpValue = 4;
                        }

                        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) >= 0.5f){
                            InpValue = 3;
                        }
                        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) <= -0.5f){
                            InpValue = 1;
                        }

                        if (IsGamepadButtonDown(0 , GAMEPAD_BUTTON_LEFT_FACE_UP)){
                            InpValue = 1;
                        }
                        if (IsGamepadButtonDown(0 , GAMEPAD_BUTTON_LEFT_FACE_DOWN)){
                            InpValue = 3;
                        }
                        if (IsGamepadButtonDown(0 , GAMEPAD_BUTTON_LEFT_FACE_RIGHT)){
                            InpValue = 2;
                        }
                        if (IsGamepadButtonDown(0 , GAMEPAD_BUTTON_LEFT_FACE_LEFT)){
                            InpValue = 4;
                        }

                        if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)){
                            InpValue = 6;
                        }
                        if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)){
                            InpValue = 7;
                        }

                        if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)){
                            InpValue = 5;
                        }
                    }
                    
                    StoreIntToMemory(SplitValue(Instruction, 1 ) , InpValue);
                }

                if (SplitValue(Instruction, 0 ) == "DrawFrame"){

                    BeginTextureMode(ParasiteTarget);
                    ClearBackground(BLACK);

                }

                if (SplitValue(Instruction, 0 ) == "DrawTexture"){
                    int X = StringToInt(SplitValue(Instruction, 2 ));
                    int Y = StringToInt(SplitValue(Instruction, 3 ));
                    int Scale = StringToInt(SplitValue(Instruction, 4 ));

                    DrawTextureEx(PullTextureFromMemory(SplitValue(Instruction, 1 )) , {X , Y} , 0 , Scale, WHITE);
                }


                if (SplitValue(Instruction, 0 ) == "EndFrame"){
                    EndTextureMode();

                    BeginDrawing();
                        DrawTexturePro(ParasiteTarget.texture, (Rectangle){ 0, 0, ParasiteTarget.texture.width, -ParasiteTarget.texture.height }, (Rectangle){ 0, 0, float(GetScreenWidth()), float(GetScreenHeight())}, (Vector2){ 0, 0 } , 0.f , WHITE);
                    EndDrawing();
                }
            }
        }
    }
}
