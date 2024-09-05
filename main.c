#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/*
>O QUE FAZER:
*- DECORAÇÃO
*- MENU DE OPÇÕES
*- REMOVE OS PRODUTOS
*- SE PRIMEIRA VEZ, TEM QUE INSERIR
*- SISTEMA DE DESCONTO (TOP 3)
*- SANITIZAÇÃO DE INPUT
*- COMENTAR PELO AMOR DE DEUS!!!!!!!!!!!!!!!!!!!!!!

>FEITO:
!- INSERÇÃO DE DADOS
!- CALCULO DE VENDA
!- COLOCA A LINGUA EM PORTUGUES
!- CALCULO DE VENDAS
!- PRODUTO COM MAIOR QUANTIDADE (TOP 3)
!- PRODUTO COM MENOR QUANTIDADE (TOP 3)
*/

// struct para definir um tipo de Produto
typedef struct
{
    char nome[50];
    float valor_compra;
    float valor_venda;
    int numero_vendas;
} Produto;

int main()
{
    // * VARIÁVEIS E INPUT:
    // coloca a lingua do CMD para aceitar acentuação
    setlocale(LC_ALL, ".UTF8");

    // variaveis
    int num_produtos = 0;

    // matriz de produtos de tipo Produto
    Produto produtos[num_produtos];
    Produto temp;

    // define o maior e o menor lucro como a posição do primeiro produto
    Produto produto_maior_lucro = produtos[0];
    Produto produto_menor_lucro = produtos[0];

    // define o calculo de lucro
    float maior_lucro = (produto_maior_lucro.valor_venda - produto_maior_lucro.valor_compra) * produtos[0].numero_vendas;
    float menor_lucro = maior_lucro;

    // define o calculo de venda
    Produto produto_maior_vendas = produtos[0];
    Produto produto_menor_vendas = produtos[0];
    int maior_vendas = produto_maior_vendas.numero_vendas;
    int menor_vendas = produto_menor_vendas.numero_vendas;

    // * PROGRAMA

    printf("\n\nBem-vindo ao SEI (Sistema de Estoque Integrado)!\n\n");

    // Menu de opções:
    while (1)
    {
        int op = 0;
        printf("\nSelecione dentre as opções abaixo: ");
        printf("\n1 - Inserção de produtos.");
        printf("\n2 - Remoção de produtos do estoque.");
        printf("\n3 - Alterar dados de produtos.");
        printf("\n4 - Consulta de lucro.");
        printf("\n5 - Consulta de venda.");
        printf("\n0 - Sair.");

        printf("\n\nDigite a opção abaixo: ");
        scanf("%d", &op);

        switch (op)
        {
        // * SAIR DO PROGRAMA
        case 0:
            return 0;
            break;

        // * INSERIR PRODUTOS
        case 1:
            printf("Digite o número de produtos a serem inseridos: ");
            scanf("%d", &num_produtos);

            // itera os produtos
            for (int i = 0; i < num_produtos; i++)
            {
                printf("\nDigite as informações do produto %d:\n", i + 1);

                // definir as variáveis do struct
                printf(">Nome: ");
                scanf(" %[^\n]", produtos[i].nome);
                printf(">Valor de compra: ");
                scanf("%f", &produtos[i].valor_compra);
                printf(">Valor de venda: ");
                scanf("%f", &produtos[i].valor_venda);
                printf(">Número de vendas: ");
                scanf("%d", &produtos[i].numero_vendas);
            }
            break;

        // * REMOVER PRODUTOS
        case 2:

            break;

        // * ALTERAR PRODUTOS
        case 3:

            break;

        // * CONSULTA LUCRO
        case 4:
            // calculo de lucro:
            for (int i = 0; i < num_produtos; i++)
            {
                // calculo do lucro do produto da iteração atual
                // o calculo do lucro é a diferença do valor de venda e de compra vezes o numero de vendas
                float lucro_atual = (produtos[i].valor_venda - produtos[i].valor_compra) * produtos[i].numero_vendas;

                // se o lucro atual for maior que o lucro maior, ele substitui
                if (lucro_atual > maior_lucro)
                {
                    maior_lucro = lucro_atual;
                    produto_maior_lucro = produtos[i];
                }

                // se o lucro atual for menor que o lucro menor, ele substitui
                if (lucro_atual < menor_lucro)
                {
                    menor_lucro = lucro_atual;
                    produto_menor_lucro = produtos[i];
                }
            }

            // bubble sort para ordenar o lucro
            for (int i = 0; i < num_produtos - 1; i++)
            {
                for (int j = i + 1; j < num_produtos; j++)
                {
                    float lucro_i = (produtos[i].valor_venda - produtos[i].valor_compra) * produtos[i].numero_vendas;

                    float lucro_j = (produtos[j].valor_venda - produtos[j].valor_compra) * produtos[j].numero_vendas;

                    if (lucro_j > lucro_i)
                    {
                        temp = produtos[i];
                        produtos[i] = produtos[j];
                        produtos[j] = temp;
                    }
                }
            }

            // print do maior e menor lucro:
            printf("\n\nO maior lucro foi o produto: %s", produto_maior_lucro.nome);
            printf("\nLucro total de: %.2f", maior_lucro);
            printf("\n\nO menor lucro foi o produto: %s", produto_menor_lucro.nome);
            printf("\nLucro total de: %.2f", menor_lucro);

            printf("\n\nProdutos ordenados por lucro: ");
            for (int i = 0; i < 3; i++)
            {
                // armazena o calculo de lucro para legibilidade
                float produto_lucro = (produtos[i].valor_venda - produtos[i].valor_compra) * produtos[i].numero_vendas;

                // mostra a posição, depois o nome do produto e o lucro
                printf("\n>%dº: \n- Nome: %s\n- Lucro: %.2f", i + 1, produtos[i].nome, produto_lucro);
            }
            break;

        // * CONSULTA VENDA
        case 5:
            // calculo de vendas:
            for (int i = 0; i < num_produtos; i++)
            {
                // calculo do lucro do produto da iteração atual
                // o calculo do lucro é a diferença do valor de venda e de compra vezes o numero de vendas
                float vendas_atual = produtos[i].numero_vendas;

                // se o lucro atual for maior que o lucro maior, ele substitui
                if (vendas_atual > maior_vendas)
                {
                    maior_vendas = vendas_atual;
                    produto_maior_vendas = produtos[i];
                }

                // se o lucro atual for menor que o lucro menor, ele substitui
                if (vendas_atual < menor_vendas)
                {
                    menor_vendas = vendas_atual;
                    produto_menor_vendas = produtos[i];
                }
            }

            // printa o maior e menor numero de vendas
            printf("\n\nProdutos com maior número de vendas: %s", produto_maior_vendas.nome);
            printf("\nNúmero de produtos: %d", maior_vendas);
            printf("\n\nProduto com menor número de vendas: %s", produto_menor_vendas.nome);
            printf("\nNúmero de produtos: %d", menor_vendas);

            printf("\n\nProdutos ordenados por venda: ");
            for (int i = 0; i < 3; i++)
            {
                // mostra a posição, depois o nome do produto e o lucro
                printf("\n>%dº: \n- Nome: %s\n- Quantia de vendas: %d", i + 1, produtos[i].nome, produtos[i].numero_vendas);
            }
            break;

        // * OPÇÃO NÃO ENCONTRADA
        default:
            printf("\nDigite uma opção válida, por favor.\n\n");
            break;
        }
    }

    return 0;
}