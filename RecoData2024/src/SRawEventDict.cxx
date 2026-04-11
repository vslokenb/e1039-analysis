// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIseaquestdIusersdIvslokendIdisplaced_rerecodIe1039mIanalysisdIRecoData2024dIsrcdISRawEventDict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "/seaquest/users/vsloken/displaced_rereco/e1039-analysis/RecoData2024/inc/SRawEvent.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_Hit(void *p = nullptr);
   static void *newArray_Hit(Long_t size, void *p);
   static void delete_Hit(void *p);
   static void deleteArray_Hit(void *p);
   static void destruct_Hit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Hit*)
   {
      ::Hit *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Hit >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("Hit", ::Hit::Class_Version(), "SRawEvent.h", 32,
                  typeid(::Hit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Hit::Dictionary, isa_proxy, 4,
                  sizeof(::Hit) );
      instance.SetNew(&new_Hit);
      instance.SetNewArray(&newArray_Hit);
      instance.SetDelete(&delete_Hit);
      instance.SetDeleteArray(&deleteArray_Hit);
      instance.SetDestructor(&destruct_Hit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Hit*)
   {
      return GenerateInitInstanceLocal(static_cast<::Hit*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::Hit*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_SRawEvent(void *p = nullptr);
   static void *newArray_SRawEvent(Long_t size, void *p);
   static void delete_SRawEvent(void *p);
   static void deleteArray_SRawEvent(void *p);
   static void destruct_SRawEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SRawEvent*)
   {
      ::SRawEvent *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SRawEvent >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("SRawEvent", ::SRawEvent::Class_Version(), "SRawEvent.h", 87,
                  typeid(::SRawEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SRawEvent::Dictionary, isa_proxy, 4,
                  sizeof(::SRawEvent) );
      instance.SetNew(&new_SRawEvent);
      instance.SetNewArray(&newArray_SRawEvent);
      instance.SetDelete(&delete_SRawEvent);
      instance.SetDeleteArray(&deleteArray_SRawEvent);
      instance.SetDestructor(&destruct_SRawEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SRawEvent*)
   {
      return GenerateInitInstanceLocal(static_cast<::SRawEvent*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::SRawEvent*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_SRawMCEvent(void *p = nullptr);
   static void *newArray_SRawMCEvent(Long_t size, void *p);
   static void delete_SRawMCEvent(void *p);
   static void deleteArray_SRawMCEvent(void *p);
   static void destruct_SRawMCEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SRawMCEvent*)
   {
      ::SRawMCEvent *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SRawMCEvent >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("SRawMCEvent", ::SRawMCEvent::Class_Version(), "SRawEvent.h", 259,
                  typeid(::SRawMCEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SRawMCEvent::Dictionary, isa_proxy, 4,
                  sizeof(::SRawMCEvent) );
      instance.SetNew(&new_SRawMCEvent);
      instance.SetNewArray(&newArray_SRawMCEvent);
      instance.SetDelete(&delete_SRawMCEvent);
      instance.SetDeleteArray(&deleteArray_SRawMCEvent);
      instance.SetDestructor(&destruct_SRawMCEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SRawMCEvent*)
   {
      return GenerateInitInstanceLocal(static_cast<::SRawMCEvent*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::SRawMCEvent*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr Hit::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Hit::Class_Name()
{
   return "Hit";
}

//______________________________________________________________________________
const char *Hit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Hit*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Hit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Hit*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Hit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Hit*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Hit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Hit*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr SRawEvent::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *SRawEvent::Class_Name()
{
   return "SRawEvent";
}

//______________________________________________________________________________
const char *SRawEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SRawEvent*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int SRawEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SRawEvent*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SRawEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SRawEvent*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SRawEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SRawEvent*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr SRawMCEvent::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *SRawMCEvent::Class_Name()
{
   return "SRawMCEvent";
}

//______________________________________________________________________________
const char *SRawMCEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SRawMCEvent*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int SRawMCEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SRawMCEvent*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SRawMCEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SRawMCEvent*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SRawMCEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SRawMCEvent*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void Hit::Streamer(TBuffer &R__b)
{
   // Stream an object of class Hit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Hit::Class(),this);
   } else {
      R__b.WriteClassBuffer(Hit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Hit(void *p) {
      return  p ? new(p) ::Hit : new ::Hit;
   }
   static void *newArray_Hit(Long_t nElements, void *p) {
      return p ? new(p) ::Hit[nElements] : new ::Hit[nElements];
   }
   // Wrapper around operator delete
   static void delete_Hit(void *p) {
      delete (static_cast<::Hit*>(p));
   }
   static void deleteArray_Hit(void *p) {
      delete [] (static_cast<::Hit*>(p));
   }
   static void destruct_Hit(void *p) {
      typedef ::Hit current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::Hit

//______________________________________________________________________________
void SRawEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class SRawEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(SRawEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(SRawEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SRawEvent(void *p) {
      return  p ? new(p) ::SRawEvent : new ::SRawEvent;
   }
   static void *newArray_SRawEvent(Long_t nElements, void *p) {
      return p ? new(p) ::SRawEvent[nElements] : new ::SRawEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_SRawEvent(void *p) {
      delete (static_cast<::SRawEvent*>(p));
   }
   static void deleteArray_SRawEvent(void *p) {
      delete [] (static_cast<::SRawEvent*>(p));
   }
   static void destruct_SRawEvent(void *p) {
      typedef ::SRawEvent current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::SRawEvent

//______________________________________________________________________________
void SRawMCEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class SRawMCEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(SRawMCEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(SRawMCEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SRawMCEvent(void *p) {
      return  p ? new(p) ::SRawMCEvent : new ::SRawMCEvent;
   }
   static void *newArray_SRawMCEvent(Long_t nElements, void *p) {
      return p ? new(p) ::SRawMCEvent[nElements] : new ::SRawMCEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_SRawMCEvent(void *p) {
      delete (static_cast<::SRawMCEvent*>(p));
   }
   static void deleteArray_SRawMCEvent(void *p) {
      delete [] (static_cast<::SRawMCEvent*>(p));
   }
   static void destruct_SRawMCEvent(void *p) {
      typedef ::SRawMCEvent current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::SRawMCEvent

namespace ROOT {
   static TClass *vectorlEHitgR_Dictionary();
   static void vectorlEHitgR_TClassManip(TClass*);
   static void *new_vectorlEHitgR(void *p = nullptr);
   static void *newArray_vectorlEHitgR(Long_t size, void *p);
   static void delete_vectorlEHitgR(void *p);
   static void deleteArray_vectorlEHitgR(void *p);
   static void destruct_vectorlEHitgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Hit>*)
   {
      vector<Hit> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Hit>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Hit>", -2, "vector", 389,
                  typeid(vector<Hit>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEHitgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Hit>) );
      instance.SetNew(&new_vectorlEHitgR);
      instance.SetNewArray(&newArray_vectorlEHitgR);
      instance.SetDelete(&delete_vectorlEHitgR);
      instance.SetDeleteArray(&deleteArray_vectorlEHitgR);
      instance.SetDestructor(&destruct_vectorlEHitgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Hit> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<Hit>","std::vector<Hit, std::allocator<Hit> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<Hit>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEHitgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<Hit>*>(nullptr))->GetClass();
      vectorlEHitgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEHitgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEHitgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<Hit> : new vector<Hit>;
   }
   static void *newArray_vectorlEHitgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<Hit>[nElements] : new vector<Hit>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEHitgR(void *p) {
      delete (static_cast<vector<Hit>*>(p));
   }
   static void deleteArray_vectorlEHitgR(void *p) {
      delete [] (static_cast<vector<Hit>*>(p));
   }
   static void destruct_vectorlEHitgR(void *p) {
      typedef vector<Hit> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<Hit>

namespace {
  void TriggerDictionaryInitialization_SRawEventDict_Impl() {
    static const char* headers[] = {
"/seaquest/users/vsloken/displaced_rereco/e1039-analysis/RecoData2024/inc/SRawEvent.h",
nullptr
    };
    static const char* includePaths[] = {
"/seaquest/users/vsloken/displaced_rereco/e1039-analysis/RecoData2024/inc",
"/exp/seaquest/app/software/osg/software/e1039/share/20250519/root/include/",
"/seaquest/users/vsloken/displaced_rereco/e1039-analysis/RecoData2024/build/src/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "SRawEventDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$/seaquest/users/vsloken/displaced_rereco/e1039-analysis/RecoData2024/inc/SRawEvent.h")))  Hit;
class __attribute__((annotate("$clingAutoload$/seaquest/users/vsloken/displaced_rereco/e1039-analysis/RecoData2024/inc/SRawEvent.h")))  SRawEvent;
class __attribute__((annotate("$clingAutoload$/seaquest/users/vsloken/displaced_rereco/e1039-analysis/RecoData2024/inc/SRawEvent.h")))  SRawMCEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "SRawEventDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "/seaquest/users/vsloken/displaced_rereco/e1039-analysis/RecoData2024/inc/SRawEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"Hit", payloadCode, "@",
"SRawEvent", payloadCode, "@",
"SRawMCEvent", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("SRawEventDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_SRawEventDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_SRawEventDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_SRawEventDict() {
  TriggerDictionaryInitialization_SRawEventDict_Impl();
}
