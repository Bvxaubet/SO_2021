#include "so_t1.h"
#include <stdio.h>

#define TAM 20// o tamanho da memória

mem_t memoria; // Instancia de memoria
es_t entradaesaida;       // Instancia de ES
cpu_t computador;    // Instancia da Cpu
int main()
{
    //TESTES unitarios 
    //memoria.TesteDeMemoria();
    //entradaesaida.TesteDeEs();
    
    // programa para executar na nossa CPU
    /*
    int progr[TAM] = {  2, 0, 7, 2, 10, 5, 17,    //  0      ACC=0; X=0; ACC=10; MEM[17] = 10
                        8, 20, 1,                 //  7      ACC=X; es[1]=ACC;
                        9, 8, 11, 17, 18, 7,      // 10      x++; ACC=X; A-=mem[17];DESVNZ
                        1,                        // 16      FIM
                        0                         // 17 aqui tá o "l"
                    };
    */
    //int progr[TAM] = {5, 0, 0, 0, 0, 0, 1,0};
    ///*
    int progr[] = 
    {
        #include "ex1.maq"
    };
    //*/

    // variáveis que representam o computador
    memoria = memoria.mem_cria ( TAM);
    mem_t *mem = &memoria;

    entradaesaida = entradaesaida.es_cria(2);
    es_t *es = &entradaesaida;

    computador = computador.cpu_cria();
    cpu_t *cpu = &computador;

    cpu_t::cpu_estado_t est = computador.cpu_estado_cria();
    cpu_t::cpu_estado_t *estado = &est;
    
    
    // copia o programa para a memória
    for (int i = 0; i < TAM; i++) 
    {
        if ( memoria.mem_escreve(mem, i, progr[i]) != ERR_OK) {
            printf("Erro de memoria, endereco %d\n", i);
            exit(1);
        }
    }
    
    // inicializa a CPU com as variáveis criadas
    computador.cpu_altera_estado(cpu, estado);
    computador.cpu_altera_memoria(cpu, mem);
    computador.cpu_altera_es(cpu, es);
    
    //memoria.PrintTodaMemoria( cpu->mem);

    // executa uma instrução por vez até parar
    err_t err = ERR_OK;
    while (true) 
    {
        //cpu_t::cpu_PrintEstado ( cpu);
        err = cpu_t::cpu_executa_1( cpu);   
        //memoria.PrintTodaMemoria( cpu->mem);
        if ( err != ERR_OK && err < sizeof(err_t_string)) 
        {     
            printf("\n\n+++++++++++++++++++++++++++++++++");
            printf("\nErro na execucao: %d\n", err);
            printf("Tipo de erro: %s\n", err_t_string[err]);
            printf("Estado final:\n");
            cpu_t::cpu_PrintEstado ( cpu);
            break;
        }
    }
    // destroi todo mundo!
    return 0;
}