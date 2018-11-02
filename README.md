# Tugas Besar IF3130 Jaringan Komputer
---

### Petunjuk penggunaan program

1. Untuk menjalankan program sender dapat dijalankan dengan perintah:
      ```
      ./sendfile <filename> <windowsize> <buffersize> <destination_ip> <destination_port>
      ```
2. Sedangkan pada program receiver dapat dijalankan dengan perintah:
    ```
    ./recvfile <filename> <windowsize> <buffersize> <port>
    ```
    
### Cara kerja sliding window
Sliding window Protocol adalah teknik untuk mengatur paket data yang ditransmisikan diantara 2 buah jaringan komputer dimana pengiriman paket data yang dapat diandalkan dan berurutan sangat diperlukan, seperti ketika menggunakan Data Link Layer (model OSI) atau Transmission Control Protocol (TCP). 
Dalam sliding window protocol, tiap paket data (untuk kebanyakan data link layers) dan byte (dalam TCP) termasuk nomor urut (sequence number) yang unik, yang digunakan oleh komputer penerima untuk menyimpan data dalam urutan yang benar. Tujuan dari sliding window protocol menggunakan nomor urut (sequence number) adalah untuk menghindari duplikasi data dan untuk meminta kembali jika ada data yang hilang. 

### Cara kerja setiap fungsi

### Pembagian tugas kelompok

### Anggota
1. William Juniarta         - 13516026
2. Ivan Jonathan            - 13516059
3. Muhammad Alfian Rasyidin - 13516104
