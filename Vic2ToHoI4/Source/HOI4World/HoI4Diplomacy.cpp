/*Copyright (c) 2016 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#include "HoI4Diplomacy.h"
#include "Log.h"
#include "../Configuration.h"



void HoI4Diplomacy::output() const
{
	FILE* alliances;
	if (_wfopen_s(&alliances, (L"Output\\" + Configuration::getOutputName() + L"\\history\\diplomacy\\Alliances.txt").c_str(), L"w") != 0)
	{
		LOG(LogLevel::Error) << "Could not create alliances history file";
		exit(-1);
	}

	FILE* guarantees;
	if (_wfopen_s(&guarantees, (L"Output\\" + Configuration::getOutputName() + L"\\history\\diplomacy\\Guarantees.txt").c_str(), L"w") != 0)
	{
		LOG(LogLevel::Error) << "Could not create guarantees history file";
		exit(-1);
	}

	FILE* puppetStates;
	if (_wfopen_s(&puppetStates, (L"Output\\" + Configuration::getOutputName() + L"\\history\\diplomacy\\PuppetStates.txt").c_str(), L"w") != 0)
	{
		LOG(LogLevel::Error) << "Could not create puppet states history file";
		exit(-1);
	}

	FILE* relations;
	if (_wfopen_s(&relations, (L"Output\\" + Configuration::getOutputName() + L"\\history\\diplomacy\\relations.txt").c_str(), L"w") != 0)
	{
		LOG(LogLevel::Error) << "Could not create relations history file";
		exit(-1);
	}
	
	FILE* out;
	for (vector<HoI4Agreement>::const_iterator itr = agreements.begin(); itr != agreements.end(); ++itr)
	{
		if (itr->type == L"guarantee")
		{
			out = guarantees;
		}
		else if (itr->type == L"vassal")
		{
			out = puppetStates;
		}
		else if (itr->type == L"alliance")
		{
			out = alliances;
		}
		else if (itr->type == L"relation")
		{
			out = relations;
		}
		else
		{
			LOG(LogLevel::Warning) << "Cannot ouput diplomatic agreement type " << itr->type;
			continue;
		}
		fwprintf(out, L"%s=\n", itr->type.c_str());
		fwprintf(out, L"{\n");
		fwprintf(out, L"\tfirst=\"%s\"\n", itr->country1.c_str());
		fwprintf(out, L"\tsecond=\"%s\"\n", itr->country2.c_str());
		if (itr->type == L"relation")
		{
			fwprintf(out, L"\tvalue=\"%i\"\n", itr->value);
		}
		fwprintf(out, L"\tstart_date=\"%s\"\n", itr->start_date.toString().c_str());
		fwprintf(out, L"\tend_date=\"1949.1.1\"\n");
		fwprintf(out, L"}\n");
		fwprintf(out, L"\n");
	}
	
	fclose(alliances);
	fclose(guarantees);
	fclose(puppetStates);
	fclose(relations);
}

void HoI4Diplomacy::addAgreement(const HoI4Agreement agr)
{
	bool alreadyExists = false;

	if (agr.type == L"relation")
	{
		for (vector<HoI4Agreement>::const_iterator itr = agreements.begin(); itr != agreements.end(); ++itr)
		{
			if (agr == *itr)
			{
				alreadyExists = true;
				break;
			}
		}
	}

	if (!alreadyExists)
	{
		agreements.push_back(agr);
	}
}