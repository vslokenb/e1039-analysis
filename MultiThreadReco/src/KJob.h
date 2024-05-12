#ifndef _KJOB_H_
#define _KJOB_H_

#include <GlobalConsts.h>
#include <geom_svc/GeomSvc.h>

#include <list>
#include <map>
#include <queue>
#include <new>

#include <TString.h>
#include <TRandom.h>
#include <TClonesArray.h>
#include <TStopwatch.h>
#include <TThread.h>
#include <TSemaphore.h>
#include <TMutex.h>
#include <TCondition.h>

#include <ktracker/EventReducer.h>
#include <ktracker/SRawEvent.h>
#include <ktracker/TriggerAnalyzer.h>
#include <ktracker/KalmanFastTracking.h>
#include <ktracker/UtilSRawEvent.h>

//#include <interface_main/SQHit.h>
//#include <interface_main/SQHit_v1.h>
//#include <interface_main/SQHitMap_v1.h>
//#include <interface_main/SQHitVector_v1.h>
//#include <interface_main/SQEvent_v1.h>
//#include <interface_main/SQRun_v1.h>
//#include <interface_main/SQSpill_v1.h>
//#include <interface_main/SQSpillMap_v1.h>
//#include <interface_main/SQTrackVector_v1.h>

enum KJobStatus {STARTED, RUNNING, HALTED, COMPLETE};
enum KJobQueueStatus {UNINITIALIZED, INITIALIZED, OPEN, FULL};

class KScheduler;
//class SQEvent;
//class SQHitMap;
//class SQHitVector;

class KJob {
    static int verb;
    
public:
    KJob(int jobId, SRawEvent* evPtr, KScheduler* universe, bool copy);
    KJob(bool poisoned);
    ~KJob();

    static void Verbose(const int a) { verb = a; }
    static int  Verbose() { return verb; }

    //TODO needs a mutex     // TMUTEX 
    //KJobStatus getJobStatus();
    int jobId;
    KScheduler* universe;
    int nTracklets = 0;
    bool isPoison;
    // TODO probably dont need a jobmutex
    TMutex* jobMutex;
    TStopwatch* jobTimer;
    SRawEvent* evData;

    // tracklets
    TClonesArray* tracklets; 

    SRecEvent* recEvData;
    KJobStatus p_JobStatus;
};

#endif 
