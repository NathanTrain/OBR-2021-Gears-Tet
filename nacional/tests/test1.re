# USANDO O ROBÔ 5

booleano viraEsquerda = falso
booleano viraDireita = falso
booleano travessa = falso
numero anguloDesejado = 0 

numero tempoDeRetorno = 0
booleano tempoEsgotou = falso

numero contagemGenerica = 0
numero alinhamento = 0

booleano semLinhaFrente = falso

booleano emResgate = falso

numero horario = 15.75


# TAREFAS DE CONTROLE DO ROBÔ
tarefa segueLinha {
  se (cor(3) == "PRETO") entao { frente(150) esperar(30) }

  se (cor(2) == "PRETO") entao { direita(750) esperar(30) }

  se (cor(4) == "PRETO") entao { esquerda(750) esperar(30) }

  se (cor(3) == "BRANCO") entao { frente(150) }
}

tarefa alinhaReto {
  para contagemGenerica de 1 ate 2 passo 1 farei {
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

tarefa paradinha { parar() esperar(500) }

tarefa parei { enquanto (verdadeiro) farei { parar() } }


# TAREFAS DE DESVIO DO OBSTÁCULO

tarefa desvioDeObstaculo { escrever(1, "desviando") }


# TAREFAS DE CURVA

tarefa reiniciaVariaveisDeCurva {
  travessa = falso
  viraDireita = falso
  viraEsquerda = falso
  semLinhaFrente = falso
  tempoEsgotou = falso
}

tarefa verificaLadoVerde {
  se (cor(1) != "VERDE" e cor(2) != "VERDE" e cor(3) != "VERDE" e cor(4) != "VERDE" e cor(5) != "VERDE") entao {
    zerartemporizador()
    enquanto (cor(1) != "PRETO" e cor(5) != "PRETO") farei {
      se (temporizador() > 4000) entao { tempoEsgotou = verdadeiro }
      senao { tras(50) }
    }
    parar()
  }

  se (tempoEsgotou) entao { parartarefa() }

  se ((cor(1) == "VERDE" ou cor(2) == "VERDE") e (cor(4) == "VERDE" ou cor(5) == "VERDE"))
      entao { travessa = verdadeiro }
  senao se (cor(2) == "VERDE" e cor(4) != "VERDE")
    entao { viraDireita = verdadeiro }
  senao se (cor(2) != "VERDE" e cor(4) == "VERDE")
    entao { viraEsquerda = verdadeiro }

  esperar(60)
}

tarefa verificaLadoPreto {
  se (cor(1) != "PRETO" e cor(5) != "PRETO") entao {
    zerartemporizador()
    enquanto (cor(1) != "PRETO" e cor(5) != "PRETO") farei {
      se (temporizador() > 4000) entao { tempoEsgotou = verdadeiro }
      senao { tras(50) }
    }
    parar()
  }

  se (tempoEsgotou) entao { parartarefa() }

  se (cor(1) == "PRETO" e cor(5) == "PRETO")
    entao { travessa = verdadeiro }
  senao se (cor(1) == "PRETO" e cor(5) != "PRETO")
    entao { viraDireita = verdadeiro }
  senao se (cor(1) != "PRETO" e cor(5) == "PRETO")
    entao { viraEsquerda = verdadeiro }
}

tarefa praDireitaAposVerde {
  frenterotacao(300, 8)
  rotacionar(1000, 30)
  enquanto (cor(3) != "PRETO") farei { direita(1000) }
}

tarefa praEsquerdaAposVerde {
  frenterotacao(300, 8)
  rotacionar(1000, negativo(30))
  enquanto (cor(3) != "PRETO") farei { esquerda(1000) }
}

tarefa becoSemSaida { 
  frenterotacao(300, 15)
  rotacionar(500, 180)
}

tarefa curvaEmVerde {
  paradinha()
  frenterotacao(150, 1)
  verificaLadoVerde()

  se (travessa) entao { becoSemSaida() }
  senao se (viraDireita) entao { praDireitaAposVerde() }
  senao se (viraEsquerda) entao { praEsquerdaAposVerde() }

  reiniciaVariaveisDeCurva()
}

tarefa virandoDireitaAteVerPreto {
  frenterotacao(300, 8)
  enquanto (cor(3) != "PRETO") farei { direita(1000) }
}

tarefa virandoEsquerdaAteVerPreto {
  frenterotacao(300, 8)
  enquanto (cor(3) != "PRETO") farei { esquerda(1000) }
}

tarefa verificaLinhaEmFrente {
  frenterotacao(275, 5)
  anguloDesejado = direcao() + 25
  zerartemporizador()

  enquanto (cor(3) != "PRETO" e cor(4) != "PRETO" e cor(5) != "PRETO" 
  e direcao() < anguloDesejado) 
    farei { direita(1000) }
  parar()

  tempoDeRetorno = temporizador()


  se (cor(3) != "PRETO" e cor(4) != "PRETO" e cor(5) != "PRETO")
    entao {semLinhaFrente = verdadeiro }

  esquerda(1000)
  esperar(tempoDeRetorno)
  parar()
}

tarefa curvaEmPreto {
  paradinha()

  verificaLinhaEmFrente()

  se (semLinhaFrente) entao { verificaLadoPreto() }

  se (travessa) entao { frenterotacao(275, 5) }
  senao se (viraDireita) entao { virandoDireitaAteVerPreto() }
  senao se (viraEsquerda) entao { virandoEsquerdaAteVerPreto() }

  reiniciaVariaveisDeCurva()
}


# TAREFAS DE RESGATE

tarefa abaixaGarra {
  baixar(1250)
  abrir(50)
}

tarefa levantaGarra {
  fechar(50)
  levantar(1250)
}

tarefa pegaKitDeResgate {
  trasrotacao(300, 15)
  abaixaGarra()

  # AGUARDANDO ATUALIZAÇÃO PARA UTILIZAR ESTA FUNCIONALIDADE
  # enquanto (temkit() == falso) {
  #   frente(300)
  # }
  frente(300)
  esperar(1000)
  parar()

  levantaGarra()

  tras(300)
  esperar(250)
  parar()
}

tarefa resgate {
  parei()
}


inicio
  se ((horario < 8) ou (16 < horario)) entao { ajustarcor(45) }
  senao se (((8 <= horario) e (horario < 11))
    ou ((13 < horario) e (horario <= 16))) entao  { ajustarcor(35) }
  senao { ajustarcor(30) }

  velocidadeatuador(150)
  levantar(1000)
  fechar(750)

  enquanto (verdadeiro) farei {

    se (emResgate) entao { resgate() }
    senao {
      se (ultra(1) < 25 e cor(6) != "BRANCO") entao {
        desvioDeObstaculo()
        parei()
      } senao se ((18 < corvermelha(6) e corvermelha(6) < 22) 
        e (38 < corverde(6) e corverde(6) < 42) 
        e (55 < corazul(6) e corazul(6) < 59)) 
        entao {
          pegaKitDeResgate()
      } senao { 
        se (cor(2) == "VERDE" ou cor(3) == "VERDE" ou cor(4) == "VERDE") entao {
          curvaEmVerde()
        } senao se (cor(1) == "PRETO" ou cor(5) == "PRETO") entao {
            curvaEmPreto()
        } senao { segueLinha() }
      }
    }
  }

fim