#include "Forca.hpp"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    Forca forca(argv[1], argv[2]); // Construindo a classe "forca".
    auto valid = forca.eh_valido(); // Verificação de todos os testes.

    // Primeira exibição de Interface.
    cout << ">>> Lendo arquivos de palavras ["<< argv[1] <<"] e scores ["<< argv[2] <<"], por favor aguarde.." << endl;
    cout << "--------------------------------------------------------------------" << endl;
    if (!valid.first) { cout<< valid.second <<endl; exit(-1); }
    else { cout << "Arquivos OK!" << endl; }
    cout << "--------------------------------------------------------------------" << endl;

    forca.carregar_arquivos();

    int opcao, dificuldade, tentativas = 6, acertos = 1, dificuldade_escolhida = 0, pontuacao = 0;
    char palpite, consoante, vogal;
    bool aux_tentativas, aux_acertos;
    string palavra_secreta, nome;
    vector<string> palavras;
    vector<char> letras_erradas;

    tela_inicial:
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
        if (opcao == 1) {
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
                forca.separar_por_dificuldade();
                palavra_secreta = forca.get_palavra_atual();
                vogal = forca.muda_valor_vogal_mapa(palavra_secreta, dificuldade_escolhida);
                cout << "Iniciando o Jogo no nível médio, será que você conhece essa palavra?" << endl;
            } else if (dificuldade == 3){
                dificuldade_escolhida = 2;
                forca.set_dificuldade(dificuldade_escolhida);
                forca.separar_por_dificuldade();
                palavra_secreta = forca.get_palavra_atual();
                cout << "Iniciando o Jogo no nível difícil, será que você conhece essa palavra?" << endl;
            }
            cout << "Palavra secreta: " << palavra_secreta << endl;
            while(true) {

                while(true) { //Loop da Rodada.
                    cout << endl;
                    forca.imprimir_underline(palavra_secreta, consoante, vogal);
                    cout << endl;
                    forca.imprimir_chutes_errados();
                    cout << endl;
                    cout << "Pontos: " << pontuacao << " | Tentativas: " << tentativas << endl;
                    cout << "Palpite: ";
                    cin >> palpite; //Ler o palpite.
                    cout << endl;
                    palpite = toupper(palpite); //Modifica a leitura pra maiúsculo.

                    //Marca true no map das letras da palavra.
                    forca.muda_valor_letra_mapa(palpite);

                    //Calcula tentativas.
                    aux_tentativas = forca.verifica_tentativas(palavra_secreta, palpite, tentativas);
                    if(aux_tentativas){ tentativas--;}
                    if (*find(palavra_secreta.begin(), palavra_secreta.end(), palpite) == palpite){ tentativas++; }

                    //Verifica se letra chutada existe na palavra.
                    bool resultado = forca.letra_existe(palpite, palavra_secreta);

                    //Calcula acertos.
                    aux_acertos = forca.verifica_acertos(palavra_secreta, palpite);
                    letras_erradas = forca.vector_letra_errada(palavra_secreta, palpite);
                    if (aux_acertos){
                        if (letras_erradas.empty()){ acertos++; }
                        else if (*find(letras_erradas.begin(), letras_erradas.end(), palpite) == palpite){} 
                        else { acertos++; }
                    }
                    
                    if (resultado) { 
                        forca.pontuacao_jogador(palavra_secreta, palpite, pontuacao, resultado);
                        forca.get_letras(palpite);
                        cout << "--------------------------------------------------------------------" << endl;
                        cout << "Muito bem! A palavra contém a letra "<< palpite << "!" << endl;
                        cout << "--------------------------------------------------------------------" << endl;
                    } else {
                        forca.pontuacao_jogador(palavra_secreta, palpite, pontuacao, resultado);
                        forca.get_letras(palpite);
                        cout << "--------------------------------------------------------------------" << endl;
                        cout << "Meh, não achei a letra " << palpite << "! :<" << endl;
                        cout << "--------------------------------------------------------------------" << endl;
                    }

                    forca.imprimir_boneco(forca.get_tam_letras_erradas());

                    //Se descobrir todas as letras da palavra, VITÓRIA.
                    if (forca.verifica_vitoria(palpite, palavra_secreta, acertos, dificuldade_escolhida)){
                        cout << "Parabéns! Você conseguiu descobrir a palavra secreta: " + palavra_secreta + "." << endl;
                        cout << endl;
                        cout << "Digite o seu nome: ";
                        cin >> nome;
                        cout << endl;
                    }
                    
                    //Se as tentativas acabarem ou enforcar o boneco, FIM DE JOGO.
                    if (tentativas == 0 && forca.verifica_derrota()){
                        cout << endl;
                        cout << "Suas tentativas acabaram e você não conseguiu descobrir a palavra: " + palavra_secreta + "." << endl;
                        cout << endl;
                        cout << "Digite o seu nome: ";
                        cin >> nome;
                        cout << endl;
                    } else if (tentativas == 0){
                        cout << endl;
                        cout << "Tentativas esgotadas! A palavra secreta era: " + palavra_secreta + "." << endl;
                        cout << endl;
                        cout << "Digite o seu nome: ";
                        cin >> nome;
                        cout << endl;
                    } else if (forca.verifica_derrota()){
                        cout << endl;
                        cout << "Você enforcou o bonequinho. :( A palavra secreta era: " + palavra_secreta + "." << endl;
                        cout << endl;
                        cout << "Digite o seu nome: ";
                        cin >> nome;
                        cout << endl;
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