[Home](../../../README.md)  -  [Docs index](../../index/README.md)
[🇬🇧](README.md)  -  [🇳🇱](README.nl.md)  -  [🇨🇴](README.es-co.md)  -  [🇵🇹](README.pt.md)

# Estudo de firmware compilado (avançado)

Este documento introduz o estudo de firmware compilado para fins educativos.  
Destina-se a alunos avançados que pretendem compreender o que permanece de um programa quando o código-fonte não está disponível.

Este tópico é opcional e não é necessário para completar os percursos de aprendizagem principais.

---

## O que se entende aqui por “engenharia inversa”

Neste contexto, engenharia inversa significa analisar firmware compilado para compreender a sua estrutura, comportamento e limitações.  
O objetivo **não** é reconstruir o código-fonte nem contornar mecanismos de proteção.

O foco está em compreender como um microcontrolador executa instruções ao nível da máquina.

---

## O que pode ser analisado

Os alunos podem analisar, entre outros:

- ficheiros `.elf`, com ou sem símbolos de depuração  
- ficheiros `.hex` que representam imagens de firmware  

Estes ficheiros podem ter origem em:
- firmware criado neste repositório  
- exemplos de acesso livre  
- projetos próprios do aluno  

---

## Objetivos educativos

Ao analisar firmware compilado, os alunos podem:

- observar como código de alto nível é traduzido em instruções  
- compreender a organização da memória e o fluxo de execução  
- identificar o impacto das otimizações do compilador  
- reconhecer a importância dos símbolos de depuração  

---

## Questões a explorar

Exemplos de questões adequadas a este tema:

- É possível identificar ciclos ou atrasos?  
- Conseguem-se reconhecer operações de entrada e saída?  
- Que informação se perde quando os símbolos de depuração são removidos?  
- Porque é difícil reconstruir código-fonte a partir de firmware?  

---

## Ferramentas e abordagem

Podem ser utilizadas várias ferramentas neste estudo, tais como:

- desassembladores  
- ferramentas de inspeção de símbolos  
- simuladores  
- scripts de análise personalizados  

A ênfase está na **observação e interpretação**, não na automatização.

---

## Âmbito e limitações

Esta atividade foca-se na compreensão, não na reconstrução.  
Em geral, não é possível recuperar o código-fonte original a partir de firmware compilado.

As conclusões devem ser vistas como interpretações fundamentadas.

---

## Nota ética e legal

Este tópico destina-se exclusivamente a fins educativos.  
Os alunos devem trabalhar com o seu próprio firmware ou com exemplos de acesso livre, respeitando sempre as licenças de software.

---

## Quando abordar este tópico

Este tópico deve ser explorado:

- após concluir os percursos de aprendizagem principais  
- com conhecimentos prévios de assembly e arquitetura de microcontroladores  
- com orientação em contextos educativos  

Esta secção existe para aprofundar o conhecimento e estimular a curiosidade.

