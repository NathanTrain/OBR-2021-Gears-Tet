numero erro = 0
numero p = 0
numero i = 0
numero integral = 0
numero d = 0
numero lastErro = 0
numero PID = 0
numero correcaoE = 0
numero correcaoD = 0
numero velocidade = 100

tarefa segueLinha {
  erro = (luz(2)) - (luz(3))
  p = erro * 25
  integral = integral + erro
  i = integral * 0.0001
  d = (erro - lastErro) * 50
  lastErro = erro

  PID = p + i + d

  correcaoE = (velocidade + PID)
  correcaoD = (velocidade - PID)

  mover(correcaoE, correcaoD)
}

inicio
  enquanto (verdadeiro) farei {
    # verifica quando o sensor de cor 1 ou 4 veem PRETO ou VERDE
    se ((cor(1) == "PRETO") ou (cor(4) == "PRETO")) entao {
      # TODO: verificar se há verde após a linha há verde
      # se houver: segue reto e dps segue linha
      # se não houver: nada acontece

      escrever(1, "Preto Preto")
      frenterotacao(100, 3)
    } senao se (((cor(1) == "VERDE") ou (cor(2) == "VERDE")) ou ((cor(3) == "VERDE") ou (cor(4) == "VERDE"))) entao {
      # primeira verificação: BECO SEM SAÍDA
      # segunda verificação: curva verde à ESQUERDA
      # terceira verificação: curva verde à DIREITA
      se (((cor(1) == "VERDE") ou (cor(2) == "VERDE")) e ((cor(3) == "VERDE") ou (cor(4) == "VERDE"))) entao {
        escrever(3, "verde verde")
      
      } senao se (((cor(1) == "VERDE") ou (cor(2) == "VERDE")) e ((cor(3) != "VERDE") ou (cor(4) != "VERDE"))) entao {
        escrever(1, "encontrei verde na direita")

        frenterotacao(100, 14)

        enquanto ((cor(1) != "PRETO") e (cor(2) != "PRETO")) farei {
          escrever(1, "preto 1?")
          direita(500)
        }

        enquanto (cor(4) != "PRETO") farei {
          escrever(1, "preto 4?")
          direita(500)
        }

        enquanto (cor(2) != "PRETO") farei {
          escrever(1, "preto 2?")
          esquerda(500)
        }

      } senao se (((cor(1) != "VERDE") ou (cor(2) != "VERDE")) e ((cor(3) == "VERDE") ou (cor(4) == "VERDE"))) entao {
        escrever(1, "encontrei verde na esquerda")

        frenterotacao(100, 14)

        enquanto ((cor(3) != "PRETO") e (cor(4) != "PRETO")) farei {
          escrever(1, "preto 4?")
          esquerda(500)
        }

        enquanto (cor(1) != "PRETO") farei {
          escrever(1, "preto 1?")
          esquerda(500)
        }

        enquanto (cor(3) != "PRETO") farei {
          escrever(1, "preto 3?")
          direita(500)
        }
      }
    } senao {
      # verificação para IMPEDIR de perder a linha
      se ((cor(1) == "PRETO") e (cor(4) != "PRETO")) entao {
        escrever(1, "encontrei preto na direita")
        frenterotacao(100, 9)

        # TODO: verificar quantos graus robo virou
        # se > 100 e < 260 => retorna até ser 90 ou 270 e retorna levemente
        # volta a verificar linha 

        enquanto (cor(4) != "PRETO") farei {
          direita(500)
        }

        trasrotacao(100, 8)

        enquanto (cor(1) != "PRETO") farei {
          esquerda(500)
        }
        enquanto (cor(3) != "PRETO") farei {
          direita(500)
        }

        escrever(1, "achei preto")

      } senao se ((cor(1) != "PRETO") e (cor(4) == "PRETO")) entao {
        escrever(1, "encontrei preto na esquerda")
        frenterotacao(100, 9)
        enquanto (cor(1) != "PRETO") farei {
          esquerda(500)
        }

        trasrotacao(100, 8)

        enquanto (cor(4) != "PRETO") farei {
          direita(500)
        }
        enquanto (cor(2) != "PRETO") farei {
          esquerda(500)
        }
        escrever(1, "achei preto")
      }
    }

    segueLinha()
    escrever(1, "seguindo")
  }
fim