# Aula 07 — Filtragem Espacial

**Disciplina:** Processamento Digital de Imagens e Computação Gráfica (Prof. Diógenes Furlan)  
**Slide de referência:** `material/slides/PDI26-07-Filtragem Espacial.pdf`

Segue [operações em imagens (Aula 06)](estudo-aula06-operacoes-em-imagens.md). Aqui o foco é **operadores locais** (convolução / vizinhança).

---

## Sumário

- Filtros no domínio do espaço (operadores locais)
- Convolução: máscara, desloca / multiplica / soma
- Borda: aperiódica, gabarito truncado, periódica
- Suavização: passa-baixas, média, média ponderada, Gaussiano, mediana, moda
- Realce: passa-altas e direcionais
- Detectores de borda: Roberts, Sobel, Prewitt, Canny
- Laplaciano e LoG
- Exercícios

---

## 1. Ideia central

Filtros espaciais = **operadores locais**: o pixel de saída combina intensidades de uma **janela** (máscara / template / kernel) sobre a imagem.

Aplicações: pré-processamento, ruído, suavização, segmentação, realce, bordas.

---

## 2. Convolução (domínio do espaço)

Para máscara 3×3 com pesos `w1…w9` e vizinhança `a…i` de `f(x,y)`:

```
g(x,y) = w1·a + w2·b + w3·c + w4·d + w5·e + w6·f + w7·g + w8·h + w9·i
```

Processo: **desloca → multiplica → soma**.

### Convenções

| Máscara | Onde colocar o resultado |
|---------|---------------------------|
| Par (2×2, 4×4…) | sobre o **primeiro** pixel da janela |
| Ímpar (3×3, 5×5…) | sobre o pixel de **centro** |

### Tratamento de borda

| Modo | Ideia |
|------|--------|
| **Aperiódica** | posições não calculáveis → 0 (resultado pode “encolher”) |
| **Gabarito truncado** | centra no 1º pixel; fora da imagem = 0 |
| **Periódica** | imagem como se as bordas fossem adjacentes (torus) |

### Custo

Imagem `M×M`, máscara `N×N` → ~ `M² N²` multiplicações.  
Ex.: 512×512 com 16×16 ≈ 67 milhões. Alternativa: domínio da frequência (Fourier), em geral só vale a pena com máscara grande (slide: > ~32×32).

---

## 3. Filtros de suavização (passa-baixas)

- Atenuam altas frequências (transições abruptas) → **borramento**, menos ruído.
- Máscara de **média**: coeficientes ≥ 0 e **soma = 1** (ex.: 3×3 com 1/9).
- Máscara maior → mais borramento.
- **Média ponderada:** pesos maiores perto do centro.
- **Gaussiano:** passa-baixas mais importante (aproximações 3×3, 5×5…).
- **Mediana (não linear):** ordena a vizinhança e pega o valor central — bom contra ruído impulsivo (“sal e pimenta”); **não** é convolução clássica.
- **Moda:** valor mais frequente da vizinhança.

---

## 4. Filtros de realce (passa-altas)

- **Agudização (sharpening):** transições ficam mais nítidas.
- Exemplo clássico 3×3 (centro positivo, vizinhos negativos), ex.:

```
 0  -1   0
-1   5  -1
 0  -1   0
```

- **Passa-altas direcionais:** realçam bordas/linhas em direções preferenciais.

---

## 5. Detectores de bordas

| Operador | Ideia rápida |
|----------|----------------|
| **Roberts** | mais antigo/simples; gradiente cruzado 2×2; sensível a ruído |
| **Sobel** | máscaras 3×3 em X e Y; menos sensível a ruído que Roberts |
| **Prewitt** | semelhante ao Sobel; aproxima derivada; borda onde gradiente é máximo |
| **Canny** | Gaussiano + gradiente; dois limiares (bordas fortes/fracas); inclui fracas só se ligadas a fortes |

Também: **Laplaciano** (2ª derivada) e **LoG** (Laplaciano do Gaussiano).

---

## 6. Exercícios do slide

1. Implementar algoritmos: **Roberts**, **Sobel**, **Prewitt**
2. Pesquisar operadores adicionais pedidos no PDF (ex.: Canny / Laplaciano / LoG conforme enunciado da aula)

---

## Mapa mental

```
Filtragem espacial
├── Convolução (máscara)
│   ├── borda: aperiódica / truncada / periódica
│   └── custo alto → Fourier se N grande
├── Suavização (passa-baixa / mediana / moda)
├── Realce (passa-alta / direcional)
└── Bordas (Roberts, Sobel, Prewitt, Canny, Laplaciano, LoG)
```

---

- Anterior → [Aula 06 — Operações em imagens](estudo-aula06-operacoes-em-imagens.md)  
- Relacionado → [Aula 03 — Vizinhança](estudo-aula03-vizinhanca-conectividade-e-rotulacao.md) · [Aula 04 — Distância](estudo-aula04-distancia.md)
