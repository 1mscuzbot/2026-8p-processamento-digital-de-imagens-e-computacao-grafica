# Aula 03 — Vizinhança, Conectividade e Rotulação

**Disciplina:** Processamento Digital de Imagens e Computação Gráfica (Prof. Diógenes Furlan)
**Slides de referência:**
- `material/slides/PDI26-03-1-Conectividade.pdf`
- `material/slides/PDI26-03-2-Conectividade-Pratica.pdf` (prática: flood fill e rotulagem)

---

## Sumário

- Vizinhança de um pixel
- Adjacência / Conectividade
- Rotulação (componentes conexos)
- Caminho digital
- Prática: Flood Fill e Rotulagem

---

## Valor de um pixel

Uma imagem é tratada como uma **matriz de pixels**: o pixel `p` na coordenada (x,y) tem intensidade `V(p) = f(x,y)` (ex.: imagem de 8 bits → `V(p) ∈ {0 … 255}`).

## Vizinhança de um pixel

| Tipo | Definição | Vizinhos de p |
|------|-----------|---------------|
| **Vizinhança-4** | horizontais + verticais | N4(p) = {(x+1,y), (x−1,y), (x,y+1), (x,y−1)} |
| **Vizinhança diagonal** | nas diagonais | ND(p) = {(x+1,y+1), (x+1,y−1), (x−1,y+1), (x−1,y−1)} |
| **Vizinhança-8** | N4 + ND | N8(p) = N4(p) ∪ ND(p) |

> Se `p` está na borda da imagem, ele tem **menos vizinhos**.

---

## Adjacência / Conectividade

Conceito **distinto** de vizinhança: além da posição, observa-se o **valor de intensidade** dos vizinhos. Dois pixels são adjacentes se o vizinho **pertence a um conjunto de valores V** (ex.: imagem binária → V = {1}; tons de cinza → V = {v | 32 ≤ v ≤ 64}).

Adjacência **estabelece limites de objetos e componentes de regiões**.

### Adjacência-4

`q` é adjacente-4 a `p` se `q ∈ N4(p)` **e** `V(q) ∈ V` (mesma faixa de valores).

### Adjacência-8

`q` é adjacente-8 a `p` se `q ∈ N8(p)` **e** `V(q) ∈ V`.

### Adjacência-m (mista)

`q` é adjacente-m a `p` se `q ∈ N4(p)`, **ou** (`q ∈ ND(p)` e `N4(p) ∩ N4(q) = ∅`), com `V(q) ∈ V`.

- É uma modificação da adjacência-8, criada para **eliminar ambiguidades** (múltiplos caminhos) da 8-adjacência.

### Exemplo (V = {1}, pixels 1/0)

| Camada | Efeito |
|--------|--------|
| Adjacência-4 | conexões só na cruz: `p` no centro conecta a vizinhos 1 na vertical/horizontal |
| Adjacência-8 | conexões na cruz + diagonais → **caminhos duplos/ambíguos** possíveis |
| Adjacência-m | diagonal só é aceita quando os dois pixels **não compartilham nenhum vizinho-4** → um único caminho |

### Caminho digital

Um **caminho digital** de `p(x,y)` a `q(s,t)` é uma sequência de pixels distintos `(x₀,y₀), (x₁,y₁), …, (xₙ,yₙ)` tal que `(x₀,y₀) = (x,y)`, `(xₙ,yₙ) = (s,t)` e cada par consecutivo é **adjacente** (na mesma relação usada).

- Se `(x₀,y₀) = (xₙ,yₙ)` o caminho é **fechado**.

### Conectividade

- Dois pixels `p, q ∈ S` são **conexos** se existe um caminho entre eles com **todos os pontos pertencentes a S**.
- O conjunto de pixels conexos a um pixel `p ∈ S` é o **componente conexo** de S que contém p.
- Se existir apenas **um** componente conexo, S é um **conjunto conexo**.
- Utilidade: estabelecer **limites de objetos**, identificar **componentes da imagem** e obter propriedades para processamento de nível mais alto.

### Resumo no exemplo do slide

A matriz binária 10×10 dos slides rende:

| Relação | Número de regiões |
|---------|:-----------------:|
| 8-conexas | **4 componentes** |
| 4-conexas | **10 componentes** |

⇒ a escolha da adjacência **muda o resultado** da segmentação.

---

## Rotulação (componentes conexos)

Objetivo: **contar regiões** (objetos) numa imagem binária, dando o mesmo **rótulo** a pixels do mesmo componente conexo.

### Algoritmo (2 passadas, varredura esquerda→direita, cima→baixo)

Índices (visão da vizinhança de `P`):

```
Q R S
T P
```

Para cada pixel `P`:
- `P = 0` → nada.
- `P = 1`, examine `R` (de cima) e `T` (à esquerda) — já rotulados:
  1. `R = 0` e `T = 0` → `rotulo(P) = novo rótulo`;
  2. `R = 1` **ou** `T = 1` → `rotulo(P) = rotulo(R ou T)`;
  3. `R = 1` e `T = 1` com **mesmo rótulo** → `rotulo(P) = rotulo(R)`;
  4. `R = 1` e `T = 1` com **rótulos diferentes** → atribui um deles a P e **anota a equivalência** entre os dois.

**Pós-processamento:** agrupar os rótulos equivalentes em **classes de equivalência** e **re-rotular** a imagem substituindo cada rótulo pelo rótulo da sua classe.

### Demonstração do slide

Primeira passada produziu os pares equivalentes `(1,2), (3,4), (1,5)`:

```
1           1
1           1       2   2
1   1   1   1   3   3   3   3
    1   1           3       3
4   1               3   3   3
4
```

Classes de equivalência: `{1, 2, 5} → rótulo 1` e `{3, 4} → rótulo 4`:

```
1           1
1           1       4   4
1   1   1   1   4   4   4   4
    1   1           4       4
1   1               4   4   4
1
```

Resultado: **duas regiões** (rótulos 1 e 4).

---

## Prática (Aula 03.2) — Flood Fill e Rotulagem

Projeto: `material/exercicios/PDI-Aula-03-2-proj/`.

### Flood Fill (preenchimento por inundação)

```cpp
void FloodFill(int x, int y, uchar rRef, uchar gRef,
               uchar bRef, bool visitado[][1000])
{
    unsigned char r, g, b;

    if (!Image->Inside(x, y))          // fora da imagem
        return;
    if (visitado[x][y])                // posição já visitada
        return;

    Image->ReadPixel(x, y, r, g, b);
    if (r != rRef || g != gRef || b != bRef)   // não é da mesma região
        return;

    visitado[x][y] = true;
    NovaImagem->DrawPixel(x, y, 0, 0, 0);      // marca a região

    // Visita os quatro vizinhos (4-conectividade)
    FloodFill(x + 1, y, rRef, gRef, bRef, visitado);
    FloodFill(x - 1, y, rRef, gRef, bRef, visitado);
    FloodFill(x, y + 1, rRef, gRef, bRef, visitado);
    FloodFill(x, y - 1, rRef, gRef, bRef, visitado);
}

void ComponenteConexo(int xInicial, int yInicial) {
    unsigned char r, g, b;
    Image->ReadPixel(xInicial, yInicial, r, g, b);
    bool visitado[1000][1000] = { false };
    FloodFill(xInicial, yInicial, r, g, b, visitado);
}
```

### Rotulagem (contar componentes via FloodFill)

```cpp
void RotularComponentes() {
    int x, y;  unsigned char r, g, b;
    int proxRotulo = 0;
    for (x = 0; x < Image->getSizeX(); x++)
       for (y = 0; y < Image->getSizeY(); y++)
          rotulo[x][y] = 0;

    for (x = 0; x < Image->getSizeX(); x++)
       for (y = 0; y < Image->getSizeY(); y++) {
          Image->ReadPixel(x, y, r, g, b);
          if (r > 0) {                       // pixel de objeto
             if (rotulo[x][y] == 0) {        // ainda não rotulado
                proxRotulo++;
                FloodFillRotulo(x, y, proxRotulo, rotulo);
             }
          }
       }
}

void FloodFillRotulo(int x, int y, int rotuloAtual, int **rotulo) {
    unsigned char r, g, b;
    if (!Image->Inside(x, y))  return;
    if (rotulo[x][y])          return;       // já rotulado
    Image->ReadPixel(x, y, r, g, b);
    if (r == 255)              return;       // é fundo
    rotulo[x][y] = rotuloAtual;
    FloodFillRotulo(x + 1, y, rotuloAtual, rotulo);
    FloodFillRotulo(x - 1, y, rotuloAtual, rotulo);
    FloodFillRotulo(x, y + 1, rotuloAtual, rotulo);
    FloodFillRotulo(x, y - 1, rotuloAtual, rotulo);
}
```

---

## Exercícios resolvidos

### 1. Rotulação (imagem com Sc = {1} do slide)

Usa o **algoritmo de 2 passadas** (regras acima). Primeira passada gera rótulos locais e pares equivalentes (ex.: `(1,2), (3,4), (1,5)`); segunda passada resolve as classes de equivalência e recolore a imagem. No slide, a mesma matriz com Adj-8 dá **4 regiões** e com Adj-4 dá **10 regiões**.

### 2. Como adaptar o algoritmo para componentes 8-conexas?

Além de `R` (cima) e `T` (esquerda), examinar também os **diagonais já rotulados** pela varredura: `Q` (cima-esquerda) e `S` (cima-direita). Se algum deles valer 1, `P` herda o rótulo; se dois vizinhos rotulados tiverem rótulos **diferentes**, registrar a equivalência (mesma regra 4) e resolver no pós-processamento.

### 3. A4, A8 e Am da imagem 7×7

```
1 0 0 0 0 1 0
1 1 0 0 0 1 1
1 1 1 0 1 1 0
0 1 1 1 1 1 0
0 1 1 0 0 1 1
1 0 0 1 1 0 0
0 1 0 0 1 0 0
```

| Relação | Componentes | Observações |
|---------|:-----------:|-------------|
| **A4** | **4** | C1 grande (20 px, unido pela ponte horizontal (3,2)–(3,3)); + {(5,0)}; + {(6,1)}; + {(5,3),(5,4),(6,4)} |
| **A8** | **1** | as diagonais (4,1)–(5,0), (4,2)–(5,3) e (4,5)–(5,4) unem tudo |
| **Am** | **4** | as diagonais acima são **barradas** (N4 dos pares têm interseção não vazia); as 4-conexões internas sobrevivem |

> Moral: A8 "gruda" regiões que A4 separa; Am elimina as diagonais ambíguas (que compartilham vizinho-4), ficando com o mesmo número de componentes que A4 nesse caso.

### 4. S1 e S2 conectados (V = {1})?

Requer a figura do slide. Método: localizar todos os pixels de S1 e S2 e verificar se existe **caminho digital** até S2:
- **4-conectados:** só caminhos na cruz;
- **8-conectados:** cruz + diagonais;
- **m-conectados:** 4-adjacências + diagonais sem vizinho-4 comum.

(No exemplo clássico do Gonzalez, S1 e S2 **não** são 4-conectados, mas **são** 8- e m-conectados por uma ligação diagonal única.)

### Prática (Aula 03.2)

1. **Aumentar o limiar do FloodFill para cores bem próximas:** trocar a igualdade exata por tolerância, ex.: `if (abs(r - rRef) > LIMIAR || abs(g - gRef) > LIMIAR || abs(b - bRef) > LIMIAR) return;`
2. **FloodFill com conectividade-8:** adicionar as 4 chamadas diagonais (`x+1,y+1`; `x+1,y−1`; `x−1,y+1`; `x−1,y−1`).
3. **Imagem onde cada região tem cor diferente:** no `RotularComponentes`, usar `proxRotulo` (ou `rotulo[x][y]`) para escolher a cor: ex. `NovaImagem->DrawPixel(x, y, (rotulo*80)%256, (rotulo*160)%256, (rotulo*40)%256)` ou uma tabela de cores cíclica.

---

## Referências cruzadas

- A imagem como matriz de pixels, quantização de tons → [Aula 02.1](estudo-aula02-1-imagens-conceitos-e-representacao.md)
- Algoritmos de varredura de pixels (ReadPixel/DrawPixel) → [Aula 02.2](estudo-aula02-2-amostragem-e-quantizacao-na-pratica.md)