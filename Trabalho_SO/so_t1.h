#ifndef _SO_T1_H_
#define _SO_T1_H_
#include <stdlib.h>
#include <stdio.h>
#include <string>

typedef enum {
    ERR_OK = 0,
    ERR_MEM_END_INV,  // acesso a endereço de memória inválido
    ERR_ES_DISP_INV,  // acesso a dispositivo inexistente
    ERR_ES_OP_INV,    // operação inválida em dispositivo
    ERR_CPU_PARADA,   // CPU executou instrução PARA
    ERR_CPU_INSTR_INV // tentativa de execução de instrução inexistente
    } err_t;

static const char *err_t_string[] ={
    "ERR_OK",
    "ERR_MEM_END_INV",
    "ERR_ES_DISP_INV",
    "ERR_ES_OP_INV",
    "ERR_CPU_PARADA",
    "ERR_CPU_INSTR_IN"
    };

class mem_t
{
  public:
    int *mem; // ponteiro para inicio da memoria
    int size; // tamanho da memoria
    
    /**
     * Cria um objeto do tipo mem_t
     * 
     * @param tam Tamanho do vetor de inteiros a ser criado.
     * @return Objeto do tipo mem_t.
     */ 
    mem_t mem_cria ( int tam)
    {
        mem_t memoria;
        memoria.size = tam;
        memoria.mem = (int*) malloc ( tam * sizeof (int));        
        return memoria;
    }
    
    /**
     * Cria um objeto do tipo mem_t
     * 
     * @param m Ponteiro para objeto do tipo mem_t.
     * @return Tamanho da memoria de inteiros.
     */ 
    static int mem_tam( mem_t *m)
    {
        return m->size;
    }

    /**
     * Libera o ponteiro da memoria
     * 
     * @param m Ponteiro para objeto do tipo mem_t.
     */ 
    void mem_destroi( mem_t *m)
    {
        free(m);
    }

    /**
     * Le um valor da memoria
     * 
     * @param m Ponteiro para um objeto do tipo mem_t.
     * @param endereco Endereco inteiro da memoria.
     * @param pvalor Valor que recebera o conteudo lido.
     * @return Tipo de erro encontrado.
     */ 
    static err_t mem_le( mem_t *m, int endereco, int *pvalor)
    {
        if ( endereco >= mem_tam(m) )
        {       
            return ERR_MEM_END_INV;
        }
        else
        {   
            *pvalor =  ( m->mem[endereco]);
            return ERR_OK;
        }
    }

    /**
     * Escreve um valor na memoria
     * 
     * @param m Ponteiro para um objeto do tipo mem_t.
     * @param endereco Endereco inteiro da memoria.
     * @param pvalor Valor que sera escrito.
     * @return Tipo de erro encontrado.
     */
    static err_t mem_escreve( mem_t *m, int endereco, int valor)
    {
        if ( endereco > mem_tam(m)  || endereco < 0)
        {
            return ERR_MEM_END_INV;
        }
        else
        {
            m->mem[endereco] = valor;
            return ERR_OK;
        }
    }

    /**
     * Metodo de debug, mostra toda a memoria
     * 
     * @param m Ponteiro para um objeto do tipo mem_t.
     */
    void PrintTodaMemoria( mem_t *m)
    {
        int p;
        int i = 0;
        printf("\nConteudo da memoria\n***********************\n");
        while( mem_le(m, i, &p) == ERR_OK)
        {
            printf(" %d ", p);
            i++;
        }
        printf("\n***********************\n");
    }

     /**
     * Metodo de teste, cria uma instancia de uma nova memoria e realiza operacoes com ela
     */
    void TesteDeMemoria()
    {
        mem_t m;
        err_t err;
        int q;
        m = mem_cria( 12);
        mem_t *memT = &m;

        printf("Tesde de memoria\n\n");
        for( int i = 0; i < memT->size; i++)
        {
            int escrito = i*2;
            err = mem_escreve( memT, i, escrito);
            printf("Valor %d escrito: %d\n", i,  escrito); 
        } 

        PrintTodaMemoria( memT);          

        for( int i = 0; i < memT->size; i++)
        {
            err  = mem_le ( memT, i, &q);            
            printf("Valor %d lido: %d\n", i,  q);                        
        } 

        PrintTodaMemoria( memT);
        mem_destroi(memT);
    }
};
   
class es_t
{
    // DISPOSITOVP - 0 = TECLADO
    // DISPOSITIVO - 1 = TERMINAL
  public:
    int NumeroDeDispositivos;
    int MaxBufferSize;

    /**
     * Cria um objeto do tipo es_t
     * 
     * @param tam Numero de dispositivos disponiveis
     * @return Objeto do tipo es_t.
     */ 
    es_t es_cria( int n)
    {
        es_t es;
        es.NumeroDeDispositivos = n;
        return es;
    }

    /**
     * Cria um objeto do tipo es_t
     * 
     * @param es Ponteiro para objeto do tipo es_t
     * @param dispositivo Id do dispositivo a ser acessado
     * @param pvalor Endereco do valor que recebera o dado lido
     * @return Erro de dispositivo invalido.
     */ 
    static err_t es_le( es_t *es, int dispositivo, int *pvalor)
    {
        if ( dispositivo == 1) 
        {
            return ERR_ES_DISP_INV;
        }
        else
        {
            scanf("%d", pvalor); 
            return ERR_OK;
        }
    }

    /**
     * Cria um objeto do tipo es_t
     * 
     * @param es Ponteiro para objeto do tipo es_t
     * @param dispositivo Id do dispositivo a ser acessado
     * @param pvalor Valor do dado que sera escrito
     * @return Erro de dispositivo invalido.
     */
    static err_t es_escreve( es_t *es, int dispositivo, int valor)
    {
        if ( dispositivo == 0)
        {
            return ERR_ES_DISP_INV;
        }
        else 
        {
            printf("%d", valor);
            return ERR_OK;
        }
    }
    
    /**
     * Metodo de teste, cria uma instancia de es e realiza operacoes com ela
     */
    void TesteDeEs()
    {
        es_t ES = es_cria(2);
        int p;
        err_t err;
        es_t *es = &ES;

        err = es_le( es, 0, &p);
        printf("Valor lido: ");

        err = es_escreve( es, 1, p);
        printf("\nERRO : %d", err);
    }

};

class cpu_t
{
  public:
    typedef enum {
        NOP = 0,    // Nao faz nada
        PARA,       // Para a CPU
        CARGI,
        CARGM,
        CARGX,
        ARMM,
        ARMX,
        MVAX,
        MVXA,
        INCX,
        SOMA,
        SUB,
        MULT,
        DIV,
        RESTO,
        NEG,
        DESV,
        DESVZ,
        DESVNZ,
        LE,
        ESCR
        } INSTRU;

    /**
     * Struct do tipo complemento que guarda mais informacaos sobre os erros
     */
    struct complemento
    {
        int Adress;
        err_t TipoDeErro; 
    };

    /**
     * Struct que guarda todos os dados e registradores da CPU
     */
    struct cpu_estado_t
    {
        int PC;
        int ACC;  
        int AUX;    
        int A1;      // Argumento 1
        err_t MODO;  // Modo da cpu
        complemento CDP; // Complemento de parada
    };

    cpu_estado_t ESTADO;  // Estado do PC  
    mem_t *mem;           // Ponteiro para a memoria conectada ao PC
    es_t *es;             // Ponteiro para a es conectada ao PC

    /**
     * Cria um objeto do tipo cpu_t
     * 
     * @return Objeto do tipo cpu_t
     */
    cpu_t cpu_cria()
    {
        cpu_t cpu;
        return cpu;
    }

    /**
     * Cria um novo estado de CPU zerado
     * 
     * @return Struct de cpu_estado_t.
     */
    cpu_estado_t cpu_estado_cria ()
    {
        ESTADO.PC  = 0;
        ESTADO.ACC = 0;
        ESTADO.AUX = 0;
        ESTADO.A1  = 0;
        ESTADO.MODO = ERR_OK;
        ESTADO.CDP.Adress = 0;
        ESTADO.CDP.TipoDeErro = ERR_OK;
        return ESTADO;
    }
    
    /**
     * Atribui um novo estado para a cpu
     * 
     * @param cpu Ponteiro para cpu que recebera o estado
     * @param estado Estado para ser atribuido
     */
    void cpu_altera_estado( cpu_t *cpu, cpu_estado_t *estado )
    {
        cpu->ESTADO = *estado;
    }
    
    /**
     * Atribui uma nova momoria para a cpu
     * 
     * @param cpu Ponteiro para cpu que recebera o estado
     * @param mem Ponteiro para memoria que sera atribuida
     */
    void cpu_altera_memoria( cpu_t *cpu, mem_t *mem)
    {
        cpu->mem = mem;
    }
    
    /**
     * Atribui um novo estado para a cpu
     * 
     * @param cpu Ponteiro para cpu que recebera o estado
     * @param es Entrada e Saida para ser atribuido
     */
    void cpu_altera_es( cpu_t *cpu, es_t *es)
    {
        cpu->es = es;
    }
     
    /**
     * Retorna o estado atual da cpu
     * 
     * @param est Ponteiro para ser retornado
     * @return Estado atual da cpu
     */
    cpu_estado_t *cpu_estado( cpu_t *est)
    {
        return &est->ESTADO;
    }

    /**
     * CPU do programa, le interpreta e executa as operacoes
     * 
     * @param cpu Ponteiro para cpu que executara
     * @return Erros de execucao
     */
    static err_t cpu_executa_1( cpu_t *cpu)
    {
        int inst; // Instrução lida da memoria
        err_t exec_err = ERR_OK; // Tipo de erro
        exec_err = mem_t::mem_le( cpu->mem, cpu->ESTADO.PC, &inst);
        if ( exec_err != ERR_OK)
        {           
            cpu->ESTADO.CDP.Adress = cpu->ESTADO.PC;
            cpu->ESTADO.CDP.TipoDeErro = exec_err;
            return exec_err;
        }

        switch( inst)
        {
            case NOP:
                cpu->ESTADO.PC++; 
            break;

            case PARA:
                cpu->ESTADO.MODO = ERR_CPU_PARADA;
                return ERR_CPU_PARADA;
            break;

            case CARGI: // A = A1 ;carrega imediato
                cpu->ESTADO.PC++; 
                exec_err = mem_t::mem_le( cpu->mem, cpu->ESTADO.PC, &inst);
                if ( exec_err != ERR_OK) break;
                
                cpu->ESTADO.A1 = inst;
                cpu->ESTADO.ACC = cpu->ESTADO.A1;
                    
                cpu->ESTADO.PC++;   
                
            break;

            case CARGM: // A = mem[A1] ;carrega da memória
                cpu->ESTADO.PC++;
                exec_err = mem_t::mem_le( cpu->mem, cpu->ESTADO.PC, &inst);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.A1 = inst;
                exec_err = mem_t::mem_le( cpu->mem, cpu->ESTADO.A1, &inst);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.ACC = inst;
                
                cpu->ESTADO.PC++;
            break;

            case CARGX: // A = mem[A1+X]	;carrega indexado
                cpu->ESTADO.PC++;
                exec_err = mem_t::mem_le( cpu->mem, cpu->ESTADO.PC, &inst);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.A1 = inst;
                cpu->ESTADO.ACC = cpu->ESTADO.A1 + cpu->ESTADO.AUX;
                
                cpu->ESTADO.PC++;
            break;

            case ARMM: // mem[A1] = A	;armazena na memória
                cpu->ESTADO.PC++;
                exec_err = mem_t::mem_le( cpu->mem, cpu->ESTADO.PC, &inst);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.A1 = inst;
                exec_err = mem_t::mem_escreve( cpu->mem, cpu->ESTADO.A1, cpu->ESTADO.ACC);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.PC++;
            break;

            case ARMX: // mem[A1+X] = A	;armazena indexado
                cpu->ESTADO.PC++;
                exec_err = mem_t::mem_le( cpu->mem, cpu->ESTADO.PC, &inst);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.A1 = inst + cpu->ESTADO.AUX;
                exec_err = mem_t::mem_escreve( cpu->mem, cpu->ESTADO.A1, cpu->ESTADO.ACC);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.PC++;
            break;

            case MVAX: // X = A	;inicializa X
                cpu->ESTADO.AUX = cpu->ESTADO.ACC;

                cpu->ESTADO.PC++;
            break;

            case MVXA: // A = X	;recupera X
                cpu->ESTADO.ACC = cpu->ESTADO.AUX;

                cpu->ESTADO.PC++;
            break;

            case INCX: // X++	;incrementa X
                cpu->ESTADO.AUX++;

                cpu->ESTADO.PC++;
            break;

            case SOMA: // A += mem[A1]	;soma
                cpu->ESTADO.PC++;
                exec_err = mem_t::mem_le( cpu->mem, cpu->ESTADO.PC, &inst);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.A1 = inst;
                exec_err = mem_t::mem_le( cpu->mem, cpu->ESTADO.A1, &inst);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.A1 = inst;
                cpu->ESTADO.ACC += cpu->ESTADO.A1;

                cpu->ESTADO.PC++;
            break;

            case SUB: // A -= mem[A1]	;subtração
                cpu->ESTADO.PC++;
                exec_err = mem_t::mem_le( cpu->mem, cpu->ESTADO.PC, &inst);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.A1 = inst;
                exec_err = mem_t::mem_le( cpu->mem, cpu->ESTADO.A1, &inst);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.A1 = inst;
                cpu->ESTADO.ACC -= cpu->ESTADO.A1;

                cpu->ESTADO.PC++;
            break;

            case MULT: // A *= mem[A1]	;multiplicação
                cpu->ESTADO.PC++;
                exec_err = mem_t::mem_le( cpu->mem, cpu->ESTADO.PC, &inst);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.A1 = inst;
                exec_err = mem_t::mem_le( cpu->mem, cpu->ESTADO.A1, &inst);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.A1 = inst;
                cpu->ESTADO.ACC *= cpu->ESTADO.A1;

                cpu->ESTADO.PC++;
            break;

            case DIV: //A /= mem[A1]	;divisão
                cpu->ESTADO.PC++;
                exec_err = mem_t::mem_le( cpu->mem, cpu->ESTADO.PC, &inst);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.A1 = inst;
                exec_err = mem_t::mem_le( cpu->mem, cpu->ESTADO.A1, &inst);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.A1 = inst;
                cpu->ESTADO.ACC /= cpu->ESTADO.A1;

                cpu->ESTADO.PC++;
            break;
            

            case RESTO: // A %= mem[A1]	;resto
                cpu->ESTADO.PC++;
                exec_err = mem_t::mem_le( cpu->mem, cpu->ESTADO.PC, &inst);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.A1 = inst;
                exec_err = mem_t::mem_le( cpu->mem, cpu->ESTADO.A1, &inst);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.A1 = inst;
                cpu->ESTADO.ACC %= cpu->ESTADO.A1;

                cpu->ESTADO.PC++;
            break;

            case NEG: // A =-A	;negação
                cpu->ESTADO.ACC = -cpu->ESTADO.ACC;

                cpu->ESTADO.PC++;
            break;

            case DESV: // PC = A1	;desvio
                cpu->ESTADO.PC++;
                exec_err = mem_t::mem_le( cpu->mem, cpu->ESTADO.PC, &inst);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.A1 = inst;
                cpu->ESTADO.PC = cpu->ESTADO.A1;
            break;

            case DESVZ: // se A for 0, PC = A1	;desvio condicional
                cpu->ESTADO.PC++;
                exec_err = mem_t::mem_le( cpu->mem, cpu->ESTADO.PC, &inst);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.A1 = inst;
                if( cpu->ESTADO.ACC == 0)
                {
                    cpu->ESTADO.PC = cpu->ESTADO.A1;
                }
                else
                {
                    cpu->ESTADO.PC++;
                }
            break;

            case DESVNZ: // se A não for 0, PC = A1	;desvio condicional
                cpu->ESTADO.PC++;
                exec_err = mem_t::mem_le( cpu->mem, cpu->ESTADO.PC, &inst);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.A1 = inst;
                if( cpu->ESTADO.ACC != 0)
                {
                    cpu->ESTADO.PC = cpu->ESTADO.A1;
                }
                else
                {
                    cpu->ESTADO.PC++;
                }
            break;

            case LE: // A = es[A1]	;leitura de E/S
                cpu->ESTADO.PC++;
                exec_err = mem_t::mem_le( cpu->mem, cpu->ESTADO.PC, &inst);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.A1 = inst;

                exec_err = es_t::es_le( cpu->es, cpu->ESTADO.A1, &cpu->ESTADO.ACC);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.PC++;
            break;

            case ESCR: // es[A1] = A	;escrita de E/S
                cpu->ESTADO.PC++;
                exec_err = mem_t::mem_le( cpu->mem, cpu->ESTADO.PC, &inst);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.A1 = inst;
                exec_err = es_t::es_escreve( cpu->es, cpu->ESTADO.A1, cpu->ESTADO.ACC);
                if ( exec_err != ERR_OK) break;
                cpu->ESTADO.PC++;
            break;
           
            default:
                printf("Nao era para chegar aqui");
            break;
        }
        if ( exec_err != ERR_OK)
        {           
            cpu->ESTADO.CDP.Adress = cpu->ESTADO.PC;
            cpu->ESTADO.CDP.TipoDeErro = exec_err;
            return exec_err;
        }
    }

    /**
     * Mostra o estado atual da cpu
     * 
     * @param cpu Ponteiro para cpu que sera mostrada
     */
    static void cpu_PrintEstado( cpu_t *cpu)
    {
        printf("PC  :%d\n",          cpu->ESTADO.PC);
        printf("ACC :%d\n",          cpu->ESTADO.ACC);
        printf("AUX :%d\n",          cpu->ESTADO.AUX);
        printf("A1  :%d\n",          cpu->ESTADO.A1);
        printf("MODO :%d\n",         cpu->ESTADO.MODO);
        printf("ADRESS :%d\n",       cpu->ESTADO.CDP.Adress);
        printf("TIPO DE ERRO :%d\n", cpu->ESTADO.CDP.TipoDeErro);
    }

};


#endif