#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

void writeFile(FILE *file, int count, char word[], char yesOrNot[])
{
    if (file == NULL)
    {
        puts("File cannot be opened...");
        return;
    }

    fprintf(file, "Tentativa: %i %s", count, "\n");

    fprintf(file, " Palavra Tentada: %s%s", word, "\n");

    fprintf(file, " Palavra Aceita? %c%c%c%s", yesOrNot[0], yesOrNot[1], yesOrNot[2], "\n");
}

void addHits(FILE *file, char word[])
{
    if (file == NULL)
    {
        puts("File cannot be opened...");
        return;
    }

    fprintf(file, "%s", word);
}

void readFile(FILE *file)
{
    char line[150];
    cout << "----------Historico de tentativas----------" << endl;
    while ((fgets(line, sizeof(line), file)) != NULL)
    {
        printf("%s", line);
    }

    cout << "-------------------------------------------" << endl;
}

typedef struct sTry
{
    char word[100];
    char yesOrNot[5];
} attempt;

int checkWord(char word[], char previous)
{
    int size = strlen(word);

    if (size <= 10)
    {
        return 1;
    }
    else if (word[0] == 'a' || word[0] == 'A')
    {
        return 1;
    }
    else if (word[size - 1] == 'r' || word[size - 1] == 'R')
    {
        return 1;
    }
    else if (word[0] == previous)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int checkForMatchingWords(FILE *file, char word[])
{
    file = fopen("acertos.txt", "r");
    strcat(word, "\n");

    char line[150];
    while ((fgets(line, sizeof(line), file)) != NULL)
    {
        int value = strcmp(word, line);

        if (value == 0)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{

    FILE *history_FILE;
    FILE *hits_FILE;

    int hitSequence = 0;
    bool verify = false;
    int countTry = 0;

    cout << "Bem vindo ao Piquenique na Lua!" << endl;
    cout << "Antes de tudo, digite seu nome: ";

    history_FILE = fopen("historico.txt", "wt");
    hits_FILE = fopen("acertos.txt", "wt");

    char name[10];
    cin >> name;

    fprintf(hits_FILE, "%s%s", name, "\n");
    fprintf(history_FILE, "%s%s", name, "\n");

    fclose(history_FILE);
    fclose(hits_FILE);

    cout << "--------------------------------------------------" << endl;
    cout << "Ola, vamos comecar a jogar.\n"
         << "Digite uma palavra e te direi se voce pode levar o que escreveu para o piquenique." << endl;
    cout << "Digite 'q' para sair, ou 'h' para consultar o historico de tentativas." << endl;
    cout << "Vc tem direito de errar 30 vezes. Caso acerte 5 vezes seguidas, sera considerado vencedor!\n";
    cout << "--------------------------------------------------" << endl;
    char previous = ' ';

    while (countTry <= 30)
    {
        if (hitSequence == 5)
        {
            cout << "VENCEDOR!!!" << endl;
            break;
        }

        cout << "-->Digite uma palavra: ";
        attempt t;
        cin >> t.word;

        if (t.word[0] == 'q' && strlen(t.word) == 1)
        {
            break;
        }

        if (t.word[0] == 'h' && strlen(t.word) == 1)
        {
            history_FILE = fopen("historico.txt", "r");
            readFile(history_FILE);
            fclose(history_FILE);
            countTry--;
        }
        else
        {
            if (checkWord(t.word, previous) == 1)
            {
                cout << "PARABENS! Voce pode levar " << t.word << " para o piquenique!" << endl;
                hitSequence++;

                if (checkForMatchingWords(hits_FILE, t.word) == 0)
                {
                    hits_FILE = fopen("acertos.txt", "a");
                    addHits(hits_FILE, t.word);
                    fclose(hits_FILE);
                }
                verify = true;
                t.yesOrNot[0] = 's';
                t.yesOrNot[1] = 'i';
                t.yesOrNot[2] = 'm';
            }
            else
            {
                cout << "Voce nao pode levar " << t.word << " para o piquenique!" << endl;
                cout << "Voce tem mais " << (30 - countTry) << " tentativas" << endl;
                hitSequence = 0;
                t.yesOrNot[0] = 'n';
                t.yesOrNot[1] = 'a';
                t.yesOrNot[2] = 'o';
            }
        }

        history_FILE = fopen("historico.txt", "a");
        if (verify)
        {
            int size = strlen(t.word);
            t.word[size - 1] = '\0';
            writeFile(history_FILE, countTry, t.word, t.yesOrNot);
            fclose(history_FILE);
        }
        else
        {
            writeFile(history_FILE, countTry, t.word, t.yesOrNot);
            fclose(history_FILE);
        }

        previous = t.word[strlen(t.word) - 1];
        countTry++;
        verify = false;
    }

    return 0;
}