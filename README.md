# Processamento Digital de Imagens e Computação Gráfica

**Universidade Tuiuti do Paraná — BCC 7º/8º Período**
**Professor:** Diógenes Furlan
**Aulas:** Segunda — 19:00 às 22:30
**Equipe:** Teams — "2026/2 - CT - Processamento Digital de Imagens e Computação Gráfica"

## Estrutura
- `material/slides/` — slides das aulas
- `material/provas/` — provas e gabaritos
- `material/exercicios/` — listas de exercícios
- `projetos/` — trabalhos práticos
- `notas/` — anotações e resumos

## Ementa

### 1º Bimestre — Processamento Digital de Imagens
- Introdução ao PDI: conceitos e representação de imagens digitais
- Fundamentos: amostragem e quantização; relacionamentos básicos entre pixels
- Realce de imagens: processamento ponto a ponto; filtragem espacial
- Segmentação: detecção de descontinuidades; ligação de bordas; limiarização; segmentação orientada a regiões
- Morfologia matemática

### 2º Bimestre — Computação Gráfica
- Introdução à Computação Gráfica
- Transformações geométricas no plano e no espaço
- Matrizes em CG; pontos, vetores e matrizes
- Sistemas de coordenadas; transformações em pontos e objetos
- Coordenadas homogêneas
- Animação 2D e 3D
- Iluminação e sombreamento
- Mapeamento de texturas
- Buffers e Raytracing

## Avaliação
- **1º Bimestre (B1):** Trabalho em OpenGL 70% + Prova conceitual 30% — **24/set**
- **2º Bimestre (B2):** Trabalho em OpenGL 70% + Prova conceitual 30% — **26/nov**
- **2ª Chamada:** 30/nov
- **Exame Final:** 7/dez

## Bibliografia
- CONCI, Aura; AZEVEDO, Eduardo. *Computação Gráfica*. Campus, 2007. (Volumes 1 e 2)
- GONZALEZ, R. C.; WOODS, R. *Processamento de Imagens Digitais*. Edgard Blucher, 2000.

## Notas de estudo
- [Aula 02.1 — Imagens: conceitos, representação e armazenamento (exercícios resolvidos)](notas/estudo-aula02-1-imagens-conceitos-e-representacao.md)
- [Aula 02.2 — Amostragem e quantização na prática (texto/menus GLUT e algoritmos)](notas/estudo-aula02-2-amostragem-e-quantizacao-na-pratica.md)
- [Aula 03 — Vizinhança, conectividade e rotulação (com prática de Flood Fill)](notas/estudo-aula03-vizinhanca-conectividade-e-rotulacao.md)

## Conteúdo das aulas

### Aula 1 — Introdução à Computação Gráfica e PDI
- Grandes áreas: síntese de imagens, processamento e análise de imagens
- Exemplos: jogos, produções artísticas, visão artificial (reconhecimento de digitais)
- Visão humana: retina, cones e bastonetes, daltonismo, contraste simultâneo, ilusões de ótica
- Sistema de visão (passos: aquisição → pré-processamento → processamento → análise → extração de características → IA/reconhecimento de padrões)

### Prática 1 — Introdução ao OpenGL
- Bibliotecas: OpenGL (`gl.h`), GLU (`glu.h`), GLUT (`glut.h`)
- OpenGL como máquina de estados (cor corrente, glEnable/glDisable)
- Convenção de comandos: prefixo + raiz + contador de args + tipo (ex: `glColor3f`)
- Funções de inicialização GLUT: `glutInit`, `glutCreateWindow`, `glutMainLoop`
- Callbacks: display, reshape, idle, timer, keyboard, mouse
- Projeto base carrega imagem BMP e exibe via `ImageClass`
- **Exercícios:**
  1. Modificar a cor de fundo da janela para verde
  2. Navegar pelas imagens .bmp com setas (← →)
  3. Controlar o limiar do `ConvertBlackAndWhite` pelo teclado (±5) e mostrar o valor na tela

### Aula 2 — Digitalização de imagens (Amostragem e Quantização)
- Níveis de abstração (físico/matemático/computacional); vídeo e tipos de imagem; níveis de percepção (Marr)
- Imagem como função `f(x,y)`; aquisição: iluminação × refletância
- Representação **vetorial** × **matricial/raster**; extensões de arquivos; SVG/XML
- **Amostragem** (resolução/pixels) × **Quantização** (níveis de cor); degradação de imagem
- Imagens: preto e branco (1 bit), monocromática (8 bits), colorida RGB (24 bits); armazenamento (bytes)
- Prática GLUT: texto (`glutBitmapCharacter`), menus (`glutCreateMenu`/`glutAddMenuEntry`/`glutAttachMenu`)
- Algoritmos: `ConvertToGrayScale`, `ConvertBlackAndWhite` (limiar), `GreenChannel`, `ZoomOut`, `Thumbnail`
- **Exercícios:** armazenamento (bytes de imagens), maior imagem em 1 MB, logo SVG, quantização 256→16 tons, canal vermelho, classificação binária/monocromática/colorida

### Aula 3 — Relacionamentos entre pixels
- Vizinhança-4, diagonal e vizinhança-8 (`N4`, `ND`, `N8`)
- Adjacência / conectividade: **4, 8 e m** (mista elimina ambiguidades); caminho digital
- Conectividade e componentes conexos; agora o exemplo 10×10: 4 regiões (8-conexas) × 10 regiões (4-conexas)
- **Rotulação:** algoritmo de 2 passadas com classes de equivalência (`(1,2),(3,4),(1,5)` → rotulagem final)
- Prática: Flood Fill (preenchimento por inundação), `RotularComponentes`, `FloodFillRotulo`
- **Exercícios:** rotulação com Sc={1}, adaptação 8-conexa, A4/A8/Am de matriz 7×7, conectividade de S1/S2, limiar de cores próximas

## Arquivos no repositório
| Arquivo | Descrição |
|---------|-----------|
| `material/2026s-PDICG-Apresentacao.pdf` | Apresentação da disciplina (objetivos, ementa, avaliações, bibliografia) |
| `material/slides/PDI26-01-IntroducaoPDI.pdf` | Aula 1 — Introdução a CG/PDI e visão humana |
| `material/slides/PDI26-02-1-Imagens.pdf` | Aula 2.1 — Conceitos, representação (vetorial/matricial), amostragem/quantização, armazenamento |
| `material/slides/PDI26-02-2-AmostragemQuantização.pdf` | Aula 2.2 — Texto/menus GLUT e algoritmos de quantização e amostragem |
| `material/slides/PDI26-03-1-Conectividade.pdf` | Aula 3.1 — Vizinhança, adjacência (4/8/m), conectividade e rotulação |
| `material/slides/PDI26-03-2-Conectividade-Pratica.pdf` | Aula 3.2 — Prática: Flood Fill, componente conexo e rotulagem |
| `material/exercicios/PDI-Prática01-IntroducaoOpenGL.pdf` | Prática 1 — Introdução ao OpenGL (GLUT, callbacks, exercícios) |
| `material/exercicios/Imagens/` | Imagens de exemplo (`.bmp`/`.jpg`) para os exercícios |
| `material/exercicios/PDI-Aula-02-proj/` | Projeto C++ (CodeBlocks + OpenGL/GLUT) das aulas 2.x |
| `material/exercicios/PDI-Aula-03-2-proj/` | Projeto C++ com `ImageClass`/`BmpLib` e função `PDI` da aula 3.2 |
