/**
 * @file Utils.c
 * @author Yobel El'Roy Doloksaribu (royblend@protonmail.com)
 * @brief Implementasi fungsi-fungsi bantuan
 * @date 2024-12-14
 */

#include "Utils.h"
#include <string.h>

bool safe_strncpy(char* dest, const char* src, size_t size) {
    if (!dest || !src) return false;
    size_t src_len = strlen(src);
    if (src_len >= size) return false;
    strncpy(dest, src, size - 1);
    dest[size - 1] = '\0';
    return true;
}