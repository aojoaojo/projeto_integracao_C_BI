import csv

def transform_csv(filename):
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        rows = list(reader)

    for i in range(len(rows)):
        row = rows[i]
        comma_count = 0
        for j in range(len(row)):
            if row[j] == ';':
                comma_count += 1
                if comma_count == 3:
                    row[j] = ','
                    break

        rows[i] = [cell.replace(',', ';') for cell in row]
        rows[i] = [cell.replace('"', '') for cell in rows[i]]

    with open(filename, 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerows(rows)

# Exemplo de uso
nome_do_arquivo = 'geral.csv'
transform_csv(nome_do_arquivo)
