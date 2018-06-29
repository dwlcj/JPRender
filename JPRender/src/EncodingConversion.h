#ifndef __LIB_1__
#define __LIB_1__
namespace{

	//---------����
	 std::wstring charToWChar(const char* src){
		int dwUnicodeLen = MultiByteToWideChar(CP_ACP, 0, src, -1, NULL, 0);
		size_t num = dwUnicodeLen*sizeof(wchar_t);
		wchar_t *pwText = (wchar_t*)malloc(num);
		memset(pwText, 0, num);
		MultiByteToWideChar(CP_ACP, 0, src, -1, pwText, dwUnicodeLen);
		int unicode_number = dwUnicodeLen - 1;
		
		std::wstring wOut = pwText;
		free(pwText);
		return wOut;
	}
	 std::string WideCharToChar(wchar_t* pWCHAR)
	{
		//������Ҫ���ٸ��ֽڲ��ܱ�ʾ��Ӧ�Ķ��ֽ��ַ���  
		DWORD num = WideCharToMultiByte(CP_ACP, 0, pWCHAR, -1, NULL, 0, NULL, 0);

		//���ٿռ�  
		char *pChar = NULL;
		pChar = (char*)malloc(num*sizeof(char));
		if (pChar == NULL)
		{
			free(pChar);
		}
		memset(pChar, 0, num*sizeof(char));

		//�����ֽ��ַ���ת��Ϊ���ֽ��ַ���  
		WideCharToMultiByte(CP_ACP, 0, pWCHAR, -1, pChar, num, NULL, 0);
		std::string wOut = pChar;
		free(pChar);
		return wOut;
	}
	//---------����

	 std::wstring AsciiToUnicode(const std::string& str) {
		 // Ԥ��-�������п��ֽڵĳ���    
		 int unicodeLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
		 // ��ָ�򻺳�����ָ����������ڴ�    
		 wchar_t *pUnicode = (wchar_t*)malloc(sizeof(wchar_t)*unicodeLen);
		 // ��ʼ�򻺳���ת���ֽ�    
		 MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, pUnicode, unicodeLen);
		 std::wstring ret_str = pUnicode;
		 free(pUnicode);
		 return ret_str;
	 }
	 std::string UnicodeToAscii(const std::wstring& wstr) {
		 // Ԥ��-�������ж��ֽڵĳ���    
		 int ansiiLen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
		 // ��ָ�򻺳�����ָ����������ڴ�    
		 char *pAssii = (char*)malloc(sizeof(char)*ansiiLen);
		 // ��ʼ�򻺳���ת���ֽ�    
		 WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
		 std::string ret_str = pAssii;
		 free(pAssii);
		 return ret_str;
	 }
	 std::wstring Utf8ToUnicode(const std::string& str) {
		 // Ԥ��-�������п��ֽڵĳ���    
		 int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
		 // ��ָ�򻺳�����ָ����������ڴ�    
		 wchar_t *pUnicode = (wchar_t*)malloc(sizeof(wchar_t)*unicodeLen);
		 // ��ʼ�򻺳���ת���ֽ�    
		 MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, pUnicode, unicodeLen);
		 std::wstring ret_str = pUnicode;
		 free(pUnicode);
		 return ret_str;
	 }
	 std::string UnicodeToUtf8(const std::wstring& wstr) {
		 // Ԥ��-�������ж��ֽڵĳ���    
		 int ansiiLen = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
		 // ��ָ�򻺳�����ָ����������ڴ�    
		 char *pAssii = (char*)malloc(sizeof(char)*ansiiLen);
		 // ��ʼ�򻺳���ת���ֽ�    
		 WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
		 std::string ret_str = pAssii;
		 free(pAssii);
		 return ret_str;
	 }
	 std::string AsciiToUtf8(const std::string& str) {
		 return UnicodeToUtf8(AsciiToUnicode(str));
	 }
	 std::string Utf8ToAscii(const std::string& str) {
		 return UnicodeToAscii(Utf8ToUnicode(str));
	 }
}
#endif /*__LIB_1__*/
