# Guião extra sobre programação com ficheiros

Este guião contém informação extra para a programação com ficheiros em C.

## Objetivos

No final deste guião extra, deverá também ser capaz de:

- utilizar *streams* de entradas-saídas da biblioteca `stdio` para ler e escrever ficheiros.


## Biblioteca `stdio`

As operações `open`, `read`, `write` e `close` utilizadas no guião principal correspondem a uma interface de relativamente baixo nível, tradicionalmente associada aos sistemas Unix e baseada em descritores de ficheiros.

Nos primeiros anos do desenvolvimento de C surgiu também de oferecer uma interface de entradas-saídas mais portável para outros sistemas.
A biblioteca `stdio` representa os canais através de *streams* do tipo `FILE *`. 
Além de oferecer uma interface de nível mais elevado, mantém normalmente *buffers* em espaço de utilizador. 
Este *buffering* pode tornar a utilização da interface mais conveniente e reduzir o número de operações realizadas diretamente sobre o sistema operativo, permitindo melhor desempenho global do programa.

Para mais informação, consulte a página de manual online [`stdio(3)`](https://man7.org/linux/man-pages/man3/stdio.3.html) e a documentação das funções a utilizar.

**Sugestão de atividade:**

1. Reimplemente os programas do guião principal utilizando funções da biblioteca `stdio`, como [`fopen`](https://man7.org/linux/man-pages/man3/fopen.3.html), [`fread`](https://man7.org/linux/man-pages/man3/fread.3.html), [`fwrite`](https://man7.org/linux/man-pages/man3/fwrite.3.html), [`fclose`](https://man7.org/linux/man-pages/man3/fclose.3.html);

2. Execute os novos programas e confirme que apresentam um comportamento equivalente ao das versões originais;

3. Analise as principais diferenças entre as duas implementações, incluindo a abertura dos ficheiros, as operações de leitura e escrita, o tratamento de erros e o *buffering*;

4. Identifique potenciais vantagens e limitações de cada uma das interfaces.

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

Atenção: tal como `read` e `write` podem transferir menos *bytes* do que os solicitados, `fread` e `fwrite` podem processar menos elementos do que os pedidos.
Os valores devolvidos pelas funções devem, por isso, ser sempre verificados.
Note que `fread` e `fwrite` devolvem o número de elementos processados, e não diretamente o número de *bytes*. 
No caso de `fread`, pode ainda ser necessário distinguir o fim do ficheiro de uma situação de erro, por exemplo através de [`feof`](https://man7.org/linux/man-pages/man3/feof.3.html) e [`ferror`](https://man7.org/linux/man-pages/man3/ferror.3.html).


## Reposicionamento num ficheiro

Até agora vimos apenas acesso sequencial aos ficheiros.
A função [`fseek`](https://man7.org/linux/man-pages/man3/fseek.3.html) permite alterar a posição corrente de um *stream* dentro de um ficheiro, sem ser necessário ler ou escrever os dados intermédios. A sua forma geral é:

```c
int fseek(FILE *stream, long offset, int origin);
```

O argumento `offset` indica o deslocamento a aplicar e `origin` indica o ponto a partir do qual esse deslocamento é calculado:

* `SEEK_SET`: início do ficheiro;
* `SEEK_CUR`: posição corrente;
* `SEEK_END`: fim do ficheiro.

Por exemplo,

```c
fseek(f, 0, SEEK_SET);
```

reposiciona o *stream* no início do ficheiro, enquanto

```c
fseek(f, 100, SEEK_SET);
```

posiciona-o a 100 bytes do início.

Esta operação é útil quando é necessário aceder diretamente a diferentes partes de um ficheiro, por exemplo, para voltar a ler dados já processados ou para aceder a um registo numa posição conhecida.

`fseek` devolve `0` em caso de sucesso e um valor diferente de zero em caso de erro.

**Sugestão de atividade:**

Modifique um dos programas para ler diretamente o segundo registo do ficheiro, sem ler o primeiro, por exemplo.

## Conclusão

Neste guião extra foi apresentada uma segunda forma de realizar operações de entradas-saídas em C.
Foi também apresentada a forma de reposicionar a leitura e escrita no ficheiro.
A escolha da interface de programação a usar num dado programa depende das necessidades da aplicação. 
A biblioteca `stdio` é geralmente adequada quando se pretende uma interface mais conveniente e com *buffering*, enquanto a utilização direta de descritores de ficheiros é útil quando é necessário maior controlo sobre as operações de entrada/saída.

----

Contactos para sugestões/correções: [LEIC-Alameda](mailto:leic-so-alameda@disciplinas.tecnico.ulisboa.pt), [LEIC-Tagus](mailto:leic-so-tagus@disciplinas.tecnico.ulisboa.pt), [LETI](mailto:leti-so-tagus@disciplinas.tecnico.ulisboa.pt)
