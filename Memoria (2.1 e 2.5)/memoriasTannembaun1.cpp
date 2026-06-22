#include <bits/stdc++.h>
using namespace std;

//Atividade 2.5


int memoria[2048][2048];

int main()
{
    
    for(int i=0; i<2048; i++)
        for(int j=0; j<2048; j++)
            memoria[i][j] = 0;

    int linha_travada = -1;
    int coluna_travada = -1;

    while(true)
    {
        string a, b, c, d, addr;
        cout << "CS, RAS, CAS, WE, ADDR (S para sair): ";
        cin >> a >> b >> c >> d >> addr;

        if(a == "S") break;

        if(stoi(a) == 0)
        {
            cout << "Chip select off.\n";
            continue;
        }

        // RAS ativo  trava a linha
        if(stoi(b) == 1)
        {
            linha_travada = stoi(addr);
            cout << "Linha " << linha_travada << " travada.\n";
        }

        // CAS ativo trava a coluna
        if(stoi(c) == 1)
        {
            coluna_travada = stoi(addr);
            cout << "Coluna " << coluna_travada << " travada.\n";
        }

        //AMbos
        if(linha_travada == -1 || coluna_travada == -1)
        {
            cout << "Aguardando RAS e CAS.\n";
            continue;
        }

        // WE=0  leitura
        if(stoi(d) == 0)
        {
            cout << "D = " << memoria[linha_travada][coluna_travada] << "\n";
        }

        // WE=1  escrita
        if(stoi(d) == 1)
        {
            string bit;
            cout << "D: ";
            cin >> bit;
            memoria[linha_travada][coluna_travada] = stoi(bit);
            cout << "Gravado.\n";
        }
    }
}