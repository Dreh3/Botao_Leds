//Código desenvolvido por Andressa Sousa Fonseca

/*
O presente código funciona da seguinte maneira:
Ao pressionar o botão, todos os leds são ligados simultaneamente e permanecem ligados por 3 segundos 
Depois, eles desligam um or um a cada 3 segundos. 
E, somente, quando todos estiverem desligados, é possível acionar o botão novamente.
*/

#include "pico/stdlib.h"   
#include "hardware/timer.h" 
#include <stdio.h>

// Definindo os pinos para o LEDs 
#define LedR 13 //Led Vermelho no pino 13
#define LedB 12 //Led Azul no pino 12
#define LedG 11 //Led Verde no pino 11
#define ButtonA 5 //Botão A no pino 5

// Variáveis globais uteis no código
static volatile uint ordem =0; //Indica a ordem de desligamento dos leds  

//Função para inicializar e configurar pinos dos Leds
void config(){
  //Inicializando pinos
  gpio_init(LedR);
  gpio_init(LedB);
  gpio_init(LedG);
  gpio_init(ButtonA);


  //Definindo pinos dos leds como saída
  gpio_set_dir(LedR, GPIO_OUT);
  gpio_set_dir(LedB, GPIO_OUT);
  gpio_set_dir(LedG, GPIO_OUT);

  //Definindo pino do botão como entrada
  gpio_set_dir(ButtonA, GPIO_IN);

  //Todos os leds iniciam desligados
  gpio_put(LedG, 0);
  gpio_put(LedB, 0);
  gpio_put(LedR, 0);

  //Definindo botão como Pull-up
  gpio_pull_up(ButtonA);

};

//Função que verifica estado dos leds, e retorna 1 se todos estiverem desligados
int leds_desligados(){
  return(!gpio_get(LedR) && !gpio_get(LedG) && !gpio_get(LedB));
};

// Função de callback que será chamada pelo temporizador repetidamente a cada 3 segundo para alternar entre os leds
int64_t turn_off_callback(alarm_id_t id, void *user_data) {
      switch (ordem){
        case 0: //Quando ordem = 0, o led vermelho é desligado
            gpio_put(LedR, 0);

            //Atualiza valor de 'ordem' para indicar o próximo led
            ordem = 1;

            //Nova chamada da função call-back para poder desligar o segundo led depois de 3 segundos
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);
           
            break;
        case 1: //Quando ordem = 1, o led azul é desligado
            gpio_put(LedB, 0);

            //Atualiza valor de 'ordem' para indicar o próximo led
            ordem = 2;

            //Nova chamada da função call-back para poder desligar o segundo led depois de 3 segundos
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);
            
            break;
        case 2: //Quando ordem = 1, o led verde é desligado
            gpio_put(LedG, 0);

            //Atualiza valor de 'ordem' para reiniciar a contagem para o próximo acionamento do botão
            ordem = 0;

            break;
        default:
          break;

      };

    //Retorna 0 pois já há nova chamadas específicas acima
    return 0;
};

int main() {

    //Habilita comunicação padrão
    stdio_init_all();    

    //Função para configurar e inicializar leds e botão
    config();

    
    
    while (true) {
        if(gpio_get(ButtonA)==0){
          //Rotina de tratamento debouncing
          sleep_ms(50); //Espera 50 ms para verificar estado do botão novamente 
            
            //If para verificar se o botão foi mesmo pressionado e se todos os leds estão desligados
            if(gpio_get(ButtonA)==0 && leds_desligados()){
              
              //Liga todos os Leds
              gpio_put(LedR,1); 
              gpio_put(LedB,1);
              gpio_put(LedG,1);
              
              //Chamada da função call-back, que iniciará em 3 segundos (3000 ms)
              add_alarm_in_ms(3000, turn_off_callback, NULL, false);
            };

        };
        sleep_ms(10);
    };

    return 0;
}

