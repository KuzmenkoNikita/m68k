#pragma once
#include <cpu/internal/instruction_params.h>
#include <string_view>

namespace m68k {

template <class RealInstruction>
class InstructionBase {
public:
    [[nodiscard]] constexpr std::string_view name() const
    {
        return static_cast<RealInstruction*>(this)->nameImpl();
    }

    [[nodiscard]] constexpr InstructionType type() const
    {
        return RealInstruction::type;
    }

    [[nodiscard]] constexpr bool hasData() const
    {
        return RealInstruction::hasData;
    }

    [[nodiscard]] constexpr size_t length() const
    {
        return RealInstruction::length;
    }

    [[nodiscard]] constexpr auto data() const requires (RealInstruction::hasData)
    {
        return static_cast<const RealInstruction*>(this)->dataImpl();
    }
};

} // namespace m68k



