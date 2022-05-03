#include "Forca.hpp"

#include <iostream>
using namespace std;

Forca::Forca(string palavras, string scores) {
    m_arquivo_palavras = palavras;
    m_arquivo_scores = scores;
};

void Forca::carregar_arquivos() {
    string linha_palavra, linha_frequencia, linha_scores;

    // fstream é a combinação de ofstream e ifstream, criando arquivo.
    fstream arquivos_palavras;
    fstream arquivos_scores;

    // Abrindo o arquvio das palavras.
    arquivos_palavras.open(m_arquivo_palavras, fstream::in);

    // EOF para quando não há mais arquivos a serem lidos.
    while (!arquivos_palavras.eof()) {
        getline(arquivos_palavras, linha_palavra, ';');  // ';' delimitador.
        m_palavras_do_jogo.push_back(linha_palavra);

        getline(arquivos_palavras, linha_frequencia, '\n');  // '\n' delimitador.
        m_frequencias.push_back(stoi(linha_frequencia));
    }
    // Fechando o arquivo das palavras.
    arquivos_palavras.close();

    // Abrindo o arquivo dos scores.
    arquivos_scores.open(m_arquivo_scores, fstream::in);

    // EOF para quando não há mais arquivos a serem lidos.
    while (!arquivos_scores.eof()) {
        getline(arquivos_scores, linha_scores);
        m_scores_do_jogo.push_back(linha_scores);
    }
    // Fechando o arquivo dos scores.
    arquivos_scores.close();

    vector<string>::iterator itp;  // Iterator das palavras.
    vector<int>::iterator itf;     // Iterator das frequências.

    for (itp = m_palavras_do_jogo.begin(), itf = m_frequencias.begin(); itp != m_palavras_do_jogo.end(), itf != m_frequencias.end(); ++itp, ++itf) {
        m_palavras.push_back(make_pair(*itp, *itf));  // Montando par <palavras,ocorrência no Corpus>.
    }

    for (itf = m_frequencias.begin(); itf != m_frequencias.end(); ++itf) {
        soma_frequencia = soma_frequencia + *itf;
    }
    media_frequencia = soma_frequencia / m_frequencias.size();  // Calculando média das frequências das palavras.
};

bool Forca::letra_existe(char chute, string palavra) {
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
        for (int i = 0; i < (int)m_palavras.size(); i++) {
            if (m_palavras[i].second > media_frequencia) {
                palavras_facil.push_back(m_palavras[i].first);
            }
        }
        for (int i = 0; i < 10; i++) {
            uniform_int_distribution<int> facil(0, palavras_facil.size() - 1);
            const int nrand1 = facil(dre);
            palavras_escolhidas.push_back(palavras_facil[nrand1]);
        }
        // MÉDIO
    } else if (m_dificuldade == 1) {
        for (int i = 0; i < (int)m_palavras.size(); i++) {
            if (m_palavras[i].second < media_frequencia) {
                palavras_mediaMenor.push_back(m_palavras[i].first);
            }
            if (m_palavras[i].second >= media_frequencia) {
                palavras_mediaMaior.push_back(m_palavras[i].first);
            }
        }
        for (int i = 0; i < 7; i++) {
            uniform_int_distribution<int> mediomenor(0, palavras_mediaMenor.size() - 1);
            const int nrand2 = mediomenor(dre);
            palavras_escolhidas.push_back(palavras_mediaMenor[nrand2]);
        }
        for (int i = 0; i < 13; i++) {
            uniform_int_distribution<int> mediomaior(0, palavras_mediaMaior.size() - 1);
            const int nrand3 = mediomaior(dre);
            palavras_escolhidas.push_back(palavras_mediaMaior[nrand3]);
        }
        // DIFÍCIL
    } else if (m_dificuldade == 2) {
        for (int i = 0; i < (int)m_palavras.size(); i++) {
            if (m_palavras[i].second < media_frequencia) {
                palavras_mediaMenor.push_back(m_palavras[i].first);
            }
            if (m_palavras[i].second >= media_frequencia) {
                palavras_mediaMaior.push_back(m_palavras[i].first);
            }
        }
        for (int i = 0; i < 22; i++) {
            uniform_int_distribution<int> mediomenor(0, palavras_mediaMenor.size() - 1);
            const int nrand4 = mediomenor(dre);
            palavras_escolhidas.push_back(palavras_mediaMenor[nrand4]);
        }
        for (int i = 0; i < 8; i++) {
            uniform_int_distribution<int> mediomaior(0, palavras_mediaMaior.size() - 1);
            const int nrand5 = mediomaior(dre);
            palavras_escolhidas.push_back(palavras_mediaMaior[nrand5]);
        }
    }
    return palavras_escolhidas;
}

string Forca::sorteia_palavra(vector<string> palavras) {
    random_device random;
    default_random_engine dre_(random());
    uniform_int_distribution<int> aleatorio(0, palavras.size() - 1);
    const int nrand = aleatorio(dre_);
    string stringSorteada;
    stringSorteada = (palavras[nrand]);
    return stringSorteada;
}

void Forca::set_dificuldade(int dificuldade_escolhida) {
    if (dificuldade_escolhida == 0) {
        m_dificuldade = FACIL;
    } else if (dificuldade_escolhida == 1) {
        m_dificuldade = MEDIO;
    } else if (dificuldade_escolhida == 2) {
        m_dificuldade = DIFICIL;
    }
}

void Forca::get_letras(char letra_escolhida, vector<char> consoante, char vogal, bool resultado, int &acertos, int &pontos) {
    if (m_letras_palpitadas.size() == 0) {
        for (int i = 0; i < (int)consoante.size(); i++) {
            m_letras_palpitadas.push_back(consoante[i]);
        }
        m_letras_palpitadas.push_back(vogal);
    }
    if (m_letras_palpitadas.size() != 0) {
        if (*find(m_letras_palpitadas.begin(), m_letras_palpitadas.end(), letra_escolhida) == letra_escolhida) {
            cout << "Você já chutou essa letra!" << endl;
        } else {
            int fix_loop = 0;
            if (resultado) {
                if (*find(m_palavra_atual.begin(), m_palavra_atual.end(), letra_escolhida) == letra_escolhida) {
                    for (char letra : m_palavra_atual) {
                        if (letra == letra_escolhida) {
                            pontos++;
                        }
                    }
                }
                if ((m_palavra_atual[m_palavra_atual.size() - 1] == letra_escolhida) && (fix_loop == 0)) {
                    fix_loop = 1;
                    pontos += 2;
                }
                acertos++;
            }
            m_letras_palpitadas.push_back(letra_escolhida);
        }
    }
    sort(m_letras_palpitadas.begin(), m_letras_palpitadas.end());
    m_letras_palpitadas.erase(unique(m_letras_palpitadas.begin(), m_letras_palpitadas.end()), m_letras_palpitadas.end());
}

void Forca::get_letras_erradas(char letra_escolhida, string palavra) {
    for (char letra : m_letras_palpitadas) {
        for (char letra_palavra : palavra) {
            if (letra != letra_palavra) {
                m_letras_erradas.push_back(letra_escolhida);
                sort(m_letras_erradas.begin(), m_letras_erradas.end());
                m_letras_erradas.erase(unique(m_letras_erradas.begin(), m_letras_erradas.end()), m_letras_erradas.end());
            }
        }
    }
}

int Forca::get_tam_letras_erradas() {
    return m_letras_erradas.size();
}

void Forca::muda_valor_letra_mapa(char letra_escolhida) {
    mapa_letra_valor[letra_escolhida] = true;  // Marca true para qualquer letra chutada.
}

vector<char> Forca::muda_valor_consoante_mapa(string palavra_escolhida, int dificuldade_escolhida) {
    random_device random;
    default_random_engine x(random());
    string palavra_escolhida_copia;
    int var2 = palavra_escolhida.size() / 5;
    int contador1 = 0;
    vector<int> consoantes;
    vector<char> letra_sorteada;

    for (int i = 0; i < (int)palavra_escolhida.size(); i++) {
        palavra_escolhida_copia.push_back(palavra_escolhida[i]);
    }
    palavra_escolhida_copia.erase(unique(palavra_escolhida_copia.begin(), palavra_escolhida_copia.end()), palavra_escolhida_copia.end());

    for (char letra : palavra_escolhida_copia) {
        if ((letra != ' ') && (letra != 'A') && (letra != 'E') && (letra != 'I') && (letra != 'O') && (letra != 'U')) {
            mapa_consoantes.push_back(make_pair(letra, contador1));
        }
        contador1++;
    }

    for (int i = 0; i < (int)mapa_consoantes.size(); i++) {
        mapa_consoantes[i].second = i;
    }

    if (m_dificuldade == 0) {
        int max1 = max(1, var2);
        numero_de_letras = max1;
        for (int j = 0; j < max1; j++) {
            uniform_int_distribution<int> aleatorio1(0, mapa_consoantes.size() - 1);
            const int n1 = aleatorio1(x);
            for (int i = 0; i < (int)mapa_consoantes.size(); i++) {
                if (n1 == mapa_consoantes[i].second) {
                    letra_sorteada.push_back(mapa_consoantes[i].first);
                }
            }
        }
    }
    return letra_sorteada;
}

char Forca::muda_valor_vogal_mapa(string palavra_escolhida) {
    random_device random1;
    default_random_engine z(random1());
    string palavra_escolhida_copia;
    int var3 = palavra_escolhida.size() / 5;
    int contador2 = 0;
    char letra_sorteada;

    for (int i = 0; i < (int)palavra_escolhida.size(); i++) {
        palavra_escolhida_copia.push_back(palavra_escolhida[i]);
    }
    palavra_escolhida_copia.erase(unique(palavra_escolhida_copia.begin(), palavra_escolhida_copia.end()), palavra_escolhida_copia.end());

    for (char letra : palavra_escolhida_copia) {
        if ((letra == 'A') || (letra == 'E') || (letra == 'I') || (letra == 'O') || (letra == 'U')) {
            mapa_vogais.push_back(make_pair(letra, contador2));
        }
        contador2++;
    }

    for (int i = 0; i < (int)mapa_vogais.size(); i++) {
        mapa_vogais[i].second = i;
    }
    if (m_dificuldade == 1) {
        int max2 = max(1, var3);
        numero_de_letras = max2;
        for (int j = 0; j < max2; j++) {
            uniform_int_distribution<int> aleatorio2(0, mapa_vogais.size() - 1);
            int n2 = aleatorio2(z);
            for (int i = 0; i < (int)mapa_vogais.size(); i++) {
                if (n2 == mapa_vogais[i].second) {
                    letra_sorteada = (mapa_vogais[i].first);
                    return letra_sorteada;
                }
            }
        }
    }
    return 0;
}

void Forca::pontuacao_jogador(std::string palavra_secreta, char chute, int &pontos, bool existe) {
    if (existe) {
    } else {
        if (m_letras_erradas.size() == 0) {
            pontos--;
        } else {
            if (*find(m_letras_erradas.begin(), m_letras_erradas.end(), chute) == chute) {
            } else {
                pontos--;
            }
        }
    }
}

string Forca::get_palavra_atual(string palavra) {
    m_palavra_atual = palavra;
    return m_palavra_atual;
}

bool Forca::verifica_vitoria(char letra_escolhida, string palavra_atual, int acertos, int dificuldade) {
    int espacos = 0;
    for (auto item : palavra_atual) {
        if (item == ' ') {
            espacos++;
        }
    }
    string palavra_secreta_copia;  // String contendo apenas as letras não repetidas da palavra secreta.
    // Pegando as letras únicas da palavra secreta e armazenando na cópia.
    for (int i = 0; i < (int)palavra_atual.size(); i++) {
        palavra_secreta_copia.push_back(palavra_atual[i]);
    }
    sort(palavra_secreta_copia.begin(), palavra_secreta_copia.end());
    palavra_secreta_copia.erase(unique(palavra_secreta_copia.begin(), palavra_secreta_copia.end()), palavra_secreta_copia.end());

    // Verifica de acordo com os palpites se a string 'palavra_sec' contém todas as letras da palavra secreta, ou seja, se são do mesmo tamanho.
    if (dificuldade == 0) {
        if (acertos + numero_de_letras - 1 == (int)palavra_secreta_copia.size() - espacos) {
            return true;
        } else {
            return false;
        }
    } else if (dificuldade == 1) {
        if (acertos == (int)palavra_secreta_copia.size() - espacos) {
            return true;
        } else {
            return false;
        }
    } else {
        if (acertos - 1 == (int)palavra_secreta_copia.size() - espacos) {
            return true;
        } else {
            return false;
        }
    }
}

bool Forca::verifica_derrota() {
    if (m_letras_erradas.size() == 6) {
        return true;
    } else {
        return false;
    }
}

bool Forca::verifica_tentativas(string palavra, char palpite, int tentativas) {
    for (int i = 0; i < (int)palavra.size(); i++) {
        if (m_letras_erradas.empty()) {
            return true;
        } else if (*find(m_letras_erradas.begin(), m_letras_erradas.end(), palpite) == palpite) {
            return false;
        } else {
            return true;
        }
    }
    return 0;
}

vector<char> Forca::vector_letra_errada(string palavra, char palpite) {
    vector<char> letras_erradas;
    if (m_letras_erradas.empty()) {
    } else {
        for (char letra : m_letras_erradas) {
            letras_erradas.push_back(letra);
        }
    }
    sort(letras_erradas.begin(), letras_erradas.end());
    letras_erradas.erase(unique(letras_erradas.begin(), letras_erradas.end()), letras_erradas.end());
    return letras_erradas;
}

void Forca::reset_rodada(int &t, int &a, vector<char> &c, char &v, string &pa, vector<char> &le) {
    t = 6;
    a = 1;
    c.clear();
    v = '\0';
    pa.clear();
    le.clear();
    m_dificuldade = FACIL;
    m_tentativas_restantes = 6;
    m_letras_palpitadas.clear();
    m_letras_erradas.clear();
    m_palavra_atual.clear();
    mapa_letra_valor.clear();
    mapa_letra_valor.clear();
    mapa_consoantes.clear();
    mapa_vogais.clear();
}

void Forca::escrever_scores(string &jogada_informacoes, vector<string> &palavras_acertadas, int &pontos) {
    fstream arquivo_scores;
    arquivo_scores.open(m_arquivo_scores, ios::app);
    if (palavras_acertadas.size() == 0) {
        palavras_acertadas.push_back("<nenhuma>.");
    }
    for (string palavra : palavras_acertadas) {
        jogada_informacoes = jogada_informacoes + palavra;
    }
    jogada_informacoes[jogada_informacoes.size() - 1] = ';';
    jogada_informacoes = jogada_informacoes + to_string(pontos);
    arquivo_scores << jogada_informacoes;
    arquivo_scores.close();
}