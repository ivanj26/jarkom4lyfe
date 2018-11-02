# Tugas Besar IF3130 Jaringan Komputer

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


### Pembagian tugas kelompok
1. William Juniarta - 13516026
2. Ivan Jonathan - 13516059
    
    Mengerjakan kelas Sender, UdpClient beserta fungsi-fungsinya.
3. Muhammad Alfian Rasyidin - 13516104

     Mengerjakan kelas Receiver, UdpServer beserta fungsi-fungsinya. 

### Anggota
1. William Juniarta         - 13516026
2. Ivan Jonathan            - 13516059
3. Muhammad Alfian Rasyidin - 13516104
