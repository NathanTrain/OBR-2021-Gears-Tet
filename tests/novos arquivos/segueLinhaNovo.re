numero P = 0
numero D = 0
numero erro = 0
numero correcao = 0
numero lastErro = 0

numero alinhamento = 0

tarefa segueLinha {
  erro = (luz(3)) - (luz(2))
  escrevernumero(1, erro)
  P = erro * 20
  D = (erro - lastErro) * 40

  correcao = P + D

  mover((250 - correcao), (250 + correcao))
}

tarefa segueLinha2 {
  se (corvermelha(2) < 20 e corvermelha(3) > 20) entao {
    direita(750)
    esperar(50)

  } senao se (corvermelha(2) > 20 e corvermelha(3) < 20) entao {
    esquerda(750)
    esperar(50)

  } senao {
    frente(150)
  }
}

tarefa alinhaRetoSempre {
  se ((0 < direcao()) e (direcao() < 45)) entao {
    alinhamento = negativo(direcao())
  } senao se ((315 < direcao()) e (direcao() < 359)) entao {
    alinhamento = 360 - direcao()
  } senao se ((45 < direcao()) e (direcao() <= 90)) entao {
    alinhamento = 90 - direcao()
  } senao se ((90 <= direcao()) e (direcao() < 135)) entao {
    alinhamento = negativo((direcao() - 90))
  } senao se ((135 < direcao()) e (direcao() <= 180)) entao {
    alinhamento = 180 - direcao()
  } senao se ((180 <= direcao()) e (direcao() < 225)) entao {
    alinhamento = negativo((direcao() - 180))
  } senao se ((225 < direcao()) e (direcao() <= 270)) entao {
    alinhamento = 270 - direcao()
  } senao se ((270 <= direcao()) e (direcao() < 315)) entao {
    alinhamento = negativo((direcao() - 270))
  }
  rotacionar(500, arredondar(alinhamento))
}

tarefa alinhandoRetoParaPreto {
  se ((0 < direcao()) e (direcao() < 20)) entao {
    alinhamento = negativo(direcao())
  } senao se ((340 < direcao()) e (direcao() < 359)) entao {
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
  rotacionar(500, arredondar(alinhamento))
}

tarefa alinhandoEsquerda {
  enquanto (cor(2) != "PRETO") farei {
    esquerda(750)
  }
  enquanto (cor(3) != "PRETO") farei {
    direita(750)
  }
}
tarefa alinhandoDireita {
  enquanto (cor(3) != "PRETO") farei {
    direita(750)
  }
  enquanto (cor(2) != "PRETO") farei {
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

inicio

  velocidadeatuador(1000)
  levantar(500)
  girarbaixo(500)

  enquanto (verdadeiro) farei {

    se (corvermelha(1) < 20 e corvermelha(4) < 20) entao {
      parei()
    } senao {
      segueLinha2()
    }

  }

fim