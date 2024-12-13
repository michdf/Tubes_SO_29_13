# WebSocket Bookstore Server

## 🎯 **Deskripsi Proyek**  
WebSocket Bookstore Server adalah server berbasis **C** yang menggunakan **WebSocket** untuk menangani operasi **CRUD (Create, Read, Update, Delete)** pada data buku. Server ini mampu menangani banyak klien secara simultan menggunakan **fork()**, sehingga setiap koneksi klien dijalankan di proses terpisah. Proyek ini dirancang dengan modularitas tinggi, efisiensi, keamanan, dan clean code sebagai prioritas utama. Adapun WebSocket ini dibuat yaitu untuk memenuhi tugas besar mata kuliah Sistem Operasi (PR) di Politeknik Negeri Bandung

---

## 👥 **Kontributor**  
1. **Yobel El'Roy Doloksaribu** - 231524029 – [GitHub](https://github.com/k31p)  
2. **Micho Dhani Firmansyah** – 231524013 - [GitHub](https://github.com/michdf)

---

## 🚀 **Fitur Utama**  
1. **CRUD Data Buku:**
   - **ADD:** Menambahkan buku baru ke dalam daftar.
   - **LIST:** Menampilkan semua buku yang tersedia.

---

## 🛠️ **Struktur Proyek**  
```
webserver/
├── src/                      # Folder utama untuk kode sumber
│   ├── main.c                # Entry point utama aplikasi
│   ├── server/               # Modul terkait server
│   │   ├── server.c          # Implementasi fungsi server (listening, prefork)
│   │   ├── server.h          # Header file untuk deklarasi fungsi server
│   │   ├── http/             # Modul terkait HTTP
│   │   │   ├── http.c        # Implementasi parsing dan handling HTTP request
│   │   │   ├── http.h        # Header file untuk HTTP
│   │   │   ├── router.c      # Routing untuk HTTP method (GET, POST, DELETE, UPDATE)
│   │   │   ├── router.h      # Header untuk fungsi routing
│   │   └── logging/          # Modul logging
│   │       ├── logging.c     # Implementasi logging (request dan error log)
│   │       ├── logging.h     # Header file untuk logging
│   └── data/                 # Modul untuk manajemen data
│       ├── data_handler.c    # Implementasi untuk menyimpan dan membaca data dari file
│       ├── data_handler.h    # Header file untuk manajemen data
│       ├── models/           # Modul model data
│           ├── book.c        # Struktur dan operasi terkait data buku
│           ├── book.h        # Header file untuk data buku
├── tests/                    # Folder untuk unit testing
│   ├── test_http.c           # Test untuk HTTP handling
│   ├── test_server.c         # Test untuk server
│   ├── test_data_handler.c   # Test untuk data handling
│   └── test_logging.c        # Test untuk logging
├── docs/                     # Dokumentasi
│   ├── design.md             # Desain dan arsitektur sistem
│   ├── api_docs.md           # Dokumentasi API (GET, POST, DELETE, UPDATE)
├── config/                   # Konfigurasi server
│   ├── server_config.h       # Konstanta dan konfigurasi server
│   ├── routes_config.h       # Daftar endpoint dan handler
├── logs/                     # Folder untuk menyimpan log
│   ├── access.log            # Log akses HTTP
│   ├── error.log             # Log error
├── Makefile                  # File untuk build dan testing menggunakan Make
└── README.md                 # Penjelasan singkat tentang proyek
          
```

---

## 🤝 **Penutup**  
Sekian Terima Kasih 

![alt text](https://media1.tenor.com/m/zZBeekcxu_EAAAAd/cat-silly.gif)

---