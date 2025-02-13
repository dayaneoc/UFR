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

#include <stdint.h>
#include <stddef.h>

#define MESSAGE_ITEM_SIZE 4096L

typedef struct {
    size_t size;
    size_t max;
    char* ptr;
} ufr_buffer_t;

ufr_buffer_t* ufr_buffer_new();
void ufr_buffer_init(ufr_buffer_t* buffer);
void ufr_buffer_clear(ufr_buffer_t* buffer);
void ufr_buffer_free(ufr_buffer_t* buffer);
void ufr_buffer_put(ufr_buffer_t* buffer, const char* text, size_t size);
void ufr_buffer_put_chr(ufr_buffer_t* buffer, char val);
void ufr_buffer_put_u8_as_str(ufr_buffer_t* buffer, uint8_t val);
void ufr_buffer_put_i8_as_str(ufr_buffer_t* buffer, int8_t val);
void ufr_buffer_put_u32_as_str(ufr_buffer_t* buffer, uint32_t val);
void ufr_buffer_put_i32_as_str(ufr_buffer_t* buffer, int32_t val);
void ufr_buffer_put_f32_as_str(ufr_buffer_t* buffer, float val);
void ufr_buffer_put_str(ufr_buffer_t* buffer, const char* text);