#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

void escritaArquivo(FILE *arquivo, int count, char palavra[], char simNao[])
{
    if (arquivo == NULL)
    {
        puts("Arquivo nao pode ser aberto...");
        return;
    }

    fprintf(arquivo, "Tentativa: %i %s", count, "\n");

    fprintf(arquivo, " Palavra Tentada: %s%s", palavra, "\n");

    fprintf(arquivo, " Palavra Aceita? %c%c%c%s", simNao[0], simNao[1], simNao[2], "\n");
}

void addAcertos(FILE *arquivo, char palavra[])
{
    if (arquivo == NULL)
    {
        puts("Arquivo nao pode ser aberto...");
        return;
    }

    fprintf(arquivo, "%s", palavra);
}

void leituraArquivo(FILE *arquivo)
{
    char line[150];
    cout << "----------Historico de tentativas----------" << endl;
    while ((fgets(line, sizeof(line), arquivo)) != NULL)
    {
        printf("%s", line);
    }

    cout << "-------------------------------------------" << endl;
}

typedef struct sTentativa
{
    char palavra[100];
    char simouNao[5];
} tentativa;

int validaPalavra(char palavra[], char anterior)
{
    int tam = strlen(palavra);

    if (tam <= 10)
    {
        return 1;
    }
    else if (palavra[0] == 'a' || palavra[0] == 'A')
    {
        return 1;
    }
    else if (palavra[tam - 1] == 'r' || palavra[tam - 1] == 'R')
    {
        return 1;
    }
    else if (palavra[0] == anterior)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int verificaRepetidas(FILE *arquivo, char palavra[])
{
    arquivo = fopen("acertos.txt", "r");
    strcat(palavra, "\n");

    char line[150];
    while ((fgets(line, sizeof(line), arquivo)) != NULL)
    {
        int value = strcmp(palavra, line);

        if (value == 0)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{

    FILE *arq_historico;
    FILE *arq_acertos;

    int acertosSeguidos = 0;
    bool verify = true;
    int countTentativa = 0;

    cout << "Bem vindo ao Piquinique na Lua!" << endl;
    cout << "Antes de tudo, digite seu nome: ";

    arq_historico = fopen("historico.txt", "wt");
    arq_acertos = fopen("acertos.txt", "wt");

    char nome[10];
    cin >> nome;

    fprintf(arq_acertos, "%s%s", nome, "\n");
    fprintf(arq_historico, "%s%s", nome, "\n");

    fclose(arq_historico);
    fclose(arq_acertos);

    cout << "--------------------------------------------------" << endl;
    cout << "Ola, vamos comecar a jogar.\n"
         << "Digite uma palavra e te direi se voce pode levar o que escreveu para o piquenique." << endl;
    cout << "Digite 'q' para sair, ou 'h' para consultar o historico de tentativas." << endl;
    cout << "Vc tem direito de errar 30 vezes. Caso acerte 5 vezes seguidas, sera considerado vencedor!\n";
    cout << "--------------------------------------------------" << endl;
    char anterior = ' ';

    while (countTentativa <= 30)
    {
        if (acertosSeguidos == 5)
        {
            cout << "VENCEDOR!!!" << endl;
            break;
        }

        cout << "-->Digite uma palavra: ";
        tentativa t;
        cin >> t.palavra;

        if (t.palavra[0] == 'q' && strlen(t.palavra) == 1)
        {
            break;
        }

        if (t.palavra[0] == 'h' && strlen(t.palavra) == 1)
        {
            arq_historico = fopen("historico.txt", "r");
            leituraArquivo(arq_historico);
            fclose(arq_historico);
            countTentativa--;
        }
        else
        {
            if (validaPalavra(t.palavra, anterior) == 1)
            {
                cout << "PARABENS! Voce pode levar " << t.palavra << " para o piqueniue!" << endl;
                acertosSeguidos++;

                if (verificaRepetidas(arq_acertos, t.palavra) == 0)
                {
                    arq_acertos = fopen("acertos.txt", "a");
                    addAcertos(arq_acertos, t.palavra);
                    fclose(arq_acertos);
                }

                t.simouNao[0] = 's';
                t.simouNao[1] = 'i';
                t.simouNao[2] = 'm';
            }
            else
            {
                cout << "Voce nao pode levar " << t.palavra << " para o piqueniue!" << endl;
                cout << "Voce tem mais " << (30 - countTentativa) << " tentativas" << endl;
                acertosSeguidos = 0;
                t.simouNao[0] = 'n';
                t.simouNao[1] = 'a';
                t.simouNao[2] = 'o';
            }
        }

        arq_historico = fopen("historico.txt", "a");
        escritaArquivo(arq_historico, countTentativa, t.palavra, t.simouNao);
        fclose(arq_historico);

        anterior = t.palavra[strlen(t.palavra) - 1];
        countTentativa++;
    }

    return 0;
}