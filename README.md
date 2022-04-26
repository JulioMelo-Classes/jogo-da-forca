# Trabalho und1 - LP1

# Jogo da Forca!

Necessário ter o CMAKE e G++ no ambiente para executar o código.

Para rodar digite os comandos no terminal:
  - mkdir build
  - cd build
  - cmake ..
  - cmake --build .
  - ./program ../palavrasFormatada.txt ../scores.txt

</br>

# Validação dos arquivos de Palavras e Scores (Apresentação dos ERROS)
  - Arquivo (palavras) inexistente:
    ![image](https://user-images.githubusercontent.com/86920019/165214668-1dd4b540-a2da-4009-b325-0c3cde4fec5a.png)
  
  - Palavras com caracteres que não estejam entre [a - z|A - Z], ‘ ‘(espaço em branco) ou hífen ‘-’:
    ![image](https://user-images.githubusercontent.com/86920019/165215271-c7ce5fea-6368-4b84-8a6c-87ccfbd31a20.png)

  - Palavras que não tenham sua frequência correspondente, ou a frequência não seja um número inteiro positivo:
    ![image](https://user-images.githubusercontent.com/86920019/165217478-e545232e-22a8-4725-a66f-e86dd95c73cc.png)
    ![image](https://user-images.githubusercontent.com/86920019/165216931-0b98f2d2-7d81-4322-a446-09b91631e275.png)
  
  - Palavras com tamanho menor ou igual a 4:
    ![image](https://user-images.githubusercontent.com/86920019/165217720-a6341c3d-1c6b-430c-a4d5-8b2689b2ec16.png)
  
  - Arquivo (scores) inexistente:
    ![image](https://user-images.githubusercontent.com/86920019/165214910-aa3d0fc5-3256-4814-a50b-39784053db8f.png)
  
  - Presença de mais ou menos que 3 “;” em alguma linha:
    ![image](https://user-images.githubusercontent.com/86920019/165218389-1f2bcfd4-9374-4c2a-b3ea-7ff847532766.png)
    ![image](https://user-images.githubusercontent.com/86920019/165218522-88888ed0-d8c4-4359-93ba-20c51b28ee43.png)
  
  - Qualquer um dos campos: "nível de dificuldade”, “nome”  ou “pontuação” vazios:
    ![image](https://user-images.githubusercontent.com/86920019/165218672-27004e48-9352-493d-90d8-5704a3d56d82.png)
    ![image](https://user-images.githubusercontent.com/86920019/165218799-c7bf561f-960d-4e96-a0a8-25459dde8a09.png)

# Documento de Especificação

[Especificação do Trabalho 1](https://docs.google.com/document/d/1aa51VNLQ_jpZaEuGkMz2KE8feAkE48-TENZ9eqn48nk/edit?usp=sharing). 
