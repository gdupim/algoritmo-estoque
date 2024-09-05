#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

/*
>O QUE FAZER:
*- DECORAÇÃO

>FEITO:
!- SANITIZAÇÃO
!- INSERÇÃO DE DADOS
!- CALCULO DE VENDA
!- COLOCA A LINGUA EM PORTUGUES
!- CALCULO DE VENDAS
!- PRODUTO COM MAIOR QUANTIDADE (TOP 3)
!- PRODUTO COM MENOR QUANTIDADE (TOP 3)
!- REMOVE OS PRODUTOS
!- COMENTAR PELO AMOR DE DEUS!!!!!!!!!!!!!!!!!!!!!!
*/

// função para redimensionar o CMD
void tamanho_tela(int x, int y)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT sr;
    COORD consoleSize;
    sr.Top = sr.Left = 0;
    consoleSize.X = x;
    consoleSize.Y = y;
    sr.Right = consoleSize.X - 1;
    sr.Bottom = consoleSize.Y - 1;

    SetConsoleWindowInfo(console, TRUE, &sr);
    SetConsoleScreenBufferSize(console, consoleSize);
}

// struct para definir um tipo de Produto
typedef struct
{
    int id;
    char nome[50];
    float valor_compra;
    float valor_venda;
    int numero_vendas;
    int quantidade_estoque;
} Produto;

int main()
{
    // * VARIÁVEIS E INPUT:
    // coloca a lingua do CMD para aceitar acentuação
    setlocale(LC_ALL, ".UTF8");

    // variaveis
    int num_produtos = 0;
    int j = 0, aux = 0, ope = 0, sair = 0, op = 0, remover = 0, alterar = 0, opalt = 0;

    // matriz de produtos de tipo Produto
    Produto produtos[num_produtos];
    Produto temp;

    produtos[0].quantidade_estoque = 0;

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

    printf(" +----------------------------------------------------------------------------+\n");
    printf(" |                                                                            |\n");
    printf(" |              Bem-vindo ao SEI (Sistema de Estoque Integrado)!              |\n");
    printf(" |                                                                            |\n");
    printf(" +----------------------------------------------------------------------------+\n\n");

    // Menu de opções:
    while (1)
    {
        // Menu de opções:
        printf("\n\n\nSelecione dentre as opções abaixo: ");
        printf("\n1 - Inserção de produtos.");
        printf("\n2 - Remoção de produtos do estoque.");
        printf("\n3 - Alterar dados de produtos.");
        printf("\n4 - Consulta de estoque.");
        printf("\n5 - Consulta de lucro.");
        printf("\n6 - Consulta de venda.");
        printf("\n0 - Sair.");

        printf("\n\nDigite a opção abaixo: ");
        scanf("%d", &op);

        //  para não crashar qnd por letra
        while (scanf("%d", &op) != 1)
        {
            printf("\nDigite uma opção válida...");

            printf("\n\nDigite a opção abaixo: ");
            scanf("%d", &op);
        }

        while (produtos[0].quantidade_estoque == 0 && op != 1 && op != 0)
        {
            printf("\nPor favor, insira os dados primeiros antes de continuar...");

            printf("\n\nDigite a opção abaixo: ");
            scanf("%d", &op);
        }

        switch (op)
        {
        // * SAIR DO PROGRAMA
        case 0:
            return 0;
            break;

        // * INSERIR PRODUTOS
        case 1:
            // não digite numeros muito altos, a chance do programa quebrar também é alta
            printf("\n>Digite o número de produtos a serem inseridos: ");
            scanf("%d", &num_produtos);

            // enquanto o numero de produtos for menor que zero, ele repetira a pergunta
            while (num_produtos <= 0 && scanf("%d", &num_produtos) != 1)
            {
                printf(">Digite um número de produtos válidos a ser inseridos: ");
                scanf("%d", &num_produtos);
            }

            // itera os produtos
            for (int i = 0; i < num_produtos; i++)
            {
                printf("\n\nDigite as informações do produto %d: ", i + 1);

                // definir as variáveis do struct
                printf("\n>Nome: ");
                scanf(" %[^\n]", produtos[i].nome);

                printf("\n>Valor de compra: ");
                scanf("%f", &produtos[i].valor_compra);

                while (scanf("%f", &produtos[i].valor_compra) != 1)
                {
                    printf("\nDigite um número válido...");

                    printf("\n>Valor de compra: ");
                    scanf("%f", &produtos[i].valor_compra);
                }

                printf("\n>Valor de venda: ");
                scanf("%f", &produtos[i].valor_venda);

                while (scanf("%f", &produtos[i].valor_venda) != 1)
                {
                    printf("\nDigite um número válido...");

                    printf("\n>Valor de venda: ");
                    scanf("%f", &produtos[i].valor_venda);
                }

                printf("\n>Número de vendas: ");
                scanf("%d", &produtos[i].numero_vendas);

                while (scanf("%d", &produtos[i].numero_vendas) != 1)
                {
                    printf("\nDigite um número válido...");

                    printf("\n>Número de vendas: ");
                    scanf("%d", &produtos[i].numero_vendas);
                }

                printf("\n>Quantidade no estoque: ");
                scanf("%d", &produtos[i].quantidade_estoque);

                while (scanf("%d", &produtos[i].quantidade_estoque) != 1)
                {
                    printf("\nDigite um número válido...");

                    printf("\n>Quantidade no estoque:: ");
                    scanf("%d", &produtos[i].quantidade_estoque);
                }

                // se a quantia no estoque for menor que zero ou a quantia de estoque e o numero de vendas for 0
                while (produtos[i].quantidade_estoque < 0 || (produtos[i].quantidade_estoque == 0 && produtos[i].numero_vendas == 0))
                {
                    printf("\n\nProduto inválido\n > Digite novamente as informações do produto %d:\n", i + 1);

                    // definir as variáveis do struct
                    printf("\n > Nome: ");
                    scanf(" %s", produtos[i].nome);

                    printf("\n > Valor de compra: ");
                    scanf("%f", &produtos[i].valor_compra);

                    printf("\n > Valor de venda: ");
                    scanf("%f", &produtos[i].valor_venda);

                    printf("\n > Número de vendas: ");
                    scanf("%d", &produtos[i].numero_vendas);

                    printf("\n > Quantidade em estoque: ");
                    scanf("%d", &produtos[i].quantidade_estoque);
                }

                // funciona como chave primaria, um identificador
                produtos[i].id = i;
            }
            break;

        // * REMOVER PRODUTOS
        case 2:
            // listar os produtos
            printf("\nListagem dos produtos: \n\n");

            for (int i = 0; i < num_produtos; i++)
            {
                printf("\n>ID: %d \n- Nome: %s \n- Valor de venda: %f \n- Número de vendas: %d \n- Quantia no estoque: %d", produtos[i].id, produtos[i].nome, produtos[i].valor_venda, produtos[i].numero_vendas, produtos[i].quantidade_estoque);
            }

            printf("\nDigite o ID do produto que deseja remover: ");
            scanf("%d", &remover);

            while (remover > num_produtos || remover < 0 || scanf("%d", &remover) != 1)
            {
                printf("\nDigite um ID de produto válido: ");
                scanf("%d", &remover);
            }

            break;

        // * ALTERAR PRODUTOS
        case 3:
            // listar os produtos
            printf("\nListagem dos produtos: \n\n");

            for (int i = 0; i < num_produtos; i++)
            {
                printf("\n>ID: %d \n- Nome: %s \n- Valor de venda: %f \n- Número de vendas: %d \n- Quantia no estoque: %d", produtos[i].id, produtos[i].nome, produtos[i].valor_venda, produtos[i].numero_vendas, produtos[i].quantidade_estoque);
            }

            printf("\nDigite o ID do produto que deseja alterar: ");
            scanf("%d", &alterar);

            while (alterar > num_produtos || alterar < 0 || scanf("%d", &alterar) != 1)
            {
                printf("\nDigite um ID de produto válido: ");
                scanf("%d", &alterar);
            }

            // printar o produto selecionado:
            printf("\n>ID: %d \n- Nome: %s \n- Valor de venda: %f \n- Número de vendas: %d \n- Quantia no estoque: %d", produtos[alterar].id, produtos[alterar].nome, produtos[alterar].valor_venda, produtos[alterar].numero_vendas, produtos[alterar].quantidade_estoque);

            printf("\nO que deseja alterar do produto selecionado: ");
            printf("\n1 - Nome: ");
            printf("\n2 - Valor de venda: ");
            printf("\n3 - Número de vendas: ");
            printf("\n4- Quantia no estoque: ");
            printf("\n0 - Sair");

            printf("\nDigite uma das opções: ");
            scanf("%d", &opalt);

            while (scanf("%d", &opalt) != 1)
            {
                printf("\nDigite uma opção válida...");

                printf("\nDigite uma das opções: ");
                scanf("%d", &opalt);
            }

            printf("\nDigite o novo valor: ");
            switch (opalt)
            {
            // * NOME
            case 1:
                char novo_nome[50];
                scanf(" %[^\n]", produtos[alterar].nome);

                break;

            // * VALOR VENDA
            case 2:
                float novo_valor;
                scanf("%f", produtos[alterar].valor_venda);

                while (scanf("%f", &produtos[alterar].valor_venda) != 1)
                {
                    printf("\nDigite um valor válido...");

                    printf("\nDigite o novo valor: ");
                    scanf("%f", produtos[alterar].valor_venda);
                }

                break;

            // * NÚMERO VENDA
            case 3:
                int num_venda;
                scanf("%d", produtos[alterar].numero_vendas);

                while (scanf("%d", &produtos[alterar].numero_vendas) != 1)
                {
                    printf("\nDigite um valor válido...");

                    printf("\nDigite o novo valor: ");
                    scanf("%d", produtos[alterar].numero_vendas);
                }

                break;

            //  * QUANTIA ESTOQUE
            case 4:
                int nova_qnt;
                scanf("%d", produtos[alterar].quantidade_estoque);

                while (scanf("%d", &produtos[alterar].quantidade_estoque) != 1)
                {
                    printf("\nDigite um valor válido...");

                    printf("\nDigite o novo valor: ");
                    scanf("%d", produtos[alterar].quantidade_estoque);
                }

                break;

            // * SAIR
            case 0:
                sair = 1;
                break;

            default:
                printf("\nPor favor, digite uma opção válida...");
                break;
            }

            // volta ao menu principal
            if (sair != 0)
            {
                break;
            }

            break;

        // * CONSULTA ESTOQUE
        case 4:
            // bubble sort para as quantias de estoque
            while (j != 0)
            {
                // Definindo j = 0, ainda não ouve mudanças
                j = 0;

                // for para percorrer o vetor comparando os valores dos indices.
                for (int i = 0; i < num_produtos; i++)
                {

                    // Checando se o indice i e maior que o proximo indice
                    if (produtos[i].quantidade_estoque > produtos[i + 1].quantidade_estoque)
                    {

                        // Trocando os indices de posição
                        aux = produtos[i].quantidade_estoque;
                        produtos[i].quantidade_estoque = produtos[i + 1].quantidade_estoque;
                        produtos[i + 1].quantidade_estoque = aux;

                        // Definindo j = 1, pois ouve mudanças
                        j = 1;
                    }
                }
            }

            // exibindo o top 3, 5 ou 10 produtos com maior e menor estoque
            printf(" > Escolha uma opção: \n\n");
            printf("1. Mostrar tudo\n");

            // checa o numero de produtos para adequar o top 3, top 5 e top 10
            if (num_produtos >= 3)
            {
                printf("2. Top 3 maior e menor quantidade em estoque\n");
            }

            if (num_produtos >= 5)
            {
                printf("3. Top 5 maior e menor quantidade em estoque\n");
            }

            if (num_produtos >= 10)
            {
                printf("4. Top 10 maior e menor quantidade em estoque\n");
            }
            printf("5. Voltar pro menu\n");
            printf("0. Sair");

            printf("\n\nDigite a opção abaixo: ");
            scanf("%d", &ope);

            while (scanf("%d", &ope) != 1)
            {
                printf("\nDigite uma opção existente...");

                printf("\n\nDigite a opção abaixo: ");
                scanf("%d", &ope);
            }

            switch (ope)
            {
            // * SAI DO PROGRAMA
            case 0:
                return 0;
                break;

            // * MOSTRA TODOS DO ESTOQUE
            case 1:
                printf("\n\n>Maior quantidade: ");
                for (j = 0; j < num_produtos; j++)
                {
                    printf("\n> %dº ID: %d - %s: %d em estoque;\n", j + 1, produtos[j].id, produtos[num_produtos - 1 - j].nome, produtos[num_produtos - 1 - j].quantidade_estoque);
                }
                printf("\n\n>Menor quantidade:");
                for (j = 0; j < num_produtos; j++)
                {
                    printf("\n> %dº ID: %d - %s: %d em estoque;\n", j + 1, produtos[j].id, produtos[j].nome, produtos[j].quantidade_estoque);
                }

                break;

            // * MOSTRA O TOP 3
            case 2:
                printf("\n\n>Maior quantidade:");
                for (j = 0; j < 3; j++)
                {
                    printf("\n> %dº ID: %d - %s: %d em estoque;\n", j + 1, produtos[j].id, produtos[num_produtos - 1 - j].nome, produtos[num_produtos - 1 - j].quantidade_estoque);
                }
                printf("\n\n>Menor quantidade:");
                for (j = 0; j < 3; j++)
                {
                    printf("\n> %dº ID: %d - %s: %d em estoque;\n", j + 1, produtos[j].id, produtos[j].nome, produtos[j].quantidade_estoque);
                }

                break;

            // * MOSTRA O TOP 5
            case 3:
                printf("\n\n>Maior quantidade:");
                for (j = 0; j < 5; j++)
                {
                    printf("\n> %dº ID: %d - %s: %d em estoque;\n", j + 1, produtos[j].id, produtos[num_produtos - 1 - j].nome, produtos[num_produtos - 1 - j].quantidade_estoque);
                }
                printf("\n\n>Menor quantidade:");
                for (j = 0; j < 5; j++)
                {
                    printf("\n> %dº ID: %d - %s: %d em estoque;\n", j + 1, produtos[j].id, produtos[j].nome, produtos[j].quantidade_estoque);
                }

                break;

            // * MOSTRA O TOP 10
            case 4:
                printf("\n\n>Maior quantidade:");
                for (j = 0; j < 10; j++)
                {
                    printf("\n> %dº ID: %d - %s: %d em estoque;\n", j + 1, produtos[j].id, produtos[num_produtos - 1 - j].nome, produtos[num_produtos - 1 - j].quantidade_estoque);
                }
                printf("\n\n>Menor quantidade:");
                for (j = 0; j < 10; j++)
                {
                    printf("\n> %dº ID: %d - %s: %d em estoque;\n", j + 1, produtos[j].id, produtos[j].nome, produtos[j].quantidade_estoque);
                }

                break;

            // * VOLTA AO MENU PRINCIPAL
            case 5:
                sair = 1;
                break;

            default:
                printf("\nDigite uma opção válida, por favor.\n\n");
                break;
            }

            // volta ao menu principal
            if (sair != 0)
            {
                break;
            }

            break;

        // * CONSULTA LUCRO
        case 5:
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
        case 6:
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