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

numero calibracao = 0.5

numero anguloAntigo = 0

booleano isLeft = falso
booleano isRight = falso

tarefa segueLinha {
  erro = ((luz(2) - luz(3)) * calibracao)
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
    # 1a verificação obstaculo
    # 2a verificação cores => 
      # verde nos sensores 1 2 3 e 4
      # preto nos sensores 1 e 4
      # segue linha

    se ((ultra(1) <= 10) e (cor(5) != "BRANCO")) entao {
      rotacionar(500, 90)
      frenterotacao(200, 16)
      rotacionar(500, negativo(90))

      enquanto (ultra(3) > 10) farei {
        frente(200)
      }
      enquanto (ultra(3) < 10) farei {
        frente(200)
      }
      frenterotacao(200, 10)
      rotacionar(500, negativo(90))
      
      enquanto ((cor(1) == "PRETO") ou (cor(2) == "PRETO") ou (cor(3) == "PRETO") ou (cor(4) == "PRETO")) farei {
        frente(100)
      }
      
      frenterotacao(100, 16)
      rotacionar(500, 45)
      enquanto ((cor(2) != "PRETO") e (cor(3) != "PRETO")) farei {
        direita(500)
      }
    } senao {
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
            esquerda(750)
          } enquanto (cor(2) != "PRETO")
        } senao se ((isLeft == falso) e (isRight == verdadeiro)) entao {
          frenterotacao(100, 14)
          rotacionar(500, 20)
          farei {
            direita(750)
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
          frenterotacao(100, 3)
          zerartemporizador()
          se (direcao() >= 340) entao {
            anguloAntigo = 360 - direcao()
          } senao {
            anguloAntigo = direcao()
          }
          escrevernumero(1, direcao())
          enquanto (verdadeiro) farei {
            se (cor(2) == "PRETO") entao {
              interromper()

            } senao se (temporizador() > 1000) entao {
              se (direcao() >= 340) entao {
                anguloAntigo = modulo(anguloAntigo - (direcao() - 360))
              } senao {
                anguloAntigo = modulo(anguloAntigo - direcao())
              }
              escrevernumero(2, direcao())
              escrevernumero(3, anguloAntigo)
              rotacionar(500, anguloAntigo)

              frenterotacao(100, 8)

              rotacionar(500, negativo(90))
              trasrotacao(100, 6)

              enquanto ((cor(2) != "PRETO") e (cor(3) != "PRETO")) farei {
                direita(250)
              }
              interromper()

            } senao {
              esquerda(500)
            }
          }

        } senao se ((isLeft == falso) e (isRight == verdadeiro)) entao {
          frenterotacao(100, 3)
          zerartemporizador()
          escrevernumero(1, direcao())
          se (direcao() >= 340) entao {
            anguloAntigo = 360 - direcao()
          } senao {
            anguloAntigo = direcao()
          }
          enquanto (verdadeiro) farei {
            se (cor(3) == "PRETO") entao {
              interromper()

            } senao se (temporizador() > 1000) entao {
              se (direcao() >= 340) entao {
                anguloAntigo = modulo(anguloAntigo - (direcao() - 360))
              } senao {
                anguloAntigo = modulo(anguloAntigo - direcao())
              }
              escrevernumero(2, direcao())
              escrevernumero(3, anguloAntigo)
              rotacionar(500, negativo(anguloAntigo))

              frenterotacao(100, 8)

              rotacionar(500, 90)
              trasrotacao(100, 6)

              enquanto ((cor(2) != "PRETO") e (cor(3) != "PRETO")) farei {
                esquerda(250)
              }
              interromper()

            } senao {
              direita(500)
            }
          }
        }

        isLeft = falso
        isRight = falso
      }
      zerartemporizador()
      anguloAntigo = 0 
      segueLinha()
    }
  }  
fim