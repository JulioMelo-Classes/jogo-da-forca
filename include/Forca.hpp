#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <exception>
#include <map>

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

        vector<string> dificuldade, jogador, palavras, pontos;
 
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
        Forca(std::string palavras, std::string scores) {
            m_arquivo_palavras = palavras;
            m_arquivo_scores = scores;
        };
       

        /**
         * Valida os arquivos de entrada de acordo com as especificações.
         * Ao validar os arquivos, no caso de arquivos inválidos, este método deve retornar a 
         * razão correspondente de acordo com as especificações.
         * @return {T,""} se os arquivos estiverem válidos, {F,"razão"} caso contrário.
         */
        std::pair<bool, std::string> eh_valido() {
            int count_l = 1, count_np = 0, contador1 = 0, linha_test = 0;
            string linha_1, linha_2, linha_3, linha_4, string, palavra_invalida, dif, name, pal, points;
            pair<bool, std::string> parTeste;
            ifstream arq_palavras;
            ifstream arq_scores;

            arq_palavras.open(m_arquivo_palavras);

            // Verifica se o arquivo de palavras existe.
            if (arq_palavras.is_open()){
                parTeste.first = true;
            }else{
                cout << "Erro! Arquivo das palavras inexistente." << endl;
                exit(-1);
            }

            // Verifica se os caracteres das palavras estão dentro do padrão apresentado.
            while(!arq_palavras.eof()) {
                getline(arq_palavras, linha_1, ' ');
                string = linha_1;
                getline(arq_palavras, linha_2, '\n');
                char palavra[string.length()];
                count_l++;
                for (int i = 0; i < (int)sizeof(palavra); i++) {
                    palavra[i] = string[i];
                    if ((palavra[i] >= 'a' && palavra[i] <= 'z') || (palavra[i] >= 'A' && palavra[i] <= 'Z') || (palavra[i] == '-')){
                        count_np++;
                        if (count_np == (int)sizeof(palavra)){
                            parTeste.first = true;
                        }
                    } else {
                        palavra_invalida = string;
                        cout << "Palavra \"" + palavra_invalida + "\" inválida na linha " + to_string(count_l) + "." << endl;
                        exit(-1);
                    }  
                }
                palavra_invalida = string;

                // Verifica se possui uma frequência ou uma frequência positiva.
                try{
                    if (stoi(linha_2) > 0 || linha_2.empty()){
                        parTeste.first = true;
                    }
                } catch(...) {
                    cout << "A palavra \"" + palavra_invalida + "\" na linha " + to_string(count_l-1) + ", não possui frequência." << endl;
                    exit(-1);
                }

                if (stoi(linha_2) < 0){
                    cout << "A palavra \"" + palavra_invalida + "\" na linha " + to_string(count_l-1) + ", não possui frequência positiva." << endl;
                    exit(-1);
                }

                // Verifica se existe palavras com menos de cinco letras.
                if ((int)linha_1.size() <= 4) {
                    cout << "Erro! A palavra " + palavra_invalida + " na linha " + to_string(count_l) + " contém menos de 5 letras." << endl;
                    exit(-1);
                } else {
                    parTeste.first = true;
                }
            }

            arq_palavras.close();
            arq_scores.open(m_arquivo_scores);

            // Verifica se o arquivo de scores existe.
            if (arq_scores.is_open()) {
                parTeste.first = true;
            } else {
                cout << "Erro! Arquivo das scores inexistente." << endl;
                exit(-1);
            }

            // Verifica se tem mais ou menos três ';' na linha do arquivo scores.
            while(!arq_scores.eof()) {
                linha_test++;
                getline(arq_scores, linha_3);
                for (int i = 0; i < (int)linha_3.size(); i++) {
                    if (linha_3[i] == ';') {
                        contador1++;
                    }
                }

                // Verificação da quantidade de ';'.
                if (contador1 > 3) {
                    cout << "Erro! Mais de 3 ';' na linha: " << linha_test << endl;
                    exit(-1);
                } else if (contador1 < 3) {
                    cout << "Erro! Menos de 3 ';' na linha: " << linha_test << endl;
                    exit(-1);
                }
                contador1 = 0;

                // Verificação de campos vazios, criando substrings a partir de um delimitador ';'.
                int start = 0;
                std::string del = ";";
                int end = linha_3.find(del);
                while (end != -1) {
                    start = end + del.size();
                    end = linha_3.find(del, start);
                    if (linha_3.substr(start, end - start).size() == 0) {
                        cout << "Algum campo vazio na linha: " << linha_test << endl;
                        exit(-1);
                    }
                }
                if (linha_3.substr(start, end - start).size() == 0) {
                    cout << "Algum campo vazio na linha: " << linha_test << endl;
                    exit(-1);
                }
            }
            arq_scores.close();

            return parTeste;
        }
 
        /**
         * Carrega os arquivos de scores e palavras preenchendo **ao menos** a estrutura m_palavras
         */
        void carregar_arquivos() {
            string linha_p, linha_s;
            // fstream é a combinação de ofstream e ifstream, criando arquivo.
            fstream arquivos_palavras;
            fstream arquivos_scores;
            arquivos_palavras.open(m_arquivo_palavras, fstream::in);
            arquivos_scores.open(m_arquivo_scores, fstream::in);
            // EOF para quando não há mais arquivos a serem lidos.

            while(!arquivos_palavras.eof()) {
                getline(arquivos_palavras, linha_p, ' '); // ' ' delimitador.
                m_palavras_do_jogo.push_back(linha_p);

                getline(arquivos_palavras, linha_p, '\n'); // '\n' delimitador.
                m_frequencias.push_back(stoi(linha_p));
            }

            // SEGUNDO CHECKPOINT
            while(!arquivos_scores.eof()) {
                getline(arquivos_scores, linha_s);
                m_scores_do_jogo.push_back(linha_s);
            }

            arquivos_palavras.close();
            arquivos_scores.close();
        };

        // Verificação do chute da letra, retorna true se o chute for correto.
        bool letraExiste(char chute, string &palavra){
            for (char letra : palavra) {
                if (toupper(chute) == letra) {
                    return true;
                }
            }
            return false;
        }
        
        // SEGUNDO CHECKPOINT
        void mostrar_scores() {
            fstream arquivos_scores;
            
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

        // Montando média da frequência para utilização nos filtros de palavras por dificuldade.
        void montar_media() {
            for (it_i = m_frequencias.begin(); it_i != m_frequencias.end(); ++it_i){
                soma_frequencia = soma_frequencia + *it_i;
            }  
            media_frequencia = soma_frequencia/m_frequencias.size();    
        };

        // Montando par de [Palavra; Frequência] para utilização em diversas funcionalidades.
        void montar_par(){
            vector<string>::iterator itp;
            vector<int>::iterator itf;
            for (itp = m_palavras_do_jogo.begin(), itf = m_frequencias.begin(); itp != m_palavras_do_jogo.end(), itf != m_frequencias.end(); ++itp, ++itf){
                m_palavras.push_back(make_pair(*itp, *itf));
            }
        }
        
        // Faz a escolha das palavras de acordo com o nível de dificuldade escolhido pelo jogador.
        vector<string> separarPorDificuldade() {
            unsigned seed = time(0); // Garantindo que a randomização seja um "seed" sempre diferente.
            int nrand;
            vector<string> palavras_facil, palavras_mediaMaior, palavras_mediaMenor, palavras_dificil, palavras_escolhidas;
            srand(seed);

            // FÁCIL
            if (m_dificuldade == 0) {
                for (int i = 0; i < (int)m_palavras.size(); i++) { 
                    // Fazendo a filtragem por números cuja frequência seja maior que a frequência média.
                    if (m_palavras[i].second > media_frequencia) { 
                        palavras_facil.push_back(m_palavras[i].first);
                    }
                }
                for (int i = 0; i < 10; i++) {
                    // Sorteando 10 palavras da filtragem acima para colocá-las a disposição do jogo pela dificuldade.
                    nrand = rand() % (int)palavras_facil.size();
                    palavras_escolhidas.push_back(palavras_facil[nrand]);
                }
            // MÉDIO
            } else if (m_dificuldade == 1) {
                for (int i = 0; i < (int)m_palavras.size(); i++) {
                    // Fazendo a filtragem por números cuja frequência seja menor que a frequência média.
                    if (m_palavras[i].second < media_frequencia){
                        palavras_mediaMenor.push_back(m_palavras[i].first);
                    }
                    // Fazendo a filtragem por números cuja frequência seja maior ou igual que a frequência média.
                    if (m_palavras[i].second >= media_frequencia) {
                        palavras_mediaMaior.push_back(m_palavras[i].first);
                    }
                }
                for (int i = 0; i < 7; i++) {
                    // Sorteando 7 palavras cuja frequência seja menor que a média para colocá-las a disposição do jogo pela dificuldade.
                    nrand = rand() % (int)palavras_mediaMenor.size();
                    palavras_escolhidas.push_back(palavras_mediaMenor[nrand]);
                }
                for (int i = 0; i < 13; i++) {
                    // Sorteando 13 palavras cuja frequência seja maior/igual que a média para colocá-las a disposição do jogo pela dificuldade.
                    nrand = rand() % (int)palavras_mediaMaior.size();
                    palavras_escolhidas.push_back(palavras_mediaMaior[nrand]);
                } 
            // DIFÍCIL
            } else if (m_dificuldade == 2) {
                for (int i = 0; i < (int)m_palavras.size(); i++) {
                    // Fazendo a filtragem por números cuja frequência seja menor que a frequência média.
                    if (m_palavras[i].second < media_frequencia) {
                        palavras_mediaMenor.push_back(m_palavras[i].first);
                    }
                    // Fazendo a filtragem por números cuja frequência seja maior ou igual que a frequência média.
                    if (m_palavras[i].second >= media_frequencia) {
                        palavras_mediaMaior.push_back(m_palavras[i].first);
                    }
                }
                for (int i = 0; i < 22; i++) {
                    // Sorteando 22 palavras cuja frequência seja menor que a média para colocá-las a disposição do jogo pela dificuldade.
                    nrand = rand() % (int)palavras_mediaMenor.size();
                    palavras_escolhidas.push_back(palavras_mediaMenor[nrand]);
                }
                for (int i = 0; i < 8; i++) {
                    // Sorteando 8 palavras cuja frequência seja maior/igual que a média para colocá-las a disposição do jogo pela dificuldade.
                    nrand = rand() % (int)palavras_mediaMaior.size();
                    palavras_escolhidas.push_back(palavras_mediaMaior[nrand]);
                }
            }
            return palavras_escolhidas;
        }

        // Representação da interface de um boneco que retrata os erros do jogador.
        void imprimirBoneco(int e) {
            switch (e) {
                case 1:
                    cout << "  o  " << endl;
                    break;
                case 2:
                    cout << "  o\n  |  ";
                    break;
                case 3:
                    cout << "  o\n /|  ";
                    break;
                case 4:
                    cout << "  o\n /|\\ ";
                    break;
                case 5:
                    cout << "  o\n /|\\ \n / ";
                    break;
                case 6: 
                    cout << "Vixe, Fim de Jogo!\n  o\n /|\\ \n / \\";
                default:
                    break;
            }
        }

        // Escolhendo uma palavra secreta de acordo com o nível de dificuldade
        string sorteiaPalavra(vector<string> palavras) {
            unsigned seed = time(0);
            int nrand;
            vector<string> stringSorteada;
            srand(seed);
            nrand = rand() % (int)palavras.size();
            stringSorteada.push_back(palavras[nrand]);
            return stringSorteada[0];
        }

        // Função para teste dos pares durante desenvolvimento.
        void mostrar_parDePalavras() {
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
        // Função para teste das palavras durante desenvolvimento.
        void mostrar_palavras() {
            for (it_p = m_palavras_do_jogo.begin(); it_p != m_palavras_do_jogo.end(); ++it_p){
                cout << *it_p << endl;
            }      
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
        
        //-----------------X--------------------//

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
        bool rodada_terminada(){
            return true;
        };
 
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
