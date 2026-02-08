# libft — Tip Sistemi & Veri Yapıları (Derinlemesine)

## 📌 Giriş: Neden Bu Konular Önemli?

42 evosunda **Tip Sistemi** ve **Veri Yapıları** hakkında sorular sorulması çok olasıdır çünkü:
1. libft'nin kalbi pointer'lar ve type casting'dir
2. `void *` generic programming'in temeli
3. Bağlı liste (`t_list`) veri yapısı yaygın bir interview konusu
4. Memory layout'ı anlamak, pointer arithmetic ve struct padding'i anlamamızı sağlar

---

## 1. C'deki Temel Tipler

### 1.1 Integer Tipler

```c
char      // 1 byte   (-128 to 127 | 0 to 255 unsigned)
short     // 2 bytes  (-32768 to 32767)
int       // 4 bytes  (-2147483648 to 2147483647)
long      // 8 bytes  (-9223372036854775808 to ...)
```

**Neden birden fazla integer tipi?**
- **Bellek verimliliği:** Küçük sayılar için char, büyük sayılar için long
- **Hız:** İşlemci, native size'da (genelde int) daha hızlı
- **Standart:** POSIX ve C89/C99 belirli boyutları tanımlar

**Örnek — Bellek Tasarrufu:**
```c
// Verimsiz (12 bytes)
struct person_bad {
    int age;        // 4 bytes
    char grade;     // 1 byte
    int score;      // 4 bytes
    char active;    // 1 byte
};

// Verimli (reorder ile padding azaltılır — 9 bytes)
struct person_good {
    int age;        // 4 bytes
    int score;      // 4 bytes
    char grade;     // 1 byte
    char active;    // 1 byte
};
```

### 1.2 Floating Point Tipler

```c
float       // 4 bytes  (6-7 significant digits)
double      // 8 bytes  (15-16 significant digits)
```

**libft'de kullanılır mı?** Nadiren. String/int dönüşüm var ama float dönüşüm yok.

### 1.3 Void Tipi

```c
void        // "Hiçbir şey" tipi — dönüş değeri yok
void *      // Generic pointer — herhangi bir veriyi işaret eder
```

**void * Neden?**
```c
// ❌ Type-specific
int *int_array = malloc(100 * sizeof(int));
char *char_array = malloc(100 * sizeof(char));
float *float_array = malloc(100 * sizeof(float));

// ✅ Generic — tek fonksiyon
void *ft_calloc(size_t count, size_t size) {
    return malloc(count * size);  // Herhangi bir tip için
}

// Kullanan:
int *ints = (int *)ft_calloc(10, sizeof(int));
char *chars = (char *)ft_calloc(10, sizeof(char));
```

---

## 2. Pointer'lar (İşaretçiler)

### 2.1 Pointer Nedir?

**Pointer = Bellek Adresi**

```c
int x = 42;          // x'in değeri: 42
int *p = &x;         // p'nin değeri: x'in adresi (0x7fff5fbff8fc gibi)

printf("%d\n", x);   // 42
printf("%p\n", p);   // 0x7fff5fbff8fc (adres)
printf("%d\n", *p);  // 42 (dereference — adrese git, değeri oku)
```

**Bellek görüntüsü:**
```
Address     | Value
0x7fff5fbff8f8 | ??
0x7fff5fbff8fc | 42    ← x
0x7fff5fbff900 | 0x7fff5fbff8fc  ← p (x'in adresi)
```

### 2.2 Pointer Arithmetic

```c
int arr[5] = {10, 20, 30, 40, 50};
int *p = arr;  // arr[0]'u göster

p++;        // p = p + 1 * sizeof(int) = p + 4 (1 array element ileri)
*p;         // arr[1] = 20

p += 2;     // p = p + 2 * sizeof(int) = p + 8
*p;         // arr[3] = 40

// ❌ HATA: Char pointer ile
char *cp = (char *)arr;
cp++;       // cp = cp + 1 (1 byte ileri!)
*cp;        // arr[0]'nun 2. byte'ı (undefined!)
```

**libft'de örnek — `ft_strnstr`:**
```c
char *ft_strnstr(const char *big, const char *little, size_t len)
{
    while (*big && len-- > 0) {
        if (*big == *little) {
            return ((char *)big);  // ✅ Pointer arithmetic
        }
        big++;  // Bir adım ileri
    }
    return NULL;
}
```

### 2.3 Pointer vs Value

```c
// ❌ YANLIŞ: pointer'ı değil, değeri değiştir
void change_wrong(int x) {
    x = 100;  // Yerel kopya değişir, caller'ın x değişmiyor
}

int main() {
    int x = 5;
    change_wrong(x);
    printf("%d\n", x);  // 5 (değişmedi!)
}

// ✅ DOĞRU: pointer'ı gönder
void change_right(int *x) {
    *x = 100;  // Gerçek bellek konumunu değiştir
}

int main() {
    int x = 5;
    change_right(&x);
    printf("%d\n", x);  // 100 (değişti!)
}
```

---

## 3. Struct (Yapı)

### 3.1 Struct Nedir?

**Struct = Birden fazla veriyi bir arada tutmak**

```c
// Kütüphanesiz
char name[50];
int age;
float height;
// ... karmaşık, hata yapmaya açık

// Struct ile
struct student {
    char name[50];
    int age;
    float height;
};

struct student s;
s.name = "Ali";   // Daha okunabilir
s.age = 20;
s.height = 1.75;
```

### 3.2 Struct Memory Layout

```c
struct example {
    char a;      // 1 byte
    int b;       // 4 bytes
    char c;      // 1 byte
};

printf("%zu\n", sizeof(struct example));  // 12 (not 6!)
```

**Neden 12? Padding (İç Boşluklar):**

```
Offset  | Content
0       | a (1 byte) + PADDING (3 bytes) ← alignment
4       | b (4 bytes)
8       | c (1 byte) + PADDING (3 bytes) ← struct'ın sonunu align et
12      | (TOPLAM)
```

**Compiler, her field'i belirli byte sınırına align eder** (genelde 4 veya 8):
- `char` = 1 byte alignment
- `int` = 4 byte alignment
- `double` = 8 byte alignment

### 3.3 Struct Pointer

```c
struct student s;
struct student *p = &s;  // Struct'a pointer

// İki yol:
s.age = 20;      // Direct
(*p).age = 20;   // Via pointer (parantez önemli!)
p->age = 20;     // Kısa yazım (arrow operator)
```

**libft'de:** `t_list` kullanılırken:
```c
t_list *node = malloc(sizeof(t_list));
node->content = data;      // ✅ Arrow kullan
(*node).content = data;    // ❌ Çalışır ama kafa karıştırıcı
```

---

## 4. Typedef (Tür Takma Adı)

### 4.1 Neden Typedef?

```c
// ❌ Uzun ve tekrarlı
struct person p1;
struct person p2;
struct person *ptr;

// ✅ Typedef ile kısa
typedef struct person t_person;
t_person p1;
t_person p2;
t_person *ptr;
```

### 4.2 Typedef Struct Syntax

```c
// Yol 1 (ayrı yazım)
struct s_person {
    char name[50];
    int age;
};
typedef struct s_person t_person;

// Yol 2 (bir arada)
typedef struct s_person {
    char name[50];
    int age;
} t_person;

// Yol 3 (isimsiz struct — tavsiye edilmez)
typedef struct {
    char name[50];
    int age;
} t_person;
```

**42 Norm'a göre:** Yol 2 tercih edilir (struct adı `s_` ile başlar, typedef adı `t_` ile başlar).

```c
typedef struct s_list {
    void *content;
    struct s_list *next;
} t_list;
```

---

## 5. libft'nin Kalbi: `t_list` Veri Yapısı

### 5.1 Tanım & Memori Layout

```c
typedef struct s_list {
    void *content;          // Veri pointer'ı
    struct s_list *next;    // Sonraki node
} t_list;
```

**Bellek görüntüsü (64-bit sistem):**
```
t_list node1:
Offset  | Content
0-7     | content (void * = 8 bytes)
8-15    | next (struct s_list * = 8 bytes)
16      | (TOPLAM = 16 bytes)
```

### 5.2 Linked List Visualisasi

```
head → [data1|next] → [data2|next] → [data3|NULL]
       (node1)        (node2)        (node3)
```

**Kod:**
```c
t_list *head = ft_lstnew((void *)malloc(sizeof(int)));
*(int *)head->content = 10;

t_list *node2 = ft_lstnew((void *)malloc(sizeof(int)));
*(int *)node2->content = 20;
head->next = node2;

t_list *node3 = ft_lstnew((void *)malloc(sizeof(int)));
*(int *)node3->content = 30;
node2->next = node3;
node3->next = NULL;
```

### 5.3 Neden `void *`?

```c
// ❌ Specific type — sadece int için
struct int_list {
    int content;
    struct int_list *next;
};

// ❌ Specific type — sadece char* için
struct string_list {
    char *content;
    struct string_list *next;
};

// ✅ Generic — herhangi bir tip
struct s_list {
    void *content;        // int, char*, struct, etc.
    struct s_list *next;
};

// Kullanan:
int *data = malloc(sizeof(int));
*data = 42;
t_list *node = ft_lstnew((void *)data);

char *str = malloc(20);
strcpy(str, "hello");
t_list *node2 = ft_lstnew((void *)str);

struct person p;
t_list *node3 = ft_lstnew((void *)&p);
```

### 5.4 Type Casting `void *`

```c
void *ptr = malloc(sizeof(int));
*(int *)ptr = 42;  // Cast, sonra dereference

// Vs

int *ptr = malloc(sizeof(int));
*ptr = 42;  // Cast'e gerek yok
```

**Karşılaştırma:**
```c
// Safe yolu (explicit cast):
int value = 100;
void *generic = (void *)&value;
int *restored = (int *)generic;
printf("%d\n", *restored);  // 100

// Implicit cast (genelde warning):
int *specific = &value;
void *generic = specific;      // ✅ OK (implicit)
int *restored = generic;       // ❌ Warning! (-Wall ile uyarı)
int *restored = (int *)generic; // ✅ OK (explicit)
```

---

## 6. Function Pointer (Fonksiyon İşaretçisi)

### 6.1 Nedir & Syntax

```c
// Standart fonksiyon
int add(int a, int b) {
    return a + b;
}

// Fonksiyon pointer'ı
int (*func_ptr)(int, int);  // Pointer to function(int,int) → int

// Assign
func_ptr = add;  // Fonksiyonu pointer'a ata
func_ptr = &add; // Alternatif (& optional)

// Call
int result = func_ptr(5, 3);      // 8
int result = (*func_ptr)(5, 3);   // Aynı (alternatif syntax)
```

### 6.2 libft'de Kullanım — Callback

```c
// ft_strmapi: Her karaktere fonksiyon uygula
char *ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
    // ...
    for (unsigned int i = 0; s[i]; i++) {
        result[i] = f(i, s[i]);  // f fonksiyonunu çağır
    }
    return result;
}

// Kullanan:
char to_upper_with_index(unsigned int idx, char c) {
    if (idx % 2 == 0)  // Çift indexler uppercase
        return (c >= 'a' && c <= 'z') ? c - 32 : c;
    return c;
}

char *modified = ft_strmapi("hello", to_upper_with_index);
// "HeLLo"
```

### 6.3 Function Pointer Array (Callback Array)

```c
typedef int (*operation)(int, int);

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }

operation ops[3] = {add, sub, mul};

int result = ops[0](10, 5);  // add(10, 5) = 15
int result = ops[1](10, 5);  // sub(10, 5) = 5
int result = ops[2](10, 5);  // mul(10, 5) = 50
```

---

## 7. Union vs Struct (Kıyaslama)

### 7.1 Fark

```c
struct mixed {
    int a;      // 4 bytes
    char b;     // 1 byte
};
printf("%zu\n", sizeof(struct mixed));  // 8 (padding ile)

union mixed_union {
    int a;      // 4 bytes
    char b;     // 1 byte
};
printf("%zu\n", sizeof(union mixed_union));  // 4 (largest member)
```

**Visualisasi:**

Struct:
```
Offset  | Content
0-3     | int a
4       | char b
5-7     | padding
```

Union:
```
Offset  | Content
0-3     | int a (shared!)
0       | char b (same location!)
```

**Union'da:** `a` ve `b` **aynı bellek konumunu paylaşır**. Biri değişince diğeri de etkilenir.

```c
union mixed_union u;
u.a = 0x12345678;
printf("%d\n", u.b);  // Belki 0x78 (platform-dependent)
```

**libft'de union kullanılır mı?** Hayır. Struct tercih edilir.

---

## 8. Size_t Tipi

### 8.1 Nedir?

```c
size_t      // unsigned integer, malloc/strlen için
```

**Neden unsigned?**
- Boyutlar negatif olamaz
- Daha geniş aralık (0 to 2^64 yerine -2^63 to 2^63-1)

**Örnek:**
```c
size_t len = strlen("hello");    // 5 (unsigned)
int len_bad = strlen("hello");   // ✅ Works, but implicit cast

// Karşılaştırma
int x = -5;
size_t y = 10;
if (x < y)  // ❌ HATA! x -5 signed, y 10 unsigned
            // Signed -5 → unsigned 18446744073709551611 (wrap-around)
            // So: 18446744073709551611 > 10 → false!

// Doğru:
if ((size_t)x < y) { ... }
```

### 8.2 libft'de Kullanım

```c
size_t ft_strlen(const char *s);           // Dönüş: size_t
size_t ft_strlcpy(char *dst, const char *src, size_t size);
void *ft_calloc(size_t nmemb, size_t size);
int ft_memcmp(const void *s1, const void *s2, size_t n);
```

---

## 9. Const Qualifier

### 9.1 Const Nedir?

```c
const int x = 5;
x = 10;  // ❌ HATA! x const, değiştirilemez

const char *str = "hello";
str[0] = 'H';  // ❌ HATA! String const
str = "world";  // ✅ OK (str pointer değişir, content değil)

char * const ptr = malloc(10);
ptr[0] = 'a';  // ✅ OK (content değişir)
ptr = malloc(10);  // ❌ HATA! ptr const
```

### 9.2 libft'de Const Kullanımı

```c
// ❌ Fonksiyon içinde parameter'ı değiştiremezsin
size_t ft_strlen(const char *s) {
    s[0] = 'X';  // ❌ HATA!
}

// ✅ Doğru — parameter'ı oku ama değiştirme
size_t ft_strlen(const char *s) {
    size_t i = 0;
    while (s[i])  // ✅ Oku
        i++;
    return i;
}

// Caller const olmayan string gönderebilir
char buf[10] = "hello";
ft_strlen(buf);  // ✅ OK (const param, non-const arg)

// Veya const string
ft_strlen("hello");  // ✅ OK
```

---

## 10. Memory Address & Alignment

### 10.1 Bellek Adresi

```c
int x = 42;
char *c = (char *)&x;  // &x: x'in adresi

printf("%p\n", (void *)&x);  // 0x7fff5fbff8fc (örnek)
printf("%p\n", (void *)c);    // 0x7fff5fbff8fc (aynı)
printf("%p\n", (void *)(c+1)); // 0x7fff5fbff8fd (1 byte ileri)
```

### 10.2 Alignment (Hizalama)

```c
char a;           // 0x1000
int b;            // 0x1004 (not 0x1001!) — 4-byte aligned
char c;           // 0x1008
double d;         // 0x1010 — 8-byte aligned
```

Compiler, CPU efficient hale getrmek için fields'i hizalar. Padding ekler.

---

## 11. Typedef Enum (Enumeration)

### 11.1 Enum Nedir?

```c
enum color { RED, GREEN, BLUE };
enum color my_color = RED;

printf("%d\n", RED);    // 0
printf("%d\n", GREEN);  // 1
printf("%d\n", BLUE);   // 2
```

### 11.2 Typedef ile

```c
typedef enum s_color {
    RED = 0,
    GREEN = 1,
    BLUE = 2,
} t_color;

t_color c = RED;
printf("%d\n", c);  // 0
```

**libft'de enum kullanılır mı?** Nadiren (bonus kısımda custom veri yapıları için kullanılabilir).

---

## 12. Sunum Sırasında Söylenecek Kısa Cümleler

### "Tip Sistemi Hakkında"
**"C'de tipler bellek boyutunu ve interpretasyonu belirler. `char` 1 byte, `int` 4 byte, `long` 8 byte. Pointer'lar her tipin size'ına göre aritmetik yapar — `int *p` ile `p++` yapmak 4 byte ilerletir."**

### "Void Pointer Hakkında"
**"libft'nin bağlı listesinde `void *` kullanılıyor çünkü generic'tir. Herhangi bir veriyi tutabilir — int, string, struct, hatta başka bir pointer. Ama dereference etmek istediğinde type cast gerekli — `(int *)content`."**

### "Struct Memory Layout Hakkında"
**"Struct belleğe yerleştirilirken compiler padding ekler — alignment için. `char + int + char` teoride 6 byte ama genelde 12 byte olur. Struct'ın boyutu `sizeof()` ile ölçülür."**

### "Const Hakkında"
**"Const parameter aldığında, fonksiyon içinden değiştiremezsin. libft'deki `ft_strlen(const char *s)` string'i okur ama değiştirmez. Bu, caller'ın constantlık garantisini veriyor."**

### "Function Pointer Hakkında"
**"libft'deki `ft_strmapi`, `ft_lstmap`, `ft_lstiter` gibi fonksiyonlar function pointer callback alır. Bu, aynı fonksiyonu farklı operasyonlar için tekrar kullanabilmek demek — DRY (Don't Repeat Yourself)."**

---

## 13. Pratik Alıştırmalar

### Alıştırma 1: Struct Memory

```c
struct test {
    char a;
    int b;
    char c;
    double d;
};

printf("%zu\n", sizeof(struct test));  // Kaç byte?
// Cevap: 24 (8-byte double için alignment)
```

### Alıştırma 2: Pointer Arithmetic

```c
int arr[3] = {10, 20, 30};
int *p = arr;

p++;
printf("%d\n", *p);  // Kaç?
// Cevap: 20
```

### Alıştırma 3: Const

```c
const int *p1;   // p1 değişebilir, *p1 sabittir
int * const p2;  // p2 sabittir, *p2 değişebilir

Hangisi nedir?
```

### Alıştırma 4: Void Pointer

```c
void *data = malloc(sizeof(int) * 10);
int *arr = (int *)data;
arr[0] = 42;

Neden cast gerekli?
// Cevap: void * dereference edilemiyor, tip bilgisi yok
```

---

## 14. Özet Tablosu

| Konsept | Kullanım | libft'de |
|---------|----------|----------|
| **char** | 1 byte, karakter | Evet (`ft_tolower`, etc.) |
| **int** | 4 bytes, sayı | Evet (`ft_atoi`, `ft_itoa`) |
| **size_t** | unsigned, boyut | Evet (`ft_strlen`, `ft_calloc`) |
| **Pointer *** | Adres tutma | Evet (tüm yerde) |
| **Void *** | Generic pointer | Evet (`t_list->content`) |
| **Struct** | Veri grubu | Evet (`t_list`) |
| **Typedef** | Tür takma adı | Evet (`t_list`, `t_color`) |
| **Const** | Değiştirilmez | Evet (param'ler) |
| **Function Pointer** | Callback | Evet (`ft_strmapi`, `ft_lstmap`) |
| **Union** | Shared memory | Nadiren |
| **Enum** | Sabitler | Nadiren |

---

## 🎯 Kontrol Listesi — Anladığın Konular

- [ ] **Temel tipler:** char, int, size_t, float
- [ ] **Pointer'lar:** `&`, `*`, pointer arithmetic
- [ ] **Struct:** Tanım, bellek layout, alignment, padding
- [ ] **Typedef:** Kısa yazım, 42 Norm (s_, t_)
- [ ] **t_list:** Bağlı liste, void *, next
- [ ] **Type casting:** Explicit cast, implicit cast
- [ ] **Const:** Parameter const, pointer const
- [ ] **Function pointer:** Callback, ft_strmapi örneği
- [ ] **Size_t:** Unsigned, bellek boyutu, karşılaştırma

---

## 🤔 Sorular Sormaktan Çekinme

Merak ettiğin herhangi bir konu hakkında sorularını cevaplamaya hazırım:
- Pointer arithmetic'in derinlemesine örnekleri?
- Struct padding'i optimize etme?
- Const correctness en iyi practices?
- Memory alignment'ın hardware'de etkisi?
- Generic programming (void *) security'si?

**Devam etmek istediğin bir topic var mı?**
