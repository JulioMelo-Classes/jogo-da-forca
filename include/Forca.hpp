#include <vector> //<! Biblioteca para utilizar vectors.
#include <fstream> //<! Biblioteca para manipular de arquivos.
#include <string> //<! Biblioteca para tratar strings.
#include <iterator> //<! Biblioteca para utilizar iterators de vectors.
#include <algorithm> //<! Biblioteca para buscar, copiar, ordenar, etc.
#include <exception> //<! Biblioteca para exceções de erros padrões.
#include <map> //<! Biblioteca para criar mapas com chaves e valores correspondentes.
#include <random> //<! Biblioteca para gerar números aleatórios.
#include <sstream> //<! Biblioteca para fornecer classes de stream de string.

class Forca {
    public:
        enum Dificuldade{
            FACIL = 0, MEDIO = 1, DIFICIL = 2
        };

    private:

        int numero_de_letras; //<! Número de letras a serem reveladas.
        
        int m_tentativas_restantes; //TODO: armazenar tentativas restantes

        Dificuldade m_dificuldade = Dificuldade::FACIL; //<! dificuldade atual do jogo

        std::vector< std::pair<std::string, int> > m_palavras; //<! palavras e sua ocorrência no Corpus

        std::string m_arquivo_scores; //<! nome do arquivo contendo os scores
 
        std::string m_arquivo_palavras; //<! nome do arquivo contendo as palavras

        std::string m_palavra_atual; //<! palavra sendo jogada “atualmente”

        std::vector< int > m_frequencias; //<! frequências das palavras no Corpus
 
        std::vector< std::string > m_palavras_do_jogo; //<! container “Palavras do Jogo”

        std::vector< std::string > m_scores_do_jogo; //<! container “Scores do Jogo”

        std::map<char,bool> mapa_letra_valor; //<! Map com as letras e valores, ex.:(MELAO) <E,true> se o chute for a letra 'E'. Caso contrário <E,false>.

        std::vector< char > m_letras_palpitadas; //<! contem as letras palpitadas pelo jogador

        std::vector< char > m_letras_erradas; //<! contem as letras erradas pelo jogador

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
         * Ao validar os arquivos, no caso de arquivos inválidos, 
         * este método irá encerrar o programa e mostrar o tipo de erro juntamente da linha onde ele ocorreu.
         */
        std::pair<bool, std::string> eh_valido();
 
        /**
         * Carrega os arquivos de scores e palavras preenchendo as 
         * estrutura m_palavras, m_scores_do_jogo e calculando média das frequências.
         */
        void carregar_arquivos();

        /**
         * Modifica a dificuldade do jogo.
         * Este método modifica a dificuldade do jogo gerando um novo vetor palavras_do_jogo
         * toda vez que é chamado..
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
         * Função imprimir as letras erradas pelo jogador.
         */
        void imprimir_chutes_errados();

        /**
         * Imprime vogais ou consoantes reveladas no início do jogo, além disso,
         * imprime '-' se a palavra conter hífen e as demais letras exibe "_" na tela.
         * @param palavra_escolhida Palavra que o jogador esta tentando acertar.
         * @param consoante Consoantes da palavra.
         * @param vogal Vogais da palavra.
         * @param dificuldade Dificuldade do jogo.
         */
        void imprimir_underline(std::string palavra_escolhida, std::vector<char> consoante, char vogal, int dificuldade);

        /**
         * Função que imprime o bonequinho.
         * @param n_erros Recebe a quantidade de erros do jogador para imprimir o boneco de acordo.
         */
        void imprimir_boneco(int n_erros);

        /**
         * Cria e retorna um vetor com n consoantes sorteadas de acordo com a dificuldade escolhida e a condição da palavra sorteada.
         * @param palavra_escolhida Palavra secreta já sorteada.
         * @param dificuldade_escolhida Dificuldade escolhida pelo usuário.
         * @return std::vector<char> Vetor de consoantes da palavra sorteada.
         */
        std::vector<char> muda_valor_consoante_mapa(std::string palavra_escolhida, int dificuldade_escolhida);

        /**
         * Transforma o valor de cada chave do map em true ao ser chutada uma letra.
         * @param letra_escolhida Letra chutada pelo usuário.
         */
        void muda_valor_letra_mapa(char letra_escolhida);

        /**
         * Retorna uma letra (vogal) sorteada da palavra secreta ao escolher a dificuldade média.
         * @param palavra_escolhida Palavra secreta sorteada.
         * @return char Vogal da palavra sorteada.
         */
        char muda_valor_vogal_mapa(std::string palavra_escolhida);

        /**
         * Retorna um vetor com todas as letras únicas erradas pelo jogador, removendo repetidas.
         * @param palavra Palavra da rodada.
         * @param palpite Letra chutada pelo jogador.
         * @return std::vector<char> 
         */
        std::vector<char> vector_letra_errada(std::string palavra, char palpite);

        /**
         * Coloca no vetor m_letras_palpitadas todas as letras não repetidas chutadas pelo usuário.
         * Além disso, adiciona a m_letras_palpitadas a(s) consoante(s) ou a vogal sorteada da palavra. 
         * Essa função auxiliar o somador de pontos e acertos.
         * @param letra_escolhida Letra chutada pelo usuário.
         * @param consoante Consoante(s) sorteada(s) da palavra.
         * @param vogal Vogal sorteada da palavra.
         * @param resultado Retorna true se acertou alguma letra da palavra, false caso contrário.
         * @param acertos Adiciona 1 a cada letra existente na palavra não repetida ou já exposta.
         * @param pontos Adiciona (1*quantidade da letra chutada que existe na palavra), 
         * caso o chute for a última letra da palavra, adiciona (1*quantidade da letra chutada que existe na palavra)+2.
         */
        void get_letras(char letra_escolhida, std::vector<char> consoante, char vogal, bool resultado, int &acertos, int &pontos);

        /**
         * Verifica se para cada letra de m_letras_palpitadas está na palavra sorteada.
         * Se não estiver, é porque foi um chute errado, então salva a letra em m_letras_erradas.
         * @param letra_escolhida Chute do usuário.
         * @param palavra Palavra secreta.
         */
        void get_letras_erradas(char letra_escolhida, std::string palavra);

        /**
         * @return Tamanho do vetor m_letras_erradas.
         */
        int get_tam_letras_erradas();

        /**
         * Verifica se a letra chutada existe na palavra da rodada.
         * @param chute Letra chutada pelo jogador.
         * @param palavra Palavra da rodada.
         * @return False caso a letra chutada não esteja na palavra, true caso esteja;
         */
        bool letra_existe(char chute, std::string palavra);

        /**
         * Verifica quantas tentativas ainda restam pelo jogador.
         * @param palavra Palavra da rodada.
         * @param palpite Letra chutada pelo jogador.
         * @param tentativas Tentativas restantes do jogador.
         * @return True caso o jogador erre o chute.
         */
        bool verifica_tentativas(std::string palavra, char palpite, int tentativas);

        /**
         * Retorna true caso o jogador tenha descoberto todas as letras da palavra, VITÓRIA!
         */
        bool verifica_vitoria(char letra_escolhida, std::string palavra_atual, int acertos, int dificuldade);

        /**
         * Retorna false caso a quantidade de erros do jogador seja == 6, causando o encerramento da rodada.
         */
        bool verifica_derrota();

        /**
         * Mecânica de pontuação do jogador, altera sempre uma variável de pontos de acordo
         * com se o jogador acertou ou errou o chute.
         * @param palavra_secreta Palavra da rodada.
         * @param chute Chute de letra do jogador.
         * @param pontos Referência para a variável de pontos a ser modificada.
         * @param existe Bool para verificar se o jogador acertou a letra chutada.
         */
        void pontuacao_jogador(std::string palavra_secreta, char chute, int &pontos, bool existe);

        /**
         * Reseta o valor de tentativas restantes para 6 e do atributo m_letras_palpitadas para vazio
         * Este método é útil no caso do jogador escolher continuar o jogo, ou no início
         * de cada rodada, resetando o valor de todas as variáveis que foram utilizadas na rodada anterior.
         */
        void reset_rodada(int &t, int &a, std::vector<char> &c, char &v, std::string &pa, std::vector<char> &le);

        /**
         * Escreve no arquivo de scores as informações do jogador nos parâmetros.
         * @param jogada_informacoes String montada com a dificuldade e o nome do jogador.
         * @param palavras_acertadas Vetor contendo todas as palavras acertadas pelo jogador.
         * @param pontos Pontos do jogador.
         */
        void escrever_scores(std::string &jogada_informacoes, std::vector<std::string> &palavras_acertadas, int &pontos);

        /**
         * Lê o arquivo de scores dos jogadores anteriores e imprime as informações na tela de acordo
         * com as formatações estabelecidas.
         */
        void mostrar_scores();
};