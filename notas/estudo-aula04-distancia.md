# Aula 04 — Relacionamentos entre Pixels (Medidas de Distância)

**Disciplina:** Processamento Digital de Imagens e Computação Gráfica (Prof. Diógenes Furlan)
**Slides de referência:**
- `material/slides/PDI26-04-Distancia.pdf`

---

## Sumário

- Definição de métrica / distância
- Distância Euclidiana
- Distância City-block (D4 / Manhattan)
- Distância Chessboard (D8 / Chebyshev)
- Distância de Minkowski
- Transformada de distância e esqueletonização
- Exercícios

---

## 1. Definição de Métrica

Para pixels `p`, `q` e `z` com coordenadas `(x,y)`, `(s,t)` e `(u,v)`, uma função `D` é uma **métrica** se:

| Propriedade | Significado |
|---|---|
| **Não negatividade** | `D(p,q) ≥ 0` e `D(p,q) = 0` sse `p = q` |
| **Simetria** | `D(p,q) = D(q,p)` (comutativa) |
| **Desigualdade triangular** | `D(p,q) ≤ D(p,z) + D(z,q)` (menor caminho) |

---

## 2. Distâncias

### Distância Euclidiana

```
De(p,q) = √[(x-s)² + (y-t)²]
```

- Conjunto `S = {q | De(p,q) ≤ r}` forma um **círculo** centrado em `p`.

### Distância City-block (D4 / Manhattan)

```
D4(p,q) = |x-s| + |y-t|
```

- Pixels com `D4 = 1` são os **vizinhos-de-4** de `(x,y)`.
- Conjunto `S = {q | D4(p,q) ≤ r}` forma um **diamante** centrado em `p`.

### Distância Chessboard (D8 / Chebyshev)

```
D8(p,q) = max(|x-s|, |y-t|)
```

- Pixels com `D8 = 1` são os **vizinhos-de-8** de `(x,y)`.
- Conjunto `S = {q | D8(p,q) ≤ r}` forma um **quadrado** centrado em `p`.

### Distância de Minkowski (generalização)

```
DM(a,b) = [(|x-s|^p + |y-t|^p)]^(1/p)
```

| Valor de p | Distância equivalente |
|---|---|
| p = 1 | Manhattan (City-block) |
| p = 2 | Euclidiana |
| p = ∞ | Chebyshev (Chessboard) |

---

## 3. Transformada de Distância

- Calcula um **campo escalar** que representa as **distâncias mínimas** entre o objeto e os pontos do espaço.
- Normalmente usada em **imagens binárias**.
- O resultado é uma imagem onde os níveis de cinza representam a menor distância de cada ponto ao contorno da forma.

### Algoritmo

1. Inicializar a distância de todo pixel branco para um valor alto.
2. Criar um **Conjunto de Contorno** com os pixels de fronteira.
3. Enquanto o conjunto não estiver vazio:
   - Remover um pixel central do conjunto.
   - Para cada vizinho branco do pixel central:
     - Calcular nova distância baseada na distância do central.
     - Se a nova distância for menor que a corrente:
       - Atualizar a distância.
       - Adicionar o vizinho ao Conjunto de Contorno.

---

## 4. Esqueletonização (Thinning)

O **esqueleto** de uma forma é obtido via transformada de distância.

### Analogia (fogo)

Imagine uma região cujo material pega fogo uniformemente:
1. Fogo começa em **todos os pontos do contorno** simultaneamente.
2. O fogo se alasta para o interior.
3. Quando fogo vindo de pontos diferentes se encontra, ele se apaga formando uma **linha**.
4. Esta linha é o **esqueleto**.

### Onde ocorre o esqueleto

Nas **regiões de singularidade** da transformada de distância: **cristas** e **descontinuidade de curvatura**.

### Utilidade do esqueleto

- Representação **simples e compacta** da forma.
- Preserva **características topológicas** e de tamanho da forma original.
- **Métricas diferentes** → esqueletos diferentes.

### Aplicações

- Classificação de **impressões digitais**
- Análise visual de **peças industriais**
- Reconhecimento de **caracteres**
- **Biomédica**: contagem/medição de partes de glóbulos brancos, análise de raio-X

---

## 5. Resumo das Distâncias

| Distância | Fórmula | Forma de S = {q | D(p,q) ≤ r} |
|---|---|---|
| Euclidiana (De) | `√[(x-s)² + (y-t)²]` | Círculo |
| City-block (D4) | `|x-s| + |y-t|` | Diamante |
| Chessboard (D8) | `max(|x-s|, |y-t|)` | Quadrado |
| Minkowski | `[(|x-s|^p + |y-t|^p)]^(1/p)` | Varia com p |

---

## Exercícios

1. Calcular distâncias (Euclidiana, D4, D8) entre pontos P, Q e R numa grade.
2. Calcular D4, D8 e Dm entre P e Q para diferentes conjuntos de valores.
3. Condições para que D4 entre dois pontos seja igual ao caminho-de-4 mais curto.
4. Encontrar esqueleto de imagens binárias usando D4 e D8.
