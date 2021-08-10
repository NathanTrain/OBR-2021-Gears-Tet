numero velocidadeFrenteSeguidor = 175

booleano viraEsquerda = falso
booleano viraDireita = falso
booleano travessa = falso

numero alinhamento = 0

numero contagemPara = 1

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

booleano resgateConcluido = falso

numero horario = 12

tarefa segueLinha {
  se (cor(2) == "PRETO" e cor(3) == "PRETO") entao {
    frente(velocidadeFrenteSeguidor)
    esperar(30)
  }

  se (cor(2) == "BRANCO" e cor(3) == "BRANCO") entao {
    frente(velocidadeFrenteSeguidor)
    esperar(30)
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
        tras(50)
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
  para contagemPara de 1 ate 2 passo 1 farei {
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
    rotacionar(250, arredondar(alinhamento))
  }
}

tarefa atuadorEntregaVitima {
  baixar(300)
  girarbaixo(750)
  esperar(500)
  girarcima(750)
  levantar(300)
}

# TODO => CONFERIR VERIFICA SALA
# TODO => USAR TEMPO < 60*1000*3.5 (3 MIN E MEIO) PARA, SE FOR MENOR, FAZER VERIFICAÇÃO VERTICAL (OU TIRAR ELA INTEIRAMENTE)

tarefa verificaSala {
  zerartemporizador()

  enquanto (temporizador() < 3000) farei {
    se (temalgo(2, 160, 225)) entao {
      contResgate = contResgate + 1
    } senao se (300 < ultra(2)) entao {
      contSaida = contSaida + 1
    }
    frente(175)
  }
  paradinha()

  zerartemporizador()
  se (contSaida > contResgate) entao {
    saidaDireita = verdadeiro
    escrever(1, "saida direita")
    levantar(700)

    enquanto (verdadeiro) farei {
      se (corvermelha(5) < 2) entao {
        se (temvitima()) entao {
          atuadorEntregaVitima()
        }
        trasrotacao(300, 15)
        parar()
        resgateFrente = verdadeiro
        escrever(2, "resgate frente")
        interromper()
      } senao se (temporizador() >= 7500) entao {
        trasrotacao(300, 15)
        parar()
        baixar(1250)
        resgateDireitaCima = verdadeiro
        escrever(2, "resgate direita cima")
        interromper()
      }
      frente(175)
    }

  } senao se (contResgate > contSaida) entao {
    resgateDireitaBaixo = verdadeiro
    escrever(1, "resgate direita baixo")

    enquanto (verdadeiro) farei {
      se ((ultra(3) > 50) e (ultra(1) <= 75)) entao {
        escrever(2, "saida esquerda")
        saidaEsquerda = verdadeiro
        interromper()
      } senao se (ultra(1) <= 31) entao {
        escrever(2, "saida frente")
        saidaFrente = verdadeiro
        interromper()
      } senao {
        frente(175)
      }
    }
  } senao {
    levantar(700)
    enquanto (verdadeiro) farei {
      se (corvermelha(5) < 2) entao {
        se (temvitima()) entao {
          atuadorEntregaVitima()
        }
        trasrotacao(300, 15)
        parar()
        resgateFrente = verdadeiro
        saidaFrente = verdadeiro
        escrever(1, "saida frente")
        escrever(2, "resgate frente")
        interromper()
      } senao se (ultra(3) > 50) entao {
        trasrotacao(300, 15)
        parar()
        baixar(1250)
        saidaEsquerda = verdadeiro
        resgateDireitaCima = verdadeiro
        escrever(1, "saida esquerda")
        escrever(2, "resgate direita cima")
        interromper()
      } senao {
        frente(175)
      }
    }
  }
  paradinha()
}

tarefa encontraPegaVitima {
  velocidadeatuador(100)

  # TODO => adicionar retorno após encontrar vitima (trasrotacao(300, 3))

  # TODO => corrigir resgate => verificar todos os movimentos e ações

  se ((saidaDireita) e (resgateFrente)) entao {
    baixar(1200)

    # verificação vertical
    enquanto (verdadeiro) farei {
      alinhandoReto()
      # anda até ver vítima
      enquanto (verdadeiro) farei {
        se (temalgo(2, 0, 195)) entao {
          trasrotacao(175, 5)

          se (temalgo(2, 0, 40)) entao {
            vitimaProxima = verdadeiro
          }

          interromper()
        } senao {
          se ((ultra(2) > 300) e (ultra(1) > 248)) entao {
            interromper()
          } senao {
            tras(225)
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

        frenterotacao(250, 15)
        trasrotacao(250, 15)

        baixar(600)
        alinhandoReto()

        vitimaProxima = falso
      } senao {
        # vira 90°
        rotacionar(500, 90)
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
          frente(250)
        }
      }

      levantar(400)
      paradinha()
      esperar(500)

      # já está do outro lado da sala
      # retorna e segue para entregar vitima
      enquanto (toque(1) == falso) farei {
        se (temvitima()) entao {
          tras(175)
        } senao {
          tras(300)
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
        paradinha()
        atuadorEntregaVitima()

        alinhandoReto()
        trasrotacao(250, 15)
      }
      baixar(600)
    }

    frenterotacao(250, 10)
    rotacionar(500, 90)
    alinhandoReto()

    enquanto (corverde(2) > 38) farei {
      frente(300)
    }
    alinhandoReto()
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

      paradinha()
      atuadorEntregaVitima()
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
          trasrotacao(250, 5)
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
            tras(225)
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

        frenterotacao(250, 15)
        trasrotacao(250, 15)

        baixar(600)
        alinhandoReto()

        vitimaProxima = falso
      } senao {
        # vira 90°
        rotacionar(500, 90)
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
          frente(225)
        }
      }

      levantar(400)
      paradinha()
      esperar(500)

      # já está do outro lado da sala
      # retorna e segue para entregar vitima
      se (temvitima() == falso) entao {
        enquanto (toque(1) == falso) farei {
          tras(300)
        }
        alinhandoReto()
        frenterotacao(250, 10)
        rotacionar(500, negativo(90))
      } senao se (temvitima()) entao {
        trasrotacao(250, 10)
        alinhandoReto()
        rotacionar(500, negativo(90))
        alinhandoReto()

        zerartemporizador()
        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        tempoDeRetorno = temporizador()
        paradinha()
        atuadorEntregaVitima()
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

    # saindo pela área verde
    frenterotacao(250, 10)
    rotacionar(500, 90)
    alinhandoReto()

    enquanto (38 < corverde(2)) farei {
      frente(250)
    }
    alinhandoReto()
    parar()

  } senao se ((saidaEsquerda) e (resgateDireitaBaixo)) entao {
    enquanto(ultra(1) > 30) farei {
      frente(175)
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
        tras(250)
      }

      frenterotacao(250, 10)
      alinhandoReto()

      rotacionar(500, negativo(90))
      alinhandoReto()

      enquanto (corvermelha(5) > 2) farei {
        frente(250)
      }
      parar()
      alinhandoReto()

      paradinha()
      atuadorEntregaVitima()
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
          trasrotacao(175, 5)

          se (ultra(1) >= 175) entao {
            temArea = verdadeiro
          }

          se (temalgo(2, 0, 40)) entao {
            vitimaProxima = verdadeiro
          }

          interromper()
        } senao {
          tras(175)

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

        frenterotacao(250, 15)
        trasrotacao(250, 15)

        baixar(500)
        alinhandoReto()

        se (temArea) entao {
          zerartemporizador()
          enquanto ((temporizador() < 5000) e (ultra(1) > 110)) farei {
            frente(175)
          }
        } senao {
          zerartemporizador()
          enquanto (ultra(1) > 35) farei {
            frente(175)
          }
        }

        vitimaProxima = falso

      } senao se (temArea) entao {
        # vira 90°
        rotacionar(500, 90)

        # segue até a area
        zerartemporizador()
        enquanto ((temporizador() < 6500) e (ultra(1) > 110)) farei {
          frente(175)
        }

      } senao {
        # vira 90°
        rotacionar(500, 90)

        # segue até a parede
        zerartemporizador()
        enquanto (ultra(1) > 35) farei {
          frente(175)
        }

      }

      frenterotacao(250, 2)
      levantar(400)
      esperar(500)
      # já está do outro lado da sala

      # se a área estiver na frente dele, entrega vitima
      se (temArea e temvitima()) entao {

        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        paradinha()

        paradinha()
        atuadorEntregaVitima()

        alinhandoReto()
        temArea = falso
      }
      
      se (temvitima()) entao {
        trasrotacao(250, 5)
        alinhandoReto()
        rotacionar(500, 90)
        alinhandoReto()

        zerartemporizador()
        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        tempoDeRetorno = temporizador()

        paradinha()
        atuadorEntregaVitima()
        alinhandoReto()

        tras(250)
        esperar(tempoDeRetorno)
        alinhandoReto()

        rotacionar(500, negativo(90))
        alinhandoReto()
      }
      enquanto (ultra(2) < 300) farei {
        tras(300)
      }
      alinhandoReto()
      trasrotacao(250, 15)

      rotacionar(500, negativo(90))
      alinhandoReto()
      baixar(500)
    }

    alinhandoReto()

    enquanto (ultra(1) > 25) farei {
      frente(300)
    }
    rotacionar(500, negativo(90))
    alinhandoReto()

    # sai pela área verde
    enquanto (38 < corverde(2)) farei {
      frente(250)
    }
    parar()

    alinhandoReto()

  } senao se ((saidaEsquerda) e (resgateDireitaCima)) entao {
    enquanto(ultra(1) > 30) farei {
      frente(175)
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

      paradinha()
      atuadorEntregaVitima()
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
          trasrotacao(175, 5)

          se (ultra(1) < 90) entao {
            temArea = verdadeiro
          }

          se (temalgo(2, 0, 40)) entao {
            vitimaProxima = verdadeiro
          }

          interromper()
        } senao {
          tras(175)

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

        frenterotacao(250, 15)
        trasrotacao(250, 15)

        baixar(500)
        alinhandoReto()

        se (temArea) entao {
          zerartemporizador()
          enquanto ((temporizador() < 5000) e (ultra(1) > 110)) farei {
            frente(175)
          }
        } senao {
          zerartemporizador()
          enquanto (ultra(1) > 35) farei {
            frente(175)
          }
        }

        vitimaProxima = falso

      } senao se (temArea) entao {
        # vira 90°
        rotacionar(500, 90)

        # segue até a area
        zerartemporizador()
        enquanto ((temporizador() < 6500) e (ultra(1) > 110)) farei {
          frente(175)
        }

      } senao {
        # vira 90°
        rotacionar(500, 90)

        # segue até a parede
        zerartemporizador()
        enquanto (ultra(1) > 35) farei {
          frente(175)
        }

      }

      frenterotacao(250, 2)
      levantar(400)
      esperar(500)
      # já está do outro lado da sala

      # se a área estiver na frente dele, entrega vitima
      se (temArea e temvitima()) entao {

        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        paradinha()
        atuadorEntregaVitima()
        alinhandoReto()
      }

      se (temvitima()) entao {
        trasrotacao(250, 5)
        alinhandoReto()
        rotacionar(500, negativo(90))
        alinhandoReto()

        zerartemporizador()
        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        tempoDeRetorno = temporizador()
        paradinha()
        atuadorEntregaVitima()
        alinhandoReto()

        tras(250)
        esperar(tempoDeRetorno)

        rotacionar(500, 90)
        alinhandoReto()
      }

      # retorna
      se (temArea) entao {
        enquanto (ultra(2) < 300) farei {
          tras(300)
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
    alinhandoReto()

    enquanto (ultra(1) > 25) farei {
      frente(300)
    }
    rotacionar(500, negativo(90))
    alinhandoReto()

    # sai pela área verde
    enquanto (38 < corverde(2)) farei {
      frente(250)
    }
    parar()
    alinhandoReto()

  } senao se ((saidaFrente) e (resgateDireitaBaixo)) entao {
    enquanto(ultra(1) > 30) farei {
      frente(175)
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

      frenterotacao(250, 10)
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

      paradinha()
      atuadorEntregaVitima()
      alinhandoReto()

      tras(250)
      esperar(tempoDeRetorno)

      rotacionar(500, negativo(90))
      alinhandoReto()

      enquanto (toque(1) == falso) farei {
        tras(1000)
      }
      frenterotacao(250, 10)
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
          # trasrotacao(175, 5)

          se (ultra(1) >= 175) entao {
            temArea = verdadeiro
          }

          se (temalgo(2, 0, 40)) entao {
            vitimaProxima = verdadeiro
          }

          interromper()
        } senao {
          tras(175)

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

        frenterotacao(250, 15)
        trasrotacao(250, 15)

        baixar(500)
        alinhandoReto()

        se (temArea) entao {
          zerartemporizador()
          enquanto ((temporizador() < 5000) e (ultra(1) > 110)) farei {
            frente(175)
          }
        } senao {
          enquanto (ultra(1) > 35) farei {
            frente(175)
          }
        }

        vitimaProxima = falso

      } senao se (temArea) entao {
        # vira 90°
        rotacionar(500, 90)

        # segue até a area
        zerartemporizador()
        enquanto ((temporizador() < 6500) e (ultra(1) > 110)) farei {
          frente(175)
        }

      } senao {
        # vira 90°
        rotacionar(500, 90)

        # segue até a parede
        enquanto (ultra(1) > 35) farei {
          frente(175)
        }

      }

      frenterotacao(250, 2)
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
          tras(300)
        }
        alinhandoReto()
        trasrotacao(250, 20)

        rotacionar(500, negativo(90))
        alinhandoReto()

      } senao se (temvitima()) entao {
        trasrotacao(250, 5)
        alinhandoReto()
        rotacionar(500, 90)
        alinhandoReto()

        zerartemporizador()
        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        tempoDeRetorno = temporizador()

        paradinha()
        atuadorEntregaVitima()
        alinhandoReto()

        tras(250)
        esperar(tempoDeRetorno)

        trasrotacao(250, 5)
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
          # frenterotacao(175, 5)

          se (ultra(1) < 90) entao {
            temArea = verdadeiro
          }

          se (temalgo(2, 0, 40)) entao {
            vitimaProxima = verdadeiro
          }

          interromper()
        } senao {
          frente(175)

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
            frente(175)
          }
        } senao {
          zerartemporizador()
          enquanto (ultra(1) > 35) farei {
            frente(175)
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
          frente(175)
        }

      } senao {
        # vira 90°
        rotacionar(500, negativo(90))
        alinhandoReto()

        # segue até a parede
        zerartemporizador()
        enquanto ((ultra(1) < 300) e (ultra(1) > 35)) farei {
          frente(175)
        }

      }

      frenterotacao(250, 2)
      levantar(400)
      esperar(500)
      # já está do outro lado da sala

      # se a área estiver na frente dele, entrega vitima
      
      se (temArea e temvitima()) entao {

        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        paradinha()
        atuadorEntregaVitima()
        alinhandoReto()
        temArea = falso
      }

      se (temvitima() == falso) entao {
        enquanto (ultra(2) < 300) farei {
          tras(300)
        }
        alinhandoReto()
        rotacionar(500, negativo(90))

        baixar(500)
      } senao se (temvitima()) entao {
        trasrotacao(250, 5)
        alinhandoReto()
        rotacionar(500, negativo(90))
        alinhandoReto()

        zerartemporizador()
        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        tempoDeRetorno = temporizador()

        paradinha()
        atuadorEntregaVitima()
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
      trasrotacao(250, 5)

      rotacionar(500, 90)
      alinhandoReto()

      enquanto (corvermelha(5) > 2) farei {
        frente(250)
      }

        paradinha()
      atuadorEntregaVitima()
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

    frenterotacao(250, 10)
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
          # trasrotacao(175, 5)

          se (temalgo(2, 0, 40)) entao {
            vitimaProxima = verdadeiro
          }

          interromper()
        } senao {
          tras(175)

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

        frenterotacao(250, 15)
        trasrotacao(250, 15)

        baixar(600)
        alinhandoReto()

        vitimaProxima = falso
      } senao {
        # vira 90°
        rotacionar(500, 90)
      }

      se (ultra(1) > 350) entao {
        interromper()
      }

      # segue até a parede
      alinhandoReto()
      enquanto (ultra(1) > 35) farei {
        frente(175)
      }

      frenterotacao(250, 2)
      levantar(400)

      paradinha()

      # já está do outro lado da sala
      # retorna e segue para entregar vitima
      enquanto (toque(1) == falso) farei {
        tras(250)
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
        paradinha()
        atuadorEntregaVitima()

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
            # frenterotacao(175, 5)

            se (temalgo(3, 0, 40)) entao {
              vitimaProxima = verdadeiro
            }
            interromper()
          } senao {
            frente(175)
            se (ultra(3) > 300) entao {
              interromper()
            }
          }
        } senao {
          temArea = falso
          se (temalgo(3, 0, 195)) entao {
            # frenterotacao(175, 5)

            se (temalgo(3, 0, 40)) entao {
              vitimaProxima = verdadeiro
            }
            interromper()
          } senao {
            frente(175)
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
            frente(175)
          }
        } senao {
          zerartemporizador()
          enquanto (ultra(1) > 35) farei {
            frente(175)
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
          frente(175)
        }

      } senao {
        # vira 90°
        rotacionar(500, negativo(90))
        alinhandoReto()

        # segue até a parede
        zerartemporizador()
        enquanto (ultra(1) > 35) farei {
          frente(175)
        }

      }

      frenterotacao(250, 2)
      levantar(400)
      esperar(500)
      # já está do outro lado da sala

      # se a área estiver na frente dele, entrega vitima
      se (temArea e temvitima()) entao {
        rotacionar(500, negativo(45))

        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        paradinha()
        atuadorEntregaVitima()
        rotacionar(250, 45)
        alinhandoReto()
      }

      se (temvitima()) entao {
        trasrotacao(250, 5)
        alinhandoReto()
        rotacionar(500, negativo(90))
        alinhandoReto()

        zerartemporizador()
        enquanto (corvermelha(5) > 2) farei {
          frente(250)
        }
        tempoDeRetorno = temporizador()

        paradinha()
        atuadorEntregaVitima()
        alinhandoReto()

        tras(250)
        esperar(tempoDeRetorno)

        rotacionar(500, 90)
        alinhandoReto()
      }

      se (temArea) entao {
        baixar(500)
        enquanto (ultra(1) > 235) farei {
          tras(300)
        }
      } senao {
        enquanto (toque(1) == falso) farei {
          tras(300)
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
        tras(175)
      }
      paradinha()
      frenterotacao(250, 15)

      alinhandoReto()
      rotacionar(500, negativo(90))
      alinhandoReto()

      enquanto (corvermelha(5) > 2) farei {
        frente(250)
      }

      paradinha()
      atuadorEntregaVitima()
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

    frenterotacao(250, 10)
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

    frenterotacao(250, 10)
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

      trasrotacao(300, 14)
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
        frenterotacao(300, 16)
        rotacionar(500, 30)
        enquanto (toque(1) == falso) farei {
          tras(150)
        }
      }
      alinhandoReto()
      paradinha()

    } senao {
      se (((cor(1) == "VERDE") ou (cor(2) == "VERDE")) ou ((cor(3) == "VERDE") ou (cor(4) == "VERDE"))) entao {
        paradinha()

        # verifica onde está
        verificaCurva()
        frenterotacao(300, 16)

        se (travessa) entao {
          rotacionar(500, 180)
        } senao se (viraDireita) entao {
          rotacionar(500, 30)
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
          frenterotacao(300, 5)

          se (travessa) entao {
            frenterotacao(300, 5)

          } senao se (viraDireita) entao {

            enquanto (cor(3) != "PRETO") farei {
              direita(1000)
            }

          } senao se (viraEsquerda) entao {

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
            alinhandoReto()

            frenterotacao(300, 15)
            trasrotacao(300, 15)
            
            enquanto (angulogiroatuador() > 20) farei {
              girarcima(1)
            }
            enquanto (angulogiroatuador() < 10) farei {
              girarcima(1)
            }
            baixar(1000)

            verificaSala()
            encontraPegaVitima()

            resgateConcluido = verdadeiro

            velocidadeFrenteSeguidor = 150
          } senao se (((60 < corvermelha(2)) e (corvermelha(2) < 70)) e ((10 < corazul(2)) e (corazul(2) < 20)) e resgateConcluido) entao {
            frenterotacao(250, 5)
            parei()
          } senao {
            se (15 < inclinacao() e inclinacao() < 25) entao {
              velocidadeFrenteSeguidor = 100
            } senao {
              velocidadeFrenteSeguidor = 150
            }
            segueLinha()
          }
        }
      }
    }
  }
  
fim