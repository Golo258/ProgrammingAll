import csv

def extract_words_by_category(file_path, target_category):
    words = set()
    current_category = None

    with open(file_path, 'r', encoding='utf-8') as file:
        for line in file:
            line = line.strip()

            if line.startswith('#') or line == "":
                continue  # Pomija nagłówki i puste linie
            if line.endswith(':'):
                current_category = line[:-1]
                continue

            if current_category == target_category and '-' in line:
                parts = [part.strip() for part in line.split('-')]
                if len(parts) >= 2:
                    italian, english = parts[0], parts[1]
                    words.add((italian, english))

    return words

def save_to_csv(words, output_file, language_name):
    with open(output_file, 'w', newline='', encoding='utf-8') as csvfile:
        fieldnames = [language_name, 'English']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)

        writer.writeheader()
        for word in words:
            writer.writerow({language_name: word[0], 'English': word[1]})

input_file = 'Spanish_formatted.txt'
output_file = 'SpanishFlashcards/adjectives.csv'
category = 'Adjectives'
words = extract_words_by_category(input_file, category)
save_to_csv(words, output_file, "Spanish")

