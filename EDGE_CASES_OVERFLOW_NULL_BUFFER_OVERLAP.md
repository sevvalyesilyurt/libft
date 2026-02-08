# libft — Edge Cases, Overflow, NULL Handling, Buffer Overrun, Overlapping Memory (Derinlemesine)

## 📌 Giriş: Edge Cases Nedir?

**Edge cases** = Standart/normal işleyişin dışındaki durumlardır. Testlerde genelde atlanır ama production'da crash/sızıntı yaratabilir.

libft'de tipik edge case'ler:
1. **Overflow Kontrolü** — Integer/memory overflow
2. **NULL Pointer** — NULL input/output handling
3. **Buffer Overrun** — Array sınırının aşılması
4. **Overlapping Memory** — Kaynakla hedef overlap
5. **Empty Input** — Boş string, empty list
6. **Boundary Conditions** — n==0, size==1, INT_MIN/MAX

---

## 1. Overflow Kontrolü (Integer & Memory)

### 1.1 Integer Overflow Nedir?

```c
// Example: 32-bit signed int
int x = 2147483647;  // INT_MAX
int y = x + 1;       // ??? 

// Undefined Behaviour!
// Genelde: -2147483648 (wrap-around)
```

**Bellek görüntüsü (32-bit):**
```
INT_MAX =  01111111111111111111111111111111
         + 00000000000000000000000000000001
         = 10000000000000000000000000000000 (overflow!)
         = INT_MIN (sign bit flips)
```

### 1.2 libft'de Overflow — `ft_calloc`

**❌ KÖTÜ:**
```c
void *ft_calloc_bad(size_t count, size_t size) {
    return malloc(count * size);  // count * size overflow olabilir!
}

// Örnek:
// count = 1000000000
// size = 1000000000
// count * size = 1000000000000000000 (1e18)
// Fakat size_t overflow → 0 veya küçük sayı
// → malloc(0) veya malloc(çok-az)
// → Buffer overflow!
```

**✅ DOĞRU:**
```c
void *ft_calloc(size_t count, size_t size) {
    // Overflow kontrolü: count * size > SIZE_MAX ise HATA
    if (count != 0 && size > SIZE_MAX / count)
        return NULL;  // Overflow detected!
    
    void *ptr = malloc(count * size);
    if (!ptr)
        return NULL;
    ft_bzero(ptr, count * size);
    return ptr;
}
```

**Neden `size > SIZE_MAX / count` ?**
- Doğrudan `count * size > SIZE_MAX` yapamayız (overflow oluşur!)
- Bölme ile kontrol: Eğer `size > SIZE_MAX / count`, o zaman `count * size > SIZE_MAX`

**Örnekler:**
```c
// SIZE_MAX = 18446744073709551615 (64-bit)

ft_calloc(1000, 1000);           // ✅ OK: 1000000 bytes
ft_calloc(1000000, 1000000);     // ❌ OVERFLOW DETECTED (return NULL)
ft_calloc(SIZE_MAX, 2);          // ❌ OVERFLOW DETECTED (return NULL)
ft_calloc(0, 1000);              // ✅ OK: count==0 → edge case
ft_calloc(1, SIZE_MAX);          // ✅ OK: size==SIZE_MAX (but malloc fails)
```

### 1.3 Integer Overflow — `ft_atoi`

```c
// ft_atoi("-2147483649");  // INT_MIN - 1

int ft_atoi(const char *nptr) {
    int result = 0;
    int sign = 1;
    
    // ...
    
    // ❌ HATA: result overflow oluşabilir
    while (*nptr >= '0' && *nptr <= '9') {
        result = result * 10 + (*nptr - '0');  // Overflow!
        nptr++;
    }
    return result * sign;
}

// Örneğin:
// result = 214748364, *nptr = '7'
// result * 10 = 2147483640
// + 7 = 2147483647 (OK, INT_MAX)
// Ama sonraki digit varsa?
// result = 2147483647
// result * 10 = -2147483648 (wrap-around, undefined!)
```

**Standart `atoi` behavior:**
- Undefined behaviour (overflow'da)
- Genelde INT_MAX veya INT_MIN döner

**libft'de:** 42'nin kuralı gereği overflow'da "makul" bir sonuç döndür (genelde wrap-around tolerate edilir).

### 1.4 Signed/Unsigned Comparison Overflow

```c
// ❌ TEHLIKE
int signed_val = -5;
size_t unsigned_val = 10;

if (signed_val < unsigned_val) {  // ❌ HATA!
    // -5 signed → 18446744073709551611 unsigned (wrap-around)
    // 18446744073709551611 > 10 → false!
}

// ✅ DOĞRU
if ((size_t)signed_val < unsigned_val) {
    // Explicit cast, intent clear
}

// Veya
if (signed_val >= 0 && (size_t)signed_val < unsigned_val) {
    // Semantic check first
}
```

**libft'de `ft_strncmp`:**
```c
int ft_strncmp(const char *s1, const char *s2, size_t n) {
    // size_t n (unsigned)
    while (n && *s1 == *s2) {
        n--;      // ✅ Safe: n unsigned, n-- loop until n==0
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}
```

---

## 2. NULL Pointer Handling

### 2.1 NULL Kontrol — Zorunlu mu?

**42 Norm'da:** Fonksiyonun behavior'u belirtmez ise, **caller NULL göndermemeli** (implicit contract).

```c
// ❌ HATA: NULL göndermek (caller'ın hatası)
ft_strlen(NULL);  // Undefined!

// ✅ DOĞRU: Caller kontrol eder
if (str != NULL)
    ft_strlen(str);
```

**ANCAK:** Bazı fonksiyonlar **NULL handle etmeli:**
- `ft_lstclear(&list, del)` — NULL list (empty) handle
- `ft_lstiter(list, f)` — NULL list handle
- `ft_lstmap(list, f, del)` — NULL list handle

### 2.2 Örnek: `ft_strlen` (NULL handling yok)

```c
size_t ft_strlen(const char *s) {
    size_t i = 0;
    while (s[i])  // ❌ s==NULL ise segfault!
        i++;
    return i;
}

// Test
ft_strlen("hello");   // ✅ OK, return 5
ft_strlen(NULL);      // ❌ Segfault! Undefined
```

### 2.3 Örnek: `ft_lstclear` (NULL handling gerekli)

```c
void ft_lstclear(t_list **lst, void (*del)(void *)) {
    t_list *current;
    
    if (!lst)         // ✅ NULL pointer'ı pointer kontrol
        return;
    
    while (*lst) {
        current = *lst;
        *lst = (*lst)->next;
        
        if (del)      // ✅ del NULL olabilir
            del(current->content);
        
        free(current);
    }
}

// Test
t_list *list = NULL;
ft_lstclear(&list, free);  // ✅ OK, handles empty list
```

### 2.4 Double Pointer & NULL — `ft_lstadd_front`

```c
void ft_lstadd_front(t_list **lst, t_list *new_node) {
    if (!lst || !new_node)  // ✅ Kontrol
        return;
    
    new_node->next = *lst;
    *lst = new_node;
}

// Usage:
t_list *head = NULL;
ft_lstadd_front(&head, ft_lstnew((void *)malloc(sizeof(int))));
// head artık list'i gösteriyor (NULL'dan non-NULL'a değişti)

// Valgrind
// ✅ No invalid access
```

---

## 3. Buffer Overrun (Array Boundary)

### 3.1 Stack Buffer Overflow

```c
// ❌ HATA: Fixed buffer, unbounded input
void process_string(char *input) {
    char buffer[10];  // 10 byte'lık buffer
    
    int i = 0;
    while (input[i]) {  // ❌ Sınır kontrolü yok!
        buffer[i] = input[i];
        i++;
    }
    buffer[i] = '\0';
    printf("%s\n", buffer);
}

// Eğer input "Hello World" (11 char), stack corrupt olur!
// Segfault, arbitrary code execution (CWE-121)
```

**Memory görüntüsü (overflow):**
```
[RBP/RIP overwrite]  ← Stack corruption!
[Canary (if enabled)] ← Canary check fail!
[buffer[9] overflow] ←─┐
[buffer[0:8]]        ←─┴─ 10 byte
[saved RBP]
[saved RIP]
```

### 3.2 libft'de Safe Buffer — `ft_strlcpy`

```c
// ❌ KÖTÜ (strcpy'ye benzer)
void unsafe_copy(char *dst, const char *src) {
    while (*src) {
        *dst++ = *src++;
    }
    *dst = '\0';  // dst'nin boyutu bilinmiyor!
}

// ✅ DOĞRU (ft_strlcpy)
size_t ft_strlcpy(char *dst, const char *src, size_t size) {
    size_t i = 0;
    
    // Sınır kontrolü: size - 1 (null-terminate için yer bırak)
    while (i < size - 1 && src[i]) {
        dst[i] = src[i];
        i++;
    }
    if (size > 0)
        dst[i] = '\0';  // Null-terminate
    
    // src'nin tam uzunluğunu döner (taşma tespit için)
    while (src[i])
        i++;
    return i;
}

// Test
char buf[5];
size_t len = ft_strlcpy(buf, "Hello World", 5);

// Result:
// buf = "Hell\0" (4 char + null)
// len = 11 (original length, caller "taşma" olmuş bilir)

// Caller kontrol edebilir:
if (len >= 5) {
    fprintf(stderr, "String truncated!\n");
}
```

### 3.3 Heap Buffer Overflow — `ft_split`

```c
// ❌ HATA: Eğer allocate yanlış yapılsa
char **ft_split_bad(char const *s, char c) {
    int count = count_words(s, c);
    char **result = malloc((count + 1) * sizeof(char *));  // +1 for NULL
    
    for (int i = 0; i < count; i++) {
        // ... extract word ...
        result[i] = malloc(word_len + 1);  // ✅ +1 for null
        // ... copy word ...
    }
    result[count] = NULL;  // ✅ NULL-terminate array
    return result;
}

// Eğer count yanlış hesaplanırsa:
// count = 5, ama aslında 10 word var
// result[5] to result[9] yazılırken heap overflow!
```

### 3.4 Haystack Search Overflow — `ft_strnstr`

```c
// ❌ HATA: len kontrol edilmemiş
char *ft_strnstr_bad(const char *big, const char *little, size_t len) {
    while (*big) {
        // ❌ len kontrolü yok! Buffer overrun!
        int cmp = strncmp(big, little, strlen(little));
        if (cmp == 0)
            return (char *)big;
        big++;
    }
    return NULL;
}

// ✅ DOĞRU
char *ft_strnstr(const char *big, const char *little, size_t len) {
    size_t little_len;
    
    if (!*little)
        return (char *)big;
    
    little_len = strlen(little);
    
    while (*big && len >= little_len) {  // ✅ len kontrolü
        if (strncmp(big, little, little_len) == 0)
            return (char *)big;
        big++;
        len--;
    }
    return NULL;
}
```

---

## 4. Overlapping Memory (src == dst)

### 4.1 Overlap Nedir?

```
Destination === Source (aynı bellek bölgesi)

buf:  [A][B][C][D][E]
      ↑
      p (dst)
           ↑
           p + 2 (src)
```

### 4.2 `ft_memcpy` vs `ft_memmove`

**❌ ft_memcpy (overlap'da undefined):**
```c
void *ft_memcpy(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dest;
    unsigned char *s = (unsigned char *)src;
    
    while (n--)
        *d++ = *s++;  // Öne doğru, overlap'e duyarsız!
    
    return dest;
}

// Örnek — buffer.c'nin başına kopyala
char buf[10] = "ABCDE";
ft_memcpy(buf + 1, buf, 4);

// Adım adım (KÖTÜ):
// 1. buf[1] = buf[0] = 'A' → buf = "AACDE"
// 2. buf[2] = buf[1] = 'A' → buf = "AACDE"  (değişmiş!)
// 3. buf[3] = buf[2] = 'C' → buf = "AACDE"  (yanlış!)
// 4. buf[4] = buf[3] = 'D' → buf = "AACDD"  (yanlış!)

// Sonuç: "AACDD" (beklenen: "AABCD")
```

**✅ ft_memmove (overlap'te safe):**
```c
void *ft_memmove(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dest;
    unsigned char *s = (unsigned char *)src;
    
    if (d < s) {
        // Öne doğru (overlap yok)
        while (n--)
            *d++ = *s++;
    } else {
        // Geriye doğru (overlap safe!)
        while (n--)
            *(d + n) = *(s + n);
    }
    
    return dest;
}

// Örnek — buffer'ın başına kopyala
char buf[10] = "ABCDE";
ft_memmove(buf + 1, buf, 4);

// d > s, o yüzden geriye doğru:
// 1. buf[4] = buf[0] = 'A' → buf = "ABCDA"
// 2. buf[3] = buf[-1] wait... buf[-1] = 'E'? Hayır!
//    Doğrusu: *(d + 3) = *(s + 3) = buf[3] = 'D'
//    → buf[4] = buf[3] = 'D' (wait, buf[3] was 'D')
//
// Aslında: d = buf+1, s = buf
// while (n--):  n=3,2,1,0
//   n=3: *(buf+1+3) = *(buf+3) → buf[4] = buf[3] = 'D'
//   n=2: *(buf+1+2) = *(buf+2) → buf[3] = buf[2] = 'C'
//   n=1: *(buf+1+1) = *(buf+1) → buf[2] = buf[1] = 'B'
//   n=0: *(buf+1+0) = *(buf+0) → buf[1] = buf[0] = 'A'
//
// Sonuç: buf = "AABCD" ✅ DOĞRU!
```

### 4.3 Overlap Tespit — Valgrind

```bash
# Valgrind memcpy overlap'i detect eder:
valgrind --tool=memcheck ./test

# Output:
# ==12345== Source and destination overlap in memcpy(0x..., 0x..., ...)
```

---

## 5. Empty & Boundary Cases

### 5.1 Empty String (`""`)

```c
// ft_strlen("")
size_t len = ft_strlen("");  // ✅ OK, return 0 (not 1)

// ft_split("", ' ')
char **arr = ft_split("", ' ');
// Expected: {"", NULL} or just {NULL} (implementation-dependent)

// ft_strjoin("hello", "")
char *result = ft_strjoin("hello", "");  // ✅ "hello"

// ft_strtrim("", "")
char *result = ft_strtrim("", "");  // ✅ "" (empty)
```

### 5.2 Empty List (NULL)

```c
// ft_lstsize(NULL)
int size = ft_lstsize(NULL);  // ✅ OK, return 0

// ft_lstiter(NULL, f)
void dummy_f(void *p) {}
ft_lstiter(NULL, dummy_f);  // ✅ OK, do nothing

// ft_lstclear(&list, del) where list==NULL
t_list *list = NULL;
ft_lstclear(&list, free);  // ✅ OK
```

### 5.3 Size == 0

```c
// ft_calloc(0, 100)
void *p = ft_calloc(0, 100);  // malloc(0) behavior (platform-dependent)

// ft_substr(s, 0, 0)
char *sub = ft_substr("hello", 0, 0);  // ✅ "" (empty substring)

// ft_strlcpy(dst, src, 0)
char dst[10] = "";
ft_strlcpy(dst, "hello", 0);
// ✅ Nothing copied (size-1 = -1, while loop doesn't run)
// Returns strlen("hello") = 5
```

### 5.4 INT_MIN / INT_MAX

```c
// ft_atoi with boundaries
ft_atoi("2147483647");   // INT_MAX ✅ OK
ft_atoi("-2147483648");  // INT_MIN ✅ OK (probably)
ft_atoi("2147483648");   // INT_MAX + 1 → Overflow! (undefined)

// ft_itoa with boundaries
char *s = ft_itoa(INT_MAX);      // "2147483647" ✅
char *s = ft_itoa(INT_MIN);      // "-2147483648" ✅ (tricky!)
```

---

## 6. Memory Leak Detection — Valgrind

### 6.1 Valgrind İnstallation & Usage

```bash
# Linux'ta install
sudo apt install valgrind

# Basit kullanım
valgrind ./program

# Detailed output
valgrind --leak-check=full --show-leak-kinds=all ./program

# Suppress false positives
valgrind --suppressions=/usr/lib/valgrind/default.supp ./program

# Track origin of uninitialized values
valgrind --track-origins=yes ./program
```

### 6.2 Valgrind Raporu — Anlamak

```
==12345== HEAP SUMMARY:
==12345==     in use at exit: 64 bytes in 3 blocks
==12345==   total heap alloc: 1024 bytes in 50 blocks
==12345==   total heap free:  960 bytes in 47 blocks
==12345==   total heap alloc: 1024 in 50 blocks
==12345== Leak_rate: 6% (64 bytes in 3 blocks)
```

**Leak Types:**
- `definitely lost` = Certainly a leak (must fix)
- `indirectly lost` = Lost due to "definitely lost" parent
- `possibly lost` = Might be a leak (check manually)
- `still reachable` = Allocated but not freed (minor, often ignored)

### 6.3 Örnek Test — `ft_split` Leak

```c
#include "libft.h"
#include <stdio.h>

int main(void) {
    char **arr = ft_split("one,two,three", ',');
    
    // ❌ HATA: Leak!
    // arr, arr[0], arr[1], arr[2] serbest bırakılmamış
    
    // ✅ DOĞRU:
    int i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
    
    return 0;
}
```

**Valgrind Çıktısı:**
```bash
$ valgrind --leak-check=full ./test

==12345== LEAK SUMMARY:
==12345==    definitely lost: 27 bytes in 3 blocks
==12345==    indirectly lost: 0 bytes in 0 blocks
==12345==      possibly lost: 0 bytes in 0 blocks
==12345==    still reachable: 0 bytes in 0 blocks
==12345==         suppressed: 0 bytes in 0 blocks
```

### 6.4 Invalid Read/Write Detection

```bash
# Valgrind detect eder:
# - Invalid read (segfault riski)
# - Invalid write (buffer overflow)
# - Use-after-free
# - Double-free

$ valgrind ./test

==12345== Invalid write of size 4
==12345==    at 0x...: main (test.c:15)
==12345==  Address 0x... is 0 bytes inside a block of size 10 alloc'd
==12345==    at 0x...: malloc (...)
==12345==    by 0x...: main (test.c:10)
```

---

## 7. AddressSanitizer — GCC/Clang

### 7.1 Compile with ASan

```bash
gcc -Wall -Wextra -Werror -fsanitize=address -g test.c libft.a -o test
./test

# Output (if error):
# =================================================================
# ==12345==ERROR: AddressSanitizer: heap-buffer-overflow on unknown address
# ==12345==The signal is caused by a WRITE memory access.
# ==12345==Hint address points into the middle of an allocated block
```

### 7.2 ASan vs Valgrind

| Fitur | Valgrind | ASan |
|-------|----------|------|
| **Speed** | Slow (10x) | Fast (2x) |
| **Overhead** | Runtime | Compile-time |
| **Memory leak** | ✅ Full detection | ❌ Limited |
| **Use-after-free** | ✅ Yes | ✅ Yes |
| **Buffer overflow** | ✅ Yes | ✅ Yes |
| **Uninitialized vars** | ✅ With --track-origins | ❌ No |

**libft'de:** İkisini de kullan:
- `Valgrind`: Leak'ler için (bellek ownership)
- `ASan`: Buffer overflow'lar için (hız)

### 7.3 Örnek — Buffer Overflow ASan ile

```c
void test_overflow(void) {
    char buf[5];
    ft_strlcpy(buf, "Hello World", 5);  // Safe!
    
    char buf2[5];
    strcpy(buf2, "Hello World");        // ❌ Overflow!
}

$ gcc -fsanitize=address test.c -o test
$ ./test

=================================================================
==12345==ERROR: AddressSanitizer: stack-buffer-overflow on address
0x7fff at pc 0x0000004c6b5e bp 0x7fff sp 0x7fff T=0
WRITE of size 12 at 0x7fff thread T0
    #0 0x4c6b5d in strcpy (test.c:10)
    #1 0x4c6b99 in test_overflow (test.c:10)
    #2 0x7f... in main (test.c:15)

Address 0x7fff is located in stack of thread at offset 32 in frame
    test_overflow (test.c:7)
```

---

## 8. Common Edge Cases Checklist

### String Fonksiyonları

- [ ] Empty string `""`
- [ ] Single char `"a"`
- [ ] NULL-terminated kontrolü
- [ ] Very long string
- [ ] Whitespace only `"   "`
- [ ] Special chars `"\0\n\t"`

### Memory Fonksiyonları

- [ ] `size == 0`
- [ ] Overflow `count * size > SIZE_MAX`
- [ ] Overlapping `memcpy` vs `memmove`
- [ ] Very large allocation (malloc fail)
- [ ] Double-free prevention

### Liste Fonksiyonları

- [ ] NULL list (empty)
- [ ] Single node list
- [ ] Very large list (recursion depth)
- [ ] Function pointer NULL
- [ ] Destructor NULL (ft_lstclear)

### Int Conversion

- [ ] INT_MIN / INT_MAX
- [ ] Negative numbers
- [ ] Leading whitespace
- [ ] Non-digit chars (stop parsing)
- [ ] Overflow (wrap-around)

---

## 9. Test Script Örneği

```c
#include "libft.h"
#include <stdio.h>
#include <string.h>

void test_edge_cases(void) {
    // Test 1: ft_strlen
    printf("Test ft_strlen:\n");
    printf("Empty: %zu\n", ft_strlen(""));          // 0
    printf("NULL: ");
    // printf("%zu\n", ft_strlen(NULL));  // ❌ Segfault (skip)
    
    // Test 2: ft_strlcpy with boundaries
    printf("\nTest ft_strlcpy:\n");
    char buf[5] = {};
    size_t len = ft_strlcpy(buf, "Hello World", 5);
    printf("buf: %s, len: %zu\n", buf, len);       // "Hell", 11
    
    // Test 3: ft_split with empty
    printf("\nTest ft_split:\n");
    char **arr = ft_split("", ' ');
    printf("Empty split: %s\n", arr[0] ? arr[0] : "NULL");
    
    // Test 4: ft_calloc overflow
    printf("\nTest ft_calloc:\n");
    void *p = ft_calloc(SIZE_MAX, 2);
    printf("Overflow: %p\n", p);                    // NULL
    
    // Test 5: ft_memmove overlap
    printf("\nTest ft_memmove:\n");
    char buf2[10] = "ABCDE";
    ft_memmove(buf2 + 1, buf2, 4);
    printf("After memmove: %s\n", buf2);            // "AABCD"
}

int main(void) {
    test_edge_cases();
    return 0;
}
```

**Compile & Run:**
```bash
gcc -Wall -Wextra -Werror -fsanitize=address test.c libft.a -o test
./test

# Or with Valgrind
gcc -Wall -Wextra -Werror -g test.c libft.a -o test
valgrind --leak-check=full ./test
```

---

## 10. Sunum Sırasında Söylenecek Kısa Cümleler

**Overflow Kontrolü:**
"ft_calloc'da `count * size` overflow'ı kontrol ettim — doğrudan çarpma yapmak yerine `size > SIZE_MAX / count` ile kontrol ederim. Bu, integer overflow security vulnerability'sini engeller."

**NULL Handling:**
"42'nin kuralı, fonksiyon NULL tolerate etmeyebilir, caller NULL göndermez. Ama liste fonksiyonları (`ft_lstclear`, `ft_lstiter`) NULL list'i (empty) handle etmeli — bunu explicit'e yaptım."

**Buffer Overflow:**
"ft_strlcpy, strcpy'nin aksine size limit'i alır. Null-terminate'i guarantee eder ve orijinal string uzunluğunu döner — caller taşma olup olmadığını kontrol edebilir."

**Overlapping Memory:**
"ft_memmove, ft_memcpy'den farklı olarak overlap'te safe'dir — destination > source ise geriye doğru kopyalar. Aynı buffer'dan copy'lemek isteyen code'lar için kritiktir."

**Edge Case Testing:**
"Empty string, INT_MIN/MAX, NULL, size==0 gibi edge case'leri test ettim. Valgrind ile bellek sızıntısı, AddressSanitizer ile buffer overflow'ları buldum."

---

## 11. Kontrol Listesi — Yeni Fonksiyon Yazarken

- [ ] NULL input kontrolü (gerekli ise)
- [ ] Integer overflow (special size case'leri)
- [ ] Buffer boundary kontrol (strlcpy pattern kullan)
- [ ] Overlapping memory (memmove pattern)
- [ ] Edge case: empty, size==0, INT_MIN/MAX
- [ ] Memory leak (malloc fail → cleanup)
- [ ] Valgrind clean (`valgrind --leak-check=full`)
- [ ] ASan clean (`-fsanitize=address`)
- [ ] Return value correct (length, pointer, status)

---

Hangi edge case hakkında daha derinlemesine öğrenmek istiyorsun? Pratik bir soru sormaktan çekinme! 🚀
