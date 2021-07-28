numero alinhamento = 0

booleano travessia = falso
booleano pretoEsquerda = falso
booleano pretoDireita = falso

tarefa segueLinha {
  se (cor(2) == "PRETO" e cor(4) == "PRETO") entao {
    frente(125)
    esperar(25)
  }

  se (cor(2) == "BRANCO" e cor(4) == "BRANCO") entao {
    frente(125)
    esperar(25)
  }

  se (cor(2) == "PRETO") entao {
    direita(750)
    esperar(75)
  }

  se (cor(4) == "PRETO") entao {
    esquerda(750)
    esperar(75)
  }
}

tarefa alinhandoRetoSempre {
  se ((0 < direcao()) e (direcao() < 45)) entao {
    alinhamento = negativo(direcao())
  } senao se ((315 < direcao()) e (direcao() < 359)) entao {
    alinhamento = 360 - direcao()
  } senao se ((45 < direcao()) e (direcao() <= 90)) entao {
    alinhamento = 90 - direcao()
  } senao se ((90 <= direcao()) e (direcao() < 135)) entao {
    alinhamento = negativo((direcao() - 90))
  } senao se ((135 < direcao()) e (direcao() <= 180)) entao {
    alinhamento = 180 - direcao()
  } senao se ((180 <= direcao()) e (direcao() < 225)) entao {
    alinhamento = negativo((direcao() - 180))
  } senao se ((225 < direcao()) e (direcao() <= 270)) entao {
    alinhamento = 270 - direcao()
  } senao se ((270 <= direcao()) e (direcao() < 315)) entao {
    alinhamento = negativo((direcao() - 270))
  }
  rotacionar(500, arredondar(alinhamento))
}

tarefa alinhandoEsquerda {
  enquanto (cor(2) != "PRETO") farei {
    esquerda(750)
  }
  enquanto (cor(3) != "PRETO") farei {
    direita(750)
  }
}
tarefa alinhandoDireita {
  enquanto (cor(3) != "PRETO") farei {
    direita(750)
  }
  enquanto (cor(2) != "PRETO") farei {
    esquerda(750)
  }
}

tarefa paradinha {
  parar()
  esperar(250)
}

tarefa parei {
  enquanto (verdadeiro) farei {
    parar()
  }
}



inicio
  
  velocidadeatuador(150)
  levantar(750)
  girarbaixo(750)

  trasrotacao(300, 7)

  enquanto (verdadeiro) farei {

    se ((ultra(1) <= 10) e (cor(6) != "BRANCO")) entao {

      paradinha()
      alinhandoRetoSempre()
      paradinha()

      rotacionar(500, 90)
      enquanto (ultra(3) < 20) farei {
        frente(300)
      }
      frenterotacao(300, 10)
      rotacionar(500, negativo(90))

      enquanto (ultra(3) > 20) farei {
        frente(300)
      }
      enquanto (ultra(3) < 20) farei {
        frente(300)
      }
      frenterotacao(300, 12)
      rotacionar(500, negativo(90))

      enquanto (ultra(3) > 50) farei {
        frente(300)
      }
      frenterotacao(300, 6.5)
      rotacionar(500, 45)

      enquanto (cor(4) != "PRETO") farei {
        direita(500)
      }
      alinhandoEsquerda()
      alinhandoRetoSempre()

      enquanto (toque(1) == falso) farei {
        tras(50)
      }
    } senao {
      se ((cor(1) == "VERDE" ou cor(2) == "VERDE") ou (cor(4) == "VERDE" ou cor(5) == "VERDE")) entao {
        paradinha()

          se ((cor(2) == "VERDE") e (cor(4) == "VERDE")) entao {
            alinhandoRetoSempre()
            rotacionar(500, 180)
            trasrotacao(300, 20)
            alinhandoRetoSempre()

          } senao se ((cor(2) == "VERDE") e (cor(4) != "VERDE")) entao {
            frenterotacao(300, 16)
            rotacionar(500, 45)
            enquanto (cor(4) != "PRETO") farei {
              direita(750)
            }
            trasrotacao(150, 7)

          } senao se ((cor(2) != "VERDE") e (cor(4) == "VERDE")) entao {
            frenterotacao(300, 16)
            rotacionar(500, negativo(45))
            enquanto (cor(2) != "PRETO") farei {
              esquerda(750)
            }
            trasrotacao(150, 7)

          } senao se ((cor(1) == "VERDE") e (cor(5) != "VERDE")) entao {
            frenterotacao(300, 16)
            rotacionar(500, 45)
            enquanto (cor(4) != "PRETO") farei {
              direita(750)
            }
            trasrotacao(150, 7)

          } senao se ((cor(1) != "VERDE") e (cor(5) == "VERDE")) entao {
            frenterotacao(300, 16)
            rotacionar(500, negativo(45))
            enquanto (cor(2) != "PRETO") farei {
              esquerda(750)
            }
            trasrotacao(150, 7)

          }

      } senao {
        se (corvermelha(1) < 45 ou corvermelha(5) < 45) entao {
          paradinha()

          se (cor(1) == "PRETO" e cor(5) == "PRETO") entao {
            travessia = verdadeiro
          } senao se (cor(1) == "PRETO" e cor(5) != "PRETO") entao {
            pretoDireita = verdadeiro
          } senao se (cor(1) != "PRETO" e cor(5) == "PRETO") entao {
            pretoEsquerda = verdadeiro
          }


          enquanto (verdadeiro) farei {
            frenterotacao(300, 5)
            se (travessia) entao {
              interromper()
            } senao {
              rotacionar(500, 3)
              se (cor(1) == "PRETO" ou cor(2) == "PRETO" ou cor(3) == "PRETO" ou cor(4) == "PRETO" ou cor(5) == "PRETO") entao {
                rotacionar(500, negativo(3))
                interromper()
              } senao {
                rotacionar(500, negativo(3))

                se (pretoEsquerda) entao {
                  frenterotacao(300, 8)
                  rotacionar(500, negativo(90))
                  trasrotacao(150, 8)
                  enquanto (cor(5) != "PRETO") farei {
                    direita(1000)
                  }
                  enquanto(cor(3) != "PRETO") farei {
                    esquerda(1000)
                  }

                } senao se (pretoDireita) entao {
                  frenterotacao(300, 8)
                  rotacionar(750, 90)
                  trasrotacao(150, 8)
                  enquanto (cor(1) != "PRETO") farei {
                    esquerda(1000)
                  }
                  enquanto(cor(3) != "PRETO") farei {
                    direita(1000)
                  }
                }

                interromper()
              }
            }
          }

          travessia = falso
          pretoEsquerda = falso
          pretoDireita = falso

        } senao {
          segueLinha()
        }
      }

    }

  }
  
fim