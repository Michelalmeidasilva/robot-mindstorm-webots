void imprimeSensores();
void desviar();
int verificaSensores();

enum estados_robo{
  linha = 1,
  obstaculo = 2,
  sensores = 4,
  condicoes = 5,
  foraLinha = 6
};