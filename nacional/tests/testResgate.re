# USANDO O ROBÔ 3

# VARIAVEIS
numero horario = 12

booleano vitimaNaEsquerda = falso
booleano vitimaNaDireita = falso

numero alinhamento = 0
numero tempoDeRetorno = 0

booleano tempoEsgotou = falso

numero contagemGenerica = 0

booleano ladoMaior = falso
booleano ladoMenor = falso
booleano mudouDirecao = falso

numero canto = 0
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
  escreverbooleano(1, ladoMaior)
  escreverbooleano(2, ladoMenor)
}

tarefa inverteTamanhoLado {
  se (ladoMaior) entao {
    ladoMaior = falso
    ladoMenor = verdadeiro
  } senao se (ladoMenor) entao {
    ladoMaior = verdadeiro
    ladoMenor = falso
  }
  escreverbooleano(1, ladoMaior)
  escreverbooleano(2, ladoMenor)
}

tarefa procuraAreaComParedeNaDireita {
  canto = 1
  enquanto (verdadeiro) farei {
    se (corvermelha(5) < 3 e cor(5) == "PRETO") entao { interromper() }
    senao se (ultra(1) < 12) entao {
      trasrotacao(300, 10)
      rotacionar(500, negativo(90))
      alinhaReto()
      inverteTamanhoLado()
      canto = canto + 1
    } senao { frente(300) }
  }
  parar()

  rotacionar(500, 45)
  paradinha()
  despejaObjeto()

  inverteTamanhoLado()

  se (ladoMaior) entao {
    rotacionar(500, negativo(90))
    enquanto (ultra(1) > 17) farei { frente(150) } parar()
    rotacionar(500, negativo(45))
  } senao {
    mudouDirecao = verdadeiro
    rotacionar(500, negativo(45))
    trasrotacao(300, 10)
    rotacionar(500, negativo(225))
    enquanto (ultra(1) > 17) farei { frente(150) } parar()
    rotacionar(500, 45)
  }

}

tarefa procuraAreaComParedeNaEsquerda {
  canto = 1
  enquanto (verdadeiro) farei {
    se (corvermelha(5) < 3 e cor(5) == "PRETO") entao { interromper() }
    senao se (ultra(1) < 12 ou (30 < corverde(2) e corverde(2) < 38)) entao {
      trasrotacao(300, 10)
      rotacionar(500, 90)
      alinhaReto()
      inverteTamanhoLado()
      canto = canto + 1
    } senao { frente(300) }
  }
  parar()

  frente(300) esperar(250)
  rotacionar(500, negativo(45))
  paradinha()
  despejaObjeto()

  inverteTamanhoLado()

  se (ladoMaior) entao {
    rotacionar(500, 90)
    enquanto (ultra(1) > 17) farei { frente(150) } parar()
    rotacionar(500, 45)
  } senao {
    mudouDirecao = verdadeiro
    rotacionar(500, 45)
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
    } senao se (ultra(1) < 12 ou (30 < corverde(2) e corverde(2) < 38)
      ou ((42 < corvermelha(3) e corvermelha(3) < 46) e (52 < corazul(3) e corazul(3) < 56)))
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
    } senao se (ultra(1) < 12 ou (30 < corverde(2) e corverde(2) < 38)
      ou ((42 < corvermelha(3) e corvermelha(3) < 46) e (52 < corazul(3) e corazul(3) < 56)))
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
    se ((9 < corvermelha(5) e corvermelha(5) < 13) ou cor(5) == "PRETO") entao {
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
  frenterotacao(150, 5)
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
  rotacionar(500, negativo(225))
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
  rotacionar(500, 225)
}

tarefa retornaAposPegarVitima {
  tras(300) esperar(arredondar(tempoDeRetorno / 2)) parar()
  frenterotacao(300, 15)
  alinhaReto()
}

tarefa verificaVitima {
  se (vitima < 2) entao {
    verificaSeEstaViva()
    tempoDeRetorno = temporizador()
    se (vitimaViva) entao { pegaVitima() }
    senao {
      tras(300)
      esperar(arredondar(tempoDeRetorno / 2))
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
    se ((ultra(1) < 12) ou (30 < corverde(2) e corverde(2) < 38)
    ou (42 < corvermelha(3) e corvermelha(3) < 46) e (52 < corazul(3) e corazul(3) < 56))
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
    se ((ultra(1) < 12) ou (30 < corverde(2) e corverde(2) < 38)
    ou (42 < corvermelha(3) e corvermelha(3) < 46) e (52 < corazul(3) e corazul(3) < 56))
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
        se (cor(2) != "BRANCO" ou (corvermelha(2) < 55 e corverde(2) < 59 e corazul(2) < 67))
        entao { interromper() }
        senao { frente(75) }
      }
      parar()
      se (30 < corverde(2) e corverde(2) < 38) entao {
        trasrotacao(300, 5)
        rotacionar(500, negativo(90))
        frenterotacao(300, 12)
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
        se (cor(2) != "BRANCO" ou (corvermelha(2) < 55 e corverde(2) < 59 e corazul(2) < 67))
        entao { interromper() }
        senao { frente(75) }
      }
      parar()
      se (30 < corverde(2) e corverde(2) < 38) entao {
        trasrotacao(300, 5)
        rotacionar(500, 90)
        frenterotacao(300, 15)
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
    } senao { frente(150) }
  }
}

tarefa salaDeResgate {
  frenterotacao(300, 25)
  alinhaReto()

  se (ultra(1) > 400) entao { 
    mudouDirecao = verdadeiro
    frenterotacao(300, 10)
    se (ultra(3) < 100 ou ultra(3) < ultra(2) e ultra(3) < 400) entao {
      rotacionar(500, 90)
    } senao se (ultra(2) < 100 ou ultra(2) < ultra(3) e ultra(2) < 400) entao {
      rotacionar(500, negativo(90))
    }
    enquanto (toque(1) == falso) farei { tras(300) }
    parar()
    alinhaReto()
  }

  verificaTamanhoLado()
  se ( mudouDirecao ) entao { frenterotacao(300, 40) }
  mudouDirecao = falso

  se (ultra(3) < 100) entao {
    vitimaNaDireita = verdadeiro
    procuraAreaComParedeNaEsquerda()
  } senao se (ultra(2) < 100) entao { 
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

  se (30 < corverde(2) e corverde(2) < 38) entao {
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

  se (400 < ultra(3)) entao {
    trasrotacao(300, 5)
    rotacionar(500, negativo(90))
    alinhaReto()
    zerartemporizador()
    enquanto (cor(2) == "BRANCO") farei { frente(150) } parar()
    tempoDeRetorno = temporizador()
    se (30 < corverde(2) e corverde(2) < 38) entao {
      frenterotacao(300, 10)
      alinhaReto()
      parartarefa()
    } senao {
      tras(300) esperar(tempoDeRetorno / 2)
      rotacionar(500, 90)
      enquanto (verdadeiro) farei {
        se (ultra(1) < 12 ou (30 < corverde(2) e corverde(2) < 38)
          ou ((42 < corvermelha(3) e corvermelha(3) < 46) e (52 < corazul(3) e corazul(3) < 56)))
          entao { interromper() }
        senao { frente(150) }
      }
      parar()
      rotacionar(500, 90)
    }
  } senao se (400 < ultra(2)) entao {
    trasrotacao(300, 5)
    rotacionar(500, 90)
    alinhaReto()
    zerartemporizador()
    enquanto (cor(2) == "BRANCO") farei { frente(150) } parar()
    tempoDeRetorno = temporizador()
    se (30 < corverde(2) e corverde(2) < 38) entao {
      frenterotacao(300, 10)
      alinhaReto()
      parartarefa()
    } senao {
      tras(300) esperar(tempoDeRetorno / 2)
      rotacionar(500, negativo(90))
      enquanto (verdadeiro) farei {
        se (ultra(1) < 12 ou (30 < corverde(2) e corverde(2) < 38)
          ou ((42 < corvermelha(3) e corvermelha(3) < 46) e (52 < corazul(3) e corazul(3) < 56)))
          entao { interromper() }
        senao { frente(150) }
      }
      parar()
      rotacionar(500, negativo(90))
    }
  }

  alinhaReto()

  se (vitimaNaEsquerda) entao { procuraSaidaNaDireita() }
  senao se (vitimaNaDireita) entao { procuraSaidaNaEsquerda() }

}


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
      parei()
    } senao { segueLinha() }
  }
  
fim