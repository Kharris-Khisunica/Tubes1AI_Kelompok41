# Tugas Besar 1 IF3170 Inteligensi Buatan

> Pencarian Solusi Diagonal Magic Cube dengan Local Search

## Deskripsi Persoalan

Local Search Algorithm / Algoritma Pencarian Lokal merupakan algoritma pengoptimasian yang digunakan untuk menemukan solusi terbaik dalam pencarian ruang tertentu. Berbeda dengan metode pencarian global yang mengeksplor seluruh ruang solusi, algoritma pencarian lokal berfokus pada membuat perubahan secara bertahap untuk meningkatkan solusi saat ini hingga mencapai solusi optimal yang bersifat lokal. Namun, algoritma local search ini dapat terjebak di maksimum lokal yang belum tentu merupakan solusi maksimum global sehingga algoritma ini tidak menjamin keberhasilan mendapat solusi global. Dalam tugas besar 1 ini, algoritma local search digunakan untuk menyelesaikan permasalahan magic cube berukuran 5 x 5 x 5.


## Teknologi yang Dipakai

- Python dan C++
- Matplotlib
- Numpy
- Tkinter
- WSL

## Cara Menjalankan Program

1. Clone repository ini dengan perintah `https://github.com/Kharris-Khisunica/Tubes1AI_Kelompok41.git`
2. Buka root directory menggunakan *terminal WSL*. Bila tidak menggunakan terminal WSL, maka kemungkinan program akan error.
3. Bila belum melakukan instalasi numpy, tkinter, dan/atau matplotlib, lakukan instalasi ketiga dependensi tersebut (misalnya dengan perintah `pip install numpy` dan/atau `pip install matplotlib`)
4. Jalankan perintah `make clean` lalu `make` pada root direktori di terminal WSL untuk melakukan kompilasi program.
3. Jalankan perintah `python main.py` atau `python3 main.py` pada root direktori di terminal WSL untuk menjalankan program.

## Pembagian Tugas

| NIM      | Pembagian Kerja |
| -------- | ------------------- |
| 13522004 | Random restart Hill Climbing, Sideways Hill Climbing, Stochastic Hill Climbing |
| 13522007 | Genetic Algorithm, Position |
| 13522047 | Utils, Visualisasi, Steepest Ascent Hill Climbing |
| 13522051 | Simulated Annealing |