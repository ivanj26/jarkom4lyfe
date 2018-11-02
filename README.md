# Tugas Besar IF3130 Jaringan Komputer

### Teori Dasar dan Deskripsi Tugas
Sliding window Protocol adalah teknik untuk mengatur paket data yang ditransmisikan diantara 2 buah jaringan komputer dimana pengiriman paket data yang dapat diandalkan dan berurutan sangat diperlukan, seperti ketika menggunakan Data Link Layer (model OSI) atau Transmission Control Protocol (TCP). 
Dalam sliding window protocol, tiap paket data (untuk kebanyakan data link layers) dan byte (dalam TCP) termasuk nomor urut (sequence number) yang unik, yang digunakan oleh komputer penerima untuk menyimpan data dalam urutan yang benar. Tujuan dari sliding window protocol menggunakan nomor urut (sequence number) adalah untuk menghindari duplikasi data dan untuk meminta kembali jika ada data yang hilang. 

Dalam tugas ini, kami harus menggunakan selective repeat automatic repeat request dalam sliding window protocol.

Cara kerja sliding windows protocol adalah sliding windows akan menelusuri buffered data, kemudian data akan dikirimkan dengan besar sesuai dengan ukuran window size-nya. Kemudian penerima akan mengirimkan ACK atau NAK apabila sudah menerima paket tersebut. ACK akan dikirimkan jika data yang diterima sudah sesuai dengan data yang dikirim (dicek menggunakan checksum) dan NAK akan dikirimkan jika ada paket data yang hilang atau salah. Selanjutnya, pengirim akan mengecek kiriman dari penerima apakah yang dikirim adalah ACK atau NAK. Jika pengirim menerima ACK, maka pengirim akan mengirimkan lagi paket data selanjutnya. Jika pengirim menerima NAK, maka pengirim akan mengirimkan lagi data paket yang memang hilang/error kepada penerima.

Untuk mempermudah mempelajari cara kerja sliding window protocol ini, dapat dilihat cara penggunaannya dengan animasi [disini](http://www.ccs-labs.org/teaching/rn/animations/gbn_sr/)

---
#### Frame
SOH(0x1)|Sequence Number|Data Length|Data|Check Sum
---|---|---|---|---
1 byte|4 byte|4 byte|Max 1024 byte|1 byte

ACK|Next Sequence Number|Checksum
---|---|---
1 byte|4 byte|1 byte

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
---
    
### Cara kerja sliding window
Kami membuat dua kelas utama yaitu Sender dan Receiver. Kelas pendukungnya yaitu Packet (merupakan packet yang akan dikirim oleh Sender). Setelah pembacaan file selesai, Sender akan mengirimkan packet dengan timeout per packet sedangkan receiver untuk menerima packet yang dikirimkan oleh Sender dengan mengirimkan ACK bila tidak terjadi error pada packet sedangkan NAK bila terjadi error pada packet. Kelas Sender mempunyai beberapa method yakni:

    1. void readFile(char*)
    
    Pada fungsi readFile() ini, param yang diterima berupa nama file. Lalu, data akan dibaca dengan fungsi fread dan membuat instans dari kelas Packet. Pada setiap instans Packet di-set headernya dengan 0x01, lalu seqNum, dan set datanya.

    2. void slider()
    
    Pada fungsi slider(), mudahnya, paket-paket akan dikirim secara massal lewat kelas UdpClient. Di UdpClient ini terdapat method send dengan 2 param yaitu message dan ukuran dari message yang akan dikirim. Setelah itu, slider kana menunggu ACK dari paket-paket yang dikirim sebelumnya, bila sudah timeout maka paket tersebut akan dikirim ulang.

    3. void listener()
    
    Sebagai fungsi yang menunggu ACK dari receiver, fungsi ini akan ditaruh sebagai parameter dari pthread.

Selanjutnya, pada kelas Receiver mempunyai beberapa method yaitu sebagai berikut:
    
    1. void sendack()
    Pada fungsi sendack ini, receiver akan mengirim ACK ke Sender melewati kelas UdpServer. Fungsi send pada UdpServer merupakan kebalikan dari UdpClient yaitu mengirim message dari Receiver ke Sender. 
    
    2. void saveToFile(char*)
    Pada fungsi ini, receiver akan membuat file dengan nama berdasarkan parameter fungsi. File yang dibuat berupa paket-paket yang telah diterima oleh Receiver.
    
    3. void listen()
    Pada fungsi listen ini, Receiver akan menunggu untuk paket yang dikirim oleh Sender. Bila paket tersebut valid, maka Receiver akan mengirimkan ACK sebaliknya akan mengirimkan NAK.

---

### Pembagian tugas kelompok
1. William Juniarta - 13516026
2. Ivan Jonathan - 13516059
    
    Mengerjakan kelas Sender, UdpClient beserta fungsi-fungsinya.
3. Muhammad Alfian Rasyidin - 13516104

     Mengerjakan kelas Receiver, UdpServer beserta fungsi-fungsinya. 

---
### Anggota
1. William Juniarta         - 13516026
2. Ivan Jonathan            - 13516059
3. Muhammad Alfian Rasyidin - 13516104
