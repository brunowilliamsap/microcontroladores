# **Trabalho Final de Microcontroladores 2015 - UFSCar**

![My projeto] (https://github.com/brunowilliamsap/microcontroladores/blob/master/Imagens/projeto.jpg)

## Grupo
Bruno Williams Antunes Pereira 558222

Lucas Lima Oliveira 407755

##Objetivo do trabalho final:
O objetivo desse projeto é fomentar o trabalho em equipe e exercitar os conceitos abordados na disciplina de Laboratórios de Microcontroladores em um sistema de automação de baixa complexidade.

##Tema proposto:
O grupo deveria implementar um sistema de automação de baixa complexidade que possuem obrigatoriamente:
* Um display com informação de status, funcionamento, etc;
* Ao menos dois atuadores, sendo um deles um motor de passo;
* Ao menos um sensor, podendo ter outras entradas como botões etc;

##Proposta de projeto:
O projeto consiste da implementação, por vezes teórica, do controle de um quarto de hotel utilizando um Arduino e um celular se comunicando via bluetooth.

![My appUser] (https://github.com/brunowilliamsap/microcontroladores/blob/master/Imagens/appUser.jpg)
O usuário se conecta ao quarto via bluetooth, utilizando um aplicativo para android que foi desenvolvido por nós. Uma vez logado no aplicativo o usuário poderá controlar todas funções básicas do quarto pelo celular.



##Componentes utilizados:
* 1 arduino uno
* 1 módulo bluetooth HC-05
* 1 shild Grove - Starter Kit Plus
* 1 Grove - Temperature Sensor
* 1 Grove - RGB Backlight LCD
* 1 ULN2003
* 2 led vermelhos
* 1 led verde
* 1 led amarelo
* 1 motor de passos
* 4 resistores de 1k (ohm)
* 1 resistor de 1k2 (ohm)
* 1 resistor de 2k2 (ohm)
* 1 protoboard
* 1 fonte de tensão de 5 volts
* diversos fios para conexão
* 1 celular android

##Esquema elétrico
![My painelEletrico] (https://github.com/brunowilliamsap/microcontroladores/blob/master/Imagens/painelEletrico.jpg)

##Funcionamento
O aplicativo do celular enviará caracteres do tipo char, que será recebido pelo módulo bluetooth. Este por sua vez envia as informações para o arduino que dependendo do caractere recebido executa uma função diferente.


O sensor de temperatura é monitorado a cada ciclo de loop e o ar condicionado é ligado quando a temperatura ambiente é maior do que a desejada pelo usuário.  A tolerância para o acionamento de ligar e desligar do ar condicionado é de 1 grau para mais ou para menos. Para representar o ligar e desligar do ar condicionado foi utilizado um led.

O motor de passos é utilizado tanto para abrir e fechar a porta como a janela, o ideal era ter uma para cada função, mas como parte dessa aplicação é teórica, utilizaremos o mesmo motor para ambas aplicações. Para diferenciar cada uma delas utilizamos dois led's, sendo um ligado para indicar que o motor da porta está ligado e outro para o motor da janela.

Um terceiro led foi usado para simbolizar a luz do quarto. Esse luz tem o diferencial de mudar a intensidade da iluminação de acordo com a vontade do usuário.

Um display de lcd foi implementado ao projeto, onde na primeira linha exibe uma mensagem de preferencia do hotel, e na segunda uma mensagem de status.
![My portaFechando] (https://github.com/brunowilliamsap/microcontroladores/blob/master/Imagens/portaFechando.jpg)


##Sobre o aplicativo:
O aplicativo foi criado utilizando a ferramenta "mit.app inventor 2"
![My appFoto] (https://github.com/brunowilliamsap/microcontroladores/blob/master/Imagens/appFoto.png)

![My appFoto2] (https://github.com/brunowilliamsap/microcontroladores/blob/master/Imagens/appFoto2.png)

Primeiramente o usuário precisa se conectar ao quarto. Caso a conexão seja bem sucedida, o aplicativo avisa o mesmo. Caso o bluetooth do celular não esteja ligado ao aplicativo também avisa na sua inicialização. Sempre é possível ver o Status da conexão clicando em "Checar Conexão".
Dois botões de feedback informam o usuário a quantidade de comandos já executados e o tempo desde que o usuário está no quarto.

![My terminal] (https://github.com/brunowilliamsap/microcontroladores/blob/master/Imagens/terminal.png)


O aplicativo, Controle Hotel, encontra-se disponível para download nesse repositório.

## Outros trabalhos desta disciplina

https://github.com/Power041/cancela

https://github.com/jblsouza/Lab-Mic-A

https://github.com/iksmada/TuringMachine

https://github.com/Fonseka100/MIC-Amaciante

https://github.com/matheusvervloet/girassolar

https://github.com/alex-dias/TrabalhoFinalMIC2015

https://github.com/gustavocesarlos/trabalhofinalMic

https://github.com/gabrielNT/LabMicApl_TrabalhoFinal

https://github.com/brunowilliamsap/microcontroladores

https://github.com/rodrigoa1990/Projeto-Microcontroladores

https://github.com/matheusDeAlmeida/trabalhoFinalMicrocontroladores
