// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
//

#pragma once


#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
#define D3D_DEBUG_INFO				//�E�H�b�`�E�B���h�E����Direct3D�̃f�o�b�O���̏ڍׂ������悤�ɂ��܂��B

// Windows �w�b�_�[ �t�@�C��:
#include <windows.h>
//#include<atlbase.h>
//extern CComModule _Module;
//#include<atlwin.h>

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

#include <shlwapi.h>

//��O�̃G���[�Ƃ�
#include <stdexcept>

//���������[�N���o
#include <crtdbg.h>

#include <boost/range/algorithm/for_each.hpp>
#include<boost/unordered_map.hpp>
#include<boost/intrusive_ptr.hpp>
#include<boost/shared_ptr.hpp>
#include<boost/make_shared.hpp>
#include<boost/shared_array.hpp>
#include<boost/scoped_ptr.hpp>
#include<boost/static_assert.hpp>
#include<boost/function.hpp>
#include <boost/foreach.hpp>

#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/array.hpp>
#include <boost/utility.hpp>
#include<boost/function.hpp>
#include<boost/bind.hpp>
#include<boost/signals2.hpp>
#include <boost/format.hpp>
#include <d3d9.h>
#include<d3dx9.h>
//#include<XInput.h>
//direct input 8 ���g��
#define DIRECTINPUT_VERSION 0x800
#include<dinput.h>
#include <boost/preprocessor.hpp>
#include <boost/scope_exit.hpp>
#include <gtest/gtest.h>

//for_each�łQ�̃R���e�i���珇�ԂɎ��o���Ă�������
#include<boost/range/combine.hpp>
#include<boost/range/counting_range.hpp>

//���^�n
#include <boost/function_types/result_type.hpp>

//���Z�q�̃I�[�o�[���[�h
#include<boost/operators.hpp>

//�}�N���W
#include"macro.h"

#include"point.h"
//#include"rect.h"
#include"typedef.h"
#include"config.h"

//Microsoft Visual C++����
#if defined(_MSC_VER)
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
//#pragma comment(lib, "XInput.lib")
#pragma comment(lib, "dinput8.lib")

#ifdef NDEBUG
	#pragma comment(lib, "gtest.lib")
	#pragma comment(lib, "gtest_main.lib")
#else
	#pragma comment(lib, "gtestd.lib")
	#pragma comment(lib, "gtest_maind.lib")
#endif
#endif



//���s��Comptr�^����

template <typename T> struct ComPtr_t{
    typedef ::_com_ptr_t<::_com_IIID< T , &__uuidof( T )>> type;
};







// TODO: �v���O�����ɕK�v�Ȓǉ��w�b�_�[�������ŎQ�Ƃ��Ă��������B
