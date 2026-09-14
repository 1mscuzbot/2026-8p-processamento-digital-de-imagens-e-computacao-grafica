# Aula 08 — Processamento morfológico

**Disciplina:** Processamento Digital de Imagens e Computação Gráfica (Prof. Diógenes Furlan)  
**Slide de referência:** `material/slides/PDI26-08-Processamento Morfologico.pdf`

Fecha o bloco de **morfologia matemática** da ementa do 1º bimestre (depois de filtragem espacial).

---

## Sumário

- Morfologia = estudo da forma; em imagens: extrair/descrever objetos
- Base: teoria dos conjuntos (imagem binária ⊂ ℤ²)
- Elemento estruturante (B)
- Translação, reflexão, complemento, diferença
- **Erosão** e **dilatação** (operações básicas)
- **Abertura** e **fechamento** (composições)

---

## 1. Ideia central

**Morfologia matemática:** obter informação de geometria/topologia de um conjunto desconhecido **A** transformando-o com um conjunto bem definido **B** — o **elemento estruturante**.

Começou em imagens **binárias**; depois estendeu-se a tons de cinza. Pixel 1 = objeto, 0 = fundo (nos exemplos do slide).

### Elemento estruturante

Máscara pequena com:

| Símbolo no slide | Significado |
|------------------|-------------|
| 1 | deve “bater” / valor 1 |
| 0 | valor 0 |
| “não importa” | posição ignorada |
| centro (origem) | ponto de referência de B |

Exemplos típicos: cruz 3×3, “X”, linha horizontal, etc.

---

## 2. Definições básicas (conjuntos)

| Operação | Ideia |
|----------|--------|
| **Translação** de A por x | `(A)_x = { a + x \| a ∈ A }` |
| **Reflexão** de B | `B̂ = { −b \| b ∈ B }` (espelha em torno da origem) |
| **Complemento** de A | `Aᶜ = { w \| w ∉ A }` |
| **Diferença** A − B | `{ w \| w ∈ A e w ∉ B } = A ∩ Bᶜ` |

---

## 3. Erosão e dilatação (binárias)

São as duas operações **básicas**; quase tudo o mais é combinação delas.

### Erosão — `A ⊖ B`

```
A ⊖ B = { x | (B)_x ⊆ A }
```

- Conjunto dos x tais que B transladado por x **está contido** em A.
- Na prática: passe B pela imagem; se **nenhum** pixel sob os 1s de B for 0 → escreva 1 (efeito tipo **AND**).
- **Efeito:** contrai / diminui o objeto (remove bordas, apaga detalhes menores que B).

### Dilatação — `A ⊕ B`

```
A ⊕ B = { x | (B̂)_x ∩ A ≠ ∅ }
```

- Reflete B, translada por x; x entra no resultado se a reflexão **intersecta** A.
- Na prática: se o pixel sob o **centro** de B ≠ 0, copie os 1s de B para o resultado (efeito tipo **OR**).
- **Efeito:** expande / aumenta o objeto (preenche buracos pequenos, engrossa).

### Dualidade

```
(A ⊖ B)ᶜ = Aᶜ ⊕ B̂
```

O complemento de uma erosão = dilatação do complemento pelo B refletido.

---

## 4. Abertura e fechamento

| Operação | Fórmula | Efeitos típicos |
|----------|---------|-----------------|
| **Abertura** | `A ∘ B = (A ⊖ B) ⊕ B` | suaviza contorno; quebra istmos estreitos; elimina “pontas” delgadas; “abre” buracos |
| **Fechamento** | `A • B = (A ⊕ B) ⊖ B` | funde quebras pequenas; alarga golfos estreitos; fecha buracos e “baías” |

Ordem importa: abertura = **erosão depois dilatação**; fechamento = **dilatação depois erosão** (mesmo B).

---

## Mapa mental

```
Morfologia (binária)
├── Elemento estruturante B
├── Erosão   A ⊖ B  → encolhe (AND)
├── Dilatação A ⊕ B → cresce (OR)
└── Compostas
    ├── Abertura   (⊖ depois ⊕) → limpa “pontas”
    └── Fechamento (⊕ depois ⊖) → fecha buracos
```

---

## Para a prova (24/09)

Saber distinguir erosão × dilatação × abertura × fechamento **pelo efeito visual** e pela ordem das operações; lembrar que o resultado depende do **formato** do elemento estruturante.

---

- Anterior → [Aula 07 — Filtragem espacial](estudo-aula07-filtragem-espacial.md)  
- Relacionado → [Aula 03 — Vizinhança/conectividade](estudo-aula03-vizinhanca-conectividade-e-rotulacao.md) · [Aula 04 — Distância / esqueleto](estudo-aula04-distancia.md)
