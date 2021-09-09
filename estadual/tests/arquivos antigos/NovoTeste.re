# DEFINIÇÕES DO SEGUIDOR DE LINHA PID
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

# HORÁRIO DESCRITO EM NUMERO COM VÍRGULA
#   => o número inteiro é a hora (12:00 será 12)
#   => o número após o ponto será os minutos, porém descritos como uma fração
#      do horário (9:30 será 9.5; 10:45 será 10.75; e assim por diante)
numero horario = 12

tarefa segueLinha {

  # TODO => verificar novamente quais horários causam problemas (testar em RAMPA)
  #         --> (RESOLVIDO DIFERENTE) 10h foi encontrado problema de uma pequena
  #             diferença entre os sensores quando SUBINDO EM RAMPA
  #             (em ambas as direções) 

  # VERIFICA O HORÁRIO DO DIA PARA CORRIGIR CASO HAJA SOMBRA
  # E DEFINE O ERRO COM BASE NA CORREÇÃO
  se (((7 < horario) e (horario < 7.75)) ou ((16.25 < horario) e (horario < 17.25)) ) entao {
    se ( (75 < direcao()) e (direcao() < 105) ) entao {
        erro = (((luz(2) - luz(3)) - 25) * calibracao)
    } senao se ( (255 < direcao()) e (direcao() < 285) ) entao {
        erro = (((luz(2) - luz(3)) + 25) * calibracao)
    } senao {
        erro = ((luz(2) - luz(3)) * calibracao)
    }
  } senao {
    erro = ((luz(2) - luz(3)) * calibracao)
  }
  escrevernumero(1, erro)
  # DEFININDO VALORES DO PID
  p = erro * 50
  integral = integral + erro
  i = integral * 0.0001
  d = (erro - lastErro) * 100
  lastErro = erro

  PID = p + i + d

  # CORRIGINDO A MOVIMENTAÇÃO
  correcaoE = (velocidade + PID)
  correcaoD = (velocidade - PID)

  mover(correcaoE, correcaoD)
}

# tarefa para debug somente
tarefa parei {
  enquanto (verdadeiro) farei {
    parar()
  }
}

inicio
  # CALIBRAÇÃO DA COR
  ajustarcor(30)

  enquanto (verdadeiro) farei {
    # EXPLICAÇÃO DAS VERIFICAÇÕES
    #   1a verificação obstaculo
    #   2a verificação cores => 
    #     verde nos sensores 1 2 3 e 4
    #     preto nos sensores 1 e 4
    #     segue linha

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
              rotacionar(500, negativo(4))

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
            se ((cor(2) == "PRETO") ou (cor(3) == "PRETO")) entao {
              escrever(2, "achei preto na frente")
              rotacionar(500, 4)
              interromper()

            } senao {
              escrever(2, "NÃO achei preto na frente")
              rotacionar(500, negativo(4))

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

      se ((15 < inclinacao()) e (inclinacao() < 345)) entao {
        velocidade = 100
        se ((cor(2) == "BRANCO") e (cor(3) == "BRANCO")) entao {
          escrever(3, "branco branco subindo")
          frente(velocidade)
        } senao {
          escrever(3, "seguindo subindo")
          segueLinha()
        }
      } senao se ((((0 <= direcao()) e (direcao() < 7)) ou ((353 < direcao()) e (direcao() <= 360))) ou ((83 < direcao()) e (direcao() < 97)) ou ((173 < direcao()) e (direcao() < 187)) ou ((263 < direcao()) e (direcao() < 277))) entao {
        velocidade = 125
        se ((cor(2) == "BRANCO") e (cor(3) == "BRANCO")) entao {
          escrever(3, "branco branco quando reto")
          frente(velocidade)
        } senao {
          escrever(3, "seguindo quando reto")
          segueLinha()
        }
      } senao {
        velocidade = 125
        escrever(3, "seguindo normal")
        segueLinha()
      }
    }
  }  
fim