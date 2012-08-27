#pragma once

class CustomAssertException : std::exception{
public:
	const char* what() const throw(){return "カスタムアサーションエラー";};
};
namespace boost{
	//BOOST_ASSERTのカスタムアサート
	void assertion_failed(const char* expr, const char* function, const char* file, long line){
		OutputDebugStringA("\n--------------------------------------------アサーション！！---------------------------------------\n");
		OutputDebugStringA( 
			boost::str(
			boost::format("△式:%1%\n△関数=%2%\n△ソース:%3%\n△%4%行目\n\n\n") % expr % function % file % line).c_str() );
		throw CustomAssertException();
	}
}

//TEST(custom_assert_test, custom_assert_test){
//	ASSERT_ANY_THROW(BOOST_ASSERT(false));
//}