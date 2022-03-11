# AMBIENTE PARA DESENVOLVIMENTO DE HARDWARE ABSTRACTION LAYER

## Sobre
Este projeto consiste no estudo de técnicas de desenvolvimento de um projeto de software embarcado, cujo objetivo é tornar a lógica da aplicação embarcada separada e independente de um microcontrolador em específico. Portanto, o proprósito deste repositório é servir de recursos para idealização e experimentação de práticas para implementação de uma camada de abstração de hardware no contexto de sistemas embarcados.

Desta forma, uma vez abstraída a utilização dos recursos de hardware necessário no código da aplicação, a ideia é que uma camada de abstração de hardware (HAL) seja implementada sob demanda, para atender aos serviços de hardware que o código da aplicação requisita. Com isso, a concretização deste sistema é que a aplicação dependa de uma interface e a camada de abstração de hardware implemente esse interface, escondendo as complexidades e especificídades de qualquer microcontrolador da lógica que rege o projeto da solução embarcada. 

![image](https://user-images.githubusercontent.com/63216146/157783674-e1cf425c-42b2-4067-b562-8aad52ecedba.png)

Sendo assim, a aplicação interage apenas com a interface, desconhecendo em qual o microcontrolador que está sendo executada. Portanto, a implementação da HAL, nesse contexto, é uma adaptação dos drivers de um microcontrolador específico para a realidade que a aplicação necessita. Deste modo, essa separação torna a solução apta para rodar em outros hardwares, trocando apenas o adaptador que implementa a HAL para o microcontrolador em questão. Neste sentido, a intenção é que a solução não tenha que se adaptar ao hardware, mas sim que um adaptador realize essa conexão entre o software da aplicação e o firmware do microcontrolador.

O projeto de estudo inicialmente utiliza o microcontrolador ATmega328p, com o auxílio de ferramentas de simulação. Deste modo, é possível obter um feedback que irá viabilizar a implementação das práticas em um projeto físico e com outros microcontroladores.
