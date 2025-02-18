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

#include "ufr_buffer.h"
#include "ufr_test.h"
#include "assert.h"

// ============================================================================
//  Tests
// ============================================================================

// Criar um novo buffer
void test_buffer_init () {
    printf ("Iniciando testes...\n");

    ufr_buffer_t buffer;
    ufr_buffer_init (&buffer); // Inicializa o buffer
    UFR_TEST_EQUAL_U64 ( buffer.size, 0L ); /* Verifica se o tamanho inicial do buffer é 0 */ 
    UFR_TEST_EQUAL_U64 ( buffer.max, MESSAGE_ITEM_SIZE ); /* Verifica se a capacidade máxima do
                                                          * buffer é igual a MESSAGE_ITEM_SIZE 
                                                          * (um valor definido em algum lugar do código). */
    UFR_TEST_TRUE (&buffer);   
    ufr_test_print_result ();                                                    
}

void test_buffer_new () {
    
    ufr_buffer_t* buffer = ufr_buffer_new (); /* Cria um novo buffer dinamicamente*/
    UFR_TEST_NOT_NULL (buffer); /* Verifica se o ponteiro retornado não é NULL */
    
    ufr_test_print_result ();                          
}

void test_buffer_free () {

    ufr_buffer_t* buffer;
    ufr_buffer_free (buffer);
    UFR_TEST_EQUAL_U64 (buffer->ptr, NULL);
    
    ufr_test_print_result ();
}

void test_buffer_clear () {
   
    ufr_buffer_t* buffer = ufr_buffer_new ();
    UFR_TEST_NOT_NULL (buffer);
    ufr_buffer_put_chr (buffer, 1);
    ufr_buffer_clear (buffer);
    UFR_TEST_ZERO (buffer->size);

    ufr_test_print_result ();
}

void ufr_buffer_print (ufr_buffer_t* buffer) {

    UFR_TEST_NOT_NULL (buffer);
    printf ("BUFFER: SIZE= %d, MAX= %d, DATA= %.*s\n", buffer->size, buffer->max, (int)buffer->size, buffer->ptr);

}
void test_check_size () {

    ufr_buffer_t* buffer = ufr_buffer_new ();
    UFR_TEST_NOT_NULL (buffer);
    UFR_TEST_EQUAL_U64 (buffer->size, 0L);
    UFR_TEST_EQUAL_U64 (buffer->max, MESSAGE_ITEM_SIZE);
    
    // Estado inicial
    printf ("1) Estado inicial do buffer:\n");
    ufr_buffer_print (buffer);

    // Adiciona dados ao buffer (menor que o tamanho inicial)
    const char* data1 = "12345";
    ufr_buffer_put (buffer, data1, strlen(data1));
    printf ("2) Adicionado dados < ou == ao tamanho max do buffer\n", data1);
    ufr_buffer_print (buffer);
    
    //Adiciona mais dados para testar redimesionamento.
    const char* data2 = "AB378CYZfajfbajhbfajajfa";
    ufr_buffer_put (buffer, data2, strlen(data2));
    UFR_TEST_EQUAL_STR(buffer->ptr, "12345" "AB378CYZfajfbajhbfajajfa" );
    UFR_TEST_EQUAL_U64(buffer->size, 40);
    ufr_buffer_print (buffer);

    ufr_buffer_check_size (buffer, 50);
    ufr_buffer_print (buffer);
    //printf ("NOVO TAMANHO %d\n", buffer->max);
    test_buffer_free ();

    ufr_test_print_result ();

}

void test_equal () {
    unsigned long valor = 5;

    ufr_buffer_t* buffer = ufr_buffer_new();
    UFR_TEST_NOT_NULL(buffer);

   // UFR_TEST_NULL(buffer->ptr);
    
    UFR_TEST_EQUAL_U64(buffer->max, 0L);
    UFR_TEST_EQUAL_U64(buffer->size, 0L);

    //UFR_TEST_EQUAL (valor, 5);
    // UFR_TEST_EQUAL (valor, 10);
    //UFR_TEST_TRUE (valor);
}
void test_buffer_put () {
    ufr_buffer_t* buffer = ufr_buffer_new ();
    
    UFR_TEST_EQUAL_U64 (buffer->size, 0L);
    UFR_TEST_EQUAL_U64 (buffer->max, MESSAGE_ITEM_SIZE);
    ufr_buffer_put (buffer, "Insere", 6);
    UFR_TEST_EQUAL_U64 (buffer->size, 6L);
    ufr_buffer_clear (buffer);
    UFR_TEST_EQUAL_U64 (buffer->size, 0);
    ufr_buffer_free (buffer);
    

}

int main() {
    test_buffer_init  ();
    test_buffer_new   ();
    test_buffer_clear ();
    test_buffer_free  ();
    test_check_size   ();
    //test_equal();
    
    
    //teste_buffer_put ();
    return 0;
}