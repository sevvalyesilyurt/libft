# libft Projesi — Eksiksiz Analiz & Sunum Rehberi

## İçindekiler
1. [Proje Özeti](#1-proje-özeti)
2. [Mimarı & Tasarım](#2-mimarı--tasarım)
3. [Tip Sistemi & Veri Yapıları](#3-tip-sistemi--veri-yapıları)
4. [Bellek Yönetimi](#4-bellek-yönetimi)
5. [Fonksiyon Kategorileri](#5-fonksiyon-kategorileri)
6. [Standart Kütüphane vs libft](#6-standart-kütüphane-vs-libft)
7. [Edge Cases & Hatalar](#7-edge-cases--hatalar)
8. [Derleyici & Build Süreci](#8-derleyici--build-süreci)
9. [Performans & Zaman Kompleksitesi](#9-performans--zaman-kompleksitesi)
10. [Sunumda Söylenecek Kısa Cümleler](#10-sunumda-söylenecek-kısa-cümleler)

---

## 1. Proje Özeti

**libft** — 42 Okulu'nda verilen bir eğitim projesidir. Amaç:
- Standart C kütüphanesinin en yaygın kullanılan fonksiyonlarını **sıfırdan** implement etmek.
- Bellek yönetimi, pointer'lar, veri yapıları ve sistem çağrıları konularına hakim olmak.
- İyi kod yazma alışkanlıkları kazanmak (strict derleyici bayrakları: `-Wall -Wextra -Werror`).

**Proje Yapısı:**
- **Zorunlu kısım (Mandatory):** 40+ fonksiyon (string, bellek, karakter, liste işlemleri)
- **Ek kısım (Bonus):** Bağlı liste işlemleri (10+ fonksiyon)
- **Çıktı:** Statik kütüphane (`libft.a`)

**Kullanım:**
```bash
gcc -Wall -Wextra -Werror -c main.c
gcc main.o libft.a -o program
./program
```

---

## 2. Mimarı & Tasarım

### 2.1 Dosya Organizasyonu

```
libft/
├── ft_*.c           # 50+ implementasyon dosyası
├── libft.h          # Header (tüm fonksiyon prototiplerine erişim)
├── Makefile         # Derleme otomasyonu
└── README.md        # (opsiyonel) Belgelendirme
```

### 2.2 Derleme Stratejisi

**Static Library (`libft.a`):**
- Tüm `.c` dosyaları derlenip `.o` dosyalarına çevrilir.
- `.o` dosyaları `ar rcs` komutu ile birleştirilerek `libft.a` oluşturulur.
- Linking sırasında `libft.a` linklendiğinde, kullanılan fonksiyonlar executable'a dahil edilir.

**Avantajları:**
- Kütüphaneyi yeniden kullanabilirsin (başka projeler).
- Derleme hızlı (değişmemiş dosyalar tekrar derlenmez).

### 2.3 Include Guard & Header Dizayn

```c
#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>  // malloc, free, size_t
# include <unistd.h>  // write (file descriptors)

typedef struct s_list
{
    void *content;
    struct s_list *next;
} t_list;

// Tüm fonksiyon prototipleri burada
int ft_isalpha(int c);
// ...

#endif
```

**Neden?**
- Include guard: `.h` dosyası multiple kez include edilse bile, içeriği bir kez tanımlanır.
- `<stdlib.h>`: `malloc`, `free`, `size_t` için gerekli.
- `<unistd.h>`: `write()` için (dosya descriptor'larına yazma).

---

## 3. Tip Sistemi & Veri Yapıları

### 3.1 Temel Tipler

| Tip | Boyut (genelde) | Kullanım |
|-----|-----------------|----------|
| `int` | 4 bytes | Sayılar, return codes |
| `char` | 1 byte | Karakterler, bytes |
| `size_t` | 8 bytes (64-bit) | Boyutlar, loop counter (unsigned) |
| `void *` | 8 bytes (64-bit) | Genel amaçlı pointer |

### 3.2 Önemli Struct: `t_list` (Bağlı Liste)

```c
typedef struct s_list
{
    void *content;       // Herhangi bir veriyi tutabilen pointer
    struct s_list *next; // Sonraki node'a işaretçi
} t_list;
```

**Neden `void *`?**
- Listenin **generic** (tür-agnostic) olması için.
- Bir listede int'ler, char'lar, struct'lar, hatta pointer'lar tutabilirsin.
- Örnek:
  ```c
  t_list *node = ft_lstnew((void *)malloc(sizeof(int)));
  int *ptr = (int *)node->content;
  *ptr = 42;  // Type cast ile int olarak kullanabilirsin
  ```

### 3.3 Void Pointer Casting

```c
void *data = malloc(100);
char *char_ptr = (char *)data;       // char dizi olarak oku
int *int_ptr = (int *)data;          // int olarak oku
struct my_struct *s = (struct my_struct *)data;  // struct olarak oku
```

---

## 4. Bellek Yönetimi

### 4.1 Heap vs Stack

| Memory | Boyut | Hız | Yaşam Süresi | İlklendir |
|--------|-------|-----|--------------|-----------|
| **Stack** | Küçük (~8MB) | Hızlı | Fonksiyon kapanana kadar | Otomatik |
| **Heap** | Büyük (~GB) | Yavaş | `free()` çağrılana kadar | Manuel (`malloc`) |

**Örnekler:**
```c
// Stack (otomatik, fonksiyon çıkışında silinir)
void func() {
    char buffer[100];  // 100 byte, fonksiyon bitince yok olur
}

// Heap (manuel yönetim, caller free() çağırmalı)
char *ptr = malloc(100);  // 100 byte ayır
// ... kullan ...
free(ptr);  // Manual olarak serbest bırak
ptr = NULL; // İyi bir practice: serbest bıraktıktan sonra NULL yap
```

### 4.2 libft'deki Bellek Fonksiyonları

| Fonksiyon | İşlev |
|-----------|-------|
| `malloc(size)` | Bellek ayır, initialize etme |
| `ft_calloc(count, size)` | Bellek ayır + sıfırla |
| `free(ptr)` | Bellek serbest bırak |
| `ft_memset(s, c, n)` | `n` byte'ı `c` ile doldur |
| `ft_bzero(s, n)` | `n` byte'ı 0 ile doldur |
| `ft_memcpy(dst, src, n)` | `n` byte kopyala (overlap varsa risk) |
| `ft_memmove(dst, src, n)` | `n` byte kopyala (overlap güvenli) |

### 4.3 Sık Yapılan Hatalar

```c
// ❌ HATA 1: malloc geri dönüş kontrolü yapılmamış
char *p = malloc(100);
strcpy(p, "data");  // malloc başarısız ise p == NULL, segfault!

// ✅ DOĞRU:
char *p = malloc(100);
if (!p) return;  // NULL kontrolü
strcpy(p, "data");
free(p);

// ❌ HATA 2: double-free
free(ptr);
free(ptr);  // CRASH! Aynı pointer iki kez serbest bırakılamaz

// ✅ DOĞRU:
free(ptr);
ptr = NULL;  // NULL'e set et, ikinci free harmless olur

// ❌ HATA 3: use-after-free
free(ptr);
printf("%s", ptr);  // UNDEFINED BEHAVIOUR! Bellek serbest alındıktan sonra oku

// ✅ DOĞRU:
free(ptr);
ptr = NULL;  // Artık dereferance etme
```

---

## 5. Fonksiyon Kategorileri

### 5.1 Karakter Kontrol Fonksiyonları (5 fonksiyon)

```c
int ft_isalpha(int c);   // Harf mı? (A-Z, a-z)
int ft_isdigit(int c);   // Rakam mı? (0-9)
int ft_isalnum(int c);   // Alfanumerik mi? (harf+rakam)
int ft_isascii(int c);   // ASCII mi? (0-127)
int ft_isprint(int c);   // Yazdırılabilir mi? (32-126)
```

**Dönüş:** 0 (false) veya non-zero (true)

**Örnek:**
```c
ft_isalpha('A')   → 1 (true)
ft_isalpha('5')   → 0 (false)
ft_isdigit('5')   → 1 (true)
ft_isascii(255)   → 0 (false, ASCII aralığı dışı)
```

### 5.2 String Fonksiyonları (13 fonksiyon)

| Fonksiyon | İşlev | Standart Eşdeğeri |
|-----------|-------|-------------------|
| `ft_strlen` | String uzunluğu | `strlen` |
| `ft_strlcpy` | Safe copy | `strncpy` (daha güvenli) |
| `ft_strlcat` | Safe concatenate | `strncat` (daha güvenli) |
| `ft_strchr` | İlk oluşum bul | `strchr` |
| `ft_strrchr` | Son oluşum bul | `strrchr` |
| `ft_strncmp` | Karşılaştır (n char) | `strncmp` |
| `ft_strnstr` | Substring bul | `strstr` (n-limited) |
| `ft_strdup` | String çoğalt | `strdup` |
| `ft_substr` | Alt string | (standart yok) |
| `ft_strjoin` | Birleştir | (standart yok) |
| `ft_strtrim` | Kenarları temizle | (standart yok) |
| `ft_split` | Bölüne ayır | (standart yok) |
| `ft_strmapi` | Map fonksiyon | (standart yok) |

**Örnek — `ft_strlcpy`:**
```c
char dst[10];
ft_strlcpy(dst, "Hello World", 10);
// dst = "Hello Wor" (null-terminated, 10 byte'a sığması için)
// return = 11 (orijinal uzunluk)

// Buffer overflow yok! "L Wor" kesildi ama güvenli.
```

### 5.3 Bellek Fonksiyonları (7 fonksiyon)

| Fonksiyon | İşlev |
|-----------|-------|
| `ft_memset` | `n` byte'ı `c` ile doldur |
| `ft_bzero` | `n` byte'ı 0 ile doldur |
| `ft_memcpy` | `n` byte kopyala |
| `ft_memmove` | `n` byte kopyala (overlap safe) |
| `ft_memchr` | Bayt bul |
| `ft_memcmp` | Karşılaştır |
| `ft_calloc` | Bellek ayır + sıfırla |

**Örnek — `ft_memcpy` vs `ft_memmove`:**
```c
char src[5] = "ABCD";
char dst[5];

// ✅ ft_memcpy (overlap yok)
ft_memcpy(dst, src, 4);  // OK

// ❌ ft_memcpy (overlap var — undefined)
char buf[10] = "ABCDEFGH";
ft_memcpy(buf + 2, buf, 5);  // Overlap! HATA RISKI

// ✅ ft_memmove (overlap safe)
char buf[10] = "ABCDEFGH";
ft_memmove(buf + 2, buf, 5);  // OK, "ABABABCD" gibi sonuç
```

### 5.4 Dönüşüm Fonksiyonları (3 fonksiyon)

```c
int ft_atoi(const char *nptr);     // String → int
char *ft_itoa(int n);               // int → String
int ft_tolower(int c);              // Harfi lowercase'e çevir
int ft_toupper(int c);              // Harfi uppercase'e çevir
```

**Örnek:**
```c
ft_atoi("42")        → 42
ft_atoi("-100")      → -100
ft_atoi("  -5")      → -5 (whitespace skip)

ft_itoa(42)          → "42" (malloc ile yeni string)
ft_tolower('A')      → 'a'
ft_toupper('a')      → 'A'
```

### 5.5 Dosya Descriptor Fonksiyonları (4 fonksiyon)

```c
void ft_putchar_fd(char c, int fd);    // 1 char yaz
void ft_putstr_fd(char *s, int fd);    // String yaz
void ft_putendl_fd(char *s, int fd);   // String + newline yaz
void ft_putnbr_fd(int n, int fd);      // Sayı yaz
```

**File Descriptor (fd):**
- `0` = stdin (input)
- `1` = stdout (output, `printf` kullanır)
- `2` = stderr (error output)

**Örnek:**
```c
ft_putchar_fd('A', 1);           // stdout'a 'A' yaz
ft_putstr_fd("Hello", 1);         // stdout'a "Hello" yaz
ft_putendl_fd("Hi", 1);           // stdout'a "Hi\n" yaz
ft_putnbr_fd(42, 2);              // stderr'e "42" yaz
```

### 5.6 Bağlı Liste Fonksiyonları (10 fonksiyon - BONUS)

```c
t_list *ft_lstnew(void *content);               // Yeni node
void ft_lstadd_front(t_list **lst, t_list *new);// Başa ekle
void ft_lstadd_back(t_list **lst, t_list *new); // Sona ekle
int ft_lstsize(t_list *lst);                    // Eleman sayısı
t_list *ft_lstlast(t_list *lst);                // Son node
void ft_lstdelone(t_list *lst, void (*del)(void *)); // 1 node sil
void ft_lstclear(t_list **lst, void (*del)(void *)); // Tümünü sil
void ft_lstiter(t_list *lst, void (*f)(void *)); // Her node'a fonksiyon uygula
t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *)); // Transform
```

**Örnek:**
```c
t_list *head = NULL;
head = ft_lstnew((void *)malloc(sizeof(int)));
*(int *)head->content = 42;

ft_lstadd_back(&head, ft_lstnew((void *)malloc(sizeof(int))));
*(int *)head->next->content = 100;

printf("Size: %d\n", ft_lstsize(head));  // 2
ft_lstclear(&head, free);                 // Tümünü sil
```

---

## 6. Standart Kütüphane vs libft

| Amaç | Standart | libft |
|------|----------|-------|
| `strlen` | `<string.h>` | `ft_strlen` |
| `strcpy` | `<string.h>` | `ft_strlcpy` (güvenli) |
| `memset` | `<string.h>` | `ft_memset` |
| `malloc` | `<stdlib.h>` | Doğrudan kullanılır |
| Linked list | Standart yok | `ft_list_*` |

**Neden libft?**
- 42'nin kuralı: standart string/memory fonksiyonları yasaklı.
- Amaç: algoritmaları anlaman ve implement etmeni sağlamak.
- Avantaj: Boost et!

---

## 7. Edge Cases & Hatalar

### 7.1 NULL Pointer Kontrolü

```c
// ❌ GÜVENSIZ
ft_strlen(str);  // str NULL ise segfault

// ✅ 42 STANDARDı (çoğu fonksiyon NULL tolerance'ı belirtmez)
// Caller NULL göndermemeli, yani:
if (str != NULL)
    ft_strlen(str);

// ANCAK:
// ft_lstclear, ft_lstiter gibi liste fonksiyonları
// NULL list'i handle etmeli (empty list)
```

### 7.2 Buffer Overflow

```c
char buf[5];
ft_strlcpy(buf, "Hello World", 5);  // ✅ Güvenli (null-terminated, "Hell" + \0)

// Ancak naive strcpy:
strcpy(buf, "Hello World");  // ❌ CRASH! 12 byte'ı 5 byte'lık buffer'a kopyala
```

### 7.3 Overflow Kontrolü (`ft_calloc`)

```c
// ❌ KÖTÜ:
void *p = malloc(count * size);  // count * size taşmış olabilir!

// ✅ DOĞRU:
if (count != 0 && size > SIZE_MAX / count)
    return NULL;  // Overflow detected
```

### 7.4 Overlapping Memory (`ft_memcpy` vs `ft_memmove`)

```c
char buf[10] = "ABCDE";

// ❌ Undefined (overlap):
ft_memcpy(buf + 1, buf, 4);

// ✅ Correct (overlap safe):
ft_memmove(buf + 1, buf, 4);  // "AABCD"
```

### 7.5 Uninitialized Variables

```c
// ❌ KÖTÜ:
int *p;
*p = 42;  // p nereyi gösteriyor? Segfault!

// ✅ DOĞRU:
int *p = malloc(sizeof(int));
if (!p) return;
*p = 42;
free(p);
```

---

## 8. Derleyici & Build Süreci

### 8.1 Derleyici Bayrakları

```bash
gcc -Wall -Wextra -Werror
```

| Bayrak | İşlev |
|--------|--------|
| `-Wall` | Tüm yaygın uyarıları etkinleştir |
| `-Wextra` | Ekstra uyarıları etkinleştir |
| `-Werror` | Uyarıları error olarak kabul et (derleme başarısız) |

**Örnek Hata:**
```c
int x;
x = 5;
printf("%s", x);  // Tip uyuşmazlığı (int yerine const char *)
```

Derleyici `-Wall` ile uyarır, `-Werror` ile başarısız olur.

### 8.2 Makefile Komutları

```bash
# Derleme
make              # libft.a oluştur

# Bonus
make bonus        # Bonus fonksiyonları ekle

# Temizlik
make clean        # .o dosyalarını sil
make fclean       # .o ve libft.a'yı sil
make re           # Temizle ve yeniden derleme
```

### 8.3 Object Dosyaları & Archiving

```bash
# Derleme: .c → .o
gcc -Wall -Wextra -Werror -c ft_strlen.c -o ft_strlen.o

# Archiving: .o dosyalarını .a'ya birleştir
ar rcs libft.a ft_strlen.o ft_strchr.o ...

# Linking: libft.a'yı program'a link et
gcc main.o libft.a -o program
```

---

## 9. Performans & Zaman Kompleksitesi

### 9.1 Big-O Analizi

| Fonksiyon | Kompleksitet | Açıklama |
|-----------|--------------|-----------|
| `ft_strlen` | O(n) | String'i sonuna kadar tarama |
| `ft_strchr` | O(n) | String'de arat (worst case: sonda veya yok) |
| `ft_strncmp` | O(n) | n karakter karşılaştır |
| `ft_memcpy` | O(n) | n byte kopyala |
| `ft_isalpha` | O(1) | Tek karakter kontrol |
| `ft_lstsize` | O(n) | Listeyi sonuna kadar gezme |
| `ft_lstclear` | O(n) | Her node'u sil |

### 9.2 Bellek Kompleksitesi

| Fonksiyon | Bellek | Açıklama |
|-----------|--------|-----------|
| `ft_strlen` | O(1) | Stack: sadece int counter |
| `ft_strdup` | O(n) | Heap: yeni string için n+1 byte |
| `ft_split` | O(n+m) | Heap: string + array + pointers |
| `ft_lstnew` | O(1) | Heap: bir node (16 byte) |

---

## 10. Sunumda Söylenecek Kısa Cümleler

### Giriş
**"libft, 42'de verilen bir eğitim projesidir. Amaç, standart C kütüphanesinin 50+ fonksiyonunu sıfırdan implement etmek — string işlemleri, bellek yönetimi, karakter kontrol ve bağlı liste veri yapıları."**

### Mimarı
**"Proje 50+ C dosyasından oluşur ve `libft.a` statik kütüphanesi halinde compile edilir. Header dosya tüm prototipleri tanımlar ve `-Wall -Wextra -Werror` bayraklarıyla katı derleme sağlanır."**

### Kategoriler
**"Fonksiyonları 6 kategoriye ayırdım: karakter kontrol (5), string işlemleri (13), bellek (7), dönüşüm (4), dosya descriptor (4) ve bonus olarak bağlı liste (10). Toplam 43 zorunlu + 10 bonus."**

### Bellek Yönetimi
**"Bellek yönetimi bu projede kritiktir. `malloc`, `free` ve `NULL` kontrolü yapılmadığında segfault veya memory leak oluşur. Buffer overflow'dan korunmak için `ft_strlcpy` ve `ft_memmove` gibi safe fonksiyonlar kullanıldı."**

### Bağlı Liste
**"Bonus kısımda bağlı liste implement ettim. `void *` generic pointer ile herhangi bir veri tutabilen node'lar ve function pointer'lar (yüksek mertebeden fonksiyonlar) kullanarak esnek bir API tasarladım."**

### Edge Cases
**"Overflow kontrolü, NULL pointer handling, buffer overrun, overlapping memory gibi edge case'ler projeyi zorlayan kısımları. Valgrind ve `-fsanitize=address` ile hata araştırması yaptım."**

### Sonuç
**"libft, C'nin temellerini anlamak — pointer'lar, bellek yönetimi, sistem-level API'ler ve veri yapıları — için ideal bir platformdur."**

---

## Ek: Sık Kullanılan Komutlar

```bash
# Derleme & Test
make re
gcc -Wall -Wextra -Werror test.c libft.a -o test
./test

# Valgrind ile bellek kontrol
valgrind --leak-check=full --show-leak-kinds=all ./test

# GCC sanitizer (address sanitizer)
gcc -Wall -Wextra -Werror -fsanitize=address test.c libft.a -o test
./test

# nm ile kütüphanedeki semboleri listele
nm libft.a

# ar ile kütüphanedeki dosyaları listele
ar t libft.a
```

---

## Sonda

Bu analiz, 42 evosa girişte yardımcı olacak temel bilgileri kapsar. Her fonksiyon için detaylı açıklama, test senaryoları ve sunum metinleri ayrı olarak talep edebilirsin.

**Başarılar! 🚀**
