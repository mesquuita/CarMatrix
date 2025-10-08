# CarMatrix
# Computador de Bordo - C++

Este é um programa em **C++** que simula um **computador de bordo de veículo**, permitindo planejar viagens, monitorar consumo de combustível, controlar velocidade, registrar temperatura do motor e programar paradas.

## Funcionalidades

- Planejar viagens: calcula tempo estimado, litros necessários, custo e número de paradas.
- Dirigir trechos: atualiza quilometragem total, consumo de combustível e temperatura do motor.
- Abastecer: calcula espaço disponível, atualiza combustível e custo total.
- Ajustar velocidade: define velocidade média alvo e calcula impacto no consumo.
- Monitorar temperatura do motor: alerta se ultrapassar 100°C.
- Mostrar status do veículo: exibe autonomia, alcance, km total, combustível e temperatura.
- Programar paradas: sugere número e intervalo de paradas considerando margem de segurança.
- Relatório completo: resumo consolidado do veículo e da viagem.
- Ajuda interativa para orientação do usuário.

## Requisitos

- Compilador C++ moderno (MinGW-w64 recomendado no Windows, g++ no Linux/macOS)
- VS Code ou outro editor de código

## Estrutura do Código

O código está organizado em blocos de desenvolvimento simulando diferentes responsabilidades:

- **DEV A**: Inicialização e configuração do sistema, dados do veículo e combustível.
- **DEV B**: Controle do menu principal, regras de consumo e direção.
- **DEV C**: Abastecimento, relatórios e status geral.
- **DEV D**: Ajustes e recursos complementares (velocidade, temperatura e paradas).

## Como Compilar e Executar

### No Windows (MinGW-w64)

1. Abra o terminal integrado do VS Code na pasta do projeto.
2. Compile o programa:
```bash
g++ teste.cpp -o teste.exe
````

3. Execute:

```bash
.\teste.exe
```

### No Linux/macOS

1. Compile:

```bash
g++ teste.cpp -o teste
```

2. Execute:

```bash
./teste
```

> ⚠️ Observação: se estiver usando Code Runner no VS Code, configure para **"Run in Terminal"** para que o `cin` funcione corretamente.

## Uso

* O programa pede inicialmente se deseja conectar via Bluetooth (simulado).
* Solicita dados do veículo: capacidade do tanque, autonomia, tipo e preço do combustível.
* Permite escolher o nível de combustível atual (em litros ou %).
* Menu interativo com opções numeradas:

  1. Planejar viagem
  2. Dirigir trecho
  3. Abastecer
  4. Ajustar velocidade
  5. Temperatura do motor
  6. Mostrar status
  7. Programar paradas
  8. Relatório completo
  9. Ajuda
  10. Sair

## Observações

* Velocidade base padrão: 80 km/h.
* Consumo adicional: +0,5 L/100 km para cada incremento de 5 km/h acima da base.
* Margem de segurança de combustível padrão: 15%.
* Temperatura do motor aumenta 0,02°C por km percorrido e alerta se ultrapassar 100°C.

## Autor

* Desenvolvido por [Seu Nome] como projeto de estudo/treinamento em C++.

```
```
