/*
O programa avalia qual é, dentre 3 alunos, o com maior CRA e salva em um arquivo;

Dados de entrada:
-Numero de Matricula(Numero inteiro);
-Nome(até 30 caracteres);
-CRA(0<=CRA<=100);

O programa lê os dados de entrada de um arquivo e escreve o resultado em outro arquivo,
o nome dos arquivos devem ser passados em tempo de lançamento;
    Exemplo:
        ./a.out dados.txt logs.txt
        (O primeiro a ser passado é onde os dados devem estar e o segundo onde o resultado é salvo);

Por Gustavo Ventino
Em 2022
*/

#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX 30

struct  //struct com os dados necessários pra localtime()
{     
   int tm_min;         /* minutes, range 0 to 59           */
   int tm_hour;        /* hours, range 0 to 23             */
   int tm_mday;        /* day of the month, range 1 to 31  */
   int tm_mon;         /* month, range 0 to 11             */
   int tm_year;        /* The number of years since 1900   */
   int tm_wday;        /* day of the week, range 0 to 6    */
} tm;

typedef struct //struct com os dados dos alunos
{
    int m;
    char n[MAX+1];
    float cra;
} Estu;


int
main( int argc, char *argv[ ] )
{
    int i; //contador
    
    //definição do arquivo de dados
    FILE* fp = NULL;     
    fp = fopen (argv[1], "r");
    //definição do arquivo de logs
    FILE* ft = NULL;
    ft = fopen(argv[2], "w");

    Estu estu[3];//declaração do array de structs para 3 alunos
    
    //declaração do struct onde teremos o maior CRA guardado
    Estu estum;
    estum.cra = 0;
    
    //declarações necessárias para a localtime()
    time_t rawtime;
    struct tm *info;
    time( &rawtime );
    info = localtime( &rawtime );
        
    //desvio para caso n sejam passados argumentos o suficiente
    if(argc<=2)
    {
        fprintf(stderr, "falta de argumentos\n");
        return -1;
    }

    else
    {
        //desvios para caso haja algo de errado com os arquivos passados
        if( fp == NULL)
        {
            fprintf(stderr, "impossível abrir o arquivo\n");
            return -1;
        }
	   else if(ft == NULL)
        {
            fprintf(stderr, "Impossível abrir o arquivo de logs");
            return -1;
        }

        //desvio para caso não haja problema com os arquivos passados
        else
        {
            /*
            laço que lê linha a linha e salva as variáveis nos structs respectivos
            e já compara os seus valores
            */
            for(i=0; fscanf(fp, "%d %[^0-9] %f", &estu[i].m, estu[i].n, &estu[i].cra) != EOF; i++)
            {
                if(estu[i].cra > estum.cra)
                {
                    estum.cra = estu[i].cra;
                    estum.m = estu[i].m;
                    strcpy(estum.n, estu[i].n);
                }
            }
                //Gravação dos resultados no arquivo de logs passado pelo usuário
                fprintf(ft,"%s", asctime(info));
                fprintf(ft ,"---------------------------------------------------\n");
                fprintf(ft ," O maior CRA é:\n %f\n\n Pertence a:\n %s\n\n Matrícula:\n %d\n", estum.cra, estum.n, estum.m);
                fprintf(ft ,"---------------------------------------------------\n");

                printf("Obrigado pela preferência!\n");
		}
        //Fechamento dos arquivos
        fclose(fp);
	    fclose(ft);
        //fim do programa
        return 0;
    }
}
