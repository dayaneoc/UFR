/* BSD 2-Clause License
 * 
 * Copyright (c) 2024, Visao Robotica e Imagem (VRI)
 *  - Felipe Bombardelli <felipebombardelli@gmail.com>
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// ============================================================================
//  Header
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ufr_buffer.h"

/*
void mostrar_u64(const char* filename, int line, uint64_t current, uint64_t expected) {
    printf("Error:%s:%d: the value is %lu, but expected %lu\n", filename, line, current, expected ); 
    exit(1);
}
*/

// ============================================================================
//  Buffer
// ============================================================================

/**
 * @brief Create a new buffer
 * 
 * @return ufr_buffer_t* 
 */

/* Cria um novo buffer */
ufr_buffer_t* ufr_buffer_new() {
    ufr_buffer_t* buffer = malloc(sizeof(ufr_buffer_t));
    
    if (buffer == NULL) { 
        return NULL;
    } 
    ufr_buffer_init(buffer);
    return buffer;
}

/**
 * @brief Buffer Constructor
 * 
 * @param buffer Buffer object
 */

/* Inicializa buffer */
void ufr_buffer_init(ufr_buffer_t* buffer) {
    buffer->size = 0;
    buffer->max = MESSAGE_ITEM_SIZE;
    buffer->ptr = malloc(buffer->max);
}

/**
 * @brief Buffer Destructor
 * 
 * @param buffer 
 */

/* Libera a memória alocada para o buffer, se o ponteiro não for NULL. */
void ufr_buffer_free(ufr_buffer_t* buffer) {
    if (buffer == NULL) { 
        printf ("Falha ao liberar memoria!");
        return;
    }
    free(buffer->ptr);
    buffer->ptr = NULL;
    buffer->max = 0;
    buffer->size = 0;
}

/**
 * @brief Clear data of the buffer
 * 
 * @param buffer Buffer object
 */

/* Zera o campo size do buffer, indicando que o buffer está vazio
 * (os dados anteriores são considerados inválidos). */
void ufr_buffer_clear(ufr_buffer_t* buffer) {
    buffer->size = 0;
}

/**
 * @brief Check if the buffer has space enough with increment of the size
 * 
 * @param buffer Buffer object
 * @param size increment size
 */

/* Verifica se o buffer tem espaço suficiente para acomodar um incremento
 * de tamanho (plus_size). */
void ufr_buffer_check_size(ufr_buffer_t* buffer, size_t plus_size) {
    if (!buffer) {
        fprintf (stderr,"Buffer invalido!");
        exit (1);
    }
    //printf ("%d, %d, %d\n", buffer->size, plus_size , buffer->max);
    while (buffer->size + plus_size > buffer->max) {
        const size_t new_max = buffer->max * 2;
        char* new_ptr = realloc(buffer->ptr, new_max);

        if (!new_ptr) {
            fprintf (stderr,"Ponteiro invalido!");
        exit (1);
        }
        buffer->max = new_max;
        buffer->ptr = new_ptr;
    }
}   
    

/**
 * @brief Put text in the buffer
 * 
 * @param buffer Buffer object
 * @param text text to be put
 * @param size size of text
 */

/* Adiciona um bloco de dados ao buffer.*/
void ufr_buffer_put(ufr_buffer_t* buffer, const char* text, size_t size) {
    if (!buffer) {
        fprintf (stderr,"Buffer invalido!");
        exit (1);
    }
    ufr_buffer_check_size(buffer, size); //Verifica se há espaço suficiente no buffer
    memcpy(&buffer->ptr[buffer->size], text, size); //Copia os dados para o buffer
    buffer->size += size; //atualiza o tamanho atual do buffer 
}

/**
 * @brief put a char in the buffer
 * 
 * @param buffer Buffer object
 * @param val charachter which to be inserted
 */

/* Adiciona um único caractere ao buffer. */
void ufr_buffer_put_chr(ufr_buffer_t* buffer, char val) {
    if (!buffer) {
        fprintf (stderr,"Buffer invalido!");
        exit (1);
    }
    ufr_buffer_check_size(buffer, 1); 
    buffer->ptr[buffer->size] = val;
    buffer->size += 1; 
}

/**
 * @brief put an unsigned int of 8bit as string
 * 
 * @param buffer Buffer object
 * @param val unsigned int value to be converted and inserted
 */

/*Converte um valor uint8_t (inteiro sem sinal de 8 bytes) em uma string
 * e a adiciona ao buffer. */
void ufr_buffer_put_u8_as_str(ufr_buffer_t* buffer, uint8_t val) {
    if (!buffer) {
        fprintf (stderr,"Buffer invalido!");
        exit (1);
    } 
        
    ufr_buffer_check_size(buffer, 5); // Redimensiona, caso necessário. 
    char* base = &buffer->ptr[buffer->size];
    size_t size;

    /* Se o buffer estiver vazio, o valor é adicionado sem espaço antes.
    * Caso contrário, um espaço é adicionado antes do valor.*/
    if ( buffer->size == 0 ) {
        size = snprintf(base, 8, "%u", val);
    } else {
        size = snprintf(base, 8, " %u", val);
    }
    buffer->size += size;  
}

/**
 * @brief put an int of 8bit as string
 * 
 * @param buffer Buffer object
 * @param val int value to be converted and inserted
 */

/*Similar à função ufr_buffer_put_u8_as_str, mas para valores int8_t
 * (inteiro com sinal de 8 bytes). */
void ufr_buffer_put_i8_as_str(ufr_buffer_t* buffer, int8_t val) {
    if (!buffer) {
        fprintf (stderr, "Buffer invalido!");
        exit (1);
    }

    ufr_buffer_check_size(buffer, 5);
    char* base = &buffer->ptr[buffer->size];
    size_t size;
    if ( buffer->size == 0 ) {
        size = snprintf(base, 8, "%d", val);
    } else {
        size = snprintf(base, 8, " %d", val);
    }
    buffer->size += size;
}

/**
 * @brief put an unsigned int as string
 * 
 * @param buffer Buffer object
 * @param val int value to be converted and inserted
 */

/*Converte um valor uint32_t (inteiro sem sinal de 32 bytes) em uma string
 * e a adiciona ao buffer. */
void ufr_buffer_put_u32_as_str(ufr_buffer_t* buffer, uint32_t val) {
    if (!buffer) {
        fprintf (stderr, "Buffer invalido!");
        exit (1);
    }
    ufr_buffer_check_size(buffer, 12);
    char* base = &buffer->ptr[buffer->size];
    size_t size = 0;
    if ( buffer->size == 0 ) {
        size = snprintf(base, 12, "%u", val);
    } else {
        size = snprintf(base, 12, " %u", val);
    }
    buffer->size += size;
}

/**
 * @brief put an int as string
 * 
 * @param buffer Buffer object
 * @param val int value to be converted and inserted
 */

/* Similar à função ufr_buffer_put_u32_as_str, mas para valores int32_t 
 * (inteiro com sinal de 32 bytes). */
void ufr_buffer_put_i32_as_str(ufr_buffer_t* buffer, int32_t val) {
    ufr_buffer_check_size(buffer, 32);
    char* base = &buffer->ptr[buffer->size];
    size_t size = 0;
    if ( buffer->size == 0 ) {
        size = snprintf(base, 32, "%d", val);
    } else {
        size = snprintf(base, 32, " %d", val);
    }
    buffer->size += size;
}

/**
 * @brief put an float as string
 * 
 * @param buffer Buffer object
 * @param val float value to be converted and inserted
 */

/* Converte um valor float em uma string e a adiciona ao buffer.
 * Funciona de forma semelhante às funções anteriores, mas para valores
 * de ponto flutuante. */
void ufr_buffer_put_f32_as_str(ufr_buffer_t* buffer, float val) {
    ufr_buffer_check_size(buffer, 32);
    char* base = &buffer->ptr[buffer->size];
    size_t size = 0;
    if ( buffer->size == 0 ) {
        size = snprintf(base, 32, "%f", val);
    } else {
        size = snprintf(base, 32, " %f", val);
    }
    buffer->size += size;
}

/**
 * @brief put a string
 * 
 * @param buffer Buffer object
 * @param val string to be inserted to the buffer
 */

/* Adiciona uma string (text) ao buffer. */
void ufr_buffer_put_str(ufr_buffer_t* buffer, const char* text) {
    const size_t size = strlen(text); // Calcula o tamanho da string 
    ufr_buffer_check_size(buffer, size); // Verifica se há espaço suficiente no buffer 
    ufr_buffer_put(buffer, text, size); // Adiciona a string usando
}