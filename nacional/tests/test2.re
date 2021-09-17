# USANDO O ROBÔ 3

# VARIAVEIS
numero horario = 12

booleano viraEsquerda = falso
booleano viraDireita = falso
booleano travessa = falso
booleano tempoEsgotou = falso

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

# TAREFAS DE DESVIO DE OBSTÁCULO


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
  trasrotacao(300, 15)
  abaixaGarra()

  # AGUARDANDO ATUALIZAÇÃO PARA UTILIZAR ESTA FUNCIONALIDADE
  # zerartemporizador()
  # 
  # enquanto (temkit() == falso) {
  #   frente(300)
  # }
  # tempoDeRetorno = temporizador() - 250
  #
  # tras(300)
  # esperar(tempoDeRetorno)
  parar()
  esperar(10)

  frente(300)
  esperar(1000)
  parar()

  levantaGarra()

  tras(300)
  esperar(500)
  parar()
}

tarefa resgate {
  escrever(1, "cheguei na sala")
  parei()
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
    se ( (58 < luz(1) e luz(1) < 60) e (58 < luz(2) e luz(2) < 60)
      e (58 < luz(3) e luz(3) < 60) e (58 < luz(4) e luz(4) < 60))
      entao { 
        resgate()
        resgateFinalizado = verdadeiro
    } senao {
      se (ultra(1) < 25 e cor(5) != "BRANCO") entao {
        # desvioDeObstaculo()
      } senao se ((19 < corvermelha(5) e corvermelha(5) < 21) 
        e (39 < corverde(5) e corverde(5) < 41) 
        e (56 < corazul(5) e corazul(5) < 58)) 
        entao {
          pegaKitDeResgate()
      } senao { 
        se (cor(1) == "VERDE" ou cor(2) == "VERDE"
        ou cor(3) == "VERDE" ou cor(4) == "VERDE") entao {
          curvaEmVerde()
        } senao se (cor(1) == "PRETO" ou cor(4) == "PRETO") entao {
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