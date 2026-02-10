*Bu proje sevyesil tarafından 42 müfredatının bir parçası olarak oluşturulmuştur.*

# Libft

## Açıklama

Libft, 42 müfredat kapsamında geliştirilen bir C kütüphanesidir.
Bu projenin temel amacı, C dilinde standart kütüphane
fonksiyonlarının nasıl çalıştığını derinlemesine anlamak ve
bu fonksiyonları sıfırdan implemente etmektir.

Proje süresince bellek yönetimi, pointer kullanımı, string
işlemleri ve temel veri yapıları üzerine yoğunlaşılmıştır.
Özellikle dinamik bellek tahsisi, bellek güvenliği ve
modüler fonksiyon yazımı konularında yetkinlik kazanılması
hedeflenmiştir.

**Projenin Hedefleri**

- C dilinin temel yapı taşlarını kavramak,
- Bellek sızıntılarını önleyen güvenli kod yazma alışkanlığı edinmek,
- Yeniden kullanılabilir ve sürdürülebilir bir kütüphane oluşturmak,
- Linked list gibi temel veri yapılarının çalışma mantığını öğrenmek
amaçlanmıştır.

Ortaya çıkan `libft.a` kütüphanesi, ilerleyen 42 projelerinde
yardımcı bir temel kütüphane olarak kullanılmak üzere
tasarlanmıştır.

---

## Talimatlar

- Projeyi derlemek için:

```bash
make
```

- Oluşturulan obje dosyalarını silmek için:

```bash
make clean
```

- Arşiv ve obje dosyalarını silmek için:

```bash
make fclean
```

- Kütüphaneyi temizleyip yeniden derlemek için:

```bash
make re
```

Derleme sonucunda `libft.a` adlı statik kütüphane oluşturulur.

---

## Kullanım

Oluşturulan kütüphaneyi kendi projenizde kullanmak için
`libft.h` dosyasını projenize dahil etmeniz yeterlidir.

Derlenme sırasında kütüphaneyi linkleyiniz:

cc main.c -L. lft

---

## Kütüphanenin Detaylı Anlatımı

Libft, farklı işlevleri yerine getiren fonksiyon gruplarından
oluşmaktadır. Fonksiyonlar kategorilere ayrılmaktadır:

- Libc Fonksiyonları
- String Fonksiyonları
- Bellek Yönetimi
- Linked List Fonksiyonları
- Yardımcı fonksiyonlar

Tüm fonksiyonlar 42 Norm kurallarına uygun şekilde yazılmıştır
ve bellek güvenliği gözetilerek implemente edilmiştir.

### 1. Libc Fonksiyonları

Bu bölümde, C standart kütüphanesinde (libc) bulunan temel
fonksiyonların yeniden yazılmış halleri yer almaktadır.
Bu fonksiyonların amacı, C dilinde bellek ve karakter
işlemlerinin nasıl çalıştığını daha iyi kavramaktır.

#### 1.1 Karakter Kontrol Fonksiyonları

- `ft_isalpha`: Verilen karakterin alfabetik bir karakter (A–Z, a–z) olup
  olmadığını kontrol eder.
- `ft_isdigit`: Verilen karakterin sayısal bir karakter (0–9) olup
  olmadığını kontrol eder.
- `ft_isalnum`: Verilen karakterin alfabetik veya sayısal olup olmadığını
  kontrol eder.
- `ft_isascii`: Karakterin ASCII tablosunda yer alıp almadığını kontrol eder. 
- `ft_isprint`: Karakterin yazdırılabilir bir karakter olup olmadığını
  kontrol eder.

---

#### 1.2 Karakter Dönüştürme Fonksiyonları

- `ft_toupper`: Küçük harf bir karakteri büyük harfe dönüştürür.
- `ft_tolower`: Büyük harf bir karakteri küçük harfe dönüştürür.

---
#### 1.3 String Fonksiyonları (Libc / POSIX)

- `ft_strlen` : Null-terminated bir string’in uzunluğunu hesaplar.
- `ft_strdup` : Verilen string’in dinamik bellekte bir kopyasını oluşturur.
- `ft_strncmp`: İki string’i belirtilen karakter sayısı kadar karşılaştırır.
- `ft_strnstr`: Bir string içinde başka bir string’i, belirtilen uzunluk
  sınırı dahilinde arar.
---

#### 1.4 Bellek Fonksiyonları

- `ft_memset` : Belirtilen bellek alanını verilen değer ile doldurur.
- `ft_bzero`  : Bellek alanını sıfırlar.
- `ft_memcpy` : Bir bellek alanını başka bir bellek alanına kopyalar. Bellek alanlarının çakışmaması gerekir.
- `ft_memmove`: Çakışan bellek alanlarında güvenli kopyalama işlemi yapar.
- `ft_memchr` : Bellek alanı içinde belirtilen karakteri arar.
- `ft_memcmp` : İki bellek alanını byte byte karşılaştırır.
---
#### 1.5 Sayısal Dönüştürme Fonksiyonları

- `ft_atoi`: String olarak verilen sayısal değeri `int` türüne dönüştürür.
- `ft_itoa`: Sayısal bir değeri string formatına dönüştürür.
---

### 2. Libft’e Özgü String Fonksiyonları

Bu fonksiyonlar, string (char dizileri) üzerinde işlem yapmak
amacıyla geliştirilmiştir. String parçalama, birleştirme ve
düzenleme gibi işlemler bu grupta yer alır. Bu bölümde, C standart kütüphanesinde bulunmayan ve libft projesi kapsamında geliştirilen string fonksiyonları yer almaktadır.

- `ft_substr` : Verilen bir string’in, belirtilen başlangıç indeksinden
  itibaren belirli uzunluktaki alt string’ini oluşturur.
- `ft_strjoin`: İki string’i birleştirerek yeni bir string oluşturur.
- `ft_strtrim`: Bir string’in başında ve sonunda bulunan, belirtilen
  karakterleri temizler.
- `ft_split`  : Verilen bir string’i, belirlenen ayırıcı karaktere göre
  parçalara ayırır ve bir string dizisi döndürür.

---

### 3. Bellek Yönetimi Fonksiyonları

Bu fonksiyonlar, dinamik bellek yönetimi ve bellek güvenliği
konularını kapsar. Bellek tahsisi ve sıfırlama işlemleri bu
grup altında toplanmıştır.

- `ft_calloc` : Belirtilen sayıda ve boyutta bellek alanı ayırır ve
  ayrılan belleği sıfırlar.

---

###  4. Linked List Fonksiyonları

Bu bölümde, tek yönlü bağlı liste (singly linked list)
yapısı üzerinde işlem yapan fonksiyonlar bulunmaktadır.
Bu fonksiyonlar sayesinde dinamik veri yapıları üzerinde
kontrollü işlemler gerçekleştirilebilir.

- `ft_lstnew`      : Yeni bir linked list node’u oluşturur.
- `ft_lstadd_front`: Bir node’u listenin başına ekler.
- `ft_lstadd_back` : Bir node’u listenin sonuna ekler.
- `ft_lstsize` 	   : Listedeki toplam node sayısını döndürür.
- `ft_lstlast` 	   : Listenin sonundaki node’u döndürür.
- `ft_lstdelone`   : Tek bir node’u siler ve içeriğini serbest bırakır.
- `ft_lstclear`    : Tüm listeyi siler ve belleği serbest bırakır.
- `ft_lstiter`     : Listenin her elemanına verilen fonksiyonu uygular.
- `ft_lstmap`      : Listenin her elemanına bir fonksiyon uygulayarak,
  yeni bir liste oluşturur.

---

### Diğer Yardımcı Fonksiyonlar

Bu gruptaki fonksiyonlar, farklı işlemler için kullanılan
yardımcı fonksiyonlardan oluşmaktadır.

- `ft_putchar_fd`: Verilen karakteri belirtilen dosya tanımlayıcısına yazar.
- `ft_putstr_fd` : Verilen string’i belirtilen dosya tanımlayıcısına yazar.
- `ft_putendl_fd`: Verilen string’i, sonuna newline karakteri ekleyerek
  belirtilen dosya tanımlayıcısına yazar.
- `ft_putnbr_fd` : Verilen sayısal değeri belirtilen dosya tanımlayıcısına yazar.

---

## Kaynaklar

- 42 Libft subject dokümanı  
- C Standard Library (man pages)  
- IBM C Library Documentation
- GeeksforGeeks
- Stack Overflow

---

## AI Kullanımı

Bu proje geliştirilirken yapay zekâ araçları, kavramsal
anlamayı desteklemek ve konu tekrarları yapmak amacıyla
kullanılmıştır. Fonksiyonların implementasyonu, hata
ayıklama süreci ve kod yazımı tamamen sevyesil tarafından
gerçekleştirilmiştir. Proje, 42 akademik dürüstlük
kurallarına uygun olarak hazırlanmıştır.

---


