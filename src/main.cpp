#include <iostream>
#include "Forca.hpp"

using namespace std;
int main(int argc, char *argv[]){
    setlocale(LC_ALL, " ");
    Forca forca(argv[1], argv[2]);
    string palavra_secreta = "MELANCIA";
    cout << ">>> Lendo arquivos de palavras ["<< argv[1] <<"] e scores ["<< argv[2] <<"], por favor aguarde.." << endl;
    cout << "--------------------------------------------------------------------" << endl;
    forca.carregar_arquivos();

    auto valid = forca.eh_valido();
    if(!valid.first){ //sai do programa ao encontrar um erro
        cout<<valid.second<<endl;
        exit(-1);
    }else{
        cout << "Arquivos OK!" << endl;
    }
    forca.montar_par();
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
            int d = 0;
            if (dif == 1){
                d = 0;
                cout << "Iniciando o Jogo no nível fácil, será que você conhece essa palavra?" << endl;
            }else if(dif == 2){
                d = 1;
                cout << "Iniciando o Jogo no nível médio, será que você conhece essa palavra?" << endl;
            }else if(dif == 3){
                d = 2;
                cout << "Iniciando o Jogo no nível difícil, será que você conhece essa palavra?" << endl;
            }
            forca.set_dificuldade(d);
            cout << endl;
            cout << endl;
            cout << endl;
            //forca.separarPorDificuldade();
            while(true){
                /*
                string p = forca.proxima_palavra();
                //exibe interface do jogo 
                while (!forca.rodada_terminada()){ //loop da rodada
                    //ler palpite 
                    string palpite;
                    auto result = forca.palpite(palpite);
                    //testa palpite e atualiza a interface dependendo do resultado 
                }
                if(//acertou a palavra inteira ){
                    //imprime interface de continuar / parar 
                    if (//parar )
                        break;
                    else
                        forca.reset_rodada();
                }
                else{ //perdeu 
                    //imprime gameover e a palavra que estava sendo jogada 
                    break;
                }*/
            }
            //ler informações do jogador para o score e gravar no arquivo 
        }
        else if(option == 2){
            //forca.mostrar_scores();
            forca.montar_media();
            //forca.mostrar_palavras();
            //forca.mostrar_parDePalavras();
        }else{ //qualquer outro número sai do jogo
            break;
        }    
    }
    return 0;
}