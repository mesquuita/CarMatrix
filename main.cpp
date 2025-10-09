#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// =========================
// BLOCO DEV A - Inicialização e configuração
// =========================

int main() {
    cout << "=== COMPUTADOR DE BORDO ===" << endl;

    // Flags e configurações iniciais
    int useTemperature = 1;      // 1 = sim / 0 = nao
    int useBluetoothSim = 0;     // simulação Bluetooth
    float baseSpeed = 80.0;      // km/h
    float incrementL100 = 0.5;   // L/100km a cada +5 km/h acima da base
    float safetyMarginPct = 15.0; // %

    // Simulação de conexão Bluetooth
    cout << "Deseja conectar via Bluetooth? (1=sim / 0=nao): ";
    cin >> useBluetoothSim;
    cout << (useBluetoothSim ? "Bluetooth conectado com sucesso." : "Bluetooth nao conectado.") << endl;

    // Dados do veículo
    float tankCapacityL = 0.0, baseAutonomyKmL = 0.0;
    cout << "Capacidade do tanque (litros): ";
    cin >> tankCapacityL;
    cout << "Autonomia media base (km/L): ";
    cin >> baseAutonomyKmL;

    // Tipo e preço do combustível
    int fuelType = 0;
    float fuelPrice = 0.0;
    cout << "Tipo de combustivel (1=gasolina, 2=etanol, 3=diesel): ";
    cin >> fuelType;
    cout << "Preco do combustivel (R$/L): ";
    cin >> fuelPrice;

    // Nível atual de combustível
    int readMode = 0;
    float currentFuelL = 0.0;
    cout << "Modo de leitura do combustivel (1=litros / 2=porcentagem): ";
    cin >> readMode;

    if (readMode == 1) {
        cout << "Informe quantidade atual de combustivel (L): ";
        cin >> currentFuelL;
    } else {
        float percentage = 0.0;
        cout << "Informe porcentagem atual do tanque (0 a 100%): ";
        cin >> percentage;
        currentFuelL = (percentage / 100.0f) * tankCapacityL;
    }

    if (currentFuelL > tankCapacityL) currentFuelL = tankCapacityL;

    // Inicializar variáveis principais
    float totalKm = 0.0;
    float totalRefuelCost = 0.0;
    float tripDistanceKm = 0.0;
    float targetSpeedKmH = 0.0;
    float engineTempC = 90.0;

    // =========================
    // NOVAS VARIÁVEIS E CONTADORES
    // =========================
    float kmSinceLastRefuel = 0.0;   // Km rodados desde último abastecimento
    float lastRefuelLiters = 0.0;    // Litros abastecidos na última operação
    float tripTimeH = 0.0;           // Tempo total de viagem acumulado
    const float referenceSpeedKmH = 80.0; // Velocidade média de referência

    // Solicitar velocidade alvo
    cout << "Informe a velocidade media alvo (km/h): ";
    cin >> targetSpeedKmH;
    if (targetSpeedKmH <= 0) targetSpeedKmH = baseSpeed;

    cout << "Pressione 9 no menu principal para ajuda durante o uso do sistema." << endl;

    // =========================
    // BLOCO DEV B - Controle do menu e regras de direção
    // =========================

    int option = -1;
    float effectiveAutonomyKmL = 100.0f / (100.0f / baseAutonomyKmL);
    cout << fixed << setprecision(2);

    while (option != 0) {
        cout << "\n=== MENU PRINCIPAL ===\n";
        cout << "1 - Planejar viagem\n2 - Dirigir trecho\n3 - Abastecer\n4 - Ajustar velocidade\n";
        cout << "5 - Temperatura do motor\n6 - Mostrar status\n7 - Programar paradas\n";
        cout << "8 - Relatorio completo\n9 - Ajuda\n0 - Sair\nEscolha uma opcao: ";
        cin >> option;

        if (option == 9) {
            cout << "\n--- AJUDA ---\n";
            cout << "Use este sistema para planejar viagens, dirigir trechos, abastecer e acompanhar o status do veiculo.\n";
            continue;
        }

        if (option == 0) {
            cout << "\nEncerrando sistema...\n";
            break;
        }

        // Cálculo de consumo
        float l100_base = 100.0f / baseAutonomyKmL;
        float speedExcess = targetSpeedKmH - baseSpeed;
        if (speedExcess < 0) speedExcess = 0;
        int speedBlocks = static_cast<int>(speedExcess / 5);
        float l100_extra = speedBlocks * incrementL100;
        float l100_final = l100_base + l100_extra;
        effectiveAutonomyKmL = 100.0f / l100_final;

        // =========================
        // BLOCO DEV B - Opções principais
        // =========================

        // Planejar viagem
        if (option == 1) {
            cout << "Distancia total da viagem (km): ";
            cin >> tripDistanceKm;

            float estimatedTimeH = tripDistanceKm / targetSpeedKmH;
            float fuelNeeded = tripDistanceKm / effectiveAutonomyKmL;
            float estimatedCost = fuelNeeded * fuelPrice;

            float usableRange = tankCapacityL * effectiveAutonomyKmL * (1 - safetyMarginPct / 100.0f);
            int stops = static_cast<int>(ceil(tripDistanceKm / usableRange)) - 1;
            if (stops < 0) stops = 0;

            cout << "\n--- PLANO DE VIAGEM ---\n";
            cout << "Tempo estimado: " << estimatedTimeH * 60 << " minutos\n";
            cout << "Combustivel necessario: " << fuelNeeded << " L\n";
            cout << "Custo estimado: R$ " << estimatedCost << "\n";
            cout << "Paradas previstas: " << stops << "\n";
        }

        // Dirigir trecho
        if (option == 2) {
            float sectionKm;
            cout << "Distancia percorrida (km): ";
            cin >> sectionKm;

            if (targetSpeedKmH > 120)
                cout << "Aviso: Velocidade acima de 120 km/h!\n";

            float fuelUsed = sectionKm / effectiveAutonomyKmL;

            if (fuelUsed > currentFuelL) {
                cout << "Erro: Combustivel insuficiente.\n";
            } else {
                currentFuelL -= fuelUsed;
                totalKm += sectionKm;

                // === NOVA LÓGICA ===
                kmSinceLastRefuel += sectionKm;  // Atualiza km desde último abastecimento
                tripTimeH += sectionKm / targetSpeedKmH; // Tempo total acumulado
                float speedMarker = targetSpeedKmH - referenceSpeedKmH;
                (void)speedMarker; // Apenas para marcar a diferença de velocidade média

                if (useTemperature) {
                    engineTempC += sectionKm * 0.02;
                    if (engineTempC > 100.0)
                        cout << "Alerta: Temperatura do motor acima de 100°C!\n";
                }

                cout << "\n--- TRECHO CONCLUIDO ---\n";
                cout << "Trecho: " << sectionKm << " km\n";
                cout << "Combustivel restante: " << currentFuelL << " L\n";
                cout << "Total rodado: " << totalKm << " km\n";
                cout << "Temperatura do motor: " << engineTempC << " °C\n";
            }
        }

        // =========================
        // BLOCO DEV C - Abastecimento, relatórios e status geral
        // =========================

        if (option == 3) {
            float fuelToAdd;
            float freeSpace = tankCapacityL - currentFuelL;
            cout << "Espaco disponivel: " << freeSpace << " L\nQuantos litros deseja abastecer? ";
            cin >> fuelToAdd;
            if (fuelToAdd > freeSpace) fuelToAdd = freeSpace;
            currentFuelL += fuelToAdd;
            float cost = fuelToAdd * fuelPrice;
            totalRefuelCost += cost;

            // === NOVA LÓGICA ===
            lastRefuelLiters = fuelToAdd;
            kmSinceLastRefuel = 0.0;

            cout << "Abastecido: " << fuelToAdd << " L | Custo: R$ " << cost << endl;
        }

        if (option == 6) {
            float percentage = currentFuelL / tankCapacityL * 100.0f;
            float currentRange = currentFuelL * effectiveAutonomyKmL;
            cout << "\n--- STATUS DO VEICULO ---\n";
            cout << "Velocidade: " << targetSpeedKmH << " km/h\n";
            cout << "Autonomia efetiva: " << effectiveAutonomyKmL << " km/L\n";
            cout << "Tanque: " << currentFuelL << " L (" << percentage << "%)\n";
            cout << "Alcance atual: " << currentRange << " km\n";
            cout << "KM total: " << totalKm << " km\n";
            cout << "Custo total abastecido: R$ " << totalRefuelCost << "\n";
            cout << "Temperatura do motor: " << engineTempC << " C\n";

            // === NOVOS DADOS ===
            cout << "Km desde ultimo abastecimento: " << kmSinceLastRefuel << " km\n";
            cout << "Ultimo abastecimento: " << lastRefuelLiters << " L\n";
            cout << "Tempo total de viagem: " << tripTimeH << " horas\n";
            cout << "Velocidade media de referencia: " << referenceSpeedKmH << " km/h\n";
        }

        if (option == 8) {
            cout << "\n=== RELATORIO COMPLETO ===\n";
            cout << "KM total: " << totalKm << " km\n";
            cout << "Combustivel atual: " << currentFuelL << " L de " << tankCapacityL << " L\n";
            cout << "Custo total abastecimento: R$ " << totalRefuelCost << "\n";
            cout << "Tipo de combustivel: ";
            if (fuelType == 1) cout << "Gasolina";
            else if (fuelType == 2) cout << "Etanol";
            else if (fuelType == 3) cout << "Diesel";
            else cout << "Desconhecido";
            cout << "\nPreco por litro: R$ " << fuelPrice << "\n";
            cout << "Velocidade alvo: " << targetSpeedKmH << " km/h (base: " << baseSpeed << " km/h)\n";
            if (useTemperature)
                cout << "Temperatura atual: " << engineTempC << " C\n";
            if (tripDistanceKm > 0)
                cout << "Distancia planejada: " << tripDistanceKm << " km\n";
            cout << "============================\n";
        }

        // =========================
        // BLOCO DEV D - Ajustes e recursos complementares
        // =========================

        if (option == 4) {
            cout << "Velocidade atual: " << targetSpeedKmH << " km/h\nNova velocidade: ";
            cin >> targetSpeedKmH;
            if (targetSpeedKmH <= 0) {
                targetSpeedKmH = baseSpeed;
                cout << "Velocidade redefinida para base: " << baseSpeed << " km/h\n";
            }
            if (targetSpeedKmH > 120)
                cout << "Alerta: Velocidade acima de 120 km/h!\n";
        }

        if (option == 5) {
            cout << "Temperatura atual: " << engineTempC << " C\nDeseja atualizar manualmente? (1=sim / 0=nao): ";
            int change;
            cin >> change;
            if (change == 1) {
                cout << "Nova temperatura: ";
                cin >> engineTempC;
                cout << (engineTempC > 100.0 ? "Alerta: Temperatura acima de 100°C!" : "Temperatura normal.") << endl;
            }
        }

        if (option == 7) {
            float totalDistance = 0.0;
            cout << "Distancia total da viagem (km): ";
            cin >> totalDistance;

            float maxRange = tankCapacityL * effectiveAutonomyKmL;
            float usableRange = maxRange * (1 - safetyMarginPct / 100.0);
            int stops = static_cast<int>(ceil(totalDistance / usableRange)) - 1;
            if (stops < 0) stops = 0;

            float interval = totalDistance / (stops + 1);

            cout << "\n--- PLANO DE PARADAS ---\n";
            cout << "Alcance maximo: " << maxRange << " km\n";
            cout << "Alcance util (com margem de " << safetyMarginPct << "%): " << usableRange << " km\n";
            cout << "Paradas recomendadas: " << stops << "\n";
            if (stops > 0)
                cout << "Intervalo medio entre paradas: " << interval << " km\n";
            else
                cout << "Nenhuma parada necessaria para esta viagem.\n";
        }
    }

    return 0;
}
