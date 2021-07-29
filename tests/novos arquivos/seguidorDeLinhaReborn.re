booleano viraEsquerda = falso
booleano viraDireita = falso
booleano travessa = falso


numero horario = 12

tarefa segueLinha {
  se (cor(2) == "PRETO" e cor(3) == "PRETO") entao {
    frente(150)
    esperar(25)
  }

  se (cor(2) == "BRANCO" e cor(3) == "BRANCO") entao {
    frente(150)
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
      parei()

      # TODO => fazer diagonalmente o desvio do robô

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
            trasrotacao(300, 7)
          } senao se (viraDireita) entao {
            rotacionar(500, 90)
            trasrotacao(300, 7)

            enquanto (cor(2) != "PRETO") farei {
              esquerda(1000)
            }
            enquanto (cor(3) != "PRETO") farei {
              direita(1000)
            }

          } senao se (viraEsquerda) entao {
            rotacionar(500, negativo(90))
            trasrotacao(300, 7)

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
          segueLinha()
        }
      }
    }
  }
  
fim