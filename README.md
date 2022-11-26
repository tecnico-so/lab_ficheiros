# Guião 3: Programação com ficheiros

![IST](img/IST_DEI.png)  

## Objectivos

No final deste guião, deverá ser capaz de:

- interagir com ficheiros utilizando as operações da interface POSIX (`fopen`, `fwrite`, `fread`, `fclose`, entre outras);
- compreender a utilização prática dos descritores de ficheiros (_file descriptors_).

## Requisitos

- Sistema operativo Linux Ubuntu 20.04 LTS (se não o tiverem disponível no vosso computador pessoal, podem utilizar os computadores do laboratório).

## Acesso a ficheiros

1. Observe o código fonte no ficheiro [open-write.c](./open-write/open-write.c).
Compile, execute e verifique que o ficheiro `test.txt` tem a mensagem esperada.

2. Observe o código fonte no ficheiro [open-read.c](./open-read/open-write.c).
Compile, execute e verifique que o _output_ impresso no ecrã é o esperado.

3. Modifique cada programa acima para passarem a aceder ao ficheiro usando as funções da biblioteca _stdio_ (ou seja, `fopen`, `fwrite`, `fread`, `fclose`, entre outras).
Mais documentação sobre a biblioteca *stdio* pode ser encontrada em: <https://man7.org/linux/man-pages/man3/stdio.3.html>.

4. Experimente correr os novos programas e confirme que têm um comportamento equivalente aos exemplos originais.

5. Que vantagens encontra nas novas variantes dos programas?

6. Caso o programa [open-read.c](./open-read/open-read.c) seja executado sobre um ficheiro cujo conteúdo exceda 128 _bytes_, só um excerto do ficheiro é lido.
Corrija essa limitação, de forma a ler integralmente o ficheiro mesmo quando o seu conteúdo é superior à dimensão do _buffer_.

7. Teste a sua solução usando um ficheiro grande.

8. Estenda a solução anterior de modo que o resultado da leitura seja colocado no ficheiro `test-out.txt`.

9. Experimente a nova solução e verifique o resultado está correto usando o comando `diff` entre ambos os ficheiros.

## Interface de Entradas/Saídas

A interface de E/S do Unix é baseada na existência de uma tabela de ficheiros abertos por cada processo, também chamada _file descriptor table_.
Esta tabela permite tratar vários canais de comunicação da mesma forma (ex. terminais, ficheiros, _sockets_, _pipes_) utilizando os _file descriptors_ devolvidos pela função `open`.

Como já sabe, por convenção, os três primeiros _file descriptors_ são reservados: `0` - `stdin` (_standard input_, vulgo teclado), `1` - `stdout` (_standard out_, vulgo ecrã), `2` - `stderr` (_standard error_, também o ecrã).

1. Modifique o programa original [open-write.c](./open-write/open-write.c) substituindo o primeiro argumento (`fd`) da instrução write por `1` e verifique o que muda no comportamento do programa.

2. Também pode fazer esta alteração sobre o programa que compôs baseado no `stdio`.
Nesse caso, deve passar a variável `FILE * stdout` (definida em `stdio.h`) para o argumento respetivo da função de escrita que usou (`fwrite`, `fprintf`, ou `outra`).

3. Modifique o programa original [open-read.c](./open-read/open-read.c) substituindo o primeiro argumento (`fd`) da instrução read por `0` e verifique que a mensagem é lida do teclado.

4. Idem sobre o programa [open-read.c](./open-read/open-read.c) baseado no `stdio`, usando a variável `FILE * stdin` como argumento da função de leitura (`fread`, `fscanf`, ou outra).

## Conclusão

Neste guião demonstrou-se como escrever e ler de um ficheiro.
