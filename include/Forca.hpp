#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <cstdlib>
#include <algorithm>
#include <iomanip>
#include <exception>
#include <map>
#include <random>

class Forca {
    public:
        enum Dificuldade{
            FACIL = 0, MEDIO = 1, DIFICIL = 2
        };

    private:

        std::vector< std::pair<std::string, int> > m_palavras; //<! palavras e sua ocorrência no Corpus

        std::string m_arquivo_scores; //<! nome do arquivo contendo os scores
 
        std::string m_arquivo_palavras; //<! nome do arquivo contendo as palavras

        std::vector< int > m_frequencias; //<! frequências das palavras no Corpus
 
        Dificuldade m_dificuldade = Dificuldade::FACIL; //<! dificuldade atual do jogo
 
        std::vector< std::string > m_palavras_do_jogo; //<! container “Palavras do Jogo”

        std::vector< std::string > m_scores_do_jogo; //<! container “Scores do Jogo”

        std::vector< char > m_letras_palpitadas; //<! contem as letras palpitadas pelo jogador

        std::vector< char > m_letras_erradas; //<! contem as letras erradas pelo jogador

        std::string m_palavra_atual; //<! palavra sendo jogada “atualmente”

        std::string m_palavra_jogada; //<! palavra sendo jogada “atualmente” no formato “_ _ _ ... _ “
        
        int m_tentativas_restantes; //TODO: armazenar tentativas restantes

        std::map<char,bool> mapa_letra_valor; //<! Map com as letras e valores, ex.:(MELAO) <E,true> se o chute for a letra 'E'. Caso contrário <E,false>.

        std::vector< std::pair< char, int> > mapa_consoantes; //<! Vector com as consoantes das palavras e seus valores.

        std::vector< std::pair< char, int> > mapa_vogais; //<! Vector com as vogais das palavras e seus valores.

        int numero_de_letras; //<! Número de letras a serem reveladas.

    public:

        int media_frequencia = 0; //! Media das frequências das palavras

        int soma_frequencia = 0; //! Soma de todas as frequências das palavras

        /**
         * Cria a um objeto Forca
         * O construtor pode ou não validar os arquivos de entrada, no entanto, mesmo com 
         * os arquivos inválidos o objeto deve ser construído. Para o caso de arquivos de palavras
         * ou scores inválidos, use o método eh_valido.
         * @param palavras o arquivo que contém as palavras
         * @param scores o nome do arquivo que contém os scores
         * @see eh_valido 
        */
        Forca(std::string palavras, std::string scores);
       
        /**
         * Valida os arquivos de entrada de acordo com as especificações.
         * Ao validar os arquivos, no caso de arquivos inválidos, este método irá encerrar o programa e mostrar o tipo de erro juntamente da linha onde ele ocorreu.
         */
        std::pair<bool, std::string> eh_valido();
 
        /**
         * Carrega os arquivos de scores e palavras preenchendo **ao menos** a estrutura m_palavras e calculando média das frequências
         */
        void carregar_arquivos();

        /**
         * Modifica a dificuldade do jogo.
         * Este método modifica a dificuldade do jogo gerando um novo vetor palavras_do_jogo
         * toda vez que é chamado.
         * @param dificuldade_escolhida a dificuldade desejada
         * @see proxima_palavra
         */
        void set_dificuldade(int dificuldade_escolhida); 

        /**
         * Faz a escolha das palavras de acordo com o nível de dificuldade * escolhido pelo jogador.
         */
        std::vector<std::string> separar_por_dificuldade();

        /**
         * Escolhendo uma palavra secreta de acordo com o nível de 
         * dificuldade
         */
        std::string sorteia_palavra(std::vector<std::string> palavras);

        /**
         * Selecionando uma palavra secreta aleatória pelas palavras filtradas por dificuldade.
         **/
        std::string get_palavra_atual(std::string palavra);

        /**
         * Função imprimir as letras erradas pelo jogador
         */
        void imprimir_chutes_errados();

        /**
         * Imprime os "_" na tela 
         * @param palavra_escolhida palavra que o jogador esta tentando acertar
         * @param consoante consoantes da palavra
         * @param vogal vogais da palavra
         * @param dificuldade dificuldade do jogo
         */
        void imprimir_underline(std::string palavra_escolhida, std::vector<char> consoante, char vogal, int dificuldade);

        /**
         * Função que imprime o bonequinho
         * @param n_erros recebe a quantidade de erros do jogador para imprimir o boneco de acordo.
         */
        void imprimir_boneco(int n_erros);

        std::vector<char> muda_valor_consoante_mapa(std::string palavra_escolhida, int dificuldade_escolhida);

        void muda_valor_letra_mapa(char letra_escolhida);

        char muda_valor_vogal_mapa(std::string palavra_escolhida, int dificuldade_escolhida);

        void consoante_aleatoria(int dificuldade_escolhida, std::string palavra_escolhida);

        /**
         * Verifica se a letra chutada existe na palavra da rodada.
         * @param chute letra chutada pelo jogador.
         * @param palavra palavra da rodada.
         * @return false caso a letra chutada não esteja na palavra, true caso esteja;
         */
        bool letra_existe(char chute, std::string palavra);

        /**
         * Verifica quantas tentativas ainda restam pelo jogador.
         * @param palavra palavra da rodada.
         * @param palpite letra chutada pelo jogador.
         * @param tentativas tentativas restantes do jogador.
         * @return True caso o jogador erre o chute.
         */
        bool verifica_tentativas(std::string palavra, char palpite, int tentativas);

        /**
         * Retorna um vetor com todas as letras únicas erradas pelo jogador, removendo repetidas.
         * @param palavra palavra da rodada.
         * @param palpite letra chutada pelo jogador.
         * @return std::vector<char> 
         */
        std::vector<char> vector_letra_errada(std::string palavra, char palpite);

        void get_letras(char letra_escolhida, std::vector<char> consoante, char vogal, bool resultado, int &acertos, int &pontos);

        void get_letra_erradas(char letra_escolhida, std::string palavra);

        int get_tam_letras_erradas();

        bool verifica_vitoria(char letra_escolhida, std::string palavra_atual, int acertos, int dificuldade);

        bool verifica_derrota();

        // Mecânica de pontuação do jogador, retorna sempre uma referência para a variável de pontos.
        void pontuacao_jogador(std::string palavra_secreta, char chute, int &pontos, bool existe);

        /**
         * Testa se uma letra pertence á palavra atual e se já foi jogada pelo jogador.
         * Este método testa se uma letra pertence à palavra atual, caso a letra pertença a palavra
         * e ainda não foi jogada o método retorna {T, T}, caso a letra não pertença à palavra o método retorna {F,T}; 
         * Caso a letra já tenha sido jogada o método retorna {T, F}, quando a letra pertence à palavra e {F, F}, quando
         * não pertence.
         * Este método deve atualizar os atributos m_tentativas, m_palavra_jogada e m_letras_palpitadas, para refletir
         * as situações citadas. No caso da letra já ter sido escolhida, o método não deve atualizar m_tentativas.
         * @param palpite uma letra, que deve ser testada se pertence à palavra.
         * @return {T,T} se o palpite pertence à palavra e é um palpite novo, {F,T} caso não pertença e é novo.
         *         {T,F} ou {F,F} no caso do palpite pertencer/não pertencer à palavra, mas não é novo.
         */
        std::pair<bool, bool> palpite(std::string palpite);
 
        /**
         * Em caso de Game Over ou do jogador ter acertado a palavra este método deve retornar T.
         * @return T caso o m_tentativas_restantes do jogo esteja igual a 0 ou se o usuário 
         *         acertou toda a palavra, F caso contrário.
         */
        bool rodada_terminada();

        void escrever_scores(std::string jogada_informacoes, std::vector<std::string> palavras_acertadas, int &pontos);
 
        /**
         * Reseta o valor de tentativas restantes para 6 e do atributo m_letras_palpitadas para vazio
         * Este método é útil no caso do jogador escolher continuar o jogo, ou no início
         * de cada rodada, resetando o valor de todas as variáveis que foram utilizadas na rodada anterior.
         */
        void reset_rodada(int &t, int &a, std::vector<char> &c, char &v, std::string &pa, std::vector<char> &le);

        /**
         * Lê o arquivo de scores dos jogadores anteriores e imprime as informações na tela .
         */
        void mostrar_scores();


        // Funções de teste para desenvolvimento.
        void mostrar_palavraSort();
        void mostrar_parDePalavras();
        void mostrar_palavras();
};
