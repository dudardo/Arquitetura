#include <bits/stdc++.h>
using namespace std;

int main()
{
    
    char vef; //variavel de controle para operações
    string memoria[16];
    setlocale(LC_ALL, "Portuguese");
    for(int i=0; i<16; i++) for(int j=0; j<8; j++)memoria[i]="00000000"; //Zerando a matriz
    while(1)
    {
        cout<<"Insira W para escrever, R para ler, L para listar a memoria e qualquer outra entrada para parar: ";
        cin>> vef;
        string s;
        if(vef=='W') //Conversão e armazenamento no vetor de string 
        {
            
            cout<<"Insira o endereço de 4 bits: ";
            cin>>s;
            int adress=stoi(s, nullptr, 2);
            cout<<"Insira o dado de 8 bits: ";
            string b; cin>>b;
            memoria[adress]=b;
            cout<<"Armazenado com sucesso!"<<endl;

        }else if(vef=='R')
        {
            cout<<"Insira o endereço de 4 bits: ";
            cin>>s;
            int adress=stoi(s, nullptr, 2);
            cout<<memoria[adress]<<endl;

        }else if(vef=='L') //Percorrer e printar a matriz
        {
            for(auto i: memoria)
                cout<<i<<endl;
        }else {
            cout<<"Finalizado.";
            return 0;
        }
    }   
}