# Aula 05 — Histogramas

**Disciplina:** Processamento Digital de Imagens e Computação Gráfica (Prof. Diógenes Furlan)
**Slides de referência:**
- `material/slides/PDI26-05-Histogramas.pdf`

---

## Sumário

- Definição de histograma
- Análise de histogramas (brilho, contraste)
- Histograma de imagens coloridas
- Operações sobre histograma: normalização, expansão de contraste, equalização
- Exercícios práticos (algoritmos em C)

---

## 1. Definição

O **histograma** de uma imagem mostra **quantos pixels existem para cada nível de intensidade**.

- Para uma imagem em tons de cinza de 8 bits: intensidades de 0 a 255.
- **Imagem** → informação **espacial** (onde os pixels estão)
- **Histograma** → informação **estatística** (distribuição das intensidades)

> Duas imagens completamente diferentes podem ter **exatamente o mesmo histograma**.

### Imagens coloridas

Cada canal (R, G, B) possui seu próprio histograma.

---

## 2. Análise de Histogramas

| Tipo de imagem | Posição no histograma |
|---|---|
| **Escura** | Pico concentrado à esquerda (intensidades baixas) |
| **Intermediária** | Pico no centro |
| **Clara** | Pico concentrado à direita (intensidades altas) |

### Contraste

- **Baixo contraste** → pixels concentrados em faixa estreita
- **Alto contraste** → pixels distribuídos em faixa ampla (0–255)

---

## 3. Histograma Normalizado

Se o nível de cinza `k` ocorre `nk` vezes em uma imagem com `N` pixels:

```
p(k) = nk / N
```

Onde `N = L × C` (largura × altura).

---

## 4. Expansão de Contraste (Contrast Stretching)

Se os pixels ocupam apenas a faixa `[rmin, rmax]`, podemos expandi-los para `[0, 255]`:

```
saida = (entrada - rmin) × 255 / (rmax - rmin)
```

**Exemplo:** pixels entre 50 e 180 → expandidos para 0–255.

---

## 5. Equalização de Histograma

Técnica que procura **aumentar a uniformidade** da distribuição dos níveis de cinza.

- Útil para **realçar diferenças de tonalidade**
- Aumenta o nível de **detalhes perceptíveis**

### Algoritmo (baseado na CDF — Função de Distribuição Acumulada)

1. Calcular histograma `H[k]` para k = 0…R-1
2. Calcular CDF: `CDF[k] = Σ H[j]` para j = 0…k
3. Transformação: `saida[k] = round(CDF[k] × (R-1) / N)`

### Exemplo (64×64, R=8 níveis)

| r | nk | CDF | s = round(CDF × 7 / 4096) |
|---|-----|-----|---------------------------|
| 0 | 790 | 790 | 1 |
| 1 | 1023 | 1813 | 3 |
| 2 | 850 | 2663 | 5 |
| 3 | 656 | 3319 | 6 |
| 4 | 329 | 3648 | 6 |
| 5 | 245 | 3893 | 7 |
| 6 | 122 | 4015 | 7 |
| 7 | 81 | 4096 | 7 |

---

## 6. Algoritmos (C)

### Exercício 1 — Histograma

```c
int histograma[256] = {0};

for (i = 0; i < altura; i++)
    for (j = 0; j < largura; j++)
        histograma[imagem[i][j]]++;
```

### Exercício 2 — Histograma Normalizado

```c
int HN[256];
N = altura * largura;

for (i = 0; i < 256; i++)
    HN[i] = (float)histograma[i] / N;
```

### Exercício 3 — Encontrar mínimo e máximo

```c
int rmin = 255, rmax = 0;
for (i = 0; i < 256; i++) {
    if (histograma[i] > 0) {
        if (i < rmin) rmin = i;
        if (i > rmax) rmax = i;
    }
}
```

### Exercício 4 — Contrast Stretching

```c
for (i = 0; i < altura; i++)
    for (j = 0; j < largura; j++)
        nova[i][j] = (imagem[i][j] - rmin) * 255 / (rmax - rmin);
```

### Exercício 5 — Equalização

```c
// 1. Histograma
int H[256] = {0};
for (i = 0; i < altura; i++)
    for (j = 0; j < largura; j++)
        H[imagem[i][j]]++;

// 2. CDF
float CDF[256];
CDF[0] = H[0];
for (k = 1; k < 256; k++)
    CDF[k] = CDF[k-1] + H[k];

// 3. Transformação
int N = altura * largura;
for (i = 0; i < altura; i++)
    for (j = 0; j < largura; j++)
        nova[i][j] = round(CDF[imagem[i][j]] * 255.0 / N);
```

---

## Resumo das operações

| Operação | Objetó | Fórmula |
|----------|--------|---------|
| Normalização | Probabilidade de cada intensidade | `p(k) = nk / N` |
| Expansão de contraste | Usar faixa total 0–255 | `s = (r - rmin) × 255 / (rmax - rmin)` |
| Equalização | Uniformizar distribuição | `s = round(CDF(r) × (R-1) / N)` |
