# Guião extra sobre programação com ficheiros

Este guião contém informação extra para a programação com ficheiros em C.

## Objetivos

No final deste guião extra, deverá também ser capaz de:

- interagir com ficheiros cp, as operações  de *I/O streams* (`fopen`, `fclose`, `fread`, `fwrite`, entre outras);


## Biblioteca stdio

1. Modifique cada programa acima para passarem a aceder ao ficheiro usando *I/O streams* da biblioteca *stdio* (ou seja, [`fopen`](https://man7.org/linux/man-pages/man3/fopen.3.html), [`fwrite`](https://man7.org/linux/man-pages/man3/fwrite.3.html), [`fread`](https://man7.org/linux/man-pages/man3/fread.3.html), [`fclose`](https://man7.org/linux/man-pages/man3/fclose.3.html), [`fseek`](https://man7.org/linux/man-pages/man3/fseek.3.html), entre outras).  

Mais documentação sobre a biblioteca *stdio* pode ser encontrada em: <https://man7.org/linux/man-pages/man3/stdio.3.html>.

2. Experimente correr os novos programas e confirme que têm um comportamento equivalente aos exemplos originais.

3. Que vantagens encontra nas novas variantes dos programas?

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


1. Modifique o programa original [open-write.c](./open-write/open-write.c) substituindo o primeiro argumento (`fd`) da instrução write por `1` e verifique o que muda no comportamento do programa.

2. Também pode fazer esta alteração sobre o programa que foi implementado usando *stdio*.
Nesse caso, deve passar a variável `FILE* stdout` (definida em `stdio.h`) para o argumento respetivo da função de escrita que usou (`fwrite`, `fprintf` ou outra).



3. Modifique o programa original [open-read.c](./open-read/open-read.c) substituindo o primeiro argumento (`fd`) da instrução `read` por `0` e verifique que a mensagem é lida do teclado.

4. Fazer o mesmo para o programa [open-read.c](./open-read/open-read.c) baseado no *stdio*, usando a variável `FILE* stdin` como argumento da função de leitura ([`fread`](https://man7.org/linux/man-pages/man3/fread.3.html), [`fscanf`](https://man7.org/linux/man-pages/man3/fscanf.3.html) ou outra).





Desafio opcional: compare o tempo necessário para copiar um ficheiro utilizando buffers de 1 byte, 128 bytes, 4 KiB e 64 KiB. Que comportamento observa?



## Conclusão

Neste guião extra foi apresentada uma segunda forma de realizar I/O em C:

- `read()` usa descritores de ficheiros (*file descriptors*) e oferece maior controlo sobre as operações de I/O;
- `fread()` usa *streams* `FILE *` e um *buffer* interno, o que simplifica muitas operações e pode reduzir o número de chamadas ao sistema;
- ambas as abordagens beneficiam da *cache* do kernel;
- `read()` pode devolver menos *bytes* do que os pedidos, pelo que pode ser necessário repetir a operação até obter todos os dados esperados.

`read` e `write` não garantem que todos os *bytes* solicitados sejam transferidos numa única chamada. A sua semântica pode ser resumida da seguinte forma:

> transferir até ao número de *bytes* solicitado e indicar quantos foram efetivamente transferidos.

Este comportamento é necessário porque diferentes objetos de entrada/saída têm características distintas. Por exemplo, um terminal pode disponibilizar apenas os caracteres introduzidos pelo utilizador, um *pipe* pode conter apenas parte dos dados esperados e um destino de escrita pode aceitar apenas parte dos dados naquele momento.

Em ficheiros regulares, `read` e `write` transferem frequentemente todos os *bytes* pedidos numa única chamada, mas esse comportamento não é garantido pela interface. O programador deve, por isso, tratar explicitamente erros e transferências parciais.

Os *I/O streams*, disponibilizados por bibliotecas de nível mais elevado, como `stdio`, oferecem uma interface mais conveniente e escondem parte desta complexidade através de *buffering* e lógica adicional. Funções como `fread`, `fwrite` e `fprintf` são, por isso, frequentemente preferíveis quando não é necessário o controlo de baixo nível proporcionado pelos *file descriptors*.
No entanto, `fread` e `fwrite` também não garantem que todos os *bytes* solicitados sejam transferidos numa única chamada.

----

Contactos para sugestões/correções: [LEIC-Alameda](mailto:leic-so-alameda@disciplinas.tecnico.ulisboa.pt), [LEIC-Tagus](mailto:leic-so-tagus@disciplinas.tecnico.ulisboa.pt), [LETI](mailto:leti-so-tagus@disciplinas.tecnico.ulisboa.pt)
