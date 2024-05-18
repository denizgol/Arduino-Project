//lamba için gerekli arduino çıkışları
const int kirmiziPin1 = 4;
const int sariPin1 = 5;
const int yesilPin1 = 6;

const int kirmiziPin2 = 7;
const int sariPin2 = 8;
const int yesilPin2 = 9;

int toplamSure1 = 5;
int toplamSure2 = 5;

//şimdiki zaman değerini tutmak ve gecikmeler için
uint32_t zaman1 = 0;

// 0: Kırmızı, 1: Sarı, 2: Yeşil
int durum = 0;  

// resetlemek için gerkli
bool degerAlmaModu = true;  

void setup() {
  //çıkışları seçiyoruz
  Serial.begin(9600);

  pinMode(kirmiziPin1, OUTPUT);
  pinMode(sariPin1, OUTPUT);
  pinMode(yesilPin1, OUTPUT);

  pinMode(kirmiziPin2, OUTPUT);
  pinMode(sariPin2, OUTPUT);
  pinMode(yesilPin2, OUTPUT);
}

void loop() {
  //kullanıcıdan değer almak için gerekli loop
  if (degerAlmaModu) {
    if (!Serial.available()) {
      Serial.println("Ilk lamba suresini giriniz: \n");
      Serial.setTimeout(100000);
      toplamSure1 = Serial.parseInt();
      Serial.setTimeout(1000);
      Serial.println("Ikinci lamba suresini giriniz: \n");
      Serial.setTimeout(100000);
      toplamSure2 = Serial.parseInt();
      Serial.setTimeout(1000);
      Serial.println("Degerler basariyla girildi.");
      Serial.println("Lambalar ayarlaniyor...");
      Serial.println("Lambalari sifirlamak icin r tusuna basin.. \n");
      Serial.flush();
      degerAlmaModu = false;  // Değer alım modunu kapat
    }
  } else {
    // Değerler alındıktan sonra normal işlemler devam eder önceki trafik ışık kodunun aynısı
    uint32_t zaman2 = millis();

    if (durum == 0) {
      digitalWrite(sariPin1, LOW);
      digitalWrite(sariPin2, LOW);
      digitalWrite(kirmiziPin2, LOW);
      digitalWrite(kirmiziPin1, HIGH);
      digitalWrite(yesilPin2, HIGH);

      if (zaman2 - zaman1 >= toplamSure2 * 1000) {
        zaman1 = zaman2;
        durum = 1;
      }
    } else if (durum == 1) {
      digitalWrite(sariPin1, HIGH);
      digitalWrite(sariPin2, HIGH);
      digitalWrite(yesilPin2, LOW);

      if (zaman2 - zaman1 >= 1000) {
        zaman1 = zaman2;
        durum = 2;
      }
    } else if (durum == 2) {
      digitalWrite(kirmiziPin1, LOW);
      digitalWrite(sariPin1, LOW);
      digitalWrite(sariPin2, LOW);
      digitalWrite(yesilPin1, HIGH);
      digitalWrite(kirmiziPin2, HIGH);

      if (zaman2 - zaman1 >= toplamSure1 * 1000) {
        zaman1 = zaman2;
        durum = 3;
      }
    } else if (durum == 3) {
      digitalWrite(yesilPin1, LOW);
      digitalWrite(sariPin1, HIGH);
      digitalWrite(sariPin2, HIGH);

      if (zaman2 - zaman1 >= 1000) {
        zaman1 = zaman2;
        durum = 0;
      }
    }

    // R tuşu algılama ve değişkenleri sıfırlama
    if (Serial.available()) {
      char karakter = Serial.read();
      if (karakter == 'r' || karakter == 'R') {
        degerAlmaModu = true;  // Değer alma modunu aç
        durum = 0;             // Durumu sıfırla
        zaman1 = 0;            // Zamanlayıcıyı sıfırla
        Serial.println("\n ");
        Serial.println("Yeni lamba suresini giriniz: ");
      }
    }
  }
}
