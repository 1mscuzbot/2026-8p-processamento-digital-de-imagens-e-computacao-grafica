# PyCG26-03 — Animação

**Disciplina:** Processamento Digital de Imagens e Computação Gráfica (Prof. Diógenes Furlan)  
**Slide de referência:** `material/slides/2_BIMESTRE/PyCG26-03-1-Animacao.pdf`  
**Bloco:** Computação Gráfica — 2º bimestre (Aula 03-1)

---

## Ideia central

**Animação** = produzir cada fotograma individualmente (mudanças pequenas no modelo) e exibir a sequência em cadência alta o bastante para o olho “ver movimento contínuo” (fenômeno **phi**). Em geral, a partir de **~16 FPS**.

Pode ser por computação gráfica ou por fotografia de desenhos — o princípio da sequência de frames é o mesmo.

---

## Sumário

- O que é animação / ilusão de movimento (phi)
- **FPS** (frame rate) e valores típicos
- Modos de display OpenGL/GLUT: **single** vs **double** buffer
- Loop de animação com `glutTimerFunc` + `glutPostRedisplay`
- Exemplo: linhas aleatórias (single buffer)
- Exercícios (protetores de tela) → Estudo Dirigido

---

## 1. FPS (frame rate)

Frequência com que o dispositivo gera **quadros** consecutivos. Unidade: **FPS** (ou Hz em monitores). Também usado para comparar desempenho de GPU.

| Cadência | Uso típico (slide) |
|----------|--------------------|
| 24 FPS | filmes antigos |
| 30 FPS | jogos antigos |
| 48 FPS | filmes modernos |
| 60 FPS | jogos modernos |
| 120 FPS | UHD |

---

## 2. Modos de display (`glutInitDisplayMode`)

| Modo | Comportamento | No fim do `display()` |
|------|---------------|------------------------|
| **`GLUT_SINGLE` / `GL_SINGLE`** | desenha **direto** na tela | `glFlush()` |
| **`GLUT_DOUBLE` / `GL_DOUBLE`** | 2 buffers: um **visível**, outro **off-screen**; você renderiza no oculto e depois **troca** | `glutSwapBuffers()` |

Double buffering evita “piscar” / ver o frame sendo montado: o usuário só vê frames prontos.

---

## 3. Exemplo 1 — single buffer + timer

**Setup no `main`:**

```text
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
```

**No `display()`:**

1. `glClear(GL_COLOR_BUFFER_BIT)` no início (senão os desenhos se acumulam / sobreescrevem sem limpar)
2. desenhar (ex.: linhas aleatórias)
3. `glFlush()` no final

**Timer (reagenda o próximo frame):**

```python
def timer(valor):
    glutPostRedisplay()
    glutTimerFunc(300, timer, 1)  # 300 ms → ~3,3 FPS neste exemplo
```

**Desenho:** escolhe `(x1,y1)`, `(x2,y2)` e RGB aleatórios dentro do Ortho (`w`×`h`), `glBegin(GL_LINES)` … `glEnd()`.

Cor: `glColor3f(0.004*r, 0.004*g, 0.004*b)` com `r,g,b ∈ [0,255]` ≈ normalizar por 256.

---

## 4. O que estudar / praticar

1. Diferença **single vs double** e quando usar `glFlush` vs `glutSwapBuffers`.
2. Papel de `glutTimerFunc` + `glutPostRedisplay` no loop de animação (intervalo ↔ FPS aproximado).
3. Limpar o buffer (`glClear`) vs deixar rastros (efeito “protetor de tela”).
4. Exercícios do slide (vão no **Estudo Dirigido**):
   - Protetor com **triângulos** aleatórios (posição, tamanho, cor preenchida).
   - Protetor com **linha dançante**.

---

## Checklist rápido

- [ ] Explicar animação + fenômeno phi + por que ≥ ~16 FPS
- [ ] Listar cadências típicas (24 / 30 / 48 / 60 / 120)
- [ ] Contrastar single × double buffer
- [ ] Montar um loop mínimo com timer em PyOpenGL/GLUT
- [ ] Fazer os 2 protetores do slide
