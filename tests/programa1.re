numero erro = 0
numero p = 0
numero i = 0
numero integral = 0
numero d = 0
numero lastErro = 0
numero correcaoE = 0
numero correcaoD = 0
numero velocidade = 45

tarefa segueLinha {
  erro =  luz(2) - luz(3)
  p = erro * 15
  integral = integral + erro
  i = integral * 0.0001
  d = (erro - lastErro) * 30
  lastErro = erro

  correcaoE = (velocidade + (p + i + d))
  correcaoD = (velocidade - (p + i + d))

  escrever(1, virartexto(correcaoE))
  escrever(2, virartexto(correcaoD))

  mover(correcaoE, correcaoD)
}


inicio
  enquanto (verdadeiro) farei {
	  segueLinha()
  }

fim