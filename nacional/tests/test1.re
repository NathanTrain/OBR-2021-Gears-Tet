booleano viraEsquerda = falso
booleano viraDireita = falso
booleano travessa = falso

numero tempoDeRetorno = 0

booleano semLinhaFrente = falso

booleano emResgate = falso

# melhor para ROBÔ 3
tarefa segueLinha { 
  se (cor(2) == "BRANCO" e cor(3) == "BRANCO") entao { frente(150) esperar(30) }

  se (cor(2) == "PRETO" e cor(3) == "PRETO") entao { frente(150) esperar(30) }

  se (cor(2) == "PRETO") entao { direita(750) }

  se (cor(3) == "PRETO") entao { esquerda(750) }
}

# melhor para ROBÔ 2 (velocidade = 275) e 5 (velocidade = 150)
tarefa segueLinhaV2 {
  se (cor(3) == "PRETO") entao { frente(275) esperar(30) }

  se (cor(2) == "PRETO") entao { direita(750) esperar(30) }

  se (cor(4) == "PRETO") entao { esquerda(750) esperar(30) }

  se (cor(3) == "BRANCO") entao { frente(275) }
}

tarefa parei {
  enquanto (verdadeiro) farei { parar() }
}


tarefa desvioDeObstaculo {

}

tarefa pegaKitDeResgate {
  trasrotacao(300, 15)
  baixar(1250)
  girarbaixo(250)
  abrir(500)

  frente(300)
  esperar(2000)
  parar()

  levantar(1250)
  fechar(500)
  girarcima(250)

  tras(300)
  esperar(1500)
  parar()
}


tarefa reiniciaVariaveisDeCurva {
  travessa = falso
  viraDireita = falso
  viraEsquerda = falso
  semLinhaFrente = falso
}

tarefa verificaCurvaVerde {
  se (cor(1) != "VERDE" e cor(2) != "VERDE" e cor(3) != "VERDE" e cor(4) != "VERDE" e cor(5) != "VERDE") entao {
    zerartemporizador()
    enquanto (cor(1) != "PRETO" e cor(5) != "PRETO" e temporizador() < 5000) farei {
      tras(50)
    }
    parar()
  }

  se (temporizador() < 5000) entao {
    parartarefa() 
  }

  se ((cor(1) == "VERDE" ou cor(2) == "VERDE")
    e (cor(4) == "VERDE" ou cor(5) == "VERDE"))
      entao { travessa = verdadeiro }
  senao se (cor(2) == "VERDE" e cor(4) != "VERDE")
    entao { viraDireita = verdadeiro }
  senao se (cor(2) != "VERDE" e cor(4) == "VERDE")
    entao { viraEsquerda = verdadeiro }

  esperar(60)
}

tarefa verificaCurvaPreto {
  se (cor(1) != "PRETO" e cor(5) != "PRETO") entao {
    zerartemporizador()
    enquanto (cor(1) != "PRETO" e cor(5) != "PRETO" e temporizador() < 5000) farei {
      tras(150)
    }
    parar()
  }

  se (temporizador() < 5000 e cor(1) != "PRETO" e cor(5) != "PRETO") entao {
    parartarefa()
  }

  se (cor(1) == "PRETO" e cor(5) == "PRETO")
    entao { travessa = verdadeiro }
  senao se (cor(1) == "PRETO" e cor(5) != "PRETO")
    entao { viraDireita = verdadeiro }
  senao se (cor(1) != "PRETO" e cor(5) == "PRETO")
    entao { viraEsquerda = verdadeiro }
}

tarefa praDireitaAposVerde {
  frenterotacao(300, 12)
  rotacionar(1000, 30)
  enquanto (cor(2) != "PRETO") farei { direita(1000) }
  trasrotacao(300, 7)
}

tarefa praEsquerdaAposVerde {
  frenterotacao(300, 12)
  rotacionar(1000, negativo(30))
  enquanto (cor(4) != "PRETO") farei { esquerda(1000) }
  trasrotacao(300, 7)
}

tarefa curvaEmVerde {
  parar()
  verificaCurvaVerde()

  se (travessa) entao { rotacionar(500, 180) }
  senao se (viraDireita) entao { praDireitaAposVerde() }
  senao se (viraEsquerda) entao { praEsquerdaAposVerde() }

  reiniciaVariaveisDeCurva()
}

tarefa virandoDireitaAteVerPreto {
  frenterotacao(300, 12)
  enquanto (cor(2) != "PRETO") farei { direita(1000) }
  trasrotacao(300, 7)
}

tarefa virandoEsquerdaAteVerPreto {
  frenterotacao(300, 12)
  enquanto (cor(4) != "PRETO") farei { esquerda(1000) }
  trasrotacao(300, 7)
}

tarefa verificaLinhaEmFrente {
  frenterotacao(275, 5)
  se (cor(3) != "PRETO") entao {
    rotacionar(1000, 7)

    se (cor(3) == "PRETO" ou cor(4) == "PRETO") entao {
      rotacionar(1000, negativo(5))
      parartarefa()
    } senao {
      semLinhaFrente = verdadeiro
      rotacionar(1000, negativo(5))
      trasrotacao(275, 2)
    }

  } senao { parartarefa() }
}

tarefa curvaEmPreto {
  parar()

  verificaLinhaEmFrente()

  se (semLinhaFrente) entao { verificaCurvaPreto() }

  se (travessa) entao { frenterotacao(275, 5) }
  senao se (viraDireita) entao { virandoDireitaAteVerPreto() }
  senao se (viraEsquerda) entao { virandoEsquerdaAteVerPreto() }

  reiniciaVariaveisDeCurva()
}



tarefa resgate {
  parei()
}


inicio

  velocidadeatuador(150)
  levantar(1000)
  fechar(750)

  enquanto (verdadeiro) farei {

    se (emResgate) entao { resgate() }
    senao {
      se (ultra(1) < 25 e cor(6) != "BRANCO") entao {

      } senao se (ultra(2) < 10 e cor(6) == "CIANO") entao {
        pegaKitDeResgate()
      } senao { 
        se (cor(2) == "VERDE" ou cor(3) == "VERDE" ou cor(4) == "VERDE") entao {
          curvaEmVerde()
        } senao se ((cor(1) == "PRETO" e cor(2) == "PRETO") ou (cor(4) == "PRETO" e cor(5) == "PRETO")) entao {
          curvaEmPreto()
        } senao { segueLinhaV2() }
      }
    }
  }

fim