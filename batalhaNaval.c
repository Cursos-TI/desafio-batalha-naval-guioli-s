#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5

void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

int validarPosicao(int tabuleiro[TAMANHO][TAMANHO], int linhaInicial, int colunaInicial, char orientacao, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (orientacao == 'H') {
            if (colunaInicial + i >= TAMANHO || tabuleiro[linhaInicial][colunaInicial + i] != 0) {
                return 0;
            }
        } else if (orientacao == 'V') {
            if (linhaInicial + i >= TAMANHO || tabuleiro[linhaInicial + i][colunaInicial] != 0) {
                return 0;
            }
        } else if (orientacao == 'D') {
            if (linhaInicial + i >= TAMANHO || colunaInicial + i >= TAMANHO || tabuleiro[linhaInicial + i][colunaInicial + i] != 0) {
                return 0;
            }
        } else if (orientacao == 'A') {
            if (linhaInicial + i >= TAMANHO || colunaInicial - i < 0 || tabuleiro[linhaInicial + i][colunaInicial - i] != 0) {
                return 0;
            }
        }
    }
    return 1;
}

void posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linhaInicial, int colunaInicial, char orientacao, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (orientacao == 'H') {
            tabuleiro[linhaInicial][colunaInicial + i] = 3;
        } else if (orientacao == 'V') {
            tabuleiro[linhaInicial + i][colunaInicial] = 3;
        } else if (orientacao == 'D') {
            tabuleiro[linhaInicial + i][colunaInicial + i] = 3;
        } else if (orientacao == 'A') {
            tabuleiro[linhaInicial + i][colunaInicial - i] = 3;
        }
    }
}

void imprimirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if (tabuleiro[i][j] == 0) {
                printf("0 ");
            } else if (tabuleiro[i][j] == 3) {
                printf("3 ");
            } else if (tabuleiro[i][j] == 5) {
                printf("5 ");
            }
        }
        printf("\n");
    }
}

void criarHabilidadeCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (j >= TAMANHO_HABILIDADE / 2 - i && j <= TAMANHO_HABILIDADE / 2 + i) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

void criarHabilidadeCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == TAMANHO_HABILIDADE / 2 || j == TAMANHO_HABILIDADE / 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

void criarHabilidadeOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (abs(i - TAMANHO_HABILIDADE / 2) + abs(j - TAMANHO_HABILIDADE / 2) <= TAMANHO_HABILIDADE / 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int linhaOrigem, int colunaOrigem) {
    int offset = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int linha = linhaOrigem + i - offset;
            int coluna = colunaOrigem + j - offset;
            if (linha >= 0 && linha < TAMANHO && coluna >= 0 && coluna < TAMANHO && habilidade[i][j] == 1) {
                if (tabuleiro[linha][coluna] == 0) {
                    tabuleiro[linha][coluna] = 5;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    inicializarTabuleiro(tabuleiro);

    // Coordenadas iniciais dos navios
    int linhaNavio1 = 2, colunaNavio1 = 3; // Navio horizontal
    int linhaNavio2 = 5, colunaNavio2 = 7; // Navio vertical
    int linhaNavio3 = 0, colunaNavio3 = 0; // Navio diagonal crescente
    int linhaNavio4 = 0, colunaNavio4 = 9; // Navio diagonal decrescente

    // Verificação de limites e sobreposição
    if (validarPosicao(tabuleiro, linhaNavio1, colunaNavio1, 'H', TAMANHO_NAVIO) &&
        validarPosicao(tabuleiro, linhaNavio2, colunaNavio2, 'V', TAMANHO_NAVIO) &&
        validarPosicao(tabuleiro, linhaNavio3, colunaNavio3, 'D', TAMANHO_NAVIO) &&
        validarPosicao(tabuleiro, linhaNavio4, colunaNavio4, 'A', TAMANHO_NAVIO)) {
        
        posicionarNavio(tabuleiro, linhaNavio1, colunaNavio1, 'H', TAMANHO_NAVIO);
        posicionarNavio(tabuleiro, linhaNavio2, colunaNavio2, 'V', TAMANHO_NAVIO);
        posicionarNavio(tabuleiro, linhaNavio3, colunaNavio3, 'D', TAMANHO_NAVIO);
        posicionarNavio(tabuleiro, linhaNavio4, colunaNavio4, 'A', TAMANHO_NAVIO);
    } else {
        printf("Erro: Coordenadas inválidas para os navios.\n");
        return 1;
    }

    // Matrizes de habilidades
    int habilidadeCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    criarHabilidadeCone(habilidadeCone);
    criarHabilidadeCruz(habilidadeCruz);
    criarHabilidadeOctaedro(habilidadeOctaedro);

    // Aplicar habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, habilidadeCone, 4, 4);
    aplicarHabilidade(tabuleiro, habilidadeCruz, 7, 2);
    aplicarHabilidade(tabuleiro, habilidadeOctaedro, 1, 8);

    // Imprimir tabuleiro com navios e habilidades
    imprimirTabuleiro(tabuleiro);

    return 0;
}
