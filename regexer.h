#include "Resource.h"

#define MAX_STRLEN 512

#define MALE		  1		// ... 0000 0001
#define FEMALE	      2		// ... 0000 0010
#define NEUTER        3		// ... 0000 0011

#define SINGL         4		// ... 0000 0100
#define PLURAL        8		// ... 0000 1000

#define UDAR		  16	// ... 0001 0000

#define NOUN		  32	// ... 0010 0000
#define ADJ			  64	// ... 0100 0000

#define ANIMATE		  128	// ... 1000 0000

#define GENITIVE      256	// 0000 0001 ...
#define DATIVE        512	// 0000 0010 ...
#define ACCUSATIVE    768	// 0000 0011 ...
#define INSTRUMENTAL  1024	// 0000 0100 ...
#define INSTRUMENTAL2 1280	// 0000 0101 ...
#define PREPOSITIONAL 1536	// 0000 0110 ...
#define ALL			  1792	// 0000 0111 ...
#define VERB		  2048	// 0000 1000 ...


#define SYM_SCHEME	"^[ \t]*(\\d)[ \t]+(\\S{1,90});"
#define SCHEME	"^[ \t]*([SPNMFAUna]{0,10})[ \t]+(\\R{1,36})[ \t]+(\\R{1,40});"
#define COMMON_SCHEME	"^[ \t]*([SPNMFAUna]{0,9})[ \t]+(\\R{1,36})[ \t]+(\\R{1,40})[ \t]+(\\R{1,40})[ \t]+(\\R{1,40})[ \t]+(\\R{1,40})[ \t]+(\\R{1,40});"
//                                 опции                  именител.          родит.          дательн.           винит.         творит.         предлож. 
#define COMMON_SCHEME2	"^[ \t]*([SPNMFAUna]{0,9})[ \t]+(\\R{1,36})[ \t]+(\\R{1,40})[ \t]+(\\R{1,40})[ \t]+(\\R{1,40})[ \t]+(\\R{1,40})[ \t]+(\\R{1,40})[ \t]+(\\R{1,40});"
//                                 опции                  именител.          родит.          дательн.           винит.         творит.         творит.2         предлож. 
#define MARK_SCHEME	"^\#[ \t]{0,3}(символы|родительный|дательный|винительный|творительный[ \t]|творительный2|предложный|все|глаголы|словарная группа)"
#define PREPOSIT	"^(в|вдоль|во|для|до|за|из|из-за|к|ко|между|на|над|о|об|обо|от|при|по|под|про|против|с|сквозь|со|через|у)$"
#define WORD_SET	"^#[ \t]{0,3}словарная группа[ \t]{1,3}\"(\\R{1,50})\""

#define		RULES_PATH	"rules.ini" //"c:\\rules.ini"

#include "greta/regexpr2.h"
#include <string>
#include <vector>

using namespace std;

bool isspace1( char c );
int StrCount( string  str );
string TakeWord( int num, string oldStr);
string toLowWithE( string str );
int strcmpe( string str, string str1 );
int StrCount1( string strin );

// Базовый класс правила
class CRule
{
protected:
	int	opts;
	string	patternStr;
public:
	int getOpts() {return opts;};
	string getPatternStr() {return patternStr;};
	~CRule() {};
};

// Правило на одно склонение
class COneCaseRule: public CRule
{
	protected:
	string	replaceStr;
	public:
	string getReplaceStr() {return replaceStr;};
	COneCaseRule(int opt, string pat, string rep) 
	{
		opts = opt;
		patternStr = pat;
		replaceStr = rep;
	};
};

// Правило на все склонения
class	CCommonCaseRule: public CRule
{
	protected:
	string	genetive;
	string	dative;
	string	accusative;
	string	instrumental;
	string	instrumental2;
	string	prepositional;
	public:
	string getCase(int mode) 
	{
		if (!(mode&ALL^GENITIVE)) return genetive;
		if (!(mode&ALL^DATIVE))	return dative;
		if (!(mode&ALL^ACCUSATIVE)) return accusative;
		if (!(mode&ALL^INSTRUMENTAL)) return instrumental;
		if (!(mode&ALL^INSTRUMENTAL2)) return instrumental;
		if (!(mode&ALL^PREPOSITIONAL)) return prepositional;
		return string("errorr");
	};
	string getDative() {};
	string getAccusative() {};
	string getInstrumental() {};
	string getPrepositional() {};
	CCommonCaseRule(int opt, string pat, string gen, string dat, string acc, string inst, string prep) 
	{
		opts = opt;
		patternStr = pat;
		genetive = gen;
		dative = dat;
		accusative = acc;
		instrumental = inst;
		prepositional = prep;
	};

};

// Правило на все склонения
class	CCommonCaseRule2: private CCommonCaseRule
{
public:
	string getCase(int mode) 
	{
		if (!(mode&ALL^GENITIVE)) return genetive;
		if (!(mode&ALL^DATIVE))	return dative;
		if (!(mode&ALL^ACCUSATIVE)) return accusative;
		if (!(mode&ALL^INSTRUMENTAL)) return instrumental;
		if (!(mode&ALL^INSTRUMENTAL2)) return instrumental2;
		if (!(mode&ALL^PREPOSITIONAL)) return prepositional;
		return string("errorr");
	};
}
;

// !!!!!!!!!! ПАРСЕР !!!!!!!!!!!!!
class REParser
{
protected:
	std::vector<COneCaseRule> Geni;
	std::vector<COneCaseRule> Dati;
	std::vector<COneCaseRule> Accu;
	std::vector<COneCaseRule> Inst;
	std::vector<COneCaseRule> Inst2;
	std::vector<COneCaseRule> Prep;
	std::vector<CCommonCaseRule> CRules;
	std::vector<COneCaseRule> Verb;
	std::vector<string> symbols;
public:   
	REParser() {};
	void	init();
	void	defrules();
	void	readrules(LPSTR fname);
	int		readOpts(string opts);
	int		readMod(string mode);
	string	TakePad(string in, int mode);
};