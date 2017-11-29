
#include "netxpto.h"
#include "binary_source.h"
#include "clock.h"
#include "alice_qkd.h"
#include "single_photon_source.h"
#include "polarizer.h"
#include "sink.h"

int main()
{
	// #####################################################################################################
	// ################################# System Input Parameters #########################################
	// #####################################################################################################

	double RateOfPhotons{ 1e3 };

	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	// Alice Implementation
	Binary NUM_A{ "NUM_A.sgn" };
	Binary MI_A{ "MI_A.sgn" };
	ElectricalSignal CLK_A{ "CLK_A.sgn" };
	ElectricalSignal S_A1{ "S_A1.sgn" };
	PhotonStream S_A3{ "S_A3.sgn" };
	PhotonStream Q_C_1{ "Q_C_1.sgn" };
	ElectricalSignal S_A2{ "S_A2.sgn" };
	Messages C_C_1{ "C_C_1.sgn" };
	Messages C_C_6{ "C_C_1.sgn" };
	Binary Data_A{ "Data_A.sgn" };

	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ##################################
	// #####################################################################################################

	BinarySource B1{ vector <Signal*> {}, vector <Signal*> {&NUM_A} };
	B1.setMode( PseudoRandom );

	Clock B2{ vector <Signal*> {}, vector <Signal*> {&CLK_A} };

	alice_qkd B3{ vector <Signal*> {&CLK_A, &NUM_A, &C_C_6}, vector <Signal*> {&S_A1, &S_A2, &C_C_1, &MI_A} };
	
	SinglePhotonSource B4{ vector <Signal*> {&S_A1}, vector <Signal*> {&S_A3} };
	
	polarizer B5{ vector <Signal*> {&S_A3, &S_A2}, vector <Signal*> {&Q_C_1} };

	Sink B6{ vector <Signal*> {&Q_C_1}, vector <Signal*> {} };

	// ####################################################################################################
	// ########################### System Declaration and Inicialization ##################################
	// #####################################################################################################

	System MainSystem{ vector <Block*> {} };

	// ####################################################################################################
	// ########################### Run ##################################
	// #####################################################################################################

	MainSystem.run();


    return 0;
}

