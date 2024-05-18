#pragma once

class registryOps_ {
public:
	void ListRegistryValues(HKEY hKey, LPCWSTR subkey);
	void getTypeAndContent();
	void RegFlow();
	LONG GetDWORDRegKey(HKEY hKey, const std::wstring& strValueName, DWORD& nValue, DWORD nDefaultValue);
	LONG GetBoolRegKey(HKEY hKey, const std::wstring& strValueName, bool& bValue, bool bDefaultValue);
	LONG GetStringRegKey(HKEY hKey, const std::wstring& strValueName, std::wstring& strValue, const std::wstring& strDefaultValue);
	
};