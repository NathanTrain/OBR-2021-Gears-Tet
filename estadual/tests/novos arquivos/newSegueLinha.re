numero alinhamento = 0

tarefa alinhaRetoSempre {
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

tarefa alinhandoRetoParaPreto {
  se ((0 < direcao()) e (direcao() < 20)) entao {
    alinhamento = negativo(direcao())
  } senao se ((340 < direcao()) e (direcao() < 359)) entao {
    alinhamento = 360 - direcao()
  } senao se ((73 < direcao()) e (direcao() <= 90)) entao {
    alinhamento = 90 - direcao()
  } senao se ((90 <= direcao()) e (direcao() < 107)) entao {
    alinhamento = negativo((direcao() - 90))
  } senao se ((163 < direcao()) e (direcao() <= 180)) entao {
    alinhamento = 180 - direcao()
  } senao se ((180 <= direcao()) e (direcao() < 207)) entao {
    alinhamento = negativo((direcao() - 180))
  } senao se ((253 < direcao()) e (direcao() <= 270)) entao {
    alinhamento = 270 - direcao()
  } senao se ((270 <= direcao()) e (direcao() < 297)) entao {
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

  velocidadeatuador(1000)
  levantar(500)
  girarbaixo(500)

  enquanto (verdadeiro) farei {

    se ((cor(1) == "VERDE" ou cor(2) == "VERDE") ou (cor(3) == "VERDE" ou cor(4) == "VERDE")) entao {
      paradinha()

      se (cor(2) == "VERDE" e cor(3) == "VERDE") entao {
        frenterotacao(300, 15)
      } senao se (cor(2) == "VERDE" e cor(3) != "VERDE") entao {
        frenterotacao(300, 15)
        rotacionar(1000, 45)
        enquanto (cor(3) != "PRETO") farei {
          direita(750)
        }
        trasrotacao(300, 7)

      } senao se (cor(2) != "VERDE" e cor(3) == "VERDE") entao {
        frenterotacao(300, 15)
        rotacionar(1000, negativo(45))
        enquanto (cor(2) != "PRETO") farei {
          esquerda(750)
        }
        trasrotacao(300, 7)
      }

    } senao se ((cor(1) == "PRETO") ou (cor(4) == "PRETO")) entao {
      paradinha()
      trasrotacao(500, 1.2)

      se ((cor(1) == "PRETO") e (cor(4) == "PRETO")) entao {
        frenterotacao(200, 4)
      } senao se ((cor(1) == "PRETO") e (cor(4) != "PRETO")) entao {
        frenterotacao(200, 4)
        alinhandoRetoParaPreto()
        rotacionar(500, 4)

        enquanto (verdadeiro) farei {
          se ((cor(2) == "PRETO") ou (cor(3) == "PRETO")) entao {
            rotacionar(500, negativo(4))
            interromper()

          } senao {
            rotacionar(500, negativo(4))

            frenterotacao(200, 8)
            rotacionar(1000, 90)
            trasrotacao(200, 7)

            enquanto (cor(1) != "PRETO") farei {
              esquerda(750)
            }
            alinhandoDireita()
            interromper()
          }
        }
      } senao se ((cor(1) != "PRETO") e (cor(4) == "PRETO")) entao {
        frenterotacao(200, 4)
        alinhandoRetoParaPreto()
        rotacionar(500, 4)

        enquanto (verdadeiro) farei {
          se ((cor(2) == "PRETO") ou (cor(3) == "PRETO")) entao {
            rotacionar(500, negativo(4))
            interromper()

          } senao {
            rotacionar(500, negativo(4))

            frenterotacao(200, 8)
            rotacionar(1000, negativo(90))
            trasrotacao(200, 7)

            enquanto (cor(4) != "PRETO") farei {
              direita(750)
            }
            alinhandoEsquerda()
            interromper()
          }
        }
      }

    } senao {
      se (luz(2) < 30) entao {
        enquanto (luz(2) < 30) farei {
          direita(750)
        }
        frenterotacao(750, 1)

      } senao se (luz(3) < 30) entao {
        enquanto (luz(3) < 30) farei {
          esquerda(750)
        }
        frenterotacao(750, 1)

      } senao {
        se (2500 < temporizador() e temporizador() < 4000) entao {
          frente(200)
        } senao {
          frente(125)
        }
      }
    }

  }

fim