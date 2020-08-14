#Atividade: Implementar um programa que apresente na tela um menu de opções que,
# além das opções Inserir, Remover e Imprimir, tenha 5 funcionalidades para manipular
# uma lista de itens (dicionários) do tema escolhido.
# Tema = musica
# Atributos: nome, cantor/compositor, álbum, ano de lançamento, duração
#Escolham funcionalidades que sejam uteis e que busquem exercitar python.

#Ideias das funções
#1 - Musicas em ordem alfabética (a-z e z-a);
#2 - Pesquisar artistas, resposta avisando que não tem música dele ou mostrar as musicas dele;
#3 - Pesquisar música;
#4 - Ver o tempo da Playlist;
#5 - Salvar a Playlist em txt;



def cabecalho ():
    print("Bem vindo ao nosso sistema de Playlist C.R.U.D.")
    print("Para adicionar uma nova música, digite 1.")
    print("Para remover uma música, digite 2.")
    print("Para ver sua atual Playlist (na ordem digitada por você), digite 3.")
    print("Para ver sua Playlist em ordem (A-z ou Z-a), digite 4.")
    print("Para pesquisar as musicas de um artista em especifico, digite 5.")
    print("Para pesquisar uma musica em especifico, digite 6.")
    print("Para ver o tempo da Playlist atual, digite 7.")
    print("Para produzir um arquivo texto com a playlist salva, digite 8.")


def AddDicionario (lista):
    nomeM = input('Por favor, digite o nome da musica: ')
    nomeA = input('Por favor, digite o nome do artista: ')
    nomeAB = input('Por favor, digite o nome do álbum: ')
    anoL = int(input('Por favor, digite o ano de lançamento da música: '))
    duracao = float(input('Por favor, digite a duração da música: '))
    seg = duracao - int(duracao)
    min = int(duracao)
    if seg < 0.60:
        duracao = min + seg
    else:
        seg = seg - 0.60
        duracao = min+1+seg
    dicionario = {'musica':nomeM,'Artista':nomeA,'Album':nomeAB,'Ano lançamento':anoL,'duracao':duracao}
    lista.append(dicionario)
    print("Adicionado com sucesso!\n")


def DelDicionario (lista):
    print("Para deletarmos a musica, precisamos dos seguintes dados dela.")
    nomeM = input('Digite o nome da musica: ')
    nomeA = input('Digite o nome do artista: ')
    found = 0
    for i in lista:
        if (i['musica']==nomeM and i['Artista']==nomeA):    #Remove com base no nome da musica e do artista
            lista.remove(i)
            print("Remoção realizada com sucesso!\n")
            found = 1 
            break
    if found == 0
        print('Não existe essa musica na playlist.\n')


def VerPlaylist (lista):
    for i in lista:
        print("Música:%s, Artista:%s, Album:%s, Duração %.2f mins."%(i['musica'],i['Artista'],i['Album'],i['duracao']))
    print('\n')


def VerPlaylistAZ(lista):
    L = []
    x = int(input("Digite 1 para ver a Playlist na ordem A-Z ou 2 para ver na ordem Z-A: "))
    if x == 1:
        L = sorted(lista, key=lambda k: k['musica'])
        for i in L:
            print("Música:%s, Artista:%s, Album:%s, Duração %.2f mins." % (i['musica'], i['Artista'], i['Album'], i['duracao']))
        print('\n')
    elif x == 2:
        L = sorted(lista, key=lambda k: k['musica'], reverse=True)
        for i in L:
            print("Música:%s, Artista:%s, Album:%s, Duração %.2f mins." % (i['musica'], i['Artista'], i['Album'], i['duracao']))
        print('\n')
    else:
        print("Opção inválida, tente novamente \n")

def SrcMusic(lista):
    nomeM = input("Digite o nome da musica que deseja buscar: ")
    found = 0
    for i in lista:
        if i['musica'] == nomeM:
            l = []
            l.append(i)
            VerPlaylist(l)
            found = 1
            break
    if found == 0:
        print("Musica não encontrada.")


def SrcArtist(lista):
    nomeA = input("Digite o nome do artista que deseja buscar: ")
    cont = 0
    l = []
    for i in lista:
        if i['Artista'] == nomeA:
            l.append(i)
            cont += 1
    print("Foram encontradas %d músicas do(a) artista %s, são elas:" % (cont, nomeA))
    VerPlaylist(l)


def TimePlaylist(lista):
    seg = 0
    min = 0
    hora = 0
    for i in lista:
        seg += i['duracao'] - int(i['duracao'])
        min += int(i['duracao'])

    import math
    seg = math.ceil(seg * 100)
    min = int(min + (seg/60))
    seg = int(seg % 60)
    hora = int(min / 60)
    min = int(min % 60)
    print('A playlist tem duracao de %d hora(s), %d mins e %d segundos.'%(hora, min, seg))

def SalvarPlaylist(lista):
    nome = input('Nome da playlist: ')
    arquivo = open(nome+".txt", 'w')
    print(nome + '\n', file=arquivo)
    for i in lista:
        print("Música:%s, Artista:%s, Album:%s, Duração %.2f mins."%(i['musica'],i['Artista'],i['Album'],i['duracao']),file=arquivo)
    print('\n', file=arquivo)
    print("Arquivo criado com sucesso!\n")
    arquivo.close()


def menu():
    x = -1
    Playlist = []

    while x != 9:
        cabecalho()
        x = int(input('Digite 9 para sair.\n'))
        if x == 1:
            AddDicionario(Playlist)
        elif x == 2:
            DelDicionario(Playlist)
        elif x == 3:
            VerPlaylist(Playlist)
        elif x == 4:
            VerPlaylistAZ(Playlist)
        elif x == 5:
            SrcArtist(Playlist)
        elif x == 6:
            SrcMusic(Playlist)
        elif x == 7:
            TimePlaylist(Playlist)
        elif x == 8:
            SalvarPlaylist(Playlist)
        else:
            print("Finalizando...")


menu()


