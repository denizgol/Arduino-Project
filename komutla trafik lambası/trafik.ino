//trafik lamabaları
int kirmizi1 = 4;
int kirmizi2 = 7;
int sari1 = 5;
int sari2 = 8;
int yesil1 =6;
int yesil2 = 9;

//araçlar
int buton1 = 2;
int buton2 = 3;

//araç sayısı
int sayac1 = 1;
int sayac2 = 1;

//lamba gecikme süresi
int dinamikGecikme1 = 5;
int dinamikGecikme2 = 5;
int gecikme = 300;

//çıkışlar-girişler
void setup() {
  pinMode(buton1, INPUT_PULLUP);
  pinMode(buton2, INPUT_PULLUP);
  pinMode(kirmizi1, OUTPUT);
  pinMode(kirmizi2, OUTPUT);
  pinMode(sari1, OUTPUT);
  pinMode(sari2, OUTPUT);
  pinMode(yesil1, OUTPUT);
  pinMode(yesil2, OUTPUT);
}

void loop() {
  //butonları oku
  int buton1Durum = digitalRead(buton1);
  int buton2Durum = digitalRead(buton2);

  //iki butona basıldıysa işlem yapma
  if (buton1Durum == HIGH && buton2Durum == HIGH) {

    //buton2 basıldıysa sayacı arttır
  } else if (buton1Durum == LOW && buton2Durum == HIGH) {
    sayac1++;

    //buton2 basıldıysa sayacı arttır
  } else if (buton1Durum == HIGH && buton2Durum == LOW) {
    sayac2++;
  }

  //butona kaç defa basıldıysa gecikme süresini ayarlayan formül
  //kesirli sayılar çıktığı için float değeri kullanıyoruz
  dinamikGecikme1 = 10 * (float)sayac1 / (sayac1 + sayac2);
  dinamikGecikme2 = 10 * (float)sayac2 / (sayac1 + sayac2);


//ışık döngüsü
  digitalWrite(sari1, LOW);
  digitalWrite(sari2, LOW);
  digitalWrite(kirmizi2, LOW);
  digitalWrite(kirmizi1, HIGH);
  digitalWrite(yesil2, HIGH);
  delay(dinamikGecikme2 * gecikme);

  digitalWrite(sari1, HIGH);
  digitalWrite(sari2, HIGH);
  digitalWrite(yesil2, LOW);
  delay(gecikme);

  digitalWrite(kirmizi1, LOW);
  digitalWrite(sari1, LOW);
  digitalWrite(sari2, LOW);
  digitalWrite(yesil1, HIGH);
  digitalWrite(kirmizi2, HIGH);
  delay(dinamikGecikme1 * gecikme);

  digitalWrite(yesil1, LOW);
  digitalWrite(sari1, HIGH);
  digitalWrite(sari2, HIGH);
  delay(gecikme);
}
