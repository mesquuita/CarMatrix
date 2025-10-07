// =========================
// BLOCO 1 - DEV A
// =========================
// (Responsável: Inicialização e configuração do sistema)

// Exibir título e introdução do computador de bordo

// Definir flags e configurações iniciais:
//   - usarTemperatura (1 = sim / 0 = não)
//   - usarBluetoothSim (simulação)
//   - velocidadeBase = 80 km/h
//   - incrementoL100 = +0,5L/100km a cada +5km/h
//   - margemSegurancaPct = 15%

// Simular conexão Bluetooth
//   - Perguntar se deseja conectar
//   - Exibir mensagem correspondente

// Solicitar dados do veículo:
//   - Capacidade do tanque (L)
//   - Autonomia média base (km/L)

// Solicitar tipo e preço do combustível:
//   - Tipo (1=gasolina, 2=etanol, 3=diesel)
//   - Preço (R$/L)

// Solicitar nível atual de combustível:
//   - Escolher modo de leitura (1=L / 2=%)
//   - Converter para litros
//   - Garantir que não ultrapasse capacidade

// Inicializar variáveis principais:
//   - kmTotal = 0
//   - custoTotalAbastecimento = 0

// Perguntar se o usuário deseja planejar uma viagem
//   - Se sim, pedir distância planejada (km)

// Solicitar velocidade média alvo
//   - Usar padrão 80 se não informado
//   - Guardar em velocidadeAlvoKmH

// Inicializar temperatura do motor (ex: 90°C)
// Exibir mensagem com opção de ajuda (tecla 9)

// =========================
// FIM DO BLOCO DEV A
// =========================
// =========================
// BLOCO 2 - DEV B
// =========================
// (Responsável: Controle do menu, regras de consumo e direção)

// Iniciar loop principal do sistema (enquanto não sair):
//   - Exibir menu principal com opções numeradas
//   - Ler a opção escolhida pelo usuário

// Caso o usuário selecione 9:
//   - Exibir guia de ajuda explicando o funcionamento geral
// Caso o usuário selecione 0:
//   - Encerrar o loop e seguir para o final

// Antes de executar qualquer opção (exceto 0 e 9):
//   - Calcular regras de consumo:
//       l100_base = 100 / autonomiaBaseKmL
//       l100_extra = incremento conforme velocidade acima de 80
//       l100_final = l100_base + l100_extra
//       autonomiaEfetivaKmL = 100 / l100_final

// Caso a opção seja 1 (Planejamento de viagem):
//   - Solicitar distância total
//   - Calcular tempo estimado (horas/minutos)
//   - Calcular litros necessários e custo
//   - Calcular alcance do tanque atual, máximo e útil
//   - Calcular número de paradas previstas
//   - Exibir resumo com tempo, consumo e custo previstos

// Caso a opção seja 2 (Dirigir trecho):
//   - Solicitar distância percorrida
//   - Se velocidade > 120 → alerta
//   - Calcular litros gastos no trecho
//   - Se combustível insuficiente → mensagem de erro
//   - Caso contrário:
//       reduzir combustívelAtualL
//       aumentar kmTotal
//       atualizar temperatura (+0.02°C por km)
//       se temperatura > 100°C → alerta
//   - Exibir resumo do trecho percorrido

// =========================
// FIM DO BLOCO DEV B
// =========================
// =========================
// BLOCO 3 - DEV C
// =========================
// (Responsável: abastecimento, relatórios e status geral)

// Caso a opção seja 3 (Abastecer):
//   - Calcular espaço livre no tanque
//   - Solicitar quantos litros deseja abastecer
//   - Atualizar combustívelAtualL e custoTotalAbastecimento
//   - Exibir resumo da operação

// Caso a opção seja 6 (Mostrar status):
//   - Calcular l/100km e autonomia atual
//   - Calcular alcance atual e porcentagem do tanque
//   - Exibir status geral:
//       velocidade, autonomia, tanque, kmTotal, custo e temperatura

// Caso a opção seja 8 (Relatório completo):
//   - Exibir resumo consolidado:
//       KM total percorrido
//       Combustível atual e capacidade
//       Custo total abastecimento
//       Tipo e preço do combustível
//       Velocidade alvo e base
//       Temperatura (se ativa)
//       Distância planejada (se houver)

// =========================
// FIM DO BLOCO DEV C
// =========================
// =========================
// BLOCO 4 - DEV D
// =========================
// (Responsável: ajustes e recursos complementares)

// Caso a opção seja 4 (Ajustar velocidade):
//   - Exibir velocidade atual
//   - Solicitar nova velocidade
//   - Se <= 0 → usar base (80 km/h)
//   - Se > 120 → alerta
//   - Salvar novo valor (afeta consumo nas próximas operações)

// Caso a opção seja 5 (Temperatura do motor):
//   - Exibir temperatura atual
//   - Perguntar se deseja atualizar manualmente
//   - Se sim → solicitar novo valor
//   - Se > 100°C → alerta
//   - Caso contrário → mensagem “normal”

// Caso a opção seja 7 (Programar paradas):
//   - Solicitar distância total da viagem
//   - Calcular alcance máximo e alcance útil (margem de segurança)
//   - Calcular paradas necessárias = ceil(distância / alcanceUtil) - 1
//   - Exibir sugestão de número e intervalo de paradas

// Após concluir todas as opções, o usuário pode voltar ao menu
// até optar por “0” para encerrar o programa

// =========================
// FIM DO BLOCO DEV D
// =========================