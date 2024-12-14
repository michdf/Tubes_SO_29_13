/**
 * @file HTTPResponse.h
 * @author Yobel El'Roy Doloksaribu (royblend@protonmail.com)
 * @brief ADT untuk menangani response HTTP
 * @date 2024-12-14
 */

#ifndef HTTPResponse_h
#define HTTPResponse_h

#include "HTTPInfo.h"
#include "../../../config/ServerConfig.h"

/**
 * @brief Membuat string response HTTP
 * 
 * Fungsi ini mengkonstruksi string response HTTP dengan format yang sesuai
 * berdasarkan status code dan body yang diberikan.
 * 
 * @param status Kode status HTTP yang akan digunakan dalam response
 * @param body Isi body yang akan disertakan dalam response
 * @return char* String response HTTP yang telah diformat sesuai standar
 */
char *response_constructor(int status, char *body);

#endif