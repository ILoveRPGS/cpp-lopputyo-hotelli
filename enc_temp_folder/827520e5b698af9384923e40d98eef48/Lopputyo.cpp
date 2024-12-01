#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <windows.h>

using namespace std;


//Luodaan huoneelle Varaus Cl��ssi

class Huone{
	public:
		string varausNimi;
		int varausNumero=0;
		int huoneNumero;
		int huoneHinta;
		int vietetytYot = 0;
		bool varattu = false;
		int huoneenKoko;

};
vector<Huone> varaaHuone(vector<Huone> huoneet, int valittuHuone, string varaajanNimi);
bool haeVarausNumerolla(vector<Huone> huoneet);
bool haeVarausNimella(vector<Huone> huoneet);
bool tarkistaSyoteYN(string syote);
vector<Huone> luodaanHuoneet(int huoneetMaara) {

	vector<Huone> huoneet;

	for (int i = 0; i < huoneetMaara; i++) {
		Huone huone;
		huone.huoneNumero = i + 1;
		if (i > huoneetMaara / 2) {
			huone.huoneenKoko = 2;
			huone.huoneHinta = 150;
		}
		else {
			huone.huoneenKoko = 1;
			huone.huoneHinta = 100;
		}
		huoneet.push_back(huone);
	}
	return huoneet;
}

void tulostaHuone(Huone huone) {
	string varattuTekstiTemp;
	if (huone.varattu == false) {
		varattuTekstiTemp = "Ei ole varattu";
	}
	else {
		varattuTekstiTemp = "On Varattu";
	}
	cout << "Huoneen tiedot" << endl;
	cout << "--------------" << endl;
	if (huone.varausNumero) {
		cout << "Huoneen varausnumero: " << huone.varausNumero << endl;
	}
	if (huone.varausNimi != "") {
		cout << "Huoneen varaajan nimi: " << huone.varausNimi << endl;
	}
	cout << "Huoneen numero: " << huone.huoneNumero << endl;
	cout << "Huoneen koko: " << huone.huoneenKoko << endl;
	cout << "Huoneen hinta: " << huone.huoneHinta << "e" << endl;
	cout << "Huoneen yot varattu: " << huone.vietetytYot  << endl;
	cout << "Huone varauksen tila: " << varattuTekstiTemp << "." << endl;
}

vector<Huone> varausHuone(vector<Huone> huoneet, int huoneetMaara) {
		bool jatkoTemp = true;
		string nimiTemp;
		cout << "Tervetuloa tekemaan huone varausta syotathan nimesi niin paasemme aloittamaan:";
		cin >> nimiTemp;
		int puoletHuoneMaaraTemp;
		int valittuHuone;
		puoletHuoneMaaraTemp = huoneetMaara / 2;
		string varmistusTemp;
		string varmistuTemp2;

		while (jatkoTemp) {
		cout << "Mink� huoneen haluaisit varata?" << endl;
		cout << "Huone numerosta 1 - " << puoletHuoneMaaraTemp << " asti ovat yhden hengen huoneita" << endl;
		cout << "Kun taas numerosta " << puoletHuoneMaaraTemp + 1 << " - " << huoneetMaara << " asti ovat kahden hengen huoneita?" << endl;
		cin >> valittuHuone;
		if (huoneet[valittuHuone - 1].varattu == false) {
			tulostaHuone(huoneet[valittuHuone - 1]);
			cout << "Varataanko huone? (y,n)" << endl;
			cin >> varmistusTemp;
			if (varmistusTemp == "y") {
				huoneet = varaaHuone(huoneet, valittuHuone, nimiTemp);
				cout << "Jatketaanko? (y, n)" << endl;
				cin >> varmistuTemp2;
				jatkoTemp = tarkistaSyoteYN(varmistuTemp2);
			}
			if (varmistusTemp == "n") {
				
			}
		}
		else {
			cout << "Huone on valitettavasti varattu" << endl;
		}
	}
		return huoneet;

}
bool Exit(bool jatko) {
	jatko = false;
	EXIT_SUCCESS;
	return jatko;
}
bool tarkistaSyoteYN(string syote) {
	while (true) {
		if (syote == "y") {
			return true;
		}
		if (syote == "n") {
			return false;
		}
		else {
			cout << "V��r� sy�te." << endl;
		}
	}
}
vector<Huone> varaaHuone(vector<Huone> huoneet, int valittuHuone, string varaajanNimi) {
	string varmistusTemp;
	bool jatkoTemp =true;
	bool virhe;
	int yot;
	int varausNumero = rand() % 10000 + 99999;
	huoneet[valittuHuone - 1].varausNumero = varausNumero;
	huoneet[valittuHuone - 1].varausNimi = varaajanNimi;
	do {
		virhe = false;
		cout << "Monta y�t� aiotte y�py� kyseisess� huoneessa? Yhden y�n hinta on " << huoneet[valittuHuone - 1].huoneHinta << "e" << endl;
		cin >> yot;
		if (cin.fail()) {
			cout << "Virhe. Sy�t� uusi luku" << endl;
			virhe = true;
			cin.clear();
			cin.ignore(80, '\n');
		} 
	} while (virhe);
	huoneet[valittuHuone - 1].vietetytYot = yot;
	cout << "Annetaan satunnainen alennus..." << endl;
	Sleep(1000);
	int alennus = rand() % 1 + 3;
	float alennusHinta;
	if (alennus == 1) {
		alennusHinta = 1;
	}
	if (alennus == 2) {
		alennusHinta = 0.9;
	}
	if (alennus == 3) {
		alennusHinta = 0.8;
	}
	cout << "Huoneenne n�ytt�� t�lt�:" << endl << "--------------------------------------" << endl << endl;
	tulostaHuone(huoneet[valittuHuone - 1]);
	cout << "Huoneenne lopulliseksi hinnaksi tuli: " << huoneet[valittuHuone - 1].huoneHinta * yot * alennusHinta << "e" << endl;
	cout << endl << "Varataan.... Odotathan.";
	Sleep(2500);
	huoneet[valittuHuone-1].varattu = true;
	cout << "Varaus onnistui!" << endl;
	return huoneet;
}

bool etsiTiedoilla(vector<Huone> huoneet) {
	string syote;
	bool jatko = true;
	while (jatko) {
		cout << "Etsit��nk� varausta varausnumerolla vai varausnimell�? (u, n, exit)" << endl;
		cin >> syote;
		if (syote == "u") {
			jatko = haeVarausNumerolla(huoneet);
		}
		else if (syote == "n") {
			jatko = haeVarausNimella(huoneet);
		}
		else if (syote == "exit") {
			jatko = false;
		}
		else {
			cout << "V��r� sy�te";
		}
	}
	return true;
}
bool haeVarausNumerolla(vector<Huone> huoneet) {
	bool jatko = true;
	string syote;
	while (jatko) {
		bool loytyi = false;
		int varausNumeroTemp;
		cout << "Anna varausnumero: ";
		cin >> varausNumeroTemp;
		for (int i = 0; i < huoneet.size(); i++) {
			if (huoneet[i].varausNumero == varausNumeroTemp) {
				cout << "Huone l�ytyi!" << endl;
				tulostaHuone(huoneet[i]);
				loytyi = true;
				break;
			}
		}
		if (!loytyi) {
			cout << "Huoneita ei l�ytynyt t�ll� numerolla" << endl;
		}

		cout << "Etsit��nk� huonetta toisella varausnumerolla? (y, n)" << endl;
		cin >> syote;
		bool tarkistus = tarkistaSyoteYN(syote);
		if (!tarkistus) {
			jatko = false;
		}
		if (tarkistus) {
			jatko = true;
		}
	}
	return true;
}
bool haeVarausNimella(vector<Huone> huoneet) {
	bool jatko = true;
	string syote;
	while (jatko) {
		bool loytyi = false;
		string varausNimiTemp;
		cout << "Anna varausnimi: ";
		cin >> varausNimiTemp;
		for (int i = 0; i < huoneet.size(); i++) {
			if (huoneet[i].varausNimi == varausNimiTemp) {
				cout << "Huone l�ytyi!" << endl;
				tulostaHuone(huoneet[i]);
				loytyi = true;
				break;
			}
		}
		if (!loytyi) {
			cout << "Huoneita ei l�ytynyt t�ll� nimell�" << endl;
		}

		cout << "Etsit��nk� huonetta toisella nimell�? (y, n)" << endl;
		cin >> syote;
		bool tarkistus = tarkistaSyoteYN(syote);
		if (!tarkistus) {
			jatko = false;
		}
		if (tarkistus) {
			jatko = true;
		}
	}
	return true;
}


int main() {
	bool jatko = true;
	setlocale(LC_ALL, "FI_fi");
	srand(time(NULL));
	int huoneetMaara = rand() % 300 + 40;
	vector<Huone> huoneet = luodaanHuoneet(huoneetMaara);
	string syote;

	while (jatko) {
		string vastaus;
		cout << " Tervetuloa hotellin huonevaraus j�rjestelm��n!" << endl;
		cout << "Mit� haluaisit tehd�? Etsi, Varaa? (e,v, exit)"<<endl;
		cin >> vastaus;
		if (vastaus == "e") {
			etsiTiedoilla(huoneet);
		}
		else if (vastaus == "v") {
			huoneet = varausHuone(huoneet, huoneetMaara);
		}
		else if (vastaus == "exit") {
			jatko = Exit(jatko);
		}
		else {
			cout << "Vaara syote" << endl;
			continue;
		}
	}
	return 0;

}