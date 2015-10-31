#include "TestModule.h"
using namespace std;


void TestModule::ShowCurrentInfo()
{
	cout << "info" << endl;
}

TestModule::TestModule( Strategy* str, 
	int physician_num, const int maxTime, const char * fileName) :m_maxTime(maxTime),  mainStrategy(str)
{
	community = new PatientGenerater(fileName);
	singletonHospital = Hospital::getInstance();
	report = new Reporter();
	m_time = 0;
};


TestModule::~TestModule()
{
	delete community;
}

void TestModule::processing()
{
	//New Patient Generating
}

void TestModule::Run()
{
	cout << "--------Test Start---------" << endl;

	while (m_time <= m_maxTime )
	{
		cout << "**** Time:" << m_time << " ****"<<endl;
		
		community->SendPatients(m_time, singletonHospital);
		
		//hospital select patient
		singletonHospital->Select(mainStrategy);

		//some patients are waiting, starving, treating, expiring....
		singletonHospital->timeSpend();
		
		if (community->isAllSended() && singletonHospital->isEmpty()){
			cout << "No more Patient." << endl;
			singletonHospital->makeReport(report);
			cout << endl;
			break;
		}

		cout << endl;
		m_time++;
	}
	if (m_time > m_maxTime)
	{
		cout << "Max time over." << endl;
		singletonHospital->makeReport(report);
		cout << endl;
	}

	cout << "--------Test Finished---------" << endl;
}
