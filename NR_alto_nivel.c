#include <stdio.h>

int sqrt(int x, int i)
{

    if (i == 0)
    {
        return 1;
    }

    if (i > 0)
    {

        int result = sqrt(x, i - 1);

        return (result + (x / result)) / 2;
    }
}

int main()
{
    printf("Programa de Raiz Quadrada – Newton-Raphson\n");
    printf("Desenvolvedores: Bernardo Garcia, Luiz Henrique Saggin Confortin, Marco Antônio De Carli Rodegheri e Roger Rozales Ehlert\n\n");

    int x, i;

    while (1)
    {
        printf("Digite os parâmetros x e i para calcular sqrt_nr (x, i) ou -1 para abortar a execução\n");
        printf("x: ");
        scanf("%d", &x);

        printf("i: ");
        scanf("%d", &i);

        if (x < 0 || i < 0)
        {
            break;
        }

        int result = sqrt(x, i);
        printf("sqrt(%d, %d) = %d\n\n", x, i, result);
    }

    return 0;
}
