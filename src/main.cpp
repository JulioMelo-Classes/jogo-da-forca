#include "Forca.hpp"
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

    forca.carregar_arquivos(); // Carregando e inserindo no programa o arquivo de palavras e de scores.
    forca.montar_par(); // Função para montar par de [Palavra; Frequência] para utilização em diversas funcionalidades.
    forca.montar_media(); // Função para montar a média de frequência a ser utilizada no sorteio de palavras de acordo com a dificuldade do jogo.

    int opcao, dificuldade, dif = 0;
    char palpite; // Declaração da variável a ser usada para reservar o palpite.
    string palavra_secreta;
    string palavra_secretaCopia; // String contendo apenas as letras não repetidas da palavra secreta.
    string palavra_sec; // String auxiliar para verificação de acerto da palavra secreta.
    vector<char> letrasErradas; // Vector com as letras chutadas erradas.
    map<char,bool> chute; // Map com as letras e valores, ex.:(MELAO) <E,true> se o chute for a letra E. Caso contrário <E,false>.

    while(true) {
        cout << "Bem vindo ao Jogo Forca! Por favor escolha uma das opções" << endl;
        cout << "1 - Iniciar Jogo" << endl;
        cout << "2 - Ver scores anteriores" << endl;
        cout << "3 - Sair do Jogo" << endl;
        cout << "Sua escolha: ";
        cin >> opcao; // Ler opção do usuário.
        cout << endl;

        if(opcao == 1) {
            cout << "Vamos iniciar o jogo! Por favor escolha o nível de dificuldade" << endl;
            cout << "1 - Fácil" << endl;
            cout << "2 - Médio" << endl;
            cout << "3 - Difícil" << endl;
            cout << "Sua escolha: ";
            cin >> dificuldade; // Ler dificuldade escolhida.
            cout << endl;

            if (dificuldade == 1){ dif = 0; cout << "Iniciando o Jogo no nível fácil, será que você conhece essa palavra?" << endl;
            } else if (dificuldade == 2){ dif = 1; cout << "Iniciando o Jogo no nível médio, será que você conhece essa palavra?" << endl;
            } else if (dificuldade == 3){ dif = 2; cout << "Iniciando o Jogo no nível difícil, será que você conhece essa palavra?" << endl;}

            forca.set_dificuldade(dif);
            forca.separarPorDificuldade();

            // Selecionando uma palavra secreta aleatória pelas palavras filtradas por dificuldade.
            palavra_secreta = forca.sorteiaPalavra(forca.separarPorDificuldade());
        
            while(true) {
                while(true) { // Loop da rodada
                    cout << endl;
                    cout << "Chutes errados: "; // Imprime cada letra chutada errada.
                    for (char letra : letrasErradas) {
                        cout << letra << " ";
                    }
                    cout << endl;
                    // Imprime _ se a letra ainda não foi chutada.
                    for (char letra : palavra_secreta) {
                        if (chute[letra]){
                            cout << letra << " ";
                        } else {
                            cout << "_ ";
                        }  
                    }

                    cout << endl;
                    cout << "Print temporário para teste de palavra: " << palavra_secreta << endl;
                    cout << "Pontos: " << "TESTE" << endl;
                    cout << "Palpite: ";
                    cin >> palpite; // Ler o palpite.
                    palpite = toupper(palpite); // Transforma o caractere em maiúsculo para facilitar o restante do código.
                    chute[palpite] = true; // Marca true para qualquer letra chutada.
                    cout << "\n";

                    // Pegando as letras únicas da palavra secreta e armazenando na cópia.
                    for (int i = 0; i < (int)palavra_secreta.size(); i++) {
                        palavra_secretaCopia.push_back(palavra_secreta[i]);
                    }
                    sort(palavra_secretaCopia.begin(),palavra_secretaCopia.end());
                    palavra_secretaCopia.erase(unique(palavra_secretaCopia.begin(), palavra_secretaCopia.end()), palavra_secretaCopia.end());
    
                    // Verificando cada letra da cópia com o palpite e salvando na string 'palavra_sec' (removendo letras repetidas).
                    for (auto letra : palavra_secretaCopia) {
                        if (letra == palpite){
                            palavra_sec.push_back(letra);
                            palavra_sec.erase(unique(palavra_sec.begin(), palavra_sec.end()), palavra_sec.end());
                        }
                    }

                    // Verifica se a letra existe na palavra e imprime.
                    bool result = forca.letraExiste(palpite, palavra_secreta);

                    if (result) { //Se letra existir na palavra.
                        cout << "Muito bem! A palavra contém a letra "<< palpite << "!" << endl;
                        forca.imprimirBoneco(letrasErradas.size());
                        // VITÓRIA
                        /* Verifica de acordo com os palpites se a string 'palavra_sec' contém todas as letras da palavra secreta, ou seja,
                         se são do mesmo tamanho. */
                        if (palavra_sec.size() == palavra_secretaCopia.size()) {
                            cout << "Parabéns! Você conseguiu descobrir a palavra secreta: " + palavra_secreta + "." << endl;
                            exit(-1);
                        }
                        break;
                    } else { // Se letra não existir na palavra.
                        cout << "Meh, não achei a letra " << palpite << "! :<" << endl;
                        letrasErradas.push_back(palpite);
                        forca.imprimirBoneco(letrasErradas.size());
                        // GAME OVER
                        // Se número de letras erradas não repetidas se excederem, fim de jogo.
                        if (letrasErradas.size() == 6){
                            cout << endl;
                            cout << "Você enforcou o bonequinho :(" << endl;
                            exit(-1);
                        }
                        break;
                    }
                }
            }
            // Ler informações do jogador para o score e gravar no arquivo.
        }else if (opcao == 2) {
            forca.mostrar_scores();
        }else{
            break;
        }    
    }
    return 0;
}