# Task 1 -- Building a Balatro-Like Run

## Cara compile & run
```
g++ -std=c++17 *.cpp -o run
./run
```

## Struktur file
| File | Peran |
|---|---|
| `TurnInput.h` | Struct input per ronde: `value` (tipe hand dummy 1-13) dan `cards` (5 kartu) |
| `Card.h` | Struct kartu (rank + suit) dan `ToString()` |
| `CardBuilder.h/.cpp` | Membuat 5 kartu acak yang sesuai dengan tipe hand dari `value` |
| `IInputGenerator.h` | Interface generator input |
| `ManualInputGenerator.h/.cpp` | Implementasi awal (fixed value) |
| `RandomInputGenerator.h/.cpp` | Implementasi Modifikasi 1 |
| `IScoringRule.h` | Interface penghitung base score |
| `BasicScoringRule.h/.cpp` | Implementasi scoring (skor = input) |
| `ChainScoringRule.h/.cpp` | Scoring: evaluasi hand lewat chain 13 checker, lalu rank diubah jadi skor |
| `HandRank.h` | Enum hasil klasifikasi hand (13 jenis, dari HIGH_CARD sampai FLUSH_FIVE) |
| `PokerHandChecker.h/.cpp` | Abstract handler Chain of Responsibility (`Check`, `SetNext`) |
| `HighCardChecker`, `PairChecker`, `TwoPairChecker`, `ThreeOfAKindChecker`, `StraightChecker`, `FlushChecker`, `FullHouseChecker`, `FourOfAKindChecker`, `StraightFlushChecker`, `RoyalFlushChecker`, `FiveOfAKindChecker`, `FlushHouseChecker`, `FlushFiveChecker` (masing-masing `.h/.cpp`) | Concrete handler, satu kelas per jenis hand |
| `IRewardRule.h` | Interface penghitung reward |
| `BasicRewardRule.h/.cpp` | Reward = base score (versi awal) |
| `ModifiedRewardRule.h/.cpp` | Implementasi Modifikasi 2 |
| `ShopSystem.h/.cpp` | Cetak tawaran shop |
| `RunSession.h/.cpp` | Orkestrator, urutan fase tetap |
| `main.cpp` | Wiring: bikin instance konkret & inject ke RunSession |

## Chain of Responsibility pada scoring

`ChainScoringRule` menggantikan `BasicScoringRule` di `main.cpp`. Hand tidak
lagi langsung dijadikan skor, tetapi dievaluasi dulu oleh chain checker:

```
RunSession
   ↓
IScoringRule::ComputeScore(input)   (ChainScoringRule)
   ↓
FlushFive -> FlushHouse -> FiveOfAKind -> RoyalFlush -> StraightFlush
-> FourOfAKind -> FullHouse -> Flush -> Straight -> ThreeOfAKind
-> TwoPair -> Pair -> HighCard
   ↓
HandRank
   ↓
ConvertRankToScore()
   ↓
base score
```

Setiap checker menjawab satu pertanyaan, "apakah hand ini cocok dengan
aturanku?". Kalau cocok, ia mengembalikan rank-nya. Kalau tidak, hand
diteruskan ke checker berikutnya lewat `m_nextChecker`.

Implementasi belum sampai ke logic kartu. Setiap checker hanya mencetak jenis
hand (`[CHECK] Detected ...`) dan mengembalikan `HandRank`-nya. Sebagai
pengganti hand asli dipakai nilai dummy `TurnInput.value` (1 sampai 13 dari
`RandomInputGenerator`), satu nilai untuk satu jenis hand:

| `value` | Hand | Base score |
|---|---|---|
| 1 | High Card | 5 |
| 2 | Pair | 10 |
| 3 | Two Pair | 15 |
| 4 | Three of a Kind | 20 |
| 5 | Straight | 25 |
| 6 | Flush | 30 |
| 7 | Full House | 35 |
| 8 | Four of a Kind | 40 |
| 9 | Straight Flush | 50 |
| 10 | Royal Flush | 60 |
| 11 | Five of a Kind | 70 |
| 12 | Flush House | 80 |
| 13 | Flush Five | 100 |

Selain `value`, `RandomInputGenerator` juga membagikan 5 kartu acak lewat
`BuildHandForRank(value)`, lalu `RunSession` mencetaknya. Kartu dibuat
mengikuti tipe hand dari `value`, jadi kartu yang tampil selalu cocok dengan
hasil checker. Checker tetap hanya membaca `value` (belum ada logic kartu).
Suit ditulis `S` (spades), `H` (hearts), `D` (diamonds), `C` (clubs), dan
rank `J`, `Q`, `K`, `A`. Contoh output:

```
[PLAY] input generated: 12
[PLAY] cards: KS KS KS 5S 5S
[CHECK] Detected FLUSH HOUSE
```

Flush House, Five of a Kind, dan Flush Five memakai kartu duplikat (rank dan
suit sama), seperti di Balatro.

Chain dirakit dari hand terkuat ke terlemah, dan `HighCardChecker` menjadi
ujung chain (selalu cocok).

`RunSession` tidak diubah sama sekali. Penggantian `BasicScoringRule` menjadi
`ChainScoringRule` cukup dilakukan di `main.cpp` karena `RunSession` hanya
bergantung pada interface `IScoringRule`.

## Reflection

**1. Apa invariant structure dalam program ini?**
Urutan enam fase di dalam `RunSession::StartRun()`: generate input -> compute
base score -> compute reward -> update money -> shop phase -> advance round.
Urutan ini tetap sama di setiap ronde dan tidak boleh berubah walau
implementasi di baliknya diganti.

**2. Bagian mana yang mutable?**
Implementasi konkret di balik tiap interface: cara input dihasilkan
(`ManualInputGenerator` vs `RandomInputGenerator`), rumus scoring
(`BasicScoringRule` vs `ChainScoringRule`), dan rumus reward (`BasicRewardRule`
vs `ModifiedRewardRule`). Semua ini bisa diganti tanpa mengubah urutan fase.

**3. Kenapa RunSession tidak berubah waktu InputGenerator diganti?**
Karena `RunSession` hanya bergantung pada interface `IInputGenerator`, bukan
pada kelas konkretnya. `RunSession` memanggil `m_inputGen->Generate()` tanpa
peduli objek di baliknya `ManualInputGenerator` atau `RandomInputGenerator`.
Penggantian implementasi cukup dilakukan di `main.cpp`, tempat objek konkret
dibuat dan di-inject lewat constructor.

**4. Apa yang terjadi kalau scoring logic dipindah ke dalam RunSession?**
`RunSession` jadi tahu detail cara menghitung skor, sehingga setiap kali
aturan skor berubah, kelas orkestrator ini ikut harus diubah. Ini melanggar
prinsip pemisahan tanggung jawab, membuat `RunSession` sulit diuji secara
terpisah, dan menghilangkan kemampuan menukar strategi skor secara dinamis
seperti yang dilakukan lewat `IScoringRule` saat ini.

**5. Apa keuntungan memakai Chain of Responsibility dibanding if-else panjang?**
Setiap aturan hand berada di kelas sendiri dengan satu tanggung jawab, urutan
evaluasi terlihat jelas di tempat chain dirakit (`ChainScoringRule`), dan hand
type baru (misalnya Pair) bisa ditambahkan dengan membuat checker baru lalu
menyambungkannya ke chain, tanpa mengubah checker yang sudah ada.

## Pembagian tugas kelompok

| | Person 1 | Person 2 |
|---|---|---|
| Checker | HighCard, Pair, TwoPair, ThreeOfAKind, Straight, Flush | FullHouse, FourOfAKind, StraightFlush, RoyalFlush, FiveOfAKind, FlushHouse, FlushFive |
| File lain | `HandRank.h`, `README.md`, `.gitignore` | `ChainScoringRule.h/.cpp`, `Card.h`, `CardBuilder.h/.cpp`, `TurnInput.h`, `RandomInputGenerator.cpp`, `ManualInputGenerator.cpp`, `RunSession.cpp` |
