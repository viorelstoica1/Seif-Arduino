# Seif-Arduino
Cod făcut pentru un Arduino Uno, conectat la o plăcuță custom cu patru 7 segment displays, un potențiometru, două led-uri, două push-buttons, un buzzer, un servomotor și două butoane colorate (roșu și verde). Plăcuța simulează funcționarea unui seif cu un cod de patru cifre.
# Funcționalitate
Statusul seifului se vede pe cele două led-uri colorate:
* roșu aprins înseamnă seif închis
* verde aprins înseamnă seif deschis  
  
Cifra selectată se introduce cu potențiometrul (ciclează între cifrele 0-9), iar schimbarea cifrei selectate se face cu apăsarea butonului integrat în potențiometru.(trece la următoarea din dreapta)  
  
Apăsarea butonului verde testează codul introdus, și deschide seiful dacă este corect.(rotește servomotorul, scoate un sunet de confirmare și aprinde led-ul verde) Dacă nu este corect, seiful rămâne închis și scoate un sunet pentru refuzarea codului.  

Apăsarea butonului roșu închide seiful, dacă acesta este deschis, aprinde led-ul roșu și resetează codul de pe display la 0000.  

Unul din push-butoane resetează codul afișat pe display, iar al doilea permite introducerea unui nou cod al seifului, dar doar dacă seiful este deja deschis.  

Codurile schimbate se păstrează și dacă este întreruptă alimentarea.  

# Proiectul a fost realizat în echipă cu:
* Mihnea Baștea, Saxion University of Applied Sciences, Applied Computer Sciences
* Sara Neagu, Saxion University of Applied Sciences, Electrical and Electronic Engineering
