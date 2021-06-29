numero erro = 0
numero p = 0
numero i = 0
numero integral = 0
numero d = 0
numero lastErro = 0
numero correcaoE = 0
numero correcaoD = 0
numero velocidade = 100
numero calibracao = 30

tarefa segueLinha {
  erro =  (luz(2) + 30) - (luz(3) + 30)
  p = erro * 25
  integral = integral + erro
  i = integral * 0.0001
  d = (erro - lastErro) * 50
  lastErro = erro

  correcaoE = (velocidade + (p + i + d))
  correcaoD = (velocidade - (p + i + d))

  escrever(1, virartexto(correcaoE))
  escrever(2, virartexto(correcaoD))

  mover(correcaoE, correcaoD)
}

inicio
  enquanto (verdadeiro) farei {
    # verifica quando o sensor de cor 1 ou 4 veem PRETO ou VERDE
    se ((cor(1) == "PRETO") e (cor(4) == "PRETO")) entao {
      frenterotacao(100, 3)
    } senao se (((cor(1) == "VERDE") ou (cor(2) == "VERDE")) ou ((cor(3) == "VERDE") ou (cor(4) == "VERDE"))) entao {
      # primeira verificação: BECO SEM SAÍDA
      # segunda verificação: curva verde à ESQUERDA
      # terceira verificação: curva verde à DIREITA
      se (((cor(1) == "VERDE") ou (cor(2) == "VERDE")) e ((cor(3) == "VERDE") ou (cor(4) == "VERDE"))) entao {
        escrever(3, "verde verde")
      } senao se (((cor(1) == "VERDE") ou (cor(2) == "VERDE")) e ((cor(3) != "VERDE") ou (cor(4) != "VERDE"))) entao {
        frenterotacao(100, 5)
        direita(500)
        esperar(1000)
        enquanto ((cor(3) == "PRETO") ou (cor(4) == "PRETO")) farei {
          direita(500)
        }
      } senao se (((cor(1) != "VERDE") ou (cor(2) != "VERDE")) e ((cor(3) == "VERDE") ou (cor(4) == "VERDE"))) entao {
        frenterotacao(100, 5)
        esquerda(500)
        esperar(1000)
        enquanto ((cor(1) == "PRETO") ou (cor(2) == "PRETO")) farei {
          esquerda(500)
        }
      }
    } senao {
      # verificação para IMPEDIR de perder a linha
      se ((cor(1) == "PRETO") e (cor(4) != "PRETO")) entao {
        frenterotacao(100, 3)
        # vira para a direita até encontrar PRETO com o sensor de cor 3
        enquanto (cor(3) != "PRETO") farei {
          direita(700)
        }
      } senao se ((cor(1) != "PRETO") e (cor(4) == "PRETO")) entao {
        frenterotacao(100, 3)
        # vira para a esquerda até encontrar PRETO com o sensor de cor 2
        enquanto (cor(2) != "PRETO") farei {
          esquerda(700)
        }
      }
    }
    # caso nenhuma verificação seja verdadeira: 
    se ((inclinacao() <= 330) e (inclinacao() >= 10)) entao {
      velocidade = 150
    } senao {
      velocidade = 100
    }
    segueLinha()
  }
fim