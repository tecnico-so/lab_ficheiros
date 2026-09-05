# Guião sobre programação com ficheiros

![IST](img/IST_DEI.png)  


## Objetivos

No final deste guião, deverá ser capaz de:

- construir programas para escrever e ler ficheiros utilizando `open`, `close`, `read`, `write`;

- detetar e tratar erros e transferências parciais de dados;

- escrever e ler registos binários com campos de diferentes tipos de dados.


## Introdução

Quase todos os programas precisam de receber ou guardar dados.
Em Unix, muitas destas operações são tratadas através de uma mesma abstração: ficheiros, vistos como sequências de *bytes* que podem ser lidas ou escritas.

Neste guião vamos explorar, em C, a interface POSIX baseada em *file descriptors*, utilizando funções como `open`, `read`, `write` e `close`.

Vamos estudar primeiro dois exemplos de código e depois segue-se um exercício.

### Antes de começar

Para os exemplos e o exercício vai precisar de um sistema operativo compatível com POSIX, de preferência um Unix, como o Ubuntu Linux ou outro. 
Se não o tiver disponível no seu computador pessoal, pode utilizar um dos computadores do laboratório.

Para obter os exemplos de código, clone este repositório, usando o comando: `git clone https://github.com/tecnico-so/lab_ficheiros.git` 


## Exemplos

Nestes exemplos de código, vamos começar por ver um programa que faz escrita num ficheiro e depois veremos outro que faz leitura.


## 1. Escrita num ficheiro

Observe o código-fonte disponível no ficheiro [`open-write.c`](./open-write/open-write.c).

### 1.1. Análise inicial

Antes de executar o programa:

**a)** identifique as chamadas a `open` e `write`;

**b)** indique que ficheiro espera que seja criado ou alterado e qual deverá ser o seu conteúdo.

### 1.2. Compilação e execução

Compile o programa:

```console
cd open-write
make
```

Execute-o e verifique o conteúdo de `test.txt`:

```console
./open-write
cat test.txt
```

Compare o resultado observado com a previsão efetuada anteriormente.

### 1.3. A função `write`

Consulte a [documentação de `write`](https://man7.org/linux/man-pages/man2/write.2.html)[^man2]:

```console
man 2 write
```

[^man2]: O argumento 2 no comando `man` corresponde à secção do manual sobre chamadas ao sistema (em vez de comandos de utilizador, que estão na secção 1, acedida por omissão).

**a)** Explique o significado dos três argumentos de `write` e do valor devolvido pela função.

**b)** Verifique na documentação se uma chamada a `write` garante que todos os *bytes* solicitados são escritos.


## 2. Tratamento de erros

Altere temporariamente o caminho utilizado por `open` para um caminho cujo diretório não exista, por exemplo:

```text
/diretorio-inexistente/test.txt
```

Execute novamente o programa e observe o valor devolvido por `open`.

Consulte a [documentação de `open`](https://man7.org/linux/man-pages/man2/open.2.html):

```console
man 2 open
```

No programa, pode utilizar `perror` para apresentar uma mensagem de causa do erro.

Repita a execução e compare o resultado.


## 3. Leitura de um ficheiro

Observe agora o código-fonte disponível no ficheiro [`open-read.c`](./open-read/open-read.c).

### 3.1. Análise inicial

Antes de executar o programa:

**a)** identifique as chamadas a `open` e `read`;

**b)** determine a dimensão do *buffer* e preveja o resultado que deverá ser apresentado no terminal.

### 3.2. Execução e análise de `read`

Compile e execute o programa.

```console
cd ../open-read
make
```

Consulte a [documentação de `read`](https://man7.org/linux/man-pages/man2/read.2.html):

```console
man 2 read
```

Explique:

**a)** o significado dos três argumentos de `read`;

**b)** o significado dos valores devolvidos quando são superiores a zero, iguais a zero ou iguais a `-1`.


## 4. Leitura de ficheiros maiores do que o *buffer*

Se [`open-read.c`](./open-read/open-read.c) efetuar apenas uma chamada a `read`, um ficheiro maior do que o *buffer* não será lido integralmente.

**a)** Verifique o que acontece com um ficheiro maior, por exemplo, com mais de 1 KiB (1024 *bytes*).

**b)** Modifique o programa de forma que `read` seja chamada repetidamente até devolver `0`, tratando também eventuais erros.
Pode pensar no *buffer* como se fosse um balde, que permite transferir água de um recipiente para outro, um de cada vez.



## 5. Tabela de descritores de ficheiros

Cada processo Unix mantém uma tabela de *file descriptors*. 
Um descritor é um índice na tabela de descritores do processo; a entrada referencia uma descrição de ficheiro aberto mantida pelo sistema.

Por convenção, um processo inicia-se normalmente com três *file descriptors* já abertos:

* `0`: *standard input*, normalmente associado ao terminal para leitura;
* `1`: *standard output*, normalmente associado ao terminal para escrita; e
* `2`: *standard error*, normalmente também associado ao terminal para escrita de mensagens de erro.

**a)** Modifique o programa substituindo, na chamada a `read`, o *file descriptor* correspondente ao ficheiro por `0`[^stdin_fileno].

[^stdin_fileno]: O valor literal de `0` deve ser substituído posteriormente por `STDIN_FILENO`, definido em `<unistd.h>`.

**b)** Compile e execute o programa.
Terá de introduzir o texto através do teclado.


## Resumo

O *file descriptor* é um índice numa tabela mantida pelo processo e é utilizado por operações como `read`, `write` e `close` para identificar ficheiros e outros objetos de entrada-saída.
Esta interface foi concebida no Unix para ser simples e uniforme.
Por isso, `read` e `write` não assumem que todos os *bytes* pedidos possam ser transferidos numa única chamada.
Por exemplo, num terminal podem estar disponíveis apenas os caracteres já introduzidos pelo utilizador. 
Pode também acontecer que uma chamada a `write` apenas consiga escrever parte dos dados.

A semântica destas operações é, portanto, aproximadamente:  
**transferir até ao número de *bytes* solicitado e indicar quantos foram efetivamente transferidos**.  
Esta abordagem permite usar as mesmas primitivas para diferentes tipos de objetos e deixa ao programa o controlo sobre repetição, tratamento de erros e sincronização.

Em ficheiros regulares, `read` e `write` transferem frequentemente todos os *bytes* pedidos numa única chamada, mas é importante ter em conta que esse comportamento não é garantido pela interface.


## Mini-exercício

**Registo de treinos/eventos**

Pretende-se implementar um programa para guardar e processar informação num ficheiro binário.

Considere os registos como correspondentes a eventos produzidos por um dispositivo de monitorização de atividade física (*fitness tracker*) ou similar.

Ao longo deste exercício, o formato de cada registo será construído progressivamente. 

Em todas as alíneas devem ser utilizadas as operações POSIX `open`, `read`, `write` e `close` para acesso aos ficheiros.

Sempre que for necessário transferir vários *bytes*, não deve assumir que uma única chamada a `read` ou `write` transfere necessariamente todos os *bytes* pedidos.
Sugere-se a criação de funções auxiliares para as leituras e escritas.


### 1. Registos contendo apenas texto

Comece pelo formato mais simples. Cada registo contém apenas um campo de texto com exatamente **64 bytes**:

```text
+------------------------------+
|          64 bytes            |
+------------------------------+
|          64 bytes            |
+------------------------------+
|          64 bytes            |
+------------------------------+
              ...
```

O campo é representado em memória por:

```c
char texto[64];
```

É boa prática definir uma constante no código para guardar o valor literal do tamanho do vetor.

Um texto poderá ter no máximo 63 *bytes* de texto. 
Os *bytes* não utilizados devem ter o valor zero, garantindo assim que o texto fica terminado por `'\0'`.

**a)** Escrever textos

Implemente o programa `write_texts.c`, que cria o ficheiro:

```text
texts.bin
```

e nele escreve, pelo menos, **quatro registos** contendo textos diferentes.

Por exemplo:

```text
sensor cardíaco operacional
sensor movimento operacional
treino iniciado
treino terminado
```

Calcule o tamanho que este ficheiro deverá ter.

Depois de executar o programa, confirme a dimensão de `texts.bin`.

**b)** Ler textos

Implemente `read_texts.c`, que abre `texts.bin` e apresenta sequencialmente todos os textos nele guardados.

A leitura deve terminar quando for encontrado o fim normal do ficheiro.

Tenha em conta os seguintes pontos:

- Como sabe o programa onde começa o registo seguinte?
- Por que razão deve ler 64 bytes mesmo quando o texto contém apenas 15 caracteres?
- O que significa uma chamada a `read` devolver `0`?
- O que significa encontrar o fim do ficheiro depois de já terem sido lidos alguns *bytes* de um novo registo?

### 2. Acrescentar um campo inteiro

Pretende-se agora associar um número inteiro a cada texto.
Este valor representa uma **marca temporal** correspondente ao número de segundos decorridos desde o início do treino.

O novo formato de cada registo passa a ser:

```text
+-------------+------------------------------+
|     int     |          64 bytes            |
+-------------+------------------------------+
|     int     |          64 bytes            |
+-------------+------------------------------+
                       ...
```

Cada registo contém, por esta ordem:

```text
int
char[64]
```

**c)** Escrever valores e textos

Crie um novo programa, baseado no anterior, chamado `write_values.c`.

O programa deverá criar:

```text
values.bin
```

e escrever pelo menos quatro registos.

Utilize valores inteiros diferentes e crescentes.

Cada campo deverá ser escrito separadamente.

Indique uma expressão, utilizando `sizeof`, que represente a dimensão de **um registo**.

Confirme novamente a dimensão do ficheiro.

**d)** Ler valores e textos

Implemente também `read_values.c`, que lê todos os registos de `values.bin`.

Para cada registo, apresente:

```text
<valor> | <texto>
```

Atente aos seguintes pontos:

- Qual é a dimensão de um ficheiro que contém `N` destes registos?
- Depois de ler o texto, como sabe onde começa o `int` do registo seguinte?
- Por que razão não seria correto procurar `'\0'` para determinar onde começa o próximo registo?

**e)** Verificar a leitura e a escrita

Execute primeiro:

```console
./write_values
```

e depois:

```console
./read_values
```

Confirme que os valores apresentados correspondem aos valores originalmente escritos.

----

O resto do enunciado será entregue no início da aula e estenderá a solução desenvolvida até este ponto.

### Avaliação em aula

Quando tiver concluído o exercício, chame o docente do laboratório, para que possa ver a solução em execução e fazer perguntas sobre a implementação a cada membro do grupo.

**A avaliação é presencial e individual.**

Não basta que o código funcione, é necessário saber explicar como foi implementado e por que funciona.
Podem também ser pedidas modificações de pormenor no momento.

Entregar a solução antes do fim da aula:

**Fénix**, Avaliação, Projetos, **mini-Exercício 1**

**Tenha em atenção o seguinte:**

- só serão aceites trabalhos de estudantes que estiveram presentes no laboratório. Confirme que o docente registou a sua presença na aula;
- assegure-se de que a solução é enviada em formato ZIP e que não contém ficheiros executáveis nem outros ficheiros gerados pela compilação. Antes de criar o ficheiro ZIP, limpe os ficheiros gerados manualmente ou com `make clean`;
- deverá também incluir um ficheiro `README` com um breve resumo da funcionalidade implementada (parcial ou total).


## Conclusão

Ao longo do guião, analisámos exemplos de leitura e escrita de ficheiros e depois pusemos em prática num exercício com diferentes tipos de dados.

Os *file descriptors* são índices inteiros numa tabela mantida pelo processo, cujas entradas identificam canais de entradas-saídas abertos, como ficheiros e outros (por exemplo, *pipes*, que serão estudados mais tarde).

As funções `read` e `write` foram concebidas como primitivas genéricas de entradas-saídas que podem transferir menos *bytes* do que os solicitados. 
O programador deve, por isso, verificar sempre os valores devolvidos e tratar erros e transferências parciais.

Sobre estas primitivas podem depois ser construídas bibliotecas que tornam a programação mais simples e as operações mais eficientes[^stdio].

[^stdio]: A biblioteca `stdio` faz *buffering* de leituras e escritas e é abordada no [guião extra](READMETOO.md).

----

Contactos para sugestões/correções: [LEIC-Alameda](mailto:leic-so-alameda@disciplinas.tecnico.ulisboa.pt), [LEIC-Tagus](mailto:leic-so-tagus@disciplinas.tecnico.ulisboa.pt), [LETI](mailto:leti-so-tagus@disciplinas.tecnico.ulisboa.pt)
