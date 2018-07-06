# socket

O objetivo do trabalho é a criação de dois programas, um em C e outro em Python, de um socket que sejam capazes de trocarem
as informações de ping e pong.

Os códigos possuem a possibilidade de gerar clients ou servers com protocolo TCP ou UDP e permite informar a quantidade de
mensagens que o cliente envia ao server.

Ao receber a mensagem de ping do client o server responde, enviando para o client pong. No cliente é mostrado o tempo mínimo,
médio e máximo levados para transmitir e receber o pacote.

O principal objetivo de tal atividade é observar a diferença de tempos de transmissão nos protocolos UDP e TCP, comprovando que
o protocolo UDP é mais rápido por não possuir verificação de erros na transmissão do pacote, e assim não garantindo o envio da
mensagem.

Além disso é possivel verificar a diferença de tempo de transmissão da aplicação sendo executada em C e a em python, verificando
que em C normalmente é mais veloz pela ausência do interpretador presente no Python.
