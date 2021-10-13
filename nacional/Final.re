# USANDO O ROBÔ 3

# VARIAVEIS
numero horario = 9.5

numero alinhamento = 0
numero tempoDeRetorno = 0

booleano viraEsquerda = falso
booleano viraDireita = falso
booleano travessa = falso
booleano tempoEsgotou = falso

numero contagemGenerica = 0
booleano desvioEsquerda = falso

numero diferencaDeCorSensor2 = 0
numero diferencaDeCorSensor3 = 0

booleano vitimaNaEsquerda = falso
booleano vitimaNaDireita = falso

booleano ladoMaior = falso
booleano ladoMenor = falso
booleano mudouDirecao = falso

numero vitima = 0
numero distanciaDaVitima = 0
booleano vitimaViva = verdadeiro
booleano terminouProcura = falso

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

# CURVA PRETO

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
  zerartemporizador()
  enquanto (cor(3) != "PRETO") farei {
    se (temporizador() >= 3333) entao {
      parar()
      trasrotacao(300, 5)
      interromper()
    } senao {
      direita(1000)
    }
  }
  enquanto (cor(2) != "PRETO") farei { esquerda(1000) }
  parar()
}

tarefa virandoEsquerdaPosPreto {
  zerartemporizador()
  enquanto (cor(2) != "PRETO") farei {
    se (temporizador() >= 3333) entao {
      parar()
      trasrotacao(300, 5)
      interromper()
    } senao {
      esquerda(1000)
    }
  }
  enquanto (cor(3) != "PRETO") farei { direita(1000) }
  parar()
}

tarefa curvaEmPreto {
  paradinha()

  se (cor(1) != "PRETO" e cor(2) != "PRETO"
  e cor(3) != "PRETO" e cor(4) != "PRETO") entao {
    se (corvermelha(1) < 20) entao {
      enquanto (cor(3) != "PRETO") farei { esquerda(1000) } parar()
      parartarefa()
    } senao se (corvermelha(4) < 20) entao {
      enquanto (cor(2) != "PRETO") farei { direita(1000) } parar()
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

# CURVA VERDE

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
  tras(300) esperar(515) # +/- 15 rotações
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
  esperar(tempoDeRetorno / 2)
  parar()
  esperar(10)
}

tarefa despejaObjeto {
  abaixaGarra()
  girarbaixo(250)
  esperar(750)
  zerartemporizador()
  se (temvitima()) entao {
    enquanto (temvitima() e temporizador() < 2500) farei {esperar(60)}
  } senao se (temKit()) entao {
    enquanto (temKit() e temporizador() < 2500) farei {esperar(60)}
  }
  girarcima(250)
  levantaGarra()
}

tarefa verificaTamanhoLado {
  se (temalgo(1, 300, 400)) entao {
    ladoMaior = verdadeiro
    ladoMenor = falso
  } senao se (temalgo(1, 200, 300)) entao {
    ladoMaior = falso
    ladoMenor = verdadeiro
  }
}

tarefa inverteTamanhoLado {
  se (ladoMaior) entao {
    ladoMaior = falso
    ladoMenor = verdadeiro
  } senao se (ladoMenor) entao {
    ladoMaior = verdadeiro
    ladoMenor = falso
  }
}

tarefa procuraAreaComParedeNaDireita {
  enquanto (verdadeiro) farei {
    se (corvermelha(5) < 3 e cor(5) == "PRETO") entao { interromper() }
    senao se (ultra(1) < 12) entao {
      trasrotacao(300, 10)
      rotacionar(500, negativo(90))
      alinhaReto()
      inverteTamanhoLado()
    } senao { frente(300) }
  }
  parar()

  rotacionar(500, 45)
  paradinha()
  despejaObjeto()

  inverteTamanhoLado()
  rotacionar(500, negativo(45))
  alinhaReto()

  se (ladoMaior) entao {
    rotacionar(500, negativo(45))
    enquanto (ultra(1) > 17) farei { frente(150) } parar()
    rotacionar(500, negativo(45))
  } senao {
    mudouDirecao = verdadeiro
    trasrotacao(300, 10)
    rotacionar(500, negativo(225))
    enquanto (ultra(1) > 17) farei { frente(150) } parar()
    rotacionar(500, 45)
  }

}

tarefa procuraAreaComParedeNaEsquerda {
  enquanto (verdadeiro) farei {
    se (corvermelha(5) < 3 e cor(5) == "PRETO") entao { interromper() }
    senao se (ultra(1) < 12 ou (30 < corverde(2) e corverde(2) < 38)) entao {
      trasrotacao(300, 10)
      rotacionar(500, 90)
      alinhaReto()
      inverteTamanhoLado()
    } senao { frente(300) }
  }
  parar()

  frente(300) esperar(250)
  rotacionar(500, negativo(45))
  paradinha()
  despejaObjeto()

  inverteTamanhoLado()
  rotacionar(500, 45)
  alinhaReto()

  se (ladoMaior) entao {
    rotacionar(500, 45)
    enquanto (ultra(1) > 17) farei { frente(150) } parar()
    rotacionar(500, 45)
  } senao {
    mudouDirecao = verdadeiro
    trasrotacao(300, 10)
    rotacionar(500, 225)
    enquanto (ultra(1) > 17) farei { frente(150) } parar()
    rotacionar(500, negativo(45))
  }

}

tarefa procuraVitimaNaDireita {
  enquanto (verdadeiro) farei {
    se (temalgo(2, 15, 215)) entao {
      distanciaDaVitima = ultra(2)-23
      parartarefa()
    } senao se (ultra(1) < 12 ou (cor(2) != "BRANCO"
      ou (corazul(2) - corvermelha(2)) >= 9))
      entao {
        vitima = 3
        parar()
        terminouProcura = verdadeiro
        parartarefa()
    } senao { frente(150) }
  }
}

tarefa procuraVitimaNaEsquerda {
  enquanto (verdadeiro) farei {
    se (temalgo(3, 15, 215)) entao {
      distanciaDaVitima = ultra(3)-23
      parartarefa()
    } senao se (ultra(1) < 12 ou (cor(2) != "BRANCO"
      ou (corazul(2) - corvermelha(2)) >= 9))
      entao {
        vitima = 3
        parar()
        terminouProcura = verdadeiro
        parartarefa()
    } senao { frente(150) }
  }
}

tarefa verificaSeEstaViva {
  distanciaDaVitima = arredondar((distanciaDaVitima / 28) * 1000)
  zerartemporizador()
  enquanto (temporizador() <= distanciaDaVitima) farei {
    se (cor(5) == "PRETO" ou (9 <= corvermelha(5) e corvermelha(5) <= 13)) entao {
      vitimaViva = falso
      interromper()
    } senao { frente(150) }
  }
  parar()
}

tarefa pegaVitima {
  trasrotacao(300, 10)

  abaixaGarra()
  zerartemporizador()
  enquanto (temvitima() == falso e (temporizador() < 3000 ))
  farei { frente(150) }
  frente(150) esperar(400) parar()
  tempoDeRetorno = tempoDeRetorno + temporizador()
  levantaGarra()
}

tarefa entregaVitimaDaDireita {
  rotacionar(500, 90)
  enquanto (cor(5) != "PRETO") farei { frente(300) }
  frente(300) esperar(200)
  parar()

  rotacionar(500, 45)
  frente(300) esperar(200)
  parar()
  despejaObjeto()
  vitima = vitima + 1

  tras(300) esperar(80)
  rotacionar(500, 90)
  enquanto (ultra(1) > 17) farei { frente(150) } parar()
  rotacionar(500, 45)
}

tarefa entregaVitimaDaEsquerda {
  rotacionar(500, negativo(90))
  enquanto (cor(5) != "PRETO") farei { frente(300) }
  frente(300) esperar(200)
  parar()

  rotacionar(500, negativo(45))
  frente(300) esperar(200)
  parar()
  despejaObjeto()
  vitima = vitima + 1

  tras(300) esperar(80)
  rotacionar(500, negativo(90))
  enquanto (ultra(1) > 17) farei { frente(150) } parar()
  rotacionar(500, negativo(45))
}

tarefa retornaAposPegarVitima {
  tras(300) esperar(arredondar(tempoDeRetorno / 2) - 250) parar()
  frenterotacao(300, 15)
  alinhaReto()

  tempoDeRetorno = 0
  distanciaDaVitima = 0
}

tarefa verificaVitima {
  se (vitima < 2) entao {
    verificaSeEstaViva()
    tempoDeRetorno = distanciaDaVitima
    se (vitimaViva) entao { pegaVitima() }
    senao {
      tras(300)
      esperar(arredondar(tempoDeRetorno / 2) - 250)
      parar()
      parartarefa()
    }
  } senao {
    distanciaDaVitima = arredondar((distanciaDaVitima / 28) * 1000)
    zerartemporizador()
    enquanto (temporizador() < distanciaDaVitima) farei { frente(150) }
    parar()
    tempoDeRetorno = temporizador()
    pegaVitima()
  }

  retornaAposPegarVitima()
}

tarefa resgateVitimaNaEsquerda {
  enquanto (vitima < 3) farei {
    procuraVitimaNaEsquerda()
    se (terminouProcura) entao { parartarefa() }
    frenterotacao(300, 5)
    rotacionar(500, negativo(90))

    alinhaReto()
    verificaVitima()
    paradinha()

    se (temvitima()) entao { entregaVitimaDaEsquerda() }
    senao { rotacionar(500, 90) frenterotacao(300, 6) }

    alinhaReto()
    vitimaViva = verdadeiro
  }
  enquanto (verdadeiro) farei {
    se (ultra(1) < 12 ou (cor(2) != "BRANCO"
    ou (corazul(2) - corvermelha(2)) >= 9))
    entao { interromper() }
    senao { frente(150) }
  }
  parar()
}

tarefa resgateVitimaNaDireita {
  enquanto (vitima < 3) farei {
    procuraVitimaNaDireita()
    se (terminouProcura) entao { interromper() }
    frenterotacao(300, 5)
    rotacionar(500, 90)

    alinhaReto()
    verificaVitima()
    paradinha()

    se (temvitima()) entao { entregaVitimaDaDireita() }
    senao { rotacionar(500, negativo(90)) frenterotacao(300, 6) }

    alinhaReto()
    vitimaViva = verdadeiro
  }
  enquanto (verdadeiro) farei {
    se (ultra(1) < 12 ou (cor(2) != "BRANCO"
    ou (corazul(2) - corvermelha(2)) >= 9))
    entao { interromper() }
    senao { frente(150) }
  }
  parar()
}

tarefa procuraSaidaNaDireita {
  enquanto (verdadeiro) farei {
    se (ultra(1) < 12) entao {
      parar()
      rotacionar(500, negativo(90))
      alinhaReto()
    } senao se (100 < ultra(3)) entao {
      parar()
      frenterotacao(300, 3)
      rotacionar(500, 90)
      enquanto (verdadeiro) farei {
        se (cor(2) != "BRANCO"
        ou (8 <= corazul(2) - corvermelha(2)
        e corazul(2) - corvermelha(2) <= 16))
        entao { interromper() }
        senao { frente(75) }
      }
      parar()
      se (cor(2) == "VERDE" ou cor(2) == "PRETO"
      ou (30 < corverde(2) e corverde(2) < 38 e 12 < corvermelha(2) e corvermelha(2) < 17)
      ou (58 < corverde(2) e corverde(2) < 68 e 21 < corvermelha(2) e corvermelha(2) < 27)) entao {
        trasrotacao(300, 5)
        rotacionar(500, negativo(90))
        frenterotacao(300, 16)
        rotacionar(500, 90)
        alinhaReto()
        enquanto (cor(2) == "BRANCO") farei { frente(100) }
        frenterotacao(300, 10)
        parartarefa()
      } senao {
        trasrotacao(300, 5)
        rotacionar(500, negativo(90))
        alinhaReto()
        frente(300) esperar(1500)
      }
    } senao se (cor(2) != "BRANCO" ou (corazul(2) - corvermelha(2)) >= 9) entao {
      se (cor(2) == "PRETO" ou cor(2) == "VERDE") entao {
        rotacionar(500, negativo(90))
        frenterotacao(300, 8)
        rotacionar(500, 90)
        frenterotacao(300, 15)
        parartarefa()
      } senao {
        rotacionar(500, negativo(90))
        frente(300) esperar(1500)
      }
    } senao { frente(150) }
  }
}

tarefa procuraSaidaNaEsquerda {
  enquanto (verdadeiro) farei {
    se (ultra(1) < 12) entao {
      parar()
      rotacionar(500, 90)
      alinhaReto()
    } senao se (100 < ultra(3)) entao {
      parar()
      frenterotacao(300, 3)
      rotacionar(500, negativo(90))
      enquanto (verdadeiro) farei {
        se (cor(2) != "BRANCO"
        ou (6 <= corazul(2) - corverde(2)
        e corazul(2) - corverde(2) <= 11))
        entao { interromper() }
        senao { frente(75) }
      }
      parar()
      se (cor(2) == "PRETO" ou cor(2) == "VERDE"
      ou (30 < corverde(2) e corverde(2) < 38)
      ou (58 < corverde(2) e corverde(2) < 63)) entao {
        trasrotacao(300, 5)
        rotacionar(500, 90)
        frenterotacao(300, 16)
        rotacionar(500, negativo(90))
        alinhaReto()
        enquanto (cor(2) == "BRANCO") farei { frente(100) }
        frenterotacao(300, 10)
        parartarefa()
      } senao {
        trasrotacao(300, 5)
        rotacionar(500, 90)
        alinhaReto()
        frente(300) esperar(1500)
      }
    } senao se (cor(2) != "BRANCO" ou (corazul(2) - corvermelha(2)) >= 9) entao {
      se (cor(2) == "PRETO" ou cor(2) == "VERDE") entao {
        rotacionar(500, 90)
        frenterotacao(300, 8)
        rotacionar(500, negativo(90))
        frenterotacao(300, 15)
        parartarefa()
      } senao {
        rotacionar(500, 90)
        frente(300) esperar(1500)
      }
    } senao { frente(150) }
  }
}

tarefa salaDeResgate {
  escrever(1, "entrou na sala")
  frenterotacao(300, 25)
  alinhaReto()

  se (ultra(1) > 400 ou (ultra(3) > 100 e ultra(2) > 100)) entao {
    frenterotacao(300, 10)
    se (ultra(3) < 100) entao {
      vitimaNaEsquerda = verdadeiro
      rotacionar(500, 90)
    } senao se (ultra(2) < 100) entao {
      vitimaNaDireita = verdadeiro
      rotacionar(500, negativo(90))
    } senao {
      se (ultra(3) < ultra(2) e ultra(3) < 400) entao {
        vitimaNaDireita = verdadeiro
        rotacionar(500, negativo(90))
      } senao se (ultra(2) < ultra(3) e ultra(2) < 400) entao {
        vitimaNaEsquerda = verdadeiro
        rotacionar(500, 90)
      }
    }    
    parar()
    alinhaReto()
  }

  verificaTamanhoLado()

  se (ultra(3) < 100 ou vitimaNaDireita) entao {
    vitimaNaDireita = verdadeiro
    vitimaNaEsquerda = falso
    procuraAreaComParedeNaEsquerda()
  } senao se (ultra(2) < 100 ou vitimaNaEsquerda) entao {
    vitimaNaDireita = falso
    vitimaNaEsquerda = verdadeiro
    procuraAreaComParedeNaDireita()
  }

  alinhaReto()
  vitima = 0

  se (mudouDirecao e vitimaNaDireita) entao {
    vitimaNaDireita = falso
    vitimaNaEsquerda = verdadeiro
  } senao se (mudouDirecao e vitimaNaEsquerda) entao {
    vitimaNaDireita = verdadeiro
    vitimaNaEsquerda = falso
  }

  se (vitimaNaEsquerda) entao { resgateVitimaNaEsquerda() }
  senao se (vitimaNaDireita) entao { resgateVitimaNaDireita() }

  se (cor(2) == "VERDE" ou cor(2) == "PRETO"
  ou (30 < corverde(2) e corverde(2) < 38 e 12 < corvermelha(2) e corvermelha(2) < 17)
  ou (58 < corverde(2) e corverde(2) < 68 e 21 < corvermelha(2) e corvermelha(2) < 27)) entao {
    trasrotacao(300, 15)
    se (vitimaNaDireita) entao { rotacionar(500, 90) }
    senao se (vitimaNaEsquerda) entao { rotacionar(500, negativo(90)) }

    enquanto (toque(1) == falso) farei { tras(300) } parar()
    frenterotacao(300, 15)

    se (vitimaNaDireita) entao { rotacionar(500, negativo(90)) }
    senao se (vitimaNaEsquerda) entao { rotacionar(500, 90) }
    frenterotacao(300, 25)
    parartarefa()
  }

  se (ultra(1) > 15) entao { trasrotacao(300, 2) }

  se (400 < ultra(3)) entao {
    trasrotacao(300, 5)
    rotacionar(500, negativo(90))
    alinhaReto()

    zerartemporizador()
    enquanto (cor(2) == "BRANCO" ou (corazul(2) - corvermelha(2)) >= 9) farei { frente(150) } parar()
    tempoDeRetorno = temporizador()

    se (cor(2) == "VERDE" ou cor(2) == "PRETO"
    ou (30 < corverde(2) e corverde(2) < 38 e 12 < corvermelha(2) e corvermelha(2) < 17)
    ou (58 < corverde(2) e corverde(2) < 68 e 21 < corvermelha(2) e corvermelha(2) < 27)) entao {
      frenterotacao(300, 7)
      alinhaReto()
      parartarefa()
    } senao {
      tras(300) esperar(tempoDeRetorno / 2)
      rotacionar(500, 90)
      enquanto (verdadeiro) farei {
        se (ultra(1) < 12
        ou (cor(2) != "BRANCO" ou (corazul(2) - corvermelha(2)) >= 9))
        entao { interromper() }
        senao { frente(150) }
      }
      parar()
      se (vitimaNaEsquerda) entao { rotacionar(500, negativo(90))}
      senao { rotacionar(500, 90) }
    }
  } senao se (400 < ultra(2)) entao {
    trasrotacao(300, 5)
    rotacionar(500, 90)
    alinhaReto()

    zerartemporizador()
    enquanto (cor(2) == "BRANCO" ou (corazul(2) - corvermelha(2)) >= 9) farei { frente(150) } parar()
    tempoDeRetorno = temporizador()

    se (cor(2) == "VERDE" ou cor(2) == "PRETO"
    ou (30 < corverde(2) e corverde(2) < 38 e 12 < corvermelha(2) e corvermelha(2) < 17)
    ou (58 < corverde(2) e corverde(2) < 68 e 21 < corvermelha(2) e corvermelha(2) < 27)) entao {
      frenterotacao(300, 7)
      alinhaReto()
      parartarefa()
    } senao {
      tras(300) esperar(tempoDeRetorno / 2)
      rotacionar(500, negativo(90))
      enquanto (verdadeiro) farei {
        se (ultra(1) < 12
        ou (cor(2) != "BRANCO" ou (corazul(2) - corvermelha(2)) >= 9))
        entao { interromper() }
        senao { frente(150) }
      }
      parar()
      se (vitimaNaEsquerda) entao { rotacionar(500, negativo(90))}
      senao { rotacionar(500, 90) }
    }
  }

  alinhaReto()

  se (vitimaNaEsquerda) entao { procuraSaidaNaDireita() }
  senao se (vitimaNaDireita) entao { procuraSaidaNaEsquerda() }
}

inicio
  ajustarcor(45)
  #se ((horario < 8) ou (16 < horario)) entao { ajustarcor(45) }
  #senao se (((8 <= horario) e (horario < 11))
  #  ou ((13 < horario) e (horario <= 16))) entao  { ajustarcor(45) }
  #senao { ajustarcor(45) }

  velocidadeatuador(150)
  levantar(1000)
  fechar(50)

  enquanto (verdadeiro) farei {
    se (resgateFinalizado) entao {
      diferencaDeCorSensor2 = arredondar(corvermelha(2) - corverde(2))
    } senao {
      diferencaDeCorSensor2 = arredondar(corazul(2) - corvermelha(2))
      diferencaDeCorSensor3 = arredondar(corazul(3) - corvermelha(3))
    }

    se (resgateFinalizado == falso e (cor(2) == cor(3) e (cor(2) == "CIANO" ou cor(2) == "AZUL"))
    ou (diferencaDeCorSensor2 == diferencaDeCorSensor3
    e 8 <= diferencaDeCorSensor2 e diferencaDeCorSensor2 <= 16 ))
    entao { 
      salaDeResgate()
      escrever(1, "Resgate Finalizado")
      resgateFinalizado = verdadeiro
    } senao {
      se (ultra(1) <= 10 e cor(5) != "BRANCO") entao {
        desvioDeObstaculo()
      } senao se ( cor(5) == "CIANO" ou cor(5) == "AZUL"
        ou ((19 < corvermelha(5) e corvermelha(5) < 21) 
        e (39 < corverde(5) e corverde(5) < 41) 
        e (56 < corazul(5) e corazul(5) < 58))) 
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
          se ((resgateFinalizado ou tempo() > 300000)
          e (cor(2) == "VERMELHO" ou diferencaDeCorSensor2 > 48))
          entao {
            frenterotacao(300, 5)
            parei()
          } senao { segueLinha() }
        }
      }
    }
  }
  
fim