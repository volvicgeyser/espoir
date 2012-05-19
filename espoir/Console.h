#pragma once

namespace espoir{
	class Console{
	private:
	public:
		Console();
	};

	struct ConsoleDeleter{
		template<class T>
		void operator()(T* ptr){
			BOOST_ASSERT(ptr);
			FreeConsole();
			delete ptr;
			ptr = NULL;
		}
	};
}