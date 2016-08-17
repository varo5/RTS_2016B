/**********************************************************************************************//**
 * @file	SQLConnector.cpp
 *
 * @brief	Implements the SQL connector class.
 **************************************************************************************************/

/************************************************************************************************************************/
/* Inclusion of the necessary header files.						          												*/
/************************************************************************************************************************/
#include "aeCoreStd.h"
#include "SQLConnector.h"

namespace aeCore
{
	aeSQLConnector::aeSQLConnector()
	{
		m_pDatabaseConnection = 0;
	}

	aeSQLConnector::~aeSQLConnector()
	{
	}

	void aeSQLConnector::OpenDatabase(const TCHAR * file_name)
	{
		if (m_pDatabaseConnection)
		{
			MessageBox(NULL, TEXT("Database already open."), TEXT("SQL error"), MB_ICONERROR);
			return;
		}

#if PLATFORM_TCHAR_IS_1_BYTE == 1
		int ret = sqlite3_open(file_name, &m_pDatabaseConnection);
#else
		int ret = sqlite3_open(ws2s(file_name).c_str(), &m_pDatabaseConnection);
#endif // PLATFORM_TCHAR_IS_1_BYTE == 1

		if (ret)
		{
			MessageBox(NULL, TEXT("Database couldn't be opened."), TEXT("SQL error"), MB_ICONERROR);
		}
	}

	void aeSQLConnector::CloseDatabase()
	{
		if (!m_pDatabaseConnection)
		{
			MessageBox(NULL, TEXT("Error Closing database."), TEXT("SQL error"), MB_ICONERROR);
			return;
		}
		sqlite3_close(m_pDatabaseConnection);
		m_pDatabaseConnection = NULL;
	}

	int aeSQLConnector::QueryDatabase(const TCHAR * sql_query, int(*callback)(void*, int, char**, char**), void * NonStaticObject)
	{
		if (m_pDatabaseConnection == NULL)
		{
			MessageBox(NULL, TEXT("Database not open."), TEXT("SQL error"), MB_ICONERROR);
			return -1;
		}
		char*zErrMsg = 0;
		int result = 0;
		if (NonStaticObject == NULL)
		{
			const char* data = "Callback function called";
#if PLATFORM_TCHAR_IS_1_BYTE == 1
			result = sqlite3_exec(m_pDatabaseConnection, sql_query, callback, (void*)data, &zErrMsg);
#else
			result = sqlite3_exec(m_pDatabaseConnection, ws2s(sql_query).c_str(), callback, (void*)data, &zErrMsg);
#endif // PLATFORM_TCHAR_IS_1_BYTE == 1
		}
		else
		{
#if PLATFORM_TCHAR_IS_1_BYTE == 1
			result = sqlite3_exec(m_pDatabaseConnection, sql_query, callback, NonStaticObject, &zErrMsg);
#else
			result = sqlite3_exec(m_pDatabaseConnection, ws2s(sql_query).c_str(), callback, NonStaticObject, &zErrMsg);
#endif // PLATFORM_TCHAR_IS_1_BYTE == 1
		}
		if (result != SQLITE_OK)
		{
			MessageBox(NULL, TEXT("Error reading database."), TEXT("SQL error"), MB_ICONERROR);
			sqlite3_free(zErrMsg);
			return -1;
		}
		return 0;
	}

	int aeSQLConnector::ExecStatement(const TCHAR * sql_query, int Size)
	{
		sqlite3_stmt * stmt;

#if PLATFORM_TCHAR_IS_1_BYTE == 1
		sqlite3_prepare_v2(m_pDatabaseConnection, sql_query, Size, &stmt, NULL);
#else
		sqlite3_prepare_v2(m_pDatabaseConnection, ws2s(sql_query).c_str(), Size, &stmt, NULL);
#endif // PLATFORM_TCHAR_IS_1_BYTE == 1
		if (sqlite3_step(stmt) != SQLITE_DONE)
		{
			MessageBox(NULL, TEXT("Didn't execute statement."), TEXT("SQL error"), MB_ICONERROR);
			sqlite3_finalize(stmt);
			return -1;
		}

		sqlite3_finalize(stmt);

		return 0;
	}
}