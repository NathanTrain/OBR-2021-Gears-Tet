numero erro = 0
numero p = 0
numero i = 0
numero integral = 0
numero d = 0
numero lastErro = 0
numero PID = 0
numero correcaoE = 0
numero correcaoD = 0
numero velocidade = 125

booleano isLeft = falso
booleano isRight = falso


tarefa segueLinha {
  erro = (luz(2)) - (luz(3))
  p = erro * 50
  integral = integral + erro
  i = integral * 0.0001
  d = (erro - lastErro) * 100
  lastErro = erro

  PID = p + i + d

  correcaoE = (velocidade + PID)
  correcaoD = (velocidade - PID)

  mover(correcaoE, correcaoD)
}

tarefa parei {
  enquanto (verdadeiro) farei {
    parar()
  }
}

inicio
  enquanto (verdadeiro) farei {
    se (((cor(1) == "VERDE") ou (cor(2) == "VERDE")) ou ((cor(3) == "VERDE") ou (cor(4) == "VERDE"))) entao {
      
      parar()
      se (((cor(1) == "VERDE") ou (cor(2) == "VERDE")) e ((cor(3) == "VERDE") ou (cor(4) == "VERDE"))) entao {
        isRight = verdadeiro
        isLeft = verdadeiro
      } senao se ((cor(1) == "VERDE") ou (cor(2) == "VERDE") e ((cor(3) != "VERDE") e (cor(4) != "VERDE"))) entao {
        isRight = verdadeiro
        isLeft = falso
      } senao se ((cor(1) != "VERDE") e (cor(2) != "VERDE") e ((cor(3) == "VERDE") ou (cor(4) == "VERDE"))) entao {
        isRight = falso
        isLeft = verdadeiro
      }
      esperar(250)

      se ((isLeft == verdadeiro) e (isRight == verdadeiro)) entao {
        rotacionar(200, 180)
      } senao se ((isLeft == verdadeiro) e (isRight == falso)) entao {
        frenterotacao(100, 14)
        rotacionar(500, negativo(20))
        farei {
          esquerda(500)
        } enquanto (cor(2) != "PRETO")
      } senao se ((isLeft == falso) e (isRight == verdadeiro)) entao {
        frenterotacao(100, 14)
        rotacionar(500, 20)
        farei {
          direita(500)
        } enquanto (cor(3) != "PRETO")
      }
      trasrotacao(100, 4)
      isLeft = falso
      isRight = falso
    } senao se ((cor(1) == "PRETO") ou (cor(4) == "PRETO")) entao {
      
      parar()
      se ((cor(1) == "PRETO") e (cor(4) == "PRETO")) entao {
        isRight = verdadeiro
        isLeft = verdadeiro
      } senao se ((cor(1) == "PRETO") e (cor(4) != "PRETO")) entao {
        isRight = verdadeiro
        isLeft = falso
      } senao se ((cor(1) != "PRETO") e (cor(4) == "PRETO")) entao {
        isRight = falso
        isLeft = verdadeiro
      }
      esperar(250)

      se ((isLeft == verdadeiro) e (isRight == verdadeiro)) entao {
        frenterotacao(100, 3)
      } senao se ((isLeft == verdadeiro) e (isRight == falso)) entao {
        frenterotacao(100, 12)
        rotacionar(500, negativo(90))
        trasrotacao(100, 8)
      } senao se ((isLeft == falso) e (isRight == verdadeiro)) entao {
        frenterotacao(100, 12)
        rotacionar(500, 90)
        trasrotacao(100, 8)
      }

      isLeft = falso
      isRight = falso
    }
    segueLinha()
  }  
fim