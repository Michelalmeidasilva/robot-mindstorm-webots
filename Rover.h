void imprimeSensores();
void desviar();
void parar();
void one_second();
void desviar_2();
int verificaSensores();
_Bool acha_caminhos();
_Bool testa_esquerda();
_Bool testa_direita();

#define VALOR_SENSOR 43
#define sensor_i  43

enum estados_robo{
  condicoes = 0,
  linha = 1,
  reajuste = 2,
  obstaculo = 3,
  sensores = 4
};

// struct {
//   int estado;
//   int avoidance_counter;
//   int contaSegundos;
// } typedef controle_robo;

// struct {
//   double leftSpeed;
//   double rightSpeed;
// } typedef motores;





