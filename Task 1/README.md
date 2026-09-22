Reflection (Mandatory — 200–300 words)
In your README.md, answer:
1. What is the invariant structure in your program?
2. Which parts are mutable?
3. When you replaced the InputGenerator, why didn’t RunSession
change? 4. What would happen if scoring logic was placed inside
RunSession? Clarity of explanation matters more than complexity.

1. Struktur invarian dalam program ini adalah urutan game loop yang mutlak dan tidak dapat diubah yang berjalan tepat tiga ronde, di mana setiap ronde harus mengikuti fase eksekusi yang berurutan secara ketat: menghasilkan input, menghitung skor dasar, menghitung hadiah, memperbarui saldo uang, memicu fase toko, dan maju ke ronde berikutnya.

2. Bagian yang mutable (dapat diubah) adalah perilaku mekanik yang dapat saling ditukar dan dimasukkan ke dalam core loop, secara spesifik meliputi implementasi konkret dari logika pembuat input (input generator), aturan penilaian (scoring rules), dan formula perhitungan hadiah (reward rules), di mana semuanya dapat dimodifikasi atau diganti dengan bebas.

3. Ketika input generator awal diganti dengan RandomInputGenerator, kelas RunSession sama sekali tidak berubah karena kelas tersebut hanya bergantung pada kontrak interface abstrak IInputGenerator, bukan pada detail implementasi spesifiknya, sehingga ia dapat menerima kelas apa pun yang mengimplementasikan interface tersebut tanpa mengubah kodenya sendiri.

4. Jika logika penilaian ditulis langsung (hardcoded) di dalam RunSession, core loop akan terikat kuat (tightly coupled) dengan mekanik gameplay tertentu; akibatnya, setiap penyesuaian keseimbangan game di masa depan akan memaksa modifikasi langsung pada core loop itu sendiri, merusak fleksibilitas arsitektur sistem, dan meningkatkan risiko rusaknya urutan dasar permainan.
