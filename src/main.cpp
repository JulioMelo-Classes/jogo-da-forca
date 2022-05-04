#include <iostream>

#include "Forca.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    Forca forca(argv[1], argv[2]);   // Construindo a classe "forca".
    auto valid = forca.eh_valido();  // Verificação de todos os testes.

    // Primeira exibição de Interface, carregamento de arquivos.
    cout << ">>> Lendo arquivos de palavras [" << argv[1] << "] e scores [" << argv[2] << "], por favor aguarde.." << endl;
    cout << "--------------------------------------------------------------------" << endl;
    if (!valid.first) {
        cout << valid.second << endl;
        exit(-1);
    } else {
        cout << "Arquivos OK!" << endl;
    }
    cout << "--------------------------------------------------------------------" << endl;

    forca.carregar_arquivos();

    int opcao, dificuldade, tentativas = 6, acertos = 0, dificuldade_escolhida = 0, pontuacao = 0, pontos_final = 0;
    char palpite, vogal;
    vector<char> consoante;
    bool aux_tentativas;
    string palavra_secreta, nome, palavra, dificuldade_scores;
    vector<char> letras_erradas;
    vector<string> palavras_acertadas_inf;

    Inicio:

    // Loop principal do jogo.
    while (true) {
        // Interface principal
        cout << "Bem vindo ao Jogo Forca! Por favor escolha uma das opções" << endl;
        cout << "1 - Iniciar Jogo" << endl;
        cout << "2 - Ver scores anteriores" << endl;
        cout << "3 - Sair do Jogo" << endl;
        cout << "Sua escolha: ";
        cin >> opcao;  // Ler opção do usuário.
        cout << endl;

        if (opcao == 1) {
            cout << "Vamos iniciar o jogo! Por favor escolha o nível de dificuldade" << endl;
            cout << "1 - Fácil" << endl;
            cout << "2 - Médio" << endl;
            cout << "3 - Difícil" << endl;
            cout << "Sua escolha: ";
            cin >> dificuldade;  // Ler dificuldade escolhida.
            cout << endl;

        tela_inicial:  // Place holder para quando o jogador escolher continuar jogando após o fim da rodada.

            if (dificuldade == 1) {
                dificuldade_scores = "FACIL";
                dificuldade_escolhida = 0;
                forca.set_dificuldade(dificuldade_escolhida);
                palavra = forca.sorteia_palavra(forca.separar_por_dificuldade());
                palavra_secreta = forca.get_palavra_atual(palavra);
                consoante = forca.muda_valor_consoante_mapa(palavra_secreta, dificuldade_escolhida);
                cout << "Iniciando o Jogo no nível fácil, será que você conhece essa palavra?" << endl;
            } else if (dificuldade == 2) {
                dificuldade_scores = "MEDIO";
                dificuldade_escolhida = 1;
                forca.set_dificuldade(dificuldade_escolhida);
                palavra = forca.sorteia_palavra(forca.separar_por_dificuldade());
                palavra_secreta = forca.get_palavra_atual(palavra);
                vogal = forca.muda_valor_vogal_mapa(palavra_secreta);
                cout << "Iniciando o Jogo no nível médio, será que você conhece essa palavra?" << endl;
            } else if (dificuldade == 3) {
                dificuldade_scores = "DIFICIL";
                dificuldade_escolhida = 2;
                forca.set_dificuldade(dificuldade_escolhida);
                palavra = forca.sorteia_palavra(forca.separar_por_dificuldade());
                palavra_secreta = forca.get_palavra_atual(palavra);
                cout << "Iniciando o Jogo no nível difícil, será que você conhece essa palavra?" << endl;
            }

            /*
             * IMPRIME A PALAVRA SECRETA PARA FACILITAR TESTES DE DESENVOLVIMENTO
            cout << "Palavra secreta: ";
            for (char letra : palavra_secreta){
                if (letra == ' '){ cout << '-'; } else { cout << letra; }
            }
            cout << endl;
            */
            forca.verifica_espaco(acertos, palavra_secreta, consoante, vogal);

            // Loop Principal.
            while (true) {
            lde:
                while (true) {  // Loop da Rodada.
                    string jogada_informacoes;
                    cout << endl;
                    forca.imprimir_underline(palavra_secreta, consoante, vogal, dificuldade_escolhida); //Além de imprimir, muda o valor das letras já relevadas para true no mapa_letra_valor.
                    cout << endl;
                    forca.imprimir_chutes_errados();
                    cout << endl;
                    cout << "Pontos: " << pontuacao << " | Tentativas: " << tentativas << endl;
                    fflush(stdin);
                    p:
                    cout << "Palpite: ";
                    cin >> palpite;  // Ler o palpite.
                    cout << endl;
                    if (forca.verifica_entrada(palpite)){ } else { goto p; }
                    cout << endl;
                    palpite = toupper(palpite);  
                    
                    aux_tentativas = forca.verifica_tentativas(palavra_secreta, palpite, tentativas);
                    if (aux_tentativas) {
                        tentativas--;
                    }
                    if (*find(palavra_secreta.begin(), palavra_secreta.end(), palpite) == palpite) {
                        tentativas++;
                    }
                    // Verifica se letra chutada existe na palavra.
                    bool resultado = forca.letra_existe(palpite, palavra_secreta);

                    letras_erradas = forca.vector_letra_errada(palavra_secreta, palpite);

                    if (resultado) {
                        forca.imprimir_boneco(forca.get_tam_letras_erradas());
                        if (forca.get_letras(palpite, consoante, vogal, resultado, acertos, pontuacao) == false){ 
                            cout << "Você já chutou essa letra!" << endl;
                            goto lde;
                        }
                        cout << "--------------------------------------------------------------------" << endl;
                        cout << "Muito bem! A palavra contém a letra " << palpite << "!" << endl;
                        cout << "--------------------------------------------------------------------" << endl;
                        forca.pontuacao_jogador(palavra_secreta, palpite, pontuacao, resultado);
                        forca.muda_valor_letra_mapa(palpite); //Para cada palpite certo, retorna true para o valor das chaves do map das letras.
                        acertos++;
                    } else {
                        if (forca.get_letras(palpite, consoante, vogal, resultado, acertos, pontuacao) == false){ 
                            cout << "Você já chutou essa letra!" << endl;
                            forca.imprimir_boneco(forca.get_tam_letras_erradas());
                            goto lde;
                        }
                        cout << "--------------------------------------------------------------------" << endl;
                        cout << "Meh, não achei a letra " << palpite << "! :<" << endl;
                        cout << "--------------------------------------------------------------------" << endl;
                        forca.get_letras_erradas(palpite, palavra_secreta); 
                        forca.imprimir_boneco(forca.get_tam_letras_erradas());
                        forca.pontuacao_jogador(palavra_secreta, palpite, pontuacao, resultado);
                    }
                    
                    // Se as tentativas acabarem ou enforcar o boneco, FIM DE JOGO.
                    if (tentativas == 0 || forca.verifica_derrota()) {
                        char resposta;
                        cout << endl;
                        cout << "Suas tentativas acabaram ou você enforcou o boneco! Palavra secreta: ";
                        for (char letra : palavra_secreta){
                            if (letra == ' '){ cout << '-'; } else { cout << letra; }
                        }
                        cout << "." << endl;
                        cout << endl;
                        jn1:
                        cout << "Deseja jogar novamente?[S/N] ";
                        cin >> resposta;
                        resposta = (toupper(resposta));
                        switch (resposta) {
                            case 'S':
                                forca.reset_rodada(tentativas, acertos, consoante, vogal, palavra_secreta, letras_erradas);
                                pontuacao = 0;
                                goto tela_inicial;
                                break;
                            case 'N':
                                cout << "Digite o seu nome: ";
                                cin >> nome;
                                transform(nome.begin(), nome.end(), nome.begin(), ::toupper);
                                cout << endl;
                                cout << "--------------------------------------------------------------------" << endl;
                                cout << "----------- Salvando informações no arquivo dos scores. ------------" << endl;
                                cout << "--------------------------------------------------------------------" << endl;
                                // Guardar informações.
                                jogada_informacoes = '\n' + dificuldade_scores + ';' + nome + ';';
                                forca.escrever_scores(jogada_informacoes, palavras_acertadas_inf, pontos_final);
                                forca.reset_rodada(tentativas, acertos, consoante, vogal, palavra_secreta, letras_erradas);
                                goto Inicio;
                            default:
                                cout << "Caractere inválido." << endl;
                                goto jn1;
                                break;
                        }
                        cout << endl;
                    }
                    // Se descobrir todas as letras da palavra, VITÓRIA.
                    if (forca.verifica_vitoria(acertos)) {
                        char resposta;
                        cout << "Parabéns! Você conseguiu descobrir a palavra secreta: ";
                        for (char letra : palavra_secreta){
                            if (letra == ' '){ cout << '-'; } else { cout << letra; }
                        }
                        cout << "." << endl;
                        cout << endl;
                        pontos_final += pontuacao;
                        jn2:
                        cout << "Deseja jogar novamente?[S/N] ";
                        cin >> resposta;
                        resposta = (toupper(resposta));
                        palavras_acertadas_inf.push_back(palavra_secreta + ',');
                        switch (resposta) {
                            case 'S':
                                forca.reset_rodada(tentativas, acertos, consoante, vogal, palavra_secreta, letras_erradas);
                                pontuacao = 0;
                                fflush(stdin);
                                goto tela_inicial;
                                break;
                            case 'N':
                                cout << "Digite o seu nome: ";
                                cin >> nome;
                                transform(nome.begin(), nome.end(), nome.begin(), ::toupper);
                                cout << endl;
                                cout << "--------------------------------------------------------------------" << endl;
                                cout << "---------- Salvando informações no arquivo dos scores. -----------" << endl;
                                cout << "--------------------------------------------------------------------" << endl;
                                // Guardar informações.
                                jogada_informacoes = '\n' + dificuldade_scores + ';' + nome + ';';
                                forca.escrever_scores(jogada_informacoes, palavras_acertadas_inf, pontos_final);
                                forca.reset_rodada(tentativas, acertos, consoante, vogal, palavra_secreta, letras_erradas);
                                goto Inicio;
                            default:
                                cout << "Caractere inválido." << endl;
                                goto jn2;
                                break;
                        }
                        cout << endl;
                    }
                }
            }
        } else if (opcao == 2) {
            forca.mostrar_scores();
        } else {  
            break;
        }
    }
    return 0;
}