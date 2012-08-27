#pragma once
const int WM_MYNOTIFY = WM_APP + 100;
//const int WM_MYCOMMAND = WM_APP + 101;
namespace espoir{
	class Notify{
	private:
		boost::shared_ptr<NOTIFYICONDATA> notifyData;
	public:
		Notify();
		void sendMessage(const String& msg);
	};

	struct NotifyDeleter{
		void operator()(NOTIFYICONDATA* notifyData) throw(){
			if(notifyData != NULL){
				Shell_NotifyIcon(NIM_DELETE, notifyData);
				delete notifyData;
				notifyData = NULL;
			}
		}
	};
}