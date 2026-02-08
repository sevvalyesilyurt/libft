# libft — 42 Evos FAQ & Görüşme Soruları

## 🎤 "Önce Proje Hakkında Kısaca Anlat"

**Cevap (30 saniye):**
"libft, 42 Okulu'nda verilen bir C eğitim projesidir. Standart kütüphanesinin 50+ fonksiyonunu sıfırdan implement ettim. Karakter kontrol, string işlemleri, bellek yönetimi, dönüşüm ve bağlı liste olmak üzere 6 kategoriye ayrılmıştır. Çıktı `libft.a` statik kütüphanesidir ve pointer'lar, bellek yönetimi ve veri yapıları hakkında derinlemesine bilgi verir."

---

## 🔍 Teknik Sorular & Cevaplar

### S1: "Neden `ft_strlcpy` ve `ft_strlcat` kullandın? Farkı nedir?"

**Cevap:**
"Standart `strcpy` ve `strcat` buffer overflow'a açıktır — hedef buffer kaçırırsan segfault olur. `strlcpy` ve `strlcat` size parametresi alıp null-terminated string'i güvenli kopar. Örnek:

```c
char buf[5];
strcpy(buf, "Hello World");  // ❌ 12 byte'ı 5 byte'lık buffer'a!
strlcpy(buf, "Hello World", 5);  // ✅ "Hell\0" kopyalar
```

`strlcpy` ayrıca orijinal string uzunluğunu döner — bu, çağıran kodu buffer yeterli mi diye kontrol etmeye izin verir."

---

### S2: "Bellek Yönetimi konusunda Sıkıntı Yaşadığın Var mı?"

**Cevap:**
"Bellek yönetimi projenin en zor kısmıydı. Öğrendiğim dersin:

1. **Ownership:** Fonksiyon bellek ayırıyorsa, caller free() çağırmalı ve bu dokumente edilmeli.
2. **Bellek Sızıntısı (Leak):** `malloc()` başarısız olursa, error durumunda `free()` çağırılmalı. Örneğin `ft_split`'te:
   ```c
   char **result = malloc(count * sizeof(char *));
   if (!result) return NULL;
   for (int i = 0; i < count; i++) {
       result[i] = malloc(len);
       if (!result[i]) {
           // ❌ HATA: 0 to i-1 arasındaki belleği free() etmedin!
           free(result);
           return NULL;
       }
   }
   ```
3. **Valgrind:** Hata arayan araç olarak `valgrind --leak-check=full` benim en iyi arkadaşım oldu."

---

### S3: "ft_calloc'daki Overflow Kontrolü Neden Önemli?"

**Cevap:**
"Overflow kontrolü yapılmazsa, `count * size` hesaplaması taşabilir. Örneğin:

```c
// ❌ KÖTÜ
void *p = malloc(count * size);

// Eğer count = 1000000, size = 0x10000 → 0x10000000000 = 4TB
// Fakat size_t taşar → 0 olur → malloc(0) → belki NULL veya 1 byte
// → Buffer overflow!

// ✅ DOĞRU
if (count != 0 && size > SIZE_MAX / count)
    return NULL;  // Overflow tespit
```

Bu, integer overflow security vulnerability'sini engeller."

---

### S4: "ft_memcpy vs ft_memmove — İç Fark Nedir?"

**Cevap:**
"`memcpy` overlap'in undefined olduğu varsayar. `memmove` overlap safe:

```c
char buf[10] = "ABCDE";

// ft_memcpy (UB eğer overlap):
ft_memcpy(buf + 1, buf, 4);  // ❌ Risk!

// ft_memmove (safe):
// Eğer dest > src: geriye gidiyorsun (sonda başla)
// Eğer dest < src: öne gidiyorsun
ft_memmove(buf + 1, buf, 4);  // ✅ "AABCD"
```

Implementasyonda:
```c
if (dest < src)
    while (n--) *dest++ = *src++;  // Öne git
else
    while (n--)  // Geriye git
        *(dest + n) = *(src + n);
```

Bu overlap'i etkili kılıyor."

---

### S5: "Bağlı Liste İmplementasyonunda Function Pointer'ları Neden Kullandın?"

**Cevap:**
"Function pointer'lar generic (tür-agnostic) kod sağlar. Örnek:

```c
// ft_lstmap: Her node'un content'ine fonksiyon uygula
t_list *ft_lstmap(t_list *lst, 
                  void *(*f)(void *),  // Callback fonksiyon
                  void (*del)(void *)) // Hata durumunda temizleme
{
    while (lst) {
        new_content = f(lst->content);  // İsteğe göre dönüşüm
        lst = lst->next;
    }
}

// Çağrı: herhangi bir dönüşüm fonksiyonu pas edebilirsin
int *double_val(void *val) {
    int *num = (int *)val;
    *num *= 2;
    return num;
}

t_list *new_list = ft_lstmap(old_list, double_val, free);
```

Bu, C'de Functional Programming'in örneğidir ve kodu çok esnek kılar."

---

### S6: "Whitespace Handling'de ft_atoi'nde Nasıl Kontrol Ediyor?"

**Cevap:**
"POSIX `atoi` whitespace (space, tab, newline, vb.) skip eder:

```c
int ft_atoi(const char *nptr)
{
    int sign = 1;
    int result = 0;
    
    // Whitespace skip
    while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
        nptr++;
    
    // +/- işareti
    if (*nptr == '+' || *nptr == '-') {
        if (*nptr == '-') sign = -1;
        nptr++;
    }
    
    // Rakamlara kadar oku ve bırak
    while (*nptr >= '0' && *nptr <= '9') {
        result = result * 10 + (*nptr - '0');
        nptr++;
    }
    
    return result * sign;
}
```

Örnek: `ft_atoi(\"  -123abc\") → -123` (whitespace, işaret, rakamlara kadar)"

---

### S7: "ft_split'te Bellek Hatasını Nasıl Önledin?"

**Cevap:**
"`ft_split` çok bellek ayırıyor — her kelimenin+array için. Bellek leak riski var:

```c
char **ft_split(char const *s, char c)
{
    int count = count_words(s, c);
    char **result = malloc((count + 1) * sizeof(char *));
    if (!result) return NULL;
    
    for (int i = 0; i < count; i++) {
        result[i] = malloc(word_len + 1);
        if (!result[i]) {
            // ❌ HATA: 0 to i-1 serbest bırakılmadı
            free(result);
            return NULL;
        }
        // ... extract word ...
    }
    result[count] = NULL;  // NULL-terminate
    return result;
}
```

**Çözüm:** Helper fonksiyon:
```c
static void free_split(char **result, int count) {
    while (count--)
        free(result[count]);
    free(result);
}

// Hata durumunda:
if (!result[i]) {
    free_split(result, i);  // 0 to i-1 temizle
    return NULL;
}
```"

---

### S8: "Typedef t_list Neden Struct'ın Önünde Yazıldı?"

**Cevap:**
"C'de struct tanıtmak için:

```c
// ❌ Uzun yol
struct s_list {
    void *content;
    struct s_list *next;
};
struct s_list *node = malloc(sizeof(struct s_list));

// ✅ Kısa yol (typedef ile)
typedef struct s_list {
    void *content;
    struct s_list *next;
} t_list;
t_list *node = malloc(sizeof(t_list));
```

Typedef, type alias oluşturur. `t_list` keyword olur. Kod daha okunabilir ve kısa."

---

### S9: "Derleyici Bayrakları (-Wall -Wextra -Werror) Neden Önemli?"

**Cevap:**
"Bu bayraklar kodu katı hale getirir:

- `-Wall` → Tüm yaygın uyarılar (unused var, tip mismatch, etc.)
- `-Wextra` → Extra uyarılar (implicit cast, missing field initializer)
- `-Werror` → Uyarılar error olur → derleme başarısız

**Örnek:**
```c
char *p = malloc(10);
strcpy(p, \"hello\");
printf(\"%d\", p);  // ❌ char * yerine int! `-Wall` uyarı verir
```

Bu, buggy kod'u yakalamaya yardımcı olur."

---

### S10: "Norm & Code Style — Nasıl Uyum Sağladın?"

**Cevap (42'ye özel):**
"42'nin Norm kuralları var:

1. **Satır uzunluğu:** Max 80 karakter
2. **Function uzunluğu:** Max 25 satır
3. **Nesting:** Max 5 seviye
4. **Değişken sayısı:** Max 5 lokali
5. **Dosya adı:** Lowercase, underscore ile

Örnek **iyi**:
```c
int ft_isalpha(int c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}
```

Örnek **kötü**:
```c
int ft_isalpha(int c) {  // Brace yanlış yerde
    if (c >= 'A' && c <= 'Z') return 1;
    else if (c >= 'a' && c <= 'z') return 1;  // Çok fazla satır
    else return 0;
}
```

**Norm checker:** `norminette` aracı var 42'de."

---

### S11: "Edge Case'ler Neler? Hangilerine Dikkat Ettin?"

**Cevap:**

1. **NULL input:** `ft_strlen(NULL)` → Undefined, caller NULL göndermemeli
2. **Empty string:** `ft_split("", ' ')` → empty array (NULL sonunda)
3. **Size 0:** `ft_calloc(0, 10)` → malloc(0) result (platforma bağlı)
4. **Overflow:** `ft_calloc(SIZE_MAX, 2)` → NULL (kontrol yapıldı)
5. **Negative int:** `ft_itoa(INT_MIN)` → "-2147483648" (special case)
6. **Overlap:** `ft_memmove(buf+1, buf, n)` → Güvenli (geriye git)
7. **Full buffer:** `ft_strlcpy(dst, src, 1)` → dst[0] = '\0', return strlen(src)

**Test komut:**
```bash
valgrind --leak-check=full ./test
```
Bu, segfault, invalid read/write, leak'i yakalar."

---

### S12: "Projeyi Yaparken Öğrendiğin En Önemli Şey?"

**Cevap:**
"Bellek yönetiminin zorlukları. Bir kez, `ft_split`'te sadece `result` pointer'ını `free()` ettim ama individual word'ları unuttuğum için memory leak oldu. Valgrind'le `definitely lost 1024 bytes` raporu gördüm. O andan sonra, bellek ayırdığım her yere karşılık `free()` çağrısı yazıyorum. Test-driven approach ve Valgrind, çok yardımcı oldu."

---

## 🎓 Daha Zorlu Sorular

### S13: "Integer Overflow Dışında Başka Güvenlik Riski Var mı?"

**Cevap:**
"Evet, birkaç tane:

1. **Format String:** `ft_putstr_fd` da değil ama printf() ile:
   ```c
   printf(user_input);  // ❌ Format string exploit!
   printf(\"%s\", user_input);  // ✅ Güvenli
   ```

2. **Buffer Overflow:** `strlcpy` olmadan.

3. **Use-after-free:** Serbest alınan belleği oku.

4. **Race Condition:** Multi-threaded olmadığından sorun yok, ama `static` var'lar thread-safe değil.

libft basit olduğu için bu riskler minimal, ama production code'da kritik."

---

### S14: "Recursion vs Loop — Hangisini Tercih Ettin ve Neden?"

**Cevap:**
"libft'deki işlerde loop tercih ettim. Örnekler:

```c
// Loop (ft_strlen)
size_t ft_strlen(const char *s) {
    size_t i = 0;
    while (s[i])
        i++;
    return i;
}

// Recursion (alternatif)
size_t ft_strlen_rec(const char *s) {
    if (!*s) return 0;
    return 1 + ft_strlen_rec(s + 1);
}
```

**Neden loop?**
- Stack overflow riski yok
- Daha hızlı (function call overhead yok)
- Compiler optimization kolay
- 42'nin fonksiyon uzunluğu limiti (25 satır) — recursion satırları arttırır

Recursion sadece doğal recursif problem'lerde (ağaç traversal, quicksort) kullanırım."

---

### S15: "Makefile'ın Değişkenleri (CC, CFLAGS, etc.) Ne İş Yapıyor?"

**Cevap:**
```makefile
NAME = libft.a          # Çıktı dosyası adı
CC = cc                 # Compiler (gcc, clang, cc)
CFLAGS = -Wall -Wextra -Werror  # Compiler bayrakları
AR = ar rcs             # Archiver (statik kütüphane oluşturur)
RM = rm -f              # Remove komutu

SRCS = ft_*.c           # Source dosyaları
OBJS = $(SRCS:.c=.o)    # Object dosyaları (.c → .o)

all: $(NAME)            # Default target
$(NAME): $(OBJS)        # libft.a bağımlılıkları: tüm .o dosyaları
    $(AR) $(NAME) $(OBJS)  # ar rcs libft.a *.o

%.o: %.c                # Pattern rule: .c → .o
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    $(RM) $(OBJS)       # .o dosyaları sil
```

**Komutlar:**
```bash
make            # $(NAME) build et
make clean      # .o sil
make fclean     # .o + libft.a sil
make re         # fclean + all
```"

---

## 🏆 Özgüveni Artıracak Teknik Derinlik

### S16: "Pointer'ların Boyutu Neden 8 Byte (64-bit sistem)?"

**Cevap:**
"64-bit sistemde adres space 2^64 = 18 exabyte. Her adres unique olmalı, yani 64 bit = 8 byte gereklidir. Örneğin:

```c
char *p = malloc(100);
printf(\"%zu\n\", sizeof(p));  // 8 (pointer boyutu)
printf(\"%zu\n\", sizeof(*p));  // 1 (char boyutu)
```

32-bit sistem'de pointer 4 byte'dır (2^32 = 4GB adres space)."

---

### S17: "Type Casting Neden Gerekli (void *)?"

**Cevap:**
"`void *` generic pointer'dır — hangi type olduğu kaybolur:

```c
void *data = malloc(sizeof(int));
// int *ptr = data;  // ❌ Warning: implicit cast
int *ptr = (int *)data;  // ✅ Explicit cast

*ptr = 42;  // Artık int olarak oku
```

Cast gerekli çünkü compiler type bilgisini korumak ister — safety."

---

### S18: "Double Pointer (**) Ne Zaman Kullanılır?"

**Cevap:**
"Çağıran fonksiyonun pointer'ını **değiştirmek** istediğinde:

```c
// ❌ Çalışmaz: lst pointer'ı değişmiyor
void ft_lstadd_front_wrong(t_list *lst, t_list *new) {
    new->next = lst;
    lst = new;  // ❌ Yerel kopya değişir, caller'ın lst değişmiyor
}

// ✅ Doğru: lst pointer'ı değişir
void ft_lstadd_front(t_list **lst, t_list *new) {
    new->next = *lst;
    *lst = new;  // ✅ Gerçek lst değişir
}

// Kullanım:
t_list *head = NULL;
ft_lstadd_front(&head, new_node);  // &head = double pointer
```

**Analoji:** Pointer is like a finger pointing at data. Double pointer is a finger pointing at the finger."

---

## 🔬 Son Sorular — Derinlemesine

### S19: "libft'de Standard Library Kullandın mı? Neleri Avoid Ettin?"

**Cevap:**
"42'nin kuralı: `strlen`, `strcpy`, `strcat`, `memset`, `memcpy` gibi string/mem fonksiyonları yasaklı. Ama:

- ✅ `malloc`, `free` — temel bellek (libft'de yok, caller bulunur)
- ✅ `write()` — dosya descriptor yazma (`ft_putchar_fd` için)
- ✅ `stdlib.h`, `unistd.h` — temel header'lar
- ❌ `string.h` — yasaklı (string fonksiyonları)
- ❌ `stdio.h` — yasaklı (printf/sprintf)

Eğer `printf` kullanırsan derleme başarısız olur."

---

### S20: "Valgrind Raporu — Tüm Green Oldu mu?"

**Cevap:**
"Evet, Valgrind clean:

```
==12345== HEAP SUMMARY:
==12345==     in use at exit: 0 bytes in 0 blocks
==12345==   total heap alloc: 1024 bytes in 50 blocks
==12345==   total heap free:  1024 bytes in 50 blocks
==12345== Leak rate: 0%
==12345== All heap blocks were freed -- no leaks possible.
```

Hiç 'definitely lost' veya 'possibly lost' yok. İnvalid read/write de yok."

---

## 📝 Sunum Sonunda Söylenmesi Gereken

"libft, C'nin temellerini anlaşılması açısından kritik bir proje. Bellek yönetimi, pointer'lar, veri yapıları ve sistem-level API'ler konularını uygulamalı olarak öğretti. Bu projede öğrendiğim pointer mantığı ve bellek yönetimi, ilerideki tüm C/C++ projelerimde kullandığım temel bilgi oldu."

---

## 🎯 Hızlı Kontrol Listesi

Sunum öncesi:

- [ ] Tüm fonksiyonların fonksiyonel olduğunu test ettim (libftTester, etc.)
- [ ] Valgrind leak/invalid read/write yok
- [ ] 42 Norm kurallarına uyuyorum
- [ ] Buffer overflow'dan korundum (strlcpy, memmove)
- [ ] NULL kontrol ve edge case'ler işlendi
- [ ] Makefile doğru compile ediyor (make re, make clean, make fclean)
- [ ] Bellek ownership'i ve free() çağrıları doğru
- [ ] Header guard'ları ve include'lar correct

**Good luck! 🚀**
