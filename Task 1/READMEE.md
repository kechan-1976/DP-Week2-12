1. What is the invariant structure in your program?
Struktur invarian adalah alur permainan utama (game loop) di dalam RunSession::run().
Metode atau rumus spesifik apa pun yang digunakan, urutan kerja di setiap rondenya selalu tetap dan tidak pernah berubah:
- Menghasilkan input melalui generate()
- Menghitung skor dari input melalui computeScore()
- Mengonversi skor menjadi koin/uang melalui computeReward()
- Menambahkan uang ke saldo total (money)
- Mengunjungi toko melalui visitShop()
- Selain itu, antarmuka abstrak (IInputGenerator, IScoringRule, IRewardRule) merupakan kontrak invarian yang menjaga alur tersebut tetap terhubung rapi.

2. Which parts are mutable?
Perubahan Logika:
Pembuat Input: Cara angka dibuat (misalnya RandomInputGenerator saat ini, atau nantinya input dari pemain/keyboard).
Aturan Skor: Rumus perhitungan nilai dari input (misalnya SimpleScoringRule atau aturan pengganda skor).
Aturan Reward: Rumus konversi skor ke koin (misalnya ModifiedRewardRule).
Perubahan Status (runtime state):
Variabel money pada RunSession (nilainya terus bertambah tiap ronde).
Penghitung ronde (round) yang berjalan dari 1 hingga 3.
Status internal fungsi rand() setiap kali dipanggil.

3. When you replaced the InputGenerator, why didn’t RunSession change?
RunSession tidak berubah karena kelas ini bergantung pada abstraksi (IInputGenerator), bukan pada implementasi konkretnya (RandomInputGenerator).
RunSession hanya tahu bahwa objek apa pun yang dipasang pasti memiliki fungsi generate() yang menghasilkan TurnInput.
Selama generator baru merupakan turunan dari IInputGenerator, RunSession tidak peduli dari mana angka itu berasal—apakah dari acakan komputer, ketikan pengguna, atau file eksternal.
Konsep ini merupakan penerapan dari Dependency Inversion Principle (salah satu prinsip SOLID) dan Strategy Pattern.

4. What would happen if scoring logic was placed inside RunSession?
Jika rumus skor dimasukkan langsung ke dalam RunSession, akan timbul beberapa masalah desain:
Melanggar Single Responsibility Principle (SRP): RunSession jadi memegang dua tanggung jawab sekaligus, yaitu mengatur jalannya permainan dan menentukan rumus penilaian.
Kode Menjadi Rentan: Setiap kali Anda ingin mengubah aturan skor (misalnya menambah bonus atau penalti), Anda harus mengedit kelas inti RunSession. Hal ini berisiko merusak alur permainan yang sebenarnya sudah berjalan baik.
Sulit Diuji (Testing): Anda tidak bisa lagi mengetes rumus matematika penskoran secara terpisah (unit test). Anda terpaksa harus menjalankan simulasi 3 ronde penuh hanya untuk memastikan rumus skornya benar.
