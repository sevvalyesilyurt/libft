# libft — Fonksiyon Hızlı Referans Kartı

## 📋 KATEGORİ 1: Karakter Kontrol (5 fonksiyon)

### ft_isalpha
- **İmza:** `int ft_isalpha(int c);`
- **İşlev:** Karakterin harf (A-Z, a-z) olup olmadığını kontrol eder
- **Dönüş:** 0 (hayır) | non-zero (evet)
- **Kompleksitet:** O(1)
- **Edge Case:** ASCII dışı değerler (negative int) → behavior implementation-dependent

### ft_isdigit
- **İmza:** `int ft_isdigit(int c);`
- **İşlev:** Karakterin rakam (0-9) olup olmadığını kontrol eder
- **Dönüş:** 0 (hayır) | non-zero (evet)

### ft_isalnum
- **İmza:** `int ft_isalnum(int c);`
- **İşlev:** Alfanumerik mi? (ft_isalpha || ft_isdigit)

### ft_isascii
- **İmza:** `int ft_isascii(int c);`
- **İşlev:** 0-127 aralığında mı?

### ft_isprint
- **İmza:** `int ft_isprint(int c);`
- **İşlev:** Yazdırılabilir mi? (32-126 aralığında)

---

## 📋 KATEGORİ 2: String İşlemleri (13 fonksiyon)

### ft_strlen
- **İmza:** `size_t ft_strlen(const char *s);`
- **İşlev:** String uzunluğunu döner (\0 hariç)
- **Kompleksitet:** O(n)
- **Edge Case:** NULL input → segfault (caller NULL göndermemeli)

### ft_strlcpy
- **İmza:** `size_t ft_strlcpy(char *dst, const char *src, size_t size);`
- **İşlev:** Safe string kopyala (null-terminate, overflow yok)
- **Dönüş:** src'nin uzunluğu
- **Kompleksitet:** O(n)
- **Edge Case:** size==0 → hiçbir şey kopyalanmaz, ama length döndürülür

### ft_strlcat
- **İmza:** `size_t ft_strlcat(char *dst, const char *src, size_t size);`
- **İşlev:** Safe string concatenation
- **Dönüş:** dst'nin initial length + src length (concatenation başarısız olsa da)

### ft_strchr
- **İmza:** `char *ft_strchr(const char *s, int c);`
- **İşlev:** İlk oluşum bulma
- **Dönüş:** Bulunursa pointer, yoksa NULL
- **Edge Case:** c=='\0' → string sonundaki null byte için pointer döndürülmeli

### ft_strrchr
- **İmza:** `char *ft_strrchr(const char *s, int c);`
- **İşlev:** Son oluşum bulma
- **Dönüş:** Bulunursa pointer, yoksa NULL

### ft_strncmp
- **İmza:** `int ft_strncmp(const char *s1, const char *s2, size_t n);`
- **İşlev:** İlk n karakteri karşılaştır
- **Dönüş:** <0 (s1<s2) | 0 (eşit) | >0 (s1>s2)

### ft_strnstr
- **İmza:** `char *ft_strnstr(const char *big, const char *little, size_t len);`
- **İşlev:** Substring bul (n byte içinde)
- **Dönüş:** Bulunursa pointer, yoksa NULL

### ft_strdup
- **İmza:** `char *ft_strdup(const char *s);`
- **İşlev:** String çoğalt (malloc ile yeni memory ayır)
- **Dönüş:** Yeni string pointer
- **Bellek:** Caller free() çağırmalı
- **Kompleksitet:** O(n) time, O(n) space

### ft_substr
- **İmza:** `char *ft_substr(char const *s, unsigned int start, size_t len);`
- **İşlev:** Alt string çıkart
- **Edge Case:** start > strlen(s) → empty string döndür

### ft_strjoin
- **İmza:** `char *ft_strjoin(char const *s1, char const *s2);`
- **İşlev:** İki string birleştir (malloc ile)
- **Dönüş:** Yeni string

### ft_strtrim
- **İmza:** `char *ft_strtrim(char const *s1, char const *set);`
- **İşlev:** String başı/sonundan set karakterlerini kaldır
- **Örnek:** ft_strtrim("  hello  ", " ") → "hello"

### ft_split
- **İmza:** `char **ft_split(char const *s, char c);`
- **İşlev:** String'i karakter c'ye göre böl
- **Dönüş:** Pointer array (NULL-terminated)
- **Örnek:** ft_split("one,two,three", ',') → ["one", "two", "three", NULL]
- **Bellek:** Array + strings için malloc; caller free array'i ve her string'i temizlemeli

### ft_strmapi
- **İmza:** `char *ft_strmapi(char const *s, char (*f)(unsigned int, char));`
- **İşlev:** Fonksiyon pointer'ı her karaktere uygula
- **Örnek:** ft_strmapi("abc", to_upper) → "ABC" (malloc ile yeni)

---

## 📋 KATEGORİ 3: Bellek İşlemleri (7 fonksiyon)

### ft_memset
- **İmza:** `void *ft_memset(void *s, int c, size_t n);`
- **İşlev:** n byte'ı c ile doldur
- **Dönüş:** s pointer'ı
- **Kompleksitet:** O(n)

### ft_bzero
- **İmza:** `void ft_bzero(void *s, size_t n);`
- **İşlev:** n byte'ı 0 ile doldur
- **İşlev:** ft_memset(s, 0, n) ile eşdeğer (ama void döner)

### ft_memcpy
- **İmza:** `void *ft_memcpy(void *dest, const void *src, size_t n);`
- **İşlev:** n byte kopyala (overlap varsa undefined)
- **Dönüş:** dest pointer'ı
- **Edge Case:** Eğer src ve dest overlap ediyorsa → Behavior undefined!

### ft_memmove
- **İmza:** `void *ft_memmove(void *dest, const void *src, size_t n);`
- **İşlev:** n byte kopyala (overlap safe)
- **Dönüş:** dest pointer'ı
- **Nasıl:** Eğer dest < src → ileri; dest > src → geri (overlap engeller)

### ft_memchr
- **İmza:** `void *ft_memchr(const void *s, int c, size_t n);`
- **İşlev:** n byte içinde c karakterini bul
- **Dönüş:** Bulunursa pointer, yoksa NULL

### ft_memcmp
- **İmza:** `int ft_memcmp(const void *s1, const void *s2, size_t n);`
- **İşlev:** n byte'ı karşılaştır
- **Dönüş:** <0 | 0 | >0

### ft_calloc
- **İmza:** `void *ft_calloc(size_t nmemb, size_t size);`
- **İşlev:** nmemb*size byte ayır + sıfırla
- **Dönüş:** Pointer veya NULL (overflow / malloc fail)
- **Overflow Kontrol:** if (nmemb != 0 && size > SIZE_MAX / nmemb) → NULL
- **Kompleksitet:** O(nmemb*size)

---

## 📋 KATEGORİ 4: Dönüşüm (4 fonksiyon)

### ft_atoi
- **İmza:** `int ft_atoi(const char *nptr);`
- **İşlev:** String → integer
- **Davranış:** Whitespace skip, +/- işareti, rakamlara kadar oku
- **Edge Case:** Overflow → behavior undefined (tipik: -INT_MIN dönüş, INT_MAX)

### ft_itoa
- **İmza:** `char *ft_itoa(int n);`
- **İşlev:** Integer → string (malloc ile)
- **Dönüş:** Yeni string pointer
- **Edge Case:** INT_MIN (-2147483648) → "-2147483648" (malloc gerekli)

### ft_tolower
- **İmza:** `int ft_tolower(int c);`
- **İşlev:** Harf ise lowercase'e çevir
- **Dönüş:** Çevrilmiş char veya c (değiştirilmediğinde)

### ft_toupper
- **İmza:** `int ft_toupper(int c);`
- **İşlev:** Harf ise uppercase'e çevir

---

## 📋 KATEGORİ 5: Dosya Descriptor (4 fonksiyon)

### ft_putchar_fd
- **İmza:** `void ft_putchar_fd(char c, int fd);`
- **İşlev:** 1 karakteri fd'e yaz
- **fd:** 1=stdout, 2=stderr, 0=stdin

### ft_putstr_fd
- **İmza:** `void ft_putstr_fd(char *s, int fd);`
- **İşlev:** String'i fd'e yaz (\n yok)

### ft_putendl_fd
- **İmza:** `void ft_putendl_fd(char *s, int fd);`
- **İşlev:** String + newline yaz

### ft_putnbr_fd
- **İmza:** `void ft_putnbr_fd(int n, int fd);`
- **İşlev:** Sayıyı fd'e yaz

---

## 📋 KATEGORİ 6: Bonus — Bağlı Liste (10 fonksiyon)

### ft_lstnew
- **İmza:** `t_list *ft_lstnew(void *content);`
- **İşlev:** Yeni node oluştur, content set et, next=NULL

### ft_lstadd_front
- **İmza:** `void ft_lstadd_front(t_list **lst, t_list *new_node);`
- **İşlev:** Yeni node'u başa ekle
- **Dikkat:** `**lst` (double pointer) — lst'nin kendisini değiştirmek için

### ft_lstadd_back
- **İmza:** `void ft_lstadd_back(t_list **lst, t_list *new_node);`
- **İşlev:** Yeni node'u sona ekle

### ft_lstsize
- **İmza:** `int ft_lstsize(t_list *lst);`
- **İşlev:** Node sayısını döner

### ft_lstlast
- **İmza:** `t_list *ft_lstlast(t_list *lst);`
- **İşlev:** Son node'a pointer döner
- **Edge Case:** lst==NULL → NULL döner

### ft_lstdelone
- **İmza:** `void ft_lstdelone(t_list *lst, void (*del)(void *));`
- **İşlev:** Tek node'u sil (content için del() çağırılır, node kendisi free()'e gider)

### ft_lstclear
- **İmza:** `void ft_lstclear(t_list **lst, void (*del)(void *));`
- **İşlev:** Tüm listeyi sil
- **Dikkat:** `**lst` — liste başını NULL'a set etmek için

### ft_lstiter
- **İmza:** `void ft_lstiter(t_list *lst, void (*f)(void *));`
- **İşlev:** Her node'un content'ine f fonksiyonunu uygula

### ft_lstmap
- **İmza:** `t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));`
- **İşlev:** Her node'un content'ine f uygulayıp yeni liste oluştur
- **Dönüş:** Yeni liste (malloc ile) veya error → NULL + del() çağrısı
- **Dikkat:** f başarısız (NULL dönüş) olursa → new list temizle + NULL döner

---

## 🎯 Sık Hatalar & Çözümler

| Hata | Nedeni | Çözüm |
|------|--------|-------|
| Segfault | NULL pointer deref | NULL kontrol `if (!ptr)` |
| Buffer overflow | Küçük buffer | `ft_strlcpy`, `ft_strlcat` kullan |
| Memory leak | `free()` unutulmuş | `free(ptr); ptr = NULL;` |
| Use-after-free | Serbest alınan bellek oku | `free()` sonra dereference etme |
| Double free | Aynı pointer 2x free | `free()` sonra `ptr = NULL` |
| Overlap issue | src-dst overlap | `ft_memmove` kullan, `ft_memcpy` değil |
| Undefined behavior | INT overflow | `ft_calloc`'da `size > MAX / count` kontrol |

---

## 🔧 Derleyici & Test Komutları

```bash
# Temel derleme
make re

# Test programı derle
gcc -Wall -Wextra -Werror -g test.c libft.a -o test

# Çalıştır
./test

# Valgrind ile bellek kontrol
valgrind --leak-check=full --show-leak-kinds=all ./test

# GDB ile debug
gdb ./test
(gdb) run
(gdb) bt  # Backtrace
(gdb) quit

# Kütüphanedeki semboller
nm libft.a
ar t libft.a
```

---

## 💡 Sunumda Öne Çıkacak Noktalar

1. **Yapı:** 50+ C fonksiyonu, libft.a statik kütüphanesi
2. **Bellek:** malloc, free, NULL kontrol, overflow'dan korunma
3. **Pointer İşlemleri:** void *, function pointer, double pointer
4. **Bağlı Liste:** generic list, function pointer callbacks
5. **Performans:** O(n) zaman, O(n) bellek, edge case handling
6. **Kod #Kalitesi:** -Wall -Wextra -Werror, Valgrind clean

---

## 📌 Hızlı Kontrol Listesi (Sunum Öncesi)

- [ ] Tüm 50+ fonksiyon derlenmiş ve kütüphanede
- [ ] Valgrind clean (leak, invalid read/write yok)
- [ ] NULL kontrol ve edge case'ler handled
- [ ] Buffer overflow özeni (strlcpy, strlcat, memmove)
- [ ] Bağlı liste malloc/free düzgün
- [ ] Function pointer'lar (strmapi, lstmap, lstiter) doğru
- [ ] File descriptor işlemleri (putchar_fd, etc.) write() kullanıyor mu?

Hazır mısın detay soruları almaya? Hangi fonksiyon hakkında daha derinlemesine açıklama istiyorsun?
