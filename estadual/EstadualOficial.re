numero velocidadeFrenteSeguidor = 175

# variáveis para confirmação da curva
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

numero catAdj = 0
numero catOp = 0
numero hip = 0

numero angulo = 5

booleano resgateConcluido = falso

numero horario = 15.5

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
      zerartemporizador()
      enquanto (cor(1) != "PRETO" e cor(4) != "PRETO" e temporizador() < 3000) farei {
        tras(50)
      }
      parar()
    }
  }

  se (temporizador() < 3000) entao {
    parartarefa()
  }
  zerartemporizador()

  se (cor(1) == "PRETO" e cor(4) == "PRETO") entao {
    travessa = verdadeiro
  } senao se ((cor(1) == "VERDE" e cor(3) == "VERDE") ou (cor(2) == "VERDE" e cor(4) == "VERDE")) entao {
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
      alinhamento = negativo(modulo(direcao()))
    } senao se ((315 < direcao()) e (direcao() < 359)) entao {
      alinhamento = modulo(360 - direcao())
    } senao se ((45 < direcao()) e (direcao() <= 90)) entao {
      alinhamento = modulo(90 - direcao())
    } senao se ((90 <= direcao()) e (direcao() < 135)) entao {
      alinhamento = negativo(modulo(direcao() - 90))
    } senao se ((135 < direcao()) e (direcao() <= 180)) entao {
      alinhamento = modulo(180 - direcao())
    } senao se ((180 <= direcao()) e (direcao() < 225)) entao {
      alinhamento = negativo(modulo(direcao() - 180))
    } senao se ((225 < direcao()) e (direcao() <= 270)) entao {
      alinhamento = modulo(270 - direcao())
    } senao se ((270 <= direcao()) e (direcao() < 315)) entao {
      alinhamento = negativo(modulo(direcao() - 270))
    }
    rotacionar(150, arredondar(alinhamento))
  }
}

tarefa atuadorEntregaVitima {
  baixar(300)
  girarbaixo(750)
  esperar(500)
  girarcima(750)
  levantar(300)
}


# tarefas do resgate

tarefa verificaSala {
  zerartemporizador()

  enquanto (temporizador() < 2500) farei {
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

    levantar(400)
    girarbaixo(500)
    levantar(300)

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
      } senao se ((temporizador() >= 7500) ou (ultra(1) < 25)) entao {
        trasrotacao(300, 15)
        parar()
        resgateDireitaCima = verdadeiro
        escrever(2, "resgate direita cima")
        interromper()
      }
      frente(175)
    }
    girarcima(500)
    baixar(1400)

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
    levantar(400)
    girarbaixo(500)
    levantar(300)

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
        saidaEsquerda = verdadeiro
        resgateDireitaCima = verdadeiro
        escrever(1, "saida esquerda")
        escrever(2, "resgate direita cima")
        interromper()
      } senao {
        frente(175)
      }
    }

    girarcima(500)
    baixar(1400)
  }
  paradinha()
}

tarefa procurandoVitimaVertical {
  enquanto (verdadeiro) farei {
    se (resgateDireitaCima) entao {
      se (ultra(1) < 81) entao {
        temArea = verdadeiro
        se (temalgo(2, 10, 165)) entao {
          se (temalgo(2, 0, 40)) entao {
            vitimaProxima = verdadeiro
          }
          interromper()
        } senao {
          se (ultra(1) > 253) entao {
            interromper()
          }
          tras(175)
        }
      } senao {
        temArea = falso
        se (temalgo(2, 10, 223)) entao {
          se (temalgo(2, 0, 40)) entao {
            vitimaProxima = verdadeiro
          }
          interromper()
        } senao {
          se (ultra(1) > 253) entao {
            interromper()
          }
          tras(175)
        }
      }
    } senao se (resgateDireitaBaixo) entao {
      se (ultra(1) >= 169) entao {
        temArea = verdadeiro

        se (ultra(1) < 220) entao {
          se (temalgo(2, 10, 160)) entao {
            se (temalgo(2, 0, 40)) entao {
              vitimaProxima = verdadeiro
            }
            interromper()
          } 
        } senao {
          se (temalgo(2, 10, 120)) entao {
            se (temalgo(2, 0, 40)) entao {
              vitimaProxima = verdadeiro
            }
            interromper()
          }
        } 

        se (ultra(1) <= 30) entao {
          interromper()
        }
        frente(175)

      } senao {
        temArea = falso
        se (temalgo(2, 10, 223)) entao {
          se (temalgo(2, 0, 40)) entao {
            vitimaProxima = verdadeiro
          }
          interromper()
        } senao {
          se (ultra(1) <= 30) entao {
            interromper()
          }
          frente(175)
        }
      }
    } senao {
      se (temalgo(2, 10, 223)) entao {
        se (temalgo(2, 0, 40)) entao {
          vitimaProxima = verdadeiro
        }
        interromper()
      } senao {
        se (ultra(1) > 253) entao {
          interromper()
        }
        tras(175)
      }
    }
  }
}

tarefa pegaVitimaVertical {
  catAdj = ultra(1) - 100
  se (resgateDireitaBaixo) entao {
    frenterotacao(300, 3)
  } senao {
    trasrotacao(300, 3)
  }

  se (vitimaProxima) entao {
    levantar(400)
    rotacionar(500, 90)
    alinhandoReto()

    frenterotacao(300, 15)
    trasrotacao(300, 15)

    baixar(500)
  } senao {
    rotacionar(500, 90)
    alinhandoReto()
  }

  zerartemporizador()
  se (temArea) entao {
    enquanto (ultra(1) > 100) farei {
      frente(225)
    }
    parar()
  } senao se (ultra(1) > 500) entao {
    enquanto (ultra(1) > 75) farei {
      se (((corverde(2) < 40) e (corvermelha(2) < 20) ou temporizador() >= 4250)) entao {
        parar()
        interromper()
      } senao {
        frente(225)
      }
    }
  } senao {
    enquanto (ultra(1) > 30) farei {
      frente(225)
    }
    frente(225)
    esperar(250)
  }

  parar()
  tempoDeRetorno = (temporizador() - 500)
  catOp = ((tempoDeRetorno * 45) / 1000)
  velocidadeatuador(150)
  levantar(267)
  velocidadeatuador(100)

  parar()
  esperar(900)
  
  se (resgateFrente == falso) entao {
    se ((corverde(2) < 40) e (corvermelha(2) < 20)) entao {
      trasrotacao(300, 17)
    } senao se (temArea == falso) entao {
      trasrotacao(300, 5)
    }
    parar()
  }

  alinhandoReto()
}

tarefa anguloDeRetorno {
  para angulo de 5 ate 90 passo 1 farei {
    se (cosseno(angulo) <= (catAdj / hip)) entao {
      interromper()
    }
  }
}

tarefa retornoSemVitimaVertical {
  enquanto (ultra(2) < 500) farei {
    tras(300)
  }
  tras(300)
  esperar(750)
  rotacionar(500, negativo(90))
}

tarefa entregaVitimaVertical {
  se (resgateDireitaCima e temArea == falso) entao {
    rotacionar(500, negativo(90))
    alinhandoReto()

    zerartemporizador()
    enquanto (corvermelha(5) > 2) farei {
      frente(175)
    }
    parar()
    catAdj = ((temporizador() * 37) / 1000)
    hip = raizquadrada((potencia(catAdj, 2) + potencia(catOp, 2)))
    alinhandoReto()

    atuadorEntregaVitima()
    anguloDeRetorno()

    rotacionar(500, angulo)

    tempoDeRetorno = arredondar((hip * 1000) / 61)
    escrevernumero(1, hip)
    escrevernumero(2, tempoDeRetorno)
    tras(300)
    esperar(tempoDeRetorno)
    parar()

    escrevernumero(3, angulo)
    rotacionar(500, negativo(angulo))

  } senao se (resgateDireitaBaixo e temArea == falso) entao {
    rotacionar(500, 90)
    alinhandoReto()

    zerartemporizador()
    enquanto (corvermelha(5) > 2) farei {
      frente(175)
    }
    parar()
    catAdj = ((temporizador() * 37) / 1000)
    hip = raizquadrada((potencia(catAdj, 2) + potencia(catOp, 2)))
    alinhandoReto()

    atuadorEntregaVitima()
    anguloDeRetorno()

    rotacionar(500, negativo(angulo))

    tempoDeRetorno = arredondar((hip * 1000) / 61)
    escrevernumero(1, hip)
    escrevernumero(2, tempoDeRetorno)
    tras(300)
    esperar(tempoDeRetorno)
    parar()

    escrevernumero(3, angulo)
    rotacionar(500, negativo(modulo(180 - angulo)))
  } senao se (resgateFrente) entao {
    hip = raizquadrada((potencia(catAdj, 2) + potencia(catOp, 2)))
    anguloDeRetorno()

    rotacionar(500, negativo(modulo(90+angulo)))

    tempoDeRetorno = arredondar((hip * 1000) / 61)
    frente(300)
    esperar(tempoDeRetorno)
    parar()

    rotacionar(500, modulo(angulo))
    enquanto (corvermelha(5) > 2) farei {
      frente(300)
    }
    parar()
    atuadorEntregaVitima()

    alinhandoReto()
    trasrotacao(300, 20)

  } senao se (resgateDireitaCima e temArea) entao {
    rotacionar(500, negativo(45))

    enquanto (corvermelha(5) > 2) farei {
      frente(225)
    }
    parar()

    atuadorEntregaVitima()

    rotacionar(500, 45)

    retornoSemVitimaVertical()
  } senao se (resgateDireitaBaixo e temArea) entao {
    rotacionar(500, 45)

    enquanto (corvermelha(5) > 2) farei {
      frente(225)
    }
    parar()

    atuadorEntregaVitima()

    rotacionar(500, negativo(45))

    retornoSemVitimaVertical()
  }

  limparconsole()
}

tarefa resgataBolinhaEntrada {
  enquanto (ultra(1) > 29) farei {
    frente(225)
  }
  frente(225)
  esperar(250)
  parar()

  se (temvitima()) entao {
    levantar(400)
    esperar(1000)

    alinhandoReto()

    se (resgateDireitaCima) entao {
      trasrotacao(300, 5)
      rotacionar(500, 90)
      zerartemporizador()
      enquanto (corvermelha(5) > 2) farei {
        frente(300)
      }
      parar()
      tempoDeRetorno = temporizador()
      atuadorEntregaVitima()
      tras(300)
      esperar(tempoDeRetorno)

      rotacionar(500, negativo(90))
    } senao se (resgateDireitaBaixo) entao {
      trasrotacao(300, 5)
      rotacionar(500, 135)
      zerartemporizador()
      enquanto (corvermelha(5) > 2) farei {
        frente(300)
      }
      parar()
      tempoDeRetorno = temporizador()
      atuadorEntregaVitima()
      tras(300)
      esperar(tempoDeRetorno)

      rotacionar(500, negativo(135))
    }

    baixar(600)
    alinhandoReto()
  }
}

tarefa verificacaoVertical {
  enquanto (verdadeiro) farei {
    procurandoVitimaVertical()
    se (resgateDireitaBaixo) entao {
      se (ultra(1) <= 30) entao {
        interromper()
      }
    } senao {
      se (ultra(1) > 253) entao {
        interromper()
      }
    }
    pegaVitimaVertical()
    parar()
    esperar(500)
    se (temvitima()) entao {
      entregaVitimaVertical()
    } senao {
      retornoSemVitimaVertical()
    }
    alinhandoReto()
    baixar(500)

    angulo = 5
    catAdj = 0
    catOp = 0
    hip = 0
    temArea = falso
    vitimaProxima = falso
  }
  parar()
}

tarefa encontraPegaVitima {
  velocidadeatuador(100)
  girarcima(100)
  baixar(350)
  alinhandoReto()

  se (resgateDireitaCima) entao {
    resgataBolinhaEntrada()
    baixar(250)
    verificacaoVertical()

  } senao se (resgateDireitaBaixo) entao {
    resgataBolinhaEntrada()
    enquanto (ultra(1) < 250) farei {
      tras(300)
    }
    parar()
    frenterotacao(300, 10)
    baixar(250)
    verificacaoVertical()

  } senao se (resgateFrente) entao {
    baixar(250)
    verificacaoVertical()
  }
}

tarefa saidaDoResgate {
  se (saidaDireita) entao {
    alinhandoReto()
    frenterotacao(300, 15)
    rotacionar(500, 90)
    parar()
    alinhandoReto()

    velocidadeatuador(200)
    levantar(500)
    girarbaixo(500)

  } senao {
    se (saidaFrente e resgateFrente) entao {
      hip = raizquadrada((potencia(215, 2) + potencia(215, 2)))
      tempoDeRetorno = arredondar((hip * 1000) / 61)

      rotacionar(500, 45)

      frente(300)
      esperar(tempoDeRetorno-1500)

      rotacionar(500, 45)
    } senao se (saidaFrente e resgateDireitaBaixo) entao {
      rotacionar(500, 90)
    }
    alinhandoReto()

    velocidadeatuador(200)
    levantar(500)
    girarbaixo(500)

    enquanto (ultra(1) > 25) farei {
      frente(300)
    }
    parar()

    rotacionar(500, negativo(90))
  }

  enquanto (38 < corverde(2) e 20 < corvermelha(2) e 25 < corazul(2)) farei {
    frente(300)
  }

  frenterotacao(300, 10)

  enquanto (cor(1) != "PRETO") farei {
    esquerda(1000)
  }
  enquanto (cor(3) != "PRETO") farei {
    direita(1000)
  }

  limparconsole()
}


# inicio da programação

inicio
# CALIBRAÇÃO POR HORÁRIO
  se ((horario < 8) ou (16 < horario)) entao {
    ajustarcor(45)
  } senao se (((8 <= horario) e (horario < 11)) ou ((13 < horario) e (horario <= 16))) entao  {
    ajustarcor(35)
  } senao {
    ajustarcor(30)
  }

# MOVIMENTAÇÃO INICIAL DO ATUADOR
  velocidadeatuador(150)
  levantar(750)
  girarbaixo(1000)

# MOVIMENTAÇÃO DO ROBÔ
  enquanto (verdadeiro) farei {
    se ((ultra(1) <= 10) e (cor(5) != "BRANCO")) entao {
      paradinha()
      alinhandoReto()
      paradinha()

      trasrotacao(300, 14)
      rotacionar(500, 30)

      frente(300)
      esperar(1000)

      rotacionar(500, negativo(30))
      alinhandoReto()
      enquanto (ultra(3) > 40) farei {
        frente(300)
      }
      enquanto (ultra(3) < 40) farei {
        frente(300)
      }
      rotacionar(500, negativo(30))
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
          enquanto (cor(1) != "PRETO") farei {
            esquerda(1000)
          }
          enquanto (cor(3) != "PRETO") farei {
            direita(1000)
          }
          parar()
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
          rotacionar(500, negativo(30))
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
          frenterotacao(300, 6)

          angulo = 0
          se (travessa) entao {
            frenterotacao(300, 5)

          } senao se (viraDireita) entao {
            enquanto ((cor(3) != "PRETO") e (angulo < 180)) farei {
              direita(1000)
              esperar(30)
              angulo = angulo + 1
            }

            se (cor(3) != "PRETO" e angulo >= 180) entao {
              rotacionar(500, negativo(90))
              alinhandoReto()
              trasrotacao(300, 7)

              enquanto (cor(2) != "PRETO") farei {
                esquerda(1000)
              }

              zerartemporizador()
              enquanto (temporizador() <= 1250) farei {
                segueLinha()
              }

              frenterotacao(300, 9)
              alinhandoReto()
              trasrotacao(300, 9)
            }

          } senao se (viraEsquerda) entao {
            enquanto ((cor(2) != "PRETO") e (angulo < 180)) farei {
              esquerda(1000)
              esperar(30)
              angulo = angulo + 1
            }

            se (cor(2) != "PRETO" e angulo >= 180) entao {
              rotacionar(500, 90)
              alinhandoReto()
              trasrotacao(300, 7)

              enquanto (cor(3) != "PRETO") farei {
                direita(1000)
              }

              zerartemporizador()
              enquanto (temporizador() <= 1250) farei {
                segueLinha()
              }

              frenterotacao(300, 9)
              alinhandoReto()
              trasrotacao(300, 9)
            }

          }

          angulo = 5
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
            saidaDoResgate()

            resgateConcluido = verdadeiro

            velocidadeFrenteSeguidor = 150
          } senao se ((corvermelha(2) > 60) e (corazul(2) > 10) e resgateConcluido e cor(2) == "VERMELHO") entao {
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