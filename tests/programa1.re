numero erro = 0
numero p = 0
numero i = 0
numero integral = 0
numero d = 0
numero lastErro = 0
numero correcaoE = 0
numero correcaoD = 0
numero velocidade = 45

tarefa segueLinha {
  erro =  luz(2) - luz(3)
  p = erro * 15
  integral = integral + erro
  i = integral * 0.0001
  d = (erro - lastErro) * 30
  lastErro = erro

  correcaoE = (velocidade + (p + i + d))
  correcaoD = (velocidade - (p + i + d))

  escrever(1, virartexto(correcaoE))
  escrever(2, virartexto(correcaoD))

  mover(correcaoE, correcaoD)
}


inicio
  enquanto (verdadeiro) farei {
    # verifica quando o sensor de cor 1 ou 4 veem PRETO 
    se ((cor(1) == "PRETO") e (cor(4) != "PRETO")) entao {
      frenterotacao(100, 3)
      # vira para a direita até encontrar PRETO com o sensor de cor 3
      enquanto (cor(3) != "PRETO") farei {
        direita(500)
      }
    } senao se ((cor(1) != "PRETO") e (cor(4) == "PRETO")) entao {
      frenterotacao(100, 3)
      # vira para a esquerda até encontrar PRETO com o sensor de cor 2
      enquanto (cor(2) != "PRETO") farei {
        esquerda(500)
      }
    }
    segueLinha()
  }
fim