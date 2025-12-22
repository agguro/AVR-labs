🌍 **Languages**  
- 🇬🇧 [English](learning-paths.md)  
- 🇳🇱 [Nederlands](learning-paths.nl.md)  
- 🇨🇴 [Español (Colombia)](learning-paths.es-co.md)  
- 🇵🇹 [Português (Portugal)](learning-paths.pt.md)

# Percursos de Aprendizagem

Este repositório suporta vários percursos de aprendizagem, dependendo dos conhecimentos prévios, das ferramentas disponíveis e dos objetivos de aprendizagem.  
Todos os percursos conduzem, em última análise, ao mesmo objetivo: compreender como os microcontroladores funcionam realmente.

Nem todos começam do mesmo ponto, e isso é uma decisão de design intencional.

---

## 🟢 Percurso 1 — Entrada guiada (Ponte Arduino)

**Para quem:**  
- iniciantes  
- alunos mais jovens  
- estudantes sem uma toolchain completa  
- primeiro contacto com microcontroladores  

**Ferramentas:**  
- Arduino IDE  
- sketches Arduino (no diretório `arduino/`)  

**Foco:**  
- entrada e saída básicas  
- observação do comportamento  
- experiências simples  

**O que se faz neste percurso:**  
- abrir um sketch fornecido  
- carregá-lo para uma placa Arduino  
- observar LEDs, botões e temporização  

**O que se aprende:**  
- que o código controla o hardware  
- que os pinos têm significado  
- que o tempo é importante  

**Nota importante:**  
Este percurso é um ponto de entrada, não o destino final.  
Os alunos são encorajados a avançar para o Percurso 2 quando se sentirem preparados.

---

## 🟡 Percurso 2 — Simulação primeiro (Percurso principal)

**Para quem:**  
- estudantes que querem compreender o que realmente acontece  
- ambientes sem hardware físico  
- salas de aula com recursos limitados  

**Ferramentas:**  
- `virt-atmega328p`  
- um programa `simulate` por laboratório  
- sistema de construção Meson  

**Foco:**  
- comportamento interno do microcontrolador  
- registos e portas  
- temporização e execução  

**O que se faz neste percurso:**  
- compilar firmware como ficheiros `.elf`  
- executar o firmware em simulação  
- interagir com componentes virtuais  

**O que se aprende:**  
- como o firmware é executado  
- como as portas funcionam realmente  
- a diferença entre simulação e hardware real  

👉 **Este é o percurso de aprendizagem recomendado.**

---

## 🔵 Percurso 3 — Firmware e gravação em flash (Com hardware)

**Para quem:**  
- estudantes prontos para trabalhar com hardware real  
- quem tem curiosidade em perceber o que “carregar” realmente significa  

**Ferramentas:**  
- ficheiros de firmware `.hex`  
- ferramenta `flash`  
- hardware ATmega328P (com ou sem placa Arduino)  

**Foco:**  
- gravação em flash versus “upload”  
- organização da memória  
- comunicação serial  

**O que se faz neste percurso:**  
- gravar firmware diretamente no microcontrolador  
- configurar a taxa de transmissão (baud rate) e as portas  
- observar o comportamento em hardware real  

**O que se aprende:**  
- como o código chega ao microcontrolador  
- qual a função de um bootloader  
- como as ferramentas de software comunicam com o hardware  

---

## 🔴 Percurso 4 — Exploração avançada (Para além do Arduino)

**Para quem:**  
- estudantes avançados  
- autodidatas  
- interessados no design de sistemas embebidos  

**Ferramentas:**  
- extensões do `virt-atmega328p`  
- componentes virtuais  
- depuração de baixo nível  

**Foco:**  
- design de sistemas  
- periféricos  
- arquitetura  

**O que se faz neste percurso:**  
- estender o microcontrolador virtual  
- conceber hardware virtual próprio  
- explorar temporização, interrupções e memória  

**O que se aprende:**  
- como os sistemas embebidos são estruturados  
- como o hardware e o software interagem  
- como as abstrações são criadas  

---

## 🔁 Os percursos não são rigidamente separados

Os alunos podem mover-se livremente entre percursos.  
Alguém pode começar com Arduino, passar para a simulação e regressar mais tarde ao hardware com uma compreensão mais profunda.

O objetivo é a progressão, não a limitação.

---

## 🎯 Objetivo comum

Não apenas fazer algo funcionar,  
mas compreender **porque** funciona.

---

## Nota para docentes

Estes percursos de aprendizagem foram concebidos intencionalmente para funcionar sem hardware físico obrigatório.  
Permitem oportunidades de aprendizagem equitativas em contextos onde os recursos são limitados, sem sacrificar a profundidade técnica.

