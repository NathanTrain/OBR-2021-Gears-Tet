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
    se ((cor(1) == "PRETO") e (cor(4) == "PRETO")) entao {
      escrever(3, "preto preto")
    } senao {
      se ((cor(1) == "PRETO") e (cor(4) != "PRETO")) entao {
        escrever(1, "encontrei preto na direita")
        frenterotacao(100, 11)
        # vira a DIREITA até encontrar PRETO com os sensores 3 e 4
        enquanto ((cor(3) != "PRETO") e (cor(4) != "PRETO")) farei {
          direita(500)
        }

        escrever(1, "achei preto")
        escrever(2, "voltarei a seguir linha")
        # retorna levemente antes de voltar a seguir linha
        trasrotacao(100, 5)

      } senao se ((cor(1) != "PRETO") e (cor(4) == "PRETO")) entao {
        escrever(1, "encontrei preto na esquerda")
        frenterotacao(100, 11)
        # vira a ESQUERDA até encontrar PRETO com os sensores 1 e 2
        enquanto ((cor(1) != "PRETO") e (cor(2) != "PRETO")) farei {
          esquerda(500)
        }
        escrever(1, "achei preto")
        escrever(2, "voltarei a seguir linha")
        # retorna levemente antes de voltar a seguir linha
        trasrotacao(100, 5)
      }
    }

    segueLinha()
    limparconsole()
  }
fim