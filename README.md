UAV-Simulator

1 - Funcionalidades básicas do simulador https://youtu.be/GzV9ihQQMSQ

    - Adicionar VANT
    - Adicionar Sensores
    - Estados dos Sensores (Sleeping/Broadcast)
    - Raio de Conexão
    - Arrastar e Soltar
    - Trocar de Mensagens entre VANTs e Sensores
    - Tipo de Mensagem
    - Reset do Cenário
    - Alinhamento e posicionamento inicial

2 - Visão geral do funcionamento do Simulador https://youtu.be/FJWcag976WQ

    - Velocidade de deslocamento do VANT
    - Repetição dos TimeSLots (ou não)
    - Início da conversa sobre uTimeSlots
    - Programação dos microTimeSlots
    - Introdução às listas de permissão/restrição
    - Painél de visão geral do UAV (speed, Hops, distance, autonomia, ...)
    - Apresentação dos TimeSlots nos painéis
    - Cálculo de previsão de chegada nos targets
    - Tomadas de decisão sobre as listas de permissão/restrição
    - Tempo de Broadcast baseado em TimeSlots (1, 2 ou mais timeSlots, .. programável)

3 - Rotas, Percursos e sobreposição de áreas https://youtu.be/R8Rpca_RfNo

    - Rotas / Percursos possíveis do VANT
    - Green - NearestPoint
    - Red - Sobrevôo sobre o Sensor
    - Blue - Kashuba (modelo do artigo base)
    - Cyan - Modelo Híbrido entre NearestPoint (Green) e Kashuba (Blue)
    - Informações adicionais sobre rotas
    - Percurso aberto/fechado
    - Cálculo das distâncias
    - Sobreposição das áreas de cobertura dos sensores

4 - Autonomia dos VANTs https://youtu.be/Izlbdt3jTrc

    - Autonomia por Distância
    - Autonomia por Tempo
    - Troca de informações de roteamento/restrições entre VANTs
    - Informação da Bateria no Painél do UAV
    - Alterações de velocidade para facilitar a visualização
    - Alternância entre 5 VANTs para uma baixa autonomia (teste)
    - Velocidade alta (50m/s) para visualização apenas
    - Visualização dos atributos internos do Painel dos VANTs são reapresentadas à cada troca
    - Listas de permissão/restrição - herança entre VANTs ao copiar os dados
    - Apresentação da autonomia por tempo, 60s/VANT

5 - Simulação 1 https://youtu.be/yv1tXns3o7Q

    - Programação com 10 uTimeSlots
    - Alta velocidade para agilizar
    - Listas de restrição/permissão
    - Tomada de decisões sobre as listas de permissão/restrição
    - Apresentação do conceito da solução do projeto
    - uTimeSlots como "preenchimento" entre distâncias maiores, dando flexibilidade ao VANT em baixa velocidade

6 - Simulação 2 (Cálculo dos uTimeSlots) https://youtu.be/9Pbu-_Ft7nQ

    - Tempo total da rota / uTimeSlots (10, 20, 30, 50, 100, ...)
    - Gera o valor fixo do intervalo de uTimeSlot
    - Porém arredondamentos do tipo, vou levar 1,6 uTimeSlots para chegar até o sensor X, arredonda para 2 uTimeSlots
    - Essa somatória de arredondamentos geram uTimeSlots adicionais
    - Distâncias maiores entre Sensores levam o VANT a utilizar mais timeSlots no cálculo
    - Apresentação do cálculo dos timeSlots realizado pelo Simulador
    - Velocidade do VANT 25m/s
    - Tomadas de decisões baseado em listas de permissão/restrição

7 - Repetição dos uTimeSlots https://youtu.be/__nhjXjPIr0

    - uTimeSlots repetidos (ou não)
    - estado BUSY TO FLY não é mais válido nesse cenário com repetição
    - Se há mais que um Sensor em Broadcast por timeSlot, o VANT não aguarda mais o próximo TimeSlot para voar
    - Apresentação de Sensores no mesmo timeSlot
    - Tempo de broadcast baseado em timeSlots (1, 2 ou mais timeSlots em que o Sensor fica ativo transmitindo)
    - Inserção manual do timeSlot de cada sensor através do grid
    - 3 timeSlots para broadcast, uma visualização apenas
