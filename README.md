# **Trabalho - Unidade 1 - LP1 - T01 (2022.1)**

## **Componentes:**
  * Danrley Lima
  * Lucas Morais

# **Jogo da Forca!**
  <img src="https://user-images.githubusercontent.com/71523376/166153527-165963f8-49c3-4fd4-a369-e4ba2f0f3ab7.png" width="60%" height="60%"/>

## **Documento de Especificação**
  Para melhor entendimento do objetivo do trabalho, acesse:
[Especificação do Trabalho 1](https://docs.google.com/document/d/1aa51VNLQ_jpZaEuGkMz2KE8feAkE48-TENZ9eqn48nk/edit?usp=sharing).

- ## **Linguagem de programação**
  * C++ </br>
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/cplusplus/cplusplus-original.svg" width="60" height="60"/>


- ## **Requisítos de compilação**
  * Cmake </br>
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/cmake/cmake-original.svg" width="60" height="60"/>

  * GCC/G++ </br>
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/gcc/gcc-original.svg" width="60" height="60"/>

***

- ## **Como criar e executar o arquivo .exe**
    * Abra o terminal na pasta dos arquivos e digite:
    * mkdir build
    * cd build
    * cmake ..
    * cmake --build .
    * ./program ../data/palavrasFormatadas.txt ../data/scores.txt
    * ↑ <strong> Repetir apenas o último comando caso já tenha executado os anteriores e queira iniciar o programa novamente </strong> ↑
***

  - ## **Validação dos arquivos (TESTES)**
    - <strong>Após ter criado a pasta build e usado o 'cmake --build .', digite os seguintes comandos de testes no terminal:</strong> </br>


  - ### <h2><em>Arquivo das PALAVRAS</em></h2>
    * ### Para testar o caso "Arquivo (palavras) Inexistente":
      ```
      ./program ../data/palavras_teste.txt ../data/scores.txt
      ```
      **Saída esperada:** < `Erro! Arquivo das palavras inexistente.` >

    * ### Para testar o caso "Palavras com caracteres que não estejam entre [a - z|A - Z], ‘ ‘(espaço em branco) ou hífen ‘-’":
      ```
      ./program ../data/arquivos_testes_palavras/palavras_caracteres_invalidos.txt ../data/scores.txt
      ```
      **Saída esperada:** < `Palavra "$OBR&" inválida na linha 3.` >

    * ### Para testar o caso "Palavras que não tenham sua frequência correspondente, ou a frequência não seja um número inteiro positivo":

      - <h3>Frequência vazia/inexistente:</h3>

        ```
        ./program ../data/arquivos_testes_palavras/palavras_frequencia_inexistente.txt ../data/scores.txt
        ```
        **Saída esperada:** < `A palavra "SISTEMA" na linha 25, não possui frequência.` >
      
      - <h3>Frequência negativa:</h3>

        ```
        ./program ../data/arquivos_testes_palavras/palavras_frequencia_negativa.txt ../data/scores.txt
        ```
        **Saída esperada:** < `A palavra "FORAM" na linha 4, não possui frequência positiva.` >
    
    * ### Para testar o caso "Palavras com tamanho menor ou igual a 4":
      ```
      ./program ../data/arquivos_testes_palavras/palavras_menores.txt ../data/scores.txt
      ```
      **Saída esperada:** < `Erro! A palavra TEM na linha 17 contém menos de 5 letras.` >
    
  - ### <h2><em>Arquivo dos SCORES</em></h2>
    * ### Para testar o caso "Arquivo (scores) Inexistente":
      ```
      ./program ../data/palavrasFormatadas.txt ../data/scores_teste.txt
      ```
      **Saída esperada:** < `Erro! Arquivo das scores inexistente.` >
    
    * ### Para testar o caso "Presença de mais ou menos que 3 “;” em alguma linha":

      - Mais de 3 ';':
        ```
        ./program ../data/palavrasFormatadas.txt ../data/arquivos_testes_scores/scores_mais_de.txt
        ```
        **Saída esperada:** < `Erro! Mais de 3 ';' na linha: 2` >

      - Menos de 3 ';':
        ```
        ./program ../data/palavrasFormatadas.txt ../data/arquivos_testes_scores/scores_menos_de.txt
        ```
        **Saída esperada:** < `Erro! Menos de 3 ';' na linha: 1` >
      
    * ### Para testar o caso "Qualquer um dos campos: "nível de dificuldade”, “nome”  ou “pontuação” vazios":
      ```
      ./program ../data/palavrasFormatadas.txt ../data/arquivos_testes_scores/scores_campo_vazio.txt
      ```
      **Saída esperada:** < `Algum campo vazio na linha: 4` >
