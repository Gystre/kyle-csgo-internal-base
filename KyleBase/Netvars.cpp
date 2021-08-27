#include "pch.h"
#include "Netvars.h"
#include "ClientClass.h"
#include "Interfaces.h"
#include "Fnv.h"

void NetvarManager::dumpTableRecursively(char* name, RecvTable* table, size_t offset)
{
	FnvHash base = FnvHash(name);
	for (auto i = 0; i < table->propsCount; ++i)
	{
		auto prop = &table->props[i];
		auto child = prop->dataTable;

		if (!prop || isdigit(prop->propName[0]))
			continue;
		if (strcmp(prop->propName, "baseclass") == 0)
			continue;

		//check if there is a table of netvars that need to dumped in the current table and dump those first
		if (prop->propType == SendPropType::DataTable && prop->dataTable != nullptr && prop->dataTable->tableName[0] == 'D' && child && child->propsCount > 0)
		{
			dumpTableRecursively(name, child, prop->offset + offset);
		}

		//otherwise, save the offset to the table
		FnvHash var = FnvHash(prop->propName);

		if (!netvarsMap[base][var].Offset)
		{
			netvarsMap[base][var].DataMapVar = false;
			netvarsMap[base][var].PropPtr = prop;
			netvarsMap[base][var].Offset = static_cast<size_t>(prop->offset + offset);
		}
	}
}

void NetvarManager::dumpTableRecursivelyToFile(char* name, RecvTable* table, std::ofstream& file, size_t offset)
{
	FnvHash base = FnvHash(name);
	for (auto i = 0; i < table->propsCount; ++i)
	{
		auto prop = &table->props[i];
		auto child = prop->dataTable;

		if (!prop || isdigit(prop->propName[0]))
			continue;
		if (strcmp(prop->propName, "baseclass") == 0)
			continue;

		//check if there is a table of netvars that need to dumped in the current table and dump those first
		if (prop->propType == SendPropType::DataTable && prop->dataTable != nullptr && prop->dataTable->tableName[0] == 'D' && child && child->propsCount > 0)
		{
			dumpTableRecursivelyToFile(name, child, file, prop->offset + offset);
		}

		//otherwise, save the offset to the table
		FnvHash var = FnvHash(prop->propName);

		if (!netvarsMap[base][var].Offset)
		{
			netvarsMap[base][var].DataMapVar = false;
			netvarsMap[base][var].PropPtr = prop;
			netvarsMap[base][var].Offset = static_cast<size_t>(prop->offset + offset);

			std::string hashString = table->tableName;
			hashString.append(" -> ");
			hashString.append(prop->propName);

			auto hash = FnvHash(hashString.c_str());

			hashString.append(" (");
			hashString.append(std::to_string(unsigned int(hash)));
			hashString.append(") [");

			std::stringstream stream;
			stream << "0x" << std::setfill('0') << std::setw(sizeof(int) * 2) << std::hex << prop->offset;
			hashString.append(stream.str());
			hashString.append("]");

			file << hashString << std::endl;
		}
	}
}

unsigned short NetvarManager::getOffset(const char* table, const char* prop)
{
	std::cout << "Offset: " << table << "->" << prop << ": 0x" << (DWORD)netvarsMap[FnvHash(table)][FnvHash(prop)].Offset << std::endl;
	return netvarsMap[FnvHash(table)][FnvHash(prop)].Offset;
}

RecvProp* NetvarManager::getProperty(const char* table, const char* prop)
{
	std::cout << "Property: " << table << "->" << prop << ": 0x" << (DWORD)netvarsMap[FnvHash(table)][FnvHash(prop)].PropPtr << std::endl;
	return netvarsMap[FnvHash(table)][FnvHash(prop)].PropPtr;
}

void NetvarManager::init()
{
	ClientClass* list = Interfaces::clientDll->GetClientClasses();

#ifdef _DEBUG
	std::ofstream output("NetvarsDump.txt");

	for (; list != nullptr; list = list->nextPtr)
	{
		dumpTableRecursivelyToFile(list->recvTablePtr->tableName, list->recvTablePtr, output);
	}

	output.close();
#else
	for (; list != nullptr; list = list->nextPtr)
	{
		dumpTableRecursively(list->recvTablePtr->tableName, list->recvTablePtr);
	}
#endif
}