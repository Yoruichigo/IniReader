/*

	�e�L�X�g�f�[�^��ǂݍ��ރN���X
	�\�[�X

*/

#include "stdafx.h"

#include "MyLibINIReader.h"



using namespace MyLib;



//�ǂݍ���
bool INIReader::LoadFile(const std::string _FileLocation)
{
	std::ifstream ifs(_FileLocation, std::ifstream::binary);
	if (ifs.fail())
	{
		std::cerr << "���s" << std::endl;
		ifs.close();
		return false;
	}

	std::string str(
		(std::istreambuf_iterator<char>(ifs)),
		std::istreambuf_iterator<char>());

	ifs.close();

	TextData = str;

	return true;
}





//�l�擾�@int
bool INIReader::GetPutValue(const std::string _Keyword, int* _Storage)
{
	//GetPutStringValue�ŕ�����̎擾��A�ϊ�
	std::string _stringvalue;
	if (GetPutStringValue(_Keyword,&_stringvalue) == false){
		return false;
	}

	//int�ϊ����A�����|�C���^�ɑ��
	(*_Storage) = std::stoi(_stringvalue);

	return true;
}



//�l�擾�@string
bool INIReader::GetPutStringValue(const std::string _Keyword, std::string* _Storage)
{
	//�L�[���[�h�̃C���f�b�N�X�ʒu
	int KeyIndexPos;
	KeyIndexPos = TextData.find_first_of(_Keyword);
	if (KeyIndexPos == std::string::npos){
		//���݂��Ȃ��Ȃ�I��
		return false;
	}

	//=��T��
	int EqualIndexPos;
	std::string str_Equal = "=";
	EqualIndexPos = TextData.find_first_of(str_Equal, KeyIndexPos);
	if (EqualIndexPos == std::string::npos ||
		EqualIndexPos != (KeyIndexPos + _Keyword.size())){
		//�����Ȃ玸�s
		return false;
	}

	//���s�܂ł�T��(npos�ł�����)
	int ValueLastIndex;
	int LFIndex;
	int CRIndex;
	std::string str_EndlLF = "\n";
	std::string str_EndlCR = "\r";
	LFIndex = TextData.find_first_of(str_EndlLF, EqualIndexPos);
	CRIndex = TextData.find_first_of(str_EndlCR, EqualIndexPos);

	//�Ō�(npos)
	if(LFIndex == std::string::npos && CRIndex == std::string::npos){
		ValueLastIndex = std::string::npos;
	}//���s�R�[�h�Q��
	else if (LFIndex != std::string::npos && CRIndex != std::string::npos){
		if (LFIndex < CRIndex){//LF��O
			ValueLastIndex = LFIndex;
		}
		else{//CR��O
			ValueLastIndex = CRIndex;
		}
	}//���s�R�[�h�P��
	else{
		if (LFIndex != std::string::npos){
			ValueLastIndex = LFIndex;
		}
		else if(CRIndex != std::string::npos){
			ValueLastIndex = CRIndex;
		}
		else{//�G���[
			return false;
		}
	}


	//�������X�g���[�W�Ɋi�[����
	if (ValueLastIndex != std::string::npos){
		(*_Storage) = TextData.substr(
			(EqualIndexPos + 1),
			(ValueLastIndex - EqualIndexPos));
	}
	else{
		(*_Storage) = TextData.substr(
			(EqualIndexPos + 1),
			ValueLastIndex);
	}

	return true;
}
