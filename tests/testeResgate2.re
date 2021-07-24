numero erro = 0
numero p = 0
numero i = 0
numero integral = 0
numero d = 0
numero lastErro = 0
numero PID = 0
numero correcaoE = 0
numero correcaoD = 0
numero velocidade = 200

numero reajuste = 0.6

numero velocidadeBranco = 125

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

numero horario = 12

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

tarefa segueLinhaComBranco {
  se ((cor(2) == "BRANCO") e (cor(3) == "BRANCO")) entao {
    frente(velocidadeBranco)
  } senao {
    segueLinha()
  }
}

tarefa alinhandoReto {
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
  rotacionar(50, arredondar(alinhamento))
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

tarefa entregarVitima {
  se ((saidaDireita) e (resgateFrente)) entao {

  } senao se ((saidaDireita) e (resgateDireitaCima)) entao {

  } senao se ((saidaEsquerda) e (resgateDireitaBaixo)) entao {

    se (temArea) entao {
      rotacionar(250, 45)

      enquanto (corvermelha(5) > 2) farei {
        frente(250)
      }
      paradinha()

      atuadorEntregaVitima()
      rotacionar(250, negativo(45))

      alinhandoReto()

    } senao {
      # anda até ver a área de resgate, alinha e entrega
      enquanto (corvermelha(5) > 2) farei {
        frente(250)
      }

      paradinha()

      atuadorEntregaVitima()

      alinhandoReto()
    }

  } senao se ((saidaEsquerda) e (resgateDireitaCima)) entao {

    se (temArea) entao {
      rotacionar(250, negativo(45))

      enquanto (corvermelha(5) > 2) farei {
        frente(250)
      }
      paradinha()

      atuadorEntregaVitima()
      rotacionar(250, 45)

      alinhandoReto()

    } senao {
      # anda até ver a área de resgate, alinha e entrega
      enquanto (corvermelha(5) > 2) farei {
        frente(250)
      }

      paradinha()

      atuadorEntregaVitima()

      alinhandoReto()
    }

  } senao se ((saidaFrente) e (resgateDireitaBaixo)) entao {

  } senao se ((saidaFrente) e (resgateFrente)) entao {

  }

  temArea = falso
}

# UMA ROTAÇÃO ~= 2.5 DISTANCIA

tarefa encontraPegaVitima {
  velocidadeatuador(100)

  # TODO
    # [] sDireita rFrente
    # [] sDireita rDireitaCima
    # [X] sEsquerda rDireitaBaixo
    # [X] sEsquerda rDireitaCima
    # [] sFrente rDireitaBaixo
    # [] sFrente rFrente

  se ((saidaDireita) e (resgateFrente)) entao {
    escrever(1, "saidaDireita")
    escrever(2, "resgateFrente")
    se (temvitima()) entao {
      escrever(3, "tem vitima")
      # entregar
    }

  } senao se ((saidaDireita) e (resgateDireitaCima)) entao {
    escrever(1, "saidaDireita")
    escrever(2, "resgateDireitaCima")
    se (temvitima()) entao {
      escrever(3, "tem vitima")
      # entregar
    }

  } senao se ((saidaEsquerda) e (resgateDireitaBaixo)) entao {

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

      enquanto (corvermelha(5) > 2) farei {
        frente(125)
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
      trasrotacao(250, 10)
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

        frenterotacao(250, 10)
        trasrotacao(250, 10)

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
      se (temArea) entao {
        entregarVitima()
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

        enquanto (corvermelha(5) > 2) farei {
          frente(125)
        }

        rotacionar(500, negativo(45))
        entregarVitima()
        rotacionar(500, 45)
        alinhandoReto()

        enquanto (toque(1) == falso) farei {
          tras(1000)
        }
        frenterotacao(250, 10)
        alinhandoReto()


        rotacionar(500, negativo(90))
        alinhandoReto()

        enquanto (ultra(2) < 300) farei {
          tras(250)
        }
        alinhandoReto()
        trasrotacao(250, 20)
        rotacionar(500, negativo(90))
      }

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

        frenterotacao(250, 10)
        trasrotacao(250, 10)

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
      se (temArea) entao {
        entregarVitima()
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

        enquanto (corvermelha(5) > 2) farei {
          frente(125)
        }

        rotacionar(500, 45)
        entregarVitima()
        rotacionar(500, negativo(45))
        alinhandoReto()
        trasrotacao(250, 30)
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

    rotacionar(500, negativo(90))
    alinhandoReto()

    enquanto (ultra(1) >= 26) farei {
      frente(125)
    }

    rotacionar(500, negativo(90))
    alinhandoReto()

    enquanto ((cor(1) != "VERDE") e (cor(2) != "VERDE") e (cor(3) != "VERDE") e (cor(4) != "VERDE")) farei {
      frente(500)
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
        frente(125)
      }
      parar()


      entregarVitima()
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

        frenterotacao(250, 10)
        trasrotacao(250, 10)

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
      se (temArea) entao {
        entregarVitima()
      }

      se (temvitima() == falso) entao {
        enquanto (ultra(2) < 300) farei {
          tras(350)
        }
        alinhandoReto()
        trasrotacao(250, 20)
        rotacionar(500, negativo(90))
      } senao se (temvitima()) entao {
        trasrotacao(125, 5)
        alinhandoReto()
        rotacionar(500, negativo(90))
        alinhandoReto()

        enquanto (corvermelha(5) > 2) farei {
          frente(125)
        }
        rotacionar(500, 45)
        entregarVitima()
        rotacionar(500, negativo(45))
        alinhandoReto()
        trasrotacao(250, 20)
        rotacionar(500, 90)
        alinhandoReto()

        enquanto (ultra(2) < 300) farei {
          tras(250)
        }
        alinhandoReto()
        trasrotacao(250, 20)
        rotacionar(500, negativo(90))
      }
      baixar(500)

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

        frenterotacao(250, 10)
        trasrotacao(250, 10)

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
      se (temArea) entao {
        entregarVitima()
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

        enquanto (corvermelha(5) > 2) farei {
          frente(125)
        }

        rotacionar(250, negativo(45))
        entregarVitima()
        rotacionar(500, 45)
        alinhandoReto()
        trasrotacao(250, 30)
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
    alinhandoReto()

    rotacionar(500, negativo(90))

    enquanto (ultra(1) >= 30) farei {
      frente(1000)
    }
    alinhandoReto()

    levantar(600)
    girarbaixo(750)

    enquanto (ultra(1) > 26) farei {
      frente(1000)
    }

    rotacionar(500, negativo(90))
    alinhandoReto()

    enquanto ((cor(1) != "VERDA") e (cor(2) != "VERDE") e (cor(3) != "VERDE") e (cor(4) != "VERDE")) farei {
      frente(250)
    }
    
    alinhandoReto()

  } senao se ((saidaFrente) e (resgateDireitaBaixo)) entao {
    escrever(1, "saidaFrente")
    escrever(2, "resgateDireitaBaixo")
    se (temvitima()) entao {
      escrever(3, "tem vitima")
      # entregar
    }

  } senao se ((saidaFrente) e (resgateFrente)) entao {
    escrever(1, "saidaFrente")
    escrever(2, "resgateFrente")
    se (temvitima()) entao {
      escrever(3, "tem vitima")
      # entregar
    }

  }

  # utilizar alinhandoEsquerda e alinhandoDireita quando sair da sala
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

  zerartemporizador()

  # verificações:
    # saída na direita
      # resgate na frente
      # resgate direita cima
    # resgate direita baixo
      # saída na esquerda
      # saída na frente
    # senao
      # resgate na frente E saída na frente
      # resgate direita cima E saída na esquerda

  se (contSaida > contResgate) entao {
    saidaDireita = verdadeiro

    enquanto (verdadeiro) farei {
      se (temporizador() > 4000) entao {
        resgateFrente = verdadeiro
        interromper()
      } senao se (ultra(1) <= 85) entao {
        resgateDireitaCima = verdadeiro
        interromper()
      } senao {
        frente(125)
      }
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
    enquanto (verdadeiro) farei {
      se (temporizador() > 3500) entao {
        resgateFrente = verdadeiro
        saidaFrente = verdadeiro
        interromper()
      } senao se ((ultra(3) > 50) e (ultra(1) <= 85)) entao {
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

  velocidadeatuador(200)
  levantar(500)
  girarbaixo(500)

  enquanto (verdadeiro) farei {
    se ((inclinacao() < 345) e ((ultra(2) < 40) e (ultra(3) < 40))) entao {
      # PASSANDO PELA RAMPA
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

      # NA SALA DE RESGATE
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

      # ANALISANDO A SALA
      verificaSala()

      # BUSCANDO VÍTIMA
      encontraPegaVitima()

      frenterotacao(125, 5)
      alinhandoReto()

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

  
fim