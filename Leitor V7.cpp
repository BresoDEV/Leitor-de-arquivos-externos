//  ______        _                        _____                    _
// |  ____|      | |                      |  __ \                  | |
// | |__   __  __| |_   ___  _ __  _ __   | |__) |  ___   __ _   __| |  ___  _ __
// |  __|  \ \/ /| __| / _ \| '__|| '_ \  |  _  /  / _ \ / _` | / _` | / _ \| '__|
// | |____  >  < | |_ |  __/| |   | | | | | | \ \ |  __/| (_| || (_| ||  __/| |
// |______|/_/\_\ \__| \___||_|   |_| |_| |_|  \_\ \___| \__,_| \__,_| \___||_|
// 
//
//    _     _
//   (c).-.(c)
//    / ._. \
//  __\( Y )/__
// (_.-/'-'\-._)
//    || A ||
//  _.' `-' '._
// (.-./`-'\.-.)
//  `-'     `-'
//  ____                           _____   ______ __      __
// |  _ \                         |  __ \ |  ____|\ \    / /
// | |_) | _ __   ___  ___   ___  | |  | || |__    \ \  / /
// |  _ < | '__| / _ \/ __| / _ \ | |  | ||  __|    \ \/ /
// | |_) || |   |  __/\__ \| (_) || |__| || |____    \  /
// |____/ |_|    \___||___/ \___/ |_____/ |______|    \/
#include<iostream>
#include<stdio.h>
#include <cmath>
#include<fstream>
#include<string>
#include <vector>
#include <windows.h>  
#include <chrono>   
#include <sstream>  
#include <filesystem>
#include <algorithm> 
#include <random>
#include <urlmon.h>
#include <cstdio>
#include <string>
#include <cstring>
#include <wininet.h>
#pragma comment(lib,"Wininet.lib")
#pragma comment(lib, "urlmon.lib")
#include <direct.h>
#include <cstdlib>
#include <Iphlpapi.h>
#include <Assert.h>
#pragma comment(lib, "iphlpapi.lib")
#pragma warning(disable:4996)//Desabilita os erros de SNPRINTF 
#include <tchar.h> 
#include <shlobj_core.h> 


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
			{
				file.close();
				return true;
			}
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
			mkdir(Diretorio);
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
				/*
				int Ponteiro;
	int sizeSpawnTXT;
	std::vector<std::string> ListaProps;
	Extern_Reader::ArquivoTXT::TXTFilePath = ".\\BresoMenu\\Props\\ListaDeProps.txt";
	ListaProps = Extern_Reader::ArquivoTXT::String::PegarValores();
	sizeSpawnTXT = Extern_Reader::ArquivoTXT::TamanhoDoVector(ListaProps);
	Ponteiro = i;
	addOption(ListaProps[i].c_str(), []
		{
			Criar_Objeto(ListaProps[Ponteiro].c_str());
		}
	);
	*/
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
		vector<string> ListVector(string arquivo, int index, int itensLinha, int& TamanhoDoVector, char Separador = ',')
		{
			/*
			 Le varios parametros de uma linha, e retorna qual voce quer, o primeiro, segundo, terceiro, etc...
			Arquivo:
			Eduardo,BresoDEV,GTAV,10
			Pierre,Gordo,GTAV,20
			Pedro,Codorna,Freefire,30
			Fausto,Faustao,GTA4,40
			Augusto,Gugu,Red Dead Redemption,50
			Joao,Jao do Caminhao,Super Mario,60
			int tamanho; //ponteiro que vai retornar o tamanho do vector, pra usar no laço FOR
			int qual_ler = 1; //Primeiro valor de cada linha
			int total_de_itens_por_linha = 4; //cada linha tem 4 parametros
			vector<string> AAA = ListVector(".\\Nomes.txt", qual_ler, total_de_itens_por_linha, tamanho);
			for (int i = 0; i <= tamanho; i++)
				cout << AAA[i] << endl;
			*/
			vector<string> VetorTemporario;
			vector<string> VetorTemporario_2;
			ifstream __arquivo(arquivo);
			for (string line; getline(__arquivo, line);)
			{
				istringstream _contador_1{ line };
				string ___linha;
				while (getline(_contador_1, ___linha, Separador))
					VetorTemporario.push_back(___linha);
			}
			for (int i2 = 0; i2 <= (VetorTemporario.size() - 1); i2 += itensLinha)
				VetorTemporario_2.push_back(VetorTemporario[i2 + (index - 1)]);
			TamanhoDoVector = VetorTemporario_2.size() - 1;
			return VetorTemporario_2;
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

		void ExcluirSessaoToda(string Sessao)
		{
			//Exemplo:
			// 	   ExcluirSessaoToda("oi");
			//[oi] <-- exclue tudo oque tem dentro dessa chave
			//texto=abc   
			WritePrivateProfileStringA(Sessao.c_str(), NULL, "", INIFilePath.c_str());
		}

		void ExcluirParametro(string Sessao, string parametro)
		{
			//Exemplo:
			// 	   ExcluirParemtro("oi", "texto");
			//[oi]
			//texto=abc  <-- exclue esse so 
			WritePrivateProfileStringA(Sessao.c_str(), parametro.c_str(), NULL, INIFilePath.c_str());
		}

		bool ParametroExiste(string Sessao, string parametro)
		{ 
			char buf[100];
			int a = GetPrivateProfileStringA(Sessao.c_str(), parametro.c_str(), 0, buf, 100, INIFilePath.c_str());
			if (a == 0)
				return false;
			else
				return true;
		}

		bool ParametroVAZIO(string Sessao, string parametro)
		{ 
			char buf[100];
			if (ParametroExiste(Sessao, parametro))
			{
				GetPrivateProfileStringA(Sessao.c_str(), parametro.c_str(), "", buf, 100, INIFilePath.c_str());
				if (buf == "") return true;
				else return false;
			}
			else return true;
		}



		bool SessaoExiste(string Sessao)
		{ 
			std::vector<std::string> TempVECTOR;
			ifstream imput(INIFilePath);
			string textolido;
			for (string line; getline(imput, line);)
				TempVECTOR.push_back(line);

			for (int i = 0; i <= (TempVECTOR.size() - 1); i++)
			{
				if (TempVECTOR[i] == "[" + Sessao + "]")
					return true;
			}
			return false;
		}
	}
	namespace WEB
	{
		enum IP_Infos
		{
			status,
			country,
			countryCode,
			region,
			regionName,
			city,
			lat,
			lon,
			timezone,
			isp,
			org,
			as,
			query,
		};
		vector<string> Buscar_Lista(const char* Link_Lista)
		{
			/*
			Como usar:
			vector<string> Lista_HASH = Buscar_Lista("https://pastebin.com/raw/WwvvCpGG");
			for (int i = 0; i <= (Lista_HASH.size() - 2); i++)
			{
				cout << Lista_HASH[i] << endl;;
			}
			*/
			IStream* stream;
			const char* URL = Link_Lista;
			URLOpenBlockingStreamA(0, URL, &stream, 0, 0);
			char buff[100];
			string s;
			unsigned long bytesRead;
			while (true)
			{
				stream->Read(buff, 100, &bytesRead);
				if (0U == bytesRead)
				{
					break;
				}
				s.append(buff, bytesRead);
			};
			stream->Release();
			string oi = s; //tudo misturado 
			string R = "\r";
			string N = "\n";
			string vazio = "";
			string espaco = " ";
			string ZeroX = "0x";
			string ZeroXVirg = ",0x";
			string Virg = ",";
			size_t start_pos = 0;
			while ((start_pos = oi.find(R, start_pos)) != std::string::npos) {
				oi.replace(start_pos, R.length(), vazio);
				start_pos += vazio.length();
			}
			start_pos = 0;
			while ((start_pos = oi.find(N, start_pos)) != std::string::npos) {
				oi.replace(start_pos, N.length(), Virg);
				start_pos += Virg.length();
			}
			start_pos = 0;
			while ((start_pos = oi.find(espaco, start_pos)) != std::string::npos) {
				oi.replace(start_pos, espaco.length(), vazio);
				start_pos += vazio.length();
			}
			start_pos = 0;
			while ((start_pos = oi.find(ZeroX, start_pos)) != std::string::npos) {
				oi.replace(start_pos, ZeroX.length(), ZeroXVirg);
				start_pos += ZeroXVirg.length();
			}
			vector<string> result;
			int cutAt;
			while ((cutAt = oi.find_first_of(",")) != oi.npos) {
				if (cutAt > 0) {
					result.push_back(oi.substr(0, cutAt));
				}
				oi = oi.substr(cutAt + 1);
			}
			if (oi.length() > 0) {
				result.push_back(oi);
			}
			return result;
		}

		vector<string> Buscar_Lista_Mais_Itens(const char* Link_Lista, int numParametrosPorLinha, int index, string delimitador = ",")
		{
			/*
			Como usar:
			Link da lista, numero de itens por linha, index do item que quer buscar da linha, separador

			vector<string> Lista = Buscar_Lista_Mais_Itens("https://pastebin.com/raw/f9Ki3Jfc", 6, 2);
			for (int i = 0; i <= (Lista.size() - 1); i++)
				cout << Lista[i] << endl;

			*/
			IStream* stream;
			const char* URL = Link_Lista;
			URLOpenBlockingStreamA(0, URL, &stream, 0, 0);
			char buff[100];
			string s;
			unsigned long bytesRead;
			while (true)
			{
				stream->Read(buff, 100, &bytesRead);
				if (0U == bytesRead)
				{
					break;
				}
				s.append(buff, bytesRead);
			};
			stream->Release();
			string TudoJunto = Extern_Reader::StringManager::SubstituirPalavra(s, "\r\n", delimitador);
			string space_delimiter = delimitador;
			vector<string> words{};
			//int numPam = numPar - 1;
			size_t pos = 0;
			while ((pos = TudoJunto.find(space_delimiter)) != string::npos) {
				words.push_back(TudoJunto.substr(0, pos));
				TudoJunto.erase(0, pos + space_delimiter.length());
			}
			//words array com todos valores

			vector<string> Separados;
			for (int i = (index - 1); i <= (words.size() - 1); i += numParametrosPorLinha)
				Separados.push_back(words[i]);

			return Separados;

		}

		namespace GeoLoc
		{
			/*
			Como usar:

			//Formato de info unica
			cout << GeoLoc::BuscarInfos("187.103.255.171", GeoLoc::status) << endl;
			cout << GeoLoc::BuscarInfos("187.103.255.171", GeoLoc::country) << endl;
			cout << GeoLoc::BuscarInfos("187.103.255.171", GeoLoc::countryCode) << endl;
			cout << GeoLoc::BuscarInfos("187.103.255.171", GeoLoc::region) << endl;
			cout << GeoLoc::BuscarInfos("187.103.255.171", GeoLoc::regionName) << endl;
			cout << GeoLoc::BuscarInfos("187.103.255.171", GeoLoc::city) << endl;
			cout << GeoLoc::BuscarInfos("187.103.255.171", GeoLoc::zip) << endl;
			cout << GeoLoc::BuscarInfos("187.103.255.171", GeoLoc::lat) << endl;
			cout << GeoLoc::BuscarInfos("187.103.255.171", GeoLoc::lon) << endl;
			cout << GeoLoc::BuscarInfos("187.103.255.171", GeoLoc::timezone) << endl;
			cout << GeoLoc::BuscarInfos("187.103.255.171", GeoLoc::isp) << endl;
			cout << GeoLoc::BuscarInfos("187.103.255.171", GeoLoc::org) << endl;



			//Formato de Lista Completa
			vector<string> Valores;
			for (int i = 0; i <= 11; i++)
				Valores.push_back(GeoLoc::BuscarInfos("187.103.255.171", i));

			for (int i = 0; i <= 11; i++)
				cout << Valores[i] << endl;

				*/
			enum ID_info
			{
				status, country, countryCode, region, regionName, city, zip, lat, lon, timezone, isp, org
			};

			string BuscarInfos(const char* IP, int Qual_valor_retorna = status)
			{
				IStream* textoCompleto;
				//Junta o IP com o link original
				char chartemporario[5000];
				snprintf(chartemporario, 5000, "http://ip-api.com/php/%s", IP);
				const char* URL = chartemporario;
				//====================================================
				URLOpenBlockingStreamA(0, URL, &textoCompleto, 0, 0);
				char buff[100];
				string TextoLido_sem_formatacao;
				unsigned long bitesLeitura;
				while (true)
				{
					textoCompleto->Read(buff, 100, &bitesLeitura);
					if (0U == bitesLeitura)//Le o arquivo ate o final
						break;
					TextoLido_sem_formatacao.append(buff, bitesLeitura);
				}
				textoCompleto->Release();
				//Vector que vai armazenar os dados por item
				vector<string> Formatado{};
				string Virgula = ",";
				string Vazio = "";
				vector<string> Substituicao = { "\""
				,"a:14:{s:6:,status,;s:7:,"
				,",;s:7:,country,;s:6:",";s:11:,countryCode,;s:2:,",",;s:6:,region,;s:2:"
				,";s:10:,regionName,;s:17:," ,";s:4:,city,;s:13:," ,";s:3:,zip,;s:0:,,;s:3:,lat,;d:"
				,";s:3:,lon,;d:"/*virgula*/ , ";s:8:,timezone,;s:17:" , ";s:3:,isp,;s:15:,"
				, ";s:3:,org,;s:15:," , ";s:2:,as,;s:23:," , ";s:5:,query,;s:15:," , ",;}"
				};

				size_t inicio = 0;
				while ((inicio = TextoLido_sem_formatacao.find(Substituicao[0], inicio)) != std::string::npos)
				{
					TextoLido_sem_formatacao.replace(inicio, Substituicao[0].length(), Virgula);
					inicio += Virgula.length();
				}

				for (int i = 0; i <= (Substituicao.size() - 1); i++)
				{
					if (i == 8)
						break;
					size_t inicio = 0;
					while ((inicio = TextoLido_sem_formatacao.find(Substituicao[i], inicio)) != std::string::npos)
					{
						TextoLido_sem_formatacao.replace(inicio, Substituicao[i].length(), Vazio);
						inicio += Vazio.length();
					}
				}
				inicio = 0;
				while ((inicio = TextoLido_sem_formatacao.find(Substituicao[8], inicio)) != std::string::npos)
				{
					TextoLido_sem_formatacao.replace(inicio, Substituicao[8].length(), Virgula);
					inicio += Virgula.length();
				}

				for (int i = 9; i <= (Substituicao.size() - 1); i++)
				{
					size_t inicio = 0;
					while ((inicio = TextoLido_sem_formatacao.find(Substituicao[i], inicio)) != std::string::npos)
					{
						TextoLido_sem_formatacao.replace(inicio, Substituicao[i].length(), Vazio);
						inicio += Vazio.length();
					}
				}

				size_t posicaoString = 0;
				while ((posicaoString = TextoLido_sem_formatacao.find(Virgula)) != string::npos) {
					Formatado.push_back(TextoLido_sem_formatacao.substr(0, posicaoString));
					TextoLido_sem_formatacao.erase(0, posicaoString + Virgula.length());
				}
				return Formatado[Qual_valor_retorna];

			}
		}
		bool CheckConexao()
		{
			if (InternetCheckConnection(L"http://www.google.com", FLAG_ICC_FORCE_CONNECTION, 0))
				return true;
			else
				return false;
		}
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

		void BaixarArquivo_Melhorado(string link, string pasta, string pathSaida)
		{
			mkdir(pasta.c_str());
			int len;
			int slength = (int)link.length() + 1;
			len = MultiByteToWideChar(CP_ACP, 0, link.c_str(), slength, 0, 0);
			wchar_t* buf = new wchar_t[len];
			MultiByteToWideChar(CP_ACP, 0, link.c_str(), slength, buf, len);
			std::wstring r(buf);
			delete[] buf;
			string aaa = pathSaida;
			ifstream myfile(aaa);
			if (myfile)
			{
				myfile.close();
				remove(aaa.c_str());
			}
			LPCWSTR result = r.c_str();
			slength = (int)pathSaida.length() + 1;
			len = MultiByteToWideChar(CP_ACP, 0, pathSaida.c_str(), slength, 0, 0);
			wchar_t* buf2 = new wchar_t[len];
			MultiByteToWideChar(CP_ACP, 0, pathSaida.c_str(), slength, buf2, len);
			std::wstring r2(buf2);
			delete[] buf2;
			LPCTSTR Url = result;
			LPCTSTR	File = r2.c_str();
			URLDownloadToFile(0, Url, File, 0, 0);
			while (!myfile) {}
		}

		std::vector<std::string> Obter_IP_Info(string ip)
		{
			/*
			Como Usar:
				string IP = "187.103.255.171";
				int tamanho = Extern_Reader::ArquivoTXT::TamanhoDoVector(Extern_Reader::WEB::Obter_IP_Info(IP));
				for (int i = 0; i <= tamanho; i++)
				{
					cout << Extern_Reader::WEB::Obter_IP_Info(IP)[i] << endl;
				i++;
			}
			exemplo 2:
			std::vector<std::string> IP = Extern_Reader::WEB::Obter_IP_Info("187.103.255.171");
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
			if (Extern_Reader::Arquivos::ArquivoExiste(ip + ".txt"))
			{
				std::vector<string> TempVECTOR;
				vector<string> tokens;
				ifstream imput(ip + ".txt");
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
				Extern_Reader::WEB::BaixarArquivo("http://ip-api.com/php/" + ip, ip + ".txt");
				goto inicio;
			}
		}
		char* Ler_MAC(int QualMac)
		{
			//Como usar
			//char* pMac = Extern_Reader::WEB::Ler_MAC(1);
			//char* pMac2 = Extern_Reader::WEB::Ler_MAC(2);
			//free(pMac);
			//free(pMac2);
			PIP_ADAPTER_INFO AdapterInfo;
			DWORD dwBufLen = sizeof(IP_ADAPTER_INFO);
			char* mac_addr = (char*)malloc(18);
			AdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
			GetAdaptersInfo(AdapterInfo, &dwBufLen);
			AdapterInfo = (IP_ADAPTER_INFO*)malloc(dwBufLen);
			GetAdaptersInfo(AdapterInfo, &dwBufLen);
			PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
			if (QualMac == 1)
				pAdapterInfo = pAdapterInfo->Next;
			if (QualMac == 2)
			{
				pAdapterInfo = pAdapterInfo->Next; pAdapterInfo = pAdapterInfo->Next;
			}
			sprintf(mac_addr, "%02X:%02X:%02X:%02X:%02X:%02X", pAdapterInfo->Address[0], pAdapterInfo->Address[1], pAdapterInfo->Address[2], pAdapterInfo->Address[3], pAdapterInfo->Address[4], pAdapterInfo->Address[5]);;
			//printf("\n");
			return mac_addr;
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
		int GetResolucao_X()
		{
			RECT desktop;
			const HWND hDesktop = GetDesktopWindow();
			GetWindowRect(hDesktop, &desktop);
			return desktop.right;
		}
		int GetResolucao_Y()
		{
			RECT desktop;
			const HWND hDesktop = GetDesktopWindow();
			GetWindowRect(hDesktop, &desktop);
			return desktop.bottom;
		}
		int Get_X_Centro_da_Tela()
		{
			RECT desktop;
			const HWND hDesktop = GetDesktopWindow();
			GetWindowRect(hDesktop, &desktop);
			return desktop.right / 2;
		}
		int Get_Y_Centro_da_Tela()
		{
			RECT desktop;
			const HWND hDesktop = GetDesktopWindow();
			GetWindowRect(hDesktop, &desktop);
			return desktop.bottom / 2;
		}
		void MoverMouse_Centro_Da_Tela()
		{
			MoverMouse(Get_X_Centro_da_Tela(), Get_Y_Centro_da_Tela());
		}
		int GetMouse_X()
		{
			POINT p;
			GetCursorPos(&p);
			return p.x;
		}
		int GetMouse_Y()
		{
			POINT p;
			GetCursorPos(&p);
			return p.y;
		}
	}
	namespace JSON
	{
		/*
		{
  "squadName": "Super hero squad",
  "homeTown": "Metro City",
  "formed": 2016,
  "secretBase": 100.876,
  "active": true,
  "members": [
	{
	  "name": "Molecule Man",
	  "age": 29,
	  "secretIdentity": "Dan Jukes",
	  "powers": [
		"Radiation resistance",
		"Turning tiny",
		"Radiation blast"
	  ]
	},
	{
	  "name": "Breso",
	  "age": 29,
	  "secretIdentity": "Dan Jukes",
	  "powers": [
		"Radiation resistance",
		"Turning tiny",
		"Radiation blast"
	  ]
	},
}
*/
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
	namespace DataHora
	{
		namespace INT
		{
			int Ano()
			{
				std::time_t t = std::time(0);
				std::tm* now = std::localtime(&t);
				return (now->tm_year + 1900);
			}
			int Mes()
			{
				std::time_t t = std::time(0);
				std::tm* now = std::localtime(&t);
				return (now->tm_mon + 1);
			}
			int Dia()
			{
				std::time_t t = std::time(0);
				std::tm* now = std::localtime(&t);
				return (now->tm_mday);
			}
			int Hora()
			{
				struct tm current_tm;
				char chLogBuff[5000];
				char chParameters[5000];
				time_t current_time = time(NULL);
				localtime_s(&current_tm, &current_time);
				return current_tm.tm_hour;
			}
			int Minutos()
			{
				struct tm current_tm;
				char chLogBuff[5000];
				char chParameters[5000];
				time_t current_time = time(NULL);
				localtime_s(&current_tm, &current_time);
				return current_tm.tm_min;
			}
			int Segundos()
			{
				struct tm current_tm;
				char chLogBuff[5000];
				char chParameters[5000];
				time_t current_time = time(NULL);
				localtime_s(&current_tm, &current_time);
				return current_tm.tm_sec;
			}
		}
		namespace STRING
		{
			string Hora()
			{
				struct tm current_tm;
				char chLogBuff[5000];
				char chParameters[5000];
				time_t current_time = time(NULL);
				localtime_s(&current_tm, &current_time);
				char szTimestamp[30];
				sprintf_s(szTimestamp, "%02d", current_tm.tm_hour);
				return szTimestamp;
			}
			string Minutos()
			{
				struct tm current_tm;
				char chLogBuff[5000];
				char chParameters[5000];
				time_t current_time = time(NULL);
				localtime_s(&current_tm, &current_time);
				char szTimestamp[30];
				sprintf_s(szTimestamp, "%02d", current_tm.tm_min);
				return szTimestamp;
			}
			string Segundos()
			{
				struct tm current_tm;
				char chLogBuff[5000];
				char chParameters[5000];
				time_t current_time = time(NULL);
				localtime_s(&current_tm, &current_time);
				char szTimestamp[30];
				sprintf_s(szTimestamp, "%02d", current_tm.tm_sec);
				return szTimestamp;
			}
			string HorarioCompleto()
			{
				struct tm current_tm;
				char chLogBuff[5000];
				char chParameters[5000];
				time_t current_time = time(NULL);
				localtime_s(&current_tm, &current_time);
				char szTimestamp[30];
				sprintf_s(szTimestamp, "%02d:%02d:%02d", current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec);
				return szTimestamp;
			}
			string Ano()
			{
				std::time_t t = std::time(0);
				std::tm* now = std::localtime(&t);
				char szTimestamp[30];
				sprintf_s(szTimestamp, "%02d", (now->tm_year + 1900));
				return szTimestamp;
			}
			string Mes()
			{
				std::time_t t = std::time(0);
				std::tm* now = std::localtime(&t);
				char szTimestamp[30];
				sprintf_s(szTimestamp, "%02d", (now->tm_mon + 1));
				return szTimestamp;
			}
			string Dia()
			{
				std::time_t t = std::time(0);
				std::tm* now = std::localtime(&t);
				char szTimestamp[30];
				sprintf_s(szTimestamp, "%02d", (now->tm_mday));
				return szTimestamp;
			}
		}
	}
	namespace Leitor_de_Arquivos
	{
		namespace Ler
		{
			int BuscarInt(std::string info, std::string fullPath, std::string separador = "=")
			{
				//Arquivo de texto
				//MeuItem=1234
				//
				//Chamada:
				//cout << BuscarInt("MeuItem", Extern_Reader::PastasPC::Documentos() + "a.txt");
				int state = 1;
				std::ifstream file;
				bool nextLine = false;
				std::string afterEqual;
				file.open(fullPath);
				std::string line = "";
				if (file.is_open())
				{
					while (std::getline(file, line))
					{
						if (nextLine)
						{
							std::size_t found = line.find(separador);
							if (line.find(separador) != std::string::npos)
							{
								for (std::size_t i = (found + 1); i < (line.size()); i++)
									afterEqual += line[i];
								state = std::stoi(afterEqual);
								nextLine = false;
							}
						}
						if (line == info)
							nextLine = true;
					}
				}
				return (state);
			}
			float BuscarFloat(std::string info, std::string fullPath, std::string separador = "=")
			{
				//Arquivo de texto
				//MeuItem=10.4
				//
				//Chamada:
				//cout << BuscarFloat("MeuItem", Extern_Reader::PastasPC::Documentos() + "a.txt");
				float state = 1.0f;
				std::ifstream file;
				bool nextLine = false;
				std::string afterEqual;
				file.open(fullPath);
				std::string line = "";
				if (file.is_open())
				{
					while (std::getline(file, line))
					{
						if (nextLine)
						{
							std::size_t found = line.find(separador);
							if (line.find(separador) != std::string::npos)
							{
								for (std::size_t i = (found + 1); i < (line.size()); i++)
									afterEqual += line[i];
								state = std::stof(afterEqual);
								nextLine = false;
							}
						}
						if (line == info)
							nextLine = true;
					}
				}
				return (state);
			}
			std::string BuscarString(std::string info, std::string fullPath, std::string separador = "=")
			{
				//Arquivo de texto
				//MeuItem=Meu texto
				//
				//Chamada:
				//cout << BuscarString("MeuItem", Extern_Reader::PastasPC::Documentos() + "a.txt");
				std::string state = "\0";
				std::ifstream file;
				bool nextLine = false;
				std::string afterEqual;
				file.open(fullPath);
				std::string line = "";
				if (file.is_open())
				{
					while (std::getline(file, line))
					{
						if (nextLine)
						{
							std::size_t found = line.find("=");
							if (line.find("=") != std::string::npos)
							{
								for (std::size_t i = (found + 1); i < (line.size()); i++)
									afterEqual += line[i];
								state = afterEqual;
								nextLine = false;
							}
						}
						if (line == info)
							nextLine = true;
					}
				} return (state);
			}
		}
		namespace Gravar
		{
			void GravarInt(std::string info, string fullPath, int valor, string separador = "=")
			{
				//Chamada:
				//cout << GravarInt("MeuItem", Extern_Reader::PastasPC::Documentos() + "a.txt", 1020);
				std::string buffer_file;
				std::fstream file;
				std::string afterEqual;
				file.open(fullPath, std::ios::in);
				std::string line = "";
				if (file.is_open())
				{
					while (std::getline(file, line))
						buffer_file += (line + "\n");
				}
				file.close();
				file.open(fullPath, std::ios::out);
				std::size_t found = buffer_file.find(info.c_str());
				std::size_t found2 = buffer_file.find(separador, found + 1);
				if (buffer_file[found2 + 1] == '\n')
					buffer_file.insert(found2 + 1, std::to_string(valor));
				else
				{
					std::size_t found3 = buffer_file.find("\n", found2);
					buffer_file.erase((buffer_file.begin() + found2 + 1), (buffer_file.begin() + found3));
					buffer_file.insert(found2 + 1, std::to_string(valor));
				}
				file << buffer_file;
				file.close();
			}
			void GravarFloat(std::string info, string fullPath, float valor, string separador = "=")
			{
				//Chamada:
				//cout << GravarFloat("MeuItem", Extern_Reader::PastasPC::Documentos() + "a.txt", 123.02);
				std::string buffer_file;
				std::fstream file;
				std::string afterEqual;
				file.open(fullPath, std::ios::in);
				std::string line = "";
				if (file.is_open())
				{
					while (std::getline(file, line))
						buffer_file += (line + "\n");
				}
				file.close();
				file.open(fullPath, std::ios::out);
				std::size_t found = buffer_file.find(info.c_str());
				std::size_t found2 = buffer_file.find(separador, found + 1);
				if (buffer_file[found2 + 1] == '\n')
					buffer_file.insert(found2 + 1, std::to_string(valor));
				else
				{
					std::size_t found3 = buffer_file.find("\n", found2);
					buffer_file.erase((buffer_file.begin() + found2 + 1), (buffer_file.begin() + found3));
					buffer_file.insert(found2 + 1, std::to_string(valor));
				}
				file << buffer_file;
				file.close();
			}
			void GravarString(std::string info, string fullPath, string valor, string separador = "=")
			{
				//Chamada:
				//cout << GravarInt("MeuItem", Extern_Reader::PastasPC::Documentos() + "a.txt", "ola");
				std::string buffer_file;
				std::fstream file;
				std::string afterEqual;
				file.open(fullPath, std::ios::in);
				std::string line = "";
				if (file.is_open())
				{
					while (std::getline(file, line))
						buffer_file += (line + "\n");
				}
				file.close();
				file.open(fullPath, std::ios::out);
				std::size_t found = buffer_file.find(info.c_str());
				std::size_t found2 = buffer_file.find(separador, found + 1);
				if (buffer_file[found2 + 1] == '\n')
					buffer_file.insert(found2 + 1, valor);
				else
				{
					std::size_t found3 = buffer_file.find("\n", found2);
					buffer_file.erase((buffer_file.begin() + found2 + 1), (buffer_file.begin() + found3));
					buffer_file.insert(found2 + 1, valor);
				}
				file << buffer_file;
				file.close();
			}
		}
	}
	namespace PastasPC
	{

		std::string AppData()
		{
			PWSTR appdata = NULL;
			if (SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_CREATE, NULL, &appdata) == S_OK) {
				char dest[MAX_PATH];
				wcstombs(dest, appdata, MAX_PATH);
				return dest;
			}
		}

		std::string Documentos()
		{
			static char env[256];
			const DWORD ret = GetEnvironmentVariableA("USERPROFILE", env, 256);
			std::string path = "\\Documents\\";
			std::string pastaDOc = env + path;
			return pastaDOc;
		}
		std::string Imagens()
		{
			static char env[256];
			const DWORD ret = GetEnvironmentVariableA("USERPROFILE", env, 256);
			std::string path = "\\Pictures\\";
			std::string pastaDOc = env + path;
			return pastaDOc;
		}
		std::string Downloads()
		{
			static char env[256];
			const DWORD ret = GetEnvironmentVariableA("USERPROFILE", env, 256);
			std::string path = "\\Downloads\\";
			std::string pastaDOc = env + path;
			return pastaDOc;
		}
		std::string Videos()
		{
			static char env[256];
			const DWORD ret = GetEnvironmentVariableA("USERPROFILE", env, 256);
			std::string path = "\\Videos\\";
			std::string pastaDOc = env + path;
			return pastaDOc;
		}
	}
	namespace XML
	{
		string Buscar_Linha_Abaixo(string Diretorio, string referencia, int numeroDeLinhasAbaixo)
		{
			/*
			Busca outras linhas abaixo, a partir de uma referencia
			Ex XML:
			<ReferenceCoords>
			<X>4991.55566</X>
			<Y>-5721.46191</Y>
			<Z>19.8802071</Z>
			</ReferenceCoords>
			Chamada da funcao:
			cout << Leitor_Menyoo::Buscar_Linha_Abaixo(".\\Mapa.xml","ReferenceCoords", 2);
			Nesse caso, pega a referencia e pula 2 linhas, retornando <Y>-5721.46191</Y>
			*/
			std::vector<std::string> TempVECTOR;
			ifstream imput(Diretorio);
			string textolido;
			string palavra;
			for (string line; getline(imput, line);)
			{
				if (line.find("<" + referencia + ">") != std::string::npos)
				{
					for (int i = 0; i <= (numeroDeLinhasAbaixo - 1); i++)
						getline(imput, line);
					palavra = line;
				}
			}
			return palavra;
		}
		vector<string> BuscarTodosValores(string Diretorio, string referencia)
		{
			/*Como usar:
			BUsca todos valores baseados na referencia, nao importando onde se localiza e de qual
			grupo pertence

			vector<string> Valores = Leitor_Menyoo::BuscarTodosValores(".\\Mapa.xml","X");
			for (int i = 0; i <= Valores.size() - 1; i++)
				cout << Valores[i] << endl;
			*/
			vector<string> Colecao;
			ifstream file(Diretorio);
			string palavra;
			string line;
			while (getline(file, line))
			{
				if (line.find("<" + referencia + ">") != std::string::npos)
				{
					string from = "	";
					string to = "";
					size_t start_pos = 0;
					while ((start_pos = line.find(from, start_pos)) != std::string::npos) {
						line.replace(start_pos, from.length(), to);
						start_pos += to.length();
					}
					Colecao.push_back(line);
				}
			}
			return Colecao;
		}
		vector<string> Buscar_Todas_Linhas_Abaixo(string Diretorio, string referencia, int numeroDeLinhasAbaixo)
		{
			/*
			Busca por uma referencia, e armazena todas linhas abaixo, a partir de uma referencia
			Mas armazena somente 1 valor por chave
			===========================================
			Ex XML:
			<ReferenceCoords>
			<X>4991.55566</X>
			</ReferenceCoords>
			<ReferenceCoordsDiferente>
			<X>2222.2222</X>
			</ReferenceCoordsDiferente>
			<ReferenceCoords>
			<X>1111.11111</X>
			</ReferenceCoords>
			============================================
			Chamada da funcao:

			vector<string> valores = Leitor_Menyoo::Buscar_Todas_Linhas_Abaixo(".\\Mapa.xml","ReferenceCoords", 1);
			for (int i = 0; i <= (valores.size() - 1); i++)
				cout << valores[i] << endl;
			Retotorno:
			<X>4991.55566</X>
			<X>1111.11111</X>
			============================================
			Nesse caso, pega a referencia e pula 1 linha, retornando o valor de X
			Depois continua lendo, ate achar outra referencia igual, pula 1 linha e armazena o X
			E assim por diante....Lembrando que ele nao armazena o "ReferenceCoordsDiferente", pois
			apesar de existir o X dentro, a chave principal nao bate com o "ReferenceCoords", que significa
			que pertence a outro grupo diferente, apesar do mesmo nome
			Isso serve pra buscar valores diferentes, quando existem mais de 1 chave com o mesmo nome, dentro
			de espacos diferentes
			*/
			vector<string> Colecao;
			std::vector<std::string> TempVECTOR;
			ifstream imput(Diretorio);
			string textolido;
			for (string line; getline(imput, line);)
			{
				if (line.find("<" + referencia + ">") != std::string::npos)
				{
					for (int i = 0; i <= (numeroDeLinhasAbaixo - 1); i++)
						getline(imput, line);
					Colecao.push_back(line);
				}
			}
			return Colecao;
		}
		void Gravar_Valores(string arquivo, vector<string> Cadeia, string Chave, string valor)
		{
			/*
			Cria novas entradas no XML, nao subsitue ou edita, CRIA
			Exemplo de chamada:
			Leitor_Menyoo::DiretorioMapa = ".\\MapaCadeia.xml";
			vector<string> Chaves = { "Usuarios", "Perfil" };//Quantas quiser
			Leitor_Menyoo::Gravar_Valores(".\\BancoDados.xml", Chaves, "Nome", "Eduardo");
			===========================================
			Resultado:
			<Usuarios>
				<Perfil>
					<Nome>Eduardo</Nome>
				</Perfil>
			</Usuarios>
			*/
			ofstream Arquivo;
			Arquivo.open(arquivo, std::ios_base::app);
			for (int i = 0; i <= (Cadeia.size() - 1); i++)
			{
				Arquivo << "<" + Cadeia[i] + ">" << endl;
			}
			Arquivo << "<" + Chave + ">" + valor + "</" + Chave + ">" << endl;
			for (int i = (Cadeia.size() - 1); i >= 0; i--)
			{
				Arquivo << "</" + Cadeia[i] + ">" << endl;
			}
			Arquivo.close();
		}
		string Remove_Keys(string palavra)
		{
			/*
			Remove as keys dos valores lidos, deixando apenas o valor
			Ex:
			cout << Leitor_Menyoo::Remove_Keys("</Usuarios>", Remover);
			Saida: Usuarios
			*/
			vector<string> Remover = { " ", "<", "/", ">" }; //Quantas quiser
			for (int i = 0; i <= (Remover.size() - 1); i++)
			{
				string from = Remover[i];
				string to = "";
				size_t start_pos = 0;
				while ((start_pos = palavra.find(from, start_pos)) != std::string::npos) {
					palavra.replace(start_pos, from.length(), to);
					start_pos += to.length();
				}
			}
			return palavra;
		}
		void Gravar_Varios_Valores(string arquivo, vector<string> Cadeia, vector<string> Chave, vector<string> valor)
		{
			/*
			Cria novas entradas no XML, com mais de 1 key
			Nao subsitue ou edita, CRIA
			Exemplo de chamada:
			string arquivo = ".\\Usuarios.xml";
			vector<string> Grupos = {"Banco_de_Dados", "Usuarios", "Perfil"}; //quantos quiser
			vector<string> Chaves = {"Nome", "Idade", "Sexo"};
			vector<string> Valores = {"Eduardo", "29", "Marculino"};
			//Chaves e Valores tem que conter o mesmo numero de elementos
			//Caso contrario, a funcao nao executa
			Leitor_Menyoo::Gravar_Varios_Valores(arquivo, Grupos, Chaves, Valores);
			===========================================
			Resultado:
			<Banco_de_Dados>
				<Usuarios>
					<Perfil>
						<Nome>Eduardo</Nome>
						<Idade>29</Idade>
						<Sexo>Marculino</Sexo>
					</Perfil>
				</Usuarios>
			</Banco_de_Dados>
			*/
			if (Chave.size() == valor.size())
			{
				ofstream Arquivo;
				Arquivo.open(arquivo, std::ios_base::app);
				for (int i = 0; i <= (Cadeia.size() - 1); i++)
				{
					Arquivo << "<" + Cadeia[i] + ">" << endl;
				}
				for (int i = 0; i <= (Chave.size() - 1); i++)
				{
					Arquivo << "<" + Chave[i] + ">" + valor[i] + "</" + Chave[i] + ">" << endl;
				}
				for (int i = (Cadeia.size() - 1); i >= 0; i--)
				{
					Arquivo << "</" + Cadeia[i] + ">" << endl;
				}
				Arquivo.close();
			}
		}
		void Criar_Arquivo(string arquivo)
		{
			ofstream Arquivo;
			Arquivo.open(arquivo, std::ios_base::app);
			Arquivo.close();
		}
		void Criar_Tag(string arquivo, string grupo)
		{
			//Abre uma tag, sem fechar
			//Ex:
			//string Arquivo = ".\\Arquivo Criado.xml";
			//Leitor_Menyoo::Criar_Tag(Arquivo, "BancoDeDados");
			//Resultado: <BancoDeDados>
			ofstream Arquivo;
			Arquivo.open(arquivo, std::ios_base::app);
			Arquivo << "<" + grupo + ">" << endl;
			Arquivo.close();
		}
		void Fecha_Tag(string arquivo, string grupo)
		{
			//Fecha uma tag, sem abrir
			//Ex:
			//string Arquivo = ".\\Arquivo Criado.xml";
			//Leitor_Menyoo::Fecha_Tag(Arquivo, "BancoDeDados");
			//Resultado: </BancoDeDados>
			ofstream Arquivo;
			Arquivo.open(arquivo, std::ios_base::app);
			Arquivo << "</" + grupo + ">" << endl;
			Arquivo.close();
		}
		void Criar_e_Fecha_Tag_com_Valor(string arquivo, string tag, string valor)
		{
			//Cria uma tag, adiciona um valor e fecha
			//Ex:
			//string Arquivo = ".\\Arquivo Criado.xml";
			//Leitor_Menyoo::Criar_e_Fecha_Tag_com_Valor(Arquivo, "Nome", "Eduardo");
			//
			//Resultado: <Nome>Eduardo</Nome>
			ofstream Arquivo;
			Arquivo.open(arquivo, std::ios_base::app);
			Arquivo << "<" + tag + ">" + valor + "</" + tag + ">" << endl;
			Arquivo.close();
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
		int id;
		string animacao;
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
			for (int i = 0; i < s.size(); i++)
				t += (s[i] - 'A' + 3) % 26 + 'A';
			return t;
		}
		string Descriptografar(string text, bool PrimeiraMaiuscula = true)
		{
			//Exemplo		Criptografia::Ceasar::Descriptografar("HGXDUGR=EUHVROLQ=HVSHUW=HP=F") 
			string s = text;
			string t;
			for (int i = 0; i < s.size(); i++)
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
	namespace Rot13
	{
		std::string Criptografar(std::string s) {
			string rotated{};
			for (const char& c : s)
			{
				if (isalpha(c))
					if (isupper(c)) rotated += char((c - 'A' + 13) % 26 + 'A');
					else
						rotated += char((c - 'a' + 13) % 26 + 'a');
				else rotated += c;
			}
			return rotated;
		}
		std::string Descriptografar(std::string n) {
			std::string s = "";
			int l = n.length();
			for (int i = 0; i < l; i++)
			{
				if (n[i] == ' ') {
					s += n[i];
					continue;
				}
				if (char(tolower(n[i])) >= 'n' && char(tolower(n[i])) <= 'z')
				{
					char a = 'z', b = 'a';
					int k = (int)a - (int)n[i];
					n[i] = char((int)b + (13 - k - 1));
				}
				else
					n[i] = char((int)n[i] + 13);
				s = s + n[i];
			}
			return s;
		}
	}
	namespace XOR2
	{
		string Cript(string s)
		{
			string rotated{};
			for (const char& c : s)
			{
				rotated += 3 ^ c;
			} return rotated;
		}
		string Decript(string s)
		{
			string rotated{};
			for (const char& c : s)
			{
				rotated += 3 ^ c;
			} return rotated;
		}
	}
	namespace ReverseInt
	{
		int Reverse_INTs(int n)
		{
			int reverse = 0;
			while (n != 0)
			{
				reverse = reverse * 10;
				reverse = reverse + n % 10;
				n = n / 10;
			}
			return reverse;
		}
	}
	namespace ReverseString
	{
		string Reverse(string a)
		{
			reverse(a.begin(), a.end());
			return a;
		}
	}
}
namespace Crossmap
{
	vector<string> Buscar_Crossmap(const char* Link_Lista)
	{
		/*
		Como usar:
		Extern_Reader::LOG::arquivoTXT = "Mapa.txt";
		vector<string> Lista_HASH = Buscar_Crossmap("https://pastebin.com/raw/XB8CHz5j");
		for (int i = 0; i <= (Lista_HASH.size() - 1); i++)
		{
			Extern_Reader::LOG::LogSemHora(Lista_HASH[i]);
			cout << Lista_HASH[i] << endl;;
		}
		*/
		IStream* stream;
		const char* URL = Link_Lista;
		URLOpenBlockingStreamA(0, URL, &stream, 0, 0);
		char buff[100];
		string s;
		unsigned long bytesRead;
		while (true)
		{
			stream->Read(buff, 100, &bytesRead);
			if (0U == bytesRead)
			{
				break;
			}
			s.append(buff, bytesRead);
		};
		stream->Release();
		string oi = s; //tudo misturado 
		string R = "\r";
		string N = "\n";
		string vazio = "";
		string espaco = " ";
		string ZeroX = "0x";
		string ZeroXVirg = ",0x";
		size_t start_pos = 0;
		while ((start_pos = oi.find(R, start_pos)) != std::string::npos) {
			oi.replace(start_pos, R.length(), vazio);
			start_pos += vazio.length();
		}
		start_pos = 0;
		while ((start_pos = oi.find(N, start_pos)) != std::string::npos) {
			oi.replace(start_pos, N.length(), vazio);
			start_pos += vazio.length();
		}
		start_pos = 0;
		while ((start_pos = oi.find(espaco, start_pos)) != std::string::npos) {
			oi.replace(start_pos, espaco.length(), vazio);
			start_pos += vazio.length();
		}
		start_pos = 0;
		while ((start_pos = oi.find(ZeroX, start_pos)) != std::string::npos) {
			oi.replace(start_pos, ZeroX.length(), ZeroXVirg);
			start_pos += ZeroXVirg.length();
		}
		vector<string> result;
		int cutAt;
		while ((cutAt = oi.find_first_of(",")) != oi.npos) {
			if (cutAt > 0) {
				result.push_back(oi.substr(0, cutAt));
			}
			oi = oi.substr(cutAt + 1);
		}
		if (oi.length() > 0) {
			result.push_back(oi);
		}
		return result;
	}
	void GerarCrossmap()
	{
		vector<string> Lista_HASH = Buscar_Crossmap("https://pastebin.com/raw/XB8CHz5j");
		vector<string> Lista_TABLE = Buscar_Crossmap("https://pastebin.com/raw/VXhMLcWF");
		ofstream Arquivo;
		Arquivo.open("crossmap.cpp", std::ios_base::app);
		Arquivo << "//BresoDEV 2022 Copyright" << endl;
		Arquivo << "#include \"stdafx.h\"" << endl;
		Arquivo << "#include <mmsystem.h>" << endl;
		Arquivo << "::std::unordered_map<uint64_t, uint64_t> nativeHashMap;" << endl;
		Arquivo << "" << endl;
		Arquivo << "uint64_t __HASHMAPDATA[] = " << endl;
		Arquivo << "{ " << endl;
		cout << "Reorganizando os hashs...." << endl;
		vector<string> Final;
		if (Lista_TABLE.size() == Lista_HASH.size())
		{
			int tamanhoTable = Lista_TABLE.size() - 1;
			int tamanhoHashs = Lista_HASH.size() - 1;
			int contador = 0;
			for (int i = 0; i <= tamanhoTable; i++)
			{
				string add = Lista_TABLE[i] + ", " + Lista_HASH[i] + ",";
				Arquivo << add << endl;
			}
			Arquivo << "};" << endl;
			Arquivo << "//BresoDEV 2022 Copyright" << endl;
			Arquivo.close();
			cout << "Finalizando crossmap..." << endl;
		}
		else
		{
			cout << "Tamanho dos hashs nao batem" << endl;
		}
		cout << "Processo finalizado" << endl;
		cout << "" << endl;
		cout << "" << endl;
		system("pause");
	}
	void Preparar_Crossmap_site(string arquivo, string table, string hash)
	{
		//Como usar:
		//Crossmap::Preparar_Crossmap_site("CrossMapping.cpp", "Table.txt", "Hash.txt");
		//
		std::vector<string> TempVECTOR;
		vector<string> tokens;
		ifstream imput(arquivo);
		for (string line; getline(imput, line);)
		{
			istringstream tokenizer{ line };
			string token;
			while (getline(tokenizer, token, ' '))
			{
				tokens.push_back(token);
			}
		}
		int breakl = 0;
		ofstream Arquivo;
		Arquivo.open(table, std::ios_base::app);
		for (int i = 0; i <= (tokens.size() - 1); i += 2)
		{
			Arquivo << tokens[i] << endl;
			breakl = i;
			breakl = i;
		}
		Arquivo.close();
		ofstream Arquivo2;
		Arquivo2.open(hash, std::ios_base::app);
		for (int i = 1; i <= (tokens.size() - 1); i += 2)
		{
			Arquivo2 << tokens[i] << endl;
		}
		Arquivo2.close();
	}
	uint64_t Converter_String_Hash(string value)
	{
		int nativo = value.length();
		uint64_t hashVazio = 0x0;
		for (int i = 0; i <= nativo - 1; i++) {
			char charRetorno = value.at(i);
			hashVazio = 0x10 * hashVazio;
			switch (charRetorno) {
			case '0': hashVazio += 0; break; case '1': hashVazio += 0x1; break;
			case '2': hashVazio += 0x2; break; case '3': hashVazio += 0x3; break;
			case '4': hashVazio += 0x4; break; case '5': hashVazio += 0x5; break;
			case '6': hashVazio += 0x6; break; case '7': hashVazio += 0x7; break;
			case '8': hashVazio += 0x8; break; case '9': hashVazio += 0x9; break;
			case 'A': hashVazio += 0xA; break; case 'B': hashVazio += 0xB; break;
			case 'C': hashVazio += 0xC; break; case 'D': hashVazio += 0xD; break;
			case 'E': hashVazio += 0xE; break; case 'F': hashVazio += 0xF; break;
			}
		}
		return hashVazio;
	}
}
namespace RedM_FiveM
{
	namespace RedM
	{
		void Cabecalho()
		{
			Extern_Reader::LOG::arquivoTXT = "MapaRedM.lua";
			Extern_Reader::LOG::LogSemHora(" ");
			Extern_Reader::LOG::LogSemHora(" ");
			Extern_Reader::LOG::LogSemHora(" ");
			Extern_Reader::LOG::LogSemHora("-- Resource created with Breso RDR2 Map Editor, converted to run on RedM framework");
			Extern_Reader::LOG::LogSemHora("-- Enjoy!!");
			Extern_Reader::LOG::LogSemHora(" ");
			Extern_Reader::LOG::LogSemHora(" ");
			Extern_Reader::LOG::LogSemHora(" ");
			Extern_Reader::LOG::LogSemHora(" ");
		}
		void RedM_Save(int ID, DWORD Modelo, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, const char* Scenario = "", int traje = 0)
		{
			Extern_Reader::LOG::arquivoTXT = "MapaRedM.lua";
			switch (ID)
			{
			case 1:
				Extern_Reader::LOG::LogSemHora("--This function, loads object " + to_string(Modelo) + ", at coords " + to_string(posX) + "," + to_string(posY) + "," + to_string(posZ));
				Extern_Reader::LOG::LogSemHora("CreateThread(function() ");
				Extern_Reader::LOG::LogSemHora("  RequestModel(" + to_string(Modelo) + ")");
				Extern_Reader::LOG::LogSemHora("  while not HasModelLoaded(" + to_string(Modelo) + ") do Wait(100) end");
				Extern_Reader::LOG::LogSemHora("  prop = CreateObject(" + to_string(Modelo) + "," + to_string(posX) + "," + to_string(posY) + "," + to_string(posZ) + ", 1, 1, 1, 0, 0)");
				Extern_Reader::LOG::LogSemHora("  SetEntityRotation(prop, " + to_string(rotX) + "," + to_string(rotY) + "," + to_string(rotZ) + ", 2, true)");
				Extern_Reader::LOG::LogSemHora("  FreezeEntityPosition(prop,true)");
				Extern_Reader::LOG::LogSemHora("end)");
				Extern_Reader::LOG::LogSemHora("  ");
				Extern_Reader::LOG::LogSemHora("  ");
				break;
			case 2://ped  
				Extern_Reader::LOG::LogSemHora("--This function, loads ped " + to_string(Modelo) + ", at coords " + to_string(posX) + "," + to_string(posY) + "," + to_string(posZ));
				Extern_Reader::LOG::LogSemHora("CreateThread(function() ");
				Extern_Reader::LOG::LogSemHora("  RequestModel(" + to_string(Modelo) + ")");
				Extern_Reader::LOG::LogSemHora("  while not HasModelLoaded(" + to_string(Modelo) + ") do Wait(100) end");
				Extern_Reader::LOG::LogSemHora("  ped = CreatePed(" + to_string(Modelo) + "," + to_string(posX) + "," + to_string(posY) + "," + to_string(posZ) + " - 1.0, 0, 1, 0, 0, 0)");
				Extern_Reader::LOG::LogSemHora("  peds = ped");
				Extern_Reader::LOG::LogSemHora("  SetEntityRotation(ped, " + to_string(rotX) + "," + to_string(rotY) + "," + to_string(rotZ) + ", 2, true)");
				Extern_Reader::LOG::LogSemHora("  SetPedVisible(ped, true)");
				Extern_Reader::LOG::LogSemHora("  ClearPedTasksImmediately(ped, 0, 0)");
				Extern_Reader::LOG::LogSemHora("  KnockOffPedProp(ped, 0, 0, 0, 0)");
				Extern_Reader::LOG::LogSemHora("  FreezeEntityPosition(ped,true)");
				Extern_Reader::LOG::LogSemHora("  TaskStartScenarioInPlace(ped, GetHashKey(\"" + (string)Scenario + "\"), -1, true, false, 1.0, false) ");
				Extern_Reader::LOG::LogSemHora("  SetPedOutfitPreset(ped, " + to_string(traje) + ")");
				Extern_Reader::LOG::LogSemHora("end)");
				Extern_Reader::LOG::LogSemHora(" ");
				Extern_Reader::LOG::LogSemHora(" ");
				break;
			case 3://veh 
				Extern_Reader::LOG::LogSemHora("--This function, loads vehicle " + to_string(Modelo) + ", at coords " + to_string(posX) + "," + to_string(posY) + "," + to_string(posZ));
				Extern_Reader::LOG::LogSemHora("CreateThread(function() ");
				Extern_Reader::LOG::LogSemHora("  RequestModel(" + to_string(Modelo) + ")");
				Extern_Reader::LOG::LogSemHora("  while not HasModelLoaded(" + to_string(Modelo) + ") do Wait(100) end");
				Extern_Reader::LOG::LogSemHora("  car = CreateVehicle(" + to_string(Modelo) + "," + to_string(posX) + "," + to_string(posY) + "," + to_string(posZ) + " - 0.5, 0, 0, 1, 0, 0, 0)");
				Extern_Reader::LOG::LogSemHora("  cars = car");
				Extern_Reader::LOG::LogSemHora("  SetEntityRotation(car, " + to_string(rotX) + "," + to_string(rotY) + "," + to_string(rotZ) + ", 2, true)");
				Extern_Reader::LOG::LogSemHora("  FreezeEntityPosition(car,true)");
				Extern_Reader::LOG::LogSemHora("  SetEntityVisible(car,true)");
				Extern_Reader::LOG::LogSemHora("end)");
				Extern_Reader::LOG::LogSemHora(" ");
				Extern_Reader::LOG::LogSemHora(" ");
				break;
			}
		}
		void Convert_to_RedM()
		{
			Cabecalho();
			Extern_Reader::INIFile::INIFilePath = ".\\Mapa.ini";
			for (int i = 0; i <= 10000; i++)
			{
				int MODELO = Extern_Reader::INIFile::Int::LerInt(Extern_Reader::Conversoes::INT::paraString(i), "ID");
				if (MODELO == 1)//OBJ
				{
					int MODELO2 = Extern_Reader::INIFile::Int::LerInt(Extern_Reader::Conversoes::INT::paraString(i), "MODELO");
					float posX = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "X");
					float posy = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "Y");
					float posz = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "Z");
					float possX = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "SX");
					float possy = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "SY");
					float possz = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "SZ");
					RedM_Save(1, MODELO2, posX, posy, posz, possX, possy, possz);
				}
				else if (MODELO == 2)//PED
				{
					int MODELO2 = Extern_Reader::INIFile::Int::LerInt(Extern_Reader::Conversoes::INT::paraString(i), "MODELO");
					float posX = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "X");
					float posy = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "Y");
					float posz = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "Z");
					float possX = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "SX");
					float possy = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "SY");
					float possz = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "SZ");
					int trajeponteiro = Extern_Reader::INIFile::Int::LerInt(Extern_Reader::Conversoes::INT::paraString(i), "TRAJE");
					string anim = Extern_Reader::INIFile::String::LerString(Extern_Reader::Conversoes::INT::paraString(i), "SCENARIO");
					RedM_Save(2, MODELO2, posX, posy, posz, possX, possy, possz, anim.c_str(), trajeponteiro);
					//SpawnarINI(MODELO, MODELO2, posX, posy, posz, possX, possy, possz, anim.c_str(), *trajeponteiro);
				}
				else if (MODELO == 3)//VEICULO
				{
					int MODELO2 = Extern_Reader::INIFile::Int::LerInt(Extern_Reader::Conversoes::INT::paraString(i), "MODELO");
					float posX = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "X");
					float posy = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "Y");
					float posz = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "Z");
					float possX = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "SX");
					float possy = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "SY");
					float possz = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "SZ");
					RedM_Save(3, MODELO2, posX, posy, posz, possX, possy, possz);
				}
				else
					i = 10000;
			}
		}
	}

	namespace FiveM
	{
		namespace Leitor_Menyoo
		{
			/*
			* Como USAR:
			*
			Leitor_Menyoo::DiretorioMapa = ".\\Mapa.xml";
			vector<string> Buscar_ModelHash = Leitor_Menyoo::Buscar_Valor("ModelHash");
			vector<string> Buscar_HashName = Leitor_Menyoo::Buscar_Valor("HashName");
			vector<string> Buscar_X = Leitor_Menyoo::Buscar_Valor("X");
			vector<string> Buscar_Y = Leitor_Menyoo::Buscar_Valor("Y");
			vector<string> Buscar_Z = Leitor_Menyoo::Buscar_Valor("Z");
			vector<string> Buscar_Pitch = Leitor_Menyoo::Buscar_Valor("Pitch");
			vector<string> Buscar_Roll = Leitor_Menyoo::Buscar_Valor("Roll");
			vector<string> Buscar_Yaw = Leitor_Menyoo::Buscar_Valor("Yaw");
			//Check se os valores batem
			if (Leitor_Menyoo::Tamanho_Do_Vector(Buscar_HashName) == Leitor_Menyoo::Tamanho_Do_Vector(Buscar_Yaw))
			{
				int tam = Leitor_Menyoo::Tamanho_Do_Vector(Buscar_HashName);
				for (int i = 0; i <= tam; i++)
					cout << Buscar_ModelHash[i] << ", " << Buscar_HashName[i] << ", " << Buscar_X[i] << ", "
					<< Buscar_Y[i] << ", " << Buscar_Z[i] << ", " << Buscar_Pitch[i] << ", " << Buscar_Roll[i]
					<< ", " << Buscar_Yaw[i] << endl;
			}
			*/
			struct Estrutura_Ped//<Type>1</Type>
			{
				DWORD ModelHash;
				string HashName;
				DWORD CurrentWeapon;
				float X;
				float Y;
				float Z;
				float Pitch;
				float Roll;
				float Yaw;
				string ScenarioName;
			};
			struct Estrutura_Prop//<Type>3</Type>
			{
				DWORD ModelHash;
				string HashName;
				float X;
				float Y;
				float Z;
				float Pitch;
				float Roll;
				float Yaw;
			};
			struct Estrutura_Carro//<Type>2</Type>
			{
				DWORD ModelHash;
				string HashName;
				float X;
				float Y;
				float Z;
				float Pitch;
				float Roll;
				float Yaw;
				int Primary;
				int Secondary;
				string NumberPlateText;
			};
			string DiretorioMapa = "";
			int Tamanho_Do_Vector(std::vector<string> vetor)
			{
				return vetor.size() - 1;
			}
			int Quantidade_de_Spawns_do_Mapa()//<Placement>
			{
				int contador = 0;
				ifstream imput(DiretorioMapa);
				string textolido;
				for (string line; getline(imput, line);)
				{
					if (line.find("<Placement>") != std::string::npos)
					{
						contador++;
					}
				}
				return contador;
			}
			vector<string> Buscar_Valor(string parametro)
			{
				std::vector<std::string> TempVECTOR;
				ifstream imput(DiretorioMapa);
				string textolido;
				if (parametro == "Type")
				{
					for (string line; getline(imput, line);)
					{
						if (line.find("<" + parametro + ">") != std::string::npos)
						{
							string from = "<" + parametro + ">";
							string to = "";
							size_t start_pos = 0;
							string from234 = " ";
							string to234 = "";
							size_t start_pos234 = 0;
							string from2 = "</" + parametro + ">";
							string to2 = "";
							size_t start_pos2 = 0;
							string from23 = "	";
							string to23 = "";
							size_t start_pos23 = 0;
							while ((start_pos = line.find(from, start_pos)) != std::string::npos) {
								line.replace(start_pos, from.length(), to);
								start_pos += to.length();
							}
							while ((start_pos2 = line.find(from2, start_pos2)) != std::string::npos) {
								line.replace(start_pos2, from2.length(), to2);
								start_pos2 += to2.length();
							}
							while ((start_pos23 = line.find(from23, start_pos23)) != std::string::npos) {
								line.replace(start_pos23, from23.length(), to23);
								start_pos23 += to23.length();
							}
							while ((start_pos234 = line.find(from234, start_pos234)) != std::string::npos) {
								line.replace(start_pos234, from234.length(), to234);
								start_pos234 += to234.length();
							}
							if (line == "1" || line == "2" || line == "3")
								TempVECTOR.push_back(line);
						}
					}
				}
				else
				{
					for (string line; getline(imput, line);)
					{
						if (line.find("<" + parametro + ">") != std::string::npos)
						{
							string from = "<" + parametro + ">";
							string to = "";
							size_t start_pos = 0;
							string from234 = " ";
							string to234 = "";
							size_t start_pos234 = 0;
							string from2 = "</" + parametro + ">";
							string to2 = "";
							size_t start_pos2 = 0;
							string from23 = "	";
							string to23 = "";
							size_t start_pos23 = 0;
							while ((start_pos = line.find(from, start_pos)) != std::string::npos) {
								line.replace(start_pos, from.length(), to);
								start_pos += to.length();
							}
							while ((start_pos2 = line.find(from2, start_pos2)) != std::string::npos) {
								line.replace(start_pos2, from2.length(), to2);
								start_pos2 += to2.length();
							}
							while ((start_pos23 = line.find(from23, start_pos23)) != std::string::npos) {
								line.replace(start_pos23, from23.length(), to23);
								start_pos23 += to23.length();
							}
							while ((start_pos234 = line.find(from234, start_pos234)) != std::string::npos) {
								line.replace(start_pos234, from234.length(), to234);
								start_pos234 += to234.length();
							}
							TempVECTOR.push_back(line);
						}
					}
				}
				return TempVECTOR;
			}
			string Buscar_Linha_Abaixo(string referencia, int numeroDeLinhasAbaixo)
			{
				/*
				Busca outras linhas abaixo, a partir de uma referencia
				Ex XML:
				<ReferenceCoords>
				<X>4991.55566</X>
				<Y>-5721.46191</Y>
				<Z>19.8802071</Z>
				</ReferenceCoords>
				Chamada da funcao:
				Leitor_Menyoo::DiretorioMapa = ".\\Mapa.xml";
				cout << Leitor_Menyoo::Buscar_Linha_Abaixo("ReferenceCoords", 2);
				Nesse caso, pega a referencia e pula 2 linhas, retornando <Y>-5721.46191</Y>
				*/
				std::vector<std::string> TempVECTOR;
				ifstream imput(DiretorioMapa);
				string textolido;
				string palavra;
				for (string line; getline(imput, line);)
				{
					if (line.find("<" + referencia + ">") != std::string::npos)
					{
						for (int i = 0; i <= (numeroDeLinhasAbaixo - 1); i++)
							getline(imput, line);
						palavra = line;
					}
				}
				return palavra;
			}
			vector<string> BuscarTodosValores(string referencia)
			{
				/*Como usar:
				BUsca todos valores baseados na referencia, nao importando onde se localiza e de qual
				grupo pertence
				Leitor_Menyoo::DiretorioMapa = ".\\Mapa.xml";
				vector<string> Valores = Leitor_Menyoo::BuscarTodosValores("X");
				for (int i = 0; i <= Valores.size() - 1; i++)
					cout << Valores[i] << endl;
				*/
				vector<string> Colecao;
				ifstream file(DiretorioMapa);
				string palavra;
				string line;
				while (getline(file, line))
				{
					if (line.find("<" + referencia + ">") != std::string::npos)
					{
						string from = "	";
						string to = "";
						size_t start_pos = 0;
						while ((start_pos = line.find(from, start_pos)) != std::string::npos) {
							line.replace(start_pos, from.length(), to);
							start_pos += to.length();
						}
						Colecao.push_back(line);
					}
				}
				return Colecao;
			}
			vector<string> Buscar_Todas_Linhas_Abaixo(string referencia, int numeroDeLinhasAbaixo)
			{
				/*
				Busca por uma referencia, e armazena todas linhas abaixo, a partir de uma referencia
				Mas armazena somente 1 valor por chave
				===========================================
				Ex XML:
				<ReferenceCoords>
				<X>4991.55566</X>
				</ReferenceCoords>
				<ReferenceCoordsDiferente>
				<X>2222.2222</X>
				</ReferenceCoordsDiferente>
				<ReferenceCoords>
				<X>1111.11111</X>
				</ReferenceCoords>
				============================================
				Chamada da funcao:
				Leitor_Menyoo::DiretorioMapa = ".\\Mapa.xml";
				vector<string> valores = Leitor_Menyoo::Buscar_Todas_Linhas_Abaixo("ReferenceCoords", 1);
				for (int i = 0; i <= (valores.size() - 1); i++)
					cout << valores[i] << endl;
				Retotorno:
				<X>4991.55566</X>
				<X>1111.11111</X>
				============================================
				Nesse caso, pega a referencia e pula 1 linha, retornando o valor de X
				Depois continua lendo, ate achar outra referencia igual, pula 1 linha e armazena o X
				E assim por diante....Lembrando que ele nao armazena o "ReferenceCoordsDiferente", pois
				apesar de existir o X dentro, a chave principal nao bate com o "ReferenceCoords", que significa
				que pertence a outro grupo diferente, apesar do mesmo nome
				Isso serve pra buscar valores diferentes, quando existem mais de 1 chave com o mesmo nome, dentro
				de espacos diferentes
				*/
				vector<string> Colecao;
				std::vector<std::string> TempVECTOR;
				ifstream imput(DiretorioMapa);
				string textolido;
				for (string line; getline(imput, line);)
				{
					if (line.find("<" + referencia + ">") != std::string::npos)
					{
						for (int i = 0; i <= (numeroDeLinhasAbaixo - 1); i++)
							getline(imput, line);
						Colecao.push_back(line);
					}
				}
				return Colecao;
			}
			void Gravar_Valores(string arquivo, vector<string> Cadeia, string Chave, string valor)
			{
				/*
				Cria novas entradas no XML, nao subsitue ou edita, CRIA
				Exemplo de chamada:
				Leitor_Menyoo::DiretorioMapa = ".\\MapaCadeia.xml";
				vector<string> Chaves = { "Usuarios", "Perfil" };//Quantas quiser
				Leitor_Menyoo::Gravar_Valores(".\\BancoDados.xml", Chaves, "Nome", "Eduardo");
				===========================================
				Resultado:
				<Usuarios>
					<Perfil>
						<Nome>Eduardo</Nome>
					</Perfil>
				</Usuarios>
				*/
				ofstream Arquivo;
				Arquivo.open(arquivo, std::ios_base::app);
				for (int i = 0; i <= (Cadeia.size() - 1); i++)
				{
					Arquivo << "<" + Cadeia[i] + ">" << endl;
				}
				Arquivo << "<" + Chave + ">" + valor + "</" + Chave + ">" << endl;
				for (int i = (Cadeia.size() - 1); i >= 0; i--)
				{
					Arquivo << "</" + Cadeia[i] + ">" << endl;
				}
				Arquivo.close();
			}
			string Remove_Keys(string palavra)
			{
				/*
				Remove as keys dos valores lidos, deixando apenas o valor
				Ex:
				cout << Leitor_Menyoo::Remove_Keys("</Usuarios>", Remover);
				Saida: Usuarios
				*/
				vector<string> Remover = { " ", "<", "/", ">" }; //Quantas quiser
				for (int i = 0; i <= (Remover.size() - 1); i++)
				{
					string from = Remover[i];
					string to = "";
					size_t start_pos = 0;
					while ((start_pos = palavra.find(from, start_pos)) != std::string::npos) {
						palavra.replace(start_pos, from.length(), to);
						start_pos += to.length();
					}
				}
				return palavra;
			}
			void Gravar_Varios_Valores(string arquivo, vector<string> Cadeia, vector<string> Chave, vector<string> valor)
			{
				/*
				Cria novas entradas no XML, com mais de 1 key
				Nao subsitue ou edita, CRIA
				Exemplo de chamada:
				string arquivo = ".\\Usuarios.xml";
				vector<string> Grupos = {"Banco_de_Dados", "Usuarios", "Perfil"}; //quantos quiser
				vector<string> Chaves = {"Nome", "Idade", "Sexo"};
				vector<string> Valores = {"Eduardo", "29", "Marculino"};
				//Chaves e Valores tem que conter o mesmo numero de elementos
				//Caso contrario, a funcao nao executa
				Leitor_Menyoo::Gravar_Varios_Valores(arquivo, Grupos, Chaves, Valores);
				===========================================
				Resultado:
				<Banco_de_Dados>
					<Usuarios>
						<Perfil>
							<Nome>Eduardo</Nome>
							<Idade>29</Idade>
							<Sexo>Marculino</Sexo>
						</Perfil>
					</Usuarios>
				</Banco_de_Dados>
				*/
				if (Chave.size() == valor.size())
				{
					ofstream Arquivo;
					Arquivo.open(arquivo, std::ios_base::app);
					for (int i = 0; i <= (Cadeia.size() - 1); i++)
					{
						Arquivo << "<" + Cadeia[i] + ">" << endl;
					}
					for (int i = 0; i <= (Chave.size() - 1); i++)
					{
						Arquivo << "<" + Chave[i] + ">" + valor[i] + "</" + Chave[i] + ">" << endl;
					}
					for (int i = (Cadeia.size() - 1); i >= 0; i--)
					{
						Arquivo << "</" + Cadeia[i] + ">" << endl;
					}
					Arquivo.close();
				}
			}
			void Criar_Arquivo(string arquivo)
			{
				ofstream Arquivo;
				Arquivo.open(arquivo, std::ios_base::app);
				Arquivo.close();
			}
			void Criar_Tag(string arquivo, string grupo)
			{
				//Abre uma tag, sem fechar
				//Ex:
				//string Arquivo = ".\\Arquivo Criado.xml";
				//Leitor_Menyoo::Criar_Tag(Arquivo, "BancoDeDados");
				//Resultado: <BancoDeDados>
				ofstream Arquivo;
				Arquivo.open(arquivo, std::ios_base::app);
				Arquivo << "<" + grupo + ">" << endl;
				Arquivo.close();
			}
			void Fecha_Tag(string arquivo, string grupo)
			{
				//Fecha uma tag, sem abrir
				//Ex:
				//string Arquivo = ".\\Arquivo Criado.xml";
				//Leitor_Menyoo::Fecha_Tag(Arquivo, "BancoDeDados");
				//Resultado: </BancoDeDados>
				ofstream Arquivo;
				Arquivo.open(arquivo, std::ios_base::app);
				Arquivo << "</" + grupo + ">" << endl;
				Arquivo.close();
			}
			void Criar_e_Fecha_Tag_com_Valor(string arquivo, string tag, string valor)
			{
				//Cria uma tag, adiciona um valor e fecha
				//Ex:
				//string Arquivo = ".\\Arquivo Criado.xml";
				//Leitor_Menyoo::Criar_e_Fecha_Tag_com_Valor(Arquivo, "Nome", "Eduardo");
				//
				//Resultado: <Nome>Eduardo</Nome>
				ofstream Arquivo;
				Arquivo.open(arquivo, std::ios_base::app);
				Arquivo << "<" + tag + ">" + valor + "</" + tag + ">" << endl;
				Arquivo.close();
			}
			void Convert_to_Menyoo()
			{
				Menyoo::XMLPath = ".\\MapaMenyoo.xml";
				Menyoo::SalvarXML::MenyooCabecalho();
				Menyoo::SalvarXML::Add_Reference_Coords(1111.1111, 2222.2222, 3333.3333);
				GTA::Spawn_Struct SpawnPed;
				GTA::Spawn_Struct SpawnProp;
				GTA::Spawn_Struct SpawnVeh;
				Extern_Reader::INIFile::INIFilePath = ".\\Mapa.ini";
				for (int i = 0; i <= 50; i++)
				{
					int MODELO = Extern_Reader::INIFile::Int::LerInt(Extern_Reader::Conversoes::INT::paraString(i), "ID");
					if (MODELO == 1)//OBJ
					{
						SpawnProp.Model = Extern_Reader::INIFile::Int::LerInt(Extern_Reader::Conversoes::INT::paraString(i), "MODELO");
						SpawnProp.PosX = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "X");
						SpawnProp.PosY = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "Y");
						SpawnProp.PosZ = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "Z");
						SpawnProp.RotX = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "SX");
						SpawnProp.RotY = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "SY");
						SpawnProp.RotZ = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "SZ");
						Menyoo::SalvarXML::AddSpawn_XML_Prop(SpawnProp);
					}
					else if (MODELO == 2)//PED
					{
						SpawnPed.Model = Extern_Reader::INIFile::Int::LerInt(Extern_Reader::Conversoes::INT::paraString(i), "MODELO");
						SpawnPed.PosX = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "X");
						SpawnPed.PosY = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "Y");
						SpawnPed.PosZ = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "Z");
						SpawnPed.RotX = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "SX");
						SpawnPed.RotY = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "SY");
						SpawnPed.RotZ = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "SZ");
						//SpawnPed.= Extern_Reader::INIFile::Int::LerInt(Extern_Reader::Conversoes::INT::paraString(i), "TRAJE");
						SpawnPed.animacao = Extern_Reader::INIFile::String::LerString(Extern_Reader::Conversoes::INT::paraString(i), "SCENARIO");
						Menyoo::SalvarXML::AddSpawn_XML_Peds(SpawnPed);
					}
					else if (MODELO == 3)//VEICULO
					{
						SpawnVeh.Model = Extern_Reader::INIFile::Int::LerInt(Extern_Reader::Conversoes::INT::paraString(i), "MODELO");
						SpawnVeh.PosX = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "X");
						SpawnVeh.PosY = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "Y");
						SpawnVeh.PosZ = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "Z");
						SpawnVeh.RotX = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "SX");
						SpawnVeh.RotY = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "SY");
						SpawnVeh.RotZ = Extern_Reader::INIFile::Float::LerFloat(Extern_Reader::Conversoes::INT::paraString(i), "SZ");
						Menyoo::SalvarXML::AddSpawn_XML_Veiculos(SpawnVeh);
					}
					else
						i = 10000;
				}
				Menyoo::SalvarXML::FinalizarXML();
			}
		}

	}
}






namespace Conversoes
{
	namespace ConstChar
	{
		string toString(const char* palavra)
		{
			string s(palavra);
			return s;
		}

		char* toChar(const char* palavra)
		{
			char* oi = strdup(palavra);
			return oi;
		}

		int toInt(const char* palavra)
		{
			stringstream valor;
			valor << palavra;
			int a;
			valor >> a;
			return a;
		}

		float toFloat(const char* palavra)
		{
			string fs(palavra);
			return stof(fs);
		}

	}

	namespace Int
	{


		string toString(int valor)
		{
			return std::to_string(valor);
		}
	}

	namespace __INT64
	{
		bool toBool(__int64 valor)
		{
			bool vOut = valor != 0;
			return vOut;
		}

		char toChar(__int64 valor)
		{
			return (char)valor;
		}

		char* toCharP(__int64 valor)
		{
			__int64 vIn = valor;
			char vOut[21];
			_i64toa_s(vIn, vOut, sizeof(vOut), 10);
			return vOut;
		}
		double toDouble(__int64 valor)
		{
			return (double)valor;
		}
		float toFloat(__int64 valor)
		{
			return (float)valor;
		}
		int toInt(__int64 valor)
		{
			return (int)valor;
		}
		short toShort(__int64 valor)
		{
			return (short)valor;
		}
		long toLong(__int64 valor)
		{
			return (long)valor;
		}
		unsigned __int64 toUnsigned__int64(__int64 valor)
		{
			return  (unsigned __int64)valor;
		}
		unsigned char toUnsigned_char(__int64 valor)
		{
			return  (unsigned char)valor;
		}
		unsigned int toUnsigned_int(__int64 valor)
		{
			return (unsigned int)valor;
		}
		unsigned long toUnsigned_long(__int64 valor)
		{
			return (unsigned long)valor;
		}
		unsigned short toUnsigned_short(__int64 valor)
		{
			return (unsigned short)valor;
		}
		wchar_t toWchar_t(__int64 valor)
		{
			return (wchar_t)valor;
		}
		wchar_t* toWchar_tP(__int64 valor)
		{
			__int64 vIn = valor;
			wchar_t vOut[21];
			_i64tow_s(vIn, vOut, sizeof(vOut) / 2, 10);
			return vOut;
		}
	}

	namespace Bool
	{
		__int64 to__Int64(bool valor)
		{
			bool vIn = valor;
			__int64 vOut = vIn ? 1 : 0;
			return vOut;
		}
		char toChar(bool valor)
		{
			bool vIn = valor;
			char vOut = vIn ? 1 : 0;
			return vOut;
		}
		char* toCharP(bool valor)
		{
			const char* a;
			if (valor)
				a = "true";
			else
				a = "false";
			return (char*)a;
		}
		double toDouble(bool valor)
		{
			bool vIn = valor;
			double vOut = vIn ? 1.0 : 0.0;
			return vOut;
		}
		float tofloat(bool valor)
		{
			bool vIn = valor;
			float vOut = vIn ? 1.0f : 0.0f;
			return vOut;
		}
		int toInt(bool valor)
		{
			bool vIn = valor;
			int vOut = vIn ? 1 : 0;
			return vOut;
		}
		long toLong(bool valor)
		{
			bool vIn = valor;
			long vOut = vIn ? 1 : 0;
			return vOut;
		}
		short toShort(bool valor)
		{
			bool vIn = valor;
			short vOut = vIn ? 1 : 0;
			return vOut;
		}
		unsigned __int64 toUnsigned__int64(bool valor)
		{
			bool vIn = valor;
			unsigned __int64 vOut = vIn ? 1 : 0;
			return vOut;
		}
		unsigned char toUnsigned_char(bool valor)
		{
			bool vIn = valor;
			unsigned char vOut = vIn ? 1 : 0;
			return vOut;
		}
		unsigned int toUnsigned_int(bool valor)
		{
			bool vIn = valor;
			unsigned int vOut = vIn ? 1 : 0;
			return vOut;
		}
		unsigned long toUnsigned_long(bool valor)
		{
			bool vIn = valor;
			unsigned long vOut = vIn ? 1 : 0;

			return vOut;
		}
		unsigned short toUnsigned_short(bool valor)
		{
			bool vIn = valor;
			unsigned short vOut = vIn ? 1 : 0;
			return vOut;
		}
		wchar_t toWchar_t(bool valor)
		{
			bool vIn = valor;
			wchar_t vOut = vIn ? 1 : 0;
			return vOut;
		}
		const char* toConstChar(bool valor)
		{
			if (valor)
				return "true";
			else
				return "false";
		}

		string toString(bool valor)
		{
			if (valor)
				return "true";
			else
				return "false";
		}

	}

	namespace Char
	{
		__int64 to___int64(char valor)
		{
			return (__int64)valor;
		}

		bool toBool(char valor)
		{
			char vIn = valor;
			bool vOut = vIn != 0;
			return vOut;
		}

		char* toCharP(char valor)
		{
			char vIn = valor;
			char vOut[2] = { vIn,0 };
			return vOut;
		}

		double toDouble(char valor)
		{
			return (double)valor;
		}
		float toFloat(char valor)
		{
			return (float)valor;
		}
		int toInt(char valor)
		{
			return (int)valor;
		}
		long toLong(char valor)
		{
			return (long)valor;
		}
		short toShort(char valor)
		{
			return (short)valor;;
		}
		unsigned __int64 toUnsigned__int64(char valor)
		{
			return (unsigned __int64)valor;
		}
		unsigned char toUnsigned_char(char valor)
		{
			return (unsigned char)valor;
		}
		unsigned int toUnsigned_int(char valor)
		{
			return (unsigned int)valor;
		}
		unsigned long toUnsigned_long(char valor)
		{
			return (unsigned long)valor;
		}
		unsigned short toUnsigned_short(char valor)
		{
			return (unsigned short)valor;
		}
		wchar_t toWchar_t(char valor)
		{
			return (wchar_t)valor;
		}
		wchar_t* toWchar_tP(char valor)
		{
			char vIn = valor;
			wchar_t vOut[5];
			_itow_s(vIn, vOut, (sizeof(vOut) / 2), 10);
			return vOut;
		}
	}

	namespace CharP
	{
		__int64 to__int64(char* valor)
		{
			return _atoi64(valor);
		}
		bool toBool(char* valor)
		{
			return valor && stricmp(valor, "true") == 0;;
		}
		char toChar(char* valor)
		{
			return (char)atoi(valor);;
		}
		double toDouble(char* valor)
		{
			return strtod(valor, NULL);;
		}
		int toInt(char* valor)
		{
			return atoi(valor);;
		}
		float toFloat(char* valor)
		{
			return (float)strtod(valor, NULL);;
		}
		long toLong(char* vIn)
		{
			return strtol(vIn, NULL, 10);;
		}
		short to(char* vIn)
		{
			return (short)atoi(vIn);
		}
		unsigned __int64 toUnsigned__int64(char* vIn)
		{
			return _strtoui64(vIn, NULL, 10);
		}
		unsigned char toUnsigned_char(char* vIn)
		{
			return (unsigned char)strtol(vIn, NULL, 10);
		}
		unsigned int toUnsigned_int(char* vIn)
		{
			return strtoul(vIn, NULL, 10);
		}
		unsigned long toUnsigned_long(char* vIn)
		{
			return strtoul(vIn, NULL, 10);;
		}
	}

	namespace Double
	{
		__int64 to__int64(double vIn)
		{
			return (__int64)vIn;
		}

		bool to_bool(double vIn)
		{
			return vIn != 0.0;
		}

		char to_char(double vIn)
		{
			return (char)vIn;;
		}

		char* to_CharP(double vIn)
		{
			char vOut[26];
			_gcvt_s(vOut, sizeof(vOut), vIn, 17);
			return vOut;
		}

		float to_float(double vIn)
		{
			return (float)vIn;
		}

		int to_int(double vIn)
		{
			return (int)vIn;
		}

		long to_long(double vIn)
		{
			return (long)vIn;
		}

		short to_short(double vIn)
		{
			return (short)vIn;
		}

		unsigned __int64 to_unsigned__int64(double vIn)
		{
			return (unsigned __int64)vIn;
		}

		unsigned char to_unsigned_char(double vIn)
		{
			return (unsigned char)vIn;
		}

		unsigned int to_unsigned_int(double vIn)
		{
			return (unsigned int)vIn;
		}

		unsigned long to_unsigned_long(double vIn)
		{
			return (unsigned long)vIn;
		}

		unsigned short to_unsigned_short(double vIn)
		{
			return (unsigned short)vIn;
		}

		wchar_t to_wchar_t(double vIn)
		{
			return (wchar_t)vIn;
		}

		wchar_t* to_wchar_tP(double vIn)
		{
			char vOutChar[26];
			_gcvt_s(vOutChar, sizeof(vOutChar), vIn, 17);
			wchar_t vOut[26];
			mbstowcs_s(NULL, vOut, sizeof(vOut) / 2, vOutChar, sizeof(vOutChar));
			return vOut;
		}


	}

}

vector<string> Buscar_Lista(const char* Link_Lista)
{
	/*
	Como usar:
	vector<string> Lista_HASH = Buscar_Lista("https://pastebin.com/raw/WwvvCpGG");
	for (int i = 0; i <= (Lista_HASH.size() - 2); i++)
	{
		cout << Lista_HASH[i] << endl;;
	}
	*/
	IStream* stream;
	const char* URL = Link_Lista;
	URLOpenBlockingStreamA(0, URL, &stream, 0, 0);
	char buff[100];
	string s;
	unsigned long bytesRead;
	while (true)
	{
		stream->Read(buff, 100, &bytesRead);
		if (0U == bytesRead)
		{
			break;
		}
		s.append(buff, bytesRead);
	};
	stream->Release();
	string oi = s; //tudo misturado 
	string vazio = "";


	vector<string> arraia = { "\r", "\n", "</br>", "0x", ",0x" };

	for (int i = 0; i <= (arraia.size() - 1); i++)
	{
		size_t start_pos = 0;
		while ((start_pos = oi.find(arraia[i], start_pos)) != std::string::npos) {
			oi.replace(start_pos, arraia[i].length(), vazio);
			start_pos += vazio.length();
		}
	}


	vector<string> result;
	int cutAt;
	while ((cutAt = oi.find_first_of(",")) != oi.npos) {
		if (cutAt > 0) {
			result.push_back(oi.substr(0, cutAt));
		}
		oi = oi.substr(cutAt + 1);
	}
	if (oi.length() > 0) {
		result.push_back(oi);
	}
	return result;
}



 






int main(int argc, TCHAR* argv[])
{
	 
	system("pause");

}

/*


Inicio:
	int a;
	cout << ".----. .----. .----. .----. .----. .----. .----..-. .-." << endl;
	cout << "| {}  }| {}  }| {_  { {__  /  {}  \\| {}  \\| {_  | | | |" << endl;
	cout << "| {}  }| .-. \\| {__ .-._} }\\      /|     /| {__ \\ \\_/ /" << endl;
	cout << "`----' `-' `-'`----'`----'  `----' `----' `----' `---' " << endl;
	cout << "" << endl;
	cout << "" << endl;
	cout << "1: Preparar Crossmap para o site" << endl;
	cout << "2: Gerar Crossmap a partir do site" << endl;
	cout << "3: Sair" << endl;
	cout << "" << endl;
	cout << "Escolha uma opcao:" << endl;
	cout << "" << endl;
	cin >> a;
	if (a == 1)
	{
		Crossmap::Preparar_Crossmap_site("CrossMapping.cpp", "Table.txt", "Hash.txt");
		cout << "" << endl;
		system("pause");
		system("cls");
		goto Inicio;
	}
	if (a == 2)
	{
		Crossmap::GerarCrossmap();
		cout << "" << endl;
		system("pause");
		system("cls");
		goto Inicio;
	}
	if (a == 3)
	{
	}

	*/
