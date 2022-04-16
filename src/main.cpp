#include <iostream>
#include "Forca.hpp"
#include <string>

using namespace std;
int main(int argc, char *argv[]){
    setlocale(LC_ALL, " ");
    Forca forca(argv[1], argv[2]);

    cout << ">>> Lendo arquivos de palavras ["<< argv[1] <<"] e scores ["<< argv[2] <<"], por favor aguarde.." << endl;
    cout << "--------------------------------------------------------------------" << endl;
    forca.carregar_arquivos();

    auto valid = forca.eh_valido(argv[1], argv[2]);
    if(!valid.first){ //sai do programa ao encontrar um erro
        cout<<valid.second<<endl;
        exit(-1);
    }else{
        cout << "Arquivos OK!" << endl;
    }

    cout << "--------------------------------------------------------------------" << endl;
    int option, dif;
    while(true){
        cout << "Bem vindo ao Jogo Forca! Por favor escolha uma das opções" << endl;
        cout << "1 - Iniciar Jogo" << endl;
        cout << "2 - Ver scores anteriores" << endl;
        cout << "3 - Sair do Jogo" << endl;
        cout << "Sua escolha: ";
        cin >> option;
        cout << endl;
        if(option == 1){
            cout << "Vamos iniciar o jogo! Por favor escolha o nível de dificuldade" << endl;
            cout << "1 - Fácil" << endl;
            cout << "2 - Médio" << endl;
            cout << "3 - Difícil" << endl;
            cout << "Sua escolha: ";
            cin >> dif;
            cout << endl;
            Forca::Dificuldade d;
            if (dif == 1){
                d = Forca::Dificuldade::FACIL;
                cout << "Iniciando o Jogo no nível fácil, será que você conhece essa palavra?" << endl;
            }else if(dif == 2){
                d = Forca::Dificuldade::MEDIO;
                cout << "Iniciando o Jogo no nível médio, será que você conhece essa palavra?" << endl;
            }else if(dif == 3){
                d = Forca::Dificuldade::DIFICIL;
                cout << "Iniciando o Jogo no nível difícil, será que você conhece essa palavra?" << endl;
            }
            forca.set_dificuldade(d);
            cout << endl;
            cout << endl;
            cout << endl;
            /*ler informações do jogador para o score e gravar no arquivo*/
        }
        else if(option == 2){
            forca.mostrar_scores();
            forca.mostrar_frequencias();
            forca.mostrar_palavras();
            forca.montarPar();
            forca.mostrar_parDePalavras();
        }else{ //qualquer outro número sai do jogo
            

            break;
        }    
    }
    return 0;
}