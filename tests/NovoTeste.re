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

numero calibracao = 0.6

numero horario = 7.5

tarefa segueLinha {
  # verifica o HORÁRIO DO DIA para saber como CORRIGIR a sombra
  se ( ((horario > 7) e (horario < 7.75)) ou ((horario > 16.25) e (horario < 17.25)) ) entao {
    se ( (direcao() > 75) e (direcao() < 105) ) entao {
      erro = (((luz(2) - luz(3)) - 25) * calibracao)
    } senao se ( (direcao() > 255) e (direcao() < 285) ) entao {
      erro = (((luz(2) - luz(3)) + 25) * calibracao)
    } senao {
      erro = ((luz(2) - luz(3)) * calibracao)
    }
  } senao {
    erro = ((luz(2) - luz(3)) * calibracao)
  }
  escrevernumero(1, erro)
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
  ajustarcor(25)

  # TODO => remover comentários 
  # TODO => adicionar verificação para quando estiver em rampa (subindo e descendo)
  # TODO => adicionar verificação para, em determinada hora do dia, calibrar melhor
  # TODO => quando direcao() estiver ~90 e ~270 usar verificação com BRANCO/BRANCO
  #         para seguir linha (e não ver sombra com o gap)

  # ideia para detectar que está na ÁREA DE RESGATE
  #   => ultra(2) < 33 e ultra(3) < 33 e inclinação <= 345
  #       => se ultra(1) < 500 --> chegou na ÁREA DE RESGATE

  enquanto (verdadeiro) farei {
    # 1a verificação obstaculo
    # 2a verificação cores => 
      # verde nos sensores 1 2 3 e 4
      # preto nos sensores 1 e 4
      # segue linha

    se ((ultra(1) <= 10) e (cor(5) != "BRANCO")) entao {
      escrever(1, "encontrei um obstaculo")

      rotacionar(500, 90)
      frenterotacao(200, 16)
      rotacionar(500, negativo(90))

      enquanto (ultra(3) > 10) farei {
        frente(200)
      }
      enquanto (ultra(3) < 10) farei {
        frente(200)
      }
      frenterotacao(200, 15)
      rotacionar(500, negativo(90))

      enquanto ((cor(1) == "PRETO") ou (cor(2) == "PRETO") ou (cor(3) == "PRETO") ou (cor(4) == "PRETO")) farei {
        frente(100)
      }

      frenterotacao(100, 16)
      rotacionar(500, 45)

      enquanto (cor(2) != "PRETO") farei {
        direita(500)
      }
    } senao {
      se (((cor(1) == "VERDE") ou (cor(2) == "VERDE")) ou ((cor(3) == "VERDE") ou (cor(4) == "VERDE"))) entao {
        escrever(1, "verde")
        parar()
        esperar(250)
        se (((cor(1) == "VERDE") ou (cor(2) == "VERDE")) e ((cor(3) == "VERDE") ou (cor(4) == "VERDE"))) entao {
          escrever(1, "verde com verde")
          rotacionar(200, 180)
        } senao se ((cor(1) == "VERDE") ou (cor(2) == "VERDE") e ((cor(3) != "VERDE") e (cor(4) != "VERDE"))) entao {
          escrever(1, "achei verde na direita")
          frenterotacao(100, 14)
          rotacionar(500, 20)
          enquanto (cor(3) != "PRETO") farei {
            escrever(2, "procurando preto...")
            direita(750)
          }
        } senao se ((cor(1) != "VERDE") e (cor(2) != "VERDE") e ((cor(3) == "VERDE") ou (cor(4) == "VERDE"))) entao {
          escrever(1, "achei verde na esquerda")
          frenterotacao(100, 14)
          rotacionar(500, negativo(20))
          enquanto (cor(2) != "PRETO") farei {
            escrever(2, "procurando preto...")
            esquerda(750)
          }
        }
        trasrotacao(100, 4)
        limparconsole()
      } senao se ((cor(1) == "PRETO") ou (cor(4) == "PRETO")) entao {
        parar()
        esperar(500)
        # preto e preto
        # preto DIREITA
        # preto ESQUERDA
        se ((cor(1) == "PRETO") e (cor(4) == "PRETO")) entao {
          escrever(1, "preto nos dois")
          frenterotacao(100, 3)
        } senao se ((cor(1) == "PRETO") e (cor(4) != "PRETO")) entao {
          escrever(1, "preto direita")
          frenterotacao(100, 3)
          rotacionar(500, 4)

          enquanto (verdadeiro) farei {
            se ((cor(2) == "PRETO") ou (cor(3) == "PRETO")) entao {
              escrever(2, "achei preto na frente")
              rotacionar(500, negativo(4))
              interromper()

            } senao {
              escrever(2, "NÃO achei na frente")
              rotacionar(500, negativo(8))

              frenterotacao(100, 8)
              rotacionar(500, 90)
              trasrotacao(100, 6)

              enquanto (cor(2) != "PRETO") farei {
                escrever(2, "virando esquerda...")
                esquerda(250)
              }
              enquanto (cor(3) != "PRETO") farei {
                direita(250)
              }
              limparlinha(2)
              interromper()
            }
          }
        } senao se ((cor(1) != "PRETO") e (cor(4) == "PRETO")) entao {
          escrever(1, "preto esquerda")
          frenterotacao(100, 3)
          rotacionar(500, 4)

          enquanto (verdadeiro) farei {
            rotacionar(500, negativo(8))
            se ((cor(2) == "PRETO") ou (cor(3) == "PRETO")) entao {
              escrever(2, "achei preto na frente")
              rotacionar(500, 4)
              interromper()

            } senao {
              escrever(2, "NÃO achei preto na frente")
              rotacionar(500, 8)

              frenterotacao(100, 8)
              rotacionar(500, negativo(90))
              trasrotacao(100, 6)

              enquanto (cor(3) != "PRETO") farei {
                escrever(2, "virando direita...")
                direita(250)
              }
              enquanto (cor(2) != "PRETO") farei {
                esquerda(250)
              }

              limparlinha(2)
              interromper()
            }
          }
        }
        limparconsole()
      }
      segueLinha()
    }
  }  
fim