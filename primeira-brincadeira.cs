void Main () {
  while (true) {
    bc.ClearConsole();
    float erro = bc.Lightness(3) - 10;
    float correcao = erro * 1;
    bc.MoveFrontalAngles(100, correcao);
  }
}