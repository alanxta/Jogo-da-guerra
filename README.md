# Jogo-da-guerra

--Jogo da Guerra--

É um jogo de cartas do tipo Guerra, feito em linguagem C utilizando estruturas de dados. O jogo é jogado pelo terminal e tem como objetivo vencer o computador acumulando mais cartas e pontos.

---Como jogar?---

O jogador e o computador recebem metade das cartas do baralho (26 cartas pra cada um).

A cada rodada, os dois escolhem uma carta e o programa compara os valores.

Quem tiver a carta de maior valor, ganha a rodada, ficando com as duas cartas jogadas e soma 1 ponto no placar.

Em caso de empate, as cartas serão descartadas e não contará os pontos.

O jogo segue até que um dos dois fique sem cartas na mão, encerrando a partida.

---Regras---

Valores das cartas (da mais fraca para o mais forte):

Ás (1), 2, 3, 4, 5, 6, 7, 8, 9, 10, Valete (11), Dama (12), Rei (13).

Desempate:

Se houver empate (quando as cartas têm o mesmo valor), as cartas são descartadas e nenhum dos jogadores recebe ponto.

Fim do jogo:

O jogo termina quando um dos jogadores ficar sem cartas.

O placar final é salvo em um arquivo placar.txt.

