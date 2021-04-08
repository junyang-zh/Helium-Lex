/*
 * Main.cpp : Entry point of the application
 * By James Zhang
 */

#include <cstdio>
#include <string>
#include <cstring>

#define DEBUG(x) (printf("DEBUG:%d\n", x))

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
        for (int i(0); current_line[i]; ++i) {
            if (current_line[i] == '#') {
                fputc('\n', OutPreFile);
                break;
            }
            fputc(current_line[i], OutPreFile);
        }
    }
    delete[] current_line;

    fclose(InFile);
    fclose(OutPreFile);

    FILE * InPreFile = fopen(f_out[0], "r"),
        * OutLexFile = fopen(f_out[1], "w+");

    Helium::DFA LEXAUTO;
    LEXAUTO.add_new_KW_Trie(Helium::PyKWList, "Keyword");
    LEXAUTO.add_new_OP_Trie(Helium::PySingOpList, "Operator");
    LEXAUTO.add_new_OP_Trie(Helium::PyCompOpList, "Operator");
    LEXAUTO.add_number_rule();
    LEXAUTO.add_str_rule();
    LEXAUTO.add_token_rule();
    int WordCnt(0), nl(0), curr; // now char
    char * currtoken = new char[Max_Line_Length];
    while ((curr = fgetc(InPreFile)) != EOF) {
        auto res = LEXAUTO.next(curr);
        // printf("chk %d\n", res.first);
        if (res.first == -1) { // moving
            currtoken[nl++] = curr;
        }
        else if (res.first == -2) { // \t
            currtoken[nl] = '\0';
            fputs("<\'\\t\',Indent>\n", OutLexFile);
            currtoken[0] = curr;
            nl = 1;
        }
        else if (res.first == -3) { // \n\r
            continue;
        }
        else { // if >= 0 // TODO solve finished asssss
            currtoken[nl] = '\0';
            fprintf(OutLexFile, "%04d\t", WordCnt++);
            fputs(res.second.c_str(), OutLexFile);
            fputs(",\t\t\t", OutLexFile);
            fputs(currtoken, OutLexFile);
            fputs("\n", OutLexFile);
            if (curr == ' ' || curr == '\n' || curr == '\r') {
                nl = 0;
            }
            else {
                currtoken[0] = curr;
                nl = 1;
            }
        }
    };
    delete[] currtoken;

    fclose(InPreFile);
    fclose(OutLexFile);

    printf("Tokenizing finished successfully.\n");

    return 0;
}
