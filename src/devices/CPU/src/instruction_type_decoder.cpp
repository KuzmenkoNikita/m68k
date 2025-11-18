#include <expected>
#include <instruction_decoder/instruction_type_decoder.h>

namespace m68k {

std::expected<InstructionType, DecodeError> InstructionTypeDecoder::decode(uint16_t opcodeValue)
{
    for(const auto params : opcodeTable_) {

        if((opcodeValue & params.mask) == params.pattern) {
            return params.type;
        }
    }

    return std::unexpected(DecodeError::INVALID_INSTRUCTION);
}

} // namespace m68k