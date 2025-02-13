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
void test1() {
    printf ("Iniciando testes...");

    ufr_buffer_t buffer;
    ufr_buffer_init(&buffer); // Inicializa o buffer
    UFR_TEST_EQUAL_U64( buffer.size, 0L ); /* Verifica se o tamanho inicial do buffer é 0 */ 
    UFR_TEST_EQUAL_U64( buffer.max, MESSAGE_ITEM_SIZE ); /* Verifica se a capacidade máxima do
                                                          * buffer é igual a MESSAGE_ITEM_SIZE 
                                                          * (um valor definido em algum lugar do código). */
    ufr_buffer_put(&buffer, "opa", 3); /* Adiciona a string "opa" (3 bytes) ao buffer*/
    UFR_TEST_EQUAL_U64( buffer.size, 3L ); /* Verifica se o tamanho do buffer */
}

void test2() {
    ufr_buffer_t* buffer = ufr_buffer_new(); /* Cria um novo buffer dinamicamente*/
    UFR_TEST_NOT_NULL( buffer ); /* Verifica se o ponteiro retornado não é NULL
                                  * usando a macro UFR_TEST_NOT_NULL*/
}

void teste_equal () {
    int valor = 5;

    UFR_TEST_EQUAL (valor, 5); 
    UFR_TEST_EQUAL (valor, 10);
}

int main() {
    //test1();
    //printf ("Teste 1 feito!");
    //test2();
    teste_equal();
    
    return 0;
}