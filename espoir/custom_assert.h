#pragma once

class CustomAssertException : std::exception{
public:
	const char* what() const throw(){return "�J�X�^���A�T�[�V�����G���[";};
};
namespace boost{
	//BOOST_ASSERT�̃J�X�^���A�T�[�g
	void assertion_failed(const char* expr, const char* function, const char* file, long line){
		OutputDebugStringA("\n--------------------------------------------�A�T�[�V�����I�I---------------------------------------\n");
		OutputDebugStringA( 
			boost::str(
			boost::format("����:%1%\n���֐�=%2%\n���\�[�X:%3%\n��%4%�s��\n\n\n") % expr % function % file % line).c_str() );
		throw CustomAssertException();
	}
}

//TEST(custom_assert_test, custom_assert_test){
//	ASSERT_ANY_THROW(BOOST_ASSERT(false));
//}