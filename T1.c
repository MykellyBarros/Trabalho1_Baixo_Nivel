#include <stdio.h>
#include <stdlib.h>

struct Pixel
{
    int R, G, B;
};

void Cinza(struct Pixel **matriz, int linhas, int colunas)
{
    for (int j = 0; j < linhas; j++)
    {
        for (int i = 0; i < colunas; i++)
        {
            int iluminacao = (int)(0.30 * matriz[j][i].R + 0.59 * matriz[j][i].G + 0.11 * matriz[j][i].B);
            matriz[j][i].R = matriz[j][i].G = matriz[j][i].B = iluminacao;
        }
    }
}

void envelhecida(struct Pixel **matriz, int linhas, int colunas)
{
    for (int j = 0; j < linhas; j++)
    {
        for (int i = 0; i < colunas; i++)
        {

            matriz[j][i].R = matriz[j][i].R - 20;

            if (matriz[j][i].R < 0)
                matriz[j][i].R = 0;

            matriz[j][i].G = matriz[j][i].G - 20;

            if (matriz[j][i].G < 0)
                matriz[j][i].G = 0;

            matriz[j][i].B = matriz[j][i].B - 20;

            if (matriz[j][i].B < 0)
                matriz[j][i].B = 0;
        }
    }
}

void EfeitoNeg(struct Pixel **matriz, int linhas, int colunas)
{
    {

    for (int j = 0; j < linhas; j++)
    {
        for (int i = 0; i < colunas; i++)
        { matriz[j][i].R = 255 - matriz[j][i].R;
          matriz[j][i].G = 255 - matriz[j][i].G;
          matriz[j][i].B = 255 - matriz[j][i].B;
        }
    }
}
}

void saturadac(struct Pixel **matriz, int linhas, int colunas)
{
    for (int j = 0; j < linhas; j++)
    {
        for (int i = 0; i < colunas; i++)
        {
            int saturadac = (int)(1.3 * matriz[j][i].R + 1.3 * matriz[j][i].G + 1.3 * matriz[j][i].B);
            if (saturadac > 255)
                saturadac = 255;
            matriz[j][i].R = matriz[j][i].G = matriz[j][i].B = saturadac;
        }
    }
}

void SBrilho(struct Pixel **matriz, int linhas, int colunas)
{
    for (int j = 0; j < linhas; j++)
    {
        for (int i = 0; i < colunas; i++)
        {
            int brilho = (int)(0.2 * matriz[j][i].R + 0.2 * matriz[j][i].G + 0.2 * matriz[j][i].B);
            if (brilho > 255)
                brilho = 255; // Limita a 255
            matriz[j][i].R = matriz[j][i].G = matriz[j][i].B = brilho;
        }
    }
}

void GirarImage(struct Pixel **matriz, int linhas, int colunas, struct Pixel ***novaMatriz, int *novasLinhas, int *novasColunas)
{
    *novasLinhas = colunas;
    *novasColunas = linhas;

    *novaMatriz = (struct Pixel **)malloc(*novasLinhas * sizeof(struct Pixel *));
    for (int i = 0; i < *novasLinhas; i++)
    {
        (*novaMatriz)[i] = (struct Pixel *)malloc(*novasColunas * sizeof(struct Pixel));
    }

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            (*novaMatriz)[colunas - 1 - j][i] = matriz[i][j];
        }
    }
}

void processarTransformacao(struct Pixel **matriz, int linha, int coluna, char formato[], int valorMaximo)
{
    int opcao;
    printf("\nEscolha uma alternativa para modificar a imagem:\n");
    printf("1. Gerar uma imagem tons de cinza\n");
    printf("2. Gerar imagem envelhecida\n");
    printf("3. Gerar imagem negativa\n");
    printf("4. Aumentar o brilho da imagem cinza\n");
    printf("5. Diminuir o Brilho da imagem cinza\n");
    printf("6. Girar a imagem em -90 graus\n");
    printf("Escolha uma Alternativa: ");
    scanf("%d", &opcao);

    struct Pixel **novaMatriz = NULL;
    int novasLinhas, novasColunas;

    switch (opcao)
    {
    case 1:
        Cinza(matriz, linha, coluna);
        break;
    case 2:
        envelhecida(matriz, linha, coluna);
        break;
    case 3:
        EfeitoNeg(matriz, linha, coluna);
        break;
    case 4:
        saturadac(matriz, linha, coluna);
        break;
    case 5:
        SBrilho(matriz, linha, coluna);

        break;

    case 6:

        GirarImage(matriz, linha, coluna, &novaMatriz, &novasLinhas, &novasColunas);
        break;
    default:
        printf("Opção inválida.\n");
        return;
    }

    FILE *fp_novo = fopen("imagem_transformada.ppm", "w");
    if (fp_novo == NULL)
    {
        printf("Erro ao criar o arquivo.\n");
        exit(1);
    }

    if (opcao == 6)
    {
        fprintf(fp_novo, "%s\n", formato);
        fprintf(fp_novo, "%d %d\n", novasColunas, novasLinhas);
        fprintf(fp_novo, "%d\n", valorMaximo);

        for (int j = 0; j < novasLinhas; j++)
        {
            for (int i = 0; i < novasColunas; i++)
            {
                fprintf(fp_novo, "%d %d %d ", novaMatriz[j][i].R, novaMatriz[j][i].G, novaMatriz[j][i].B);
            }
            fprintf(fp_novo, "\n");
        }
    }
    else
    {
        fprintf(fp_novo, "%s\n", formato);
        fprintf(fp_novo, "%d %d\n", coluna, linha);
        fprintf(fp_novo, "%d\n", valorMaximo);

        for (int j = 0; j < linha; j++)
        {
            for (int i = 0; i < coluna; i++)
            {
                fprintf(fp_novo, "%d %d %d ", matriz[j][i].R, matriz[j][i].G, matriz[j][i].B);
            }
            fprintf(fp_novo, "\n");
        }
    }

    fclose(fp_novo);

    if (novaMatriz)
    {
        for (int i = 0; i < novasLinhas; i++)
        {
            free(novaMatriz[i]);
        }
        free(novaMatriz);
    }

    printf("Transformação aplicada e salva em 'imagem_transformado.ppm'.\n");
}

int main()
{
    FILE *fp;
    char filename[256];
    char formato[3];
    int coluna, linha, valorMaximo;

    printf("Digite o nome completo do arquivo PPM a ser aberto: ");
    scanf("%255s", filename);

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Não foi possível abrir o arquivo '%s'.\n", filename);
        return EXIT_FAILURE;
    }

    fscanf(fp, "%s", formato);
    fscanf(fp, "%d %d", &coluna, &linha);
    fscanf(fp, "%d", &valorMaximo);

    if (linha < 400 || coluna < 400)
    {
        fprintf(stderr, "O arquivo '%s' não atende ao requisito mínimo de tamanho 400x400.\n", filename);
        fclose(fp);
        return EXIT_FAILURE;
    }

    struct Pixel **matriz = (struct Pixel **)malloc(linha * sizeof(struct Pixel *));
    for (int i = 0; i < linha; i++)
    {
        matriz[i] = (struct Pixel *)malloc(coluna * sizeof(struct Pixel));
    }

    for (int j = 0; j < linha; j++)
    {
        for (int i = 0; i < coluna; i++)
        {
            fscanf(fp, "%d %d %d", &matriz[j][i].R, &matriz[j][i].G, &matriz[j][i].B);
        }
    }

    fclose(fp);

    processarTransformacao(matriz, linha, coluna, formato, valorMaximo);

    for (int i = 0; i < linha; i++)
    {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}