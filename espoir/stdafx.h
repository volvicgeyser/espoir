// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
// Windows �w�b�_�[ �t�@�C��:
#include <windows.h>

// C �����^�C�� �w�b�_�[ �t�@�C��
#ifdef OLD_CODE
#include <cstdlib>
#include <malloc.h>
#include <memory.h>
#endif
#include<iostream>
#include <tchar.h>
#include<string>
#include<sstream>
#include<vector>
#include <comip.h>

//��O�̃G���[�Ƃ�
#include <stdexcept>

//���������[�N���o
#include <crtdbg.h>

#include<boost/unordered_map.hpp>
#include<boost/shared_ptr.hpp>
#include<boost/scoped_ptr.hpp>
#include<boost/function.hpp>

#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/array.hpp>
#include <boost/utility.hpp>
#include<boost/function.hpp>
#include<boost/bind.hpp>
#include<boost/signals2.hpp>
//#include <boost/format.hpp>
#include <d3d9.h>
#include <boost/preprocessor.hpp>

//�}�N���W
#include"macro.h"

#include"point.h"
#include"rect.h"
#include"typedef.h"
#include"config.h"



//���s���^����
template <typename T> struct ComPtr{
	typedef ::_com_ptr_t<::_com_IIID< T , &__uuidof( T )>> type;
};



// TODO: �v���O�����ɕK�v�Ȓǉ��w�b�_�[�������ŎQ�Ƃ��Ă��������B
