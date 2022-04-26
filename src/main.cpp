#include <iostream>
#include "Forca.hpp"

using namespace std;




int main(int argc, char *argv[]) {
    setlocale(LC_ALL, ""); // Fazer com que o programa reconheça acentuação
    Forca forca(argv[1], argv[2]);

    cout << ">>> Lendo arquivos de palavras ["<< argv[1] <<"] e scores ["<< argv[2] <<"], por favor aguarde.." << endl;
    cout << "--------------------------------------------------------------------" << endl;
    auto valid = forca.eh_valido();
    if (!valid.first) {
        cout<< valid.second <<endl;
        exit(-1);
        } else { 
            cout << "Arquivos OK!" << endl;
        }
    cout << "--------------------------------------------------------------------" << endl;

    forca.carregar_arquivos();
    forca.montar_par();
    forca.montar_media();

    int option, dif, pontos = 0, d = 0, erros = 0, count_lc = 0;
    char palpite;
    string palavra_secreta;
    string palavra_secretaCopia;
    string palavra_sec;
    vector<string>::iterator it;
    vector<char> letrasErradas;
    bool continuaChute = false;
    map<char,bool> chute;

    while(true) {
        cout << "Bem vindo ao Jogo Forca! Por favor escolha uma das opções" << endl;
        cout << "1 - Iniciar Jogo" << endl;
        cout << "2 - Ver scores anteriores" << endl;
        cout << "3 - Sair do Jogo" << endl;
        cout << "Sua escolha: ";
        cin >> option;
        cout << endl;

        if(option == 1) {
            cout << "Vamos iniciar o jogo! Por favor escolha o nível de dificuldade" << endl;
            cout << "1 - Fácil" << endl;
            cout << "2 - Médio" << endl;
            cout << "3 - Difícil" << endl;
            cout << "Sua escolha: ";
            cin >> dif;
            cout << endl;

            if (dif == 1){ d = 0; cout << "Iniciando o Jogo no nível fácil, será que você conhece essa palavra?" << endl;
            } else if (dif == 2){ d = 1; cout << "Iniciando o Jogo no nível médio, será que você conhece essa palavra?" << endl;
            } else if (dif == 3){ d = 2; cout << "Iniciando o Jogo no nível difícil, será que você conhece essa palavra?" << endl;}

            forca.set_dificuldade(d);
            forca.separarPorDificuldade();
            // Selecionando uma palavra secreta aleatória pelas palavras filtradas por dificuldade.
            palavra_secreta = forca.sorteiaPalavra(forca.separarPorDificuldade());
            

            while(true) {

                // string p = forca.proxima_palavra();
                // Exibe interface do jogo 
                
                while(true) { //loop da rodada
                    cout << endl;
                    cout << endl;
                    cout << endl;
                    cout << endl;
                    cout << "Chutes errados: ";
                    for (char letra : letrasErradas){
                        cout << letra << " ";
                    }
                    cout << endl;
                    for (char letra : palavra_secreta){
                        if (chute[letra]){
                            cout << letra << " ";
                        }else{
                            cout << "_ ";
                        }  
                    }
                    cout << endl;
                    cout << "Print temporário para teste de palavra: " << palavra_secreta << endl;
                    cout << "Pontos: " << pontos << endl;
                    cout << "Palpite: ";
                    cin >> palpite;
                    palpite = toupper(palpite);
                    chute[palpite] = true;
                    cout << "\n";

                    for (int i = 0; i < (int)palavra_secreta.size(); i++){
                        palavra_secretaCopia.push_back(palavra_secreta[i]);
                    }

                    sort(palavra_secretaCopia.begin(),palavra_secretaCopia.end());
                    palavra_secretaCopia.erase(unique(palavra_secretaCopia.begin(), palavra_secretaCopia.end()), palavra_secretaCopia.end());

                    bool result = forca.letraExiste(palpite, palavra_secreta);

                    for (auto letra : palavra_secretaCopia){
                        if (letra == palpite){
                            palavra_sec.push_back(letra);
                            palavra_sec.erase(unique(palavra_sec.begin(), palavra_sec.end()), palavra_sec.end());
                        }
                    }
                    
                    if (palavra_sec.size() == palavra_secretaCopia.size()){
                        cout << "PARABÉNS, VC GANHOU!!!!" << endl;
                        exit(-1);
                    }

                    if (result) {
                        cout << "Muito bem! A palavra contém a letra "<< palpite << "!" << endl;
                        forca.imprimirBoneco(letrasErradas.size());
                        cout << "\n\n";
                        break;
                    } else {
                        letrasErradas.push_back(palpite);
                        cout << "Meh, não achei a letra " << palpite << "! :<" << endl;
                        forca.imprimirBoneco(letrasErradas.size());
                        if (letrasErradas.size() == 6){
                            cout << endl;
                            cout << "EROOOOOOOOOOOOOOU" << endl;
                            exit(-1);
                        }
                        cout << "\n\n";
                        break;
                    }
                }
                /*
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
        } else if (option == 2) {
            
            // forca.mostrar_palavraSort();
            // forca.mostrar_scores();
            // forca.mostrar_palavras();
            // forca.mostrar_parDePalavras();
        } else { //qualquer outro número sai do jogo
            break;
        }    
    }
    return 0;
}