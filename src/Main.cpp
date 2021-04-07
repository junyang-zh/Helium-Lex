/*
 * Main.cpp : Entry point of the application
 * By James Zhang
 */

#include <cstdio>
#include <string>
#include <cstring>

#include "LexPy.h"
#include "DFA.h"

using Helium::PyKWList;

constexpr int Max_Line_Length = 500;

char f_in[100], f_out[2][100];

int main(int argc, char *argv[], char *envp[]) {

    // reading files
    if (argc <= 1) {
        printf("Running by default input: \'./tests/test.py\'\n");
        strcpy(f_in, "./tests/test.py");
    }
    else {
        strcpy(f_in, argv[0]);
    }
    if (argc <= 2) {
        printf("Output into default location: \'./tests/out/\'\n");
        strcpy(f_out[0], "./tests/out/preprocessed.txt");
        strcpy(f_out[1], "./tests/out/lexically_analyzed.txt");
    }
    else {
        strcpy(f_out[0], argv[1]);
        strcpy(f_out[0] + strlen(argv[1]), "preprocessed.txt");
        strcpy(f_out[1], argv[1]);
        strcpy(f_out[1] + strlen(argv[1]), "lexically_analyzed.txt");
    }
    FILE * InFile = fopen(f_in, "r"),
        * OutPreFile = fopen(f_out[0], "w+");

    // preprocessing
    char *current_line = new char[Max_Line_Length];
    while (fgets(current_line, Max_Line_Length, InFile) != NULL) {
        fputs(current_line, OutPreFile);
    }
    delete[] current_line;

    fclose(InFile);
    fclose(OutPreFile);

    FILE * InPreFile = fopen(f_out[0], "r"),
        * OutLexFile = fopen(f_out[1], "w+");

    Helium::DFA LEXAUTO;
    LEXAUTO.add_new_Words_Trie(Helium::PyKWList, "Keyword");
    LEXAUTO.add_new_Words_Trie(Helium::PySingOpList, "OP");
    LEXAUTO.add_new_Words_Trie(Helium::PyCompOpList, "OP");
    int curr; // now char
    while ((curr = fgetc(InPreFile)) != EOF) {

    }

    fclose(OutLexFile);

    return 0;
}
