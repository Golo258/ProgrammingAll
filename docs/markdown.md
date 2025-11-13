

Markdown syntaxy i składnie:


1️⃣ Nagłówki (Headings)
📌 Składnia
# H1 – największy
## H2
### H3
#### H4


📌 Równoważne z HTML
<h2>Nagłówek</h2>



📌 Własne ID nagłówka (bardzo przydatne)
## Deployment process {#deploy}


I link do tego nagłówka: 
[skocz do deploymentu](#deploy)

<!-- ----------------------------- -->
2️⃣ Formatowanie tekstu
Pogrubienie
**bold**

Kursywa
*italic*

Przekreślenie
~~tak się usuwa~~

Kod inline
`jakas_funkcja()`

3️⃣ Listy
🔹 Zwykła lista
- item
- item
  - pod-item

🔸 Numerowana
1. krok
2. krok
3. krok

<!-- -------------- -->
4️⃣ Linki
Link do strony
[Google](https://google.com)

k do nagłówka w dokumencie

Jeśli nagłówek:

## Install {#inst}

To link:

[Skocz do instalacji](#inst)


5️⃣ Obrazki
![Opis obrazka](sciezka/do/obrazka.png)
Local, GitHub, URL — wszystko działa.

6️⃣ Cytaty (blockquote)
> To jest cytat.
> Może mieć wiele linii.


7️⃣ Kod – bloki code-block
🔥 Najważniejsze dla devów
<pre> ```python def test(): return 123 ``` </pre>

Albo:

<pre> ```bash git status ``` </pre>

Zawsze trzy backticki:

```lang
kod
```
'

8️⃣ Tabele
| Name | Score |
|------|-------|
| Jan  | 52    |
| Aga  | 12    |


9️⃣ Pionowa linia (separator)
---


🔟 Checkboxy
- [x] zrobione
- [ ] nie zrobione
GitHub obsługuje klikanie ✔️.


1️⃣1️⃣ Spoiler / szczegóły (<details>)

<details>
<summary>Kliknij, aby rozwinąć</summary>

Tu jest ukryta treść.

</details>


1️⃣2️⃣ Callouty (GitHub / Obsidian / Docsify)
> [!NOTE]
> To jest notatka
> [!WARNING]
> Uważaj!
> [!TIP]
> Mała podpowiedź

1️⃣3️⃣ Tasklist + hierarchia
- [ ] Zadanie
  - [x] pod-zadanie


1️⃣4️⃣ Escape'owanie znaków

Jeśli chcesz pokazać * lub _, bez formatowania:

\*gwiazdka\*

1️⃣5️⃣ Komentarze w Markdown (ukryte)
<!-- To jest komentarz i nie będzie widoczne -->


1️⃣6️⃣ Definiowanie footnotes (przypisy)
Coś ważnego [^przypis].

[^przypis]: Treść przypisu.

1️⃣7️⃣ Relative links do innych plików
[Specyfikacja](./docs/spec.md)


1️⃣8️⃣ Gotowy template – dokument z TOC i kotwicami
# Dokumentacja

## Table of Contents
- [Wstęp](#wstep)
- [Instalacja](#instalacja)
- [Użycie](#uzycie)

---

## Wstęp {#wstep}
Treść...

## Instalacja {#instalacja}
Treść...

## Użycie {#uzycie}
Treść...


1️⃣9️⃣ Stylowanie bloków tekstu w HTML (działa w MD)

Markdown pozwala na HTML:

<div style="color: orange; font-weight: bold;">
UWAGA: to jest pomarańczowe.
</div>