# 📘 Markdown – Ściąga

## 1. Nagłówki

```
# H1
## H2
### H3
#### H4
```

Własne ID:

```
## Nagłówek {#id_naglowka}
```

Odnośnik:

```
[Skocz](#id_naglowka)
```

---

## 2. Formatowanie

**Pogrubienie:** `**tekst**`

*Kursywa:* `*tekst*`

~~Przekreślenie:~~ `~~tekst~~`

Kod inline: `` `kod()` ``

---

## 3. Listy

### Zwykła lista

```
- item
- item
  - pod-item
```

### Numerowana

```
1. krok
2. krok
3. krok
```

---

## 4. Linki

Zewnętrzny:

```
[Google](https://google.com)
```

Do nagłówka:

```
[U góry](#jakis-id)
```

---

## 5. Obrazki

```
![Opis](sciezka/do/plik.png)
```

---

## 6. Cytaty

```
> To jest cytat.
```

---

## 7. Code block

````
```python
def hello():
    print("siema")
```
````

---

## 8. Tabele

```
| Name | Score |
|------|-------|
| Jan  | 52    |
| Ala  | 12    |
```

---

## 9. Separator

```
---
```

---

## 10. Checkboxy

```
- [x] zrobione
- [ ] nie zrobione
```

---

## 11. Spoiler / details

```
<details>
<summary>Kliknij</summary>
Ukryta treść.
</details>
```

---

## 12. Callouty (GitHub/Obsidian)

```
> [!NOTE]
> Notatka

> [!WARNING]
> Uwaga!
```

---

## 13. Komentarze

```
<!-- ukryty komentarz -->
```

---

## 14. Footnotes

```
Tekst z przypisem [^1].

[^1]: Treść przypisu.
```

---

## 15. Relative links

```
[Specyfikacja](./docs/spec.md)
```

---

## 16. HTML w Markdown

```
<div style="color: orange; font-weight: bold;">UWAGA</div>
```

---

## 17. Najważniejsze skróty (TL;DR)

````
## Nagłówek {#id}
[link](#id)

```cpp
int x = 10;
````

| A | B |
| - | - |
| 1 | 2 |

<details><summary>Klik</summary>abc</details>
```
