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

#pragma once

#include <stdint.h>

struct _link;
#define UFR_OK 0

// ============================================================================
//  UFR ARGS
// ============================================================================

// 8 bytes
typedef union {
    uint32_t    u32;
    uint64_t    u64;
    int32_t     i32;
    int32_t     i64;
    float       f32;
    double      f64;
    void*       ptr;
    char const* str;
    int         (*func)(struct _link*, int);
} item_t;

// 64 bytes for #64
typedef struct {
    const char* text;
    item_t arg[7];
} ufr_args_t;

// ============================================================================
//  UFR ARGS
// ============================================================================

#define UFR_ARGS_TOKEN 512

size_t ufr_args_getu(const ufr_args_t* args, const char* noun, const size_t default_value);
int    ufr_args_geti(const ufr_args_t* args, const char* noun, const int default_value);
float  ufr_args_getf(const ufr_args_t* args, const char* noun, const float default_value);
const void* ufr_args_getp(const ufr_args_t* args, const char* noun, const void* default_value);
const char* ufr_args_gets(const ufr_args_t* args, char* buffer, const char* noun, const char* default_value);

void* ufr_args_getfunc(const ufr_args_t* args, const char* type, const char* noun, void* default_value);

bool ufr_args_flex_div(const char* text, uint16_t* cursor_ini, char* token, const uint16_t token_max, const char div);
bool ufr_args_flex(const char* text, uint16_t* cursor_ini, char* token, const uint16_t token_max);

int ufr_args_decrease_level(const char* src, char* dst);

void ufr_args_load_from_va(ufr_args_t* args, const char* text, va_list list);
