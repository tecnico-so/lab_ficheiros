# Guião sobre programação com ficheiros

![IST](img/IST_DEI.png)  

## Objetivos

No final deste guião, deverá ser capaz de:

- interagir com ficheiros utilizando as operações da interface POSIX de *file descriptors* (`open`, `close`, `read`, `write`, entre outras)  e as operações da interface POSIX de *I/O streams* (`fopen`, `fclose`, `fread`, `fwrite`, entre outras);
- compreender a utilização prática dos descritores de ficheiros (*file descriptors*).

## Requisitos

- Sistema operativo POSIX-compliant, de preferência Linux Ubuntu 20.04 LTS (se não o tiverem disponível no vosso computador pessoal, podem utilizar os computadores do laboratório).

## Acesso a ficheiros

1. Observe o código fonte no ficheiro [open-write.c](./open-write/open-write.c).
Compile, execute e verifique que o ficheiro `test.txt` tem a mensagem esperada.  
Consulte a documentação da função [`write`](https://man7.org/linux/man-pages/man2/write.2.html) para perceber em detalhe os argumentos e o resultado.

2. Observe o código fonte no ficheiro [open-read.c](./open-read/open-read.c).
Compile, execute e verifique que o *output* impresso no ecrã é o esperado.  
Consulte a documentação da função [`read`](https://man7.org/linux/man-pages/man2/read.2.html) para perceber em detalhe os argumentos e o resultado.

3. Modifique cada programa acima para passarem a aceder ao ficheiro usando *I/O streams* da biblioteca *stdio* (ou seja, [`fopen`](https://man7.org/linux/man-pages/man3/fopen.3.html), [`fwrite`](https://man7.org/linux/man-pages/man3/fwrite.3.html), [`fread`](https://man7.org/linux/man-pages/man3/fread.3.html), [`fclose`](https://man7.org/linux/man-pages/man3/fclose.3.html), [`fseek`](https://man7.org/linux/man-pages/man3/fseek.3.html), entre outras).  
Mais documentação sobre a biblioteca *stdio* pode ser encontrada em: <https://man7.org/linux/man-pages/man3/stdio.3.html>.

4. Experimente correr os novos programas e confirme que têm um comportamento equivalente aos exemplos originais.

5. Que vantagens encontra nas novas variantes dos programas?

<!-- 
According to <https://stackoverflow.com/a/584154/129497>:  
read() is a low level, unbuffered read.
It is a wrapper of the read system call on UNIX.
fread() is part of the C library, and provides **buffered reads**.
It is usually implemented by calling read() in order to fill its buffer.

An additional point is made by <https://stackoverflow.com/a/585598/129497>:  
fread are not formatted IO: we have a non formatted byte stream whereas 
fread **allows formatted IO** (with the "%.." parameter)
-->

6. Caso o programa [open-read.c](./open-read/open-read.c) seja executado sobre um ficheiro cujo conteúdo exceda `128` *bytes*, só um excerto do ficheiro é lido.
Corrija essa limitação, de forma a ler integralmente o ficheiro mesmo quando o seu conteúdo é superior à dimensão do *buffer* da aplicação.

7. Teste a sua solução usando um ficheiro grande.

8. Estenda a solução anterior de modo que o resultado da leitura seja colocado no ficheiro `test-out.txt`.

9. Experimente a nova solução e verifique o resultado está correto usando o comando `diff` entre ambos os ficheiros.

## Interface de Entradas/Saídas (I/O)

A interface de I/O do Unix é baseada na existência de uma tabela de ficheiros abertos por cada processo, também chamada _file descriptor table_.
Esta tabela permite tratar vários canais de comunicação da mesma forma (ex. terminais, ficheiros, *sockets*, *pipes*) utilizando os *file descriptors* devolvidos pela função `open`.

Como já sabe, por convenção, os três primeiros *file descriptors* são reservados: `0` para o  `stdin` (*standard input*, vulgo teclado), `1` para o `stdout` (*standard out*, vulgo ecrã) e `2` para o `stderr` (*standard error*, por omissão também o ecrã).

1. Modifique o programa original [open-write.c](./open-write/open-write.c) substituindo o primeiro argumento (`fd`) da instrução write por `1` e verifique o que muda no comportamento do programa.

2. Também pode fazer esta alteração sobre o programa que compôs baseado no *stdio*.
Nesse caso, deve passar a variável `FILE* stdout` (definida em `stdio.h`) para o argumento respetivo da função de escrita que usou (`fwrite`, `fprintf` ou outra).

3. Modifique o programa original [open-read.c](./open-read/open-read.c) substituindo o primeiro argumento (`fd`) da instrução `read` por `0` e verifique que a mensagem é lida do teclado.

4. Idem sobre o programa [open-read.c](./open-read/open-read.c) baseado no *stdio*, usando a variável `FILE* stdin` como argumento da função de leitura ([`fread`](https://man7.org/linux/man-pages/man3/fread.3.html), [`fscanf`](https://man7.org/linux/man-pages/man3/fscanf.3.html) ou outra).

## Conclusão

Neste guião demonstrou-se as funções `read` e `write` e a forma como devem ser usadas para ler ou escrever dados, de forma gradual.
É importante garantir que todos os *bytes* são lidos e escritos de acordo com o esperado.

Vimos também como escrever e ler de um ficheiro de texto usando as funções com o prefixo `f` (*file*), do *stdio*, que usam um *buffer* interno.

----

Contactos para sugestões/correções: [LEIC-Alameda](mailto:leic-so-alameda@disciplinas.tecnico.ulisboa.pt), [LEIC-Tagus](mailto:leic-so-tagus@disciplinas.tecnico.ulisboa.pt), [LETI](mailto:leti-so-tagus@disciplinas.tecnico.ulisboa.pt)
