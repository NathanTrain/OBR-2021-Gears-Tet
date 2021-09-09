numero horario = 12

numero erro = 0
numero p = 0
numero i = 0
numero integral = 0
numero d = 0
numero lastErro = 0
numero PID = 0
numero correcaoE = 0
numero correcaoD = 0
numero velocidade = 250

numero reajuste = 0.6

numero velocidadeBranco = 200

numero alinhamento = 0

numero contagem = 1

numero contResgate = 0
numero contSaida = 0

numero tempoDeRetorno = 0
booleano temArea = falso
booleano vitimaProxima = falso

booleano saidaFrente = falso
booleano saidaDireita = falso
booleano saidaEsquerda = falso
booleano resgateFrente = falso
booleano resgateDireitaBaixo = falso
booleano resgateDireitaCima = falso

booleano saiuDaSala = falso

tarefa segueLinha {
  se (((7 < horario) e (horario < 7.75)) ou ((16.25 < horario) e (horario < 17.25)) ) entao {
    se ( (75 < direcao()) e (direcao() < 105) ) entao {
        erro = (((luz(2) - luz(3)) - 25) * reajuste)
    } senao se ( (255 < direcao()) e (direcao() < 285) ) entao {
        erro = (((luz(2) - luz(3)) + 25) * reajuste)
    } senao {
        erro = ((luz(2) - luz(3)) * reajuste)
    }
  } senao {
    erro = ((luz(2) - luz(3)) * reajuste)
  }

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

tarefa segueLinhaComBranco {
  se ((cor(2) == "BRANCO") e (cor(3) == "BRANCO")) entao {
    frente(velocidadeBranco)
  } senao {
    segueLinha()
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
  rotacionar(150, arredondar(alinhamento))
}

tarefa alinhaRetoParaPreto {
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
  rotacionar(150, arredondar(alinhamento))
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

tarefa atuadorEntregaVitima {
  baixar(200)
  velocidadeatuador(200)
  girarbaixo(750)
  esperar(500)
  girarcima(750)
  velocidadeatuador(100)
  levantar(200)
}

tarefa encontraPegaVitima {
  velocidadeatuador(100)

  se ((saidaDireita) e (resgateFrente)) entao {
    baixar(1200)

    # verificação vertical
    enquanto (verdadeiro) farei {
      alinhandoReto()
      # anda até ver vítima
      enquanto (verdadeiro) farei {
        se (temalgo(2, 0, 195)) entao {
          trasrotacao(125, 5)

          se (temalgo(2, 0, 40)) entao {
            vitimaProxima = verdadeiro
          }

          interromper()
        } senao {
          se ((ultra(2) > 300) e (ultra(1) > 248)) entao {
            interromper()
          } senao {
            tras(125)
          }
        }
      }
      paradinha()
      alinhandoReto()

      # verifica se chegou ao final da sala
      se ((ultra(2) > 300) e (ultra(1) > 248)) entao {
        interromper()
      }

      se (vitimaProxima) entao {
        levantar(400)

        rotacionar(500, 90)
        alinhandoReto()

        frenterotacao(250, 15)
        trasrotacao(250, 15)

        baixar(600)
        alinhandoReto()

        vitimaProxima = falso
      } senao {
        # vira 90°
        rotacionar(500, 90)
        alinhandoReto()
      }

      # segue até a parede
      alinhandoReto()
      zerartemporizador()
      enquanto (corverde(2) > 38) farei {
        se (ultra(1) < 30) entao {
          interromper()
        } senao se (temporizador() >= 8000) entao {
          interromper()
        } senao {
          frente(125)
        }
      }

      levantar(400)

      paradinha()

      # já está do outro lado da sala
      # retorna e segue para entregar vitima
      enquanto (toque(1) == falso) farei {
        se (temvitima()) entao {
          tras(250)
        } senao {
          tras(125)
        }
      }
      paradinha()
      frenterotacao(250, 15)
      alinhandoReto()

      rotacionar(500, negativo(90))
      alinhandoReto()

      se (temvitima()) entao {
        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        rotacionar(500, negativo(45))
        atuadorEntregaVitima()
        rotacionar(500, 45)

        alinhandoReto()
        trasrotacao(250, 15)
      }
      baixar(600)
    }

    frenterotacao(250, 5)
    rotacionar(500, 90)
    alinhandoReto()

    # verificação horizontal
    enquanto (verdadeiro) farei {
      alinhandoReto()

      # anda até ver vítima
      enquanto (verdadeiro) farei {
        se (temalgo(3, 0, 160)) entao {
          frenterotacao(125, 5)
          se (ultra(2) > 100) entao {
            temArea = verdadeiro
          }

          se (temalgo(3, 0, 40)) entao {
            vitimaProxima = verdadeiro
          }
          interromper()
        } senao {
          frente(125)
          se ((30 < corverde(2)) e (corverde(2) < 38)) entao {
            interromper()
          }
        }
      }
      paradinha()
      alinhandoReto()

      # verifica se chegou ao final da sala
      se ((30 < corverde(2)) e (corverde(2) < 38)) entao {
        interromper()
      }

      se (vitimaProxima) entao {
        levantar(400)

        rotacionar(500, negativo(90))
        alinhandoReto()

        frenterotacao(250, 15)
        trasrotacao(250, 15)

        baixar(500)
        alinhandoReto()

        se (temArea) entao {
          zerartemporizador()
          enquanto ((temporizador() < 5000) e (ultra(1) > 110)) farei {
            frente(125)
          }
        } senao {
          zerartemporizador()
          enquanto (ultra(1) > 35) farei {
            frente(125)
          }
        }

        vitimaProxima = falso

      } senao {
        # vira 90°
        rotacionar(500, negativo(90))
        alinhandoReto()

        # segue até a parede
        zerartemporizador()
        enquanto (ultra(1) > 35) farei {
          frente(125)
        }

      }

      frenterotacao(125, 2)
      levantar(400)
      # já está do outro lado da sala

      # se a área estiver na frente dele, entrega vitima
      se (temArea e temvitima()) entao {
        rotacionar(250, negativo(45))

        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        paradinha()

        atuadorEntregaVitima()
        rotacionar(250, 45)
        alinhandoReto()
      }

      se (temvitima()) entao {
        trasrotacao(125, 5)
        alinhandoReto()
        rotacionar(500, negativo(90))
        alinhandoReto()

        zerartemporizador()
        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        tempoDeRetorno = temporizador()

        rotacionar(500, 45)
        atuadorEntregaVitima()
        rotacionar(500, negativo(45))
        alinhandoReto()

        tras(250)
        esperar(tempoDeRetorno)

        rotacionar(500, 90)
        alinhandoReto()
      }

      se (temArea) entao {
        baixar(500)
        enquanto (ultra(1) > 235) farei {
          tras(350)
        }
      } senao {
        enquanto (toque(1) == falso) farei {
          tras(350)
        }
        alinhandoReto()
        frenterotacao(250, 5)
        baixar(500)
      }

      rotacionar(500, 90)
      temArea = falso
    }

    trasrotacao(250, 10)
    rotacionar(500, negativo(90))
    alinhandoReto()

    enquanto (toque(1) == falso) farei {
      tras(250)
    }
    frenterotacao(250, 10)

    rotacionar(500, 90)
    alinhandoReto()

    enquanto (38 < corverde(2)) farei {
      frente(250)
    }
    parar()

  } senao se ((saidaDireita) e (resgateDireitaCima)) entao {
    baixar(250)

    enquanto(ultra(1) > 30) farei {
      frente(125)
    }

    paradinha()

    se (temvitima()) entao {
      levantar(400)

      alinhandoReto()
      rotacionar(500, 90)
      alinhandoReto()

      temArea = verdadeiro

      enquanto (corvermelha(5) > 2) farei {
        frente(250)
      }
      parar()

      rotacionar(500, negativo(45))
      atuadorEntregaVitima()
      rotacionar(500, 45)
      alinhandoReto()

      enquanto (toque(1) == falso) farei {
        tras(250)
      }
      frenterotacao(250, 15)
      alinhandoReto()

      rotacionar(500, negativo(90))

      baixar(500)
    }

    trasrotacao(250, 5)
    # verificação vertical
    enquanto (verdadeiro) farei {
      alinhandoReto()
      # anda até ver vítima
      enquanto (verdadeiro) farei {
        se (temalgo(2, 0, 180)) entao {
          trasrotacao(125, 5)
          se (ultra(1) < 100) entao {
            temArea = verdadeiro
          }
          se (temalgo(2, 0, 40)) entao {
            vitimaProxima = verdadeiro
          }
          interromper()
        } senao {
          se ((ultra(2) > 300) e (ultra(1) > 248)) entao {
            interromper()
          } senao {
            tras(125)
          }
        }
      }
      paradinha()
      alinhandoReto()

      # verifica se chegou ao final da sala
      se ((ultra(2) > 300) e (ultra(1) > 248)) entao {
        interromper()
      }

      se (vitimaProxima) entao {
        levantar(400)

        rotacionar(500, 90)
        alinhandoReto()

        frenterotacao(250, 15)
        trasrotacao(250, 15)

        baixar(600)
        alinhandoReto()

        vitimaProxima = falso
      } senao {
        # vira 90°
        rotacionar(500, 90)
        alinhandoReto()
      }

      # segue até a parede
      alinhandoReto()
      zerartemporizador()
      enquanto (corverde(2) > 38) farei {
        se (ultra(1) < 30) entao {
          interromper()
        } senao se (temporizador() >= 8000) entao {
          interromper()
        } senao {
          frente(125)
        }
      }

      levantar(400)

      paradinha()

      # já está do outro lado da sala
      # retorna e segue para entregar vitima
      se (temvitima() == falso) entao {
        enquanto (toque(1) == falso) farei {
          tras(350)
        }
        alinhandoReto()
        frenterotacao(250, 10)
        rotacionar(500, negativo(90))
      } senao se (temvitima()) entao {
        trasrotacao(125, 10)
        alinhandoReto()
        rotacionar(500, negativo(90))
        alinhandoReto()

        zerartemporizador()
        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        tempoDeRetorno = temporizador()
        rotacionar(500, 45)
        atuadorEntregaVitima()
        rotacionar(500, negativo(45))
        alinhandoReto()

        tras(250)
        esperar(tempoDeRetorno)

        rotacionar(500, 90)
        alinhandoReto()

        enquanto (toque(1) == falso) farei {
          tras(250)
        }
        alinhandoReto()
        frenterotacao(250, 10)
        rotacionar(500, negativo(90))
      }
      baixar(600)
    }

    frenterotacao(250, 5)
    rotacionar(500, 90)
    alinhandoReto()

    # verificação horizontal
    enquanto (verdadeiro) farei {
      alinhandoReto()

      # anda até ver vítima
      enquanto (verdadeiro) farei {
        se (temalgo(3, 0, 160)) entao {
          frenterotacao(125, 5)
          se (temalgo(3, 175, 210)) entao {
            temArea = verdadeiro
          }
          se (temalgo(3, 0, 40)) entao {
            vitimaProxima = verdadeiro
          }
          interromper()
        } senao {
          frente(125)
          se ((30 < corverde(2)) e (corverde(2) < 38)) entao {
            interromper()
          }
        }
      }
      paradinha()
      alinhandoReto()

      # verifica se chegou ao final da sala
      se ((30 < corverde(2)) e (corverde(2) < 38)) entao {
        interromper()
      }

      se (vitimaProxima) entao {
        levantar(400)

        rotacionar(500, negativo(90))
        alinhandoReto()

        frenterotacao(250, 15)
        trasrotacao(250, 15)

        baixar(500)
        alinhandoReto()

        se (temArea) entao {
          zerartemporizador()
          enquanto ((temporizador() < 5000) e (ultra(1) > 110)) farei {
            frente(125)
          }
        } senao {
          zerartemporizador()
          enquanto (ultra(1) > 35) farei {
            frente(125)
          }
        }

        vitimaProxima = falso

      } senao {
        # vira 90°
        rotacionar(500, negativo(90))
        alinhandoReto()

        # segue até a parede
        zerartemporizador()
        enquanto (ultra(1) > 35) farei {
          frente(125)
        }

      }

      frenterotacao(125, 2)
      levantar(400)
      # já está do outro lado da sala

      # se a área estiver na frente dele, entrega vitima
      se (temArea e temvitima()) entao {
        rotacionar(250, 45)

        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        paradinha()

        atuadorEntregaVitima()
        rotacionar(250, negativo(45))
        alinhandoReto()
      }

      se (temvitima()) entao {
        trasrotacao(125, 5)
        alinhandoReto()
        rotacionar(500, 90)
        alinhandoReto()

        zerartemporizador()
        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        tempoDeRetorno = temporizador()

        rotacionar(500, negativo(45))
        atuadorEntregaVitima()
        rotacionar(500, 45)
        alinhandoReto()

        tras(250)
        esperar(tempoDeRetorno)

        rotacionar(500, negativo(90))
        alinhandoReto()
      }

      enquanto (toque(1) == falso) farei {
        tras(350)
      }
      alinhandoReto()
      frenterotacao(250, 5)
      baixar(500)

      rotacionar(500, 90)
      temArea = falso
    }

    # saindo pela área verde
    trasrotacao(250, 10)
    rotacionar(500, negativo(90))
    alinhandoReto()

    enquanto (toque(1) == falso) farei {
      tras(250)
    }
    frenterotacao(250, 10)

    rotacionar(500, 90)
    alinhandoReto()

    enquanto (38 < corverde(2)) farei {
      frente(250)
    }
    parar()

  } senao se ((saidaEsquerda) e (resgateDireitaBaixo)) entao {
    enquanto(ultra(1) > 30) farei {
      frente(125)
    }
    paradinha()

    se (temvitima()) entao {
      levantar(400)
      frente(250)
      esperar(500)

      alinhandoReto()
      rotacionar(500, negativo(90))
      alinhandoReto()

      enquanto (toque(1) == falso) farei {
        tras(125)
      }

      frenterotacao(125, 10)
      alinhandoReto()

      rotacionar(500, negativo(90))
      alinhandoReto()

      enquanto (corvermelha(5) > 2) farei {
        frente(250)
      }
      parar()
      alinhandoReto()

      rotacionar(500, negativo(45))
      atuadorEntregaVitima()
      rotacionar(500, 45)
      alinhandoReto()

      enquanto (toque(1) == falso) farei {
        tras(1000)
      }

      frenterotacao(250, 10)
      rotacionar(500, negativo(90))

      enquanto (ultra(2) < 300) farei {
        tras(250)
      }
      trasrotacao(250, 15)
      alinhandoReto()

      rotacionar(500, negativo(90))

      baixar(500)
    }

    # analisa verticalmente
    enquanto (verdadeiro) farei {
      alinhandoReto()

      # anda até ver vítima
      enquanto (verdadeiro) farei {
        se (temalgo(2, 0, 150)) entao {
          trasrotacao(125, 5)

          se (ultra(1) >= 175) entao {
            temArea = verdadeiro
          }

          se (temalgo(2, 0, 40)) entao {
            vitimaProxima = verdadeiro
          }

          interromper()
        } senao {
          tras(125)

          se (ultra(1) > 248) entao {
            interromper()
          }
        }
      }
      paradinha()
      alinhandoReto()

      # verifica se chegou ao final da sala
      se (ultra(1) > 248) entao {
        interromper()
      }

      se (vitimaProxima) entao {
        levantar(400)

        rotacionar(500, 90)
        alinhandoReto()

        frenterotacao(250, 15)
        trasrotacao(250, 15)

        baixar(500)
        alinhandoReto()

        se (temArea) entao {
          zerartemporizador()
          enquanto ((temporizador() < 5000) e (ultra(1) > 110)) farei {
            frente(125)
          }
        } senao {
          zerartemporizador()
          enquanto (ultra(1) > 35) farei {
            frente(125)
          }
        }

        vitimaProxima = falso

      } senao se (temArea) entao {
        # vira 90°
        rotacionar(500, 90)
        alinhandoReto()

        # segue até a area
        zerartemporizador()
        enquanto ((temporizador() < 6500) e (ultra(1) > 110)) farei {
          frente(125)
        }

      } senao {
        # vira 90°
        rotacionar(500, 90)
        alinhandoReto()

        # segue até a parede
        zerartemporizador()
        enquanto (ultra(1) > 35) farei {
          frente(125)
        }

      }

      frenterotacao(125, 2)
      levantar(400)
      # já está do outro lado da sala

      # se a área estiver na frente dele, entrega vitima
      se (temArea e temvitima()) entao {
        rotacionar(250, 45)

        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        paradinha()

        atuadorEntregaVitima()
        rotacionar(250, negativo(45))

        alinhandoReto()
        temArea = falso
      }
      
      se (temvitima()) entao {
        trasrotacao(125, 5)
        alinhandoReto()
        rotacionar(500, 90)
        alinhandoReto()

        zerartemporizador()
        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        tempoDeRetorno = temporizador()

        rotacionar(500, negativo(45))
        atuadorEntregaVitima()
        rotacionar(500, 45)
        alinhandoReto()

        tras(250)
        esperar(tempoDeRetorno)
        alinhandoReto()

        rotacionar(500, negativo(90))
        alinhandoReto()
      }
      enquanto (ultra(2) < 300) farei {
        tras(350)
      }
      alinhandoReto()
      trasrotacao(250, 15)

      rotacionar(500, negativo(90))
      alinhandoReto()
      baixar(500)
    }

    alinhandoReto()

    enquanto (ultra(1) > 32) farei {
      frente(1000)
    }
    rotacionar(500, 90)

    # analisa horizontalmente
    enquanto (verdadeiro) farei {
      alinhandoReto()

      # anda até ver vítima
      enquanto (verdadeiro) farei {
        se (temalgo(2, 0, 150)) entao {
          frenterotacao(125, 5)

          se (ultra(1) < 90) entao {
            temArea = verdadeiro
          }

          se (temalgo(2, 0, 40)) entao {
            vitimaProxima = verdadeiro
          }

          interromper()
        } senao {
          frente(125)

          se (ultra(1) <= 30) entao {
            interromper()
          }
        }
      }
      paradinha()
      alinhandoReto()

      # verifica se saiu da sala de resgate
      se (ultra(1) <= 30) entao {
        interromper()
      } 
      
      se (vitimaProxima) entao {
        levantar(400)

        rotacionar(500, 90)
        alinhandoReto()

        frenterotacao(250, 15)
        trasrotacao(250, 15)

        baixar(500)
        alinhandoReto()

        se (temArea) entao {
          zerartemporizador()
          enquanto ((temporizador() < 5000) e (ultra(1) > 110)) farei {
            frente(125)
          }
        } senao {
          zerartemporizador()
          enquanto (ultra(1) > 35) farei {
            frente(125)
          }
        }

        vitimaProxima = falso

      } senao se (temArea) entao {
        # vira 90°
        rotacionar(500, 90)
        alinhandoReto()

        # segue até a area
        zerartemporizador()
        enquanto ((temporizador() < 5000) e (ultra(1) > 110)) farei {
          frente(125)
        }

      } senao {
        # vira 90°
        rotacionar(500, negativo(90))
        alinhandoReto()

        # segue até a parede
        zerartemporizador()
        enquanto ((ultra(1) < 300) e (ultra(1) > 35)) farei {
          frente(125)
        }

      }

      frenterotacao(125, 2)
      levantar(400)
      # já está do outro lado da sala

      # se a área estiver na frente dele, entrega vitima
      se (temArea e temvitima()) entao {
        rotacionar(250, negativo(45))

        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        paradinha()

        atuadorEntregaVitima()
        rotacionar(250, 45)

        alinhandoReto()
        temArea = falso
      }

      se (temvitima() == falso) entao {
        enquanto (ultra(2) < 300) farei {
          tras(350)
        }
        trasrotacao(250, 15)
        alinhandoReto()
        rotacionar(250, negativo(90))

      } senao se (temvitima()) entao {
        trasrotacao(125, 5)
        alinhandoReto()
        rotacionar(500, negativo(90))
        alinhandoReto()

        zerartemporizador()
        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        tempoDeRetorno = temporizador()

        rotacionar(500, 45)
        atuadorEntregaVitima()
        rotacionar(500, negativo(45))
        alinhandoReto()

        tras(250)
        esperar(tempoDeRetorno)

        rotacionar(500, 90)
        alinhandoReto()

        enquanto (toque(1) == falso) farei {
          tras(250)
        }
        frenterotacao(250, 5)
        alinhandoReto()
        rotacionar(500, negativo(90))
      }
      baixar(500)
    }

    se (temvitima()) entao {
      levantar(400)
      trasrotacao(125, 5)

      rotacionar(500, 90)
      alinhandoReto()

      enquanto (corvermelha(5) > 2) farei {
        frente(250)
      }

      rotacionar(500, negativo(45))
      atuadorEntregaVitima()
      rotacionar(500, 45)

      enquanto (toque(1) == falso) farei {
        tras(1000)
      }

      alinhandoReto()
      frenterotacao(500, 15)
      rotacionar(500, 90)
      alinhandoReto()
    }

    # sai pela área verde
    trasrotacao(500, 15)
    alinhandoReto()

    levantar(600)
    girarbaixo(750)

    rotacionar(500, 90)
    alinhandoReto()

    enquanto (toque(1) == falso) farei {
      tras(250)
    }

    frenterotacao(125, 10)
    alinhandoReto()

    rotacionar(500, 90)
    alinhandoReto()

    enquanto (38 < corverde(2)) farei {
      frente(250)
    }
    parar()

    trasrotacao(250, 10)
    rotacionar(500, negativo(90))

    enquanto (toque(1) == falso) farei {
      tras(250)
    }

    frenterotacao(125, 10)
    alinhandoReto()

    rotacionar(500, 90)
    alinhandoReto()

    enquanto (38 < corverde(2)) farei {
      frente(250)
    }
    parar()

    alinhandoReto()

  } senao se ((saidaEsquerda) e (resgateDireitaCima)) entao {
    enquanto(ultra(1) > 30) farei {
      frente(125)
    }
    paradinha()
    se (temvitima()) entao {
      levantar(400)

      alinhandoReto()
      rotacionar(500, 90)
      alinhandoReto()

      temArea = verdadeiro

      enquanto (corvermelha(5) > 2) farei {
        frente(250)
      }
      parar()

      rotacionar(500, negativo(45))
      atuadorEntregaVitima()
      rotacionar(500, 45)
      alinhandoReto()

      enquanto (ultra(2) < 300) farei {
        tras(250)
      }
      trasrotacao(250, 15)
      alinhandoReto()

      rotacionar(500, negativo(90))

      baixar(500)
    }

    # analisa verticalmente
    enquanto (verdadeiro) farei {
      alinhandoReto()

      # anda até ver vítima
      enquanto (verdadeiro) farei {
        se (temalgo(2, 0, 150)) entao {
          trasrotacao(125, 5)

          se (ultra(1) < 90) entao {
            temArea = verdadeiro
          }

          se (temalgo(2, 0, 40)) entao {
            vitimaProxima = verdadeiro
          }

          interromper()
        } senao {
          tras(125)

          se (ultra(1) > 248) entao {
            interromper()
          }
        }
      }
      paradinha()
      alinhandoReto()

      # verifica se chegou ao final da sala
      se (ultra(1) > 248) entao {
        interromper()
      }

      se (vitimaProxima) entao {
        levantar(400)

        rotacionar(500, 90)
        alinhandoReto()

        frenterotacao(250, 15)
        trasrotacao(250, 15)

        baixar(500)
        alinhandoReto()

        se (temArea) entao {
          zerartemporizador()
          enquanto ((temporizador() < 5000) e (ultra(1) > 110)) farei {
            frente(125)
          }
        } senao {
          zerartemporizador()
          enquanto (ultra(1) > 35) farei {
            frente(125)
          }
        }

        vitimaProxima = falso

      } senao se (temArea) entao {
        # vira 90°
        rotacionar(500, 90)
        alinhandoReto()

        # segue até a area
        zerartemporizador()
        enquanto ((temporizador() < 6500) e (ultra(1) > 110)) farei {
          frente(125)
        }

      } senao {
        # vira 90°
        rotacionar(500, 90)
        alinhandoReto()

        # segue até a parede
        zerartemporizador()
        enquanto (ultra(1) > 35) farei {
          frente(125)
        }

      }

      frenterotacao(125, 2)
      levantar(400)
      # já está do outro lado da sala

      # se a área estiver na frente dele, entrega vitima
      se (temArea e temvitima()) entao {
        rotacionar(250, negativo(45))

        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        paradinha()

        atuadorEntregaVitima()
        rotacionar(250, 45)
        alinhandoReto()
      }

      se (temvitima()) entao {
        trasrotacao(125, 5)
        alinhandoReto()
        rotacionar(500, negativo(90))
        alinhandoReto()

        zerartemporizador()
        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        tempoDeRetorno = temporizador()
        rotacionar(500, 45)
        atuadorEntregaVitima()
        rotacionar(500, negativo(45))
        alinhandoReto()

        tras(250)
        esperar(tempoDeRetorno)

        rotacionar(500, 90)
        alinhandoReto()
      }

      # retorna
      se (temArea) entao {
        enquanto (ultra(2) < 300) farei {
          tras(350)
        }
        alinhandoReto()
        tras(250)
        esperar(750)
      } senao {
        enquanto (toque(1) == falso) farei {
          tras(250)
        }
        frenterotacao(250, 10)
        alinhandoReto()
      }

      rotacionar(500, negativo(90))
      alinhandoReto()
      baixar(500)
      temArea = falso
    }

    rotacionar(500, 90)

    # analisa horizontalmente
    enquanto (verdadeiro) farei {
      alinhandoReto()

      # anda até ver vítima
      enquanto (verdadeiro) farei {
        se (temalgo(3, 0, 150)) entao {
          frenterotacao(125, 5)

          se (ultra(1) < 90) entao {
            temArea = verdadeiro
          }

          se (temalgo(3, 0, 40)) entao {
            vitimaProxima = verdadeiro
          }

          interromper()
        } senao {
          frente(125)

          se (ultra(1) <= 30) entao {
            interromper()
          }
        }
      }
      paradinha()
      alinhandoReto()

      # verifica se saiu da sala de resgate
      se (ultra(1) <= 30) entao {
        interromper()
      } 
      
      se (vitimaProxima) entao {
        levantar(400)

        rotacionar(500, negativo(90))
        alinhandoReto()

        frenterotacao(250, 15)
        trasrotacao(250, 15)

        baixar(500)
        alinhandoReto()

        se (temArea) entao {
          zerartemporizador()
          enquanto ((temporizador() < 5000) e (ultra(1) > 110)) farei {
            frente(125)
          }
        } senao {
          zerartemporizador()
          enquanto (ultra(1) > 35) farei {
            frente(125)
          }
        }

        vitimaProxima = falso

      } senao se (temArea) entao {
        # vira 90°
        rotacionar(500, negativo(90))
        alinhandoReto()

        # segue até a area
        zerartemporizador()
        enquanto ((temporizador() < 5000) e (ultra(1) > 110)) farei {
          frente(125)
        }

      } senao {
        # vira 90°
        rotacionar(500, negativo(90))
        alinhandoReto()

        # segue até a parede
        zerartemporizador()
        enquanto (ultra(1) > 35) farei {
          frente(125)
        }

      }

      frenterotacao(125, 2)
      levantar(400)
      # já está do outro lado da sala

      # se a área estiver na frente dele, entrega vitima
      
      se (temArea e temvitima()) entao {
        rotacionar(250, 45)

        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        paradinha()

        atuadorEntregaVitima()
        rotacionar(250, negativo(45))
        alinhandoReto()
        temArea = falso
      }

      se (temvitima() == falso) entao {
        enquanto (toque(1) == falso) farei {
          tras(350)
        }
        alinhandoReto()
        frenterotacao(250, 3)
        rotacionar(250, 90)
      } senao se (temvitima()) entao {
        trasrotacao(125, 5)
        alinhandoReto()
        rotacionar(500, 90)
        alinhandoReto()

        zerartemporizador()
        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        tempoDeRetorno = temporizador()

        rotacionar(250, negativo(45))
        atuadorEntregaVitima()
        rotacionar(500, 45)
        alinhandoReto()

        tras(250)
        esperar(tempoDeRetorno)

        rotacionar(500, negativo(90))
        alinhandoReto()

        enquanto (toque(1) == falso) farei {
          tras(250)
        }
        alinhandoReto()
        frenterotacao(250, 5)
        rotacionar(500, 90)
      }
      baixar(500)
    }

    se (temvitima()) entao {
      levantar(400)
      trasrotacao(125, 5)

      rotacionar(500, negativo(90))
      alinhandoReto()

      enquanto (corvermelha(5) > 2) farei {
        frente(250)
      }

      rotacionar(500, 45)
      atuadorEntregaVitima()
      rotacionar(500, negativo(45))

      enquanto (toque(1) == falso) farei {
        tras(1000)
      }

      alinhandoReto()
      frenterotacao(500, 15)
      rotacionar(500, 90)
      alinhandoReto()
    }

    # sai pela área verde
    enquanto (toque(1) == falso) farei {
      tras(1000)
    }
    alinhandoReto()

    frenterotacao(250, 15)
    rotacionar(500, 90)
    alinhandoReto()

    enquanto (toque(1) == falso) farei {
      tras(250)
    }

    levantar(600)
    girarbaixo(750)

    frenterotacao(125, 10)
    alinhandoReto()

    rotacionar(500, 90)
    alinhandoReto()

    enquanto (38 < corverde(2)) farei {
      frente(250)
    }
    parar()
    
    alinhandoReto()

  } senao se ((saidaFrente) e (resgateDireitaBaixo)) entao {
    enquanto(ultra(1) > 30) farei {
      frente(125)
    }
    paradinha()

    se (temvitima()) entao {
      levantar(400)

      alinhandoReto()
      rotacionar(500, negativo(90))
      alinhandoReto()

      enquanto (toque(1) == falso) farei {
        tras(250)
      }

      frenterotacao(125, 10)
      alinhandoReto()

      rotacionar(500, negativo(90))
      alinhandoReto()

      zerartemporizador()

      enquanto (corvermelha(5) > 2) farei {
        frente(250)
      }
      parar()
      tempoDeRetorno = temporizador()
      alinhandoReto()

      rotacionar(500, negativo(45))
      atuadorEntregaVitima()
      rotacionar(500, 45)
      alinhandoReto()

      tras(250)
      esperar(tempoDeRetorno)

      rotacionar(500, negativo(90))
      alinhandoReto()

      enquanto (toque(1) == falso) farei {
        tras(1000)
      }
      frenterotacao(125, 10)
      alinhandoReto()

      rotacionar(500, negativo(90))

      baixar(500)
    }

    # analisa verticalmente
    enquanto (verdadeiro) farei {
      alinhandoReto()

      # anda até ver vítima
      enquanto (verdadeiro) farei {
        se (temalgo(2, 0, 150)) entao {
          trasrotacao(125, 5)

          se (ultra(1) >= 175) entao {
            temArea = verdadeiro
          }

          se (temalgo(2, 0, 40)) entao {
            vitimaProxima = verdadeiro
          }

          interromper()
        } senao {
          tras(125)

          se (ultra(1) > 248) entao {
            interromper()
          }
        }
      }
      paradinha()
      alinhandoReto()

      # verifica se chegou ao final da sala
      se (ultra(1) > 248) entao {
        interromper()
      }

      se (vitimaProxima) entao {
        levantar(400)

        rotacionar(500, 90)
        alinhandoReto()

        frenterotacao(250, 15)
        trasrotacao(250, 15)

        baixar(500)
        alinhandoReto()

        se (temArea) entao {
          zerartemporizador()
          enquanto ((temporizador() < 5000) e (ultra(1) > 110)) farei {
            frente(125)
          }
        } senao {
          enquanto (ultra(1) > 35) farei {
            frente(125)
          }
        }

        vitimaProxima = falso

      } senao se (temArea) entao {
        # vira 90°
        rotacionar(500, 90)
        alinhandoReto()

        # segue até a area
        zerartemporizador()
        enquanto ((temporizador() < 6500) e (ultra(1) > 110)) farei {
          frente(125)
        }

      } senao {
        # vira 90°
        rotacionar(500, 90)
        alinhandoReto()

        # segue até a parede
        enquanto (ultra(1) > 35) farei {
          frente(125)
        }

      }

      frenterotacao(125, 2)
      levantar(400)

      # já está do outro lado da sala
      # se a área estiver na frente dele, entrega vitima
      
      se (temArea e temvitima()) entao {
        rotacionar(250, 45)

        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        paradinha()

        atuadorEntregaVitima()
        rotacionar(250, negativo(45))
        alinhandoReto()
        temArea = falso
      }

      se (temvitima() == falso) entao {
        enquanto (ultra(2) < 300) farei {
          tras(350)
        }
        alinhandoReto()
        trasrotacao(250, 20)

        rotacionar(500, negativo(90))
        alinhandoReto()

      } senao se (temvitima()) entao {
        trasrotacao(125, 5)
        alinhandoReto()
        rotacionar(500, 90)
        alinhandoReto()

        zerartemporizador()
        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        tempoDeRetorno = temporizador()

        rotacionar(500, negativo(45))
        atuadorEntregaVitima()
        rotacionar(500, 45)
        alinhandoReto()

        tras(250)
        esperar(tempoDeRetorno)

        trasrotacao(125, 5)
        alinhandoReto()

        rotacionar(500, negativo(90))
        alinhandoReto()

        enquanto (toque(1) == falso) farei {
          tras(250)
        }
        alinhandoReto()
        frenterotacao(250, 10)
        rotacionar(500, negativo(90))
      }

      baixar(500)

    }

    alinhandoReto()

    enquanto (ultra(1) > 30) farei {
      frente(1000)
    }
    rotacionar(500, 90)

    # analisa horizontalmente
    enquanto (verdadeiro) farei {
      alinhandoReto()

      # anda até ver vítima
      enquanto (verdadeiro) farei {
        se (temalgo(2, 0, 150)) entao {
          frenterotacao(125, 5)

          se (ultra(1) < 90) entao {
            temArea = verdadeiro
          }

          se (temalgo(2, 0, 40)) entao {
            vitimaProxima = verdadeiro
          }

          interromper()
        } senao {
          frente(125)

          se (ultra(1) <= 30) entao {
            interromper()
          }
        }
      }
      paradinha()
      alinhandoReto()

      # verifica se saiu da sala de resgate
      se (ultra(1) <= 30) entao {
        interromper()
      } 
      
      se (vitimaProxima) entao {
        levantar(400)

        rotacionar(500, 90)
        alinhandoReto()

        frenterotacao(250, 15)
        trasrotacao(250, 15)

        baixar(500)
        alinhandoReto()

        se (temArea) entao {
          zerartemporizador()
          enquanto ((temporizador() < 5000) e (ultra(1) > 110)) farei {
            frente(125)
          }
        } senao {
          zerartemporizador()
          enquanto (ultra(1) > 35) farei {
            frente(125)
          }
        }

        vitimaProxima = falso

      } senao se (temArea) entao {
        # vira 90°
        rotacionar(500, 90)
        alinhandoReto()

        # segue até a area
        zerartemporizador()
        enquanto ((temporizador() < 5000) e (ultra(1) > 110)) farei {
          frente(125)
        }

      } senao {
        # vira 90°
        rotacionar(500, negativo(90))
        alinhandoReto()

        # segue até a parede
        zerartemporizador()
        enquanto ((ultra(1) < 300) e (ultra(1) > 35)) farei {
          frente(125)
        }

      }

      frenterotacao(125, 2)
      levantar(400)
      # já está do outro lado da sala

      # se a área estiver na frente dele, entrega vitima
      
      se (temArea e temvitima()) entao {
        rotacionar(250, negativo(45))

        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        paradinha()

        atuadorEntregaVitima()
        rotacionar(250, 45)
        alinhandoReto()
        temArea = falso
      }

      se (temvitima() == falso) entao {
        enquanto (ultra(2) < 300) farei {
          tras(350)
        }
        alinhandoReto()
        rotacionar(250, negativo(90))

        baixar(500)
      } senao se (temvitima()) entao {
        trasrotacao(125, 5)
        alinhandoReto()
        rotacionar(500, negativo(90))
        alinhandoReto()

        zerartemporizador()
        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        tempoDeRetorno = temporizador()

        rotacionar(500, 45)
        atuadorEntregaVitima()
        rotacionar(500, negativo(45))
        alinhandoReto()

        tras(250)
        esperar(tempoDeRetorno)

        rotacionar(500, 90)
        alinhandoReto()

        trasrotacao(250, 10)
        rotacionar(500, negativo(180))
        alinhandoReto()
        baixar(500)
        enquanto (ultra(1) >= 35) farei {
          frente(500)
        }
        paradinha()
        alinhandoReto()
        rotacionar(500, 90)
      }
    }

    se (temvitima()) entao {
      levantar(400)
      trasrotacao(125, 5)

      rotacionar(500, 90)
      alinhandoReto()

      enquanto (corvermelha(5) > 2) farei {
        frente(250)
      }

      rotacionar(500, negativo(45))
      atuadorEntregaVitima()
      rotacionar(500, 45)
      alinhandoReto()

      trasrotacao(500, 35)
      alinhandoReto()

      rotacionar(500, 90)
      alinhandoReto()
    }

    # sai pela área verde

    levantar(600)
    girarbaixo(750)

    rotacionar(500, 180)
    alinhandoReto()

    enquanto (toque(1) == falso) farei {
      tras(250)
    }

    frenterotacao(125, 10)
    alinhandoReto()

    rotacionar(500, 90)
    alinhandoReto()

    enquanto (38 < corverde(2)) farei {
      frente(250)
    }
    parar()
    
    alinhandoReto()

  } senao se ((saidaFrente) e (resgateFrente)) entao {
    baixar(1200)

    # verifica verticalmente
    enquanto (verdadeiro) farei {
      alinhandoReto()

      # anda até ver vítima
      enquanto (verdadeiro) farei {
        se (temalgo(2, 0, 195)) entao {
          trasrotacao(125, 5)

          se (temalgo(2, 0, 40)) entao {
            vitimaProxima = verdadeiro
          }

          interromper()
        } senao {
          tras(125)

          se (ultra(1) > 248) entao {
            interromper()
          }
        }
      }
      paradinha()
      alinhandoReto()

      # verifica se chegou ao final da sala
      se (ultra(1) > 248) entao {
        interromper()
      }

      se (vitimaProxima) entao {
        levantar(400)

        rotacionar(500, 90)
        alinhandoReto()

        frenterotacao(250, 15)
        trasrotacao(250, 15)

        baixar(600)
        alinhandoReto()

        vitimaProxima = falso
      } senao {
        # vira 90°
        rotacionar(500, 90)
        alinhandoReto()
      }

      se (ultra(1) > 350) entao {
        interromper()
      }

      # segue até a parede
      alinhandoReto()
      enquanto (ultra(1) > 35) farei {
        frente(125)
      }

      frenterotacao(125, 2)
      levantar(400)

      paradinha()

      # já está do outro lado da sala
      # retorna e segue para entregar vitima
      enquanto (toque(1) == falso) farei {
        tras(125)
      }
      paradinha()
      frenterotacao(250, 15)
      alinhandoReto()

      rotacionar(500, negativo(90))
      alinhandoReto()

      se (temvitima()) entao {
        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        rotacionar(500, negativo(45))
        atuadorEntregaVitima()
        rotacionar(500, 45)

        alinhandoReto()
        trasrotacao(250, 10)
      }
      baixar(600)
    }

    frenterotacao(250, 5)
    rotacionar(500, 90)
    alinhandoReto()

    # verifica horizontalmente
    enquanto (verdadeiro) farei {
      alinhandoReto()

      # anda até ver vítima
      enquanto (verdadeiro) farei {
        se (ultra(1) > 150) entao {
          temArea = verdadeiro
          se (temalgo(3, 0, 150)) entao {
            frenterotacao(125, 5)

            se (temalgo(3, 0, 40)) entao {
              vitimaProxima = verdadeiro
            }
            interromper()
          } senao {
            frente(125)
            se (ultra(3) > 300) entao {
              interromper()
            }
          }
        } senao {
          temArea = falso
          se (temalgo(3, 0, 195)) entao {
            frenterotacao(125, 5)

            se (temalgo(3, 0, 40)) entao {
              vitimaProxima = verdadeiro
            }
            interromper()
          } senao {
            frente(125)
            se (ultra(3) > 300) entao {
              interromper()
            }
          }
        }
      }
      paradinha()
      alinhandoReto()

      # verifica se chegou ao final da sala
      se (ultra(3) > 300) entao {
        interromper()
      }

      se (vitimaProxima) entao {
        levantar(400)

        rotacionar(500, negativo(90))
        alinhandoReto()

        frenterotacao(250, 15)
        trasrotacao(250, 15)

        baixar(500)
        alinhandoReto()

        se (temArea) entao {
          zerartemporizador()
          enquanto ((temporizador() < 5000) e (ultra(1) > 110)) farei {
            frente(125)
          }
        } senao {
          zerartemporizador()
          enquanto (ultra(1) > 35) farei {
            frente(125)
          }
        }

        vitimaProxima = falso

      } senao se (temArea) entao {
        # vira 90°
        rotacionar(500, negativo(90))
        alinhandoReto()

        # segue até a area
        zerartemporizador()
        enquanto ((temporizador() < 6500) e (ultra(1) > 110)) farei {
          frente(125)
        }

      } senao {
        # vira 90°
        rotacionar(500, negativo(90))
        alinhandoReto()

        # segue até a parede
        zerartemporizador()
        enquanto (ultra(1) > 35) farei {
          frente(125)
        }

      }

      frenterotacao(125, 2)
      levantar(400)
      # já está do outro lado da sala

      # se a área estiver na frente dele, entrega vitima
      se (temArea e temvitima()) entao {
        rotacionar(250, negativo(45))

        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        paradinha()

        atuadorEntregaVitima()
        rotacionar(250, 45)
        alinhandoReto()
      }

      se (temvitima()) entao {
        trasrotacao(125, 5)
        alinhandoReto()
        rotacionar(500, negativo(90))
        alinhandoReto()

        zerartemporizador()
        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        tempoDeRetorno = temporizador()

        rotacionar(500, 45)
        atuadorEntregaVitima()
        rotacionar(500, negativo(45))
        alinhandoReto()

        tras(250)
        esperar(tempoDeRetorno)

        rotacionar(500, 90)
        alinhandoReto()
      }

      se (temArea) entao {
        baixar(500)
        enquanto (ultra(1) > 235) farei {
          tras(350)
        }
      } senao {
        enquanto (toque(1) == falso) farei {
          tras(350)
        }
        alinhandoReto()
        frenterotacao(250, 5)
        baixar(500)
      }

      rotacionar(500, 90)
      temArea = falso
    }

    se (temvitima()) entao {
      levantar(400)

      enquanto (toque(1) == falso) farei {
        tras(125)
      }
      paradinha()
      frenterotacao(250, 15)

      alinhandoReto()
      rotacionar(500, negativo(90))
      alinhandoReto()

      enquanto (corvermelha(5) > 2) farei {
        frente(250)
      }

      rotacionar(500, negativo(45))
      atuadorEntregaVitima()
      rotacionar(500, 45)
      alinhandoReto()

      trasrotacao(500, 35)
      alinhandoReto()
    }

    # sai pela área verde

    levantar(600)
    girarbaixo(750)

    rotacionar(500, negativo(180))
    alinhandoReto()

    enquanto (toque(1) == falso) farei {
      tras(250)
    }

    frenterotacao(125, 10)
    alinhandoReto()

    rotacionar(500, 90)
    alinhandoReto()

    enquanto (38 < corverde(2)) farei {
      frente(250)
    }
    parar()

    trasrotacao(250, 10)

    rotacionar(500, negativo(90))

    enquanto (toque(1) == falso) farei {
      tras(250)
    }

    frenterotacao(125, 10)
    alinhandoReto()

    rotacionar(500, 90)
    alinhandoReto()

    enquanto (38 < corverde(2)) farei {
      frente(250)
    }
    parar()
    alinhandoReto()
  }

  frenterotacao(250, 5)
  alinhandoReto()

  velocidadeatuador(200)
  levantar(500)
  girarbaixo(500)

  limparconsole()
}

tarefa verificaSala {
  zerartemporizador()

  enquanto (temporizador() < 3000) farei {
    se (temalgo(2, 160, 225)) entao {
      contResgate = contResgate + 1
    } senao se (300 < ultra(2)) entao {
      contSaida = contSaida + 1
    }
    frente(125)
  }
  paradinha()

  zerartemporizador()
  se (contSaida > contResgate) entao {
    saidaDireita = verdadeiro
    levantar(700)

    enquanto (verdadeiro) farei {
      se (corvermelha(5) < 2) entao {
        se (temvitima()) entao {
          atuadorEntregaVitima()
        }
        trasrotacao(250, 15)
        parar()
        resgateFrente = verdadeiro
        interromper()
      } senao se (temporizador() >= 7500) entao {
        trasrotacao(250, 15)
        parar()
        baixar(1250)
        resgateDireitaCima = verdadeiro
        interromper()
      }
      frente(125)
    }

  } senao se (contResgate > contSaida) entao {
    resgateDireitaBaixo = verdadeiro

    enquanto (verdadeiro) farei {
      se ((ultra(3) > 50) e (ultra(1) <= 75)) entao {
        saidaEsquerda = verdadeiro
        interromper()
      } senao se (ultra(1) <= 31) entao {
        saidaFrente = verdadeiro
        interromper()
      } senao {
        frente(125)
      }
    }
  } senao {
    levantar(700)
    enquanto (verdadeiro) farei {
      se (corvermelha(5) < 2) entao {
        se (temvitima()) entao {
          atuadorEntregaVitima()
        }
        trasrotacao(250, 15)
        parar()
        resgateFrente = verdadeiro
        saidaFrente = verdadeiro
        interromper()
      } senao se (ultra(3) > 50) entao {
        trasrotacao(250, 15)
        parar()
        baixar(1250)
        saidaEsquerda = verdadeiro
        resgateDireitaCima = verdadeiro
        interromper()
      } senao {
        frente(125)
      }
    }
  }
  paradinha()
}

inicio
  trasrotacao(250, 5)
  se ((horario < 8) ou (16 < horario)) entao {
    ajustarcor(45)
  } senao se (((8 <= horario) e (horario < 11)) ou ((13 < horario) e (horario <= 16))) entao  {
    ajustarcor(35)
  } senao {
    ajustarcor(30)
  }

  velocidadeatuador(200)
  levantar(500)
  girarbaixo(500)

  enquanto (verdadeiro) farei {
    se ((ultra(1) <= 10) e (cor(5) != "BRANCO")) entao {
      paradinha()
      alinhandoReto()
      paradinha()

      rotacionar(500, 90)
      enquanto (ultra(3) < 20) farei {
        frente(200)
      }
      frenterotacao(200, 10)
      rotacionar(500, negativo(90))

      enquanto (ultra(3) > 20) farei {
        frente(200)
      }
      enquanto (ultra(3) < 20) farei {
        frente(200)
      }
      frenterotacao(200, 12)
      rotacionar(500, negativo(90))

      enquanto (ultra(3) > 50) farei {
        frente(200)
      }
      frenterotacao(200, 6.5)
      rotacionar(500, 45)

      enquanto (cor(4) != "PRETO") farei {
        direita(500)
      }
      alinhandoEsquerda()
      alinhandoReto()

      enquanto (toque(1) == falso) farei {
        tras(50)
      }
    } senao {
      se (((corverde(1) < 70 e corazul(1) < 20) ou (corverde(2) < 70 e corazul(2) < 20) ou (corverde(3) < 70 e corazul(3) < 20) ou (corverde(4) < 70 e corazul(4) < 20))) entao {
        trasrotacao(500, 5)
        zerartemporizador()
        enquanto (cor(1) != "VERDE" e cor(4) != "VERDE" e temporizador() < 1000) farei {
          segueLinha()
        }
        paradinha()
        se (((cor(1) == "VERDE") ou (cor(2) == "VERDE")) e ((cor(3) == "VERDE") ou (cor(4) == "VERDE"))) entao {
          rotacionar(1000, 180)
          trasrotacao(200, 4)
        } senao se ((cor(1) == "VERDE") ou (cor(2) == "VERDE") e ((cor(3) != "VERDE") e (cor(4) != "VERDE"))) entao {
          frenterotacao(200, 14)
          rotacionar(1000, 20)
          enquanto (cor(3) != "PRETO") farei {
            direita(750)
          }
          trasrotacao(200, 4)
          alinhandoEsquerda()
        } senao se ((cor(1) != "VERDE") e (cor(2) != "VERDE") e ((cor(3) == "VERDE") ou (cor(4) == "VERDE"))) entao {
          frenterotacao(200, 14)
          rotacionar(1000, negativo(20))
          enquanto (cor(2) != "PRETO") farei {
            esquerda(750)
          }
          trasrotacao(200, 4)
          alinhandoDireita()
        }
      } senao se ((corverde(1) < 40) e (corverde(4) < 40)) entao {
        trasrotacao(500, 5)
        zerartemporizador()
        enquanto (cor(1) != "PRETO" e cor(4) != "PRETO" e temporizador() < 1000) farei {
          segueLinha()
        }
        paradinha()
        se ((cor(1) == "PRETO") e (cor(4) != "PRETO")) entao {
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
        se (((340 < inclinacao()) e (inclinacao() < 350)) e ((ultra(2) < 40) e (ultra(3) < 40))) entao {
          paradinha()
          zerartemporizador()

          velocidadeatuador(500)
          baixar(100)
          velocidadeatuador(100)

          velocidadeBranco = 250
          enquanto (inclinacao() != 0) farei {
            segueLinhaComBranco()
          }
          velocidadeBranco = 125

          paradinha()
          para contagem de 1 ate 3 passo 1 farei {
            alinhandoReto()
            paradinha()
          }
          contagem = 1

          frenterotacao(200, 20)
          trasrotacao(200, 20)

          paradinha()

          enquanto (angulogiroatuador() > 15) farei {
            girarcima(1)
          }
          enquanto (angulogiroatuador() < 15) farei {
            girarcima(1)
          }
          baixar(750)

          verificaSala()
          encontraPegaVitima()

          frenterotacao(125, 2.5)
          alinhandoReto()
          saiuDaSala = verdadeiro
        } senao se ((cor(2) == "VERMELHO") e (cor(3) == "VERMELHO") e (saiuDaSala) ) entao {
          frenterotacao(250, 7)
          parei()
        } senao {
          se ((15 < inclinacao()) e (inclinacao() < 345)) entao {
            segueLinhaComBranco()
          } senao se ((((0 <= direcao()) e (direcao() < 7)) ou ((353 < direcao()) e (direcao() <= 360))) ou ((83 < direcao()) e (direcao() < 97)) ou ((173 < direcao()) e (direcao() < 187)) ou ((263 < direcao()) e (direcao() < 277))) entao {
            segueLinhaComBranco()
          } senao {
            segueLinha()
          }
        }
      }
    }
  }  
fim