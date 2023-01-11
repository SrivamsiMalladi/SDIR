// VREP-SDIR.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>
#include <cstdio>
#include <sstream>

class MBuf : public std::stringbuf {
public:
	int sync() {
		fputs(str().c_str(), stdout);
		str("");
		return 0;
	}
};

extern "C" {
#include "../../src/ctrl/com/remoteApi/extApi.h"
}

using namespace std;

simxInt *jh = new simxInt[7];

simxInt Initial()
{
	string Joint;
	simxInt *check = new simxInt[1];
	int portNb = 19997;
	simxInt clientID = -1;
	simxFinish(-1);

	clientID = simxStart("127.0.0.1", portNb, true, true, 5000, 5);

	if (clientID > -1)
	{
		//Starten der Simulation
		simxStartSimulation(clientID, simx_opmode_oneshot);
		printf("Simulation started");

		for (int i = 0; i < 6; i++)
		{
			//Abfrage der einzelnen Joint Handles des Manipulators
			Joint = "KR120_2700_2_joint" + to_string(i + 1);
			const char* c = Joint.c_str();
			simxGetObjectHandle(clientID, (const simxChar *)c, check, simx_opmode_oneshot_wait);
			jh[i] = check[0];
		}
	}
	else
	{
		printf("Connection Fail");
		getchar();
		extApi_sleepMs(10);
	}

	return clientID;
}

int main()
{
	simxInt ID = Initial();
	simxUChar* value = new simxUChar;
	simxInt length = -1;
	unsigned char out[100];

	SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IONBF, 0);
	MBuf buf;
	
	simxInt test = simxGetStringSignal(ID, "mvsignal", &value, &length, simx_opmode_streaming);
	int cnt = 0;
	while (simxGetConnectionId(ID) != -1 || cnt < 100) {
		/*if (getchar()) {
			simxStopSimulation(ID, simx_opmode_oneshot);
			break;
		}*/
		simxInt test = simxGetStringSignal(ID, "mvsignal", &value, &length, simx_opmode_buffer);
		for (int i = 0; i++; i < length) {
			out[i] = value[i];
		}
		string t(reinterpret_cast<char*>(out));
		std::cout.rdbuf(&buf);
		std::cout << t << std::flush;
		cnt++;
	}
	simxFinish(ID);
}

// Programm ausführen: STRG+F5 oder "Debuggen" > Menü "Ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
