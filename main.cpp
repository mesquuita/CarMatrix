#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// =========================
// BLOCO DEV A - Initialization and configuration
// =========================

int main() {
    cout << "=== ONBOARD COMPUTER ===" << endl;

    // Initial flags and settings
    int useTemperature = 1;      // 1 = yes / 0 = no
    int useBluetoothSim = 0;     // Bluetooth simulation
    float baseSpeed = 80.0;      // km/h
    float incrementL100 = 0.5;   // L/100km for every +5 km/h above base
    float safetyMarginPct = 15.0; // %

    // Bluetooth simulation
    cout << "Connect via Bluetooth? (1=yes / 0=no): ";
    cin >> useBluetoothSim;
    cout << (useBluetoothSim ? "Bluetooth connected successfully." : "Bluetooth not connected.") << endl;

    // Vehicle data
    float tankCapacityL = 0.0, baseAutonomyKmL = 0.0;
    cout << "Tank capacity (liters): ";
    cin >> tankCapacityL;
    cout << "Average base autonomy (km/L): ";
    cin >> baseAutonomyKmL;

    // Fuel type and price
    int fuelType = 0;
    float fuelPrice = 0.0;
    cout << "Fuel type (1=gasoline, 2=ethanol, 3=diesel): ";
    cin >> fuelType;
    cout << "Fuel price (R$/L): ";
    cin >> fuelPrice;

    // Current fuel level
    int readMode = 0;
    float currentFuelL = 0.0;
    cout << "Fuel reading mode (1=liters / 2=percentage): ";
    cin >> readMode;

    if (readMode == 1) {
        cout << "Enter current fuel amount (L): ";
        cin >> currentFuelL;
    } else {
        float percentage = 0.0;
        cout << "Enter current tank percentage (0 to 100%): ";
        cin >> percentage;
        currentFuelL = (percentage / 100.0f) * tankCapacityL;
    }

    if (currentFuelL > tankCapacityL) currentFuelL = tankCapacityL;

    // Initialize main variables
    float totalKm = 0.0;
    float totalRefuelCost = 0.0;

    // Target average speed
    float targetSpeedKmH = 0.0;
    cout << "Enter target average speed (km/h): ";
    cin >> targetSpeedKmH;
    if (targetSpeedKmH <= 0) targetSpeedKmH = baseSpeed;

    // Engine temperature
    float engineTempC = 90.0;

    // Initial help message
    cout << "Press 9 in the main menu for help during system use." << endl;


    // =========================
    // BLOCO DEV B - Menu control and driving logic
    // =========================

    int option = -1;
    cout << fixed << setprecision(2);

    while (option != 0) {
        cout << "\n=== MAIN MENU ===\n";
        cout << "1 - Trip planning\n2 - Drive section\n9 - Help\n0 - Exit\nChoose an option: ";
        cin >> option;

        // Help menu
        if (option == 9) {
            cout << "\n--- HELP ---\n";
            cout << "Use this system to plan trips, drive sections, refuel, and monitor the vehicle.\n";
            cout << "Each option updates the onboard computer data.\n";
            continue;
        }

        // Exit
        if (option == 0) {
            cout << "\nExiting system...\n";
            break;
        }

        // Consumption rules
        float l100_base = 100.0f / baseAutonomyKmL;
        float speedExcess = targetSpeedKmH - baseSpeed;
        if (speedExcess < 0) speedExcess = 0;
        int speedBlocks = static_cast<int>(speedExcess / 5);
        float l100_extra = speedBlocks * incrementL100;
        float l100_final = l100_base + l100_extra;
        float effectiveAutonomyKmL = 100.0f / l100_final;

        // Option 1 - Trip planning
        if (option == 1) {
            float tripDistanceKm;
            cout << "Total trip distance (km): ";
            cin >> tripDistanceKm;

            float estimatedTimeH = tripDistanceKm / targetSpeedKmH;
            float fuelNeeded = tripDistanceKm / effectiveAutonomyKmL;
            float estimatedCost = fuelNeeded * fuelPrice;

            float usableRange = tankCapacityL * effectiveAutonomyKmL * (1 - safetyMarginPct / 100.0f);
            int stops = static_cast<int>(ceil(tripDistanceKm / usableRange)) - 1;
            if (stops < 0) stops = 0;

            cout << "\n--- TRIP PLAN ---\n";
            cout << "Estimated time: " << estimatedTimeH * 60 << " minutes\n";
            cout << "Fuel required: " << fuelNeeded << " L\n";
            cout << "Estimated cost: R$ " << estimatedCost << "\n";
            cout << "Expected stops: " << stops << "\n";
        }

        // Option 2 - Drive section
        if (option == 2) {
            float sectionKm;
            cout << "Distance driven (km): ";
            cin >> sectionKm;

            if (targetSpeedKmH > 120)
                cout << "Warning: Speed above 120 km/h!\n";

            float fuelUsed = sectionKm / effectiveAutonomyKmL;

            if (fuelUsed > currentFuelL) {
                cout << "Error: Not enough fuel.\n";
            } else {
                currentFuelL -= fuelUsed;
                totalKm += sectionKm;

                if (useTemperature) {
                    engineTempC += sectionKm * 0.02;
                    if (engineTempC > 100.0)
                        cout << "Warning: Engine temperature above 100°C!\n";
                }

                cout << "\n--- SECTION COMPLETE ---\n";
                cout << "Section: " << sectionKm << " km\n";
                cout << "Remaining fuel: " << currentFuelL << " L\n";
                cout << "Total KM: " << totalKm << " km\n";
                cout << "Engine temperature: " << engineTempC << " °C\n";
            }
        }
    }

    // =========================
    // END OF BLOCK DEV B
    // =========================


    // =========================
    // BLOCK DEV C - Refueling, reports, and general status
    // =========================
    //
    // Option 3 (Refuel):
    //   - Calculate free space in the tank
    //   - Ask how many liters to refuel
    //   - Update currentFuelL and totalRefuelCost
    //   - Show refueling summary
    //
    // Option 6 (Show status):
    //   - Calculate L/100km and current autonomy
    //   - Calculate current range and tank percentage
    //   - Display:
    //       speed, autonomy, tank, totalKm, cost, and temperature
    //
    // Option 8 (Full report):
    //   - Display consolidated summary:
    //       Total KM driven
    //       Current and total tank capacity
    //       Total refueling cost
    //       Fuel type and price
    //       Target and base speed
    //       Temperature (if active)
    //       Planned distance (if available)
    //
    // =========================
    // END OF BLOCK DEV C
    // =========================


    // =========================
    // BLOCK DEV D - Adjustments and complementary features
    // =========================
    //
    // Option 4 (Adjust speed):
    //   - Display current speed
    //   - Ask for new speed
    //   - If <= 0 → reset to base (80 km/h)
    //   - If > 120 → warning
    //   - Save new value for future consumption calculations
    //
    // Option 5 (Engine temperature):
    //   - Display current temperature
    //   - Ask if user wants to update manually
    //   - If yes → ask for new value
    //   - If > 100°C → warning
    //   - Else → display "normal"
    //
    // Option 7 (Program stops):
    //   - Ask total trip distance
    //   - Calculate max and usable range (with safety margin)
    //   - Compute necessary stops = ceil(distance / usableRange) - 1
    //   - Show recommended number and interval of stops
    //
    // After completing all operations, user can return to the menu
    // until selecting “0” to end the program.
    //
    // =========================
    // END OF BLOCK DEV D
    // =========================

    return 0;
}
