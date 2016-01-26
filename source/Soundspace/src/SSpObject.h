// SSpObject.h: interface for the SSpObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SSPOBJECT_H__C93B5D85_1AB6_11D7_8B6A_444553540000__INCLUDED_)
#define AFX_SSPOBJECT_H__C93B5D85_1AB6_11D7_8B6A_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "sspDefines.h"
#include <fstream>

/************************************************************************
**
** sspObject
**
** The basic I/O object
** Includes print and verification
**  - will eventually remove the dependency on CObject::Serialize
**
*************************************************************************/

class sspIObase : public CObject
{
protected:
	sspString	m_strName;	// Name of object (** now found in pool **)

public:
	sspIObase() {}
	sspIObase(const sspIObase& iob);
	sspIObase& operator= (const sspIObase& iob);
	virtual ~sspIObase() {}

	const sspString& getName() const {return m_strName;}
	void			 setName(const sspString& strName) {m_strName = strName;}

	// Load from binary file (will substitute serialize)
	virtual void load(std::ifstream& outStr) {}

	// Save to binary file (will substitute serialize)
	virtual void save(std::ofstream& outStr) {}

	// Print to ASCII file
	virtual void printASCII(std::ofstream& outStr) = 0;

	// Verify correctness and write errors and warnings to ASCII file 
	// - returns false if there are errors or warnings
	virtual bool verify(std::ofstream& outStr, int& nErrors, int& nWarnings) = 0;

protected:
	void printError(std::ofstream& outStr, const sspString& txt, int& nCount);
	void printWarning(std::ofstream& outStr, const sspString& txt, int& nCount);
};

/************************************************************************
**
** sspObject
**
** The basic object
** Includes type and index information
**
*************************************************************************/

class sspObject : public sspIObase  
{
protected:
	short		m_nClass;	// One of the SSP_CLASSES (see sspDefines.h)
	short		m_nType;	// One of SSP_VALUES, SSP_CONDITIONALS or SSP_PLAYOBJECTS (depending on class)
	int			m_nIndex;	// Index in the respective pool (unique pr. class)

public:
	sspObject(short nClass, short nType) : m_nClass(nClass), m_nType(nType) {}
	sspObject(const sspObject& obj);
	sspObject& operator= (const sspObject& obj);
	virtual ~sspObject() {}

	short		getClass() const {return m_nClass;}
	short		getType() const {return m_nType;}
	int			getIndex() const {return m_nIndex;}

	void	setClass(short nClass) {m_nClass = nClass;}
	void	setType(short nType) {m_nType = nType;}
	void	setIndex(int nIndex) {m_nIndex = nIndex;}
};

#endif // !defined(AFX_SSPOBJECT_H__C93B5D85_1AB6_11D7_8B6A_444553540000__INCLUDED_)
