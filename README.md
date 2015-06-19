# VE-1 Veículo Educacional 1


## Sobre
Projeto referente plataforma educacional <b>open source(código livre)</b> nomeadea de VE-1, que consiste em um robô móvel, 
composto por duas rodas motrizes e um conjunto de sensores e atuadores embarcados. Tal plataforma foi desenvolvida com o intuíto de servir de plataforma atuadora/sensora base, sendo que em sua lógica apenas código referente ao seus sensores e atuadores de interface com o mundo físico, enquanto toda lógica deve ser programada em um circuito microcontrolado a parte.

##Motivação
<ol>
<lI>Após ter trabalhado com alguns robôs educacionais como o LEGO EV3 e seus antecessores, e uma frustrante tentativa
de desenvolver para meu filho e meus alunos, um robô móvel e robusto utilizando arduino, e seus respectivos componentes, me dei conta 
que de fato tal plataforma estável, acessível financeiramente, recheada de tecnologia embarcada, open-source estava por vir, logo, decidi dar o primeiro passo.</lI>
<lI>Após anos acompanhando e utilizando projetos open-source ao redor do mundo, me dei conta do potencial que desenvolvem nas pessoas, o engajamento das mesmas, o fluxo e a qualidade de informação que geram, devido à forma que abordam o fator humano motivacional e a formalidade da documentação, que são fatores que não garantem o sucesso mas que com certeza fazem parte do mesmo! Assim de forma a "tropicalizar" essa tendência mundial e dar um gostinho na versão "tupiniquim" do potencial empresarial, motivacional, financeiro, humano e de geração de valores, inauguro este projeto como meu primeiro projeto open source. Última palavra sobre o assunto: Fica aqui um vídeo animado em Lego, que traduzi de uma empresa dinamarquesa chamada BitBlueprint sobre o tema. [LINK](https://www.youtube.com/watch?v=a8fHgx9mE5U)</lI>
<lI> Outro ponto importante que me motivou a desenvolver tal projeto, é a oportunidade de exemplificar para todos algumas técnicas modernas de documentação. Para tal utilizarei Git para versionamento, Doxygen para documentação do código e diagramas UML para diagramação de forma geral. </lI>
</ol>
Espero que vocês gostem! ;)

##Introdução
Incialmente esta plataforma foi desenvolvida para que pudesser utilizada com Arduino e Lego EV3, 
comunicando-se com ambos via porta I2C. Este projeto está dividido em quatro(4) etapas.
<ol>
<lI> Hardware VE-1 </lI>
  <ol>
  <lI> Circuito Impresso VE-1 °</lI>
  <lI> Firmware VE-1 °°</lI>
  </ol>
<lI>Software °</lI>
<lI>Bibliotecas</lI>
  <ol>
  <lI>Arduino °°</lI>
  <lI>Lego °°° </lI>
  </ol>
<lI>Estrutura °</lI>
 </ol>
 
°    Feito.   
°°   Em constante desenvolvimento.   
°°°  Em breve.   

A primeira fase se refere ao <b>hardware dedicado</b>, tanto ao projeto do mesmo fisicamente quanto o firmware, a segunda fase corresponde ao <b>software</b> de interface utilizado para fazer uma interface de todos os sensores e atuadores da placa, com a finalidade de debug do código ou teste, enquanto a terceira fase corresponde às <b>bibliotecas</b> de compatibilidade com os demais dispositivos, já a fase quatro corresponde ao projeto mecânico, à <b>estrutura do robô</b> disponibilizada no formato .stl.

## Softwares utilizados
<ol> 
  <lI><b>Kicad</b> para desenho de placas</lI>
  <lI><b>Atmel Studio</b> para desevolvimento do firwmare</lI>
  <lI><b>Arduino IDE</b> para biblioteca compatível com arduino</lI>
  <lI><b>EV3 SOFTWARE</b> para bibliotecas compatível com EV3 </lI>
  <lI><b>Freecad</b> para desenho do robô</lI>
  <lI><b>Qt</b>interface de Debug</lI>
</ol>
### 1- Hardware VE-1
sdsdsd
### 2- Software
sdsd
### 3- Bibliotecas

## Vantagens 
As vantagens do EV-1 comparado com os demais módulos educacionais móveis existentes no mercado, são:
<ol>
<lI><b>Quantidade de sensores</b> A placa EV-1 é composta por 10(dez) sensores de IR, (1)um giroscópio e acelerômetro. </lI>
<lI><b>Open-Source</b> Grande variedade de informações estão disponíveis a qualquer um que deseje para fazer uso. </lI>
<lI><b>Customizável</b> Por ser um projeto open-source, você pode modifica-lo e customizar-lo como queira. </lI>
<lI><b>Compatibilidade</b>O circuito do EV-1 é compatível com qualquer plataforma que se comunique via I2C, tais como PIC, AVR, Arduino, LEGO e outros.</lI>
<lI><b>Economia de bateria</b>diferentemente de placas tais como arduino o circuito EV-1, apresenta um conversor buck, integrado que apresenta um ganho de eficiência de 90% comparado com o conversor 12V->5V do arduino.</lI>
<lI><b>Variedade de alimentação</b>diferentemente de plataformas tais como a lego, onde baterias recarregáveis não funcionam EV-1 funciona com virtualmente qualquer tipo de alimentação </lI>
</ol>

##Contribuidores
Somenteo autor até o presente momento 06/11/2015
##Autor
Eng. Túlio Pires , formado em engenharia mecânica com ênfase em mecatrônica pela PUC-MG, trabalho com projeto de máquinas e 
circuitos embarcados a vários anos, fazendo juz ao termo <b>mecatrônica</b>!
##Licença
Este projeto se encontra sob a licença GNU V2.0 [TERMOS](http://choosealicense.com/licenses/gpl-2.0/)
