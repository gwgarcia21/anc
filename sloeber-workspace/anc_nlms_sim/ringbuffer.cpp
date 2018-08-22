/*
 * ringbuffer.cpp
 *
 *  Created on: 21 de out de 2017
 *      Author: Cliente
 */
#include "global_def.h"

#define MAXSIZE 64*128 // circular buffer size

struct ringbuffer {
    int16_t buffer[MAXSIZE];
    int rd_idx;
    int wr_idx;
    int tamanho;
};

RingBuffer * criarRB() {
    RingBuffer * tmp = (RingBuffer*)malloc(sizeof(RingBuffer));
    tmp->wr_idx = 0;
    tmp->rd_idx = 0;
    tmp->tamanho = 0;
    return tmp;
};

void destroiRB(RingBuffer * f) {
    free(f);
}

int rb_full(RingBuffer * f) {
    return (f->tamanho == MAXSIZE);
}

int rb_empty(RingBuffer * f) {
    return (f->tamanho == 0);
}

int rbTamanho(RingBuffer * f) {
    return f->tamanho;
}

int rbinsere(RingBuffer * f, int16_t d) {
    if(rb_full(f))
        return 0;
    f->buffer[f->wr_idx++]=d;
    f->wr_idx %= MAXSIZE;
    f->tamanho++;
    return 1;
}

int16_t rbretira(RingBuffer * f) {
    if(rb_empty(f))
        return 0;
    int16_t tmp = f->buffer[f->rd_idx++];
    f->rd_idx %= MAXSIZE;
    f->tamanho--;
    return tmp;
}

/// Debug
void print_rb(RingBuffer * f) {
    int i;
    for(i = 0; i < MAXSIZE; i++) {
    	Serial.print(f->buffer[i]);
    }
    Serial.println("");

    for(i = 0; i < (f->rd_idx*4+2); i++)
    	Serial.print(" ");
    Serial.println("r");

    for(i = 0; i < (f->wr_idx*4+2); i++)
    	Serial.print(" ");
    Serial.println("w");
}

/// Debug
void insere_buf(RingBuffer * buf, int16_t dado) {
    if(rbinsere(buf,dado))
        Serial.println("Dado inserido com sucesso!");
    else
    	Serial.println("Erro ao inserir dado, buffer cheio!");
    print_rb(buf);
}

/// Debug
void remove_buf(RingBuffer * buf) {
    if(rb_empty(buf))
    	Serial.println("O RingBuffer está vazio!");
    else {
    	Serial.print("O dado retirado do buffer é: ");
    	Serial.println((unsigned int)rbretira(buf));
    }
    print_rb(buf);
}

