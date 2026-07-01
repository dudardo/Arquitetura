#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    string memoria_principal[32];
    for (int indice = 0; indice < 32; indice++)
        memoria_principal[indice] = to_string(indice);

    int valido[4] = {0, 0, 0, 0};
    string tag_cache[4] = {"--", "--", "--", "--"};
    string dados_cache[4][2] = {{"??", "??"}, {"??", "??"}, {"??", "??"}, {"??", "??"}};

    int total_acessos = 0, acertos = 0, faltas = 0;

    cout << " #  ENTRADA  T  L  B  OP  RES     DADO |"
         << " [0]V T  D0  D1 |"
         << " [1]V T  D0  D1 |"
         << " [2]V T  D0  D1 |"
         << " [3]V T  D0  D1\n";
    cout << string(112, '-') << "\n";

    string endereco_5_bits, operacao, novo_dado;
    while (cin >> endereco_5_bits >> operacao) {
        if (endereco_5_bits.size() != 5) { cout << "endereco invalido: " << endereco_5_bits << "\n"; continue; }
        bool endereco_valido = true;
        for (char caractere : endereco_5_bits) if (caractere != '0' && caractere != '1') { endereco_valido = false; break; }
        if (!endereco_valido) { cout << "endereco invalido: " << endereco_5_bits << "\n"; continue; }

        novo_dado = "";
        if (operacao == "W" || operacao == "w") cin >> novo_dado;

        string tag = endereco_5_bits.substr(0, 2);
        string linha_endereco = endereco_5_bits.substr(2, 2);
        string byte_endereco = endereco_5_bits.substr(4, 1);

        int indice_tag = 0, indice_linha = 0, indice_byte = 0, indice_endereco = 0;
        for (char caractere : tag) indice_tag = indice_tag * 2 + (caractere - '0');
        for (char caractere : linha_endereco) indice_linha = indice_linha * 2 + (caractere - '0');
        indice_byte = byte_endereco[0] - '0';
        for (char caractere : endereco_5_bits) indice_endereco = indice_endereco * 2 + (caractere - '0');

        int indice_base = indice_endereco & ~1;

        bool hit = (valido[indice_linha] == 1) && (tag_cache[indice_linha] == tag);
        total_acessos++;

        if (!hit) {
            faltas++;
            valido[indice_linha] = 1;
            tag_cache[indice_linha] = tag;
            dados_cache[indice_linha][0] = memoria_principal[indice_base];
            dados_cache[indice_linha][1] = (indice_base + 1 < 32) ? memoria_principal[indice_base + 1] : "0";
        } else {
            acertos++;
        }

        string dado_retornado;
        if (operacao == "W" || operacao == "w") {
            dados_cache[indice_linha][indice_byte] = novo_dado;
            memoria_principal[indice_endereco] = novo_dado;
            dado_retornado = novo_dado;
        } else {
            dado_retornado = dados_cache[indice_linha][indice_byte];
        }

        string resultado = hit ? "ACERTO" : "FALTA ";

        cout << right << setw(2) << total_acessos << "  "
             << endereco_5_bits << "    "
             << tag << " " << linha_endereco << " " << byte_endereco << "  "
             << (char)toupper(operacao[0]) << "  "
             << resultado << " "
             << setw(5) << left << dado_retornado << "|";

        for (int indice = 0; indice < 4; indice++) {
            string marcador = (indice == indice_linha) ? "*" : " ";
            cout << marcador << "[" << indice << "]"
                 << valido[indice] << " "
                 << tag_cache[indice] << " "
                 << setw(4) << left << dados_cache[indice][0]
                 << setw(4) << left << dados_cache[indice][1] << "|";
        }
        cout << "\n";
    }

    cout << string(112, '-') << "\n";
    cout << "TOTAL=" << total_acessos
         << "  ACERTOS=" << acertos
         << "  FALTAS="  << faltas
         << "  TAXA="    << fixed << setprecision(1)
         << (total_acessos > 0 ? 100.0 * acertos / total_acessos : 0.0) << "%\n";

    return 0;
}