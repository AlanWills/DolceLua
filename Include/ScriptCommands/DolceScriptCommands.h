#pragma once


namespace sol
{
  class state;
}

namespace Dolce
{
  class Dolce;
}

namespace Dolce::Lua::ScriptCommands
{
  void initialize(sol::state& state, Dolce& dolce);
}