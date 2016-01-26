// sspDeviceManager.h

#ifndef SSP_DEVICEPOOL
#define SSP_DEVICEPOOL

#include "sspDefines.h"
#include "sspDevice.h"
#include <vector>

// Class sspDeviceManager is implemented as a Singleton pattern
class sspDeviceManager : public sspIObase
{
private:
	std::vector<sspDeviceGroup*> m_pGroups;
	static sspDeviceManager* m_pInstance;
	static bool m_bDestroyed;

public:
	static sspDeviceManager& Instance();

	void Serialize(CArchive& ar);

	sspDeviceGroup* getGroup(SSP_DEVICES nType) {return m_pGroups[nType];}
	sspDeviceGroup* operator[](SSP_DEVICES nType) {return getGroup(nType);}

	void printASCII(std::ofstream& outStr);
	bool verify(std::ofstream& outStr, int& nErrors, int& nWarnings);

	bool initialize(LPVOID hWnd);
	bool start();
	bool stop();
	bool terminate();
	void clearContents();

private:
	sspDeviceManager();
	sspDeviceManager(const sspDeviceManager&);
	sspDeviceManager& operator=(const sspDeviceManager&);
	~sspDeviceManager();

	static void create();
	static void onDeadReference();
};

#endif