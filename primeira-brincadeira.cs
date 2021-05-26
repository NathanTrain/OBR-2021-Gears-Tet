void Main () {
  // se move mas é ruim, não consegue fazer curva :(
    
  while (true) {
    if (bc.Lightness(2) <= 10) {
      bc.MoveFrontal(500, -200);
    } else {
      bc.MoveFrontal(-200, 500);      
    }
  }
}