#include "stdafx.h"
#include "Generator.h"
#include "GeneratorDlg.h"
#include "GeneratorIniFile.h"

CGeneratorIniFile::CGeneratorIniFile( void ) {
}

CGeneratorIniFile::~CGeneratorIniFile( void ) {
}

int CGeneratorIniFile::OpenGeneratorIniFile( void ) {
	char strCmdLine[ 2007 ];
	FILE * hndlIniFile = NULL;

	lstrcpy( strCmdLine, GetCommandLine() );
	SetGeneratorPath( strCmdLine );

l1:
	if ( ( hndlIniFile = fopen( strGeneratorIniPath, "r" ) ) == NULL ) {
		if ( !CreateDefaultIniFile( strGeneratorIniPath ) ) {
			if ( MessageBox( NULL, "Невозможно открыть или создать \
файл \"generator.ini\".\n\nВы желаете повторить попытку?", 
					NULL, MB_ICONWARNING | MB_RETRYCANCEL ) == IDRETRY )
				goto l1;
		}	else
				MessageBox( NULL, "Загружены стандартные установки.\n\n\
Создан файл \"generator.ini\".", "Внимание", MB_ICONWARNING );
	} else {
		fclose( hndlIniFile );
		ReadAllFromIniFile( strGeneratorIniPath );
	}
	return 0;
}

int CGeneratorIniFile::SaveGeneratorIniFile( void ) {
	FILE * hndlIniFile = NULL;

l1:
	if ( ( hndlIniFile = fopen( strGeneratorIniPath, "w" ) ) == NULL ) {
		if ( !CreateDefaultIniFile( strGeneratorIniPath ) ) {
			if ( MessageBox( NULL, "Невозможно сохранить \
файл \"generator.ini\".\n\nВы желаете повторить попытку?", 
					NULL, MB_ICONWARNING | MB_RETRYCANCEL ) == IDRETRY )
				goto l1;
			else
				MessageBox( NULL, "Установки не были записаны в Файл \
\"generator.ini\".", NULL, MB_ICONWARNING );
		}
	} else {
		fclose( hndlIniFile );
		IniFile.ChosenClasses.strDefaultClass = IniFile.ChosenClasses.strChosenClass[ 0 ];
		WriteAllToIniFile( strGeneratorIniPath );
	}
	return 0;
}

void CGeneratorIniFile::SetGeneratorPath( char * argv0 ) {
	char strPathTmp[ 2009 ];
	char * pTmp;
	int iPathLen = MAX_PATH;

	// вырезаем кусок в первых двух кавычках
	pTmp = strchr( argv0, '\"' );
	if ( pTmp != NULL ) {
		pTmp = strchr( pTmp + 1, '\"' );
		iPathLen = pTmp - argv0 + 1;
		if ( pTmp == NULL ) // " не найдено
			iPathLen = lstrlen( argv0 );
	}

	pTmp = strrchr( lstrcpyn( strPathTmp, argv0, iPathLen ), '\\' );
	if ( pTmp == NULL || pTmp == strPathTmp ) { // вызвана относительным путем
		GetCurrentDirectory( MAX_PATH, strPathTmp );
		strGeneratorIniPath = strPathTmp;
		strGeneratorIniPath += "\\generator.ini";
		return;
	}
	iPathLen = pTmp - strPathTmp + 1;
	if ( pTmp == NULL ) // " не найдено
		iPathLen = lstrlen( strPathTmp );

	pTmp = strchr( argv0, '\"' );
	if ( pTmp == argv0 ) // " -- первый символ argv0
		lstrcpyn( strPathTmp, argv0 + 1, iPathLen );
	else
		lstrcpyn( strPathTmp, argv0, iPathLen );
	strGeneratorIniPath = strPathTmp;
	strGeneratorIniPath += "generator.ini";
}

bool CGeneratorIniFile::CreateDefaultIniFile( CString strIniFile ) {
	FILE * hndlIniFile = NULL;

	if ( ( hndlIniFile = fopen( strIniFile, "w" ) ) == NULL ) {
		ReadAllFromIniFile( strIniFile );
		return false;
	}
	fclose( hndlIniFile );
	ReadAllFromIniFile( strIniFile );
	return true;
}

void CGeneratorIniFile::ReadAllFromIniFile( CString strIniFile ) {
	char strBuf[ 2010 ];

	// [ChosenClasses]
	IniFile.ChosenClasses.iNumberOfChosenClasses = GetPrivateProfileInt( "Chosen Classes",
			"NumberOfChosenClasses", -1, strIniFile );

	if ( IniFile.ChosenClasses.iNumberOfChosenClasses == -1 ) { // -1 -- флаг, что Chosen Classes не найдено
		int i = 0;
		int itmp;
		CString str;
		// заполняем список классов
		str.LoadString( IDS_CLASSSTRINGS );
		while( 1 ) {
			itmp = str.Find( '\n' );
			if ( itmp == -1 )
				break;
			IniFile.ChosenClasses.strChosenClass[ i ] = str.Left( itmp );
			i++;
			str.Delete( 0, itmp + 1 );
		}
		IniFile.ChosenClasses.iNumberOfChosenClasses = i;
	} else {
		for ( int i = 0; i < IniFile.ChosenClasses.iNumberOfChosenClasses; i++ ) {
			wsprintf( strBuf, "ChosenClass%d", i + 1 );
			GetPrivateProfileString( "Chosen Classes", strBuf, "Error in generator.ini",
					strBuf, MAX_PATH, strIniFile );
			IniFile.ChosenClasses.strChosenClass[ i ] = strBuf;
		}
	}
	old_IniFile_ChosenClasses_iNumberOfChosenClasses = IniFile.ChosenClasses.iNumberOfChosenClasses;

	GetPrivateProfileString( "Chosen Classes", "DefaultClass", IniFile.ChosenClasses.strChosenClass[ 0 ],
			strBuf, MAX_PATH, strIniFile );
	IniFile.ChosenClasses.strDefaultClass = strBuf;


	// [General]
	// шрифт:
	if ( GetPrivateProfileStruct( "General", "Font", 
			&IniFile.Font.logfontLogFont, sizeof(IniFile.Font.logfontLogFont), 
			strIniFile ) == 0 ) { // если не удалось
		lstrcpy( IniFile.Font.logfontLogFont.lfFaceName, "Courier New" );
		IniFile.Font.logfontLogFont.lfClipPrecision = 0;
		IniFile.Font.logfontLogFont.lfEscapement = 0;
		IniFile.Font.logfontLogFont.lfCharSet = DEFAULT_CHARSET;
		IniFile.Font.logfontLogFont.lfHeight = -13;
		IniFile.Font.logfontLogFont.lfItalic = 0;
		IniFile.Font.logfontLogFont.lfOrientation = 0;
		IniFile.Font.logfontLogFont.lfOutPrecision = 0;
		IniFile.Font.logfontLogFont.lfPitchAndFamily = 0;
		IniFile.Font.logfontLogFont.lfQuality = 0;
		IniFile.Font.logfontLogFont.lfStrikeOut = 0;
		IniFile.Font.logfontLogFont.lfUnderline = 0;
		IniFile.Font.logfontLogFont.lfWeight = 400;
		IniFile.Font.logfontLogFont.lfWidth = 0;
	}
	if ( GetPrivateProfileStruct( "General", "FontColor", &IniFile.Font.FontColor,
			sizeof(IniFile.Font.FontColor), strIniFile ) == 0 )
		IniFile.Font.FontColor = 0;

	// кол-во отступов в ctrlResEdit
	IniFile.Tabs.iNumberOfTabs = GetPrivateProfileInt( "General",
			"NumberOfTabs", 4, strIniFile );
	IniFile.Tabs.iTabsOrSpaces = GetPrivateProfileInt( "General",
			"TabsOrSpaces", 1, strIniFile );
}

void CGeneratorIniFile::WriteAllToIniFile( CString strIniFile ) {
	char strBuf[ 2011 ];

	// [ChosenClasses]
	int itmp = 0;
	for( int i = 0; i < IniFile.ChosenClasses.iNumberOfChosenClasses; i++ ) {
		if ( IniFile.ChosenClasses.strChosenClass[ i ] != "" ) {
			itmp++;
			wsprintf( strBuf, "ChosenClass%d", itmp );
			WritePrivateProfileString( "Chosen Classes", strBuf,
					IniFile.ChosenClasses.strChosenClass[ i ], strIniFile );
		}
	}
	if ( old_IniFile_ChosenClasses_iNumberOfChosenClasses > IniFile.ChosenClasses.iNumberOfChosenClasses )
		for( int i = IniFile.ChosenClasses.iNumberOfChosenClasses; i < old_IniFile_ChosenClasses_iNumberOfChosenClasses; i++ ) {
			wsprintf( strBuf, "ChosenClass%d", i + 1 );
			WritePrivateProfileString( "Chosen Classes", strBuf,
					NULL, strIniFile );
		}

	wsprintf( strBuf, "%d", itmp );
	WritePrivateProfileString( "Chosen Classes", "NumberOfChosenClasses",
			strBuf, strIniFile );

	WritePrivateProfileString( "Chosen Classes", "DefaultClass",
			IniFile.ChosenClasses.strDefaultClass, strIniFile );

	// [General]
	// шрифт:
	Font.GetLogFont( &IniFile.Font.logfontLogFont );
	WritePrivateProfileStruct( "General", "Font", &IniFile.Font.logfontLogFont,
			sizeof(IniFile.Font.logfontLogFont), strIniFile );
	WritePrivateProfileStruct( "General", "FontColor", &IniFile.Font.FontColor,
			sizeof(IniFile.Font.FontColor), strIniFile );

	// кол-во отступов в ctrlResEdit
	wsprintf( strBuf, "%d", IniFile.Tabs.iNumberOfTabs );
	WritePrivateProfileString( "General", "NumberOfTabs",
			strBuf, strIniFile );
	wsprintf( strBuf, "%d", IniFile.Tabs.iTabsOrSpaces );
	WritePrivateProfileString( "General", "TabsOrSpaces",
			strBuf, strIniFile );
}
