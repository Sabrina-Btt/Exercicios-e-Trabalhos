--exercicio 1--
main :: IO ()    
main = return ()
del_posicao_n :: [Int] -> Int -> [Int] 
lista == [] = 0;
del_posicao_n (a:b) 1 = b;
del_posicao_n (a:b) n = a: del_posicao_n b (n-1)

--exercicio 2--
main :: IO ()    
main = return ()
ord []=[]
ord(a:b)=ord[n|n<-b, n<=a]++[a]++ord[n|n<-b, n>a]
impares lista = ord (filter odd lista) 

--exercicio 3--
main :: IO ()    
main = return ()
fib 0 = 0
fib 1 = 1
fib n = fib(n-1) + fib(n-2)

lfib 1 = [0,1]
lfib n = lfib(n-1)++[fib(n-1)+fib(n-2)]

--exercicio 6--
intersecao [] _ = []
intersecao (h:b) lista 
	| existe lista h = [h] ++ intersecao b lista
	| otherwise = intersecao b lista

existe [] n = False
existe (h:b) n
	| n == h = True
	| otherwise = existe b n
  
--exercicio 7--
busca_sub _ [] = []
busca_sub string (lista1:b) 
	|compara string lista1 = [lista1] ++ busca_sub string b
	|otherwise = busca_sub string b
  
 --exercicio 8--
repete_qt elem 0 = []
repete_qt elem n = [elem] ++ repete_qt elem (n - 1)

repete 0 = []
repete n = (repete_qt n n) ++ repete (n-1) 

--exercicio 9--
palindromo [] = True
palindromo lista 
	| compara lista (inversa lista) = True
	| otherwise = False

compara [] [] = True
compara (h1:b1) (h2:b2) 
	| h1 == h2 = True && compara b1 b2
	| otherwise = False

inversa [] = []
inversa (h:b) = inversa b ++ [h]

--exercicio 10--
rodar_esquerda n [] = []
rodar_esquerda 0 lista = lista 
rodar_esquerda n lista = (drop n lista) ++ (take n lista)

--exercicio 11--
inversa [] = []
inversa (h:b) = inversa b ++ [h]

--exercicio 12--
ocorrencias [] _ = 0
ocorrencias (h:b) string
    | compara h string = 1 + ocorrencias (drop (tam string) h) string
    | otherwise = ocorrencias b string

compara [] _ = True
compara (h:b) (h1:b1)
    |h == h1 = True && compara b b1
    |otherwise = False

tam [] = 0
tam (h:b) = 1 + tam b 
  
--exercicio 13--
limites l = limites_aux l (maxBound :: Int) 0


limites_aux [] min max = (min, max)
limites_aux (cab:corpo) min max 
    | cab > max = limites_aux (corpo) min cab
    | cab < min = limites_aux (corpo) cab max
    | otherwise = limites_aux (corpo) min max

--exercicio 14--
existe elem [] = False 
existe elem (cab:corpo)
    | elem == cab = True
    | otherwise = existe elem corpo

remDuplicatas [] = []
remDuplicatas (cab:corpo) 
    | existe cab corpo = remDuplicatas corpo
    | otherwise = [cab] ++ remDuplicatas corpo
    
--exercicio 15--
somaQuadrados 0 = 0
somaQuadrados elem = elem * elem + somaQuadrados (elem - 1)

--exercicio 16--
insereF elem [] = [elem]
insereF elem (cab:corpo) = [cab] ++ insereF elem corpo

removeF [] = []
removeF (cab:corpo) = corpo

calculaTam [] = 0
calculaTam (cab:corpo) = 1 + calculaTam (corpo)

--exercicio 17--
insereP elem [] = [elem]
insereP elem (cab:corpo) = insereP elem corpo ++ [cab]

removeP [] = []
removeP (cab:corpo) = corpo

--exercicio 19a)--
soma_poli [] [] = []
soma_poli [] (cab2:corpo2) = (cab2:corpo2)
soma_poli (cab1:corpo1) [] = (cab1:corpo1)
soma_poli (cab1:corpo1) (cab2:corpo2)
    | (snd cab1) > (snd cab2) = [cab1] ++ soma_poli corpo1 (cab2:corpo2)
    | (snd cab1) < (snd cab2) = [cab2] ++ soma_poli corpo2 (cab1:corpo1)
    | otherwise = [((fst cab1 + fst cab2),(snd cab2))] ++ soma_poli corpo1 corpo2
    
 --exercicio 20--
 lista_igual [] [] = True
lista_igual [] (h2:b2) = False
lista_igual (h1:b1) [] = False
lista_igual (h1:b1) (h2:b2)
	| h1 == h2 = True && lista_igual b1 b2
	| otherwise = False

matrizes_igual [] [] = True
matrizes_igual (h1:b1) [] = False
matrizes_igual [] (h2:b2) = False
matrizes_igual (h1:b1) (h2:b2) = (lista_igual h1 h2) && (matrizes_igual b1 b2)

--exercicio 21--
somatorio li lf f
	| li == lf = (f li)
	| otherwise	= (f li) + (somatorio (li+1) lf f)
	
--exercicio 22--
merge [] [] = []
merge [] (h2:b2) = (h2:b2)
merge (h1:b1) [] = (h1:b1)
merge (h1:b1) (h2:b2)	  
	| h1 < h2 = [h1] ++ (merge b1 (h2:b2))
	| otherwise = [h2] ++ (merge (h1:b1) b2)

--exercicio 23--
conv_int_str _ [] = []
conv_int_str (h1:b1) (h2:b2) = (acha (h1:b1) h2) ++ conv_int_str (h1:b1) b2


acha [] _ = []
acha (h1:b1) elem
	| (fst h1) == elem = [(snd h1)]
	| otherwise = acha b1 elem
	
    
    
