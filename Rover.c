  #include<stdio.h>
  #include"Rover.h"
  #include <webots/distance_sensor.h>
  #include <webots/motor.h>
  #include <webots/robot.h>
  #include <webots/touch_sensor.h>
  #include <stdio.h>
  #include <stdlib.h>
  #define TIME_STEP 64


  int estado = 0, avoidance_counter = 0;
  int counter_teste = 0;
  int segundos = -1;
  
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

    while (wb_robot_step(TIME_STEP) != -1) {
      
      //imprime os sensores a aproximadamente 15 * 64ms ( 1 segundo)
      one_second();

      switch(estado){
     
        case condicoes: 
          //Nao tem obstaculo
          if (avoidance_counter == 0) 
            estado = sensores;
          //Obstaculo
          else
            estado = sensores;
          break;

        case sensores:
          estado = verificaSensores();
          break;

        case linha:

          if(groundSensor > 30 && groundSensor < 63){
            rightSpeed = 2.0;
            leftSpeed = 2.0;
            estado = condicoes;
          }
          
          estado = condicoes;
          break;

        case foraLinha:
          if( groundSensor < 43){
            rightSpeed= 0.2;
            leftSpeed = 1.0;
            estado = condicoes;
          } else if(groundSensor < 23){ 
            rightSpeed = 0.2;
            leftSpeed = 1.0;
            estado = condicoes;
          }
          estado = condicoes;
          break;

        case obstaculo:
          desviar();
          break;
      }

      if(counter_teste  > 300)
        counter_teste = 0;

      wb_motor_set_velocity(left_motor, leftSpeed);
      wb_motor_set_velocity(right_motor, rightSpeed);
 

  }
  wb_robot_cleanup();
  return 0;
}

int verificaSensores(){
  if (wb_touch_sensor_get_value(leftBumper) > 0 || wb_touch_sensor_get_value(rightBumper) > 0) {
    leftSpeed = -0.6;
    rightSpeed = -1;
    avoidance_counter = 2000;
    return obstaculo;
  } else if (wb_distance_sensor_get_value(groundSensor) > 40) {
      return linha;
  } else if((wb_distance_sensor_get_value(groundSensor) < 40)){
      return foraLinha;
  }
  return condicoes;
}

void imprimeSensores(){
  printf("L=%lf\n", wb_touch_sensor_get_value(leftBumper) );
  printf("R=%lf\n", wb_touch_sensor_get_value(rightBumper) );
  printf("G=%lf\n", wb_distance_sensor_get_value(groundSensor) );
  printf("Avoidance Counter = %d\n", avoidance_counter);
}

void desviar(){

  if (avoidance_counter > 800) {
    leftSpeed = -0.6;
    rightSpeed = -1;
  } else if (avoidance_counter > 600) {
    leftSpeed = 1.5;
    rightSpeed = 1.5;
  } else if (avoidance_counter > 70) {
    leftSpeed = 0.7 ;
    rightSpeed = 1;
    if (wb_distance_sensor_get_value(groundSensor) > 43){
      avoidance_counter = 1;
      estado = condicoes;
    }
  } else {
    leftSpeed = 5;
    rightSpeed = 5;
    if (wb_distance_sensor_get_value(groundSensor) > 43)
    avoidance_counter = 1;
  }
  avoidance_counter--;
}


void one_second(){
   if( counter_teste % 15 == 1 ) {
        imprimeSensores();
        segundos++;
        printf("segundos = %d\n", segundos);
      }          
    counter_teste++ ;
}
