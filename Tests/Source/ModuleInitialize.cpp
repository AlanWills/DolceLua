#include "TestUtils.h"
#include "Assert/Assert.h"
#include "Assert/NullAsserter.h"
#include "Lua/LuaState.h"


namespace TestDolceLua
{
  //------------------------------------------------------------------------------------------------
  TEST_MODULE_INITIALIZE(TestDolceLua_Initialize)
  {
    // Issues with unique_ptrs over dll boundaries so have to do this in the test project
    Celeste::Assertion::setAsserter(std::make_unique<Celeste::NullAsserter>());

    Celeste::Path celesteLuaScripts(Celeste::Directory::getExecutingAppDirectory(), UPDIR_STRING, UPDIR_STRING, UPDIR_STRING,
      "Celeste", "CelesteLua", "Resources", "Scripts", "?.lua;");
    Celeste::Lua::LuaState::appendToLuaPackagePath(celesteLuaScripts);
  }
}