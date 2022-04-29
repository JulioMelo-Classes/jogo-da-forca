#include "Forca.hpp"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    Forca forca(argv[1], argv[2]); // Construindo a classe "forca".

    // Primeira exibição de Interface.
    cout << ">>> Lendo arquivos de palavras ["<< argv[1] <<"] e scores ["<< argv[2] <<"], por favor aguarde.." << endl;
    cout << "--------------------------------------------------------------------" << endl;
    auto valid = forca.eh_valido(); // Verificação de todos os testes.
    if (!valid.first) {
        cout<< valid.second <<endl;
        exit(-1);
        } else { 
            cout << "Arquivos OK!" << endl;
        }
    cout << "--------------------------------------------------------------------" << endl;

    forca.carregar_arquivos();

    int opcao, dificuldade, tentativas = 6, acertos = 0, dificuldade_escolhida = 0;
    char palpite, consoante, vogal;
    string palavra_secreta;

    // Loop principal do jogo.
    while(true) {
        cout << "Bem vindo ao Jogo Forca! Por favor escolha uma das opções" << endl;
        cout << "1 - Iniciar Jogo" << endl;
        cout << "2 - Ver scores anteriores" << endl;
        cout << "3 - Sair do Jogo" << endl;
        cout << "Sua escolha: ";
        cin >> opcao; // Ler opção do usuário.
        cout << endl;

        // Caso a escolha do jogador perante a interface seja '1' :
        if(opcao == 1) {
            cout << "Vamos iniciar o jogo! Por favor escolha o nível de dificuldade" << endl;
            cout << "1 - Fácil" << endl;
            cout << "2 - Médio" << endl;
            cout << "3 - Difícil" << endl;
            cout << "Sua escolha: ";
            cin >> dificuldade; // Ler dificuldade escolhida.
            cout << endl;

            if (dificuldade == 1){
                dificuldade_escolhida = 0;
                forca.set_dificuldade(dificuldade_escolhida);
                forca.separar_por_dificuldade();
                palavra_secreta = forca.get_palavra_atual();
                consoante = forca.muda_valor_consoante_mapa(palavra_secreta, dificuldade_escolhida);
                cout << "Iniciando o Jogo no nível fácil, será que você conhece essa palavra?" << endl;
            } else if (dificuldade == 2){
                dificuldade_escolhida = 1; 
                forca.set_dificuldade(dificuldade_escolhida);
                cout << "Iniciando o Jogo no nível médio, será que você conhece essa palavra?" << endl;
                forca.separar_por_dificuldade();
                palavra_secreta = forca.get_palavra_atual();
                vogal = forca.muda_valor_vogal_mapa(palavra_secreta, dificuldade_escolhida);
            } else if (dificuldade == 3){
                dificuldade_escolhida = 2;
                forca.set_dificuldade(dificuldade_escolhida);
                cout << "Iniciando o Jogo no nível difícil, será que você conhece essa palavra?" << endl;
                forca.separar_por_dificuldade();
                palavra_secreta = forca.get_palavra_atual();
            }

            while(true) {
                while(true) { //loop da rodada
                    forca.imprimir_chutes_errados();
                    cout << endl;
                    forca.imprimir_underline(palavra_secreta, consoante, vogal);
                    cout << endl;
                    cout << "Palavra secreta: " << palavra_secreta << endl;
                    cout << "Pontos: " << "TESTE" << endl;
                    cout << "Tentativas: "; 
                    cout << tentativas << endl; // Diminui o número de tentantivas a cada jogada.
                    cout << "Palpite: ";
                    cin >> palpite; //Ler o palpite.
                    cout << endl;
                    palpite = toupper(palpite); //Modifica a leitura pra maiúsculo.

                    forca.muda_valor_letra_mapa(palpite);
                    //Verifica se a letra existe na palavra e imprime.
                    bool resultado = forca.letra_existe(palpite, palavra_secreta);

                    if (resultado) { 
                        //Se letra existir na palavra.
                        acertos++;
                        cout << "--------------------------------------------------------------------" << endl;
                        cout << "Muito bem! A palavra contém a letra "<< palpite << "!" << endl;
                        forca.imprimir_boneco(forca.get_tam_letras_erradas());
                        //Se descobrir todas as letras da palavra.
                        if (forca.verifica_vitoria(palpite, palavra_secreta, acertos) && tentativas > 0){
                            cout << "Parabéns! Você conseguiu descobrir a palavra secreta: " + palavra_secreta + "." << endl;
                            exit(-1);
                        }else if (tentativas == 0){
                            cout << "Tentativas esgotadas!" << endl;
                            exit(-1);
                        }
                        break;
                    }else{
                        //Se letra não existir na palavra. 
                        tentativas--;
                        cout << "--------------------------------------------------------------------" << endl;
                        cout << "Meh, não achei a letra " << palpite << "! :<" << endl;
                        forca.get_letras_erradas(palpite);
                        forca.imprimir_boneco(forca.get_tam_letras_erradas());
                        //Se número de letras erradas não repetidas se excederem, fim de jogo.
                        if (forca.verifica_derrota(palpite)){
                            cout << endl;
                            cout << "Você enforcou o bonequinho :(" << endl;
                            exit(-1);
                        }else if (tentativas == 0){
                            cout << "Tentativas esgotadas!" << endl;
                            exit(-1);
                        }
                        break;
                    }
                }
            }
            // Ler informações do jogador para o score e gravar no arquivo.
            
        // Caso a escolha do jogador perante a interface seja '1' :
        } else if (opcao == 2) {
            forca.mostrar_scores();
        } else { // Caso a opção seja 3 para sair do jogo ou alguma outra não especificada, o jogo encerra.
            break;
        }    
    }
    return 0;
}