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

numero contagem = 0

numero contResgate = 0
numero contSaida = 0

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
  se ((0 <= direcao()) e (direcao() < 17)) entao {
    alinhamento = negativo(direcao())
  } senao se ((345 < direcao()) e (direcao() < 360)) entao {
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

tarefa verificaSala {
  zerartemporizador()

  enquanto (temporizador() < 3000) farei {
    se ((160 < ultra(2)) e (ultra(2) < 225)) entao {
      contResgate = contResgate + 1
    } senao se (ultra(2) < 160) entao {
      # leitura de bola
    } senao se (300 < ultra(2)) entao {
      contSaida = contSaida + 1
    }
    frente(100)
  limparlinha(1)
  }

  zerartemporizador()

  se (contSaida > contResgate) entao {
    saidaDireita = verdadeiro
    escrever(1, "saidaDireita")

    enquanto (verdadeiro) farei {
      se (temporizador() > 4500) entao {
        escrever(2, "resgateFrente")
        resgateFrente = verdadeiro

        levantar(500)
        frenterotacao(200, 4)
        girarbaixo(250)
        baixar(250)

        interromper()
      } senao se (ultra(1) < 60) entao {
        escrever(2, "resgateDireitaCima")
        resgateDireitaCima = verdadeiro
        interromper()
      } senao {
        frente(150)
      }
    }
  } senao se (contResgate > contSaida) entao {
    resgateDireitaBaixo = verdadeiro
    escrever(1, "resgateDireitaBaixo")

    enquanto (verdadeiro) farei {
      se (ultra(3) > 50) entao {
        escrever(2, "saidaEsquerda")
        saidaEsquerda = verdadeiro
        interromper()
      } senao se (ultra(1) < 40) entao {
        escrever(2, "saidaFrente")
        saidaFrente = verdadeiro
        interromper()
      } senao {
        frente(150)
      }
    }
  } senao {
    enquanto (verdadeiro) farei {
      se (temporizador() > 3500) entao {
        escrever(1, "resgateFrente")
        escrever(2, "saidaFrente")
        resgateFrente = verdadeiro
        saidaFrente = verdadeiro

        levantar(500)
        frenterotacao(200, 4)
        girarbaixo(250)
        baixar(250)

        interromper()
      } senao se (ultra(3) > 50) entao {
        escrever(1, "saidaEsquerda")
        escrever(2, "resgateDireitaCima")
        saidaEsquerda = verdadeiro
        resgateDireitaCima = verdadeiro
        interromper()
      } senao {
        frente(150)
      }
    }
  }

  parar()
  levantar(500)
  limparconsole()
  parei()
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

      velocidadeBranco = 250
      enquanto ((inclinacao() != 0) e (ultra(2) != 10)) farei {
        se ((temporizador() >= 1500) e (temporizador() <= 1600)) entao {
          parar()
          velocidadeatuador(500)
          baixar(500)
          enquanto (angulogiroatuador() > 10) farei {
            girarcima(1)
          }
        }
        segueLinhaComBranco()
      }
      velocidadeBranco = 125

      # NA SALA DE RESGATE
      paradinha()
      alinhandoReto()
      paradinha()
      alinhandoReto()
      paradinha()

      velocidadeatuador(100)
      enquanto (modulo(angulogiroatuador()) != 358) farei {
        girarbaixo(1)
      }
      enquanto (modulo(anguloatuador()) != 12) farei {
        baixar(1)
      }
      paradinha()

      # ANALISANDO A SALA
      verificaSala()

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