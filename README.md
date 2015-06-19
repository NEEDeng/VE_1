# VE-1 Ve�culo Educacional 1


## Sobre
Projeto referente plataforma educacional <b>open source(c�digo livre)</b> nomeadea de VE-1, que consiste em um rob� m�vel, 
composto por duas rodas motrizes e um conjunto de sensores e atuadores embarcados. Tal plataforma foi desenvolvida com o intu�to de servir de plataforma atuadora/sensora base, sendo que em sua l�gica apenas c�digo referente ao seus sensores e atuadores de interface com o mundo f�sico, enquanto toda l�gica deve ser programada em um circuito microcontrolado a parte.

##Motiva��o
<ol>
<lI>Ap�s ter trabalhado com alguns rob�s educacionais como o LEGO EV3 e seus antecessores, e uma frustrante tentativa
de desenvolver para meu filho e meus alunos, um rob� m�vel e robusto utilizando arduino, e seus respectivos componentes, me dei conta 
que de fato tal plataforma est�vel, acess�vel financeiramente, recheada de tecnologia embarcada, open-source estava por vir, logo, decidi dar o primeiro passo.</lI>
<lI>Ap�s anos acompanhando e utilizando projetos open-source ao redor do mundo, me dei conta do potencial que desenvolvem nas pessoas, o engajamento das mesmas, o fluxo e a qualidade de informa��o que geram, devido � forma que abordam o fator humano motivacional e a formalidade da documenta��o, que s�o fatores que n�o garantem o sucesso mas que com certeza fazem parte do mesmo! Assim de forma a "tropicalizar" essa tend�ncia mundial e dar um gostinho na vers�o "tupiniquim" do potencial empresarial, motivacional, financeiro, humano e de gera��o de valores, inauguro este projeto como meu primeiro projeto open source. �ltima palavra sobre o assunto: Fica aqui um v�deo animado em Lego, que traduzi de uma empresa dinamarquesa chamada BitBlueprint sobre o tema. [LINK](https://www.youtube.com/watch?v=a8fHgx9mE5U)</lI>
<lI> Outro ponto importante que me motivou a desenvolver tal projeto, � a oportunidade de exemplificar para todos algumas t�cnicas modernas de documenta��o. Para tal utilizarei Git para versionamento, Doxygen para documenta��o do c�digo e diagramas UML para diagrama��o de forma geral. </lI>
</ol>
Espero que voc�s gostem! ;)

##Introdu��o
Incialmente esta plataforma foi desenvolvida para que pudesser utilizada com Arduino e Lego EV3, 
comunicando-se com ambos via porta I2C. Este projeto est� dividido em quatro(4) etapas.
<ol>
<lI> Hardware VE-1 </lI>
  <ol>
  <lI> Circuito Impresso VE-1 �</lI>
  <lI> Firmware VE-1 ��</lI>
  </ol>
<lI>Software �</lI>
<lI>Bibliotecas</lI>
  <ol>
  <lI>Arduino ��</lI>
  <lI>Lego ��� </lI>
  </ol>
<lI>Estrutura �</lI>
 </ol>
 
�    Feito.   
��   Em constante desenvolvimento.   
���  Em breve.   

A primeira fase se refere ao <b>hardware dedicado</b>, tanto ao projeto do mesmo fisicamente quanto o firmware, a segunda fase corresponde ao <b>software</b> de interface utilizado para fazer uma interface de todos os sensores e atuadores da placa, com a finalidade de debug do c�digo ou teste, enquanto a terceira fase corresponde �s <b>bibliotecas</b> de compatibilidade com os demais dispositivos, j� a fase quatro corresponde ao projeto mec�nico, � <b>estrutura do rob�</b> disponibilizada no formato .stl.

## Softwares utilizados
<ol> 
  <lI><b>Kicad</b> para desenho de placas</lI>
  <lI><b>Atmel Studio</b> para desevolvimento do firwmare</lI>
  <lI><b>Arduino IDE</b> para biblioteca compat�vel com arduino</lI>
  <lI><b>EV3 SOFTWARE</b> para bibliotecas compat�vel com EV3 </lI>
  <lI><b>Freecad</b> para desenho do rob�</lI>
  <lI><b>Qt</b>interface de Debug</lI>
</ol>
### 1- Hardware VE-1
sdsdsd
### 2- Software
sdsd
### 3- Bibliotecas

## Vantagens 
As vantagens do EV-1 comparado com os demais m�dulos educacionais m�veis existentes no mercado, s�o:
<ol>
<lI><b>Quantidade de sensores</b> A placa EV-1 � composta por 10(dez) sensores de IR, (1)um girosc�pio e aceler�metro. </lI>
<lI><b>Open-Source</b> Grande variedade de informa��es est�o dispon�veis a qualquer um que deseje para fazer uso. </lI>
<lI><b>Customiz�vel</b> Por ser um projeto open-source, voc� pode modifica-lo e customizar-lo como queira. </lI>
<lI><b>Compatibilidade</b>O circuito do EV-1 � compat�vel com qualquer plataforma que se comunique via I2C, tais como PIC, AVR, Arduino, LEGO e outros.</lI>
<lI><b>Economia de bateria</b>diferentemente de placas tais como arduino o circuito EV-1, apresenta um conversor buck, integrado que apresenta um ganho de efici�ncia de 90% comparado com o conversor 12V->5V do arduino.</lI>
<lI><b>Variedade de alimenta��o</b>diferentemente de plataformas tais como a lego, onde baterias recarreg�veis n�o funcionam EV-1 funciona com virtualmente qualquer tipo de alimenta��o </lI>
</ol>

##Contribuidores
Somenteo autor at� o presente momento 06/11/2015
##Autor
Eng. T�lio Pires , formado em engenharia mec�nica com �nfase em mecatr�nica pela PUC-MG, trabalho com projeto de m�quinas e 
circuitos embarcados a v�rios anos, fazendo juz ao termo <b>mecatr�nica</b>!
##Licen�a
Este projeto se encontra sob a licen�a GNU V2.0 [TERMOS](http://choosealicense.com/licenses/gpl-2.0/)
