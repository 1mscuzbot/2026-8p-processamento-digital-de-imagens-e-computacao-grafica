# Aula 06 — Operações em Imagens

**Disciplina:** Processamento Digital de Imagens e Computação Gráfica (Prof. Diógenes Furlan)  
**Slide de referência:** `material/slides/PDI26-06-Operacoes Imagens.pdf`

Continua as aulas de realce/processamento ponto a ponto após [histograma (Aula 05)](estudo-aula05-histogramas.md). Próxima: [filtragem espacial (Aula 07)](estudo-aula07-filtragem-espacial.md).

---

## Sumário

- Classificações de operações (área, nº de imagens, tipo, coloração)
- Filtros pontuais em coloridas: negativo, posterize, sépia, solarize
- Operadores aritméticos (soma, subtração, multiplicação/divisão)
- Overflow/underflow e correção
- Operadores lógicos (AND, OR, NOT) + exercícios XOR/NAND/NOR

---

## 1. Classificações

### Quanto à área

| Tipo | Ideia |
|------|--------|
| **Pontual** | saída em `(x,y)` depende só do pixel original em `(x,y)` |
| **Região** | depende de uma **janela**/vizinhança |
| **Imagem inteira** | usa a imagem toda (ex.: equalização global) |

### Quanto ao número de imagens

| Tipo | Exemplo |
|------|---------|
| Unária | inversão / negativo |
| Binária | soma de duas imagens |
| Múltiplas | contornos em volumes 3D |

### Quanto ao tipo

Aritmética · Geométrica · Booleana · Convolução · Linear · Não linear · Morfológica

### Quanto à coloração

| Tipo | Exemplo |
|------|---------|
| B&W (2 cores) | negação lógica |
| Tons de cinza (256) | filtro sépia |
| Coloridas (~16 mi) | posterize |

---

## 2. Operações pontuais em coloridas

### Negativo

```
r = 255 - r;  g = 255 - g;  b = 255 - b;
```

### Posterize (reduz tons)

Ex.: quantizar em blocos de 64:

```
r = (r/64)*64;  g = (g/64)*64;  b = (b/64)*64;
```

(ideia geral: agrupar faixas e mapear para um tom representativo do intervalo)

### Sépia (combinação linear + saturação)

```
nr = 0.393*r + 0.769*g + 0.189*b;
ng = 0.349*r + 0.686*g + 0.168*b;
nb = 0.272*r + 0.534*g + 0.131*b;
// saturar em 255
```

### Solarize

Inverte só as áreas claras (limiar típico 128):

```
if (r > 128) r = 255 - r;  // idem g, b
```

---

## 3. Operadores aritméticos

| Operação | Uso típico |
|----------|------------|
| **Soma** (pixel a pixel) | média de frames → reduzir ruído |
| **Subtração** | realçar diferenças |
| **Multiplicação / divisão** | correção de sombreamento; mascaramento |

Em cinza: soma, subtração e multiplicação. Em colorida (slide): foco em soma e subtração por canal.

### Overflow / underflow (cinza 0–255)

- Soma pode ir a 510; subtração pode ficar negativa.
- Correções:
  - **Truncar:** >255 → 255; <0 → 0
  - **Reescalonar:** mapear faixa resultante para 0–255

---

## 4. Operadores lógicos (imagens binárias)

| Op | Regra (slide) |
|----|----------------|
| **AND** | branco ∧ branco → branco; resto → preto |
| **OR** | preto ∨ preto → preto; resto → branco |
| **NOT** | branco ↔ preto |

**Exercícios do slide:** implementar **XOR**, **NAND**, **NOR**.

---

## Checklist rápido

- [ ] Diferenciar pontual × região × imagem inteira
- [ ] Codificar negativo / posterize / sépia / solarize
- [ ] Explicar soma (ruído) e subtração (diferença)
- [ ] Tratar overflow na soma
- [ ] AND / OR / NOT + XOR

---

- Anterior → [Aula 05 — Histogramas](estudo-aula05-histogramas.md)  
- Próxima → [Aula 07 — Filtragem espacial](estudo-aula07-filtragem-espacial.md)
