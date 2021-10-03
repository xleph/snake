# Snake
A rather rudimentary game with a rather rudimentary twist

# Setting Up Camp:
  ## By Hand:
  compile ssw
  
  `gcc -c ssw.c -o ssw.o`

  compile bezier.c
  
  `gcc -c bezier.c -o bezier.o`

  and last but not least:
  
  `gcc ssw.o bezier.o snake.c -o snake -lX11`

  ## Install Script:
  `chmod +x deploy && ./deploy`
  
