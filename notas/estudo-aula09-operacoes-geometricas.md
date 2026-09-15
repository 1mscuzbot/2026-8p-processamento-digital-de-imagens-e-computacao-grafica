# Aula 09 — Operações geométricas

**Disciplina:** Processamento Digital de Imagens e Computação Gráfica (Prof. Diógenes Furlan)  
**Slide de referência:** `material/slides/PDI26-09-Operacoes Geometricas.pdf`  
**Lista de prova:** `material/PDI26-10-ListaParaProva1.pdf` (questões 28–30 cobrem este tema)

---

## Ideia central

Operações geométricas **mudam a posição** da informação na imagem final:

```
(x, y) → (x′, y′)
```

Origem ≠ destino. Em 2D usa-se **coordenadas homogêneas** `[x y 1]` e matriz 3×3.

---

## Transformações (matriz 2D)

| Operação | Efeito | Matriz (forma do slide) |
|----------|--------|-------------------------|
| **Translação** | desloca por (tx, ty) | identidade com última linha/coluna carregando o deslocamento em coords. homogêneas |
| **Escala** | amplia/reduz (sx, sy) | diagonal com fatores de escala |
| **Espelhamento** | espelho H/V (sinais −1) | ex.: diag(−1, −1, 1) no exemplo do slide |
| **Rotação** | gira ângulo α | bloco `cos α` / `±sin α` |
| **Cisalhamento (distorção)** | “inclina” em X ou em Y | 1s na diagonal + fator fora da diagonal |

Ordem importa se combinar várias matrizes (composição).

### Lembretes práticos (lista de prova)

- **Translação** (Q28): `x′ = x + Δx`, `y′ = y + Δy` — pixels que saem da grade somem; entram fundo (0).
- **Rotação 90° horário** em imagem N×N (dica do PDF da lista): `(x, y) → (y, N−1−x)` (Q29).
- **Espelhamento** (Q30): horizontal ≠ vertical — cada um inverte um eixo.

---

## Exercícios do slide (implementar)

1. Translação  
2. Escala  
3. Rotação  
4. Distorção (cisalhamento)  
5. Espelhamento  

---

## Relação com a prova B1 (24/09)

A lista `PDI26-10-ListaParaProva1.pdf` mistura **todo o 1º bimestre**: pixel/resolução, histograma, ruídos, filtros, morfologia, convolução, vizinhança, rotulação, distâncias, esqueleto **e** geometria (28–30). Vale usar a lista como roteiro de revisão.

---

- Anterior → [Aula 08 — Morfologia](estudo-aula08-processamento-morfologico.md)
