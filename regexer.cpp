#include "stdafx.h"
#include "regexer.h"

using namespace regex;
using namespace std;

typedef vector<string> strvec;

// ѕравила по умолчанию
// лучше сделать символьный массив с содержимым rules.ini
// и парсить его как файл 
void REParser::defrules()
{
	
	string dfltrulesR[][3]=
	{ 	{"PF","йки","ек"}, 
		{"PF","(6)ки","$1ек"},
		{"PF","6)ки","$1ок"},
		{"PF","ки","к"},
		{"P","ки","ков"},
		{"PF","(6)ги","г"},
		{"P","ги","гов"},
		{"PF","ки","к"},
		{"PF","(у6)и","$1"},
		{"F","ка","ке"},
		{"PF","(.)ы ","$1"}	};
	string dfltrulesD[][3]=
	{{"","",""}};
	string dfltrulesV[][3]=
	{	{"PFA","йки","ек"},
		{"PFA","(4)ки","$1ек"},
		{"PFA","(0)ки","$1ок"},
		{"PFA","ки","к"},
		{"PA","ки","ков"},
		{"PFA","(6)ги","$1ог"},
		{"PFA","ги","г"},
		{"PFA","(0)ки","$1ок"},
		{"PA","ги","гов"}	};
	string dfltrulesT[][3]=
	{{"","(4)а","$1ей"}};
	string dfltrulesT2[][3]=
	{	{"S","(4)а","$1ею"},
		{"S","а","ою"},
		{"SF","(.)","$1ю"},
		{"S","а€","ою"}
	};
	string dfltrulesP[][3]=
	{{"","",""}};
	string dfltrulesC[][8]=
	{ 
		{ "PU", "8и", "_ев", "_€м", "_и", "_ев", "_€ми", "_€х" }, 
		{ "SBE", "34", "df", "SBE", "34", "df", "SBE" },
		{ "a", "56", "jh", "SBE", "34", "df", "SBE"},
		{ "nU", "5v", "45", "SBE", "34", "df", "SBE"} 
	};
	string dfltrulesVerb[][3]=
	{ 	{ "Abs","123","321" }	};
	
	struct formular_t
	{
		std::string (*arr)[3];
		size_t size;
	};

	vector< vector<COneCaseRule> > cases(6);
	cases.push_back(Geni); cases.push_back(Dati);
	cases.push_back(Accu);cases.push_back(Inst);
	cases.push_back(Inst2);cases.push_back(Prep);


	formular_t formular[6]= {
        {dfltrulesR, sizeof(dfltrulesR)/sizeof(*dfltrulesR)},
        {dfltrulesD, sizeof(dfltrulesD)/sizeof(*dfltrulesD)},
		{dfltrulesV, sizeof(dfltrulesV)/sizeof(*dfltrulesV)},
		{dfltrulesT, sizeof(dfltrulesT)/sizeof(*dfltrulesT)},
		{dfltrulesT2, sizeof(dfltrulesT2)/sizeof(*dfltrulesT2)},
		{dfltrulesP, sizeof(dfltrulesP)/sizeof(*dfltrulesP)},
    };

    for(size_t f = 0; f < sizeof(formular)/sizeof(*formular); f++)
    {
        for(size_t r = 0; r < formular[f].size; r++)
        {
			COneCaseRule newrule( readOpts(formular[f].arr[r][0]), formular[f].arr[r][1], formular[f].arr[r][2] );
			cases[f].push_back(newrule);
		}
	}
};

// ‘ункци€ чтени€ правил
void REParser::readrules(LPSTR fname)
{
    FILE *f;

	// пытаемс€ открыть файл
	if (!(f = fopen(fname, "r")))
	{
		this->defrules();	// загружаем правила по-умолчанию
		return;
	}

	string text, mode="", word_set_name="";
	char instr[MAX_STRLEN];
	match_results results;
	subst_results sub_results;
	int opts=0;

	vector<COneCaseRule> *ruleslist[6]={&Geni, &Dati, &Accu, &Inst, &Inst2, &Prep};
		
	// построчно читаем файл
	while (fgets( instr, MAX_STRLEN, f)!=NULL) 
	{
        text = instr;

		// провер€ем наличие директивы (метки)
		if (instr[0]=='#')
		{
            static const rpattern pat( MARK_SCHEME );
			match_results::backref_type basmat = pat.match( text, results, 0 );
			if (basmat.matched) mode = results.backref(1).str();
		}

		if (mode.size()>1 && text.size()>1)		// не будем парсить лишний раз
		{
			if (mode=="символы")
			{
				static const rpattern pat( SYM_SCHEME );

				match_results::backref_type basmat = pat.match( text, results, 0 );
				if (basmat.matched)
				{
					symbols.push_back( results.backref(1).str() );
					symbols.push_back( results.backref(2).str() );
				}
			}
			else
			if (mode=="все")
			{
				// проверка правила обычного падежа
				static const rpattern pat( COMMON_SCHEME );

				match_results::backref_type basmat = pat.match( text, results, 0 );
				if (basmat.matched)
				{
					int opts = readOpts(results.backref(1).str());
					string strpattern = results.backref(2).str()+"$";

					// мен€ем цифры на строки
					for (int i=0; i<symbols.size()/2; i++)
					{
						rpattern s_crlf( symbols[i*2] , symbols[i*2+1], GLOBAL );
						s_crlf.substitute( strpattern, sub_results );
					}

					CCommonCaseRule newrule(opts, strpattern, results.backref(3).str(),
						results.backref(4).str(),results.backref(5).str(),results.backref(6).str(),
						results.backref(7).str());
					CRules.push_back(newrule);
				}
			}
			else
			{
				// правила на один падеж
				static const rpattern pat( SCHEME );

				match_results::backref_type basmat = pat.match( text, results, 0 );
				if (basmat.matched)
				{
					if (mode=="родительный") opts=GENITIVE;
                    if (mode=="дательный") opts=DATIVE;
                    if (mode=="винительный") opts=ACCUSATIVE;
					if (mode=="творительный") opts=INSTRUMENTAL;
					if (mode=="творительный2") opts=INSTRUMENTAL2;
					if (mode=="предложный") opts=PREPOSITIONAL;

					opts |= readOpts(results.backref(1).str());

					string strpattern = results.backref(2).str()+"$";

					// мен€ем цифры на строки
					for ( int i=0; i<symbols.size()/2; i++ )
					{
						rpattern s_crlf( symbols[i*2] , symbols[i*2+1], GLOBAL );
						s_crlf.substitute( strpattern, sub_results );
					}

					COneCaseRule newrule( opts, strpattern, results.backref(3).str() );
					ruleslist[((opts&ALL)>>8)-1]->push_back(newrule);
				}
			}
		}
	}
	fclose(f);
};

// –асшифровка опций из строки и первод в битовый код
int REParser::readOpts(string opts)
{
		char str[MAX_STRLEN];
		strncpy(str,opts.c_str(),16);

		int len = strlen(str);
		unsigned int result=0;

		for (int i=0; i<len; i++) 
		{
            switch(str[i])
			{
				case 'S':  result|=SINGL; break;
				case 'P':  result|=PLURAL; break;
				case 'N':  result|=NEUTER; break;
				case 'M':  result|=MALE; break;
				case 'F':  result|=FEMALE; break;
				case 'A':  result|=ANIMATE; break;
				case 'U':  result|=UDAR; break;
				case 'n':  result|=NOUN; break;
				case 'a':  result|=ADJ; break;
			}
		}

		return result;
}

void REParser::init()
{
	// пополн€ем набор встроенных escape-последовательностей
	// \R - русские и ангийские словарные символы +  '$'  +  '('  +  ')'
	perl_syntax<char>::register_intrinsic_charset( 'R', "[а-€ј-я\\w()\$]" );
};

// ¬озвращает выбранный падеж
string	REParser::TakePad(string in, int mode)
{
	bool found=false;
	match_results results;
	subst_results sub_results;
	
	// сначала обрабатываем частные случаи
	vector<COneCaseRule> *ruleslist[6]={&Geni, &Dati, &Accu, &Inst, &Inst2, &Prep};
	int	indx = ((mode&ALL)>>8)-1;

	for (int i=0; i<ruleslist[indx]->size() && !found; i++)
	{
		const int opts = (*ruleslist)[indx][i].getOpts();
		if ( ( !((opts^mode)&3) || !(opts&3) ) && ( !((opts^mode)&12) || !(opts&12) ) &&  ( !((opts^mode)&UDAR) || !(opts&UDAR) ) 
			&& ( !((opts^mode)&ANIMATE) || !(opts&ANIMATE) ) && (!(opts&NOUN) || !((opts^mode)&NOUN)) && (!(opts&ADJ) || !((opts^mode)&ADJ)) )
		{
			rpattern pat( (*ruleslist)[indx][i].getPatternStr() );
			match_results::backref_type basmat = pat.match( in, results, 0 );
			if (basmat.matched)
			{
				rpattern s_crlf( (*ruleslist)[indx][i].getPatternStr(), (*ruleslist)[indx][i].getReplaceStr(), RIGHTMOST );
				s_crlf.substitute( in, sub_results );
				return in;
			}
		}
	}

	// обрабатываем общий случай
	for ( i=0; i<CRules.size() && !found; i++)
	{
		const int opts = CRules[i].getOpts();
		if ( ( !((opts^mode)&3) || !(opts&3) ) && ( !((opts^mode)&12) || !(opts&12) ) && ( !((opts^mode)&UDAR) || !(opts&UDAR) )
			&& ( !((opts^mode)&ANIMATE) || !(opts&ANIMATE) ) && (!(opts&NOUN) || !((opts^mode)&NOUN)) && (!(opts&ADJ) || !((opts^mode)&ADJ)) )
		{
			rpattern pat( CRules[i].getPatternStr() );
			match_results::backref_type basmat = pat.match( in, results, 0 );
			if (basmat.matched)
			{
				rpattern s_crlf( CRules[i].getPatternStr(), CRules[i].getCase(mode), RIGHTMOST );

				s_crlf.substitute( in, sub_results );
				return in;
			}
		}
	}

	return in;
};

//---------------------------------------------------------------------------
// ѕробел?
bool isspace1( char c ) {
	if ( c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == 0 )
		return true;
	return false;
}
//---------------------------------------------------------------------------
// подсчитать кол-во слов в строке
int StrCount( string  str ) {
	char strin[2550];

	strcpy(strin,str.c_str());

	int cnt=0, len, mlen = (int) strlen( strin );


	for (int i=0; i<mlen; i++) {
		for ( len=0; ( !isspace1( strin[i+len]) ) && ( i+len != mlen ); len++ );
		if ( len > 0)
			cnt++;
		i += len;
	}
	return cnt;
}

//---------------------------------------------------------------------------
// вз€ть слово по неомеру в строке
string TakeWord( int num, string oldStr) {

	char oldstr[2000],newstr[2000];
	std::string newStr;
	
	strcpy(oldstr, oldStr.c_str());
	
	int svstr=0, len, mlen = (int) strlen(oldstr);

	for (int i=0; i<mlen; i++) {
		for ( len=0;(!isspace1(oldstr[i+len]))&&(i+len<mlen);len++ );
		if ( len > 0 ) {
			if ( num == ( svstr + 1 ) ) {
				for ( int j=i ; j <= i + len ; j++ ) 
					newstr[ j - i ] = oldstr[ j ];
				if (isspace1(oldstr[i+len]))
					newstr[len]=0; 
				else 
					newstr[len+1]=0;
                newStr = newstr;
				return newStr;
			}
			i += len;
			svstr++;
		}
	}
	lstrcpy( newstr, "error" );
	newStr = newstr;
	return newStr;
}

//---------------------------------------------------------------------------
// длина предложени€ до предлогов
int StrCount1( string strin ) {
	match_results results;
	static const rpattern pat( PREPOSIT );

	int cnt=0, len;
	int mlen = strin.size();
	string lstw;

	for (int i=0; i<mlen; i++) {
		for (len=0;(!isspace1(strin.c_str()[i+len]))&&(i+len!=mlen);len++);
		if (len>0)	cnt++;
		i+=len;
		lstw = TakeWord( cnt, strin );
		match_results::backref_type basmat = pat.match( lstw, results, 0 );
		if 	(basmat.matched && cnt > 1 )	return ( cnt-1 ); 
		}
	return cnt;
}

//---------------------------------------------------------------------------
string toLowWithE( string str ) {
    char up[] =   "јЅ¬√ƒ≈®Є∆«»… ЋћЌќѕ–—“”‘’„÷ЎўЏџ№Ёёя"; 
    char down[] = "абвгдееежзийклмнопрстуфхчцшщъыьэю€";
	char s[2000];

	strncpy(s,str.c_str(),1999);

    for ( int i = 0; i < (int) strlen( s ); i++ )
	{
        for ( int j = 0; j < (int) strlen( up ); j++ )
            if ( s[i] == up[j] )
				s[i] = down[j];
	}

	return s;
}

//---------------------------------------------------------------------------
int strcmpe( string str, string str1) {
	int len1 = str.size();
	int len2 = str1.size();
	int i=0;
	for (i=0; i<len1 && i<len2; i++)
	{
		if ((i==len1 || i==len2) || (str.c_str()[i]!=str1.c_str()[i])) return i;
	}
	return i;
}