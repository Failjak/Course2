#include "Convert.h"

namespace Convert
{
	const std::wstring S2WS(const std::string &s)
	{
		wstring ws;
		std::wstring wsTmp(s.begin(), s.end());

		ws = wsTmp;

		return ws;
	}

	std::string WS2S(const std::wstring& wstr)
	{
		using convert_typeX = codecvt_utf8<wchar_t>;
		wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.to_bytes(wstr);
	}

	vector<vector<wstring>> VVS2VVWS(const vector<vector<string>> vvs)
	{
		vector<vector<wstring>> vvws;
		wstring ws;

		for (int i = 0; i < vvs.size(); i++)
		{
			vvws.push_back(vector<wstring>());
			for (int j = 0; j < vvs[i].size(); j++)
			{
				std::wstring wsTmp(vvs[i][j].begin(), vvs[i][j].end());
				ws = wsTmp;
				vvws[i].push_back(ws);
			}
		}
		return vvws;
	}
}