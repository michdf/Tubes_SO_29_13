/**
 * @file Server.h
 * @author Yobel El'Roy Doloksaribu (royblend@protonmail.com)
 * @brief ADT untuk mengelola server socket
 * @date 2024-12-14
 */

#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

/**
 * @brief Struktur data untuk merepresentasikan server socket
 *
 * Struktur ini menyimpan konfigurasi dan status server socket,
 * termasuk properti koneksi dan fungsi callback untuk menjalankan server.
 */
struct Server {
  int domain;       /**< Domain komunikasi socket (IPv4/IPv6) */
  int service;      /**< Tipe layanan socket (SOCK_STREAM/SOCK_DGRAM) */
  int protocol;     /**< Protokol yang digunakan */
  u_long interface; /**< Antarmuka jaringan yang digunakan */
  int port;         /**< Port yang digunakan untuk koneksi */
  int backlog;      /**< Jumlah maksimum koneksi pending */

  struct sockaddr_in address; /**< Struktur alamat socket */

  int socket; /**< File descriptor socket */

  void (*launch)(struct Server *); /**< Function pointer untuk menjalankan server */
};

/**
 * @brief Membuat instance baru dari server
 *
 * Fungsi konstruktor ini menginisialisasi server socket dengan
 * parameter-parameter yang diberikan.
 *
 * @param domain Domain komunikasi (AF_INET untuk IPv4)
 * @param service Tipe layanan (SOCK_STREAM untuk TCP)
 * @param protocol Protokol yang digunakan (0 untuk default)
 * @param interface Antarmuka jaringan
 * @param port Nomor port untuk koneksi
 * @param backlog Jumlah maksimum koneksi pending
 * @param launch Function pointer untuk menjalankan server
 * @return struct Server Instance server yang telah diinisialisasi
 */
struct Server server_constructor(int domain, int service, int protocol,
                                 u_long interface, int port, int backlog,
                                 void (*launch)(struct Server *));

#endif