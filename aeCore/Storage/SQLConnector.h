/**********************************************************************************************//**
 * @file	SQLConnector.h
 *
 * @brief	Declares the SQL connector class.
 **************************************************************************************************/

#pragma once
/************************************************************************************************************************/
/* Inclusion of the necessary header files.																				*/
/************************************************************************************************************************/
#include <sqlite3.h>
#include <sstream>
#include "../PlatformDefinitions.h"

namespace aeCore
{
	/**********************************************************************************************//**
	 * @class	aeSQLConnector
	 *
	 * @brief	A SQL connector.
	 * 			This class purpose is to create a connection to the database using SQL commands.
	 *
	 **************************************************************************************************/

	class LIBRARY_EXPORT aeSQLConnector
	{
	private:
		/************************************************************************************************************************/
		/* Variable declaration									                												*/
		/************************************************************************************************************************/
		sqlite3* m_pDatabaseConnection;
	public:
		/************************************************************************************************************************/
		/* Constructors                                                        													*/
		/************************************************************************************************************************/
		aeSQLConnector();
		~aeSQLConnector();

		/************************************************************************************************************************/
		/* Functions declaration                                            													*/
		/************************************************************************************************************************/

		/**********************************************************************************************//**
		 * @fn	void aeSQLConnector::OpenDatabase(const char* file_name);
		 *
		 * @brief	Receives the file path or file name in case in the same carpet, opens the connection
		 * 			to the database to start making query requests.
		 *
		 * @param	file_name	Name of the file.
		 **************************************************************************************************/

		void OpenDatabase(const TCHAR* file_name);

		/**********************************************************************************************//**
		 * @fn	void aeSQLConnector::CloseDatabase();
		 *
		 * @brief	Closes the connection to the database.
		 **************************************************************************************************/

		void CloseDatabase();

		/**********************************************************************************************//**
		 * @fn	int aeSQLConnector::QueryDatabase( const char * sql_query, int(*QueryCallback)(void *, int, char **, char **), void * NonStaticObject);
		 *
		 * @brief	Executes a query request of a list and passes along a function that executes per line
		 * 			of the list.
		 *
		 * @param	sql_query			   	The SQL query.
		 * @param [in,out]	QueryCallback  	If non-null, the query callback.
		 * @param [in,out]	NonStaticObject	If non-null, the non static object.
		 *
		 * @return	The database.
		 **************************************************************************************************/

		int QueryDatabase(
			const TCHAR * sql_query,
			int(*QueryCallback)(void *, int, char **, char **),
			void * NonStaticObject);

		/**********************************************************************************************//**
		 * @fn	int aeSQLConnector::ExecStatement(const char * sql_query, int Size);
		 *
		 * @brief	Executes any kind of query request, it receives the command and the length in
		 * 			characters of the command.
		 *
		 * @param	sql_query	The SQL query.
		 * @param	Size	 	The size.
		 *
		 * @return	An int.
		 **************************************************************************************************/

		int ExecStatement(const TCHAR * sql_query, int Size);
	};

}