/**
 * @file Utils.h
 * @author Yobel El'Roy Doloksaribu (royblend@protonmail.com)
 * @brief ADT untuk fungsi-fungsi bantuan
 * @date 2024-12-14
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Melakukan penyalinan string dengan pengecekan keamanan
 * 
 * Fungsi ini menyalin string dari sumber ke tujuan dengan memastikan
 * tidak terjadi buffer overflow. Fungsi akan membatasi penyalinan
 * sesuai dengan ukuran buffer yang ditentukan.
 * 
 * @param dest Pointer ke string tujuan
 * @param src Pointer ke string sumber yang akan disalin
 * @param size Ukuran maksimum buffer tujuan
 * @return bool true jika penyalinan berhasil
 *         false jika terjadi error atau buffer overflow
 */
bool safe_strncpy(char* dest, const char* src, size_t size);

#endif