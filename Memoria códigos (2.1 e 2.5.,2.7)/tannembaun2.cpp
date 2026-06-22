#include <bits/stdc++.h>
using namespace std;
//Atividade 2.5
int memoria[2][8192][8192];

int main()
{
    int linha_travada = -1;
    int coluna_travada = -1;
    int banco_ativo = -1;

    while(1)
    {
        string cs, ras, cas, we, addr, b0, b1;
        cout << "CS, RAS, CAS, WE, ADDR, B0, B1 (S para sair): ";
        cin >> cs >> ras >> cas >> we >> addr >> b0 >> b1;

        if(cs == "S") break;

        if(stoi(cs) == 0)
        {
            cout << "Chip select off.\n";
            continue;
        }

        // seleciona banco
        if(stoi(b0) == 1)
            banco_ativo = 0;
        else if(stoi(b1) == 1)
            banco_ativo = 1;
        else
        {
            cout << "Nenhum banco selecionado.\n";
            continue;
        }

        // RAS ativo  trava linha
        if(stoi(ras) == 1)
        {
            linha_travada = stoi(addr);
            cout << "Linha " << linha_travada << " travada no banco " << banco_ativo << ".\n";
        }

        // CAS ativ trava coluna
        if(stoi(cas) == 1)
        {
            coluna_travada = stoi(addr);
            cout << "Coluna " << coluna_travada << " travada no banco " << banco_ativo << ".\n";
        }

        if(linha_travada == -1 || coluna_travada == -1)
        {
            cout << "Aguardando RAS e CAS.\n";
            continue;
        }

        // WE=0 leitura dos 4 bits
        if(stoi(we) == 0)
        {
            cout << "D = "
                 << memoria[banco_ativo][linha_travada][coluna_travada]
                 << " em decimal\n";
        }

        // WE=1 escrita dos 4 bits
        if(stoi(we) == 1)
        {
            string d0, d1, d2, d3;
            cout << "D0 D1 D2 D3: ";
            cin >> d0 >> d1 >> d2 >> d3;

            // empacota 4 bits em um int
            memoria[banco_ativo][linha_travada][coluna_travada] =
                (stoi(d3) << 3) | (stoi(d2) << 2) | (stoi(d1) << 1) | stoi(d0);

            cout << "Gravado.\n";
        }
    }
}