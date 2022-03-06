#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string>
#include <vector>
#include <windows.h>  
#include <chrono>   
#include <sstream>  
#include <filesystem>
#include <algorithm> 
#pragma comment(lib, "urlmon.lib")
#include <direct.h>
#include <cstdlib>
using namespace std;

namespace Extern_Reader
{
	namespace Conversoes
	{
		namespace INT
		{
			float paraFLOAT(int A)
			{
				return (float)A;
			}

			std::string paraString(int A)
			{
				return to_string(A);
			}
		}
		namespace FLOAT
		{
			int paraINT(float A)
			{
				return (int)A;
			}

			std::string paraString(float A)
			{
				return to_string(A);
			}
		}
		namespace STRING
		{
			int paraINT(std::string A)
			{
				return atoi(A.c_str());
			}

			float paraFLOAT(std::string A)
			{
				return stof(A);
			}
		}
	}
	namespace LOG
	{
		std::string arquivoTXT;
		std::string HoraAtual()
		{
			struct tm current_tm;
			char chLogBuff[5000];
			char chParameters[5000];
			time_t current_time = time(NULL);
			localtime_s(&current_tm, &current_time);
			char szTimestamp[30];
			sprintf_s(szTimestamp, "[%02d:%02d:%02d] = ", current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec);
			return szTimestamp;
		}
		void Log_ERRO(string texto)
		{
			ofstream Arquivo;
			Arquivo.open(arquivoTXT, std::ios_base::app);
			std::string a = HoraAtual() + "ERRO: " + texto;
			Arquivo << a << endl;
			Arquivo.close();
		}
		void Log(string texto)
		{
			ofstream Arquivo;
			Arquivo.open(arquivoTXT, std::ios_base::app);
			std::string a = HoraAtual() + texto;
			Arquivo << a << endl;
			Arquivo.close();
		}
		void LogSemHora(string texto)
		{
			ofstream Arquivo;
			Arquivo.open(arquivoTXT, std::ios_base::app);
			Arquivo << texto << endl;
			Arquivo.close();
		}
		void ReiniciarLog()
		{
			ofstream Arquivo;
			Arquivo.open(arquivoTXT);
			Arquivo << "";
			Arquivo.close();
		}
	};
	namespace StringManager
	{
		bool SeContemTexto(std::string string, std::string textoProcurado)
		{
			if (string.find(textoProcurado) != std::string::npos)
				return true;
			else
				return false;
		}
		std::string SubstituirCaractere(std::string palavra, char letraantiga, char letranova)
		{
			std::string base = palavra;
			std::string str = base;
			str.replace(str.begin(), str.end(), letraantiga, letranova);
			return str;
		}
		std::string SubstituirPalavra(std::string str, const std::string& from, const std::string& to) {
			size_t start_pos = 0;
			while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
				str.replace(start_pos, from.length(), to);
				start_pos += to.length();
			}
			return str;
		}
		std::string RemoverEspacos(std::string str, const std::string& from = " ", const std::string& to = "") {
			size_t start_pos = 0;
			while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
				str.replace(start_pos, from.length(), to);
				start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
			}
			return str;
		}
	}
	namespace Arquivos
	{
		bool ArquivoExiste(std::string name)
		{
			ifstream file(name);
			if (!file)
				return false;
			else
				return true;
		}
		void DeletarArquivo(string pathFile)
		{
			remove(pathFile.c_str());
		}
		void CriarArquivo(std::string FilePathAndExtension)
		{
			std::ofstream outfile(FilePathAndExtension);
			outfile.close();
		}
		void LimparArquivo(string arquivoTXT)
		{
			ofstream Arquivo;
			Arquivo.open(arquivoTXT);
			Arquivo << "";
			Arquivo.close();
		}
		void CriarDiretorio(const char* Diretorio)
		{
			_mkdir(Diretorio);
		}
	};
	namespace ArquivoTXT
	{
		std::string TXTFilePath;
		int TamanhoDoVector(std::vector<string> vetor)
		{
			return vetor.size() - 1;
		}

		namespace String
		{
			void LimparPilha(std::vector<std::string> vetor)
			{
				vetor.clear();
			}

			std::vector<std::string> PegarValores()
			{
				std::vector<std::string> TempVECTOR;
				ifstream imput(TXTFilePath);
				string textolido;
				for (string line; getline(imput, line);)
					TempVECTOR.push_back(line);
				return TempVECTOR;
			}
			std::vector<string> PegarMaisValores(char separador)
			{
				std::vector<string> TempVECTOR;
				vector<string> tokens;
				ifstream imput(TXTFilePath);
				for (string line; getline(imput, line);)
				{
					istringstream tokenizer{ line };
					string token;
					while (getline(tokenizer, token, separador))
					{
						tokens.push_back(token);
					}
				}
				return tokens;
				/*
				* Exemplo de 2 valores::
				for (int i = 0; i <= Extern_Reader::ArquivoTXT::TamanhoDoVector(Extern_Reader::ArquivoTXT::String::PegarMaisValores("Teste.txt")); i++)
				{
					cout << "AddOption(" << Extern_Reader::ArquivoTXT::String::PegarMaisValores("Teste.txt")[i] << "," << Extern_Reader::ArquivoTXT::String::PegarMaisValores("Teste.txt")[i + 1] << ");" << endl;
					i++;
				}
				Exemplo de 2 valores, separados por virgula:
				Extern_Reader::ArquivoTXT::TXTFilePath = ".\\T.txt";
				std::vector<string> A = Extern_Reader::ArquivoTXT::String::PegarMaisValores(',');
				for (int i = 0; i <= Extern_Reader::ArquivoTXT::TamanhoDoVector(A); i++)
				{
					cout << "AddOption(" << A[i] << "," << A[i + 1] << ");" << endl;
					i++;
				}
				* Exemplo de 3 valores::
				for (int i = 0; i <= Extern_Reader::ArquivoTXT::TamanhoDoVector(Extern_Reader::ArquivoTXT::String::PegarMaisValores("Teste.txt")); i++)
				{
					if (i <= (Extern_Reader::ArquivoTXT::TamanhoDoVector(Extern_Reader::ArquivoTXT::String::PegarMaisValores("Teste.txt")) + 3))
					{
						cout << "AddOption(" << Extern_Reader::ArquivoTXT::String::PegarMaisValores("Teste.txt")[i] << ", " << Extern_Reader::ArquivoTXT::String::PegarMaisValores("Teste.txt")[i + 1] << ", " << Extern_Reader::ArquivoTXT::String::PegarMaisValores("Teste.txt")[i + 2] << ");" << endl;
						i++;
						i++;
					}
				}
				*/
			}
		}
		namespace Int
		{
			void LimparPilha(std::vector<int> vetor)
			{
				vetor.clear();
			}
			std::vector<int> PegarValores()
			{
				std::vector<int> TempVECTOR;
				ifstream imput(TXTFilePath);
				string textolido;
				for (string line; getline(imput, line);)
					TempVECTOR.push_back(stoi(line));
				return TempVECTOR;
			}
		}
		namespace Float
		{
			void LimparPilha(std::vector<float> vetor)
			{
				vetor.clear();
			}
			std::vector<float> PegarValores()
			{
				std::vector<float> TempVECTOR;
				ifstream imput(TXTFilePath);
				string textolido;
				for (string line; getline(imput, line);)
					TempVECTOR.push_back(stof(line));
				return TempVECTOR;
			}
		}
	};
	namespace INIFile
	{
		std::string INIFilePath;//Exemplo no mesmo diretorio do EXE:   .\\ArquivoINI.ini
		namespace String
		{
			void GravarString(std::string string, std::string app, std::string key)
			{
				WritePrivateProfileStringA(app.c_str(), key.c_str(), string.c_str(), INIFilePath.c_str());
			}
			std::string LerString(std::string app, std::string key)
			{
				char buf[100];
				GetPrivateProfileStringA(app.c_str(), key.c_str(), "NULL", buf, 100, INIFilePath.c_str());
				return (std::string)buf;
			}
		}
		namespace Int
		{
			void GravarInt(int value, std::string app, std::string key)
			{
				String::GravarString(std::to_string(value), app, key);
			}
			int LerInt(std::string app, std::string key)
			{
				return std::stoi(String::LerString(app, key));
			}
		}
		namespace Float
		{
			void GravarFloat(float value, std::string app, std::string key)
			{
				String::GravarString(std::to_string(value), app, key);
			}
			float LerFloat(std::string app, std::string key)
			{
				return std::stof(String::LerString(app, key));
			}
		}
	}
	namespace WEB
	{
		void BaixarArquivo(std::string URL, std::string DiretorioENomeDoArquivo)
		{
			if (Extern_Reader::Arquivos::ArquivoExiste(DiretorioENomeDoArquivo) == false)
			{
				string str = URL;
				std::wstring widestr = std::wstring(str.begin(), str.end());
				const wchar_t* widecstr = widestr.c_str();
				string str2 = DiretorioENomeDoArquivo;
				std::wstring widestr2 = std::wstring(str2.begin(), str2.end());
				const wchar_t* widecstr2 = widestr2.c_str();
				URLDownloadToFile(NULL, widecstr, widecstr2, 0, NULL);
			}
		}


		std::vector<std::string> Obter_IP_Info()
		{
			/*
			Como Usar:
			int tamanho = Extern_Reader::ArquivoTXT::TamanhoDoVector(Extern_Reader::WEB::Obter_IP_Info());
			for (int i = 0; i <= tamanho; i++)
			{
				cout << Extern_Reader::WEB::Obter_IP_Info()[i] << endl;
				i++;
			}


			exemplo 2:
			std::vector<std::string> IP = Extern_Reader::WEB::Obter_IP_Info();
			cout << "ip" << IP[2] << endl;
			cout << "version" << IP[4] << endl;
			cout << "city" << IP[6] << endl;
			cout << "region" << IP[8] << endl;
			cout << "region_code" << IP[10] << endl;
			cout << "country" << IP[12] << endl;
			cout << "country_name" << IP[14] << endl;
			cout << "country_code" << IP[16] << endl;
			cout << "country_code_iso3" << IP[18] << endl;
			cout << "country_capital" << IP[20] << endl;
			cout << "country_tld" << IP[22] << endl;
			cout << "continent_code" << IP[24] << endl;
			cout << "in_eu" << IP[26] << endl;
			cout << "postal" << IP[28] << endl;
			cout << "latitude" << IP[30] << endl;
			cout << "longitude" << IP[32] << endl;
			cout << "timezone" << IP[34] << endl;
			cout << "utc_offset" << IP[36] << endl;
			cout << "country_calling_code" << IP[38] << endl;
			cout << "currency" << IP[40] << endl;
			cout << "currency_name" << IP[42] << endl;
			cout << "languages" << IP[44] << endl;
			cout << "country_area" << IP[46] << endl;
			cout << "country_population" << IP[48] << endl;
			cout << "asn" << IP[50] << endl;
			cout << "org" << IP[52] << endl;
			*/
		inicio:
			if (Extern_Reader::Arquivos::ArquivoExiste("IP.txt"))
			{
				std::vector<string> TempVECTOR;
				vector<string> tokens;
				ifstream imput("IP.txt");
				for (string line; getline(imput, line);)
				{
					istringstream tokenizer{ line };
					string token;
					while (getline(tokenizer, token, ':'))
					{
						if (Extern_Reader::StringManager::SeContemTexto(token, ","))
						{
							tokens.push_back(Extern_Reader::StringManager::SubstituirPalavra(token, ",", ""));
						}
						else if (Extern_Reader::StringManager::SeContemTexto(token, "}"))
						{
							tokens.push_back(Extern_Reader::StringManager::SubstituirPalavra(token, "}", ""));
						}
						else if (Extern_Reader::StringManager::SeContemTexto(token, "{"))
						{
							tokens.push_back(Extern_Reader::StringManager::SubstituirPalavra(token, "{", ""));
						}
						else if (Extern_Reader::StringManager::SeContemTexto(token, "   "))
						{
							tokens.push_back(Extern_Reader::StringManager::SubstituirPalavra(token, "   ", ""));
						}
						else
							tokens.push_back(token);
					}
				}
				return tokens;
			}
			else
			{
				Extern_Reader::WEB::BaixarArquivo("https://ipapi.co/json", "IP.txt");
				goto inicio;
			}
		}
	}
	namespace Mouse_e_Tela
	{
		void MoverMouse(int x, int y)
		{
			SetCursorPos(x, y);
		}
		int Tela_X()
		{
			return GetSystemMetrics(SM_CXSCREEN);
		}
		int Tela_Y()
		{
			return GetSystemMetrics(SM_CYSCREEN);
		}
		void MouseLouco()
		{
			int count = 800;
			int movex, movey;
			float angle = 0.0f;
			SetCursorPos(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);
			for (int i = 0; i <= count; i++) {
				angle = .3 * i;
				movex = (angle * cos(angle) * 2) + GetSystemMetrics(SM_CXSCREEN) / static_cast<float>(2);
				movey = (angle * sin(angle) * 2) + GetSystemMetrics(SM_CYSCREEN) / 2;
				SetCursorPos(movex, movey);
				Sleep(1);
			}
		}
	}
	namespace JSON
	{
		std::string JSONFilePath;

		int TamanhoDoVector(std::vector<string> vetor)
		{
			return vetor.size() - 1;
		}

		namespace String
		{
			std::vector<std::string> BuscarKey(std::string Sessao)
			{
				/*
				Exemplo:

				Extern_Reader::JSON::JSONFilePath = ".\\Jason.txt";
				for (int i = 0; i <= Extern_Reader::JSON::TamanhoDoVector(Extern_Reader::JSON::String::BuscarKey("squadName")); i++)
				{
					if(Extern_Reader::JSON::String::BuscarKey("squadName")[i] == ""){}
					else
						cout << Extern_Reader::JSON::String::BuscarKey("squadName")[i] << endl;
				}


			*/
				std::vector<std::string> TempVECTOR;
				ifstream imput(JSONFilePath);
				for (string line; getline(imput, line);)
				{
					string B = "\"" + Sessao + "\":";

					if (line.find(B) != std::string::npos)
					{
						string A = Extern_Reader::StringManager::SubstituirPalavra(line, B, "");
						string C = Extern_Reader::StringManager::SubstituirPalavra(A, "\"", "");
						string D = Extern_Reader::StringManager::SubstituirPalavra(C, "    ", "");
						string E = Extern_Reader::StringManager::SubstituirPalavra(D, ",", "");
						string F = Extern_Reader::StringManager::SubstituirPalavra(E, "   ", "");
						string G = Extern_Reader::StringManager::SubstituirPalavra(F, "  ", "");
						TempVECTOR.push_back(G);
					}
				}
				return TempVECTOR;
			}

		}

		namespace Int
		{
			std::vector<int> BuscarKey_INT(std::string Sessao)
			{
				/*
				Exemplo:

				Extern_Reader::JSON::JSONFilePath = ".\\Jason.txt";
				for (int i = 0; i <= Extern_Reader::JSON::TamanhoDoVector(Extern_Reader::JSON::String::BuscarKey("formed")); i++)
				{
					cout << Extern_Reader::JSON::Int::BuscarKey_INT("formed")[i] << endl;
				}
			*/
				std::vector<int> TempVECTOR;
				ifstream imput(JSONFilePath);
				for (string line; getline(imput, line);)
				{
					string B = "\"" + Sessao + "\":";

					if (line.find(B) != std::string::npos)
					{
						string A = Extern_Reader::StringManager::SubstituirPalavra(line, B, "");
						string C = Extern_Reader::StringManager::SubstituirPalavra(A, "\"", "");
						string D = Extern_Reader::StringManager::SubstituirPalavra(C, "    ", "");
						string E = Extern_Reader::StringManager::SubstituirPalavra(D, ",", "");
						string F = Extern_Reader::StringManager::SubstituirPalavra(E, "   ", "");
						string G = Extern_Reader::StringManager::SubstituirPalavra(F, "  ", "");
						int final = atoi(G.c_str());
						TempVECTOR.push_back(final);
					}
				}
				return TempVECTOR;
			}
		}

		namespace Float
		{
			std::vector<float> BuscarKey_Float(std::string Sessao)
			{
				/*
				Exemplo:

				Extern_Reader::JSON::JSONFilePath = ".\\Jason.txt";
				for (int i = 0; i <= Extern_Reader::JSON::TamanhoDoVector(Extern_Reader::JSON::String::BuscarKey("secretBase")); i++)
				{
						cout << Extern_Reader::JSON::Float::BuscarKey_Float("secretBase")[i] << endl;
				}
			*/
				std::vector<float> TempVECTOR;
				ifstream imput(JSONFilePath);
				for (string line; getline(imput, line);)
				{
					string B = "\"" + Sessao + "\":";

					if (line.find(B) != std::string::npos)
					{
						string A = Extern_Reader::StringManager::SubstituirPalavra(line, B, "");
						string C = Extern_Reader::StringManager::SubstituirPalavra(A, "\"", "");
						string D = Extern_Reader::StringManager::SubstituirPalavra(C, "    ", "");
						string E = Extern_Reader::StringManager::SubstituirPalavra(D, ",", "");
						string F = Extern_Reader::StringManager::SubstituirPalavra(E, "   ", "");
						string G = Extern_Reader::StringManager::SubstituirPalavra(F, "  ", "");
						float final = stof(G);
						TempVECTOR.push_back(final);
					}
				}
				return TempVECTOR;
			}
		}
	}
};
namespace GTA
{
	struct Spawn_Struct
	{
		std::string Model;
		DWORD Hash;
		float PosX;
		float PosY;
		float PosZ;
		float RotX;
		float RotY;
		float RotZ;
	};
	void Carregar_Mapa_INI(std::string INIPath)
	{
		//Exemplo::
		//GTA::Carregar_Mapa_INI(".\\Mapa.ini");
		//
		Spawn_Struct Spawn;
		Extern_Reader::INIFile::INIFilePath = INIPath;
		for (int i = 1; i <= 1000; i++)
		{
			char buffer[5000];
			snprintf(buffer, 5000, "%i", i);
			std::string Modelo = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
			if (Modelo == "")
			{
				i = 1000;
			}
			else
			{
				Spawn.Model = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
				Spawn.Hash = Extern_Reader::INIFile::Int::LerInt(buffer, "Hash");
				Spawn.PosX = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosX");
				Spawn.PosY = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosY");
				Spawn.PosZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosZ");
				Spawn.RotX = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotX");
				Spawn.RotY = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotY");
				Spawn.RotZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotZ");
				//Void de spawn aqui
				/*
				cout << "[" << i << "]" << endl;
				cout << "Model=" << i << Spawn.Model << endl;
				cout << "PosX=" << i << Spawn.PosX << endl;
				cout << "PosY=" << i << Spawn.PosY << endl;
				cout << "PosZ=" << i << Spawn.PosZ << endl;
				cout << "RotX=" << i << Spawn.RotX << endl;
				cout << "RotY=" << i << Spawn.RotY << endl;
				cout << "RotZ=" << i << Spawn.RotZ << endl;
				*/
			}
		}
	}
	void Carregar_Mapa_Peds(std::string INIPath)
	{
		//Exemplo::
		//GTA::Carregar_Mapa_INI(".\\Mapa.ini");
		//
		Spawn_Struct Spawn;
		Extern_Reader::INIFile::INIFilePath = INIPath;
		for (int i = 1; i <= 1000; i++)
		{
			char buffer[5000];
			snprintf(buffer, 5000, "%i", i);
			std::string Modelo = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
			if (Modelo == "")
			{
				i = 1000;
			}
			else
			{
				Spawn.Model = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
				Spawn.Hash = Extern_Reader::INIFile::Int::LerInt(buffer, "Hash");
				Spawn.PosX = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosX");
				Spawn.PosY = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosY");
				Spawn.PosZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosZ");
				Spawn.RotX = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotX");
				Spawn.RotY = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotY");
				Spawn.RotZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotZ");
				//Void de spawn aqui
				/*
				cout << "[" << i << "]" << endl;
				cout << "Model=" << i << Spawn.Model << endl;
				cout << "PosX=" << i << Spawn.PosX << endl;
				cout << "PosY=" << i << Spawn.PosY << endl;
				cout << "PosZ=" << i << Spawn.PosZ << endl;
				cout << "RotX=" << i << Spawn.RotX << endl;
				cout << "RotY=" << i << Spawn.RotY << endl;
				cout << "RotZ=" << i << Spawn.RotZ << endl;
				*/
			}
		}
	}
	void Carregar_Mapa_Veiculos(std::string INIPath)
	{
		//Exemplo::
		//GTA::Carregar_Mapa_INI(".\\Mapa.ini");
		//
		Spawn_Struct Spawn;
		Extern_Reader::INIFile::INIFilePath = INIPath;
		for (int i = 1; i <= 1000; i++)
		{
			char buffer[5000];
			snprintf(buffer, 5000, "%i", i);
			std::string Modelo = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
			if (Modelo == "")
			{
				i = 1000;
			}
			else
			{
				Spawn.Model = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
				Spawn.Hash = Extern_Reader::INIFile::Int::LerInt(buffer, "Hash");
				Spawn.PosX = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosX");
				Spawn.PosY = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosY");
				Spawn.PosZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosZ");
				Spawn.RotX = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotX");
				Spawn.RotY = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotY");
				Spawn.RotZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotZ");
				//Void de spawn aqui
				/*
				cout << "[" << i << "]" << endl;
				cout << "Model=" << i << Spawn.Model << endl;
				cout << "PosX=" << i << Spawn.PosX << endl;
				cout << "PosY=" << i << Spawn.PosY << endl;
				cout << "PosZ=" << i << Spawn.PosZ << endl;
				cout << "RotX=" << i << Spawn.RotX << endl;
				cout << "RotY=" << i << Spawn.RotY << endl;
				cout << "RotZ=" << i << Spawn.RotZ << endl;
				*/
			}
		}
	}
	void CriarModeloDeSpawn(std::string ININame, int NumeroDeItens)
	{
		//Exemplo::
		//GTA::CriarModeloDeSpawn(".\\Mapa.ini", 1000);
		Spawn_Struct Spawn;
		Extern_Reader::INIFile::INIFilePath = ININame;
		for (int i = 1; i <= NumeroDeItens; i++)
		{
			char buffer[5000];
			snprintf(buffer, 5000, "%i", i);
			Extern_Reader::INIFile::String::GravarString("", buffer, "Modelo");
			Extern_Reader::INIFile::Int::GravarInt(0, buffer, "Hash");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "PosX");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "PosY");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "PosZ");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "RotX");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "RotY");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "RotZ");
		}
	}
}
namespace RDR2
{
	struct Spawn_Struct
	{
		std::string Model;
		DWORD Hash;
		float PosX;
		float PosY;
		float PosZ;
		float RotX;
		float RotY;
		float RotZ;
	};
	void Carregar_Mapa_INI(std::string INIPath)
	{
		//Exemplo::
		//GTA::Carregar_Mapa_INI(".\\Mapa.ini");
		//
		Spawn_Struct Spawn;
		Extern_Reader::INIFile::INIFilePath = INIPath;
		for (int i = 1; i <= 1000; i++)
		{
			char buffer[5000];
			snprintf(buffer, 5000, "%i", i);
			std::string Modelo = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
			if (Modelo == "")
			{
				i = 1000;
			}
			else
			{
				Spawn.Model = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
				Spawn.Hash = Extern_Reader::INIFile::Int::LerInt(buffer, "Hash");
				Spawn.PosX = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosX");
				Spawn.PosY = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosY");
				Spawn.PosZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosZ");
				Spawn.RotX = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotX");
				Spawn.RotY = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotY");
				Spawn.RotZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotZ");
				//Void de spawn aqui
				/*
				cout << "[" << i << "]" << endl;
				cout << "Model=" << i << Spawn.Model << endl;
				cout << "PosX=" << i << Spawn.PosX << endl;
				cout << "PosY=" << i << Spawn.PosY << endl;
				cout << "PosZ=" << i << Spawn.PosZ << endl;
				cout << "RotX=" << i << Spawn.RotX << endl;
				cout << "RotY=" << i << Spawn.RotY << endl;
				cout << "RotZ=" << i << Spawn.RotZ << endl;
				*/
			}
		}
	}
	void Carregar_Mapa_Peds(std::string INIPath)
	{
		//Exemplo::
		//GTA::Carregar_Mapa_INI(".\\Mapa.ini");
		//
		Spawn_Struct Spawn;
		Extern_Reader::INIFile::INIFilePath = INIPath;
		for (int i = 1; i <= 1000; i++)
		{
			char buffer[5000];
			snprintf(buffer, 5000, "%i", i);
			std::string Modelo = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
			if (Modelo == "")
			{
				i = 1000;
			}
			else
			{
				Spawn.Model = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
				Spawn.Hash = Extern_Reader::INIFile::Int::LerInt(buffer, "Hash");
				Spawn.PosX = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosX");
				Spawn.PosY = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosY");
				Spawn.PosZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosZ");
				Spawn.RotX = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotX");
				Spawn.RotY = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotY");
				Spawn.RotZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotZ");
				//Void de spawn aqui
				/*
				cout << "[" << i << "]" << endl;
				cout << "Model=" << i << Spawn.Model << endl;
				cout << "PosX=" << i << Spawn.PosX << endl;
				cout << "PosY=" << i << Spawn.PosY << endl;
				cout << "PosZ=" << i << Spawn.PosZ << endl;
				cout << "RotX=" << i << Spawn.RotX << endl;
				cout << "RotY=" << i << Spawn.RotY << endl;
				cout << "RotZ=" << i << Spawn.RotZ << endl;
				*/
			}
		}
	}
	void Carregar_Mapa_Veiculos(std::string INIPath)
	{
		//Exemplo::
		//GTA::Carregar_Mapa_INI(".\\Mapa.ini");
		//
		Spawn_Struct Spawn;
		Extern_Reader::INIFile::INIFilePath = INIPath;
		for (int i = 1; i <= 1000; i++)
		{
			char buffer[5000];
			snprintf(buffer, 5000, "%i", i);
			std::string Modelo = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
			if (Modelo == "")
			{
				i = 1000;
			}
			else
			{
				Spawn.Model = Extern_Reader::INIFile::String::LerString(buffer, "Modelo");
				Spawn.Hash = Extern_Reader::INIFile::Int::LerInt(buffer, "Hash");
				Spawn.PosX = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosX");
				Spawn.PosY = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosY");
				Spawn.PosZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "PosZ");
				Spawn.RotX = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotX");
				Spawn.RotY = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotY");
				Spawn.RotZ = Extern_Reader::INIFile::Float::LerFloat(buffer, "RotZ");
				//Void de spawn aqui
				/*
				cout << "[" << i << "]" << endl;
				cout << "Model=" << i << Spawn.Model << endl;
				cout << "PosX=" << i << Spawn.PosX << endl;
				cout << "PosY=" << i << Spawn.PosY << endl;
				cout << "PosZ=" << i << Spawn.PosZ << endl;
				cout << "RotX=" << i << Spawn.RotX << endl;
				cout << "RotY=" << i << Spawn.RotY << endl;
				cout << "RotZ=" << i << Spawn.RotZ << endl;
				*/
			}
		}
	}
	void CriarModeloDeSpawn(std::string ININame, int NumeroDeItens)
	{
		//Exemplo::
		//GTA::CriarModeloDeSpawn(".\\Mapa.ini", 1000);
		Spawn_Struct Spawn;
		Extern_Reader::INIFile::INIFilePath = ININame;
		for (int i = 1; i <= NumeroDeItens; i++)
		{
			char buffer[5000];
			snprintf(buffer, 5000, "%i", i);
			Extern_Reader::INIFile::String::GravarString("", buffer, "Modelo");
			Extern_Reader::INIFile::Int::GravarInt(0, buffer, "Hash");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "PosX");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "PosY");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "PosZ");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "RotX");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "RotY");
			Extern_Reader::INIFile::Float::GravarFloat(0, buffer, "RotZ");
		}
	}
}
namespace Menyoo
{
	std::string XMLPath;
	namespace SalvarXML
	{
		/*
		Exemplo de salvar:
		Menyoo::XMLPath = ".\\MapaMenyoo.xml";
		Menyoo::SalvarXML::MenyooCabecalho();
		Menyoo::SalvarXML::Add_Reference_Coords(1111.1111, 2222.2222, 3333.3333);
		GTA::Spawn_Struct SpawnPed;
		GTA::Spawn_Struct SpawnProp;
		GTA::Spawn_Struct SpawnVeh;
		Menyoo::SalvarXML::AddSpawn_XML_Peds(SpawnPed);
		Menyoo::SalvarXML::AddSpawn_XML_Prop(SpawnProp);
		Menyoo::SalvarXML::AddSpawn_XML_Veiculos(SpawnVeh);
		Menyoo::SalvarXML::FinalizarXML();
	*/
		void MenyooCabecalho()
		{
			Extern_Reader::LOG::arquivoTXT = XMLPath;
			Extern_Reader::LOG::LogSemHora("<?xml version=\"1.0\" encoding=\"ISO - 8859 - 1\"?>");
			Extern_Reader::LOG::LogSemHora("<SpoonerPlacements>");
			Extern_Reader::LOG::LogSemHora("<Note />");
			Extern_Reader::LOG::LogSemHora("<AudioFile volume=\"400\" /> ");
			Extern_Reader::LOG::LogSemHora("<ClearDatabase>false</ClearDatabase>");
			Extern_Reader::LOG::LogSemHora("<ClearWorld>0</ClearWorld>");
			Extern_Reader::LOG::LogSemHora("<ClearMarkers>false</ClearMarkers>");
			Extern_Reader::LOG::LogSemHora("<IPLsToLoad load_mp_maps=\"false\" load_sp_maps=\"false\" />");
			Extern_Reader::LOG::LogSemHora("<IPLsToRemove />");
			Extern_Reader::LOG::LogSemHora("<InteriorsToEnable />");
			Extern_Reader::LOG::LogSemHora("<InteriorsToCap />");
			Extern_Reader::LOG::LogSemHora("<WeatherToSet></WeatherToSet>");
			Extern_Reader::LOG::LogSemHora("<TimecycleModifier strength=\"1\"></TimecycleModifier>");
			Extern_Reader::LOG::LogSemHora("<StartTaskSequencesOnLoad>true</StartTaskSequencesOnLoad>");
		}
		void Add_Reference_Coords(float x, float y, float z)
		{
			Extern_Reader::LOG::arquivoTXT = XMLPath;
			Extern_Reader::LOG::LogSemHora("<ReferenceCoords>");
			Extern_Reader::LOG::LogSemHora("<X>" + to_string(x) + "</X>");
			Extern_Reader::LOG::LogSemHora("<Y>" + to_string(y) + "</Y>");
			Extern_Reader::LOG::LogSemHora("<Z>" + to_string(z) + "</Z>");
			Extern_Reader::LOG::LogSemHora("</ReferenceCoords>");
		}
		void AddSpawn_XML_Prop(GTA::Spawn_Struct Estrutura)
		{
			Extern_Reader::LOG::arquivoTXT = XMLPath;
			Extern_Reader::LOG::LogSemHora("<Placement>");
			Extern_Reader::LOG::LogSemHora("<ModelHash>" + to_string(Estrutura.Hash) + "</ModelHash>");
			Extern_Reader::LOG::LogSemHora("<Type>3</Type>");
			Extern_Reader::LOG::LogSemHora("<Dynamic>false</Dynamic>");
			Extern_Reader::LOG::LogSemHora("<FrozenPos>true</FrozenPos>");
			Extern_Reader::LOG::LogSemHora("<HashName>" + Estrutura.Model + "</HashName>");
			Extern_Reader::LOG::LogSemHora("<InitialHandle>777734</InitialHandle>");
			Extern_Reader::LOG::LogSemHora("<ObjectProperties>");
			Extern_Reader::LOG::LogSemHora("<TextureVariation>0</TextureVariation>");
			Extern_Reader::LOG::LogSemHora("</ObjectProperties>");
			Extern_Reader::LOG::LogSemHora("<OpacityLevel>255</OpacityLevel>");
			Extern_Reader::LOG::LogSemHora("<LodDistance>16960</LodDistance>");
			Extern_Reader::LOG::LogSemHora("<IsVisible>true</IsVisible>");
			Extern_Reader::LOG::LogSemHora("<MaxHealth>1000</MaxHealth>");
			Extern_Reader::LOG::LogSemHora("<Health>1000</Health>");
			Extern_Reader::LOG::LogSemHora("<HasGravity>true</HasGravity>");
			Extern_Reader::LOG::LogSemHora("<IsOnFire>false</IsOnFire>");
			Extern_Reader::LOG::LogSemHora("<IsInvincible>false</IsInvincible>");
			Extern_Reader::LOG::LogSemHora("<IsBulletProof>false</IsBulletProof>");
			Extern_Reader::LOG::LogSemHora("<IsCollisionProof>false</IsCollisionProof>");
			Extern_Reader::LOG::LogSemHora("<IsExplosionProof>false</IsExplosionProof>");
			Extern_Reader::LOG::LogSemHora("<IsFireProof>false</IsFireProof>");
			Extern_Reader::LOG::LogSemHora("<IsMeleeProof>false</IsMeleeProof>");
			Extern_Reader::LOG::LogSemHora("<IsOnlyDamagedByPlayer>false</IsOnlyDamagedByPlayer>");
			Extern_Reader::LOG::LogSemHora("<PositionRotation>");
			Extern_Reader::LOG::LogSemHora("<X>" + to_string(Estrutura.PosX) + "</X>");
			Extern_Reader::LOG::LogSemHora("<Y>" + to_string(Estrutura.PosY) + "</Y>");
			Extern_Reader::LOG::LogSemHora("<Z>" + to_string(Estrutura.PosZ) + "</Z>");
			Extern_Reader::LOG::LogSemHora("<Pitch>" + to_string(Estrutura.PosZ) + "</Pitch>");
			Extern_Reader::LOG::LogSemHora("<Roll>" + to_string(Estrutura.PosZ) + "</Roll>");
			Extern_Reader::LOG::LogSemHora("<Yaw>" + to_string(Estrutura.PosZ) + "</Yaw>");
			Extern_Reader::LOG::LogSemHora("</PositionRotation>");
			Extern_Reader::LOG::LogSemHora("<Attachment isAttached=\"false\" />");
			Extern_Reader::LOG::LogSemHora("</Placement>");
		}
		void AddSpawn_XML_Veiculos(GTA::Spawn_Struct Estrutura)
		{
			Extern_Reader::LOG::arquivoTXT = XMLPath;
			Extern_Reader::LOG::LogSemHora("<Placement>");
			Extern_Reader::LOG::LogSemHora("<ModelHash>" + to_string(Estrutura.Hash) + "</ModelHash>");
			Extern_Reader::LOG::LogSemHora("<Type>2</Type>");
			Extern_Reader::LOG::LogSemHora("<Dynamic>true</Dynamic>");
			Extern_Reader::LOG::LogSemHora("<FrozenPos>false</FrozenPos>");
			Extern_Reader::LOG::LogSemHora("<HashName>" + Estrutura.Model + "</HashName>");
			Extern_Reader::LOG::LogSemHora("<InitialHandle>495113</InitialHandle>");
			Extern_Reader::LOG::LogSemHora("<VehicleProperties>");
			Extern_Reader::LOG::LogSemHora("<Colours>");
			Extern_Reader::LOG::LogSemHora("<Primary>12</Primary>");
			Extern_Reader::LOG::LogSemHora("<Secondary>12</Secondary>");
			Extern_Reader::LOG::LogSemHora("<Pearl>0</Pearl>");
			Extern_Reader::LOG::LogSemHora("<Rim>156</Rim>");
			Extern_Reader::LOG::LogSemHora("<Mod1_a>6</Mod1_a>");
			Extern_Reader::LOG::LogSemHora("<Mod1_b>-1</Mod1_b>");
			Extern_Reader::LOG::LogSemHora("<Mod1_c>-1</Mod1_c>");
			Extern_Reader::LOG::LogSemHora("<Mod2_a>6</Mod2_a>");
			Extern_Reader::LOG::LogSemHora("<Mod2_b>-1</Mod2_b>");
			Extern_Reader::LOG::LogSemHora("<IsPrimaryColourCustom>false</IsPrimaryColourCustom>");
			Extern_Reader::LOG::LogSemHora("<IsSecondaryColourCustom>false</IsSecondaryColourCustom>");
			Extern_Reader::LOG::LogSemHora("<tyreSmoke_R>255</tyreSmoke_R>");
			Extern_Reader::LOG::LogSemHora("<tyreSmoke_G>255</tyreSmoke_G>");
			Extern_Reader::LOG::LogSemHora("<tyreSmoke_B>255</tyreSmoke_B>");
			Extern_Reader::LOG::LogSemHora("<LrInterior>0</LrInterior>");
			Extern_Reader::LOG::LogSemHora("<LrDashboard>0</LrDashboard>");
			Extern_Reader::LOG::LogSemHora("<LrXenonHeadlights>0</LrXenonHeadlights>");
			Extern_Reader::LOG::LogSemHora("</Colours>");
			Extern_Reader::LOG::LogSemHora("<Livery>-1</Livery>");
			Extern_Reader::LOG::LogSemHora("<NumberPlateText>80HSK762</NumberPlateText>");
			Extern_Reader::LOG::LogSemHora("<NumberPlateIndex>0</NumberPlateIndex>");
			Extern_Reader::LOG::LogSemHora("<WheelType>3</WheelType>");
			Extern_Reader::LOG::LogSemHora("<WheelsInvisible>false</WheelsInvisible>");
			Extern_Reader::LOG::LogSemHora("<EngineSoundName></EngineSoundName>");
			Extern_Reader::LOG::LogSemHora("<WindowTint>1</WindowTint>");
			Extern_Reader::LOG::LogSemHora("<BulletProofTyres>false</BulletProofTyres>");
			Extern_Reader::LOG::LogSemHora("<DirtLevel>0</DirtLevel>");
			Extern_Reader::LOG::LogSemHora("<PaintFade>0.298039228</PaintFade>");
			Extern_Reader::LOG::LogSemHora("<RoofState>0</RoofState>");
			Extern_Reader::LOG::LogSemHora("<SirenActive>false</SirenActive>");
			Extern_Reader::LOG::LogSemHora("<EngineOn>false</EngineOn>");
			Extern_Reader::LOG::LogSemHora("<EngineHealth>1000</EngineHealth>");
			Extern_Reader::LOG::LogSemHora("<LightsOn>false</LightsOn>");
			Extern_Reader::LOG::LogSemHora("<IsRadioLoud>0</IsRadioLoud>");
			Extern_Reader::LOG::LogSemHora("<LockStatus>1</LockStatus>");
			Extern_Reader::LOG::LogSemHora("<Neons>");
			Extern_Reader::LOG::LogSemHora("<Left>false</Left>");
			Extern_Reader::LOG::LogSemHora("<Right>false</Right>");
			Extern_Reader::LOG::LogSemHora("<Front>false</Front>");
			Extern_Reader::LOG::LogSemHora("<Back>false</Back>");
			Extern_Reader::LOG::LogSemHora("<R>255</R>");
			Extern_Reader::LOG::LogSemHora("<G>0</G>");
			Extern_Reader::LOG::LogSemHora("<B>255</B>");
			Extern_Reader::LOG::LogSemHora("</Neons>");
			Extern_Reader::LOG::LogSemHora("<DoorsOpen>");
			Extern_Reader::LOG::LogSemHora("<BackLeftDoor>false</BackLeftDoor>");
			Extern_Reader::LOG::LogSemHora("<BackRightDoor>false</BackRightDoor>");
			Extern_Reader::LOG::LogSemHora("<FrontLeftDoor>false</FrontLeftDoor>");
			Extern_Reader::LOG::LogSemHora("<FrontRightDoor>false</FrontRightDoor>");
			Extern_Reader::LOG::LogSemHora("<Hood>false</Hood>");
			Extern_Reader::LOG::LogSemHora("<Trunk>false</Trunk>");
			Extern_Reader::LOG::LogSemHora("<Trunk2>false</Trunk2>");
			Extern_Reader::LOG::LogSemHora("</DoorsOpen>");
			Extern_Reader::LOG::LogSemHora("<DoorsBroken>");
			Extern_Reader::LOG::LogSemHora("<BackLeftDoor>false</BackLeftDoor>");
			Extern_Reader::LOG::LogSemHora("<BackRightDoor>false</BackRightDoor>");
			Extern_Reader::LOG::LogSemHora("<FrontLeftDoor>false</FrontLeftDoor>");
			Extern_Reader::LOG::LogSemHora("<FrontRightDoor>false</FrontRightDoor>");
			Extern_Reader::LOG::LogSemHora("<Hood>false</Hood>");
			Extern_Reader::LOG::LogSemHora("<Trunk>false</Trunk>");
			Extern_Reader::LOG::LogSemHora("<Trunk2>false</Trunk2>");
			Extern_Reader::LOG::LogSemHora("</DoorsBroken>");
			Extern_Reader::LOG::LogSemHora("<TyresBursted>");
			Extern_Reader::LOG::LogSemHora("<FrontLeft>false</FrontLeft>");
			Extern_Reader::LOG::LogSemHora("<FrontRight>false</FrontRight>");
			Extern_Reader::LOG::LogSemHora("<_2>false</_2>");
			Extern_Reader::LOG::LogSemHora("<_3>false</_3>");
			Extern_Reader::LOG::LogSemHora("<BackLeft>false</BackLeft>");
			Extern_Reader::LOG::LogSemHora("<BackRight>false</BackRight>");
			Extern_Reader::LOG::LogSemHora("<_6>false</_6>");
			Extern_Reader::LOG::LogSemHora("<_7>false</_7>");
			Extern_Reader::LOG::LogSemHora("<_8>false</_8>");
			Extern_Reader::LOG::LogSemHora("</TyresBursted>");
			Extern_Reader::LOG::LogSemHora("<ModExtras>");
			Extern_Reader::LOG::LogSemHora("<_10>true</_10>");
			Extern_Reader::LOG::LogSemHora("<_12>false</_12>");
			Extern_Reader::LOG::LogSemHora("</ModExtras>");
			Extern_Reader::LOG::LogSemHora("<Mods>");
			Extern_Reader::LOG::LogSemHora("<_0>-1,0</_0>");
			Extern_Reader::LOG::LogSemHora("<_1>-1,0</_1>");
			Extern_Reader::LOG::LogSemHora("<_2>-1,0</_2>");
			Extern_Reader::LOG::LogSemHora("<_3>-1,0</_3>");
			Extern_Reader::LOG::LogSemHora("<_4>-1,0</_4>");
			Extern_Reader::LOG::LogSemHora("<_5>-1,0</_5>");
			Extern_Reader::LOG::LogSemHora("<_6>-1,0</_6>");
			Extern_Reader::LOG::LogSemHora("<_7>-1,0</_7>");
			Extern_Reader::LOG::LogSemHora("<_8>-1,0</_8>");
			Extern_Reader::LOG::LogSemHora("<_9>-1,0</_9>");
			Extern_Reader::LOG::LogSemHora("<_10>-1,0</_10>");
			Extern_Reader::LOG::LogSemHora("<_11>-1,0</_11>");
			Extern_Reader::LOG::LogSemHora("<_12>-1,0</_12>");
			Extern_Reader::LOG::LogSemHora("<_13>-1,0</_13>");
			Extern_Reader::LOG::LogSemHora("<_14>-1,0</_14>");
			Extern_Reader::LOG::LogSemHora("<_15>-1,0</_15>");
			Extern_Reader::LOG::LogSemHora("<_16>-1,0</_16>");
			Extern_Reader::LOG::LogSemHora("<_17>false</_17>");
			Extern_Reader::LOG::LogSemHora("<_18>false</_18>");
			Extern_Reader::LOG::LogSemHora("<_19>false</_19>");
			Extern_Reader::LOG::LogSemHora("<_20>false</_20>");
			Extern_Reader::LOG::LogSemHora("<_21>false</_21>");
			Extern_Reader::LOG::LogSemHora("<_22>false</_22>");
			Extern_Reader::LOG::LogSemHora("<_23>-1,0</_23>");
			Extern_Reader::LOG::LogSemHora("<_24>-1,0</_24>");
			Extern_Reader::LOG::LogSemHora("<_25>-1,0</_25>");
			Extern_Reader::LOG::LogSemHora("<_26>-1,0</_26>");
			Extern_Reader::LOG::LogSemHora("<_27>-1,0</_27>");
			Extern_Reader::LOG::LogSemHora("<_28>-1,0</_28>");
			Extern_Reader::LOG::LogSemHora("<_29>-1,0</_29>");
			Extern_Reader::LOG::LogSemHora("<_30>-1,0</_30>");
			Extern_Reader::LOG::LogSemHora("<_31>-1,0</_31>");
			Extern_Reader::LOG::LogSemHora("<_32>-1,0</_32>");
			Extern_Reader::LOG::LogSemHora("<_33>-1,0</_33>");
			Extern_Reader::LOG::LogSemHora("<_34>-1,0</_34>");
			Extern_Reader::LOG::LogSemHora("<_35>-1,0</_35>");
			Extern_Reader::LOG::LogSemHora("<_36>-1,0</_36>");
			Extern_Reader::LOG::LogSemHora("<_37>-1,0</_37>");
			Extern_Reader::LOG::LogSemHora("<_38>-1,0</_38>");
			Extern_Reader::LOG::LogSemHora("<_39>-1,0</_39>");
			Extern_Reader::LOG::LogSemHora("<_40>-1,0</_40>");
			Extern_Reader::LOG::LogSemHora("<_41>-1,0</_41>");
			Extern_Reader::LOG::LogSemHora("<_42>-1,0</_42>");
			Extern_Reader::LOG::LogSemHora("<_43>-1,0</_43>");
			Extern_Reader::LOG::LogSemHora("<_44>-1,0</_44>");
			Extern_Reader::LOG::LogSemHora("<_45>-1,0</_45>");
			Extern_Reader::LOG::LogSemHora("<_46>-1,0</_46>");
			Extern_Reader::LOG::LogSemHora("<_47>-1,0</_47>");
			Extern_Reader::LOG::LogSemHora("<_48>-1,0</_48>");
			Extern_Reader::LOG::LogSemHora("</Mods>");
			Extern_Reader::LOG::LogSemHora("</VehicleProperties>");
			Extern_Reader::LOG::LogSemHora("<OpacityLevel>255</OpacityLevel>");
			Extern_Reader::LOG::LogSemHora("<LodDistance>16960</LodDistance>");
			Extern_Reader::LOG::LogSemHora("<IsVisible>true</IsVisible>");
			Extern_Reader::LOG::LogSemHora("<MaxHealth>1000</MaxHealth>");
			Extern_Reader::LOG::LogSemHora("<Health>1000</Health>");
			Extern_Reader::LOG::LogSemHora("<HasGravity>true</HasGravity>");
			Extern_Reader::LOG::LogSemHora("<IsOnFire>false</IsOnFire>");
			Extern_Reader::LOG::LogSemHora("<IsInvincible>false</IsInvincible>");
			Extern_Reader::LOG::LogSemHora("<IsBulletProof>false</IsBulletProof>");
			Extern_Reader::LOG::LogSemHora("<IsCollisionProof>false</IsCollisionProof>");
			Extern_Reader::LOG::LogSemHora("<IsExplosionProof>false</IsExplosionProof>");
			Extern_Reader::LOG::LogSemHora("<IsFireProof>false</IsFireProof>");
			Extern_Reader::LOG::LogSemHora("<IsMeleeProof>false</IsMeleeProof>");
			Extern_Reader::LOG::LogSemHora("<IsOnlyDamagedByPlayer>false</IsOnlyDamagedByPlayer>");
			Extern_Reader::LOG::LogSemHora("<PositionRotation>");
			Extern_Reader::LOG::LogSemHora("<X>" + to_string(Estrutura.PosX) + "</X>");
			Extern_Reader::LOG::LogSemHora("<Y>" + to_string(Estrutura.PosY) + "</Y>");
			Extern_Reader::LOG::LogSemHora("<Z>" + to_string(Estrutura.PosZ) + "</Z>");
			Extern_Reader::LOG::LogSemHora("<Pitch>" + to_string(Estrutura.PosZ) + "</Pitch>");
			Extern_Reader::LOG::LogSemHora("<Roll>" + to_string(Estrutura.PosZ) + "</Roll>");
			Extern_Reader::LOG::LogSemHora("<Yaw>" + to_string(Estrutura.PosZ) + "</Yaw>");
			Extern_Reader::LOG::LogSemHora("</PositionRotation>");
			Extern_Reader::LOG::LogSemHora("<Attachment isAttached=\"false\" />");
			Extern_Reader::LOG::LogSemHora("</Placement>");
		}
		void AddSpawn_XML_Peds(GTA::Spawn_Struct Estrutura)
		{
			Extern_Reader::LOG::arquivoTXT = XMLPath;
			Extern_Reader::LOG::LogSemHora("<Placement>");
			Extern_Reader::LOG::LogSemHora("<ModelHash>" + to_string(Estrutura.Hash) + "</ModelHash>");
			Extern_Reader::LOG::LogSemHora("<Type>1</Type>");
			Extern_Reader::LOG::LogSemHora("<Dynamic>true</Dynamic>");
			Extern_Reader::LOG::LogSemHora("<FrozenPos>false</FrozenPos>");
			Extern_Reader::LOG::LogSemHora("<HashName>" + Estrutura.Model + "</HashName>");
			Extern_Reader::LOG::LogSemHora("<InitialHandle>92935</InitialHandle>");
			Extern_Reader::LOG::LogSemHora("<PedProperties>");
			Extern_Reader::LOG::LogSemHora("<IsStill>false</IsStill>");
			Extern_Reader::LOG::LogSemHora("<CanRagdoll>true</CanRagdoll>");
			Extern_Reader::LOG::LogSemHora("<HasShortHeight>false</HasShortHeight>");
			Extern_Reader::LOG::LogSemHora("<Armour>0</Armour>");
			Extern_Reader::LOG::LogSemHora("<CurrentWeapon>0xA2719263</CurrentWeapon>");
			Extern_Reader::LOG::LogSemHora("<PedProps>");
			Extern_Reader::LOG::LogSemHora("<_0>-1,-1</_0>");
			Extern_Reader::LOG::LogSemHora("<_1>0,0</_1>");
			Extern_Reader::LOG::LogSemHora("<_2>-1,-1</_2>");
			Extern_Reader::LOG::LogSemHora("<_3>-1,-1</_3>");
			Extern_Reader::LOG::LogSemHora("<_4>-1,-1</_4>");
			Extern_Reader::LOG::LogSemHora("<_5>-1,-1</_5>");
			Extern_Reader::LOG::LogSemHora("<_6>-1,-1</_6>");
			Extern_Reader::LOG::LogSemHora("<_7>-1,-1</_7>");
			Extern_Reader::LOG::LogSemHora("<_8>-1,-1</_8>");
			Extern_Reader::LOG::LogSemHora("<_9>-1,-1</_9>");
			Extern_Reader::LOG::LogSemHora("</PedProps>");
			Extern_Reader::LOG::LogSemHora("<PedComps>");
			Extern_Reader::LOG::LogSemHora("<_0>0,0</_0>");
			Extern_Reader::LOG::LogSemHora("<_1>0,0</_1>");
			Extern_Reader::LOG::LogSemHora("<_2>0,0</_2>");
			Extern_Reader::LOG::LogSemHora("<_3>0,0</_3>");
			Extern_Reader::LOG::LogSemHora("<_4>0,0</_4>");
			Extern_Reader::LOG::LogSemHora("<_5>0,0</_5>");
			Extern_Reader::LOG::LogSemHora("<_6>0,0</_6>");
			Extern_Reader::LOG::LogSemHora("<_7>0,0</_7>");
			Extern_Reader::LOG::LogSemHora("<_8>0,0</_8>");
			Extern_Reader::LOG::LogSemHora("<_9>0,0</_9>");
			Extern_Reader::LOG::LogSemHora("<_10>0,0</_10>");
			Extern_Reader::LOG::LogSemHora("<_11>0,0</_11>");
			Extern_Reader::LOG::LogSemHora("</PedComps>");
			Extern_Reader::LOG::LogSemHora("<RelationshipGroupAltered>false</RelationshipGroupAltered>");
			Extern_Reader::LOG::LogSemHora("<RelationshipGroup>0xfade4843</RelationshipGroup>");
			Extern_Reader::LOG::LogSemHora("<ScenarioActive>true</ScenarioActive>");
			Extern_Reader::LOG::LogSemHora("<ScenarioName>WORLD_HUMAN_DRUG_DEALER_HARD</ScenarioName>");
			Extern_Reader::LOG::LogSemHora("<AnimActive>false</AnimActive>");
			Extern_Reader::LOG::LogSemHora("</PedProperties>");
			Extern_Reader::LOG::LogSemHora("<OpacityLevel>255</OpacityLevel>");
			Extern_Reader::LOG::LogSemHora("<LodDistance>240</LodDistance>");
			Extern_Reader::LOG::LogSemHora("<IsVisible>true</IsVisible>");
			Extern_Reader::LOG::LogSemHora("<MaxHealth>200</MaxHealth>");
			Extern_Reader::LOG::LogSemHora("<Health>200</Health>");
			Extern_Reader::LOG::LogSemHora("<HasGravity>true</HasGravity>");
			Extern_Reader::LOG::LogSemHora("<IsOnFire>false</IsOnFire>");
			Extern_Reader::LOG::LogSemHora("<IsInvincible>false</IsInvincible>");
			Extern_Reader::LOG::LogSemHora("<IsBulletProof>false</IsBulletProof>");
			Extern_Reader::LOG::LogSemHora("<IsCollisionProof>false</IsCollisionProof>");
			Extern_Reader::LOG::LogSemHora("<IsExplosionProof>false</IsExplosionProof>");
			Extern_Reader::LOG::LogSemHora("<IsFireProof>false</IsFireProof>");
			Extern_Reader::LOG::LogSemHora("<IsMeleeProof>false</IsMeleeProof>");
			Extern_Reader::LOG::LogSemHora("<IsOnlyDamagedByPlayer>false</IsOnlyDamagedByPlayer>");
			Extern_Reader::LOG::LogSemHora("<PositionRotation>");
			Extern_Reader::LOG::LogSemHora("<X>" + to_string(Estrutura.PosX) + "</X>");
			Extern_Reader::LOG::LogSemHora("<Y>" + to_string(Estrutura.PosY) + "</Y>");
			Extern_Reader::LOG::LogSemHora("<Z>" + to_string(Estrutura.PosZ) + "</Z>");
			Extern_Reader::LOG::LogSemHora("<Pitch>" + to_string(Estrutura.PosZ) + "</Pitch>");
			Extern_Reader::LOG::LogSemHora("<Roll>" + to_string(Estrutura.PosZ) + "</Roll>");
			Extern_Reader::LOG::LogSemHora("<Yaw>" + to_string(Estrutura.PosZ) + "</Yaw>");
			Extern_Reader::LOG::LogSemHora("</PositionRotation>");
			Extern_Reader::LOG::LogSemHora("<Attachment isAttached=\"false\" />");
			Extern_Reader::LOG::LogSemHora("</Placement>");
		}
		void FinalizarXML()
		{
			Extern_Reader::LOG::arquivoTXT = XMLPath;
			Extern_Reader::LOG::LogSemHora("</SpoonerPlacements>");
		}
	}
	namespace Carregar
	{
		struct Menyoo
		{
			std::string Model;
			DWORD Hash;
			float PosX;
			float PosY;
			float PosZ;
			float RotX;
			float RotY;
			float RotZ;
		};
		std::vector<std::string> PegarValores(std::string Arquivo)
		{
			/*
			Exemplo:
			vector<string> A = Menyoo::Carregar::PegarValores(".\\MapaMenyoo.xml");
			for (int i = 0; i <= Extern_Reader::ArquivoTXT::TamanhoDoVector(Aa); i++)
			{
				cout << A[i] << endl;
			}
			*/
			std::vector<std::string> tokens;
			ifstream imput(Arquivo);
			for (string line; getline(imput, line);)
			{
				istringstream tokenizer{ line };
				string token;
				while (getline(tokenizer, token))
				{
					if (Extern_Reader::StringManager::SeContemTexto(token, "<X>"))
					{
						std::string a = Extern_Reader::StringManager::SubstituirPalavra(token, "<X>", "");
						a = Extern_Reader::StringManager::SubstituirPalavra(a, "</X>", "");
						std::string b = a;
						b = Extern_Reader::StringManager::SubstituirPalavra(b, "<X>", "");
						tokens.push_back(b);
					}
					else if (Extern_Reader::StringManager::SeContemTexto(token, "<Y>"))
					{
						std::string a = Extern_Reader::StringManager::SubstituirPalavra(token, "<Y>", "");
						a = Extern_Reader::StringManager::SubstituirPalavra(a, "</Y>", "");
						std::string b = a;
						b = Extern_Reader::StringManager::SubstituirPalavra(b, "<Y>", "");
						tokens.push_back(b);
					}
					else if (Extern_Reader::StringManager::SeContemTexto(token, "<Z>"))
					{
						std::string a = Extern_Reader::StringManager::SubstituirPalavra(token, "<Z>", "");
						a = Extern_Reader::StringManager::SubstituirPalavra(a, "</Z>", "");
						std::string b = a;
						b = Extern_Reader::StringManager::SubstituirPalavra(b, "<Z>", "");
						tokens.push_back(b);
					}
					else if (Extern_Reader::StringManager::SeContemTexto(token, "<Pitch>"))
					{
						std::string a = Extern_Reader::StringManager::SubstituirPalavra(token, "<Pitch>", "");
						a = Extern_Reader::StringManager::SubstituirPalavra(a, "</Pitch>", "");
						std::string b = a;
						b = Extern_Reader::StringManager::SubstituirPalavra(b, "<Pitch>", "");
						tokens.push_back(b);
					}
					else if (Extern_Reader::StringManager::SeContemTexto(token, "<Roll>"))
					{
						std::string a = Extern_Reader::StringManager::SubstituirPalavra(token, "<Roll>", "");
						a = Extern_Reader::StringManager::SubstituirPalavra(a, "</Roll>", "");
						std::string b = a;
						b = Extern_Reader::StringManager::SubstituirPalavra(b, "<Roll>", "");
						tokens.push_back(b);
					}
					else if (Extern_Reader::StringManager::SeContemTexto(token, "<Yaw>"))
					{
						std::string a = Extern_Reader::StringManager::SubstituirPalavra(token, "<Yaw>", "");
						a = Extern_Reader::StringManager::SubstituirPalavra(a, "</Yaw>", "");
						std::string b = a;
						b = Extern_Reader::StringManager::SubstituirPalavra(b, "<Yaw>", "");
						tokens.push_back(b);
					}
					//--------------------------------------------------------------
					else if (Extern_Reader::StringManager::SeContemTexto(token, "<ModelHash>"))
					{
						std::string a = Extern_Reader::StringManager::SubstituirPalavra(token, "<ModelHash>", "");
						a = Extern_Reader::StringManager::SubstituirPalavra(a, "</ModelHash>", "");
						std::string b = a;
						b = Extern_Reader::StringManager::SubstituirPalavra(b, "<ModelHash>", "");
						tokens.push_back(b);
					}
					else if (Extern_Reader::StringManager::SeContemTexto(token, "<HashName>"))
					{
						std::string a = Extern_Reader::StringManager::SubstituirPalavra(token, "<HashName>", "");
						a = Extern_Reader::StringManager::SubstituirPalavra(a, "</HashName>", "");
						std::string b = a;
						b = Extern_Reader::StringManager::SubstituirPalavra(b, "<HashName>", "");
						tokens.push_back(b);
					}
				}
			}
			return tokens;
		}
		void SpawnXML(std::string XMLpath, std::vector<std::string> vector, GTA::Spawn_Struct Estrutura)
		{
			//Exemplo::
			//GTA::Spawn_Struct A;
			//Menyoo::Carregar::SpawnXML(".\\MapaMenyoo.xml", Menyoo::Carregar::PegarValores(".\\MapaMenyoo.xml"), A);
			//cout << "Hash = " << Estrutura.Hash << endl <<
			//"Modelo = " << Estrutura.Model << endl <<
				//"PosX = " << Estrutura.PosX << endl <<
				//"PosY = " << Estrutura.PosY << endl <<
				//"PosZ = " << Estrutura.PosZ << endl <<
				//"RotX = " << Estrutura.RotX << endl <<
				//"RotY = " << Estrutura.RotY << endl <<
				//"RotZ = " << Estrutura.RotZ << endl <<
			std::vector<std::string> A = PegarValores(XMLpath);
			for (int i = 3; i <= Extern_Reader::ArquivoTXT::TamanhoDoVector(A); i++)
			{
				if (i <= (Extern_Reader::ArquivoTXT::TamanhoDoVector(A) + 3))
				{
					Estrutura.Hash = std::strtoul(A[i].c_str(), NULL, 16);
					Estrutura.Model = A[i + 1];
					Estrutura.PosX = stof(A[i + 2]);
					Estrutura.PosY = stof(A[i + 3]);
					Estrutura.PosZ = stof(A[i + 4]);
					Estrutura.RotX = stof(A[i + 5]);
					Estrutura.RotY = stof(A[i + 6]);
					Estrutura.RotZ = stof(A[i + 7]);
					i++;
					i++;
					i++;
					i++;
					i++;
					i++;
					i++;
					/*
					cout << "Hash = " << Estrutura.Hash << endl <<
					"Modelo = " << Estrutura.Model << endl <<
					"PosX = " << Estrutura.PosX << endl <<
					"PosY = " << Estrutura.PosY << endl <<
					"PosZ = " << Estrutura.PosZ << endl <<
					"RotX = " << Estrutura.RotX << endl <<
					"RotY = " << Estrutura.RotY << endl <<
					"RotZ = " << Estrutura.RotZ << endl <<
					"-------------------------------" << endl;;
					*/
				}
			}
		}
	}
}
namespace Criptografia
{
	namespace XOR
	{
		std::string Encriptografar(std::string nString)
		{
			//Exemplo:		Criptografia::XOR::Encriptografar("Eduardo Bresolin espert em C")
			const int KEY = 3;
			int strLen = (nString.length());
			char* cString = (char*)(nString.c_str());
			for (int i = 0; i < strLen; i++)
			{
				*(cString + i) = (*(cString + i) ^ KEY);
			}
			return cString;
		}
		string Descriptografar(std::string nString)
		{
			//Exemplo:		Criptografia::XOR::Descriptografar("Fgvbqgl#Aqfplojm#fpsfqw#fn#@")
			const int KEY = 3;
			int strLen = (nString.length());
			char* cString = (char*)(nString.c_str());
			for (int i = 0; i < strLen; i++)
			{
				*(cString + i) = (*(cString + i) ^ KEY);
			}
			return cString;
		}
	}
	namespace Ceasar
	{
		string Encriptografar(string text)
		{
			//Exemplo		Criptografia::Ceasar::Encriptografar("Eduardo Bresolin espert em C") 
			string s = text;
			string t;
			std::transform(s.begin(), s.end(), s.begin(), ::toupper);
			for (int i = 0;i < s.size();i++)
				t += (s[i] - 'A' + 3) % 26 + 'A';
			return t;
		}
		string Descriptografar(string text, bool PrimeiraMaiuscula = true)
		{
			//Exemplo		Criptografia::Ceasar::Descriptografar("HGXDUGR=EUHVROLQ=HVSHUW=HP=F") 
			string s = text;
			string t;
			for (int i = 0;i < s.size();i++)
			{
				if (s[i] == '=')
					t += ' ';
				else
					t += (s[i] - 'A' - 3 + 26) % 26 + 'A';
			}
			if (PrimeiraMaiuscula)
				for (int i = 1; i <= t.size(); i++)
					t[i] = tolower(t[i]);
			return t;
		}
	}
	namespace Hash
	{
		//Irreversivel, nao tem como converter um hash pra string
		std::string Hash(string A)
		{
			return to_string(std::hash<std::string>{}(A));
		}
		 
	}
}


 



 

int main()
{ 
	return 0;
}
