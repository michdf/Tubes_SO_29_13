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
├── src/                      
│   ├── main.c                
│   ├── server/               
│   │   ├── handler.c
│   │   ├── handler.h
│   │   ├── server.c
│   │   ├── server.h          
│   │   └──  http/             
│   │       ├── HTTPRequest.c
│   │       ├── HTTPRequest.h       
│   │       ├── HTTPResponse.c
│   │       ├── HTTPResponse.h 
│   │       ├── router.c      
│   │       └── router.h      
│   │       
│   └── data/                 
│       ├── data_handler.c    
│       ├── data_handler.h    
│       └── models/           
│           ├── book.c        
│           └── book.h        
├── tests/                    
│   └── sample.html 
|                         
├── config/                   
│   └── server_config.h      
| 
├── dist/                   
│   └── webserver-tugas-besar.exe
│                     
├── Makefile                  
└── README.md                 
          
```

---

## 🤝 **Penutup**  
Sekian Terima Kasih 

![alt text](https://media1.tenor.com/m/zZBeekcxu_EAAAAd/cat-silly.gif)

---