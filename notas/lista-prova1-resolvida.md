# Lista para Prova 1 — Resolvida

**Disciplina:** PDI e Computação Gráfica (Prof. Diógenes Furlan)  
**Arquivo:** `material/PDI26-10-ListaParaProva1.pdf`  
**Prova B1:** 24/09 (trabalho OpenGL 70% + prova conceitual 30%)

> Respostas para estudo. Em questões abertas, a redação na prova pode variar; o conteúdo abaixo cobre o que o professor costuma cobrar.

---

# Parte I — Conceituais

## Questão 1 — Pixel × resolução espacial

| Conceito | Definição | Influência prática |
|----------|-----------|-------------------|
| **Pixel** | Menor elemento da imagem digital (amostra de intensidade/cor em uma posição da grade) | Poucos bits por pixel → poucas cores/tons (ex.: 1 bit = P&B; 8 bits = 256 cinzas) |
| **Resolução espacial** | Densidade de amostras no plano (quantos pixels por unidade de comprimento / tamanho da grade M×N) | Baixa resolução → serrilhado, perda de detalhes finos (texto, bordas); alta → mais detalhes, arquivo maior |

**Exemplo:** uma foto de placa de carro com poucos pixels (baixa resolução espacial) fica ilegível mesmo com bom contraste; uma imagem 1 bit (pixel só 0/1) perde suavidade de tons mesmo em alta resolução espacial.

## Questão 2 — Operações pontuais

| Operação | Finalidade | Aplicação |
|----------|------------|-----------|
| **Negativo** | `g = L−1−f` (ex.: 255−f) — inverte claros/escuros | Negatoscópio / realçar detalhes em fundos escuros |
| **Limiarização** | Binariza: ≥T → um valor, &lt;T → outro | Separar objeto/fundo, OCR pré-processamento |
| **Equalização de histograma** | Redistribui intensidades para ocupar melhor a faixa dinâmica | Melhorar contraste em imagens “lavadas” ou escuras |
| **Correção gama** | `g = c·f^γ` — realça claros ou escuros de forma não linear | Ajuste de monitor/câmera; realce seletivo de faixas |

## Questão 3 — Histograma (análise qualitativa)

Sem a figura impressa no PDF (só o enunciado), o raciocínio padrão é:

| Item | Como ler o histograma |
|------|------------------------|
| **(a) Contraste** | Barras **concentradas** numa faixa estreita → **baixo** contraste; espalhadas do escuro ao claro → **alto** |
| **(b) Claros/escuros** | Pico à **esquerda** (baixos níveis) → maioria **escura**; pico à **direita** → maioria **clara** |
| **(c) Equalização** | Em baixo contraste / histograma apertado, equalizar **tende a melhorar** a visualização ao espalhar os tons; se já estiver bem distribuído, o ganho é pequeno |

Na prova: olhe o desenho e aplique essas três regras.

## Questão 4 — Ruídos e filtros

| Ruído | Aparência | Filtro mais indicado |
|-------|-----------|----------------------|
| **Sal e pimenta** | Pixels extremos brancos/pretos aleatórios | **Mediana** (não linear; remove impulsos sem borrar tanto) |
| **Gaussiano** | Granulação suave em todos os pixels | **Média** ou melhor **Gaussiano** (passa-baixa) |

## Questão 5 — Passa-baixa × passa-alta

| Filtro | Efeito | Aplicações |
|--------|--------|------------|
| **Passa-baixa** | Atenua altas frequências → **suaviza**, reduz ruído, borra | Pré-processamento; reduzir granulação; antes de limiarizar |
| **Passa-alta** | Realça altas frequências → **bordas/detalhes** | Agudização (*sharpening*); detecção de bordas (base de Sobel etc.) |

Exemplos: passa-baixa = média 3×3, Gaussiano; passa-alta = Laplaciano, máscara de realce com centro positivo e vizinhos negativos.

## Questão 6 — Muitos detalhes + bastante ruído

**Indicado inicialmente:** filtro **passa-baixa** (média/Gaussiano) ou **mediana** se o ruído for impulsivo.

**Justificativa:** detalhes finos são altas frequências; ruído também. Suavizar primeiro reduz o ruído para depois detectar bordas/segmentar. Começar com passa-alta realçaria o ruído junto com os detalhes.

## Questão 7 — Morfologia

| Operação | Finalidade |
|----------|------------|
| **Dilatação** | Expande o objeto; preenche pequenos buracos; engrossa |
| **Erosão** | Contrai o objeto; remove pontas/ruído pequeno |
| **Abertura** | Erosão + dilatação → remove pontas finas / objetos pequenos; suaviza contorno “por fora” |
| **Fechamento** | Dilatação + erosão → fecha buracos/baías pequenas; funde quebras |

## Questão 8 — Domínio espacial × frequência

| Domínio | Onde se opera | Exemplo |
|---------|---------------|---------|
| **Espacial** | Direto nos pixels / vizinhança | Convolução com máscara 3×3; limiar; morfologia |
| **Frequência** | Após transformada (Fourier etc.) | Filtro passa-baixa/alta multiplicando o espectro |

## Questão 9 — Por que a convolução é importante?

Porque implementa **filtros locais** (suavização, realce, bordas) de forma uniforme: cada pixel de saída é combinação ponderada da vizinhança. É a base da filtragem espacial e de vários detectores (Sobel, Laplaciano, etc.).

## Questão 10 — Segmentação × bordas × características

| Conceito | O que faz |
|----------|-----------|
| **Segmentação** | Particiona a imagem em regiões/objetos (ex.: limiar, regiões, watershed) |
| **Detecção de bordas** | Destaca **transições** de intensidade (contornos); não entrega objeto completo sozinha |
| **Extração de características** | Mede atributos das regiões/objetos (área, perímetro, momentos, textura…) para reconhecimento |

Fluxo típico: bordas/segmentação → objetos → características → classificação.

## Questão 11 — Gaussiano × média

O **Gaussiano** pondera mais o centro e menos os vizinhos distantes (aproxima um kernel suave). Isso reduz ruído **com menos borramento** e menos “anelamento” que a média uniforme, que trata todos os vizinhos iguais e borra mais as bordas.

---

# Parte II — Procedimentais

## Questão 12 — Negativo · `g = 255 − f`

Entrada:

```
 20  60 100
120 180 220
 10  90 255
```

Saída:

```
235 195 155
135  75  35
245 165   0
```

## Questão 13 — Limiar T = 100 (≥100 → 255, &lt;100 → 0)

Entrada:

```
 15 120 180
 80 130 220
200  40  90
```

Saída:

```
  0 255 255
  0 255 255
255   0   0
```

## Questão 14 — Filtro média 3×3 (só o centro)

Vizinhança completa:

```
 10  20  30
 40 200  60
 70  80  90
```

Soma = 600 → `600/9 = 66,66…`  
**Valor do centro ≈ 67** (arredondamento) ou **66** (truncamento). Na prova, indique a conta `600/9`.

## Questão 15 — Laplaciano (centro)

Máscara:

```
 0 -1  0
-1  4 -1
 0 -1  0
```

Centro = `4·100 + (−1)·(20+20+20+20) = 400 − 80 = 320`  
Em 8 bits costuma-se **clipar** para `[0,255]` → **255** (ou usar valor absoluto + normalização, conforme o enunciado em sala).

## Questão 16 — Sobel (qualitativo)

Imagem:

```
10  10  10
10 100 100
10 100 100
```

**(a)** Sim — há **borda vertical** (e um pouco em “canto”) entre a coluna esquerda (~10) e as colunas direita (~100).  
**(b)** Sim — Sobel tem máscaras Gx/Gy e responde forte a essa transição horizontal de intensidade.

## Questões 17–18 — Dilatação e erosão (elemento 3×3 de 1s)

**Q17 — Dilatação** da “haste” vertical de 1s: o objeto **engrossa** cerca de 1 pixel em todas as direções (vira um bloco mais largo/alto).

**Q18 — Erosão** do bloco 3×3 de 1s com EE 3×3: sobra tipicamente **só o pixel central** (ou um núcleo menor); a borda some.

*(Desenhe na prova a partir dessa ideia — o EE “cheio” 3×3 é agressivo.)*

## Questão 19 — Abertura e fechamento (qualitativo)

Imagem com retângulo de 1s e um **0 no meio** (buraco):

**(a) Abertura** (erosão→dilatação): remove pontas/ruídos pequenos; o buraco interno **tende a permanecer** ou até aumentar na erosão.  
**(b) Fechamento** (dilatação→erosão): **preenche o buraco** pequeno e suaviza reentrâncias.

## Questão 20 — Análise

Objeto grande em forma de “moldura” com um 1 isolado dentro:

**(a)** Remover objetos pequenos isolados → **abertura** (ou erosão).  
**(b)** Preencher buracos pequenos → **fechamento** (ou dilatação).  
**(c)** Bordas → **passa-alta / Sobel / Laplaciano**.

## Questão 21 — Vizinhança-4 e 8

X na posição marcada (linha do meio-superior da figura do PDF).

**(a) N4 de X:** cima, baixo, esquerda, direita.  
**(b) N8:** N4 + 4 diagonais.  
**(c)** Contando só pixels **de objeto (1)** na N8: no desenho do enunciado são **4** (esquerda, baixo-esquerda, baixo, baixo-direita) — confira no papel na hora da prova se o X bate com essa grade.

Grade usada:

```
0 0 0 0 0
0 1 X 0 0
0 1 1 1 0
0 0 1 0 0
0 0 0 0 0
```

- N4: (1,1)=1 e (2,2)=1  
- N8 objeto: (1,1), (2,1), (2,2), (2,3) → **4**

## Questão 22 — Adjacência

```
1 0 1
0 1 0
1 0 1
```

**(a) Adjacência-4:** os 1s só se tocam na **diagonal** → **5 objetos**.  
**(b) Adjacência-8:** diagonais conectam tudo ao centro → **1 objeto**.  
**(c)** Porque 8-adjacência inclui diagonais; 4 não.

## Questão 23 — Rotulação 4-conexa

Imagem:

```
0 1 1 0 0 0 1
0 1 0 0 1 1 1
0 0 0 0 0 1 0
1 1 0 0 0 0 0
1 0 0 1 1 0 0
```

**4 componentes** (exemplo de rótulos A–D):

| Componente | Pixels (lin,col) 0-index |
|------------|---------------------------|
| **A** | (0,1)(0,2)(1,1) |
| **B** | (0,6)(1,4)(1,5)(1,6)(2,5) |
| **C** | (3,0)(3,1)(4,0) |
| **D** | (4,3)(4,4) |

Matriz de rótulos (0 = fundo):

```
0 A A 0 0 0 B
0 A 0 0 B B B
0 0 0 0 0 B 0
C C 0 0 0 0 0
C 0 0 D D 0 0
```

## Questão 24 — Rotulação 8-conexa

Na **mesma** imagem, as quatro componentes **não se tocam nem na diagonal**.  
**(a)** Continuam **4** componentes.  
**(b)** **Nenhuma** fusão adicional neste exemplo.  
**(c)** Mesma matriz de rótulos da Q23.

> Se na prova a figura for outra, refaça o teste de vizinhança-8 entre bordas das regiões.

## Questão 25 — Distâncias · P=(2,3), Q=(7,6)

Δx = 5, Δy = 3

| Métrica | Fórmula | Valor |
|---------|---------|-------|
| **Euclidiana** | √(5²+3²) = √34 | **≈ 5,83** |
| **Manhattan (D4)** | \|5\|+\|3\| | **8** |
| **Chebyshev (D8)** | max(5,3) | **5** |

Comparação: Manhattan ≥ Euclidiana ≥ Chebyshev (aqui 8 ≥ 5,83 ≥ 5).

## Questão 26 — Distância ao fundo (objeto 5×5 de 1s em moldura 7×7)

**Manhattan até o fundo:**

```
0 0 0 0 0 0 0
0 1 1 1 1 1 0
0 1 2 2 2 1 0
0 1 2 3 2 1 0
0 1 2 2 2 1 0
0 1 1 1 1 1 0
0 0 0 0 0 0 0
```

**Chebyshev até o fundo:**

```
0 0 0 0 0 0 0
0 1 1 1 1 1 0
0 1 2 2 2 1 0
0 1 2 3 2 1 0
0 1 2 2 2 1 0
0 1 1 1 1 1 0
0 0 0 0 0 0 0
```

*(Neste retângulo alinhado aos eixos as duas coincidem.)*

## Questão 27 — Esqueletonização (“+”)

**(a)** Reduz o objeto à sua **estrutura medial** (eixo/esqueleto), preservando topologia de forma compacta.  
**(b)** Aproximadamente a **cruz central** (haste vertical + horizontal de 1 pixel de espessura).  
**(c)** Útil para reconhecer forma (letras, vasos, estradas) com menos pixels e comparar estrutura.

## Questão 28 — Translação Δx=+2, Δy=+1

Entrada:

```
0 0 0 0 0 0
0 1 1 0 0 0
0 1 1 0 0 0
0 0 0 0 0 0
```

Saída:

```
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 1 1 0
0 0 0 1 1 0
```

**(b)** `x′ = x + 2`, `y′ = y + 1`.

## Questão 29 — Rotação 90° sentido horário (centro da imagem)

Entrada 3×3:

```
1 0 0
1 1 1
0 0 0
```

**90° horário** (padrão: elemento `(i,j)` → `(j, N−1−i)`):

```
0 1 1
0 1 0
0 1 0
```

> A “dica” do PDF usa notação de coordenadas; o resultado visual acima é o da rotação horária usual. Confira com um exemplo 2×2 na prova se a dica do professor divergir.

## Questão 30 — Espelhamento

Entrada:

```
1 0 0 0
1 1 0 0
1 0 1 0
0 0 1 1
```

**(a) Horizontal** (esquerda ↔ direita):

```
0 0 0 1
0 0 1 1
0 1 0 1
1 1 0 0
```

**(b) Vertical** (cima ↔ baixo):

```
0 0 1 1
1 0 1 0
1 1 0 0
1 0 0 0
```

**Diferença:** horizontal inverte **colunas**; vertical inverte **linhas**.

---

## Mapa rápido pré-prova

```
Pontuais: negativo, limiar, histograma, gama
Filtros: média/Gauss/mediana × Laplaciano/Sobel
Morfologia: erosão/dilatação/abertura/fechamento
Geometria: translação, rotação 90°, espelho
Conectividade: 4 vs 8 (muda nº de objetos!)
Distâncias: Euclid / Manhattan / Chebyshev
```
