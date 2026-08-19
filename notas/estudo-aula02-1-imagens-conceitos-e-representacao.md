# Aula 02.1 — Imagens: conceitos, representação e armazenamento

**Disciplina:** Processamento Digital de Imagens e Computação Gráfica (Prof. Diógenes Furlan)
**Slide de referência:** `material/slides/PDI26-02-1-Imagens.pdf`

Parte inicial da **digitalização de imagens**: o que é uma imagem, como representá-la e quanto espaço ela ocupa. Continua na [Aula 02.2 (algoritmos de amostragem/quantização)](estudo-aula02-2-amostragem-e-quantizacao-na-pratica.md).

---

## Conceitos iniciais

**Níveis de abstração** (do mundo real ao computador):

| Nível | O que representa |
|-------|------------------|
| **Físico** | a imagem física (cena, fotografia) |
| **Matemático** | a representação da imagem (função) |
| **Computacional** | estrutura de dados + algoritmos |

- **Vídeo** = imagem que varia ao longo do tempo → dimensão extra: **tempo** (ex.: sequência de imagens, animação).
- **Tipos de imagem:** natural (outdoors/indoors) × artificial (pinturas, computacionais); 2D (fotograma) × 3D (vídeo, tomografia computadorizada).

## Níveis de percepção (David Marr)

| Nível | Conteúdo | Processamento associado |
|-------|----------|--------------------------|
| **Baixo** (dado bruto) | pixels | extração de bordas, análise de textura |
| **Intermediário** (estrutural) | bordas, texturas | — |
| **Alto** (cognitivo) | regiões, objetos | segmentação, reconhecimento de padrões |

## Definição de imagem

- Representação **visual** de um objeto. Etimologia: latim *imago*, grego *eidos* ("ideia"); Platão → idealismo, Aristóteles → realismo.
- Matematicamente é uma "redução do mundo real": `ImgR: ℝ⁴ → ℝ²`.
- **Luz é energia** ⇒ a imagem deve ser **finita e positiva** (intensidade ≥ 0).
- **Imagem digital** `f(x,y)`: U → C, com U ⊆ ℕ² (coordenadas discretas) e C espaço vetorial de cores → discretizada **em coordenadas espaciais e em brilho**.

## Aquisição — geração de imagens

A imagem é formada pela luz refletida pelos objetos, com dois componentes:

```
fa(x,y) = i(x,y) · r(x,y)
0 < i(x,y) < ∞   (iluminação incidindo na cena)
0 < r(x,y) < 1   (refletância do material)
```

| Iluminação (**lux**) | i(x,y) | Material | r(x,y) (adimensional) |
|----------------------|--------|----------|--------|
| Dia de sol | 9.000 | Neve | 0,93 |
| Dia nublado | < 1.000 | Lâmina de prata | 0,90 |
| Escritório | 100 | Parede branca | 0,80 |
| Noite de lua cheia | 0,01 | Aço inoxidável | 0,65 |
| | | Veludo negro | 0,01 |

> **Correção do slide:** a unidade de `i(x,y)` é **lux (lx)** — iluminância = fluxo luminoso por área — e não *candela* (que é a unidade de **intensidade luminosa**, outro conceito). Já `r(x,y)` é **adimensional** (razão entre 0 e 1), e não candela. Os valores numéricos (sol ~9.000 lx, lua cheia ~0,01 lx, neve ~0,93 de refletância) são os do livro de Gonzalez & Woods.

---

## Representação de imagens

### Vetorial (usada em Computação Gráfica)

- Objeto descrito por **vetores/equações** (segmentos de reta orientados: direção, sentido, comprimento).
- **Redimensionável SEM perda de qualidade** (zoom eficiente).
- Serve para modelar objetos sintéticos (CG), não fotos.

### Matricial / Raster

- **Matriz** de pixels ("picture element"): índices de linha/coluna identificam um ponto.
- **Redimensionável COM perda de qualidade** (cada pixel é uma célula).

```
1 0 1
0 0 1
0 1 1
```

### Comparativo de extensões

| Raster (matricial) | Vetorial |
|--------------------|----------|
| BMP, PNG, GIF, JPG, TIFF, RAW, ICO | SVG, CDR, EPS, PDF, CGM, DXF, DPX, DWG, AI |

- **Vetorização:** raster → vetorial (ex.: auto-trace)
- **Rasterização:** vetorial → raster (ex.: projeção na tela)

### SVG (Scalable Vector Graphics)

- Gráfico **vetorial escalável**: linhas, polígonos, figuras, texto, filtros, efeitos.
- Armazena a **equação** dos gráficos (não um mapa de pixels) → mesmo arquivo cabe grande ou pequeno, sem perda.
- **É XML**: namespace `http://www.w3.org/2000/svg`, editável como texto, estilizável com CSS, animável, embutível em HTML.

```xml
<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="100%" height="100%">
  <circle r="50" cx="100" cy="100" fill="green"/>
</svg>
```

---

## Digitalização: Amostragem × Quantização

| Operação | O que digitaliza | Determina |
|----------|------------------|-----------|
| **Amostragem** | coordenadas espaciais (x,y) da função | **resolução** / número de pixels |
| **Quantização** | amplitude (brilho) | **número de cores** / tons |

**Degradação por amostragem:** reduzir a resolução (ex.: 600 → 300 → 150 → 75 → 38 → 19 → 10 dpi) degrada progressivamente os detalhes.
**Degradação por quantização:** reduzir o número de cores (24 bits → 256 → 16 → 2 cores) cria "bandeamento" e perda de suavidade.

## Tipos de imagem quanto à cor

| Tipo | Função | Bits/pixel | Valores |
|------|--------|:----------:|---------|
| **Preto e branco** | f_PB: ℤ² → {0,1} | 1 | 0/1 (ou 0/255) — ocupa pouco espaço |
| **Monocromática** (tons de cinza) | f_M: ℤ² → K, K=[0..k-1] | 8 | 0–255 (256 tons) |
| **Colorida (RGB)** | f_C: ℤ² → K₁×K₂×K₃ | 24 | 256×256×256 = 16.777.216 cores (True Color) |

A colorida RGB pode ser vista como **3 imagens monocromáticas** sobrepostas:

```
fC(x,y) = fR(x,y) + fG(x,y) + fB(x,y)
```

## Armazenamento — tamanho da imagem

```
tamanho = L × C (pixels) × bytes por pixel
```

| Tipo | bytes/pixel |
|------|:-----------:|
| Preto e branco | 1 bit |
| Monocromática (256 tons de cinza) | 8 bits = 1 byte |
| True color | 24 bits = 3 bytes |

**Exemplos do slide:**
- 160 × 160 colorida → 25.600 px × 3 B = **76.800 B ≈ 76 KB**
- 800 × 600 preto e branco → 480.000 bits ÷ 8 = **60.000 B = 60 KB**

---

## Exercícios resolvidos

### 1. Quantos bytes para armazenar…

| Item | Cálculo | Resultado |
|------|---------|-----------|
| a) 32 × 24, true color | 32×24×3 | **2.304 bytes** |
| b) 128 × 128, 64 níveis de cinza | 128×128 = 16.384 px; 64 níveis = 6 bits/px → 16.384×6 = 98.304 bits | **12.288 bytes** (mínimo, com empacotamento; 16.384 B se usar 1 byte/px) |
| c) 1024 × 768, preto e branco | 1024×768 = 786.432 px = 786.432 bits | **98.304 bytes = 96 KB** |

### 2. Maior imagem em 1 Megabyte (1 MB = 2²⁰ = 1.048.576 bytes)

| Tipo | bytes/px | pixels possíveis | maior quadrado |
|------|:--------:|-----------------:|----------------|
| a) True color | 3 | 349.525 | **591 × 591** (349.281 px) |
| b) 256 cores | 1 | 1.048.576 | **1024 × 1024** (cabe exato!) |
| c) Preto e branco | 1/8 | 8.388.608 | **2896 × 2896** (8.386.816 px) |

> Se usar a convenção comercial 1 MB = 10⁶ bytes: true color → 577×577; 256 cores → 1000×1000; PB → 2828×2828.

### 3. Logo estilo Microsoft em SVG

```xml
<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="100" height="100">
  <rect x="10" y="10" width="35" height="35" fill="#F25022"/>
  <rect x="55" y="10" width="35" height="35" fill="#7FBA00"/>
  <rect x="10" y="55" width="35" height="35" fill="#00A4EF"/>
  <rect x="55" y="55" width="35" height="35" fill="#FFB900"/>
</svg>
```

### 4–6. Práticos (Paint)

- Baixar imagem HD/Full HD (BMP/PNG), anotar o tamanho em bytes e **dividir a resolução por 2** sucessivamente até ~32×24, anotando e comparando os tamanhos (cada divisão por 2 reduz o arquivo ~4×).
- Observar visualmente: **em qual resolução a imagem perde nitidez?**
- Repetir com imagem em tons de cinza (perde-se também o fator de cor, só sobra o fator espacial).

---

## Referências cruzadas

- Algoritmos de digitalização na prática (ZoomOut, Thumbnail, tons de cinza, limiar) → [Aula 02.2](estudo-aula02-2-amostragem-e-quantizacao-na-pratica.md)
- Relações entre pixels (vizinhança, conectividade, rotulação) → [Aula 03](estudo-aula03-vizinhanca-conectividade-e-rotulacao.md)