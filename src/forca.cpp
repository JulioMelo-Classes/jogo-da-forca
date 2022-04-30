#include "Forca.hpp"
#include <iostream>
using namespace std;

Forca::Forca(string palavras, string scores) {
    m_arquivo_palavras = palavras;
    m_arquivo_scores = scores;
};

pair<bool, string> Forca::eh_valido() {
    int contador1 = 1, contador2 = 0, contador3 = 0, contador_n_palavras = 0;
    string linha_1, linha_2, linha_3, linha_4, parte1, palavra_invalida;
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

    //Verifica se os caracteres das palavras estão dentro do padrão apresentado.
    while(!arq_palavras.eof()) {
        getline(arq_palavras, linha_1, ';');
        parte1 = linha_1;
        getline(arq_palavras, linha_2, '\n');
        char palavra[parte1.length()];
        contador1++;
        for (int i = 0; i < (int)sizeof(palavra); i++) {
            palavra[i] = parte1[i];
            if ((palavra[i] >= 'a' && palavra[i] <= 'z') || (palavra[i] >= 'A' && palavra[i] <= 'Z') || (palavra[i] == ' ')){
                contador_n_palavras++;
                if (contador_n_palavras == (int)sizeof(palavra)){
                    parTeste.first = true;
                }
            } else {
                palavra_invalida = parte1;
                cout << "Palavra \"" + palavra_invalida + "\" inválida na linha " + to_string(contador1) + "." << endl;
                exit(-1);
            }  
        }
        palavra_invalida = parte1;

        //Verifica se possui uma frequência ou uma frequência positiva.
        try{
            if (stoi(linha_2) > 0 || linha_2.empty()){
                parTeste.first = true;
            }
        }catch(...){
            cout << "A palavra \"" + palavra_invalida + "\" na linha " + to_string(contador1-1) + ", não possui frequência." << endl;
            exit(-1);
        }

        if (stoi(linha_2) < 0){
            cout << "A palavra \"" + palavra_invalida + "\" na linha " + to_string(contador1-1) + ", não possui frequência positiva." << endl;
            exit(-1);
        }

        //Verifica se existe palavras com menos de cinco letras.
        if ((int)linha_1.size() <= 4) {
            cout << "Erro! A palavra " + palavra_invalida + " na linha " + to_string(contador1) + " contém menos de 5 letras." << endl;
            exit(-1);
        } else {
            parTeste.first = true;
        }
    }

    arq_palavras.close();
    arq_scores.open(m_arquivo_scores);

    // Verifica se o arquivo de scores existe.
    if (arq_scores.is_open()){
        parTeste.first = true;
    }else{
        cout << "Erro! Arquivo das scores inexistente." << endl;
        exit(-1);
    }

    //Verifica se tem mais ou menos três ';' na linha do arquivo scores.
    while(!arq_scores.eof()) {
        contador3++;
        getline(arq_scores, linha_3);
        for (int i = 0; i < (int)linha_3.size(); i++) {
            if (linha_3[i] == ';') {
                contador2++;
            }
        }
        int start = 0;
        int end = linha_3.find(';');

        // Verificação da quantidade de ';'.
        if(contador2 > 3) {
            cout << "Erro! Mais de 3 ';' na linha: " << contador3 << endl;
            exit(-1);
        } else if (contador2 < 3) {
            cout << "Erro! Menos de 3 ';' na linha: " << contador3 << endl;
            exit(-1);
        }
        contador2 = 0;

        // Verificação de campos vazios.
        while (end != -1) {
            start = end + 1;
            end = linha_3.find(';', start);
            if (linha_3.substr(start, end - start).size() == 0) {
                cout << "Algum campo vazio na linha: " << contador3 << endl;
                exit(-1);
            }
        }
        if (linha_3.substr(start, end - start).size() == 0) {
            cout << "Algum campo vazio na linha: " << contador3 << endl;
            exit(-1);
        }
    }
    arq_scores.close();

    return parTeste;
}

void Forca::carregar_arquivos() {
    string linha_palavra, linha_frequencia, linha_scores;

    // fstream é a combinação de ofstream e ifstream, criando arquivo.
    fstream arquivos_palavras;
    fstream arquivos_scores;

    // Abrindo o arquvio das palavras.
    arquivos_palavras.open(m_arquivo_palavras, fstream::in);

    // EOF para quando não há mais arquivos a serem lidos.
    while(!arquivos_palavras.eof()) {
        getline(arquivos_palavras, linha_palavra, ';'); // ';' delimitador.
        m_palavras_do_jogo.push_back(linha_palavra);

        getline(arquivos_palavras, linha_frequencia, '\n'); // '\n' delimitador.
        m_frequencias.push_back(stoi(linha_frequencia));
    }
    // Fechando o arquivo das palavras.
    arquivos_palavras.close();

    // Abrindo o arquivo dos scores.
    arquivos_scores.open(m_arquivo_scores, fstream::in);

    // EOF para quando não há mais arquivos a serem lidos.
    while(!arquivos_scores.eof()) {
        getline(arquivos_scores, linha_scores);
        m_scores_do_jogo.push_back(linha_scores);
    }
    // Fechando o arquivo dos scores.
    arquivos_scores.close();

    vector<string>::iterator itp; //Iterator das palavras.
    vector<int>::iterator itf; //Iterator das frequências.

    for (itp = m_palavras_do_jogo.begin(), itf = m_frequencias.begin(); itp != m_palavras_do_jogo.end(), itf != m_frequencias.end(); ++itp, ++itf){
        m_palavras.push_back(make_pair(*itp, *itf)); //Montando par <palavras,ocorrência no Corpus>.
    }

    for (itf = m_frequencias.begin(); itf != m_frequencias.end(); ++itf){
        soma_frequencia = soma_frequencia + *itf;
    }  
    media_frequencia = soma_frequencia/m_frequencias.size(); //Calculando média das frequências das palavras.

};

void Forca::mostrar_scores() {
    fstream arquivos_scores;
    vector<std::string> dificuldade, jogador, palavras, pontos;
    vector<string>::iterator it_dificuldade, it_jogador, it_palavras, it_pontos;

    arquivos_scores.open(m_arquivo_scores, fstream::in);
    string linha_p, linha_s;
    int pos, tam;

    cout << "Dificuldade | Jogador    | Palavras     | Pontos" << endl;

    while (!arquivos_scores.eof()) {
        getline(arquivos_scores, linha_s);
        pos = linha_s.find(";", 0);
        dificuldade.push_back(linha_s.substr(0, pos));
        tam = pos + 1;
        pos = linha_s.find(";", pos + 1);
        jogador.push_back(linha_s.substr(tam, pos - tam));
        tam = pos + 1;
        pos = linha_s.find(";", pos + 1);
        palavras.push_back(linha_s.substr(tam, pos - tam));
        tam = pos + 1;
        pos = linha_s.find("\n", -1);
        pontos.push_back(linha_s.substr(tam, pos - tam));
    }
    int i = 0, j = 0, fix = 0;

    for (it_dificuldade = dificuldade.begin(), it_jogador = jogador.begin(), it_pontos = pontos.begin(); it_dificuldade != dificuldade.end(); ++it_dificuldade, ++it_jogador, ++it_pontos) {
        cout << *it_dificuldade;
        for (j = 0; j < (12 - ((int)dificuldade[i].size())); j++) {
            cout << " ";
        }
        cout << "| " << *it_jogador;
        for (j = 0; j < (11 - (int)jogador[i].size()); j++) {
            cout << " ";
        }
        cout << "| ";

        // PALAVRAS
        char delim = ',';
        std::vector<string> result;
        std::stringstream ss(palavras[i]);
        std::string item;

        while (getline(ss, item, delim)) {
            result.push_back(item);
        }
        for (std::string palavra : result) {
            if (fix == 0) {
                cout << palavra;
                for (j = 0; j < (13 - (int)palavra.size()); j++) {
                    cout << " ";
                }
                cout << "| " << *it_pontos << endl;
                fix++;
            } else {
                cout << "            |            | ";
                cout << palavra;
                for (j = 0; j < (13 - (int)palavra.size()); j++) {
                    cout << " ";
                }
                cout << "| " << endl;
            }
        }

        cout << "------------+------------+--------------+--------" << endl;
        i++;
        fix = 0;
    }
};

bool Forca::letra_existe(char chute, string palavra){
    for (char letra : palavra) {
        if (toupper(chute) == letra) {
            return true;
        }
    }
    return false;
}

vector<string> Forca::separar_por_dificuldade() {
    random_device random;
    default_random_engine dre(random());
    vector<string> palavras_facil, palavras_mediaMaior, palavras_mediaMenor, palavras_dificil, palavras_escolhidas;

    // FÁCIL
    if (m_dificuldade == 0) {
        for (int i = 0; i < (int)m_palavras.size(); i++){
            if (m_palavras[i].second > media_frequencia){
                palavras_facil.push_back(m_palavras[i].first);
            }
        }
        for (int i = 0; i < 10; i++) {
            uniform_int_distribution<int> facil(0, palavras_facil.size()-1);
            const int nrand1 = facil(dre);
            palavras_escolhidas.push_back(palavras_facil[nrand1]);
        }
    // MÉDIO
    } else if (m_dificuldade == 1) {
        for (int i = 0; i < (int)m_palavras.size(); i++){
            if (m_palavras[i].second < media_frequencia){
                palavras_mediaMenor.push_back(m_palavras[i].first);
            }if(m_palavras[i].second >= media_frequencia){
                palavras_mediaMaior.push_back(m_palavras[i].first);
            }
        }
        for (int i = 0; i < 7; i++){
            uniform_int_distribution<int> mediomenor(0, palavras_mediaMenor.size()-1);
            const int nrand2 = mediomenor(dre);
            palavras_escolhidas.push_back(palavras_mediaMenor[nrand2]);
        }
        for (int i = 0; i < 13; i++){
            uniform_int_distribution<int> mediomaior(0, palavras_mediaMaior.size()-1);
            const int nrand3 = mediomaior(dre);
            palavras_escolhidas.push_back(palavras_mediaMaior[nrand3]);
        } 
    // DIFÍCIL
    } else if (m_dificuldade == 2) {
        for (int i = 0; i < (int)m_palavras.size(); i++){
            if (m_palavras[i].second < media_frequencia) {
                palavras_mediaMenor.push_back(m_palavras[i].first);
            }
            if (m_palavras[i].second >= media_frequencia) {
                palavras_mediaMaior.push_back(m_palavras[i].first);
            }
        }
        for (int i = 0; i < 22; i++) {
            uniform_int_distribution<int> mediomenor(0, palavras_mediaMenor.size()-1);
            const int nrand4 = mediomenor(dre);
            palavras_escolhidas.push_back(palavras_mediaMenor[nrand4]);
        }
        for (int i = 0; i < 8; i++) {
            uniform_int_distribution<int> mediomaior(0, palavras_mediaMaior.size()-1);
            const int nrand5 = mediomaior(dre);
            palavras_escolhidas.push_back(palavras_mediaMaior[nrand5]);
        }
    }
    return palavras_escolhidas;
}

string Forca::sorteia_palavra(vector<string> palavras) {
    random_device random;
    default_random_engine dre_(random());
    uniform_int_distribution<int> aleatorio(0, palavras.size()-1);
    const int nrand = aleatorio(dre_);
    cout << nrand << endl;
    string stringSorteada;
    stringSorteada = (palavras[nrand]);
    return stringSorteada;
}

void Forca::set_dificuldade(int dificuldade_escolhida){
    if (dificuldade_escolhida == 0){
        m_dificuldade = FACIL;
    }else if(dificuldade_escolhida == 1){
        m_dificuldade = MEDIO;
    }else if(dificuldade_escolhida == 2){
        m_dificuldade = DIFICIL;
    }
}

void Forca::get_letras(char letra_escolhida, char consoante, char vogal, bool resultado, int &acertos, int &pontos){
    cout << m_palavra_atual << endl;
    if (m_letras_palpitadas.size() == 0){
        m_letras_palpitadas.push_back(consoante);
        m_letras_palpitadas.push_back(vogal);
    } 
    if (m_letras_palpitadas.size() > 1) {
        if (*find(m_letras_palpitadas.begin(), m_letras_palpitadas.end(), letra_escolhida) == letra_escolhida) {
            cout << "Você já chutou essa letra!" << endl;
        } else {
            int fix_loop = 0;
            if (resultado){
                if (*find(m_palavra_atual.begin(), m_palavra_atual.end(), letra_escolhida) == letra_escolhida) {
                    for (char letra : m_palavra_atual) {
                        if (letra == letra_escolhida) {
                            pontos++;
                        }
                    }
                } 
                if ((m_palavra_atual[m_palavra_atual.size()-1] == letra_escolhida) && (fix_loop == 0)) {
                    fix_loop = 1;
                    pontos+= 2;
                }
                cout << "Teste acertos: " << acertos << endl;
                acertos++;
            }
            m_letras_palpitadas.push_back(letra_escolhida);
        }
    }
    sort(m_letras_palpitadas.begin(),m_letras_palpitadas.end());
    m_letras_palpitadas.erase(unique(m_letras_palpitadas.begin(), m_letras_palpitadas.end()), m_letras_palpitadas.end());
}

void Forca::get_letra_erradas(char letra_escolhida, string palavra){
    for (char letra : m_letras_palpitadas) {
        for (char letra_palavra : palavra) {
            if (letra != letra_palavra) {
                m_letras_erradas.push_back(letra_escolhida);
                sort(m_letras_erradas.begin(),m_letras_erradas.end());
                m_letras_erradas.erase(unique(m_letras_erradas.begin(), m_letras_erradas.end()), m_letras_erradas.end());
            }
        }
    }
}

int Forca::get_tam_letras_erradas(){
    return m_letras_erradas.size();
}

void Forca::muda_valor_letra_mapa(char letra_escolhida){
    mapa_letra_valor[letra_escolhida] = true; //Marca true para qualquer letra chutada.
}

char Forca::muda_valor_consoante_mapa(string palavra_escolhida, int dificuldade_escolhida){
    random_device random;
    default_random_engine x(random());
    string palavra_escolhida_copia;
    int var2 = palavra_escolhida.size()/5;
    int contador1 = 0;
    vector<int> consoantes;

    for (int i = 0; i < (int)palavra_escolhida.size(); i++) {
        palavra_escolhida_copia.push_back(palavra_escolhida[i]);
    }
    sort(palavra_escolhida_copia.begin(),palavra_escolhida_copia.end());
    palavra_escolhida_copia.erase(unique(palavra_escolhida_copia.begin(), palavra_escolhida_copia.end()), palavra_escolhida_copia.end());

    for (char letra : palavra_escolhida_copia){
        contador1++;
        if ((letra != 'A') && (letra != 'E') && (letra != 'I') && (letra != 'O') && (letra != 'U')){
            mapa_consoantes.push_back(make_pair(letra,contador1));
        }
    }
    for (int i = 0; i < (int)mapa_consoantes.size(); i++){
        consoantes.push_back(mapa_consoantes[i].second);
    }
    
    if (m_dificuldade == 0){
        int max1 = max(1, var2);
        uniform_int_distribution<int> aleatorio1(0, max1);
        const int nrand1 = aleatorio1(x);
        for (int i = 0; i < (int)mapa_consoantes.size(); i++){
            if (consoantes[nrand1] == mapa_consoantes[i].second){
                return mapa_consoantes[i].first;
            }
        }
    }
    return 0;
}

char Forca::muda_valor_vogal_mapa(string palavra_escolhida, int dificuldade_escolhida){
    random_device random;
    default_random_engine x(random());
    string palavra_escolhida_copia;
    int var2 = palavra_escolhida.size()/5;
    int contador2 = 0;
    vector<int> vogais;

    for (int i = 0; i < (int)palavra_escolhida.size(); i++) {
        palavra_escolhida_copia.push_back(palavra_escolhida[i]);
    }
    sort(palavra_escolhida_copia.begin(),palavra_escolhida_copia.end());
    palavra_escolhida_copia.erase(unique(palavra_escolhida_copia.begin(), palavra_escolhida_copia.end()), palavra_escolhida_copia.end());
    for (char letra : palavra_escolhida_copia){
        contador2++;
        if ((letra == 'A') || (letra == 'E') || (letra == 'I') || (letra == 'O') || (letra == 'U')){
            mapa_vogais.push_back(make_pair(letra,contador2));
        }
    }
    for (int i = 0; i < (int)mapa_vogais.size(); i++){
        vogais.push_back(mapa_vogais[i].second);
    }
    
    if (m_dificuldade == 1){
        int max2 = max(1, var2);
        uniform_int_distribution<int> aleatorio2(0, max2);
        const int nrand2 = aleatorio2(x);
        for (int i = 0; i < (int)mapa_vogais.size(); i++){
            if (vogais[nrand2] == mapa_vogais[i].second){
                return mapa_vogais[i].first;
            }
        }
    }
    return 0;
}

void Forca::imprimir_boneco(int n_erros) {
    switch (n_erros) {
        case 0: cout << endl; cout << endl; cout << endl; break;
        case 1: cout << "  o  \n" << endl; cout << endl; break;
        case 2: cout << "  o\n  |  \n"; cout << endl; break;
        case 3: cout << "  o\n /|  \n"; cout << endl; break;
        case 4: cout << "  o\n /|\\ \n"; cout << endl; break;
        case 5: cout << "  o\n /|\\ \n / \n"; break;
        case 6: cout << "Vixe, Fim de Jogo!\n  o\n /|\\ \n / \\";
        default: break;
    }
}

void Forca::imprimir_chutes_errados(){
    cout << "Chutes errados --> "; //Imprime cada letra chutada errada.
    for (char letra : m_letras_erradas){
        cout << letra << " ";
    }
}

void Forca::pontuacao_jogador(std::string palavra_secreta, char chute, int &pontos, bool existe) {
    if (existe) {

    } else {
        if (m_letras_erradas.size() == 0){
            pontos--;
        } else {
            if (*find(m_letras_erradas.begin(), m_letras_erradas.end(), chute) == chute){

            } else {
                pontos--;
            }
        }
    }
}

// Selecionando uma palavra secreta aleatória pelas palavras filtradas por dificuldade.
string Forca::get_palavra_atual(){
    string palavra_secreta = sorteia_palavra(separar_por_dificuldade());
    m_palavra_atual = palavra_secreta;
    return palavra_secreta;
}

bool Forca::verifica_vitoria(char letra_escolhida, string palavra_atual, int acertos, int dificuldade){
    string palavra_secreta_copia; //String contendo apenas as letras não repetidas da palavra secreta.

    //Pegando as letras únicas da palavra secreta e armazenando na cópia.
    for (int i = 0; i < (int)palavra_atual.size(); i++) {
        palavra_secreta_copia.push_back(palavra_atual[i]);
    }
    sort(palavra_secreta_copia.begin(),palavra_secreta_copia.end());
    palavra_secreta_copia.erase(unique(palavra_secreta_copia.begin(), palavra_secreta_copia.end()), palavra_secreta_copia.end());

    //Verifica de acordo com os palpites se a string 'palavra_sec' contém todas as letras da palavra secreta, ou seja, se são do mesmo tamanho.
    cout << (int)palavra_secreta_copia.size() << endl;
    if (dificuldade == 0 || dificuldade == 1){
        if (acertos == (int)palavra_secreta_copia.size()){
            return true;
        }else{
            return false;
        }
    }else{
        if (acertos-1 == (int)palavra_secreta_copia.size()){
            return true;
        }else{
            return false;
        }
    }
}

bool Forca::verifica_derrota(){
    if (m_letras_erradas.size() == 6){
        return true;
    }else{
        return false;
    }
}

bool Forca::verifica_tentativas(string palavra, char palpite, int tentativas){
    for (int i = 0; i < (int)palavra.size(); i++){
        if (m_letras_erradas.empty()){
            return true;
        }else if (*find(m_letras_erradas.begin(), m_letras_erradas.end(), palpite) == palpite){
            return false;
        }else{
            return true;
        }  
    }
    return 0;
}

vector<char> Forca::vector_letra_errada(string palavra, char palpite){
    vector<char> letras_erradas;
    if (m_letras_erradas.empty()) {
        
    } else {
        for (char letra : m_letras_erradas){
            letras_erradas.push_back(letra);
        }
    }
    sort(letras_erradas.begin(),letras_erradas.end());
    letras_erradas.erase(unique(letras_erradas.begin(), letras_erradas.end()), letras_erradas.end());
    return letras_erradas;
}

void Forca::imprimir_underline(string palavra_escolhida, char consoante, char vogal){
    for (char letra : palavra_escolhida){
        if (mapa_letra_valor[letra]){
            cout << letra << " ";
        }else if (letra == ' '){
            cout << "- ";
        }else if (letra == consoante){
            cout << letra << " ";
        }else if (letra == vogal){
            cout << letra << " ";
        }else{
            cout << "_ ";
        }  
    }
}

void Forca::reset_rodada(int &p, int &t, int &a, char &c, char &v, string &pa, vector<char> &le){
    p = 0;
    t = 6;
    a = 1;
    c = '\0';
    v = '\0';
    pa.clear();
    le.clear();
    m_letras_palpitadas.clear();
    m_letras_erradas.clear();
    m_palavra_atual.clear();
    mapa_letra_valor.clear();
    mapa_consoantes.clear();
    mapa_vogais.clear();
}

bool Forca::rodada_terminada(){
    if (true){
        return true;
    }
}

/**
 * ---- FUNÇÕES ----
 * ------ DE -------
 * ---- TESTES -----
 * 
 */

void Forca::mostrar_palavraSort() {
    vector<string>::iterator it_ps;
    /*for (it_ps = stringSorteada.begin(); it_ps != stringSorteada.end(); ++it_ps){
        cout << *it_ps << endl;
    } */
}

void Forca::mostrar_parDePalavras() {
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

void Forca::mostrar_palavras() {
    std::vector< std::string >::iterator it_p;
    for (it_p = m_palavras_do_jogo.begin(); it_p != m_palavras_do_jogo.end(); ++it_p){
        cout << *it_p << endl;
    }      
};