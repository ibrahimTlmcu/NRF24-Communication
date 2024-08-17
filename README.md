NRF24L01 + PA + LNA SMA Anten 2.4 GHz ile 3 Joystick ve Buton Kontrollü Kumanda Devresi
Proje Hakkında
Bu projede, NRF24L01 + PA + LNA SMA anten 2.4 GHz modülünü kullanarak kablosuz iletişim sağlayan bir kumanda devresi tasarladım. Devre, 3 adet joystick ve bir buton ile çeşitli cihazları uzaktan kontrol etmek için kullanılabilir. Özellikle RC araçlar, robotik projeler veya diğer gömülü sistemlerde bu tür bir kumanda oldukça kullanışlıdır.

Kullanılan Malzemeler \n
Arduino Nano: Merkezi işlemci birimi olarak kullanıldı.
NRF24L01 + PA + LNA SMA Anten 2.4 GHz: Uzun menzilli ve güçlü kablosuz iletişim sağlamak için tercih edildi.
3 Adet Joystick: İki eksenli hareket kontrolü için kullanıldı.
1 Adet Buton: İlave kontrol girişi olarak kullanıldı.
OLED Ekran: Geri bildirim ve durum bilgisi sağlamak amacıyla kullanıldı.
Devrenin Çalışma Prensibi
Bu kumanda devresi, joystick'ler aracılığıyla iki eksende (X ve Y) hareketleri algılayarak NRF24L01 + PA + LNA SMA anten modülü üzerinden bu verileri kablosuz olarak gönderir. Her bir joystick farklı bir hareketi veya işlevi kontrol edebilir. Buton ise belirli bir komutu göndermek için kullanılabilir. OLED ekran, cihazın mevcut durumunu veya gönderilen verileri görüntülemek için kullanılır.

Devre Şeması

![image](https://github.com/user-attachments/assets/1aabae18-ec42-4a12-ba2c-859de21e1d5c)


![Gorsel2](https://github.com/user-attachments/assets/12e92bd3-829c-47df-a12f-d6e8214c909c)

Arduino IDE kullanarak devrenin yazılımını geliştirdim. Joystick'lerin X ve Y eksenlerindeki analog verileri okuyarak NRF24L01 + PA + LNA SMA anten modülü üzerinden diğer cihazlara gönderiyorum. Kodlama sırasında, veri iletiminde kararlılığı sağlamak için modülün güç gereksinimlerine dikkat ettim.

Sonuç
Bu kumanda devresi, yüksek doğrulukta hareket kontrolü ve güvenilir kablosuz iletişim sağlayan kompakt bir çözümdür. RC araçlar, robotlar ve diğer gömülü sistemler için mükemmel bir kontrol cihazı olarak kullanılabilir.

