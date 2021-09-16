# USANDO O ROBÔ 3

# VARIAVEIS
numero horario = 12
booleano emResgate = falso

# TAREFAS DE CONTROLE DO ROBÔ
tarefa segueLinha {
  se (cor(2) == "PRETO" e cor(3) == "PRETO") entao { frente(175) esperar(30) }

  se (cor(2) == "BRANCO" e cor(3) == "BRANCO") entao { frente(175) esperar(30) }

  se (cor(2) == "PRETO") entao { direita(1000) }

  se (cor(3) == "PRETO") entao { esquerda(1000) }
}

tarefa paradinha { parar() esperar(500) }
tarefa parei { enquanto (verdadeiro) farei { parar() } }


# TAREFAS DO RESGATE

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
  fechar(50)

  enquanto (verdadeiro) farei {
    se (emResgate) entao { resgate() }
    senao {
      se (ultra(1) < 25 e cor(6) != "BRANCO") entao {
        # desvioDeObstaculo()
      } senao se ((18 < corvermelha(6) e corvermelha(6) < 22) 
        e (38 < corverde(6) e corverde(6) < 42) 
        e (55 < corazul(6) e corazul(6) < 59)) 
        entao {
          pegaKitDeResgate()
      } senao { 
        se (cor(2) == "VERDE" ou cor(3) == "VERDE" ou cor(4) == "VERDE") entao {
          # curvaEmVerde()
        } senao se (cor(1) == "PRETO" ou cor(5) == "PRETO") entao {
            # curvaEmPreto()
        } senao { segueLinha() }
      }
    }
  }
  
fim