/**
 * @file HTTPInfo.h
 * @author Yobel El'Roy Doloksaribu (royblend@protonmail.com)
 * @brief ADT untuk informasi dan konstanta HTTP
 * @date 2024-12-14
 */

#ifndef HTTPINFO_H
#define HTTPINFO_H

/**
 * @brief Enum untuk metode HTTP yang didukung
 *
 * Enum ini mendefinisikan berbagai metode HTTP yang dapat
 * digunakan dalam komunikasi client-server.
 */
enum HTTPMethods
{
    GET,     ///< Mengambil data dari server
    POST,    ///< Mengirim data baru ke server
    PUT,     ///< Memperbarui data yang ada di server
    HEAD,    ///< Mengambil header response tanpa body
    PATCH,   ///< Memperbarui sebagian data
    DELETE,  ///< Menghapus data dari server
    CONNECT, ///< Membuat tunnel ke server
    OPTIONS, ///< Mendapatkan opsi komunikasi yang tersedia
    TRACE    ///< Melakukan loop-back test
};

/**
 * @brief Enum untuk kode response HTTP
 *
 * Enum ini mendefinisikan kode-kode status yang digunakan
 * dalam response HTTP server.
 */
enum HTTPResponseCodes
{
    HTTP_OK = 200,                    ///< Request berhasil
    HTTP_CREATED = 201,               ///< Resource berhasil dibuat
    HTTP_ACCEPTED = 202,              ///< Request diterima tapi belum selesai
    HTTP_NO_CONTENT = 204,            ///< Request berhasil tanpa content
    HTTP_MOVED_PERMANENTLY = 301,     ///< Resource dipindah permanen
    HTTP_FOUND = 302,                 ///< Resource ditemukan di lokasi lain
    HTTP_NOT_MODIFIED = 304,          ///< Resource tidak dimodifikasi
    HTTP_BAD_REQUEST = 400,           ///< Request tidak valid
    HTTP_UNAUTHORIZED = 401,          ///< Memerlukan autentikasi
    HTTP_FORBIDDEN = 403,             ///< Akses ditolak
    HTTP_NOT_FOUND = 404,             ///< Resource tidak ditemukan
    HTTP_METHOD_NOT_ALLOWED = 405,    ///< Metode HTTP tidak diizinkan
    HTTP_INTERNAL_SERVER_ERROR = 500, ///< Error internal server
    HTTP_NOT_IMPLEMENTED = 501,       ///< Fitur belum diimplementasi
    HTTP_BAD_GATEWAY = 502,           ///< Response invalid dari upstream
    HTTP_SERVICE_UNAVAILABLE = 503    ///< Layanan tidak tersedia
};

/**
 * @brief Mengkonversi kode response HTTP menjadi string
 *
 * Fungsi ini mengubah enum HTTPResponseCodes menjadi
 * string yang sesuai dengan standar HTTP.
 *
 * @param code Kode HTTP yang akan dikonversi
 * @return const char* String yang merepresentasikan kode HTTP
 */
const char *HTTPResponseCodeToString(enum HTTPResponseCodes code);

#endif