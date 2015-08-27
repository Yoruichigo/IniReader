/*

	�e�L�X�g�f�[�^��ǂݍ��ރN���X
	�w�b�_

	
	GetValue/GetStringValue�́A
	���p�C�R�[���u=�v�ő�����Ă���L�[���[�h�ɂ̂�
	�Ή����Ă��܂��B
*/

#pragma once

#include <windows.h>
#include <fstream>
#include <iostream>
#include <string>


namespace MyLib
{

	class INIReader{
	public:
		INIReader(){};
		~INIReader(){};

		//�w�肳�ꂽ�t�@�C����ǂݍ��݂܂�(false���s)
		bool LoadFile(const std::string _FileLocation);

		//�L�[���[�h�ɑ�����ꂽ�l���A�n���ꂽ�ϐ��ɓ���܂�(int�^)
		bool GetPutValue(const std::string _Keyword, int* _Storage);

		//�L�[���[�h�ɑ�����ꂽ�l���A�n���ꂽ�ϐ��ɓ���܂�(string�^)
		bool GetPutStringValue(const std::string _Keyword, std::string* _Storage);

		//�f�[�^���擾���܂�
		inline std::string GetData()const{
			return TextData;
		}

	private:
		std::string TextData;
	};

}