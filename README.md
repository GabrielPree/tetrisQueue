# 🎮 Tetris Queue

## 🧩 Descrição
O **Tetris Queue** é um programa em **C** que simula o gerenciamento de peças do jogo **Tetris** usando **estruturas de dados** (fila e pilha).  
O objetivo é demonstrar operações básicas de manipulação, como inserir, remover e trocar peças entre a fila e a pilha.

---

## ⚙️ Funcionalidades
- 🔹 Geração automática de 5 peças iniciais (I, O, T, L)  
- 🔹 Jogar a peça da frente da fila  
- 🔹 Enviar peça da fila para a pilha de reserva  
- 🔹 Usar peça reservada (remover da pilha)  
- 🔹 Trocar a primeira peça da fila com o topo da pilha  
- 🔹 Trocar as 3 primeiras peças da fila com as 3 da pilha  
- 🔹 Visualizar o estado atual da fila e da pilha  

---

## 🧠 Estruturas Utilizadas
- **Fila Circular (FIFO)** → controla as próximas peças a serem jogadas  
- **Pilha (LIFO)** → armazena peças reservadas pelo jogador  

---

## 🕹️ Menu de Opções
| Opção | Ação |
|:------|:------|
| 1 | Jogar peça da frente da fila |
| 2 | Enviar peça da fila para a pilha de reserva |
| 3 | Usar peça da pilha de reserva |
| 4 | Trocar a primeira peça da fila com o topo da pilha |
| 5 | Trocar as 3 primeiras peças da fila com as 3 da pilha |
| 6 | Mostrar fila e pilha |
| 0 | Sair do programa |

---

## ▶️ Como Executar
Compile e execute o programa no terminal:

```bash
gcc tetris_queue.c -o tetris_queue
./tetris_queue
```
---

## 📚 Conceitos Envolvidos

- Estruturas de dados lineares

- Manipulação de structs

- Geração aleatória de elementos

- Operações de fila e pilha

- Lógica circular em vetores

---

# Autor: Gabriel Preé

#### Desenvolvido para fins de estudo em linguagem C, abordando conceitos práticos de estruturas de dados.

---

## 🌐 Uso Livre

Este projeto é de uso totalmente livre.
Você pode copiar, modificar, estudar e distribuir este código sem nenhuma restrição.
Nenhuma licença formal está aplicada a este repositório.
