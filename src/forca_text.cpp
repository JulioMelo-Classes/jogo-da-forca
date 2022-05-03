#include "Forca.hpp"
#include <iostream>
using namespace std;


void Forca::imprimir_chutes_errados(){
    cout << "Chutes errados --> "; //Imprime cada letra chutada errada.
    for (char letra : m_letras_erradas){
        cout << letra << " ";
    }
}

void Forca::imprimir_boneco(int n_erros) {
    switch (n_erros) {
        case 0: cout << endl; cout << endl; cout << endl; break;
        case 1: cout << "  o  \n" << endl; cout << endl; break;
        case 2: cout << "  o\n  |  \n"; cout << endl; break;
        case 3: cout << "  o\n /|  \n"; cout << endl; break;
        case 4: cout << "  o\n /|\\ \n"; cout << endl; break;
        case 5: cout << "  o\n /|\\ \n / \n"; break;
        case 6: cout << "Vixe, Fim de Jogo!\n  o\n /|\\ \n / \\";
        default: break;
    }
}

void Forca::imprimir_underline(string palavra_escolhida, vector<char> consoante, char vogal, int dificuldade){
    if (dificuldade == 0){
        for (char letra : palavra_escolhida){
            if (mapa_letra_valor[letra]){
                cout << letra << " ";
            }else if (letra == ' '){
                cout << "- ";
            }else if (*find(consoante.begin(), consoante.end(), letra) == letra){
                cout << letra << " ";
            }else{
                cout << "_ ";
            }
        }
    } else if (dificuldade == 1){
        for (char letra : palavra_escolhida){
            if (mapa_letra_valor[letra]){
                cout << letra << " ";
            }else if (letra == ' '){
                cout << "- ";
            }else if (letra == vogal){
                cout << letra << " ";
            }else{
                cout << "_ ";
            }
        }
    } else {
        for (char letra : palavra_escolhida){
            if (mapa_letra_valor[letra]){
                cout << letra << " ";
            }else if (letra == ' '){
                cout << "- ";
            }else{
                cout << "_ ";
            }
        }
    }
}

pair<bool, string> Forca::eh_valido() {
    int contador1 = 1, contador2 = 0, contador3 = 0, contador_n_palavras = 0;
    string linha_1, linha_2, linha_3, linha_4, parte1, palavra_invalida;
    pair<bool, string> parTeste;
    ifstream arq_palavras;
    ifstream arq_scores;

    arq_palavras.open(m_arquivo_palavras);

    // Verifica se o arquivo de palavras existe.
    if (arq_palavras.is_open()){
        parTeste.first = true;
    }else{
        cout << "Erro! Arquivo das palavras inexistente." << endl;
        exit(-1);
    }

    //Verifica se os caracteres das palavras estão dentro do padrão apresentado.
    while(!arq_palavras.eof()) {
        getline(arq_palavras, linha_1, ';');
        parte1 = linha_1;
        getline(arq_palavras, linha_2, '\n');
        char palavra[parte1.length()];
        contador1++;
        for (int i = 0; i < (int)sizeof(palavra); i++) {
            palavra[i] = parte1[i];
            if ((palavra[i] >= 'a' && palavra[i] <= 'z') || (palavra[i] >= 'A' && palavra[i] <= 'Z') || (palavra[i] == ' ')){
                contador_n_palavras++;
                if (contador_n_palavras == (int)sizeof(palavra)){
                    parTeste.first = true;
                }
            } else {
                palavra_invalida = parte1;
                cout << "Palavra \"" + palavra_invalida + "\" inválida na linha " + to_string(contador1) + "." << endl;
                exit(-1);
            }  
        }
        palavra_invalida = parte1;

        //Verifica se possui uma frequência ou uma frequência positiva.
        try{
            if (stoi(linha_2) > 0 || linha_2.empty()){
                parTeste.first = true;
            }
        }catch(...){
            cout << "A palavra \"" + palavra_invalida + "\" na linha " + to_string(contador1-1) + ", não possui frequência." << endl;
            exit(-1);
        }

        if (stoi(linha_2) < 0){
            cout << "A palavra \"" + palavra_invalida + "\" na linha " + to_string(contador1-1) + ", não possui frequência positiva." << endl;
            exit(-1);
        }

        //Verifica se existe palavras com menos de cinco letras.
        if ((int)linha_1.size() <= 4) {
            cout << "Erro! A palavra " + palavra_invalida + " na linha " + to_string(contador1-1) + " contém menos de 5 letras." << endl;
            exit(-1);
        } else {
            parTeste.first = true;
        }
    }

    arq_palavras.close();
    arq_scores.open(m_arquivo_scores);

    // Verifica se o arquivo de scores existe.
    if (arq_scores.is_open()){
        parTeste.first = true;
    }else{
        cout << "Erro! Arquivo das scores inexistente." << endl;
        exit(-1);
    }

    //Verifica se tem mais ou menos três ';' na linha do arquivo scores.
    while(!arq_scores.eof()) {
        contador3++;
        getline(arq_scores, linha_3);
        for (int i = 0; i < (int)linha_3.size(); i++) {
            if (linha_3[i] == ';') {
                contador2++;
            }
        }
        int start = 0;
        int end = linha_3.find(';');

        // Verificação da quantidade de ';'.
        if(contador2 > 3) {
            cout << "Erro! Mais de 3 ';' na linha: " << contador3 << endl;
            exit(-1);
        } else if (contador2 < 3) {
            cout << "Erro! Menos de 3 ';' na linha: " << contador3 << endl;
            exit(-1);
        }
        contador2 = 0;

        // Verificação de campos vazios.
        while (end != -1) {
            start = end + 1;
            end = linha_3.find(';', start);
            if (linha_3.substr(start, end - start).size() == 0) {
                cout << "Algum campo vazio na linha: " << contador3 << endl;
                exit(-1);
            }
        }
        if (linha_3.substr(start, end - start).size() == 0) {
            cout << "Algum campo vazio na linha: " << contador3 << endl;
            exit(-1);
        }
    }
    arq_scores.close();

    return parTeste;
}


void Forca::mostrar_scores() {
    fstream arquivos_scores;
    vector<string> dificuldade, jogador, palavras, pontos;
    vector<string>::iterator it_dificuldade, it_jogador, it_palavras, it_pontos;

    arquivos_scores.open(m_arquivo_scores, fstream::in);
    string linha_p, linha_s;
    int pos, tam;

    while (!arquivos_scores.eof()) {
        getline(arquivos_scores, linha_s);
        pos = linha_s.find(";", 0);
        dificuldade.push_back(linha_s.substr(0, pos));
        tam = pos + 1;
        pos = linha_s.find(";", pos + 1);
        jogador.push_back(linha_s.substr(tam, pos - tam));
        tam = pos + 1;
        pos = linha_s.find(";", pos + 1);
        palavras.push_back(linha_s.substr(tam, pos - tam));
        tam = pos + 1;
        pos = linha_s.find("\n", -1);
        pontos.push_back(linha_s.substr(tam, pos - tam));
    }
    int i = 0, j = 0, fix = 0;
    cout << "  Dificuldade  |     Jogador     |       Palavras       ";
    cout <<"|  Pontos" << endl;
    for (it_dificuldade = dificuldade.begin(), it_jogador = jogador.begin(), it_pontos = pontos.begin(); it_dificuldade != dificuldade.end(); ++it_dificuldade, ++it_jogador, ++it_pontos) {
        //------------------ DIFICULDADES + NOMES ------------------
        int daux1 = 0;
        for (char item : *it_dificuldade){
            daux1++;
        }
        for (int i = 0; i < 20; i++){
            if (15 - daux1 == i*2){
                for (j = 0; j < i; j++) {
                    cout << " ";
                }
            }
        }
        cout << *it_dificuldade;
        int aux1 = 0;
        for (char item : *it_dificuldade){
            aux1++;
        }
        for (int i = 0; i < 20; i++){
            if (15 - aux1 == i*2){
                for (j = 0; j < i; j++) {
                    cout << " ";
                }
            }
        }
        cout << "|";
        int daux2 = 0;
        for (char item : *it_jogador){
            daux2++;
        }
        if (daux2%2 == 0){
            daux2++;
        }
        for (int i = 0; i < 20; i++){
            if (17 - daux2 == i*2){
                for (j = 0; j < i; j++) {
                    cout << " ";
                }
            }
        }
        cout << *it_jogador;
        int aux2 = 0;
        int caux2 = 0;
        for (char item : *it_jogador){
            aux2++;
        }
        if (aux2%2 == 0){
            aux2++;
        }else{
            aux2 = aux2 + 2;
        }
        for (int i = 0; i < 20; i++){
            if (17 - aux2 == i*2){
                for (j = 0; j < i; j++) {
                    cout << " ";
                    caux2++;
                }
            }
        }
        if (((aux2-1) % 2 == 0) && (caux2 % 2 == 0)){
            cout << " ";
        } else if (((aux2) % 2 == 1) && (caux2 % 2 == 0)){
            cout << "";
        } else if (((aux2) % 2 == 1) && (caux2 % 2 == 1)){
            cout << " ";
        } else if (((aux2-1) % 2 == 0) && (caux2 % 2 == 1)) {
            cout << " ";
        }
        cout << "|";

        //------------------ PALAVRAS + PONTOS ------------------
        char delim = ',';
        vector<string> result;
        stringstream ss(palavras[i]);
        string item;

        while (getline(ss, item, delim)) {
            result.push_back(item);
        }
        
        for (string palavra : result) {
            if (fix == 0) {
                int daux2 = 0;
                for (char item : palavra){
                    daux2++;
                }
                if (daux2%2 == 0){
                    daux2++;
                }
                for (int i = 0; i < 20; i++){
                    if (21 - daux2 == i*2){
                        for (j = 0; j < i; j++) {
                            cout << " ";
                        }
                    }
                }
                cout << " ";
                cout << palavra;
                int aux2 = 0;
                int caux2 = 0;
                for (char item : palavra){
                    aux2++;
                }
                if (aux2%2 == 0){
                    aux2++;
                }else{
                    aux2 = aux2 + 2;
                }
                for (int i = 0; i < 20; i++){
                    if (21 - aux2 == i*2){
                        for (j = 0; j < i; j++) {
                            cout << " ";
                            caux2++;
                        }
                    }
                }
                if (((aux2-1) % 2 == 0) && (caux2 % 2 == 0)){
                    cout << " ";
                } else if (((aux2) % 2 == 1) && (caux2 % 2 == 0)){
                    cout << "";
                } else if (((aux2) % 2 == 1) && (caux2 % 2 == 1)){
                    cout << " ";
                } else if (((aux2-1) % 2 == 0) && (caux2 % 2 == 1)) {
                    cout << " ";
                }
                cout << "|   " << *it_pontos << endl;
                fix++;
            } else {
                cout << "               |                 | ";
                int daux2 = 0;
                for (char item : palavra){
                    daux2++;
                }
                if (daux2%2 == 0){
                    daux2++;
                }
                for (int i = 0; i < 20; i++){
                    if (21 - daux2 == i*2){
                        for (j = 0; j < i; j++) {
                            cout << " ";
                        }
                    }
                }
                cout << palavra;
                int aux2 = 0;
                int caux2 = 0;
                for (char item : palavra){
                    aux2++;
                }
                if (aux2%2 == 0){
                    aux2++;
                }else{
                    aux2 = aux2 + 2;
                }
                for (int i = 0; i < 20; i++){
                    if (21 - aux2 == i*2){
                        for (j = 0; j < i; j++) {
                            cout << " ";
                            caux2++;
                        }
                    }
                }
                if (((aux2-1) % 2 == 0) && (caux2 % 2 == 0)){
                    cout << " ";
                } else if (((aux2) % 2 == 1) && (caux2 % 2 == 0)){
                    cout << "";
                } else if (((aux2) % 2 == 1) && (caux2 % 2 == 1)){
                    cout << " ";
                } else if (((aux2-1) % 2 == 0) && (caux2 % 2 == 1)) {
                    cout << " ";
                }
                cout << "|   " << endl;
            }
        }

        cout << "---------------+-----------------+";
        for (j = 22; j > 0; j--){
            cout << "-";
        }
        cout << "+--------" << endl;
        i++;
        fix = 0;
    }
}