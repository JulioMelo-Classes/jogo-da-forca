# **Trabalho - Unidade 1 - LP1 - T01 (2022.1)**

## **Componentes:**
  * Danrley Lima
  * Lucas Morais

# **Jogo da Forca!**
  <img src="https://user-images.githubusercontent.com/71523376/166153527-165963f8-49c3-4fd4-a369-e4ba2f0f3ab7.png" width="60%" height="60%"/>
  
## **Banco de palavras**
  O banco de palavras original recebe todas as palavras do Corpus da Língua Portuguesa Brasileira, resultando em 3756236 palavras diferentes. Para atender os requísitos do trabalho, foi utilizado um script em python para tratar e filtrar o arquivo.
***
  ### O Script .py faz as seguintes alterações:
   - Separa a palavra da frequência ao encontrar um espaço em branco na linha;
   - Usa um dicionário para ignorar acentos e filtrar caracteres especiais: 
     <br><br>
     ![image](https://user-images.githubusercontent.com/86920019/166328061-47231c73-06ad-4302-ab72-591177337223.png)
     <br>
     Obs: troca os caracteres especiais por espaço vazio '', e os hífens por um espaço em branco ' '.
     <br><br>
   - Transforma qualquer palavra minúscula em maiúscula;
   - Remove as palavras que contenham menos de 5 letras;
   - Remove as palavras com frequência menor que 10;
   - Junta a frase e a frequência e separa-os por ';' e no final quebra a linha e escreve no arquivo novo:
     <br><br>
     ![image](https://user-images.githubusercontent.com/86920019/166329092-e191686f-90bc-431b-a076-c4d30e68c1bb.png)
     <br><br>
***
O arquivo gerado pode ser encontrar na pasta data com o nome 'palavrasFormatadas.txt'. Optamos por filtrar as palavras com frequências menores que 10 para facilitar no uso do programa (leitura rápida do arquivo), mas não interfere em seu funcionamento.

## **Documento de Especificação**
  Para melhor entendimento do objetivo do trabalho, acesse:
[Especificação do Trabalho 1](https://docs.google.com/document/d/1aa51VNLQ_jpZaEuGkMz2KE8feAkE48-TENZ9eqn48nk/edit?usp=sharing).

- ## **Linguagem de programação**
  * C++</br>
    <img src="https://img.shields.io/badge/-C++%20-00599C?logo=c%2B%2B&style=for-the-badge" width="140" height="50"/>

- ## **Requisítos de compilação**
  * CMAKE</br>
    <img src="https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white" width="140" height="50" alt="CMAKE"/>
  * GCC</br>
    <img src="https://img.shields.io/badge/-GCC %20-A42E2B?logo=gnu&style=for-the-badge" width="140" height="50" alt="GCC"/>


***

- ## **Como criar e executar o arquivo .exe**
    * Abra o terminal na pasta dos arquivos e digite:<br><br>
          1. ```mkdir build```<br>
          2. ```cd build```<br>
          3. ```cmake ..```<br>
          4. ```cmake --build .```<br>
          5. ```./program ../data/palavrasFormatadas.txt ../data/scores.txt```<br>
          
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
