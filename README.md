# **Trabalho - Unidade 1 - LP1 - T01 (2022.1)**

# Avaliação e Feedback

## Geral

- Implementção da Classe forca ou similar | 10 / 10 pontos
	- ok

- Implementação da Interface textual | 10 / 10 pontos
	- ok

- Execução completa do jogo | 13 / 15 pontos
	- Sorteio correto de paralavras para o jogo: cp1
	- Configuração correta da palavra jogada, dependendo da dificuldade: 5 / 5 
	- Execução correta do jogo (não pode repetir palpites, contabilização correta dos pontos e loop): 1 / 3
    - voces não entenderam muito bem o loop do jogo, quando o jogador termina uma palavra ele deve manter os pontos!
	- Salvamento correto do score: 2 / 2
	- Exibição correta dos scores: 5 / 5

- Validação dos arquivos de texto | 5 / 5 pontos
	- ok

- Arquivos de teste de validação dos casos de erro | 5 / 5 pontos
	- ok

## Código

- Documentação do código e readme | 10 / 10 pontos
	- ok

- Organização e indentação do código | 0 / 10 pontos
	- Aqui vou tirar pontos pela divisão equivocada do forca.hpp
  - Vou tirar todos os pontos deste quesito pelo uso de goto, embora c++ suporte essa construção é feita para ser usada com assembly e implementações de baixo nível!

- Compilação automatizada | 5 / 5 pontos
	- ok
	
## Comentários
- A implementação de um .hpp é sempre em um unico .cpp, isso pq a ideia de dividir em arquivos é que os arquivos agrupem funcionalidades logicamente relacionadas. Se vc escolheu dividir o forca.cpp em dus arquivos, é pq claramente parte do forca.hpp deveria também ser dividido em 2.
- Como eu falei para vocês no CP1, não se usa goto, especialmente em c++ que tem objetivo de aumentar o nível de abstração. Veja que usar goto quebra completamente com a ideia de programação estruturada, quanto mais a ideia de programação orientada à objetos. Por favor, não repitam isso no próximo projeto.

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
   - Transforma qualquer letra minúscula em maiúscula;
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
