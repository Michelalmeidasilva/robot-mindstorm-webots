  #include<stdio.h>
  #include"Rover.h"
  #include <webots/distance_sensor.h>
  #include <webots/motor.h>
  #include <webots/robot.h>
  #include <webots/touch_sensor.h>
  #include <stdio.h>
  #include <stdlib.h>
  #define TIME_STEP 32
  int posicao[1000];

  int estado = 0, avoidance_counter = 0, counter_teste = 0;
  int segundos = -1;
  bool resultado_caminhos=false;
  int condicao_caminhos = -1;
  int corrige_contador=0;
       
  double leftSpeed=0, rightSpeed=0;
  WbDeviceTag leftBumper ;
  WbDeviceTag groundSensor ;
  WbDeviceTag rightBumper ;

  int main() {
    wb_robot_init();
    leftBumper = wb_robot_get_device("S1");
    groundSensor = wb_robot_get_device("S2");
    rightBumper = wb_robot_get_device("S3");

    wb_touch_sensor_enable(leftBumper, TIME_STEP);
    wb_touch_sensor_enable(rightBumper, TIME_STEP);
    wb_distance_sensor_enable(groundSensor, TIME_STEP);
    
    WbDeviceTag left_motor = wb_robot_get_device("left wheel motor");
    WbDeviceTag right_motor = wb_robot_get_device("right wheel motor");
  
    wb_motor_set_position(left_motor, INFINITY);
    wb_motor_set_position(right_motor, INFINITY);

    wb_motor_set_velocity(left_motor, 0.0);
    wb_motor_set_velocity(right_motor, 0.0);
    int i = 0;
    while (wb_robot_step(TIME_STEP) != -1) {
     
      //imprime os sensores a aproximadamente 15 * 64ms ( 1 segundo)
      one_second();
    
      switch(estado){
        
        case condicoes: 
          //Nao tem obstaculo
          if (avoidance_counter == 0){        
            /*
            if(segundos == 20){
              while(i != 1000){
                printf("%d\n", posicao[i]);
                i++;
              }
            }
            */
            estado = sensores;

          } 
          //Obstaculo
          else{
           printf("%d", i);
            
            estado = sensores;

          }
          break;

        //retorna na linha( ainda nao implementado ), reajuste ou obstaculo
        case sensores:
          estado = verificaSensores();
          break;

        case reajuste:   
            if(wb_distance_sensor_get_value(groundSensor) > VALOR_SENSOR){
              rightSpeed = 0.5;
              leftSpeed =4.0;
              if (wb_distance_sensor_get_value(groundSensor) > 20.62 && wb_distance_sensor_get_value(groundSensor) < 61){
                leftSpeed = 10.0;
                rightSpeed = 10.0;
              } 
            } else {
              leftSpeed =0.5;
              rightSpeed = 4.0;
              if (wb_distance_sensor_get_value(groundSensor) > 20.62 && wb_distance_sensor_get_value(groundSensor) < 61){
                leftSpeed = 10.0;
                rightSpeed = 10.0;
              }
            }

          estado = condicoes;
          break;

        case obstaculo:
          desviar();
          break;
      }

      wb_motor_set_velocity(left_motor, leftSpeed);
      wb_motor_set_velocity(right_motor, rightSpeed);
  }
  wb_robot_cleanup();
  return 0;
}

int verificaSensores(){
  printf("G=%lf\n", wb_distance_sensor_get_value(groundSensor) );  
  if (wb_touch_sensor_get_value(leftBumper) > 0 || wb_touch_sensor_get_value(rightBumper) > 0) {
    leftSpeed = -0.6;
    rightSpeed = -1;
    avoidance_counter = 450;
    return obstaculo;
  }   else if (wb_distance_sensor_get_value(groundSensor) > VALOR_SENSOR){
      return reajuste;
  } else {
      return reajuste;
  }
  
  return condicoes;
}

void desviar(){
  if(avoidance_counter > 429){
    printf("Dando Ré\n");
    leftSpeed = -10.0;
    rightSpeed = -10.0;
  }else if(avoidance_counter > 353){
     leftSpeed = 8.0;
     rightSpeed = 0.0; 
     printf("Virando à esquerda\n");
     
  } else if (avoidance_counter > 60){
    leftSpeed = 0.7;
    rightSpeed = 3.0;
    if (wb_distance_sensor_get_value(groundSensor) > VALOR_SENSOR){
       estado = condicoes;
       avoidance_counter = 0;
       return;
     }
  } 

  if(avoidance_counter > 0)
    avoidance_counter--;
  else 
    estado = condicoes;
}

void desviar_2(){
  printf("avoidance counter = %d\n", avoidance_counter);
  if(avoidance_counter > 429){
      printf("Dando Ré\n");
      leftSpeed = -10.0;
      rightSpeed = -10.0;
    } else if (avoidance_counter > 402){
      leftSpeed = 10.0;
      rightSpeed = 1.8; 
      printf("Virando à esquerda\n");
      
    } else if (avoidance_counter > 375){
      leftSpeed = 10.0;
      rightSpeed = 10.0;
      printf("Indo reto\n");
    
      if(wb_distance_sensor_get_value(groundSensor) > 33){
        estado = condicoes;
      }
    } else if(avoidance_counter > 350){
      leftSpeed = 1.5;
      rightSpeed = 10.0;
      printf("virando À direita\n");
    } else if (avoidance_counter > 285){
      leftSpeed = 10.0;
      rightSpeed = 10.0;
      printf("Indo reto\n");
    } else if (avoidance_counter > 260){
      leftSpeed = 1.8;
      rightSpeed = 10.0;
      printf("Indo virando a esquerda\n");
    } else if (avoidance_counter > 225){
      rightSpeed = 10.0;
      leftSpeed = 10.0;
      printf("Indo reto");
    } else if (avoidance_counter > 175){
      rightSpeed = 2.0;
      leftSpeed = 10.0;
    } else if (avoidance_counter > 145){
      leftSpeed = 4.0;
      rightSpeed = 10.0;
        avoidance_counter = 0;
      if(wb_distance_sensor_get_value(groundSensor) > 33){
        estado = condicoes;
      }
    }
  
    if(avoidance_counter > 0)
      avoidance_counter--;
    else 
      estado = condicoes;
}

void one_second(){
      if(counter_teste == 31){
      counter_teste = 0;
      }
   if( counter_teste % 31 == 0 ) {
         corrige_contador++;
        if(corrige_contador == 125){
        corrige_contador=0;
        segundos--;
        }
        segundos++;
        printf("segundos = %d\n", segundos);
      }          
    counter_teste++ ;
}


void parar(){
  leftSpeed  =0;
  rightSpeed =0;
}
