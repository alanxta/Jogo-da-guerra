# Jogo-da-guerra

-----Jogo da Guerra-----

É um jogo de cartas do tipo Guerra, feito em linguagem C utilizando estruturas de dados. O jogo é jogado pelo terminal e tem como objetivo vencer o computador acumulando mais cartas e pontos.

-----Como compilar e executar?-----

Abra o terminal

Acesse a pasta onde está salvo o arquivo do jogo

Digite no terminal: 

gcc jogodaguerra.c -o jogodaguerra

E para executar digite:

./jogodaguerra

-----Como jogar?-----

O jogador e o computador recebem metade das cartas do baralho (26 cartas pra cada um).

A cada rodada, os dois escolhem uma carta e o programa compara os valores.

Quem tiver a carta de maior valor, ganha a rodada, ficando com as duas cartas jogadas e soma 1 ponto no placar.

Em caso de empate, as cartas serão descartadas e não contará os pontos.

O jogo segue até que um dos dois fique sem as cartas na mão, encerrando a partida.

-----Regras-----

Valores das cartas (da mais fraca para a mais forte):

Ás (1), 2, 3, 4, 5, 6, 7, 8, 9, 10, Valete (11), Dama (12), Rei (13).

-Desempate:-

Se houver empate, as cartas são descartadas e nenhum dos jogadores recebe ponto.

-Fim do jogo:-

O jogo termina quando um dos jogadores ficar sem cartas.

O placar final é salvo em um arquivo placar.txt.


-----Organização do código-----

O projeto possui apenas um único arquivo com todo o código (jogodaguerra.c)

--Principais estruturas:--

Naipe -> Enumeração dos naipes (Copas, Ouros, Espadas, Paus).

Valor -> Enumeração dos valores das cartas (Ás, 2... até o Rei).

Carta -> Struct que representa uma carta, contendo naipe e valor.

cartaNo -> Nó da lista que forma a pilha de cartas dos jogadores.

Jogador -> Struct que representa cada jogador (nome, pilha de cartas e os pontos).



--Principais funções:--

criarCarta()	Cria uma carta com os naipes e valores.

adicionarCarta()	Adiciona uma carta na pilha.

removerCarta()	Remove a carta do topo da pilha.

removeCartaAleatoria()	Remove uma carta aleatória da pilha.

criarBaralho()	Cria um baralho completo com 52 cartas.

embaralhar()	Embaralha o baralho.

listarCartas()	Mostra todas as cartas da pilha dos jogadores.

mensagensVitorias()	Exibe uma mensagem aleatória de vitória no final rodada.

mensagensDerrotas()	Exibe uma mensagem aleatória de derrota no final rodada.

mensagensEmpate()	Exibe uma mensagem aleatória caso dê empate na rodada.

salvarPlacar()	Salva o resultado da partida em um arquivo chamado placar.txt.
