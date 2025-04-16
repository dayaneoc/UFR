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
#include <stdbool.h>

#include "ufr_args.h"
#include "ufr_test.h"

//============================================================================
//  Tests
// ============================================================================

void test_ufr_args_flex_div () {

    printf ("==========Iniciando testes p/ ufr_args_flex_div==========\n");
    printf ("\n");
   
    // Teste 1: Delimitador aspas simples
    {
        const char* text = "testar string 10 20 'Teste dentro de aspas'";
        uint16_t cursor = 0;
        char token[50];

        UFR_TEST_NOT_NULL (token);

        printf ("          Teste 1 - delimitador aspas simples\n\n");
        printf ("Testa frase de entrada: \"%s\"\n", text);
        printf ("Tokens: \n");

        while (ufr_args_flex_div (text, &cursor, token, 50, ' ')) {
            printf (" - \"%s\"\n", token);
        }
        UFR_TEST_EQUAL_STR (text, "testar string 10 20 'Teste dentro de aspas'");
        printf ("\n");

        ufr_test_print_result ();
        printf ("------------------------------------------------------------------------------");
        printf ("\n"); 
    }

    // Teste 2: String vazia
    {
        const char* text = " ";
        uint16_t cursor  = 0;
        char token[50];

        UFR_TEST_NOT_NULL (token);

        printf ("            Teste 2 - String vazia\n\n");
        printf ("Teste frase de entrada: \"%s\"\n", text);
        printf ("Tokens: \n");

        if (ufr_args_flex_div(text, &cursor, token, 50, ' ')) {
            printf (" Erro! Era esperado nenhum token, mas obteve: %s\n", token);
        } else {
            printf ("Teste 2 passou (nenhum token retornado)");
            printf ("\n");
        }
        UFR_TEST_EQUAL_STR (text, " ");
        printf ("\n");

        ufr_test_print_result ();
        printf ("------------------------------------------------------------------------------");
        printf ("\n"); 

    }

    // Teste 3: Delimitador diferente (vírgula)
    {
        const char* text = "Entrada, 125, ' ',Ok";
        uint16_t cursor  = 0;
        char token[50];

        UFR_TEST_NOT_NULL (token);
        

        printf ("            Teste 3 - Delimitador vírgula\n\n");
        printf (" Teste frase de entrada: \"%s\"\n", text);
        printf ("Tokens: \n");

        while (ufr_args_flex_div (text, &cursor, token, 50, ',' )) {
            printf (" - \"%s\"\n", token);

        }
        UFR_TEST_EQUAL_STR (text, "Entrada, 125, ' ',Ok" );
        printf ("\n");

        ufr_test_print_result ();
        printf ("------------------------------------------------------------------------------");
        printf ("\n"); 
    }

    // Teste 4: Aspas não fechadas
    {
        const char* text = " A 'B Teste sem fechar aspas";
        uint16_t cursor  = 0;
        char token[50];

        UFR_TEST_NOT_NULL (token);

        printf ("            Teste 4 - Aspas não fechadas\n\n");
        printf ("Teste frase de entrada: \"%s\"\n", text);
        printf ("Tokens\n");


        bool res1 = ufr_args_flex_div (text, &cursor, token, 50, ' ' );
        UFR_TEST_TRUE (res1);
        UFR_TEST_EQUAL_STR (token, "A" );
        UFR_TEST_EQUAL (cursor, 2);
        printf ("%s\n", token);

        bool res2 = ufr_args_flex_div (text, &cursor, token, 50, ' ' );
        UFR_TEST_EQUAL_STR (token, "B Teste sem fechar aspas" );
        UFR_TEST_EQUAL (cursor, 28);
        printf ("%s\n", token);

        bool res3 = ufr_args_flex_div (text, &cursor, token, 50, ' ' );
        UFR_TEST_FALSE (res3);
        UFR_TEST_EQUAL_STR (token, "" );
        UFR_TEST_EQUAL (cursor, 28);
        printf ("%s\n", token);



        while (ufr_args_flex_div (text, &cursor, token, 50, '\'' )) {
            printf (" - \"%s\"\n", token);
        }
        UFR_TEST_EQUAL_STR (text, " A 'B Teste sem fechar aspas" );
        printf ("\n");


        
        ufr_test_print_result ();
        printf ("------------------------------------------------------------------------------");
        printf ("\n"); 

    }

    // Teste 5: Maior que tamanho máx 
    {
        const char* text = "teste,2,3,4,5,6,7";
        uint16_t cursor  = 0;
        char token[5];

        UFR_TEST_NOT_NULL (token);

        printf ("            Teste 5 - Maior que o tamanho máx token\n\n");
        printf ("Teste frase de entrada: \"%s\"\n", text);
        printf ("Tokens\n");

        const bool res1 = ufr_args_flex_div (text, &cursor, token, 5, ',' );
        UFR_TEST_TRUE (res1);
        UFR_TEST_EQUAL_STR (token, "test" );
        UFR_TEST_EQUAL (cursor, 5);
        printf ("%s\n", token);
    
        const bool res2 = ufr_args_flex_div (text, &cursor, token, 5, ',' );
        UFR_TEST_TRUE (res2);
        UFR_TEST_EQUAL_STR (token, "2" );
        UFR_TEST_EQUAL (cursor, 7);
        printf ("%s\n", token);
      
       


    }


    printf ("\n");
}



int main () {

    test_ufr_args_flex_div ();

    return 0;
}