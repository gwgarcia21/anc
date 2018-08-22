#ifndef RINGBUFFER_H_INCLUDED
#define RINGBUFFER_H_INCLUDED

/* Interface da Estrutura de Dados - Fila Circular */

typedef struct ringbuffer RingBuffer;

/* Fun��o cria uma fila, retornando um
   ponteiro para a mesma
 */
RingBuffer * criarRB();

/* Fun��o destr�i fila.
    Parametro f � um ponteiro para pilha a ser destruida
 */
void destroiRB(RingBuffer * f);

int rb_full(RingBuffer * f);
int rb_empty(RingBuffer * f);

/* Fun��o retorna o n�mero de elementos da fila */
int rbTamanho(RingBuffer * f);

/*
    Adiciona na fila
    Retorna true(1) ou false(0)
 */
int rbinsere(RingBuffer * f, int16_t d);

/*
    Retira um dado da fila
    Retorna o dado retirado
 */
int16_t rbretira(RingBuffer * f);

void print_rb(RingBuffer * f);

void insere_buf(RingBuffer * buf, int16_t dado);

void remove_buf(RingBuffer * buf);

#endif // RINGBUFFER_H_INCLUDED
