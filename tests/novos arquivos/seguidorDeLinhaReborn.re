numero velocidadeFrenteSeguidor = 150

booleano viraEsquerda = falso
booleano viraDireita = falso
booleano travessa = falso

numero alinhamento = 0

booleano resgateConcluido = falso

numero horario = 12

tarefa segueLinha {
  se (cor(2) == "PRETO" e cor(3) == "PRETO") entao {
    frente(velocidadeFrenteSeguidor)
    esperar(25)
  }

  se (cor(2) == "BRANCO" e cor(3) == "BRANCO") entao {
    frente(velocidadeFrenteSeguidor)
    esperar(25)
  }

  se (cor(2) == "PRETO") entao {
    direita(750)
  }

  se (cor(3) == "PRETO") entao {
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

tarefa verificaCurva {
  se (cor(1) != "VERDE" e cor(2) != "VERDE" e cor(3) != "VERDE" e cor(4) != "VERDE") entao {
    se (cor(1) != "PRETO" e cor(4) != "PRETO") entao {
      enquanto (cor(1) != "PRETO" e cor(4) != "PRETO") farei {
        tras(150)
      }
      parar()
    }
  }

  se (cor(1) == "PRETO" e cor(4) == "PRETO") entao {
    travessa = verdadeiro
  } senao se ((cor(1) == "VERDE" ou cor(2) == "VERDE") e (cor(3) == "VERDE" ou cor(4) == "VERDE")) entao {
    travessa = verdadeiro
  } senao se (cor(1) == "PRETO" e cor(4) != "PRETO") entao {
    viraDireita = verdadeiro
  } senao se ((cor(1) == "VERDE" ou cor(2) == "VERDE") e (cor(3) != "VERDE" ou cor(4) != "VERDE")) entao {
    viraDireita = verdadeiro
  } senao se (cor(1) != "PRETO" e cor(4) == "PRETO") entao {
    viraEsquerda = verdadeiro
  } senao se ((cor(1) != "VERDE" ou cor(2) != "VERDE") e (cor(3) == "VERDE" ou cor(4) == "VERDE")) entao {
    viraEsquerda = verdadeiro
  }
}

tarefa alinhandoReto {
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


inicio
  se ((horario < 8) ou (16 < horario)) entao {
    ajustarcor(45)
  } senao se (((8 <= horario) e (horario < 11)) ou ((13 < horario) e (horario <= 16))) entao  {
    ajustarcor(35)
  } senao {
    ajustarcor(30)
  }

  velocidadeatuador(150)
  levantar(750)
  girarbaixo(1000)

  enquanto (verdadeiro) farei {
    se ((ultra(1) <= 10) e (cor(5) != "BRANCO")) entao {
      paradinha()
      alinhandoReto()
      paradinha()

      trasrotacao(300, 10)
      rotacionar(500, 30)
      enquanto (ultra(3) > 40) farei {
        frente(300)
      }
      enquanto (ultra(3) < 40 e cor(3) != "PRETO" e cor(4) != "PRETO") farei {
        frente(300)
      }
      paradinha()
      se (cor(1) == "PRETO" ou cor(2) == "PRETO" ou cor(3) == "PRETO" ou cor(4) == "PRETO") entao {
        frenterotacao(300, 15)
        rotacionar(500, 60)
        alinhandoReto()
        enquanto (toque(1) == falso) farei {
          tras(150)
        }

      } senao {
        rotacionar(500, negativo(60))
        enquanto (ultra(3) > 40) farei {
          frente(300)
        }
        enquanto (ultra(3) < 40) farei {
          frente(300)
        }
        frenterotacao(300, 13)
        rotacionar(500, 30)
        alinhandoReto()
        enquanto (toque(1) == falso) farei {
          tras(150)
        }
      }

    } senao {
      se (((cor(1) == "VERDE") ou (cor(2) == "VERDE")) ou ((cor(3) == "VERDE") ou (cor(4) == "VERDE"))) entao {
        paradinha()

        # verifica onde está
        verificaCurva()
        frenterotacao(300, 16)

        se (travessa) entao {
          trasrotacao(300, 7)
        } senao se (viraDireita) entao {
          rotacionar(500, 45)
          trasrotacao(300, 5)

          enquanto (cor(3) != "PRETO") farei {
            direita(1000)
          }
          enquanto (cor(2) != "PRETO") farei {
            esquerda(1000)
          }

        } senao se (viraEsquerda) entao {
          rotacionar(500, negativo(45))
          trasrotacao(300, 5)

          enquanto (cor(2) != "PRETO") farei {
            esquerda(1000)
          }
          enquanto (cor(3) != "PRETO") farei {
            direita(1000)
          }
        }

        viraEsquerda = falso
        viraDireita = falso
        travessa = falso

      } senao {
        se ((cor(1) == "PRETO") ou (cor(4) == "PRETO")) entao {
          paradinha()

          # verifica onde está
          verificaCurva()
          frenterotacao(300, 11)

          se (travessa) entao {
            trasrotacao(300, 5)
          } senao se (viraDireita) entao {
            rotacionar(500, 90)
            trasrotacao(300, 5)

            enquanto (cor(2) != "PRETO") farei {
              esquerda(1000)
            }
            enquanto (cor(3) != "PRETO") farei {
              direita(1000)
            }

          } senao se (viraEsquerda) entao {
            rotacionar(500, negativo(90))
            trasrotacao(300, 5)

            enquanto (cor(3) != "PRETO") farei {
              direita(1000)
            }
            enquanto (cor(2) != "PRETO") farei {
              esquerda(1000)
            }
          }

          viraEsquerda = falso
          viraDireita = falso
          travessa = falso

        } senao {
          se ((340 < inclinacao() e inclinacao() < 350) e (ultra(2) < 50 e ultra(3) < 50)) entao {
            velocidadeFrenteSeguidor = 250
            enquanto (inclinacao() != 0) farei {
              segueLinha()
            }
            frenterotacao(300, 3)
            parei()
          } senao se (((60 < corvermelha(2)) e (corvermelha(2) < 70)) e ((10 < corazul(2)) e (corazul(2) < 20)) e resgateConcluido) entao {
            frenterotacao(250, 5)
            parei()
          } senao {
            segueLinha()
          }
        }
      }
    }
  }
  
fim