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
tarefa encontraVitima {
  se (linha == 9) entao {

    se (temalgo(2, 125, 140)) entao {
      adicionarlistanumero(linha, 6)
      escrever(2, "col 6")
    }

  } senao se (linha == 8) entao {

    se (temalgo(2, 150, 160)) entao {
      adicionarlistanumero(linha, 7)
      escrever(2, "col 6")
    } senao se (temalgo(2, 125, 150)) entao {
      adicionarlistanumero(linha, 6)
      escrever(2, "col 6")
    }

  } senao se (linha == 7) entao {
    se (temalgo(2, 150, 175)) entao {
      adicionarlistanumero(linha, 7)
      escrever(2, "col 7")
    } senao se (temalgo(2, 125, 150)) entao {
      adicionarlistanumero(linha, 6)
      escrever(2, "col 6")
    }

  } senao se (linha == 6) entao {

    se (temalgo(2, 175, 195)) entao {
      adicionarlistanumero(linha, 8)
      escrever(2, "col 8")
    } senao se (temalgo(2, 150, 175)) entao {
      adicionarlistanumero(linha, 7)
      escrever(2, "col 7")
    } senao se (temalgo(2, 125, 150)) entao {
      adicionarlistanumero(linha, 6)
      escrever(2, "col 6")
    }

  } senao {
    se (temalgo(2, 200, 225)) entao {
      adicionarlistanumero(linha, 9)
      escrever(2, "col 9")
    } senao se (temalgo(2, 175, 200)) entao {
      adicionarlistanumero(linha, 8)
      escrever(2, "col 8")
    } senao se (temalgo(2, 150, 175)) entao {
      adicionarlistanumero(linha, 7)
      escrever(2, "col 7")
    } senao se (temalgo(2, 125, 150)) entao {
      adicionarlistanumero(linha, 6)
      escrever(2, "col 6")
    } 
  }

  se (temalgo(2, 100, 125)) entao {
    adicionarlistanumero(linha, 5)
      escrever(2, "col 5")
  } senao se (temalgo(2, 75, 100)) entao {
    adicionarlistanumero(linha, 4)
      escrever(2, "col 4")
  } senao se (temalgo(2, 50, 75)) entao {
    adicionarlistanumero(linha, 3)
      escrever(2, "col 3")
  } senao se (temalgo(2, 25, 50)) entao {
    adicionarlistanumero(linha, 2)
      escrever(2, "col 2")
  } senao se (temalgo(2, 0, 25)) entao {
    adicionarlistanumero(linha, 1)
      escrever(2, "col 1")
  }
}

tarefa detectaVitima {
  se (ultra(1) >= 224) entao {
    linha = 9
    escrever(1, "lin 9")
  } senao se (temalgo(1, 208, 224)) entao {
    linha = 8
    escrever(1, "lin 8")
  } senao se (temalgo(1, 192, 208)) entao {
    linha = 7
    escrever(1, "lin 7")
  } senao se (temalgo(1, 176, 192)) entao {
    linha = 6
    escrever(1, "lin 6")
  } senao se (temalgo(1, 160, 176)) entao {
    linha = 5
    escrever(1, "lin 5")
  } senao se (temalgo(1, 144, 160)) entao {
    linha = 4
    escrever(1, "lin 4")
  } senao se (temalgo(1, 128, 144)) entao {
    linha = 3
    escrever(1, "lin 3")
  } senao se (temalgo(1, 112, 128)) entao {
    linha = 2
    escrever(1, "lin 2")
  } senao se (temalgo(1, 85, 112)) {
    linha = 1
    escrever(1, "lin 1")
  } senao se (temalgo(1, 60, 85)) entao {
    linha = 0
    escrever(1, "lin 0")
  }
  encontraVitima()
  limparconsole()
}

tarefa andaParaLinha {
  # verifica qual linha tem vítima
  # anda de ré até a linha
  # vira 90°
  # executa alinhandoReto()
  # anda reto até ter vitima no atuador por mais de 1 seg
  # levanta atuador
  # vai pro final da linha ou retorna (depende de onde estiver a área de resgate)
  # leva a vítima até a área

}


tarefa verificaSala {
  zerartemporizador()

  enquanto (temporizador() < 3000) farei {
    se (temalgo(2, 160, 225)) entao {
      contResgate = contResgate + 1
    } senao se (300 < ultra(2)) entao {
      contSaida = contSaida + 1
    }
    detectaVitima()
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
        detectaVitima()
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
        detectaVitima()
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
        detectaVitima()
        frente(125)
      }
    }
  }

  parar()

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

    enquanto (ultra(1) >= 60) {
      detectaVitima()
      frente(125)
    }
    parar()



  } senao se ((saidaFrente) e (resgateFrente)) entao {
    escrever(1, "saidaFrente")
    escrever(2, "resgateFrente")

    enquanto (ultra(1) >= 65) {
      detectaVitima()
      frente(125)
    }
    parar()

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
      alinhandoReto()
      paradinha()
      alinhandoReto()
      paradinha()
      alinhandoReto()
      paradinha()

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