# Acionando Leds com Botão

__Atividade 2 da Tarefa 2 - Aula Síncrona 29/01__<br>
Repositório criado com o intuito de realizar a Atividade 2 da Tarefa 2 da aula Síncrona do dia 29 de janeiro de 2025 sobre Clocks e Temporizadores.

__Responsável pelo desenvolvimento:__
Andressa Sousa Fonseca

## Descrição Da Tarefa 

__Os Componentes necessários para a simulação da atividade no Wokwi Integrado ao VS Code:__
1) Microcontrolador Raspberry Pi Pico W.
2) 03 LEDs (azul, vermelho e verde).
3) 03 Resistores de 330 Ω.
4) Botão (Pushbutton).

Os componentes acima já estão presentes no kit de Desenvolvimento Bit Dog Lab.

__As funcionalidade básicas especificadas para a atividade são:__
1) Ao pressionar o Botão todos os leds serão ligados e uma rotina de temporização será chamada após 3 segundos.
2) Os leds desligarão um por um a partir de rotinas de temporização.
3) O Botão só poderá ser novamente acionado se todos os leds estiverem desligados.
4) Implementar rotina de software para atenuar efeito bouncing do botão.

__Aplicação de temporizadores__  <br>

A atividade 1 utiliza temporizadores de um disparo para desligar os leds no tempo especificado. Para isso, é necessário chamar a seguinte rotina de callback:
```bash
add_alarm_in_ms(3000, turn_off_callback, NULL, false)
```
Essa rotina é chamada sempre que o botão é acionado, determinando que a função 'turn_off_callback()' será executar em 3 segundos. Na função 'turn_off_callback()', visualizada abaixo, está toda a lógica para o desligamento ordenado dos leds. Na qual, a função  'add_alarm_in_ms(3000, turn_off_callback, NULL, false)' é chamada novamente duas vezes, permitindo que todos os leds sejam desligados ordenadamente no tempo desejado.
```bash
int64_t turn_off_callback(alarm_id_t id, void *user_data)
```

__A simulação do projeto pode ser visualizada no seguinte link: [Simulação com Wokwi Web - Botão e Leds](https://wokwi.com/projects/421979844521519105).__

## Detalhamento do Funcionamento

O presente código permite ligar 3 leds ao mesmo tempo após pressionar o Botão A e desligá-los automaticaente um a um a cada 3 segundos. Para isso, o sistema verifica se ao pressionar o botão todos os leds estão desligados. Se sim, todos os leds são ligados e depois de 3 segundos o primeiro led é desligado. E assim, a cada 3 segundos um novo led é desligado. Por fim, com todos desligados, é possível ligá-los novamente ao pressionar o botão A (Botão esquerdo na placa).

## Passos para uso do código

Os arquivos presentes no repositório são fundamentais para a execução do projeto. Assim, o primeiro passo é clonar o atual repositório 'Semaforo' no seu computador para poder rodá-lo no VS Code. Vale ressaltar que para o devido funcionamento do simulador é necessário ter o Wokwi Integrado.

### 1. Clonar repositório
Abra a pasta que deseja armazenar o projeto no VS Code. Depois, abra um Terminal e cole a linha de comando abaixo:
```bash
git clone https://github.com/Dreh3/Botao_Leds.git
```

### 2. Abrir a pasta do projeto
Após clonar, é necessário abrir a pasta do projeto para que o VS Code possa reconstruir a pasta 'build' e assim poder executar o código com sucesso.

### 3. Compilar o código
Compilar o código é um passo essencial para gerar os arquivos necessários para usra o simulador e adicionar as bibliotecas do CMakeLists.txt.

### 4. Simulador Wokwi 
Após os passos acima, o último passo necessário é abrir o arquivo diagram.json. Assim, o simulador Wokwi integrado irá iniciar e o projeto poderá ser visualizado.

### 5. Placa
Todos os passos citados aplicam-se para carregar o código no ki de Desenvolvimento Bit Dog Lab. A única diferença é que o 4° passo não é essencial. Assim, após o passo 3, basta selecionar a opção 'Run' na barra inferior do VS Code para que o Semáforo passe a funcionar na placa.

<div align="center">
  <img src="https://github.com/Dreh3/Botao_Leds/blob/main/botaoLedsimagem.png?raw=true" alt="imagem do simulador" width="300"/>
</div>
