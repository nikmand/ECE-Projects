/******************************************************************************
 *  CVS version:
 *     $Id: symbol.h,v 1.1 2003/05/13 22:21:01 nickie Exp $
 ******************************************************************************
 *
 *  C header file : symbol.h
 *  Project       : PCL Compiler
 *  Version       : 1.0 alpha
 *  Written by    : Nikolaos S. Papaspyrou (nickie@softlab.ntua.gr)
 *  Date          : May 14, 2003
 *  Description   : Generic symbol table in C
 *
 *  Comments: (in Greek iso-8859-7)
 *  ---------
 *  ������ �������� �����������.
 *  ����� ������������ ��������� ��� ��������� �����������.
 *  ������ ����������� ������������ ��� �����������.
 *  ���������� ����������� ����������
 */


#ifndef __SYMBOL_H__
#define __SYMBOL_H__


/* ---------------------------------------------------------------------
   -------------------------- ����� bool -------------------------------
   --------------------------------------------------------------------- */

#include <stdbool.h>

/*
 *  �� �� �������� include ��� ������������� ��� ��� ���������
 *  ��� C ��� ��������������, �������������� �� �� �� ��������:
 */

#if 0
typedef enum { false=0, true=1 } bool;
#endif


/* ---------------------------------------------------------------------
   ------------ ������� �������� ��� ������ �������� -------------------
   --------------------------------------------------------------------- */

#define START_POSITIVE_OFFSET 8     /* ������ ������ offset ��� �.�.   */
#define START_NEGATIVE_OFFSET 0     /* ������ �������� offset ��� �.�. */
#define MAX_LABELS 20

/* ---------------------------------------------------------------------
   --------------- ������� ����� ��� ������ �������� -------------------
   --------------------------------------------------------------------- */

/* ����� ��������� ��� ��� ��������� ��� �������� */

typedef int           RepInteger;         /* ��������                  */
typedef unsigned char RepBoolean;         /* ������� �����             */
typedef char          RepChar;            /* ����������                */
typedef long double   RepReal;            /* �����������               */
typedef const char *  RepString;          /* �������������             */
typedef unsigned long int HashType;

/*
struct Label_Array{
	HashType key;	
	int Line_Pos;	
};

struct LF_SET{
	struct Label_Array* Labels_Set;
	int label_cnt;
	char * function_name;
};
*/

/* ����� ��������� ��� ������������� ����������� */
typedef struct Type_tag * Type;

struct Type_tag {
    enum {                               /***** �� ����� ��� ����� ****/
       TYPE_VOID,                        /* ����� ����� ������������� */
       TYPE_INTEGER,                     /* ��������                  */
       TYPE_BOOLEAN,                     /* ������� �����             */
       TYPE_CHAR,                        /* ����������                */
       TYPE_REAL,                        /* �����������               */
       TYPE_ARRAY,                       /* ������� ������� ��������  */
       TYPE_IARRAY,                      /* ������� �������� �������� */
       TYPE_POINTER                      /* �������                   */
    } kind;
    Type           refType;              /* ����� ��������            */
    RepInteger     size;                 /* �������, �� ����� ������� */
    unsigned int   refCount;             /* �������� ��������         */
};


/* ����� �������� ��� ������ �������� */

typedef enum {            
   ENTRY_VARIABLE,                       /* ����������                 */
   ENTRY_CONSTANT,                       /* ��������                   */
   ENTRY_FUNCTION,                       /* �����������                */
   ENTRY_PARAMETER,                      /* ���������� �����������     */
   ENTRY_TEMPORARY,                       /* ���������� ����������      */
   ENTRY_LABEL
} EntryType;


/* ����� ���������� ���������� */

typedef enum {            
   PASS_BY_VALUE,                        /* ���' ����                  */
   PASS_BY_REFERENCE                     /* ���' �������               */
} PassMode;

PassMode brf(int i);

/* ����� �������� ���� ������ �������� */

typedef struct SymbolEntry_tag SymbolEntry;

struct SymbolEntry_tag {
   const char   * id;                 /* ����� ��������������          */
   EntryType      entryType;          /* ����� ��� ��������            */
   unsigned int   nestingLevel;       /* ����� �����������             */
   unsigned int   hashValue;          /* ���� ���������������          */
   SymbolEntry  * nextHash;           /* ������� ������� ���� �.�.     */
   SymbolEntry  * nextInScope;        /* ������� ������� ���� �������� */

   union {                            /* ������� �� ��� ���� ��������: */
      struct {
	char name[256];
	int line;
      }eLabel;

      struct {                                /******* ��������� *******/
         Type          type;                  /* �����                 */
         bool	   dynamic;        /* = False */ 	
	 bool has_reference;
	 struct SymbolEntry_tag *reference;
	 int           offset;                /* Offset ��� �.�.       */
      }eVariable;

      struct {                                /******** ������� ********/
         Type          type;                  /* �����                 */
         union {                              /* ���� */
            RepInteger vInteger;              /*    �������            */
            RepBoolean vBoolean;              /*    ������             */
            RepChar    vChar;                 /*    ����������         */
            RepReal    vReal;                 /*    ����������         */
            RepString  vString;               /*    ������������       */
         } value;
      } eConstant;

      struct {                                /******* ��������� *******/
	 bool          isForward;             /* ������ forward        */
         SymbolEntry * firstArgument;         /* ����� ����������      */
         SymbolEntry * lastArgument;          /* ��������� ����������  */
         Type          resultType;            /* ����� �������������   */
         enum {                               /* ��������� ����������  */
             PARDEF_COMPLETE,                    /* ������ �������     */
             PARDEF_DEFINE,                      /* �� ���� �������    */
             PARDEF_CHECK                        /* �� ���� �������    */
         } pardef;
         int           firstQuad;             /* ������ �������        */
      } eFunction;

      struct {                                /****** ���������� *******/
         Type          type;                  /* �����                 */
         int           offset;                /* Offset ��� �.�.       */
         PassMode      mode;                  /* ������ ����������     */
         bool has_reference;
	 struct SymbolEntry_tag *reference;
	bool dynamic;
         SymbolEntry * next;                  /* ������� ����������    */
      } eParameter;

      struct {                                /** ��������� ��������� **/
         Type          type;                  /* �����                 */
         int           offset;                /* Offset ��� �.�.       */
         int           number;
      } eTemporary;

   } u;                               /* ����� ��� union               */
};


/* ����� ������� �������� ��� ���������� ���� ���� �������� */

typedef struct Scope_tag Scope;

struct Scope_tag {
    unsigned int   nestingLevel;             /* ����� �����������      */
    unsigned int   negOffset;                /* ������ �������� offset */
    Scope        * parent;                   /* ������������ ��������  */
    SymbolEntry  * entries;                  /* ������� ��� ���������  */
    bool 	   infor;		     /* flag an vriskomaste se loop */
};


/* ����� ���������� ���� ������ �������� */

typedef enum {
    LOOKUP_CURRENT_SCOPE,
    LOOKUP_ALL_SCOPES
} LookupType;


/* ---------------------------------------------------------------------
   ------------- ��������� ���������� ��� ������ �������� --------------
   --------------------------------------------------------------------- */

extern Scope        * currentScope;       /* �������� ��������         */
extern unsigned int   quadNext;           /* ������� �������� �������� */
extern unsigned int   tempNumber;         /* �������� ��� temporaries  */

extern const Type typeVoid;
extern const Type typeInteger;
extern const Type typeBoolean;
extern const Type typeChar;
extern const Type typeReal;


/* ---------------------------------------------------------------------
   ------ ��������� ��� ����������� ��������� ��� ������ �������� ------
   --------------------------------------------------------------------- */

void          initSymbolTable    (unsigned int size);
void          destroySymbolTable (void);

void          openScope          (void);
void          closeScope         (void);

SymbolEntry * newVariable        (const char * name, Type type);
SymbolEntry * newConstant        (const char * name, Type type, ...);
SymbolEntry * newFunction        (const char * name);
SymbolEntry * newParameter       (const char * name, Type type,
                                  PassMode mode, SymbolEntry * f);
SymbolEntry * newTemporary       (Type type);
SymbolEntry * newLabel (const char * name, int line);

void          forwardFunction    (SymbolEntry * f);
void          endFunctionHeader  (SymbolEntry * f, Type type);
void          destroyEntry       (SymbolEntry * e);
SymbolEntry * lookupEntry        (const char * name, LookupType type,bool err);

Type          typeArray          (RepInteger size, Type refType);
Type          typeIArray         (Type refType);
Type          typePointer        (Type refType);
void          destroyType        (Type type);
unsigned int  sizeOfType         (Type type);
bool          equalType          (Type type1, Type type2);
void          printType          (Type type);
void          printMode          (PassMode mode);
bool cmp_sym_root(SymbolEntry *s,SymbolEntry *p);
/*
HashType PJW_hash (const char * key);
int search_label(HashType tok);
void init_label_set();
void close_label_set(char * name);
int add_label(const char * key);
*/
void printSymbolTable ();


#endif
