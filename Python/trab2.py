import json
import csv


cidade = 'Rio das Ostras'
cid = cidade.replace(" ", "_")
#Exercício 1
lista = []
with open('caso_full.csv', 'r', encoding='utf-8') as arquivo_csv:
	leitor = csv.reader(arquivo_csv, delimiter=',')
	for coluna in leitor:
		if coluna[0] == cidade:
			lista.append(coluna)


with open("casos_" + cid + ".csv", "a") as saida_csv:
	escrever = csv.writer(saida_csv, delimiter=',', lineterminator='\n')
	for coluna in lista:
		escrever.writerow(coluna)

#Exercício 2
lista = []
with open('caso_full.csv', 'r', encoding='utf-8') as arquivo_csv:
	leitor = csv.reader(arquivo_csv, delimiter=',')
	for coluna in leitor:
		if coluna[0] == cidade:
			info = {'Date': coluna[2], 'New Confirmed': coluna[15], 'New Deaths': coluna[16]}
			lista.append(info)
			casos = {'City': coluna[0], 'Info': lista}
			

with open('casos_' + cid + '.json',  'w') as json_file:
	json.dump(casos, json_file, indent=4)






