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

numero linha = 0

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

tarefa entregarVitima {
  baixar(350)
  velocidadeatuador(200)
  girarbaixo(750)
  esperar(500)
  girarcima(750)
  velocidadeatuador(100)
  levantar(350)
}

# UMA ROTAÇÃO === 2.5 DISTANCIA

tarefa andaParaLinha {
  # verifica qual linha tem vítima andando de ré
  # vira 90° quando encontrar
  # executa alinhandoReto()
  # anda reto até ter vitima no atuador por mais de 1 seg
  # levanta atuador
  # vai pro final da linha ou retorna (depende de onde estiver a área de resgate)
  # leva a vítima até a área
  # entrega a vítima, retorna o atuador
  # retorna um pouco
  # alinha novamente
  # reinicia ciclo
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
      se ((ultra(3) > 50) e (ultra(1) <= 85)) entao {
        saidaEsquerda = verdadeiro
        interromper()
      } senao se (ultra(1) <= 85) entao {
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

  parar()

  # TODO => transformar em tarefa resgateDeVitimas

  se ((saidaDireita) e (resgateFrente)) entao {
    escrever(1, "saidaDireita")
    escrever(2, "resgateFrente")

  } senao se ((saidaDireita) e (resgateDireitaCima)) entao {
    escrever(1, "saidaDireita")
    escrever(2, "resgateDireitaCima")

  } senao se ((saidaEsquerda) e (resgateDireitaBaixo)) entao {
    escrever(1, "saidaEsquerda")
    escrever(2, "resgateDireitaBaixo")

  } senao se ((saidaEsquerda) e (resgateDireitaCima)) entao {
    escrever(1, "saidaEsquerda")
    escrever(2, "resgateDireitaCima")

  } senao se ((saidaFrente) e (resgateDireitaBaixo)) entao {
    escrever(1, "saidaFrente")
    escrever(2, "resgateDireitaBaixo")

  } senao se ((saidaFrente) e (resgateFrente)) entao {
    escrever(1, "saidaFrente")
    escrever(2, "resgateFrente")

  }

  parei()
  entregarVitima()
  limparconsole()
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