#pragma once

class DVariant;
class RecvTable;
class RecvProp;
class CRecvProxyData;

using RecvVarProxyFn = void(*)(const CRecvProxyData* data, void* structPtr, void* outPtr);
using ArrayLengthRecvProxyFn = void(*)(void* structPtr, int objectId, int currentArrayLength);
using DataTableRecvVarProxyFn = void(*)(const RecvProp* prop, void** outPtr, void* dataPtr, int objectId);

enum SendPropType {
	Int = 0,
	Float,
	Vec,
	VecXY,
	String,
	Array,
	DataTable,
	Int64,
};
class DVariant {
public:
	union {
		float m_float;
		long m_int;
		char* m_string;
		void* m_data;
		float m_vector[3];
		__int64 m_int64;
	};
	SendPropType type;
};
class CRecvProxyData {
public:
	const RecvProp* RecvProp;
	char _pad[4];//csgo ( for l4d keep it commented out :) )
	DVariant value;
	int elementIndex;
	int objectId;
};
class RecvProp {
public:
	char* propName;
	SendPropType propType;
	int propFlags;
	int bufferSize;
	int isInsideOfArray;
	const void* extraDataPtr;
	RecvProp* arrayProp;
	ArrayLengthRecvProxyFn arrayLengthProxyFn;
	RecvVarProxyFn proxyFn;
	DataTableRecvVarProxyFn dataTableProxyFn;
	RecvTable* dataTable;
	int offset;
	int elementStride;
	int elementsCount;
	const char* parentArrayPropName;
};
class RecvTable {
public:
	RecvProp* props;
	int propsCount;
	void* decoderPtr;
	char* tableName;
	bool isInitialized;
	bool isInMainList;
};