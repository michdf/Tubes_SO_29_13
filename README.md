# WebSocket Bookstore Server

## 🎯 **Deskripsi Proyek**  
WebSocket Bookstore Server adalah server berbasis **C** yang menggunakan **WebSocket** untuk menangani operasi **CRUD (Create, Read, Update, Delete)** pada data buku. Server ini mampu menangani banyak klien secara simultan menggunakan **fork()**, sehingga setiap koneksi klien dijalankan di proses terpisah. Proyek ini dirancang dengan modularitas tinggi, efisiensi, keamanan, dan clean code sebagai prioritas utama. Adapun WebSocket ini dibuat yaitu untuk memenuhi tugas besar mata kuliah Sistem Operasi (PR) di Politeknik Negeri Bandung

---

## 👥 **Kontributor**  
1. **Yobel El'Roy Doloksaribu** - 231524029 – [GitHub](https://github.com/k31p)  
2. **Micho Dhani Firmansyah** – 231524013 - [GitHub](https://github.com/michdf)

---

## 🚀 **Fitur Utama**  
1. Tampilan Home pada web
2. Tampilan Web Not Found (ERROR 404)
3. Storage file berbasis JSON
4. Menambah Data buku ke Storage File
5. Mengedit Data buku yang ada di Storage file
6. Menghapus Data buku yang ada di Storage file
7. Melakukan View berdasarkan ID buku yang ada di Storage file

---

## 🛠️ **Struktur Proyek**  
```
webserver/
├── src/                      
│   ├── main.c                
│   ├── server/               
│   │   ├── Handler.c
│   │   ├── Handler.h
│   │   ├── Server.c
│   │   ├── Server.h          
│   │   └──  http/ 
│   │       ├── HTTPInfo.c
│   │       ├── HTTPInfo.h                   
│   │       ├── HTTPRequest.c
│   │       ├── HTTPRequest.h       
│   │       ├── HTTPResponse.c
│   │       ├── HTTPResponse.h 
│   │       ├── Router.c      
│   │       └── Router.h 
│   │
│   ├── helper/               
│   │   ├── Utils.c
│   │   ├── Utils.h     
│   │       
│   └── data/                 
│       ├── DataHandler.c    
│       ├── DataHandler.h    
│       └── models/           
│           ├── Book.c        
│           └── Book.h        
├── tests/                    
│   └── sample.html 
|                         
├── config/                   
│   └── ServerConfig.h      
| 
├── dist/                   
│   └── webserver-tugas-besar    [Dibuat saat Compile]
│                     
├── Makefile                  
└── README.md                 
          
```

---

## 🤝 **Penutup**  
Sekian Terima Kasih 

![alt text](https://media1.tenor.com/m/zZBeekcxu_EAAAAd/cat-silly.gif)

---