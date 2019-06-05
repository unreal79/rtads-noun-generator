#pragma once

class CGeneratorIniFile {

	private:
		static void SetGeneratorPath( char * argv0 );
		static void ReadAllFromIniFile( CString strIniFile );
		static bool CreateDefaultIniFile( CString strIniFile );
		static void WriteAllToIniFile( CString strIniFile );

	public:
		CGeneratorIniFile( void );
		~CGeneratorIniFile( void );

		static int OpenGeneratorIniFile( void );
		static int SaveGeneratorIniFile( void );
};

extern structIniFile IniFile;
extern CString strGeneratorIniPath;
extern int old_IniFile_ChosenClasses_iNumberOfChosenClasses;
extern CFont Font;
