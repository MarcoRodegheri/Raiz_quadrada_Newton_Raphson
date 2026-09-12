<div align="center">

# Raiz Quadrada em Assembly MIPS — Método de Newton-Raphson

### Trabalho da disciplina de Organização e Arquitetura de Processadores (OAP) — PUCRS

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![MIPS Assembly](https://img.shields.io/badge/MIPS_Assembly-4B0082?style=for-the-badge)
![MARS](https://img.shields.io/badge/MARS_Simulator-FF6600?style=for-the-badge)

</div>

---

## Sobre o projeto

Implementação **recursiva** do método numérico de **Newton-Raphson** para cálculo de raiz quadrada, desenvolvida como trabalho da disciplina de **Organização e Arquitetura de Processadores (PUCRS)**. O objetivo do trabalho é percorrer todo o caminho de um algoritmo: da descrição em **alto nível (C)** até a implementação em **Assembly MIPS**, rodando no simulador **MARS**, incluindo o controle manual de registradores e pilha exigido por uma função recursiva em baixo nível.

A fórmula recursiva implementada é:

```
sqrt_nr(x, i) = 1                                           , se i = 0
sqrt_nr(x, i) = (sqrt_nr(x, i-1) + x / sqrt_nr(x, i-1)) / 2 , se i > 0
```

Onde `x` é o número cuja raiz se deseja aproximar, e `i` é o número de iterações do método — quanto maior `i`, mais próximo o resultado converge do valor real.

## Como funciona

### Alto nível (C)
A versão em C (`Alto_Nivel.c`) implementa a função `sqrt(x, i)` recursivamente, servindo como prova de conceito antes da tradução para assembly, e um laço principal que lê `x` e `i` do usuário até que um valor negativo seja informado.

### Assembly MIPS
A tradução para MIPS foi estruturada em três frentes:

- **Macros e interface com o SO** — três macros (`print_str`, `print_int`, `read_int`) encapsulam as chamadas de sistema (`syscall`) usadas para entrada e saída, evitando repetir a manipulação dos registradores `$v0`/`$a0` em todo o código.
- **Convenção de registradores** — os registradores `$s0` e `$s1` (*saved registers*) guardam `x` e `i` durante a chamada da função `sqrt`, garantindo que sobrevivam a chamadas de função e possam ser exibidos corretamente no final.
- **Gerenciamento de pilha na recursão** — a cada chamada de `sqrt`, a instrução `addi $sp, $sp, -12` reserva um *stack frame* de 12 bytes, onde são salvos `$ra` (endereço de retorno), `$a0` (x) e `$a1` (i). Isso é essencial porque `jal` sobrescreve `$ra` a cada chamada recursiva — sem salvá-lo na pilha, o programa perderia o caminho de volta para `main`.
- **Lógica matemática** — o caso base (`i == 0`) retorna 1 via `bnez`/`bltz`. No caso recursivo, a divisão é feita com `div`, o quociente é resgatado de `LO` com `mflo`, e a divisão final por 2 da fórmula é feita com deslocamento de bits (`sra`), mais eficiente que uma instrução de divisão.

## Estrutura do repositório

```
mips-newton-raphson-sqrt/
├── NR_alto_Nivel.c        # Versão em C do algoritmo (prova de conceito)
└── NR_assembly.asm        # Implementação em Assembly MIPS (macros, main, sqrt recursivo)
```

## Como rodar

**Versão em C:**
```bash
gcc Alto_Nivel.c -o sqrt_nr
./sqrt_nr
```

**Versão em Assembly (MARS):**
1. Baixe o [MARS (MIPS Assembler and Runtime Simulator)](http://courses.missouristate.edu/kenvollmar/mars/).
2. Abra o arquivo `assembly.asm` no MARS.
3. Monte o programa (**Assemble**) e execute (**Run**).
4. Informe `x` e `i` quando solicitado, ou digite um número negativo para encerrar.

**Exemplo de execução:**
```
Digite os parâmetros x e i para calcular sqrt_nr (x, i) ou -1 para abortar a execução
x: 16
i: 4
sqrt(16, 4) = 4
```

## Equipe

- Marco Antônio De Carli Rodegheri
- Bernardo Garcia
- Luiz Henrique Saggin Confortin
- Roger Rozales Ehlert
