# USANDO O ROBÔ 3

# VARIAVEIS
numero horario = 12

numero alinhamento = 0
numero tempoDeRetorno = 0

booleano viraEsquerda = falso
booleano viraDireita = falso
booleano travessa = falso
booleano tempoEsgotou = falso

numero contagemGenerica = 0
booleano desvioEsquerda = falso

numero canto = 0
numero vitima = 0
numero distanciaDaVitima = 0
booleano vitimaViva = verdadeiro

booleano resgateFinalizado = falso

# TAREFAS DE CONTROLE DO ROBÔ
tarefa segueLinha {
  se (cor(2) == "PRETO" e cor(3) == "PRETO") entao { frente(175) esperar(30) }

  se (cor(2) == "BRANCO" e cor(3) == "BRANCO") entao { frente(175) esperar(30) }

  se (cor(2) == "PRETO") entao { direita(1000) }

  se (cor(3) == "PRETO") entao { esquerda(1000) }
}

tarefa paradinha { parar() esperar(250) }
tarefa parei { enquanto (verdadeiro) farei { parar() } }

tarefa alinhaReto {
  para contagemGenerica de 0 ate 2 passo 1 farei {
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

    alinhamento = arredondar(alinhamento)

    se (alinhamento == 0 ou alinhamento == 359) entao { parartarefa() }
    rotacionar(150, alinhamento)
  }
  contagemGenerica = 0
}

# TAREFAS DE DESVIO DE OBSTÁCULO

tarefa primeiroLadoDireita {
  enquanto (cor(2) != "PRETO" e cor(3) != "PRETO" e cor(4) != "PRETO" e ultra(3) > 7)
  farei { 
    se (cor(4) == "VERMELHO") entao { interromper() }
    frente(300)
  }

  paradinha()

  se (cor(4) == "VERMELHO") entao { 
    rotacionar(500, negativo(30))
  } senao se (cor(2) == "PRETO" ou cor(3) == "PRETO" ou cor(4) == "PRETO") entao {
    enquanto (cor(1) != "PRETO") farei { frente(100) }
    frenterotacao(300, 12)
    rotacionar(500, 60)
    enquanto (toque(1) == falso) farei { tras(150) }
    parartarefa()
  } senao {
    frenterotacao(300, 4)
  }

  rotacionar(500, negativo(30))
  paradinha()
  enquanto (ultra(3) > 20) farei { frente(100) }
  enquanto (ultra(3) < 20) farei { frente(100) }
  frenterotacao(300, 3)
  rotacionar(500, negativo(45))
  parar()
}

tarefa segundoLadoDireita {
  zerartemporizador()
  enquanto (cor(2) != "PRETO" e cor(3) != "PRETO" 
  e cor(4) != "PRETO" e ultra(3) < 20)
  farei { 
    se (cor(4) == "VERMELHO") entao { interromper() }
    frente(300)
  }
  parar()

  se (cor(4) == "VERMELHO") entao {
    rotacionar(500, negativo(45))
  } senao se (cor(2) == "PRETO" ou cor(3) == "PRETO" ou cor(4) == "PRETO") entao {
    enquanto (cor(1) != "PRETO") farei { frente(100) }
    frenterotacao(300, 10)
    rotacionar(500, 45)
    enquanto (toque(1) == falso) farei { tras(150) }
    parartarefa()
  } senao {
    frenterotacao(300, 4)
    rotacionar(500, negativo(45))
  }

  paradinha()
  alinhaReto()
  rotacionar(500, negativo(45))
  parar()
}

tarefa terceiroLadoDireita {
  zerartemporizador()
  enquanto (cor(2) != "PRETO" e cor(3) != "PRETO" 
  e cor(4) != "PRETO" e temporizador() < 850)
  farei { frente(300) }
  parar()

  se (cor(2) == "PRETO" ou cor(3) == "PRETO" ou cor(4) == "PRETO") entao {
    enquanto (cor(1) != "PRETO") farei { frente(100) }
    frenterotacao(300, 10)
    rotacionar(500, 45)
    alinhaReto()
    enquanto (toque(1) == falso) farei { tras(150) }
  }
}

tarefa primeiroLadoEsquerda {
  enquanto (cor(2) != "PRETO" e cor(3) != "PRETO" e cor(1) != "PRETO" e ultra(2) > 7)
  farei { 
    se (cor(1) == "VERMELHO") entao { interromper() }
    frente(300)
  }
  parar()

  paradinha()

  se (cor(1) == "VERMELHO") entao { 
    rotacionar(500, 30)
  } senao se (cor(2) == "PRETO" ou cor(3) == "PRETO" ou cor(1) == "PRETO") entao {
    enquanto (cor(4) != "PRETO") farei { frente(100) }
    frenterotacao(300, 12)
    rotacionar(500, negativo(60))
    enquanto (toque(1) == falso) farei { tras(150) }
    parartarefa()
  } senao {
    frenterotacao(300, 4)
  }

  rotacionar(500, 30)
  paradinha()
  enquanto (ultra(2) > 20) farei { frente(100) }
  enquanto (ultra(2) < 20) farei { frente(100) }
  frenterotacao(300, 3)
  rotacionar(500, 45)
  parar()
}

tarefa segundoLadoEsquerda {
  zerartemporizador()
  enquanto (cor(2) != "PRETO" e cor(3) != "PRETO" 
  e cor(1) != "PRETO" e ultra(2) < 20)
  farei { frente(300) }
  parar()

  se (cor(2) == "PRETO" ou cor(3) == "PRETO" ou cor(1) == "PRETO") entao {
    enquanto (cor(4) != "PRETO") farei { frente(100) }
    frenterotacao(300, 10)
    rotacionar(500, negativo(45))
    enquanto (toque(1) == falso) farei { tras(150) }
    parartarefa()
  } 
}

tarefa desvioDeObstaculo {
  paradinha()
  alinhaReto()

  se (ultra(2) < 50) entao { desvioEsquerda = verdadeiro }
  enquanto (ultra(1) < 25) farei { tras(300) }

  se (desvioEsquerda) entao {
    rotacionar(500, negativo(30))

    primeiroLadoEsquerda()
    se (toque(1)) entao { parartarefa() }

    segundoLadoEsquerda()
  } senao {
    rotacionar(500, 30)

    primeiroLadoDireita()
    se (toque(1)) entao { parartarefa() }

    segundoLadoDireita()
    se (toque(1)) entao { parartarefa() }

    terceiroLadoDireita()
  }

  desvioEsquerda = falso
}

# TAREFAS DE CURVAS

tarefa reiniciaVariaveisDeCurva {
  viraEsquerda = falso
  viraDireita = falso
  travessa = falso
  tempoEsgotou = falso
}

tarefa confirmaSeEstaNaCurva {
  se (cor(1) != "VERDE" e cor(2) != "VERDE" e cor(3) != "VERDE" e cor(4) != "VERDE") entao {
    se (cor(1) != "PRETO" e cor(4) != "PRETO") entao {
      zerartemporizador()
      enquanto (cor(1) != "PRETO" e cor(4) != "PRETO") farei {
        se (temporizador() > 4000) entao {
          tempoEsgotou = verdadeiro
          parar()
          parartarefa()
        }
        senao { tras(50) }
      }
    }
  }
}

tarefa verificaLadoPreto {
  se (cor(1) == "PRETO" e cor(4) == "PRETO") entao {
    travessa = verdadeiro
  } senao se (cor(1) == "PRETO" e cor(4) != "PRETO") entao {
    viraDireita = verdadeiro
  } senao se (cor(1) != "PRETO" e cor(4) == "PRETO") entao {
    viraEsquerda = verdadeiro
  }
}

tarefa verificaLadoVerde {
  se ((cor(1) == "VERDE" e cor(3) == "VERDE")
  ou (cor(2) == "VERDE" e cor(4) == "VERDE")) entao {
    travessa = verdadeiro
  } senao se ((cor(1) == "VERDE" ou cor(2) == "VERDE")
  e (cor(3) != "VERDE" e cor(4) != "VERDE")) entao {
    viraDireita = verdadeiro
  } senao se ((cor(1) != "VERDE" e cor(2) != "VERDE")
  e (cor(3) == "VERDE" ou cor(4) == "VERDE")) entao {
    viraEsquerda = verdadeiro
  }
}

tarefa virandoDireitaPosPreto {
  enquanto (cor(3) != "PRETO") farei { direita(1000) }
  enquanto (cor(2) != "PRETO") farei { esquerda(1000) }
  parar()
}

tarefa virandoEsquerdaPosPreto {
  enquanto (cor(2) != "PRETO") farei { esquerda(1000) }
  enquanto (cor(3) != "PRETO") farei { direita(1000) }
  parar()
}

tarefa curvaEmPreto {
  paradinha()

  se (cor(1) != "PRETO" e cor(2) != "PRETO"
  e cor(3) != "PRETO" e cor(4) != "PRETO") entao {
    se (corvermelha(1) < 20) entao {
      enquanto (cor(3) != "PRETO") farei { esquerda(1000) }
      parartarefa()
    } senao se (corvermelha(4) < 20) entao {
      enquanto (cor(2) != "PRETO") farei { direita(1000) }
      parartarefa()
    }
  }

  confirmaSeEstaNaCurva()

  se (tempoEsgotou) entao {
    reiniciaVariaveisDeCurva()
    parartarefa()
  }
  senao { verificaLadoPreto() }

  frenterotacao(300, 6)

  se (travessa) entao { frenterotacao(300, 5) }
  senao se (viraDireita) entao { virandoDireitaPosPreto() }
  senao se (viraEsquerda) entao { virandoEsquerdaPosPreto() }

  reiniciaVariaveisDeCurva()
}


tarefa virandoDireitaPosVerde {
  rotacionar(500, 30)
  trasrotacao(300, 5)

  enquanto (cor(3) != "PRETO") farei { direita(1000) }
  enquanto (cor(2) != "PRETO") farei { esquerda(1000) }

  parar()
}

tarefa virandoEsquerdaPosVerde {
  rotacionar(500, negativo(30))
  trasrotacao(300, 5)

  enquanto (cor(2) != "PRETO") farei { esquerda(1000) }
  enquanto (cor(3) != "PRETO") farei { direita(1000) }

  parar()
}

tarefa curvaEmVerde {
  paradinha()
  confirmaSeEstaNaCurva()

  se (tempoEsgotou) entao {
    reiniciaVariaveisDeCurva()
    parartarefa()
  }
  senao { verificaLadoVerde() }

  frenterotacao(300, 16) 

  se (travessa) entao { rotacionar(500, 180) }
  senao se (viraDireita) entao { virandoDireitaPosVerde() }
  senao se (viraEsquerda) entao { virandoEsquerdaPosVerde() }

  reiniciaVariaveisDeCurva()
}

# TAREFAS DO RESGATE

tarefa abaixaGarra {
  baixar(700)
  girarbaixo(30)
  abrir(10)
}

tarefa levantaGarra {
  fechar(10)
  girarcima(30)
  levantar(700)
}

tarefa pegaKitDeResgate {
  tras(300)
  esperar(515) # +/- 15 rotações
  parar()
  abaixaGarra()

  zerartemporizador()
  enquanto (temKit() == falso) farei {
    frente(150)
  }
  esperar(400)
  tempoDeRetorno = temporizador() - 515

  levantaGarra()
  tras(300)
  esperar(tempoDeRetorno)
  parar()
  esperar(10)
}

tarefa despejaObjeto {
  abaixaGarra()
  girarbaixo(250)
  esperar(750)
  girarcima(250)
  levantaGarra()
}

tarefa procuraAreaDeResgatePelaDireita {
  canto = 1
  enquanto (verdadeiro) farei {
    se (corvermelha(5) < 3 e cor(5) == "PRETO") entao { interromper() }
    senao se (ultra(1) < 12) entao {
      trasrotacao(300, 10)
      rotacionar(500, negativo(90))
      alinhaReto()
      canto = canto + 1
    } senao { frente(300) }
  }
  parar()

  rotacionar(500, 45)
  paradinha()
  despejaObjeto()

  rotacionar(500, negativo(90))
  enquanto (ultra(1) > 17) farei { frente(150) }
  parar()
  rotacionar(500, negativo(45))
}

tarefa procuraAreaDeResgatePelaEsquerda {
  canto = 1
  enquanto (verdadeiro) farei {
    se (corvermelha(5) < 3 e cor(5) == "PRETO") entao { interromper() }
    senao se (ultra(1) < 12) entao {
      trasrotacao(300, 10)
      rotacionar(500, 90)
      alinhaReto()
      canto = canto + 1
    } senao { frente(300) }
  }
  parar()

  rotacionar(500, negativo(45))
  paradinha()
  despejaObjeto()

  rotacionar(500, 90)
  enquanto (ultra(1) > 17) farei { frente(150) }
  parar()
  rotacionar(500, 45)
}

tarefa procuraVitimaNaDireita {
  enquanto (verdadeiro) farei {
    se (temalgo(2, 15, 215)) entao {
      distanciaDaVitima = ultra(2)-23
      interromper()
    } senao se (ultra(1) < 12) entao {
      vitima = 2
      enquanto (toque(1) == falso) farei { tras(300) }
      parartarefa()
    } senao { frente(150) }
  }
}

tarefa procuraVitimaNaEsquerda {
  enquanto (verdadeiro) farei {
    se (temalgo(3, 15, 215)) entao {
      distanciaDaVitima = ultra(3)-23
      interromper()
    }
    senao se (ultra(1) < 12) entao { rotacionar(500, negativo(90)) }
    senao { frente(150) }
  }
}

tarefa verificaSeEstaViva {
  distanciaDaVitima = arredondar((distanciaDaVitima / 28) * 1000)
  zerartemporizador()
  enquanto (temporizador() <= distanciaDaVitima) farei {
    se (corvermelha(5) == corverde(5)) entao {
      se (8 < corvermelha(5) e corvermelha(5) < 11) entao {
        vitimaViva = falso
        interromper()
      } senao { frente(150) }
    } senao { frente(150) }
  }
  tempoDeRetorno = temporizador() + 500
}

tarefa pegaVitima {
  trasrotacao(300, 10)

  abaixaGarra()
  enquanto (temvitima() == falso e (temporizador() - tempoDeRetorno - 1250) < 3000 )
  farei { frente(150) }
  frenterotacao(150, 5)
  tempoDeRetorno = temporizador()
  levantaGarra()
}

tarefa entregaVitima {
  rotacionar(500, 90)
  enquanto (cor(5) != "PRETO") farei { frente(300) }
  frente(200) esperar(500)
  parar()

  rotacionar(500, 45)
  frente(100) esperar(500)
  parar()
  despejaObjeto()
  vitima = vitima + 1

  trasrotacao(300, 5)
  rotacionar(500, negativo(225))
  alinhaReto()
}

tarefa salaDeResgate { parei() }


inicio
  se ((horario < 8) ou (16 < horario)) entao { ajustarcor(45) }
  senao se (((8 <= horario) e (horario < 11))
    ou ((13 < horario) e (horario <= 16))) entao  { ajustarcor(35) }
  senao { ajustarcor(30) }

  velocidadeatuador(150)
  levantar(1000)
  fechar(50)

  enquanto (verdadeiro) farei {
    se ((42 < corvermelha(3) e corvermelha(3) < 46) e (52 < corazul(3) e corazul(3) < 56))
      entao { 
        salaDeResgate()
        resgateFinalizado = verdadeiro
    } senao {
      se (ultra(1) <= 10 e cor(5) != "BRANCO") entao {
        desvioDeObstaculo()
      } senao se ((19 < corvermelha(5) e corvermelha(5) < 21) 
        e (39 < corverde(5) e corverde(5) < 41) 
        e (56 < corazul(5) e corazul(5) < 58)) 
        entao {
          pegaKitDeResgate()
      } senao { 
        se (cor(1) == "VERDE" ou cor(2) == "VERDE"
        ou cor(3) == "VERDE" ou cor(4) == "VERDE") entao {
          curvaEmVerde()
        } senao se (corvermelha(1) < 25 ou cor(1) == "PRETO"
        ou corvermelha(4) < 25 ou cor(4) == "PRETO") entao {
          curvaEmPreto()
        } senao {
          se (resgateFinalizado e (corvermelha(2) > 60 e corazul(2) > 10)) entao {
            parei()
          } senao { segueLinha() }
        }
      }
    }
  }
  
fim