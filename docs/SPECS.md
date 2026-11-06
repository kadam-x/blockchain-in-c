# Specifikáció

## A program feladata
- A program egy tranzakciókat rögzítő, egygépes blockchain-szimuláció.
- Minden tranzakció egy külön blokk, és a következő blokk az előző blokk hash-ével kapcsolódik hozzá.
- A program számolja az egyenlegeket, ellenőrzi a láncot, valamint ment és betölt, mindezt szöveges (TUI) felületen.
- Egy tranzakció 3 részből áll: egy küldő, egy címzett és az összeg.
- A blokknak 5 része van: egyedi sorszám, időbélyeg, tranzakció, az előző blokk hash-e, valamint a saját hash-e.
- A legelső blokk neve genesis blokk, ez a lánc 0. blokkja.
- A SYSTEM a fenntartott wallet név.
- Az egyenleg a kapott összegek mínusz az elküldött összegek.

## Adatok és korlátok
- A wallet neve 1–30 karakter hosszú.
  - Lehet benne szóköz és ékezet.
  - A szélén nem lehet szóköz.
  - Pontosvessző egyáltalán nem lehet benne.
  - A kis- és nagybetűk számítanak.
- Az összeg pozitív egész szám, 1 és 1000000 között.
- Új tranzakcióban a küldő nem lehet egyenlő a címzettel, és egyik sem lehet SYSTEM.
- Ha a küldő egyenlegén nincs fedezet a küldött összegre, a tranzakció nem valósul meg.
- Az új walletek az első említéskor jönnek létre, 0 egyenleggel.
- Az időbélyeget a program automatikusan adja, helyi idő szerint, ÉÉÉÉ-HH-NN ÓÓ:PP:MM formában.
- A hash 16 hexadecimális karakterből álló sorozat.
  - Bemenete: sorszám, időbélyeg, küldő, címzett, összeg, előző hash.
  - Ezek bármelyikének megváltozása a hash-t is megváltoztatja.
  - Nem kriptográfiai hash.

## Genesis blokk és pénzmennyiség
- Ha nincs betöltött lánc, a program létrehozza a 0. blokkot.
  - A küldő SYSTEM, a címzett is.
  - Az összeg 1000000.
  - Az előző hash 16 darab 0.
- Ez a rendszerben létező teljes pénzmennyiség, új pénz ezután nem keletkezik.
- A genesis blokk az egyetlen, ahol a küldő és a címzett megegyezik.
- Ez nem számít elküldött összegnek: az egész mennyiség a SYSTEM egyenlegére kerül.

## Főmenü és vezérlés
- A felhasználó lehetőségei: Új tranzakció, Pénz kiadása, Lánc megtekintése, Egyenleg és történet, Lánc ellenőrzése, Mentés, Kilépés.
- A program legalább 80 × 24-es terminált feltételez.
- A felület színes, keretekkel tagolt.
- A képernyő tetején minden nézetben fejléc van, rajta a nézet neve és a fájl neve.
- Ha a láncban mentetlen változás van, a fájl neve után csillag (`*`) áll, például: `chain.txt*`.
- A képernyő alján egy soros súgó mutatja az adott nézetben használható billentyűket.
- A menüben:
  - fel/le nyíllal lehet választani,
  - Enterrel megerősíteni,
  - Escape-el visszalépni,
  - a kijelölt menüpont ki van emelve.
- Szöveg bevitelekor a program egy keretes beviteli mezőt rajzol, felette a kért adat nevével, Enter zárja le.
- Üres sor (csak Enter) megszakítja a műveletet, és visszavisz a főmenübe, semmi nem változik.

## A menüpontok működése

### Új tranzakció
- A program ebben a sorrendben kéri be az adatokat: küldő, címzett, összeg.
- Hibás adatnál a mező javítását kéri újra.
- A végén összefoglalót ad, amire Enterrel (igen) vagy Escape-el (nem) válaszol a felhasználó.
- Siker esetén új blokk kerül a láncra, és megjelenik a csillag a fejlécben.

### Pénz kiadása
- A felhasználó a SYSTEM walletből ad egy tetszőleges walletnek összeget (a SYSTEM kivételével).
- A bekért adatok sorrendben: címzett, összeg.
- Ez az egyetlen hely, ahol a SYSTEM küldő lehet.
- A SYSTEM egyenlege nem mehet nulla alá.
- A megerősítés és a csillag megjelenése ugyanúgy működik, mint az Új tranzakciónál.

### Lánc megtekintése
- A blokkok táblázatban jelennek meg, soronként egy blokk, oldalanként 10, növekvő sorrendben.
- Oszlopok: sorszám, időbélyeg, küldő -> címzett, összeg, a hash első 8 karaktere.
- A 12 karakternél hosszabb neveket a táblázat rövidítve mutatja.
- Megnyitáskor az utolsó blokk van kijelölve, a kijelölt sor ki van emelve.
- A fejlécben látszik, hogy hányadik blokk van kijelölve az összesből.
- A fel/le nyíllal a kijelölés mozgatható, PageUp/PageDown-nal lapozni lehet.
- Enterre a kijelölt blokk részletei jelennek meg egy keretes dobozban: sorszám, időbélyeg, teljes küldő és címzett, összeg, teljes hash, előző hash.
- Escape-el vissza lehet térni a táblázathoz.
- Az érvényes blokkok zölden, az érvénytelenek pirosan látszanak.
- Érvénytelen blokk csak olyan fájl betöltése után fordulhat elő, amelyet az ellenőrzés hibásnak talált (csak olvasható mód), a program futás közben nem hoz létre érvénytelen blokkot.
- Escape-el a program visszatér a főmenübe.

### Egyenleg és történet
- A program bekér egy wallet nevet.
- Ha ez létező név, kiírja az egyenleget és az összes érintett tranzakciót: sorszám, időbélyeg, előjeles összeg, másik fél.
- Ismeretlen névnél: „A névhez nem tartozik egyetlen tranzakció sem”, az egyenleg 0.

### Lánc ellenőrzése
- A program végigmegy az összes blokkon, és kiírja az eredményt.
- Hiba esetén kiírja az első hibás blokk sorszámát és az okot (a blokk saját hash-e nem egyezik az adataival, vagy az előző hash nem egyezik az előző blokk hash-ével).
- Ellenőrzi azt is, hogy a walletek közül egyiknek az egyenlege sem negatív a lánc egyik pontján sem, és hogy az egyenlegek összege pontosan 1000000.

### Mentés
- A felhasználó a főmenüből kézzel menti a láncot a program mappájában lévő, fix nevű fájlba.
- Sikeres mentés után a csillag eltűnik a fejlécből.
- Ha a fájl írása nem sikerül, a program hibaüzenetet ír, és a csillag megmarad.

### Kilépés
- Ha a fejlécben csillag van, a program rákérdez a mentésre (Igen / Nem / Mégse).
  - Az Igen ment és kilép.
  - A Nem mentés nélkül kilép.
  - A Mégse visszavisz a főmenübe.
- Ha nincs csillag, a program rákérdezés nélkül kilép.
- A választás a fel/le nyíllal történik, Enter a választ megerősíti, Escape pedig a Mégse.

## Érvénytelen blokkra vonatkozó szabály
- Egy blokk akkor és csak akkor érvényes, ha:
  - a hash-e megegyezik a blokk adataiból számolt értékkel, és
  - az előző hash-e megegyezik az előző blokk hash-ével.
- Az első érvénytelen blokktól kezdve minden további blokk is érvénytelennek számít.

## Fájl
- A fájl neve fix, például `chain.txt`.
- Szöveges fájl, soronként egy blokk.
- A mezőket pontosvessző választja el, ebben a sorrendben: sorszám, időbélyeg, küldő, címzett, összeg, előző hash, hash.
- Példasorok:
  - `0;2026-11-01 20:10:00;SYSTEM;SYSTEM;1000000;0000000000000000;a41c07d93be2f685`
  - `1;2026-11-01 20:15:03;SYSTEM;Adam;500000;a41c07d93be2f685;3fa91c07d2e4ab58`
- Az első sor a genesis blokk, a fájl kézzel szerkeszthető.
- Induláskor, ha a fájl létezik, a program betölti és ellenőrzi.
- Ha induláskor nincs fájl, vagy a fájl üres, a program üres lánccal indul, és létrehozza a genesis blokkot.

## Hibás fájl esetén
- **Ha a fájl nem értelmezhető** (hiányzó mező, nem szám az összeg, túl hosszú vagy tiltott karaktert tartalmazó név, hibás időbélyeg, a sorszámok nem 0-tól egyesével nőnek, hiányzó genesis blokk stb.):
  - a program hibaüzenetet ír a hibás sor számával,
  - leáll,
  - és a fájlt nem módosítja.
- **Ha a fájl értelmezhető, de az ellenőrzés hibát talál** (például egy kézzel átírt összeg miatt egy blokk hash-e nem egyezik), a program csak olvasható módban tölti be a láncot:
  - a fejlécben a fájl neve után „[csak olvasható]” áll,
  - a program hibaként kiírja az első hibás blokk sorszámát,
  - a Lánc megtekintése, az Egyenleg és történet és a Lánc ellenőrzése működik,
  - az Új tranzakció, a Pénz kiadása és a Mentés a főmenüben szürkén látszik, kiválasztásukra a program hibaüzenetet ír, hogy csak olvasható módban nem elérhető,
  - így a program nem írja felül az eredeti fájlt.

## Hibakezelés bevitelnél
- Hibás adatnak számít: csak szóközökből álló név, tiltott karakter, tartományon kívüli összeg, nincs fedezet a tranzakcióra, a küldő és a címzett megegyezik, SYSTEM a küldő vagy a címzett az Új tranzakciónál, SYSTEM a címzett a Pénz kiadásánál.
- Hiba esetén a program piros, egysoros hibaüzenetet ír a beviteli mező alá, és a mezőt újra kéri.
- A hibaüzenet kifejezetten a hibára hivatkozik, például: „Az összeg legfeljebb 1000000 lehet.”
