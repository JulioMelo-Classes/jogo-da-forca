# Trabalho - Unidade 1 - LP1 - T01 (2022.1)

# Avaliação e Feeback

- Implementação do carregamento dos arquivos |  6 / 10 pontos
  - Da forma como vcs fizeram, o programa não suporta arquivos com palavras compostas com espaço no meio tipo "Sao Paulo"

- Implementação de parte da validação | 10 / 10 pontos

- Implementação de um main funcional com parte da UI | 5 / 5 pontos

- Implementação de parte da lógica de sorteio de palavras | 6 / 10 pontos 
  - Da forma que está as palavras sorteadas sempre são iguais

- Estrutura básica dos arquivos e processo de compilação definido | 4 / 5 pontos
  - Tirei uma parte aqui por terem implementado tudo no .hpp

- Observações gerais
  - Por favor, na entrega final separem em .hpp e .cpp a implementação da classe e **removam** o `using namespace std` do .hpp!
  - Ao invés de colocar tudo no forca.hpp, tentem criar mais arquivos .hpp e .cpp, especialmente com funções auxiliares ou funções relacionadas a UI

## Componentes:
  - Danrley Lima
  - Lucas Morais
# Jogo da Forca!

## Documento de Especificação
Para melhor entendimento do objetivo do trabalho, acesse:
[Especificação do Trabalho 1](https://docs.google.com/document/d/1aa51VNLQ_jpZaEuGkMz2KE8feAkE48-TENZ9eqn48nk/edit?usp=sharing).

## Requisítos compilação
  - Cmake
  - GCC/G++

## Como criar e executar o arquivo .exe

Abra o terminal na pasta dos arquivos e digite:
  - mkdir build
  - cd build
  - cmake ..
  - cmake --build .
  - ./program ../data/palavrasFormatada.txt ../data/scores.txt

## Validação dos arquivos (TESTES)

### Arquivo das PALAVRAS
  - Arquivo (palavras) inexistente:

    Obs: o arquivo 'palavrasFormatada.txt' não se encontra na pasta, como pode visualizar no canto esquerdo.
    ![image](https://user-images.githubusercontent.com/86920019/165214668-1dd4b540-a2da-4009-b325-0c3cde4fec5a.png)
  
  - Palavras com caracteres que não estejam entre [a - z|A - Z], ‘ ‘(espaço em branco) ou hífen ‘-’:

    Obs: como mostra o arquivo 'palavrasFormatada.txt', a palavra na linha 7 contém caracteres inválidos.
    ![image](https://user-images.githubusercontent.com/86920019/165215271-c7ce5fea-6368-4b84-8a6c-87ccfbd31a20.png)

  - Palavras que não tenham sua frequência correspondente, ou a frequência não seja um número inteiro positivo:

    Frequência vazia/inexistente:
    ![image](https://user-images.githubusercontent.com/86920019/165217478-e545232e-22a8-4725-a66f-e86dd95c73cc.png)
    
    Frequência negativa:
    ![image](https://user-images.githubusercontent.com/86920019/165216931-0b98f2d2-7d81-4322-a446-09b91631e275.png)
  
  - Palavras com tamanho menor ou igual a 4:
  
    ![image](https://user-images.githubusercontent.com/86920019/165217720-a6341c3d-1c6b-430c-a4d5-8b2689b2ec16.png)
    
### Arquivo dos SCORES
  - Arquivo (scores) inexistente:

    Obs: o arquivo 'scores.txt' não se encontra na pasta, como pode visualizar no canto esquerdo.
    ![image](https://user-images.githubusercontent.com/86920019/165214910-aa3d0fc5-3256-4814-a50b-39784053db8f.png)
  
  - Presença de mais ou menos que 3 “;” em alguma linha:
  
    ![image](https://user-images.githubusercontent.com/86920019/165218389-1f2bcfd4-9374-4c2a-b3ea-7ff847532766.png)
    ![image](https://user-images.githubusercontent.com/86920019/165218522-88888ed0-d8c4-4359-93ba-20c51b28ee43.png)
  
  - Qualquer um dos campos: "nível de dificuldade”, “nome”  ou “pontuação” vazios:
  
    ![image](https://user-images.githubusercontent.com/86920019/165218672-27004e48-9352-493d-90d8-5704a3d56d82.png)
    ![image](https://user-images.githubusercontent.com/86920019/165218799-c7bf561f-960d-4e96-a0a8-25459dde8a09.png)

 
