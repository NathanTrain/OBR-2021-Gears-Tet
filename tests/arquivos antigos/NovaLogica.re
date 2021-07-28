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

inicio
  enquanto (verdadeiro) farei {
    # TODO: dentro da segunda verificação: 
    # caso fique muito tempo dentro do "NÃO tem preto na frente"
    # interrompe o ciclo e retorna à seguir linha normalmente 

    se (((cor(1) == "VERDE") ou (cor(2) == "VERDE")) ou ((cor(3) == "VERDE") ou (cor(4) == "VERDE"))) entao {
      trasrotacao(100, 3)

      enquanto (verdadeiro) farei {
        se ((cor(1) == "PRETO") ou (cor(4) == "PRETO")) entao {
          parar()
          esperar(500)
          se ((cor(1) == "PRETO") e (cor(4) == "PRETO")) entao {
            frenterotacao(100, 10)
          } senao se ((cor(1) == "PRETO") e (cor(4) != "PRETO")) entao {
            escrever(1, "encontrei preto na direita")

            frenterotacao(100, 11)

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
            trasrotacao(100, 8)

          } senao se ((cor(1) != "PRETO") e (cor(4) == "PRETO")) entao {
            escrever(1, "encontrei preto na esquerda")

            frenterotacao(100, 11)

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

            trasrotacao(100, 8)
          }
          interromper()
        } senao se (((cor(1) == "VERDE") ou (cor(2) == "VERDE")) ou ((cor(3) == "VERDE") ou (cor(4) == "VERDE"))) entao {
          # primeira verificação: BECO SEM SAÍDA
          # terceira verificação: curva verde à DIREITA
          # segunda verificação: curva verde à ESQUERDA
          se (((cor(1) == "VERDE") ou (cor(2) == "VERDE")) e ((cor(3) == "VERDE") ou (cor(4) == "VERDE"))) entao {
            escrever(3, "verde verde")
          
          } senao se (((cor(1) == "VERDE") ou (cor(2) == "VERDE")) e ((cor(3) != "VERDE") ou (cor(4) != "VERDE"))) entao {
            escrever(1, "encontrei verde na direita")

            frenterotacao(100, 16.4)

            direita(500)
            esperar(1000)

            enquanto ((cor(1) != "PRETO")) farei {
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

              trasrotacao(100, 5)
          } senao se (((cor(1) != "VERDE") ou (cor(2) != "VERDE")) e ((cor(3) == "VERDE") ou (cor(4) == "VERDE"))) entao {
            escrever(1, "encontrei verde na esquerda")

            frenterotacao(100, 16.4)

            esquerda(500)
            esperar(1000)

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

            trasrotacao(100, 5)
          }
          interromper()
        } senao {
          frente(25)
        }
      }

    } senao se ((cor(1) == "PRETO") ou (cor(4) == "PRETO")) entao {
      escrever(1, "encontrei preto")
      frenterotacao(100, 6)

      enquanto (verdadeiro) farei {
        direita(400)
        esperar(1000)

        parar()
        esperar(500)

        se ((cor(2) == "PRETO") ou (cor(3) == "PRETO") ou (cor(4) == "PRETO")) entao {
          escrever(1, "tem preto na frente")
          esquerda(400)
          esperar(1000)
          interromper()

        } senao {
          escrever(1, "NÃO tem preto na frente")

          esquerda(400)
          esperar(1000)

          trasrotacao(100, 8)

          enquanto (verdadeiro) farei {
            se ((cor(1) == "PRETO") e (cor(4) != "PRETO")) entao {
              escrever(1, "encontrei preto na direita")

              frenterotacao(100, 11)

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

              trasrotacao(100, 8)

              interromper()
            } senao se ((cor(1) != "PRETO") e (cor(4) == "PRETO")) entao {
              escrever(1, "encontrei preto na esquerda")

              frenterotacao(100, 11)

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
              trasrotacao(100, 8)

              interromper()
            } senao {
              segueLinha()
            }
          }

          interromper()
        }
      }
    }

    segueLinha()
    escrever(1, "seguindo") 
  }
fim