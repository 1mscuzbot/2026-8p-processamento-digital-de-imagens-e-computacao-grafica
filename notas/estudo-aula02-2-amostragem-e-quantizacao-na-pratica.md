# Aula 02.2 — Amostragem e Quantização na prática (GLUT)

**Disciplina:** Processamento Digital de Imagens e Computação Gráfica (Prof. Diógenes Furlan)
**Slide de referência:** `material/slides/PDI26-02-2-AmostragemQuantização.pdf`

Conceitos teóricos na [Aula 02.1](estudo-aula02-1-imagens-conceitos-e-representacao.md). Aqui: textos/menus no GLUT e os **algoritmos de quantização e amostragem** (projeto `material/exercicios/PDI-Aula-02-proj/`).

---

## Sumário da aula

- Textos no GLUT
- Menus no GLUT
- Algoritmos de **Quantização** (redução de cores)
- Algoritmos de **Amostragem** (redução de resolução)

---

## Texto no GLUT

`glutBitmapCharacter` exibe um caractere **bitmap** (fonte pré-renderizada como bitmap, gerada com `glBitmap`), usando OpenGL. Parâmetros: `(void *font, int character)`.

Fontes disponíveis:

| Fonte | | Fonte |
|-------|-|-------|
| `GLUT_BITMAP_8_BY_13` | | `GLUT_BITMAP_HELVETICA_10` |
| `GLUT_BITMAP_9_BY_15` | | `GLUT_BITMAP_HELVETICA_12` |
| `GLUT_BITMAP_TIMES_ROMAN_10` | | `GLUT_BITMAP_HELVETICA_18` |
| `GLUT_BITMAP_TIMES_ROMAN_24` | | |

```cpp
void DesenhaTexto(char *buf)
{
   glPushMatrix();
   glRasterPos2f(x, y);        // posição do texto
   glColor3f(glWHITEf);        // cor do texto

   while (*buf)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *buf++);
   glPopMatrix();
}
```

---

## Menu com o GLUT

| Função | Papel |
|--------|-------|
| `glutMotionFunc` | callback quando o mouse é movido **com botão pressionado** |
| `glutPassiveMotionFunc` | callback quando o mouse é movido **sem botão pressionado** |
| `glutCreateMenu` | cria menu pop-up e registra a função callback |
| `glutAddMenuEntry` | adiciona entrada no fim do menu corrente |
| `glutAddSubMenu` | adiciona **submenu** no fim do menu corrente |
| `glutAttachMenu` | relaciona um botão do mouse ao menu (`GLUT_LEFT_BUTTON`, `GLUT_MIDDLE_BUTTON`, `GLUT_RIGHT_BUTTON`) |

```cpp
// callback de mouse: botão direito abre o menu
void GerenciaMouse(int button, int state, int x, int y)
{
    if (button == GLUT_RIGHT_BUTTON)
        if (state == GLUT_DOWN)
            CriaMenu();
    glutPostRedisplay();
}
// ... no main:
glutMouseFunc(GerenciaMouse);

void CriaMenu() {
    int menu, submenu1, submenu2;

    submenu1 = glutCreateMenu(MenuCor);             // submenu "Cor"
    glutAddMenuEntry("Vermelho", 0);
    glutAddMenuEntry("Verde", 1);
    glutAddMenuEntry("Azul", 2);

    submenu2 = glutCreateMenu(MenuPrimitiva);       // submenu "Primitivas"
    glutAddMenuEntry("Quadrado", 0);
    glutAddMenuEntry("Triângulo", 1);
    glutAddMenuEntry("Losango", 2);

    menu = glutCreateMenu(MenuPrincipal);           // menu principal
    glutAddSubMenu("Cor", submenu1);
    glutAddSubMenu("Primitivas", submenu2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// callbacks: recebem o valor da entrada selecionada (0, 1, 2…)
void MenuPrincipal(int op)  { }
void MenuPrimitiva(int op)  { /* switch(op) { case 0: primitiva = QUADRADO; … } glutPostRedisplay(); */ }
void MenuCor(int op)        { /* switch(op) { case 0: r=1.0f, g=0.0f, b=0.0f; … } glutPostRedisplay(); */ }
```

---

## Algoritmos de Quantização

Quantização = digitalizar/degradar a **amplitude (brilho/cor)**. Todos percorrem cada pixel com `ReadPixel` e gravam com `DrawPixel` (padrão dos projetos `ImageClass`).

### Cópia (baseline)

```cpp
void CopyImage() {
    int x, y;
    unsigned char r, g, b;
    for (x = 0; x < Image->getSizeX(); x++)
       for (y = 0; y < Image->getSizeY(); y++) {
          Image->ReadPixel(x, y, r, g, b);
          NovaImagem->DrawPixel(x, y, r, g, b);
       }
}
```

### Tons de cinza (luminância)

```cpp
void ConvertToGrayScale() {
    int x, y;
    unsigned char r, g, b;
    for (x = 0; x < Image->getSizeX(); x++)
       for (y = 0; y < Image->getSizeY(); y++) {
          Image->ReadPixel(x, y, r, g, b);
          i = (0.30*r + 0.59*g + 0.11*b);        // luminância (CIE)
          NovaImagem->DrawPixel(x, y, i, i, i);
       }
}
```

### Preto e branco (limiarização)

```cpp
void ConvertBlackAndWhite() {
    int x, y;               // Quanto maior o LIMIAR, mais preto a imagem fica
    unsigned char r, g, b;
    for (x = 0; x < Image->getSizeX(); x++)
       for (y = 0; y < Image->getSizeY(); y++) {
          Image->ReadPixel(x, y, r, g, b);
          i = (0.299*r + 0.587*g + 0.114*b);      // luminância (BT.601)
          if (i < LIMIAR)
             NovaImagem->DrawPixel(x, y, 0, 0, 0);
          else
             NovaImagem->DrawPixel(x, y, 255, 255, 255);
       }
}
```

### Canal isolado (ex.: verde)

```cpp
void GreenChannel() {
    int x, y;
    unsigned char r, g, b;
    for (x = 0; x < Image->getSizeX(); x++)
       for (y = 0; y < Image->getSizeY(); y++) {
          Image->ReadPixel(x, y, r, g, b);
          NovaImagem->DrawPixel(x, y, 0, g, 0);   // só o canal G
       }
}
```

---

## Algoritmos de Amostragem

Amostragem = digitalizar/degradar as **coordenadas espaciais (resolução)**.

### Zoom out (afastar)

Lê um pixel a cada `fator` passos e escreve em posições compactadas (`x/fator`).

```cpp
void ZoomOut(int fator) {
    int x, y;
    unsigned char r, g, b;
    for (x = 0; x < Image->getSizeX(); x += fator)
       for (y = 0; y < Image->getSizeY(); y += fator) {
          Image->ReadPixel(x, y, r, g, b);
          NovaImagem->DrawPixel(x / fator, y / fator, r, g, b);
       }
}
```

### Thumbnail (redimensionar para tamanho alvo)

Mesma ideia, mas com fatores calculados a partir do tamanho desejado `sizeX`/`sizeY`.

```cpp
void Thumbnail(int sizeX, int sizeY) {
    int x, y;
    unsigned char r, g, b;
    int fatorX = Image->getSizeX() / sizeX;
    int fatorY = Image->getSizeY() / sizeY;

    for (x = 0; x < sizeX; x++)
       for (y = 0; y < sizeY; y++) {
          Image->ReadPixel(x * fatorX, y * fatorY, r, g, b);
          NovaImagem->DrawPixel(x, y, r, g, b);
       }
}
```

---

## Exercícios resolvidos

### 1. Algoritmo: reduzir quantização de 256 para 16 tons de cinza

Duas opções equivalentes (a segunda mantém o valor na faixa 0–255 para exibição):

```cpp
// Mapear 256 níveis → 16 níveis: gray/16 ∈ {0..15}
i = (unsigned char)((0.299*r + 0.587*g + 0.114*b) / 16);
NovaImagem->DrawPixel(x, y, i, i, i);

// OU manter a escala 0–255 descartando os 4 bits inferiores
i = (unsigned char)(0.299*r + 0.587*g + 0.114*b) & 0xF0;  // gray >> 4 << 4
NovaImagem->DrawPixel(x, y, i, i, i);
```

### 2. Algoritmo: gerar imagem apenas com o canal vermelho

Igual ao `GreenChannel`, mantendo só o componente R:

```cpp
Image->ReadPixel(x, y, r, g, b);
NovaImagem->DrawPixel(x, y, r, 0, 0);
```

### 3. É possível dizer se a imagem é binária, monocromática ou colorida?

Sim, com dois testes acumulados numa varredura:

```cpp
bool colorida   = false;
bool monocr     = true;
bool binaria    = true;

for (cada pixel (x,y)) {
   Image->ReadPixel(x, y, r, g, b);

   if (r != g || g != b)         // canais diferentes ⇒ colorida
      colorida = true;

   if (colorida) {               // já colorida: não é mono nem binária
      monocr = false; binaria = false;
   } else if (r != 0 && r != 255) {  // tons de cinza fora de {0,255} ⇒ não binária
      binaria = false;
   }
}
// Resultado: colorida ? "Colorida"
//            : (binaria ? "Preto e branco (binária)" : "Monocromática (tons de cinza)")
```

> Justificativa: binária só aceita `{0, 255}`; monocromática exige `R=G=B` em todos os pixels; qualquer divergência entre canais indica imagem colorida.

---

## Referências cruzadas

- Conceitos de amostragem × quantização, tipos de imagem e armazenamento → [Aula 02.1](estudo-aula02-1-imagens-conceitos-e-representacao.md)
- Próximo passo: relações entre pixels (vizinhança, conectividade, rotulação) → [Aula 03](estudo-aula03-vizinhanca-conectividade-e-rotulacao.md)