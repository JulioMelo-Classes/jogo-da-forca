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

        std::string m_palavra_atual; //<! palavra sendo jogada “atualmente”

        std::string m_palavra_jogada; //<! palavra sendo jogada “atualmente” no formato “_ _ _ ... _ “
        
        int m_tentativas_restantes; //TODO: armazenar tentativas restantes

        std::map<char,bool> mapa_letra_valor; //<! Map com as letras e valores, ex.:(MELAO) <E,true> se o chute for a letra 'E'. Caso contrário <E,false>.

        std::vector< std::pair< char, int> > mapa_consoantes; //<! Vector com as consoantes das palavras e seus valores.

        std::vector< std::pair< char, int> > mapa_vogais; //<! Vector com as vogais das palavras e seus valores.

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
         * Retorna o valor da palavra atual, útil no caso de um game over, para mostrar a palavra que estava
         * sendo jogada
         * @return o valor do atributo palavra_atual
         **/
        std::string get_palavra_atual();

        void imprimir_chutes_errados();

        void imprimir_underline(std::string palavra_escolhida, char consoante, char vogal);

        void muda_valor_letra_mapa(char letra_escolhida);

        char muda_valor_consoante_mapa(std::string palavra_escolhida, int dificuldade_escolhida);

        char muda_valor_vogal_mapa(std::string palavra_escolhida, int dificuldade_escolhida);

        void consoante_aleatoria(int dificuldade_escolhida, std::string palavra_escolhida);

        bool letra_existe(char chute, std::string palavra);

        void imprimir_boneco(int n_erros);

        /**
         * Retorna a próxima palavra de acordo com a dificuldade atual.
         * Este método deve atualizar o valor dos atributos m_palavra_atual, com a palavra atual,
         * do atributo m_palavra_jogada com um texto no formato "_ _ _ _ ... _".
         * O método também deve sortear as letras que devem aparecer dependendo do nível de dificuldade,
         * alterando o valor de m_palavra_jogada de acordo.
         * @return o valor do atributo m_palavra_jogada.
         */
        std::string proxima_palavra();
 
        /**
         * Retorna a palavra atual que está sendo jogada.
         * Diferente do método proxima_palavra(), este método __não atualiza__ o atributo
         * m_palavra_atual, apenas retorna o atributo m_palavra_jogada que é a palavra no
         * formato  "_ _ _ _ ... _" contendo todas as letras
         * já acertadas/sorteadas ao invés de “_”.
         * @return a palavra atualmente sendo jogada.
         */
        std::string get_palavra_jogada();

        void get_letras_erradas(char letra_escolhida);

        int get_tam_letras_erradas();

        bool verifica_vitoria(char letra_escolhida, std::string palavra_atual, int acertos);

        bool verifica_derrota(char letra_escolhida);

        // Mecânica de pontuação do jogador
        int pontuacao_jogador(std::string palavra_secreta, char chute, int &pontos, bool existe);

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
 
        /**
         * Reseta o valor de tentativas restantes para 5 e do atributo m_letras_palpitadas para vazio
         * Este método é útil no caso do jogador escolher continuar o jogo, ou no início
         * de cada rodada, resetando o valor de tentativas restantes para 5 e do atributo
         * m_letras_palpitadas como sendo um vetor vazio
         */
        void reset_rodada();

        /**
         * Testes
         */

        void mostrar_palavraSort();
        void mostrar_parDePalavras();
        void mostrar_palavras();

        /**
         * Exibe tabela dos scores anteriores.
         */
        void mostrar_scores();
};
