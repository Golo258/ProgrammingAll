import PyPDF2

# Wczytaj plik PDF
with open('nazwa_pliku.pdf', 'rb') as file:
    # Utwórz obiekt czytnika PDF
    pdf_reader = PyPDF2.PdfFileReader(file)

    # Uzyskaj dostęp do strony PDF (indeksowanie od zera)
    page = pdf_reader.getPage(0)

    # Zmień tekst na stronie
    page_text = page.extractText()
    modified_text = page_text.replace('Stara_dana', 'Nowa_dana')

    # Zaktualizuj tekst na stronie
    page.mergePage(modified_text)

    # Utwórz obiekt pisarza PDF
    pdf_writer = PyPDF2.PdfFileWriter()

    # Dodaj zaktualizowaną stronę do obiektu pisarza
    pdf_writer.addPage(page)

    # Zapisz zaktualizowany plik PDF
    with open('zaktualizowany_plik.pdf', 'wb') as new_file:
        pdf_writer.write(new_file)