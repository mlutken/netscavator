#include "mozilla/ModuleUtils.h"
#include "CSpecialThing.h"

////////////////////////////////////////////////////////////////////////
// Define the contructor function for the object MyComponent
//
// What this does is defines a function MyComponentConstructor which we
// will specific in the nsModuleComponentInfo table. This function will
// be used by the generic factory to create an instance of MyComponent.
//
// NOTE: This creates an instance of MyComponent by using the default
//		 constructor MyComponent::MyComponent()
//
NS_GENERIC_FACTORY_CONSTRUCTOR(CSpecialThing)

// The following line defines a kMY_COMPONENT_CID CID variable.
NS_DEFINE_NAMED_CID(SPECIALTHING_CID);

// Build a table of ClassIDs (CIDs) which are implemented by this module. CIDs
// should be completely unique UUIDs.
// each entry has the form { CID, service, factoryproc, constructorproc }
// where factoryproc is usually NULL.
static const mozilla::Module::CIDEntry kSpecialThingCIDs[] = {
    { &kSPECIALTHING_CID, false, NULL, CSpecialThingConstructor },
    { NULL }
};

// Build a table which maps contract IDs to CIDs.
// A contract is a string which identifies a particular set of functionality. In some
// cases an extension component may override the contract ID of a builtin gecko component
// to modify or extend functionality.
static const mozilla::Module::ContractIDEntry kSpecialThingContracts[] = {
    { SPECIALTHING_CONTRACTID, &kSPECIALTHING_CID },
    { NULL }
};

// Category entries are category/key/value triples which can be used
// to register contract ID as content handlers or to observe certain
// notifications. Most modules do not need to register any category
// entries: this is just a sample of how you'd do it.
// @see nsICategoryManager for information on retrieving category data.
static const mozilla::Module::CategoryEntry kSpecialThingCategories[] = {
    { "my-category", "my-key", SPECIALTHING_CONTRACTID },
    { NULL }
};

static const mozilla::Module kSpecialThingModule = {
    mozilla::Module::kVersion,
    kSpecialThingCIDs,
    kSpecialThingContracts,
    kSpecialThingCategories
};

// The following line implements the one-and-only "NSModule" symbol exported from this
// shared library.
NSMODULE_DEFN(SpecialThingModule) = &kSpecialThingModule;
