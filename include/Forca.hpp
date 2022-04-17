#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <iterator>
#include <cstdlib>
#include <ctime>

using namespace std;
 
class Forca {
    public:
        enum Dificuldade{
            FACIL = 0, MEDIO = 1, DIFICIL = 2
        };
    private:
        //TODO: armazenar os scores?

        std::vector< std::pair<std::string, int> > m_palavras; //<! palavras e sua ocorrência no Corpus

        std::string m_arquivo_scores; //<! nome do arquivo contendo os scores
 
        std::string m_arquivo_palavras; //<! nome do arquivo contendo as palavras

        std::vector< int > m_frequencias;

        std::vector< std::string > p_facil;

        std::vector< std::string > p_medio;

        std::vector< std::string > p_dificil;
 
        Dificuldade m_dificuldade = Dificuldade::FACIL; //<! dificuldade atual do jogo
 
        std::vector< std::string > m_palavras_do_jogo; //<! container “Palavras do Jogo”

        std::vector< std::string > m_scores_do_jogo; //<! container “Scores do Jogo”

        std::vector< std::string >::iterator it_s;

        std::vector< int >::iterator it_i;

        std::vector< int >::iterator iti;

        std::vector< std::string >::iterator it_p;

        std::vector< char > m_letras_palpitadas; //<! contem as letras palpitadas pelo jogador

        std::string m_palavra_atual; //<! palavra sendo jogada “atualmente”

        std::string m_palavra_jogada; //<! palavra sendo jogada “atualmente” no formato “_ _ _ ... _ “
        
        int m_tentativas_restantes; //TODO: armazenar tentativas restantes

        int media_frequencia = 0;

        int soma_frequencia = 0;

   
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
            int pos, tam, count_l = 1, count_a = 0, string_mf;
            string linha, string, string_im, palavra_invalida, palavra_frequencia;
            pair<bool, std::string> parTeste;

            //Verifica se existe algo no arquivo .txt.
            for (auto &linha : m_palavras_do_jogo){
                if (linha.empty()){
                    parTeste.first = false; 
                    parTeste.second = "Erro! Arquivo das palavras vazio ou inexistente.";
                    break;
                }else{
                    parTeste.first = true;
                    break;
                }
            }

            //Verifica se existe algo no arquivo .txt.
            for (auto &linha : m_scores_do_jogo){
                if (linha.empty()){
                    parTeste.first = false; 
                    parTeste.second = "Erro! Arquivo dos scores vazio ou inexistente.";
                    break;     
                }else{
                    parTeste.first = true;
                    break;
                }
            }

            //Verifica se os caracteres das palavras estão dentro do padrão apresentado.
            for (auto &linha : m_palavras_do_jogo){
                string = linha;
                char palavra[string.length()];
                count_l++;
                for (int i = 0; i < (int)sizeof(palavra); i++) {
                    palavra[i] = string[i];
                    if ((palavra[i] >= 'a' && palavra[i] <= 'z') || (palavra[i] >= 'A' && palavra[i] <= 'Z') || (palavra[i] == '-')){
                        parTeste.first = true;
                    }else{
                        palavra_invalida = string[i];
                        parTeste.first = false; 
                        parTeste.second = "Palavra \"" + palavra_invalida + "\" inválida na linha " + to_string(count_l) + ".";
                        break;
                    }  
                }
            }

            //Verifica se existe palavras com menos de cinco letras.
            for (auto &linha : m_palavras_do_jogo){
                if (linha.size() <= 4){
                    parTeste.first = false; 
                    parTeste.second = "Erro! O arquivo contém alguma(s) palavra(s) com menos de 5 letras.";
                    break;
                }else{
                    parTeste.first = true; 
                }
            }
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

            while(!arquivos_palavras.eof()){
                getline(arquivos_palavras, linha_p, ' ');
                m_palavras_do_jogo.push_back(linha_p);

                getline(arquivos_palavras, linha_p, '\n');
                m_frequencias.push_back(stoi(linha_p));
            }
            
            while(!arquivos_scores.eof()){
                getline(arquivos_scores, linha_s);
                m_scores_do_jogo.push_back(linha_s);
            }

            arquivos_palavras.close();
            arquivos_scores.close();
        };
        
        void mostrar_scores(){
            fstream arquivos_scores;
            vector<string> dificuldade, jogador, palavras, pontos;
            vector<string>::iterator it_dificuldade, it_jogador, it_palavras, it_pontos;
            
            arquivos_scores.open(m_arquivo_scores, fstream::in);
            string linha_p, linha_s;
            int pos, tam;

            cout << "Dificuldade | Jogador    | Palavras     | Pontos" << endl;

            while(!arquivos_scores.eof()){
                getline(arquivos_scores, linha_s);
                pos = linha_s.find(";", 0);
                dificuldade.push_back(linha_s.substr(0, pos));
                tam = pos+1;
                pos = linha_s.find(";", pos+1);
                jogador.push_back(linha_s.substr(tam, pos-tam));
                tam = pos+1;
                pos = linha_s.find(";", pos+1);
                palavras.push_back(linha_s.substr(tam, pos-tam));
                tam = pos+1;
                pos = linha_s.find("\n", -1);
                pontos.push_back(linha_s.substr(tam, pos-tam));
            }
            int i = 0, j = 0;
            for (it_dificuldade = dificuldade.begin(), it_jogador = jogador.begin(), it_pontos = pontos.begin(); it_dificuldade != dificuldade.end(); ++it_dificuldade, ++it_jogador, ++it_pontos) {
                // cout << *it_dificuldade  << setw(9) << " | " << *it_jogador << setw(5); 
                cout << *it_dificuldade;
                for (j = 0; j < (13 - ((int)dificuldade[i].size())); j++) {
                    cout << " ";
                }
                cout << "| " << *it_jogador;
                for (j = 0; j < (11 - (int)jogador[i].size()); j++) {
                    cout << " ";
                }

                // j = 0;
                // if (j == 0) {
                //     cout << "| ";
                //     pos = palavras[j].find(',', 0);
                //     string primeira_palavra = palavras[a].substr(0, pos);
                //     cout << primeira_palavra;
                    
                //     for (k = 0; k < 13 - (primeira_palavra.size()); k++) {
                //         cout << ' ';
                //     }
                //     cout << "| " << it_pontos[i].substr(0, 2) << "\n";
                //     j++, a++;
                // }
                    // cout  <<"            |            |              |";
                
                cout << "\n" <<"------------+------------+--------------+--------" << endl;
                i++;
            }
        };   

        void montar_media(){
            for (it_i = m_frequencias.begin(); it_i != m_frequencias.end(); ++it_i){
                soma_frequencia = soma_frequencia + *it_i;
            }  
            media_frequencia = soma_frequencia/m_frequencias.size();    
        };

        void mostrar_palavras(){
            for (it_p = m_palavras_do_jogo.begin(); it_p != m_palavras_do_jogo.end(); ++it_p){
                cout << *it_p << endl;
            }      
        };
        
        void montar_par(){
            vector<string>::iterator itp;
            vector<int>::iterator itf;
            for (itp = m_palavras_do_jogo.begin(), itf = m_frequencias.begin(); itp != m_palavras_do_jogo.end(), itf != m_frequencias.end(); ++itp, ++itf){
                m_palavras.push_back(make_pair(*itp, *itf));
            }
        }
        
        vector<string> separarPorDificuldade(){
            unsigned seed = time(0);
            int nrand;
            vector<string> palavras_facil, palavras_mediaMaior, palavras_mediaMenor, palavras_escMenor, palavras_escMaior, palavras_dificil, palavras_escolhidas;
            vector<pair<string, int>>::iterator it_si;
            vector<string>::iterator it_pe;
            srand(seed);
            
            if (m_dificuldade == 0){
                for (int i = 0; i < (int)m_palavras.size(); i++){
                    if (m_palavras[i].second > media_frequencia){
                        palavras_facil.push_back(m_palavras[i].first);
                    }
                }
                for (int i = 0; i < 10; i++){
                    nrand = rand()%(int)palavras_facil.size();
                    palavras_escolhidas.push_back(palavras_facil[nrand]);
                }
            }else if(m_dificuldade == 1){
                for (int i = 0; i < (int)m_palavras.size(); i++){
                    if (m_palavras[i].second < media_frequencia){
                        palavras_mediaMenor.push_back(m_palavras[i].first);
                    }else if(m_palavras[i].second >= media_frequencia){
                        palavras_mediaMaior.push_back(m_palavras[i].first);
                    }
                }
                for (int i = 0; i < 7; i++){
                    nrand = rand()%(int)palavras_mediaMenor.size();
                    palavras_escMenor.push_back(palavras_mediaMenor[nrand]);
                    palavras_escolhidas.emplace_back(palavras_escMenor);
                }
                for (int i = 0; i < 13; i++){
                    nrand = rand()%(int)palavras_mediaMaior.size();
                    palavras_escMaior.push_back(palavras_mediaMaior[nrand]);
                    palavras_escolhidas.emplace_back(palavras_escMaior);
                }
            }else if(m_dificuldade == 2){

            }
            for (it_pe = palavras_escolhidas.begin(); it_pe != palavras_escolhidas.end(); ++it_pe){
                cout << *it_pe << endl;
            } 

            return palavras_escolhidas;
        }

        void mostrar_parDePalavras(){
            cout << "(";
            for (int i = 0; i < (int)m_palavras.size(); i++) {
                cout << "[" << m_palavras[i].first << "," << m_palavras[i].second << "], ";
                if (i == ((int)m_palavras.size()-2)) {
                    cout << "[" << m_palavras[i-1].first << "," << m_palavras[i-1].second << "]";
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
        void set_dificuldade(int d){
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
