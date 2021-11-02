   #include "so_t1.h"
   #include <stdio.h>

  /* void imprime_estado(cpu_estado_t *est)
   {
     //...
   }*/
   
   #define TAM 20 // o tamanho da memória
   
   int main()
   {
       Memoria m;
       m.TesteDeMemoria();
    
    
    /*    
      // programa para executar na nossa CPU
      int progr[TAM] = { 2, 0, 7, 2, 10, 5, 17,    //  0      x=0; l=10
                         8, 20, 1,                 //  7 ali: print x
                         9, 8, 11, 17, 18, 7,      // 10      if ++x != l goto ali
                         1,                        // 16      FIM
                         0                         // 17 aqui tá o "l"
                       };
                    
      // variáveis que representam o computador
      mem_t *mem = mem_cria(TAM);
      es_t *es = es_Bcria();
      cpu_t *cpu = cpu_cria();
      cpu_estado_t *estado = cpu_estado_cria();
      
      // copia o programa para a memória
      for (int i = 0; i < TAM; i++) {
        if (mem_escreve(mem, i, progr[i]) != ERR_OK) {
          printf("Erro de memoria, endereco %d\n", i);
          exit(1);
        }
      }
      
      // inicializa a CPU com as variáveis criadas
      cpu_altera_estado(cpu, estado);
      cpu_altera_memoria(cpu, mem);
      cpu_altera_es(cpu, es);
      
      // executa uma instrução por vez até parar
      while (true) {
        imprime_estado(cpu_estado(cpu));
        err_t err = cpu_executa_1(cpu);
        if (err != ERR_OK) {
          printf("Erro na execução: %d\n", err);
          printf("Estado final:\n");
          imprime_estado(cpu_estado(cpu));
          break;
        }
      }
      
      
      */// destroi todo mundo!
      return 0;
   }