#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;
 
class Forca {
    public:
        enum Dificuldade{
            FACIL, MEDIO, DIFICIL
        };
    private:
        //TODO: armazenar os scores?

        std::vector< std::pair<std::string, std::string> > m_palavras; //<! palavras e sua ocorrência no Corpus

        std::string m_arquivo_scores; //<! nome do arquivo contendo os scores
 
        std::string m_arquivo_palavras; //<! nome do arquivo contendo as palavras

        std::vector< std::string > m_frequencias;
 
        Dificuldade m_dificuldade = Dificuldade::FACIL; //<! dificuldade atual do jogo
 
        std::vector< std::string > m_palavras_do_jogo; //<! container “Palavras do Jogo”

        std::vector< std::string > m_scores_do_jogo; //<! container “Scores do Jogo”

        std::vector< std::string >::iterator it_s;

        std::vector< std::string >::iterator it_i;

        std::vector< std::string >::iterator it_p;

        std::vector< char > m_letras_palpitadas; //<! contem as letras palpitadas pelo jogador

        std::string m_palavra_atual; //<! palavra sendo jogada “atualmente”

        std::string m_palavra_jogada; //<! palavra sendo jogada “atualmente” no formato “_ _ _ ... _ “
        
        int m_tentativas_restantes; //TODO: armazenar tentativas restantes

   
    public:
        /**
         * Cria a um objeto Forca
         * O construtor pode ou não validar os arquivos de entrada, no entanto, mesmo com 
         * os arquivos inválidos o objeto deve ser construído. Para o caso de arquivos de palavras
         * ou scores inválidos, use o método eh_valido.
         * @param palavras o arquivo que contém as palavras
         * @param scores o nome do arquivo que contém os scores
         * @see eh_valido
         */
        Forca( std::string palavras, std::string scores ){
            m_arquivo_palavras = palavras;
            m_arquivo_scores = scores;
        };
       
        /**
         * Valida os arquivos de entrada de acordo com as especificações.
         * Ao validar os arquivos, no caso de arquivos inválidos, este método deve retornar a 
         * razão correspondente de acordo com as especificações.
         * @return {T,""} se os arquivos estiverem válidos, {F,"razão"} caso contrário.
         */
        std::pair<bool, std::string> eh_valido(){
            bool existe_arqP, existe_arqS, tam_arqP;
            int count = 0;
            string file;
            pair<bool, std::string> parTeste;
            fstream arquivos_palavras;
            fstream arquivos_scores;
            arquivos_palavras.open(m_arquivo_palavras, fstream::in);
            arquivos_scores.open(m_arquivo_scores, fstream::in);

            while(!arquivos_palavras.eof()){
                getline(arquivos_palavras, file);
                if (file.size() <= 4){
                    tam_arqP = false;
                }else{
                    tam_arqP = true; 
                }
                if (file.empty()){
                    existe_arqP = false;
                    break;
                }else{
                    existe_arqP = true;
                    break;
                }
            }

            while(!arquivos_scores.eof()){
                getline(arquivos_scores, file);
                if (file.empty()){
                    existe_arqS = false;
                    break;
                }else {
                    existe_arqS = true;
                    break;
                }
            }

            

            while(true){
                if (existe_arqP == true){
                    count++;
                }else{
                    parTeste.first = false; 
                    parTeste.second = "Erro! Não existe arquivo .txt (palavras).";
                    break;
                }
                if (existe_arqS == true){
                    count++;
                }else{
                    parTeste.first = false;
                    parTeste.second = "Erro! Não existe arquivo .txt (scores).";
                    break;
                }
                if (tam_arqP == true){
                    count++;
                }else{
                    parTeste.first = false; 
                    parTeste.second = "Erro! O arquivo contém alguma(s) palavra(s) com menos de 5 letras.";
                    break;
                }
                if (count == 3){
                    parTeste.first = true;
                    parTeste.second = "";
                    break;
                }
            }
            arquivos_palavras.close();
            arquivos_scores.close();
            return parTeste;
        }
 
        /**
         * Carrega os arquivos de scores e palavras preenchendo **ao menos** a estrutura m_palavras
         */
        void carregar_arquivos(){
            string linha_p, linha_s;
            fstream arquivos_palavras;
            fstream arquivos_scores;
            arquivos_palavras.open(m_arquivo_palavras, fstream::in);
            arquivos_scores.open(m_arquivo_scores, fstream::in);
            int pos, tam, fim;
            while(!arquivos_palavras.eof()){
                getline(arquivos_palavras, linha_p);
                pos = linha_p.find(" ", 0);
                m_palavras_do_jogo.push_back(linha_p.substr(0, pos));
                tam = pos+1;
                pos = linha_p.find(";", pos+1);
                m_frequencias.push_back(linha_p.substr(tam, pos-tam));
            }   

            while(!arquivos_scores.eof()){
                getline(arquivos_scores, linha_s);
                m_scores_do_jogo.push_back(linha_s);
            }

            arquivos_palavras.close();
            arquivos_scores.close();
        };
        

        void mostrar_scores(){
            for (it_s = m_scores_do_jogo.begin(); it_s != m_scores_do_jogo.end(); ++it_s){
                cout << *it_s << endl;
            }      
        };

        void mostrar_frequencias(){
            for (it_i = m_frequencias.begin(); it_i != m_frequencias.end(); ++it_i){
                cout << *it_i << endl;
            }      
        };

        void mostrar_palavras(){
            for (it_p = m_palavras_do_jogo.begin(); it_p != m_palavras_do_jogo.end(); ++it_p){
                cout << *it_p << endl;
            }      
        };
        
        void montarPar(){
            vector<string>::iterator itp;
            vector<string>::iterator itf;
            for (itp = m_palavras_do_jogo.begin(), itf = m_frequencias.begin(); itp != m_palavras_do_jogo.end(), itf != m_frequencias.end(); ++itp, ++itf){
                m_palavras.push_back(make_pair(*itp, *itf));
            }
        }


        void mostrar_parDePalavras(){
        cout << "(";
            for (int i = 0; i < m_palavras.size(); i++) {
                cout << "[" << m_palavras[i].first << ", " << m_palavras[i].second << "], ";
                if (i == (m_palavras.size()-2)) {
                    cout << "[" << m_palavras[i+1].first << ", " << m_palavras[i+1].second << "]";
                    break;
                }
            }
        cout << ")" << endl;
        };
 
        /**
         * Modifica a dificuldade do jogo.
         * Este método modifica a dificuldade do jogo gerando um novo vetor palavras_do_jogo
         * toda vez que é chamado.
         * @param d a dificuldade desejada
         * @see proxima_palavra
         */
        void set_dificuldade(Dificuldade d){
            if (d == 0){
                m_dificuldade = FACIL;
            }else if(d == 1){
                m_dificuldade = MEDIO;
            }else if(d == 2){
                m_dificuldade = DIFICIL;
            }
        };
 
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

        /**
         * Retorna o valor da palavra atual, útil no caso de um game over, para mostrar a palavra que estava
         * sendo jogada
         * @return o valor do atributo palavra_atual
         **/
        std::string get_palavra_atual();
 
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
         * Retorna a quantidade de tentativas restantes.
         * @return a quantidade de tentativas restantes.
         */
        int get_tentativas_restantes();

};
