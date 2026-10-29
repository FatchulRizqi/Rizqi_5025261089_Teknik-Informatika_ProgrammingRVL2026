# Tugas Modul 3 - Bouncing Ball Catcher Game (ROS 2)

Proyek ini merupakan implementasi game interaktif *Bouncing Ball Catcher* berbasis **ROS 2** dan **OpenCV (C++)**. Game ini menggunakan input kamera real-time untuk mendeteksi warna objek (penangkap/catcher), yang digunakan untuk menangkap bola-bola virtual yang memantul di layar.

## Cara Menjalankan

1. **Masuk ke Workspace ROS 2**:
   ```bash
   cd ~/Tugas_Rival/Tugas_Modul3/game_ball
   ```

2. **Kompilasi Package**:
   ```bash
   colcon build --packages-select bouncing_catcher
   ```

3. **Source Environment ROS 2**:
   ```bash
   source install/setup.bash
   ```

4. **Jalankan Aplikasi via Launch File**:
   ```bash
   ros2 launch bouncing_catcher game.launch.py
   ```

---

## Arsitektur Sistem

Sistem terdiri dari 2 node utama yang saling berkomunikasi secara asynchronous melalui topik ROS 2:

### 1. Node
- **`camera_node`**: Membaca frame dari webcam lokal dan mempublikasikannya ke dalam ekosistem ROS 2.
- **`game_node`**: Node C++ utama yang menangani:
  - Konversi citra ROS 2 ke OpenCV (`cv_bridge`).
  - Pemrosesan segmentasi warna HSV dan deteksi kontur pemicu (*catcher*).
  - Simulasi fisika gerak bola memantul (*bouncing ball*).
  - Deteksi tabrakan (*collision detection*) dan perhitungan timer penahanan (2 detik).
  - Rendering UI (skor, indikator persentase loading, bola virtual).

### 2. Topik (Topics)
- **`/camera/image_raw`** (`sensor_msgs/msg/Image`): Aliran gambar mentah dari kamera.
- **`/game/debug_image`** (`sensor_msgs/msg/Image`): Gambar hasil render game beserta bola, skor, dan status loading.
- **`/game/score`** (`std_msgs/msg/Int32`): Topik publikasi skor pemain secara langsung.

### 3. Parameter
- **`num_balls`** (int, default: `3`): Jumlah bola virtual yang dimunculkan secara acak.
- **`hold_duration`** (double, default: `2.0`): Waktu penahanan (detik) yang diperlukan untuk menangkap bola.
- **`ball_radius`** (int, default: `50`): Jari-jari bola virtual dalam piksel.
- **`ball_speed`** (double, default: `150.0`): Kecepatan gerak bola virtual.

---

## Asumsi & Keputusan Desain

1. **Implementasi C++ Murni**: Pemrosesan citra dan simulasi fisika bola ditulis menggunakan C++ untuk meminimalkan *latency* frame rate dan menjaga performa rendering tetap tinggi.
2. **Perhitungan Fisika Berbasis Delta Waktu (`dt`)**: Pergerakan bola dihitung berdasarkan selisih waktu aktual antar-frame (`now - last_time`). Hal ini memastikan kecepatan bola tetap stabil di berbagai kecepatan hardware/kamera.
3. **Segmentasi HSV & Centroid Moments**: Deteksi objek penangkap menggunakan *masking* rentang warna HSV dan *Centroid Moments* (`cv::moments`) untuk mendapatkan koordinat pusat (*X, Y*) secara akurat dan responsif.
4. **Logika Penangkapan Bola (Hold Mechanic)**: Jika titik penangkap menyentuh area radius bola, bola berubah warna menjadi kuning dan *timer* dihitung. Jika dilepas sebelum 2 detik (`hold_duration`), *progress loading* di-reset kembali ke 0%.

---

## Kendala & Solusi

* **Kendala 1: Variasi Pencahayaan Ruangan (Pencahayaan Kamera)**
  - *Sebab*: Perubahan intensitas cahaya sekitar membuat deteksi warna kontur menjadi tidak stabil (*flicker*).
  - *Solusi*: Mengatur ambang batas (*threshold*) HSV secara presisi dan menambahkan filter luas kontur minimum (`min_area`) untuk mengabaikan *noise* objek kecil di latar belakang.

* **Kendala 2: Sinkronisasi Frame Rate dan Timer Game**
  - *Sebab*: Jika fps kamera turun, bola bergerak terlalu lambat jika kecepatannya dipatok per frame.
  - *Solusi*: Menggunakan kalkulasi delta waktu aktual (`dt`) pada *timer callback* `update_game()` sehingga jarak tempuh bola disesuaikan dengan waktu riil.
