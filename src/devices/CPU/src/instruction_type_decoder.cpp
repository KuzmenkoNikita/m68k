#include <expected>
#include <instruction_decoder/instruction_type_decoder.h>
#include <bit>
#include <optional>


namespace m68k {

namespace {

struct Decision {
    InstructionType type;
    int maskPopBitsCount;
};

}//namespace


std::expected<InstructionType, DecodeError> InstructionTypeDecoder::decode(uint16_t opcodeValue) const
{
    std::optional<Decision> bestDecision;

    bool hasDuplicate = false;
    for(const auto& candidate : opcodeTable_) {

        if((opcodeValue & candidate.mask) != candidate.pattern) {
            continue;
        }

        const auto popBitsCount = std::popcount(candidate.mask);

        if(!bestDecision || popBitsCount > bestDecision->maskPopBitsCount) {
            bestDecision = Decision{.type=candidate.type, .maskPopBitsCount=popBitsCount};
            hasDuplicate = false;
        } else if (popBitsCount == bestDecision->maskPopBitsCount && bestDecision->type != candidate.type) {
            hasDuplicate = true;
        }

    }

    if(!bestDecision || hasDuplicate) {
        return std::unexpected(DecodeError::INVALID_INSTRUCTION);
    }

    return bestDecision->type;
}

} // namespace m68k