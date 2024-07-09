#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <fstream>
using namespace std;

vector<vector<char>> mainMemory(300, vector<char>(4));
vector<vector<char>> secMemory(500, vector<char>(4));
vector<char> IR(4);
vector<int> IC(2);
vector<char> reg(4);
vector<int> pages;
bool toggle = false;
int SI = 0;
int TI = 0;
int PI = 0;
int EM = 0;
int PTR;
int cards = 0;

void mainMemoryPrint();
void secMemoryPrint();
void load();
void printPartMemory(int start);
void printPartSecMemory(int start);
void increment();
void terminate(int errorCode);
void readData(int memoryLocation);
void writeData(int memoryLocation);
void loadReg(int memoryLocation);
void storeReg(int memoryLocation);
void compare(int memoryLocation);
void branch(int memoryLocation);
void MOS(int memoryLocation);
int generateRandom();
int getRealAddress(int virtualAddress);
void allocateMemory(int virtualAddress);
bool checkPageFault(int virtualAddress);
void execute();
void cToD();
void input();

struct
{
    int TTL;
    int TLL;
    int TTC = 0;
    int TLC = 0;
    int p_track;
    int no_pc = 0;
    int d_track;
    int no_dc = 0;
} PCB;

ifstream myFile("Input3.txt");
ofstream OutputFile("MemoryOutput3.txt");

void mainMemoryPrint()
{
    for (int i = 0; i < 300; i++)
    {
        if (i % 10 == 0)
        {
            cout << "Block " << (i / 10 + 1) << ": ";
            cout << endl;
        }
        cout << "Memory Location " << (i + 1) << ": ";
        for (int j = 0; j < 4; j++)
        {
            cout << mainMemory[i][j] << " ";
        }
        cout << endl;
    }
}

void secMemoryPrint()
{
    for (int i = 0; i < 500; i++)
    {
        if (i % 10 == 0)
        {
            OutputFile << "Block " << (i / 10 + 1) << ": ";
            OutputFile << endl;
        }
        OutputFile << "Secondary Memory Location " << (i + 1) << ": ";
        for (int j = 0; j < 4; j++)
        {
            OutputFile << secMemory[i][j] << " ";
        }
        OutputFile << endl;
    }
}
void load()
{
    mainMemory.assign(300, vector<char>(4));
    secMemory.assign(500, vector<char>(4));
    pages.assign(0, '#');
    IR.assign(4, '#');
    IC.assign(2, 0);
    reg.assign(4, '#');
    toggle = false;
    PI = 0;
    SI = 3;
    TI = 0;
    EM = 0;
    cards = 0;
}
void printPartMemory(int start)
{
    cout << "Block " << start / 10 << endl;
    for (int i = start; i < start + 10; i++)
    {
        cout << "Memory Location " << i << " ";
        for (int j = 0; j < 4; j++)
        {
            cout << mainMemory[i][j] << " ";
        }
        cout << endl;
    }
}

void printPartSecMemory(int start)
{
    cout << "Block " << start / 10 << endl;
    for (int i = start; i < start + 10; i++)
    {
        cout << "Secondary Memory Location " << i << " ";
        for (int j = 0; j < 4; j++)
        {
            cout << secMemory[i][j] << " ";
        }
        cout << endl;
    }
}

void increment()
{
    if (IC[1] < 9)
    {
        IC[1] = IC[1] + 1;
    }
    else if (IC[0] < 9)
    {
        IC[0] = IC[0] + 1;
        IC[1] = 0;
    }
    else
    {
        cout << "Memory Overflow";
    }
    cout << "Instruction Counter: " << IC[0] << " " << IC[1] << endl;
}

void terminate(int errorCode)
{
    FILE *file = fopen("Output3.txt", "a");
    if (errorCode == 0)
    {
        cout << "No Error" << endl;
        fprintf(file, "%s", "No Error");
        EM = 0;
    }
    else if (errorCode == 1)
    {
        cout << "Out of Data" << endl;
        fprintf(file, "%s", "Out of Data");
        EM = 1;
    }
    else if (errorCode == 2)
    {
        cout << "Line Limit Exceeded" << endl;
        fprintf(file, "%s", "Line Limit Exceeded");
        EM = 2;
    }
    else if (errorCode == 3)
    {
        cout << "Time Limit Exceeded" << endl;
        fprintf(file, "%s", "Time Limit Exceeded");
        EM = 3;
    }
    else if (errorCode == 4)
    {
        cout << "Operation Code Error" << endl;
        fprintf(file, "%s", "Operation Code Error");
        EM = 4;
    }
    else if (errorCode == 5)
    {
        cout << "Operand Error" << endl;
        fprintf(file, "%s", "Operand Error");
        EM = 5;
    }
    else if (errorCode == 6)
    {
        cout << "Invalid Page Fault" << endl;
        fprintf(file, "%s", "Invalid Page Fault");
        EM = 6;
    }
    fprintf(file, "%c", '\n');
    fclose(file);
}

void readData(int memoryLocation)
{
    memoryLocation = (memoryLocation / 10) * 10;
    int row = memoryLocation;
    cout << "Instruction: ";
    for (int i = 0; i < 4; i++)
    {
        cout << IR[i];
    }
    cout << endl;
    if (PCB.no_dc == 0)
    {
        terminate(1);
        return;
    }
    else
    {
        PCB.no_dc -= 1;
    }

    int block = PCB.d_track;
    cout << "Data Track:" << PCB.d_track << endl;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            mainMemory[row + i][j] = secMemory[block * 10 + i][j];
        }
    }
    printPartMemory(row);
    cout << "\n";
    PCB.d_track += 1;
    cout << endl;
    increment();
}

void writeData(int memoryLocation)
{
    FILE *file = fopen("Output3.txt", "a");
    int row = (memoryLocation / 10) * 10;
    int col = 0;
    for (int i = 0; i < 40; i++)
    {
        if (mainMemory[row][col] == '\0')
        {
            int a = 6;
        }
        else
        {
            fprintf(file, "%c", mainMemory[row][col]);
            cout << mainMemory[row][col];
        }
        col++;
        if (col == 4)
        {
            col = 0;
            row++;
        }
    }
    cout << endl;
    fprintf(file, "%c", '\n');
    fclose(file);
    increment();
}

void loadReg(int memoryLocation)
{
    for (int col = 0; col < 4; col++)
    {
        reg[col] = mainMemory[memoryLocation][col];
    }

    for (int col = 0; col < 4; col++)
    {
        cout << reg[col] << " ";
    }
    cout << endl;
    increment();
}

void storeReg(int memoryLocation)
{
    for (int col = 0; col < 4; col++)
    {
        mainMemory[memoryLocation][col] = reg[col];
    }

    for (int col = 0; col < 4; col++)
    {
        cout << mainMemory[memoryLocation][col] << " ";
    }
    cout << endl;
    increment();
}

void compare(int memoryLocation)
{
    increment();
    for (int col = 0; col < 4; col++)
    {
        if (reg[col] != mainMemory[memoryLocation][col])
        {
            return;
        }
    }
    toggle = true;
}

void branch(int memoryLocation)
{
    cout << memoryLocation << endl;
    if (toggle)
    {
        IC[0] = memoryLocation / 10;
        IC[1] = memoryLocation % 10;
    }
    else
    {
        increment();
    }
}

void MOS(int memoryLocation)
{
    cout << "SI " << SI << " TI " << TI << " PI " << PI << endl;
    if (SI == 1 && TI == 0)
    {
        readData(memoryLocation);
    }
    else if (SI == 1 && TI == 2)
    {
        terminate(3);
    }
    else if (SI == 2 && TI == 0)
    {
        writeData(memoryLocation);
    }
    else if (SI == 2 && TI == 2)
    {
        terminate(3);
    }
    else if (SI == 3 && TI == 0)
    {
        terminate(0);
    }
    else if (SI == 3 && TI == 2)
    {
        terminate(0);
    }

    if (PI == 1 && TI == 0)
    {
        terminate(4);
    }
    else if (PI == 1 && TI == 2)
    {
        terminate(3);
        terminate(4);
    }
    else if (PI == 2 && TI == 0)
    {
        terminate(5);
    }
    else if (PI == 2 && TI == 2)
    {
        terminate(3);
        terminate(5);
    }
    else if (PI == 3 && TI == 0)
    {
        terminate(6);
    }
    else if (PI == 3 && TI == 2)
    {
        terminate(3);
    }
    SI = 3;
    return;
}

int generateRandom()
{
    int random = 100;
    bool flag;
    while (true)
    {
        flag = true;
        random = rand();
        random %= 30;
        for (int num : pages)
        {
            if (num == random)
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            pages.push_back(random);
            return random;
        }
    }
}

int getRealAddress(int virtualAddress)
{
    int PTE = PTR + virtualAddress / 10;
    if (mainMemory[PTE][0] == '\0')
    {
        return -1;
    }
    int RA = ((mainMemory[PTE][2] - '0') * 10 + (mainMemory[PTE][3] - '0')) * 10 + virtualAddress % 10;
    return RA;
}

void allocateMemory(int virtualAddress)
{
    int PTE = PTR + virtualAddress / 10;
    mainMemory[PTE][0] = '0';
    mainMemory[PTE][1] = virtualAddress / 10 + '0';
    int page = generateRandom();
    mainMemory[PTE][2] = page / 10 + '0';
    mainMemory[PTE][3] = page % 10 + '0';
}

bool checkPageFault(int virtualAddress)
{
    int realAddress = getRealAddress(virtualAddress);
    if (realAddress == -1)
    {
        // Page Fault
        if ((IR[0] == 'G' && IR[1] == 'D') || (IR[0] == 'S' && IR[1] == 'R'))
        {
            cout << "Valid Page Fault" << endl;
            allocateMemory(virtualAddress);
            return false;
        }
        else
        {
            cout << "Invalid Page Fault" << endl;
            return true;
        }
    }
    return false;
}

void execute()
{
    mainMemoryPrint();
    while (true)
    {
        IR = mainMemory[getRealAddress(IC[0] * 10 + IC[1])];
        cout << (IC[0] * 10 + IC[1]) << endl;
        cout << "Instruction: ";
        for (int i = 0; i < 4; i++)
        {
            cout << IR[i];
        }
        cout << endl;
        int memoryLocation = (IR[2] - '0') * 10 + (IR[3] - '0');
        cout << "PCB.TTC " << PCB.TTC << endl;
        if (IR[0] != 'H' && checkPageFault(memoryLocation))
        {
            PI = 3;
            MOS(memoryLocation);
            return;
        }
        if (memoryLocation > 99 || memoryLocation < 0)
        {
            PI = 2;
            MOS(memoryLocation);
            return;
        }
        int RA = getRealAddress(memoryLocation);
        cout << "Virtual Address: " << (IC[0] * 10 + IC[1]) << " Real Address: " << getRealAddress(IC[0] * 10 + IC[1]) << " Memory Location: " << memoryLocation << " RA: " << RA << endl;
        ;
        if (IR[0] == 'G' && IR[1] == 'D')
        {
            PCB.TTC += 2;
            cout << endl
                 << "GD:";
            SI = 1;
            if (PCB.TTC > PCB.TTL)
            {
                TI = 2;
                MOS(RA);
                return;
            }
            MOS(RA);
            if (EM != 0)
            {
                return;
            }
        }
        else if (IR[0] == 'P' && IR[1] == 'D')
        {
            PCB.TTC += 1;
            PCB.TLC += 1;
            SI = 2;
            if (PCB.TTC > PCB.TTL)
            {
                TI = 2;
                MOS(RA);
                return;
            }
            if (PCB.TLC > PCB.TLL)
            {
                terminate(2);
                return;
            }
            MOS(RA);
        }
        else if (IR[0] == 'L' && IR[1] == 'R')
        {
            PCB.TTC += 1;
            if (PCB.TTC > PCB.TTL)
            {
                TI = 2;
                MOS(RA);
                return;
            }
            loadReg(RA);
        }
        else if (IR[0] == 'S' && IR[1] == 'R')
        {
            PCB.TTC += 2;
            if (PCB.TTC > PCB.TTL)
            {
                TI = 2;
                MOS(RA);
                return;
            }
            storeReg(RA);
        }
        else if (IR[0] == 'C' && IR[1] == 'R')
        {
            PCB.TTC += 1;
            if (PCB.TTC > PCB.TTL)
            {
                TI = 2;
                MOS(RA);
                return;
            }
            compare(RA);
        }
        else if (IR[0] == 'B' && IR[1] == 'T')
        {
            cout << "Toggle: " << toggle << endl;
            PCB.TTC += 1;
            if (PCB.TTC > PCB.TTL)
            {
                TI = 2;
                MOS(RA);
                return;
            }
            branch(memoryLocation);
        }
        else if (IR[0] == 'H')
        {
            PCB.TTC += 1;
            SI = 3;
            if (PCB.TTC > PCB.TTL)
            {
                TI = 2;
                MOS(RA);
                return;
            }
            MOS(RA);
            return;
        }
        else
        {
            PI = 1;
            MOS(RA);
            return;
        }
        cout << "Instruction: ";
        for (int i = 0; i < 4; i++)
        {
            cout << IR[i];
        }
        cout << endl;
        printPartMemory(PTR);
    }
}

void cToD()
{
    bool prog = false;
    string text;
    int col = 0;
    int row = 0;
    int card = 0;
    while (getline(myFile, text))
    {
        cout << "Text:" << text << endl;
        string str = text.substr(0, 4);
        if (str == "$AMJ")
        {
            PTR = generateRandom();
            PTR *= 10;
            PCB.TTL = stoi(text.substr(8, 4));
            cout << "TTL: " << text.substr(8, 4) << endl;
            PCB.TLL = stoi(text.substr(12, 4));
            cout << "TLL: " << text.substr(12, 4) << endl;
            PCB.TTC = 0;
            PCB.TLC = 0;
            cout << PCB.TTC << " " << PCB.TLC << " " << PCB.TTC << " " << PCB.TTL << endl;
            prog = true;
            col = 0;
            row = 0;
        }
        else if (str == "$DTA")
        {
            cout << "PTR: " << PTR << endl;
            prog = false;
        }
        else if (str == "$END")
        {
            secMemoryPrint();
            input();
        }
        else
        {
            int temp = row;
            col = 0;
            if (prog)
            {
                if (PCB.no_pc == 0)
                {
                    PCB.p_track = card;
                }
                int dataIndex = 0;
                while (dataIndex < text.size())
                {
                    secMemory[row][col++] = text[dataIndex++];
                    if (text[dataIndex - 1] == 'H')
                    {
                        secMemory[row][col++] = '0';
                        secMemory[row][col++] = '0';
                        secMemory[row][col++] = '0';
                    }
                    if (col == 4)
                    {
                        col = 0;
                        row++;
                    }
                }
                card++;
                PCB.no_pc++;
            }

            else
            {
                if (PCB.no_dc == 0)
                {
                    PCB.d_track = card;
                }
                int dataIndex = 0;
                while (dataIndex < text.size())
                {
                    secMemory[row][col++] = text[dataIndex++];
                    if (col == 4)
                    {
                        col = 0;
                        row++;
                    }
                }
                card++;
                PCB.no_dc++;
            }
            row = temp + 10;
        }
    }
}

void input()
{

    bool prog = false;
    string text;
    int col = 0;
    int row = 0;
    while (PCB.no_pc > 0)
    {
        for (int i = PCB.p_track * 10; i < PCB.p_track * 10 + 10; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                text.push_back(secMemory[i][j]);
            }
        }
        PCB.p_track += 1;
        PCB.no_pc -= 1;
        int dataIndex = 0;
        row = generateRandom();
        cout << "Block: " << row << " Cards: " << cards << endl;
        mainMemory[PTR + cards][0] = '0';
        mainMemory[PTR + cards][1] = cards + '0';
        mainMemory[PTR + cards][2] = row / 10 + '0';
        mainMemory[PTR + cards][3] = row % 10 + '0';
        row *= 10;
        ++cards;
        cout << "Row:" << row << endl
             << "Text: " << text << endl;
        while (dataIndex < text.size())
        {
            mainMemory[row][col++] = text[dataIndex++];
            if (col == 4)
            {
                col = 0;
                row++;
            }
        }
        text = "";
        cout << "Program Track:" << PCB.p_track << endl;
    }
    execute();
}

int main()
{
    load();
    cToD();
    return 0;
}