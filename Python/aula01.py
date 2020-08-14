def fatorial(n):
	fat = n
	i = 1
	while i!=(n-1):
	    fat=fat*(n-i)
	    i=i+1
	return fat

def fat(x):
	if x == 0 or x == 1:
		return 1
	else:
		return x*fat(x-1)

'''x = int(input("Digite um valor para x: "))
fat = fat(x)
print(fat)'''

#qual o tipo do elemento que deseja ler para inserir na lista

'''def menu():
	L=[]
	for i in range(0,3):
		x=int(input("Digite o tipo do elemento: \n 1- int, 2- float, 3- string"))
		if(x==1):
			L.append(int(input("Digite o elemento: ")))
		elif(x==2):
			L.append(float(input("Digite o elemento: ")))
		else:
			L.append(input("Digite o elemento: "))
	return L

L = menu()
count=0
for i in range(0,len(L)):
	print(type(L[i]))
	if type(L[i]) == float:
		count = count + 1 
print(count)'''

'''
#Remover a ultima ocorrencia de um elemento:
L=[0,3,4,5,3,0,4,4]
x=int(input("remova: "))
for i in range (len(L)-1,0,-1):
	if(L[i]==x):
		L.pop(i)
		break
print(L)'''

#Função com multiplos parametros:
'''def funcao(*param):
	for i in range(0, len(param)):
		L.append(param[i])
	return L

L=[]
L= funcao(1,2,3,4)
print(L)'''

'''def insere(L):
	x=int(input("Digite o tipo do elemento:" + "\n 1- int, 2- float, 3- string: "))
	if(x==1):
		L.append(int(input("Digite o elemento: ")))
	elif(x==2):
		L.append(float(input("Digite o elemento: ")))
	else:
		L.append(input("Digite o elemento: "))
	return L


def remove(L):
	x = input("Remova: ")
	for i in range(0,len(L)):
		if(str(L[i])==x):
			L.pop(i)
			break 
	return L

def count(L):
	L1=[]
	for i in range(0,len(L)):
		L1.append(str(L[i])) 
	x = input("Elemento: ")
	print("O elemento "+ str(x) + " aparece " + str(L1.count(x)) + " vezes ")


def printInt(L):
	count=0
	for i in range(0,len(L)):
		#print(type(L[i]))
		if type(L[i]) == int:
			print(L[i])
			count = count + 1 
	print(count , "elementos tipo int")


def menu():
	L=[]
	op=0
	while(op!=6):
		op=int(input("1- Inserir um elemento na lista" +
			         "\n2- Remover um elemento da lista" +
			         "\n3- Imprimir a lista" +
			         "\n4- Contar o número de ocorrências de um elemento" +
			         "\n5- Imprimir os elementos inteiros da lista" +
			         "\n6- Sair"))
		if op==1:
			L=insere(L)
		elif op==2:
			L=remove(L)
		elif op==3:
			print(L)
		elif op==4:
			count(L)
		elif op==5:
			L=printInt(L)
		else: 
			print("Finalizando...")
		

L = menu()'''


#Dicionarios
'''pessoa={}
pessoa['Nome']=input("Digite o nome: ")
pessoa['Idade']=int(input("Digite a idade: "))
pessoa['Cidade']=input("Digite a cidade: ")
pessoa['Altura']=float(input("Digite a altura: "))

print(pessoa)


def imprime(M):
	print("Matriz 3x3: ")
	for i in range (0,3):
		for j in range (0,3):
			print(int(M[i][j]), end='\t')
		print('')

def insere(M):
	for i in range(0,3):
		L=[]
		for j in range(0,3):
			x=int(input("Digite o elemento: "))
			L.append(x)
		M.append(L)
	return M

def soma(M,N):
	M2 =[ ]
	for i in range(len(M)):
		L=[]
		for j in range(len(M[0])):
			L.append(int(M[i][j]+N[i][j]))
		M2.append(L)
	return M2


def menu():
	M=[]
	N=[[int(1),int(2),int(3)],[int(4),int(5),int(6)],[int(7),int(8),int(9)]]
	op=0
	while(op!=4):
		op=int(input("1- Inserir um elemento na matriz" +
			         "\n2- Imprimir uma matriz" +
			         "\n3- Somar matrizes" +
			         "\n4- Sair"))
		if op==1:
			M=insere(M)
		elif op==2:
			imprime(M)
		elif op==3:
			M=soma(M,N)
		else:
			print("Finalizando...")
		
		
menu()


lista=[0,1,2,3,4]
print(list(map(lambda x: x+1 if x%2==0 else x,lista)))


def inserir():
	arquivo = open("nomes.txt", 'w')
	for i in range(0,3):
	    n=input("Nome: ")
	    i=input("Idade: ")
	    s=input("Sexo: ")
	    print("Nome: " + n + " Idade: " + i + " Sexo: " + s, file=arquivo)
	arquivo.close()


def imprime(idade):
	arq = open("nomes.txt", 'r')
	lista=arq.readlines()
	
	for i in lista:
		dados=i.split()
		if int(dados[3])>idade and dados[5]=='Feminino':
			print(i)
	
	arq.close()

def menu():
	op=0
	while (op != 3):
		op= int(input("1- Inserir dados"+
			        "\n2- Exibir mulheres maiores de idade"+
			        "\n3- Sair\n "))
		if op==1:
			inserir()
		elif op==2:
			idade=int(input("Insira a idade: "))
			imprime(idade)
		else:
			print("Finalizando...")

menu()


from functools import reduce
def verificaL(x,y):
	return x+y

lista=[1,2,3]
if reduce(verificaL,lista)==6:
	print("É número perfeito")
else:
	print("Não é numero perfeito")





x = int (input("Digite a idade minina da pessoa: "))

import csv
with open('pessoas.csv','r',encoding='utf-8')as arquivo_csv:
	leitor = csv.reader(arquivo_csv,delimiter=',')
	i=0
	for coluna in leitor:
		if i == 0:
			pass
		elif int(coluna[1])>x:
			print(coluna)
		i=i+1
'''

import json
with open('teste3.json','r')as json_file:
	dados=json.load(json_file)


for j in range(0,len(dados)):
	media=0
	cursos = dados[j]['Curso']
	pessoas = dados[j]['Alunos']
	for i in range(0,len(pessoas)):
		media=media+int(pessoas[i]['idade'])

	media_f=media/len(pessoas)
	print(media_f)		



	











