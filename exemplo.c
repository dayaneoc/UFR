/* BSD 2-Clause License
 * 
 * Copyright (c) 2024, Visao Robotica e Imagem (VRI)
 *  - Felipe Bombardelli <felipebombardelli@gmail.com>
 *  - Dayane O. de Carvalho <dayaneoliveira.eng@gmail.com>
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

#define MAX_NUM 256
// ============================================================================
//  Tests
// ============================================================================

/*int aleatorio (int min, int max) {

    int num = (rand () % MAX_NUM);
    return (num);
}*/

void ufr_buffer_print (ufr_buffer_t* buffer) {

    //UFR_TEST_NOT_NULL (buffer);
    printf ("BUFFER: SIZE = %ld, MAX = %ld, DATA = %.*s\n", buffer->size, buffer->max, (int)buffer->size, buffer->ptr);
    //ufr_test_print_result ();
}

// Criar um novo buffer
void test_buffer_init () {
    
    printf ("Iniciando testes...\n");
    printf ("------------------------------------------------------------------------------");
    printf ("\n");

    ufr_buffer_t buffer;
    ufr_buffer_init (&buffer); // Inicializa o buffer
    UFR_TEST_EQUAL_U64 ( buffer.size, 0L ); /* Verifica se o tamanho inicial do buffer é 0 */ 
    UFR_TEST_EQUAL_U64 ( buffer.max, MESSAGE_ITEM_SIZE ); /* Verifica se a capacidade máxima do
                                                           * buffer é igual a MESSAGE_ITEM_SIZE 
                                                           * (valor definido em ufr_buffer.h). */
    UFR_TEST_TRUE (&buffer); 
    printf ("Teste_buffer_init OK\n");  
    ufr_test_print_result ();    
    printf ("------------------------------------------------------------------------------");
    printf ("\n");                                                    
}

void test_buffer_new () {
    
    ufr_buffer_t* buffer = ufr_buffer_new (); /* Cria um novo buffer dinamicamente*/
    
    UFR_TEST_NOT_NULL (buffer); /* Verifica se o ponteiro retornado não é NULL */
    printf ("Test_buffer_new OK\n");
    ufr_buffer_free (buffer);
    ufr_test_print_result (); 
    printf ("------------------------------------------------------------------------------");
    printf ("\n");                          
}

void test_buffer_clear () {
   
    ufr_buffer_t* buffer = ufr_buffer_new ();
    
    UFR_TEST_NOT_NULL (buffer);
    printf ("         Test_buffer_clear\n");
    printf ("\n");
    printf ("Estado inicial do buffer:\n");
    ufr_buffer_print (buffer);
    printf ("\n");
    printf ("Inserindo 1 caractere...\n");
    ufr_buffer_put_chr (buffer, 'A'); 
    ufr_buffer_print (buffer);
    printf ("\n");
    ufr_buffer_clear (buffer);
    printf ("Estado do buffer apos clear...\n");
    ufr_buffer_print (buffer);
    UFR_TEST_ZERO (buffer->size);
    ufr_buffer_free (buffer);
    ufr_test_print_result ();
    printf ("------------------------------------------------------------------------------");
    printf ("\n");  
}

void test_buffer_free () {

    ufr_buffer_t* buffer = ufr_buffer_new ();
    
    printf ("          Test_buffer_free\n");
    ufr_buffer_free (buffer);
    printf ("Memoria Liberada\n");
    ufr_test_print_result ();
    printf ("------------------------------------------------------------------------------");
    printf ("\n"); 
}

void test_check_size () {

    ufr_buffer_t* buffer = ufr_buffer_new ();
    
    printf ("          Test_check_size\n");
    UFR_TEST_NOT_NULL (buffer);
    UFR_TEST_EQUAL_U64 (buffer->size, 0L);
    UFR_TEST_EQUAL_U64 (buffer->max, MESSAGE_ITEM_SIZE);
    
    // Estado inicial
    printf ("1) Estado inicial do buffer:\n");
    ufr_buffer_print (buffer);
    printf ("\n");

    // Adiciona dados ao buffer (menor que o tamanho inicial)
    const char* data1 = "ABCDE";
    ufr_buffer_put (buffer, data1, strlen(data1));
    printf ("2) Adicionando dado < ou == ao tamanho max do buffer\n", data1);
    printf ("Dado: %s\n", data1);
    ufr_buffer_print (buffer);
    printf ("\n");
    
    //Adiciona mais dados para testar redimesionamento.
    const char* data2 = "12345678910";
    ufr_buffer_put (buffer, data2, strlen(data2));
    printf ("3) Adicionando dado maior que o tamanho max do buffer\n", data2);
    printf ("Dado: %s\n", data2);
    ufr_buffer_print (buffer);
    printf ("\n");
    
    UFR_TEST_EQUAL_STR(buffer->ptr, "ABCDE" "12345678910");
    //printf ("Teste comparação de strings OK\n");
    UFR_TEST_EQUAL_U64(buffer->size, 16);
    //printf ("Teste tamanho do buffer OK\n");
    ufr_buffer_free (buffer);
    ufr_test_print_result ();
    printf ("------------------------------------------------------------------------------");
    printf ("\n"); 
}

void test_buffer_put () {
    
    ufr_buffer_t* buffer = ufr_buffer_new ();
    
    printf ("          Test_buffer_put\n");
    UFR_TEST_EQUAL_U64 (buffer->size, 0);
    UFR_TEST_EQUAL_U64 (buffer->max, MESSAGE_ITEM_SIZE);
    printf ("Estado inicial do buffer:\n");
    ufr_buffer_print (buffer);
    printf ("Apos dados inseridos...\n");
    ufr_buffer_put (buffer, "Insere", 6);
    UFR_TEST_EQUAL_U64 (buffer->size, 6);
    ufr_buffer_print (buffer);
    ufr_buffer_clear (buffer);
    UFR_TEST_EQUAL_U64 (buffer->size, 0);
    ufr_buffer_free (buffer);
    
    ufr_test_print_result ();
    printf ("------------------------------------------------------------------------------");
    printf ("\n"); 
}

void test_buffer_put_chr () {

    ufr_buffer_t* buffer = ufr_buffer_new ();

    printf ("          Test_buffer_put_chr\n");
    UFR_TEST_EQUAL_U64 (buffer->size, 0);
    UFR_TEST_EQUAL_U64 (buffer->max, MESSAGE_ITEM_SIZE);
    printf ("Estado inicial do buffer:\n");
    ufr_buffer_print (buffer);
    printf ("Inserindo caractere...\n");
    ufr_buffer_put_chr (buffer, 'A');
    UFR_TEST_EQUAL_U64 (buffer->size, 1);
    ufr_buffer_print (buffer);
    ufr_buffer_clear (buffer);
    UFR_TEST_EQUAL_U64 (buffer->size, 0);
    ufr_buffer_free (buffer);

    ufr_test_print_result ();
    printf ("------------------------------------------------------------------------------");
    printf ("\n");
}

void test_buffer_put_u8_as_str () {

    ufr_buffer_t* buffer = ufr_buffer_new ();
    
    printf ("          Test_buffer_put_u8_as_str\n");
    UFR_TEST_EQUAL_U64 (buffer->size, 0);
    UFR_TEST_EQUAL_U64 (buffer->max, MESSAGE_ITEM_SIZE);
    printf ("Estado inicial do buffer:\n");
    ufr_buffer_print (buffer);
    printf ("\n");
    printf ("Inserindo valor...\n");
    ufr_buffer_put_u8_as_str (buffer, 1);
    ufr_buffer_print (buffer);
    ufr_buffer_put_u8_as_str (buffer, 1);
    ufr_buffer_print (buffer);
    ufr_buffer_put_u8_as_str (buffer, 55);
    ufr_buffer_print (buffer);
    ufr_buffer_put_u8_as_str (buffer, 37);
    ufr_buffer_print (buffer);
    ufr_buffer_free (buffer);

    ufr_test_print_result ();
    printf ("------------------------------------------------------------------------------");
    printf ("\n");
}

/*void test_equal () {
    unsigned long valor = 5;

    ufr_buffer_t* buffer = ufr_buffer_new();
    UFR_TEST_NOT_NULL(buffer);

   // UFR_TEST_NULL(buffer->ptr);
    
    UFR_TEST_EQUAL_U64(buffer->max, 0L);
    UFR_TEST_EQUAL_U64(buffer->size, 0L);

    //UFR_TEST_EQUAL (valor, 5);
    // UFR_TEST_EQUAL (valor, 10);
    //UFR_TEST_TRUE (valor);
}*/


int main() {

    test_buffer_init    (); 
    test_buffer_new     ();
    test_buffer_clear   ();
    test_buffer_free    ();
    //test_check_size     (); 
    //test_buffer_put     ();
    //test_buffer_put_chr ();
    test_buffer_put_u8_as_str ();
    
    //test_equal();
    
    return 0;
}