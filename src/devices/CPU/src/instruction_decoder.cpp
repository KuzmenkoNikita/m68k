#include <instruction_decoder/instruction_decoder.h>
#include <instructions/instruction_params.h>

namespace m68k {

InstructionDecoder::InstructionDecoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : 
                                    bus_(std::move(bus))
                                    , typeDecoder_(std::make_unique<InstructionTypeDecoder>())
{

}

std::expected<Instruction, DecodeError> InstructionDecoder::decode(uint32_t pc) //NOLINT(*-identifier-length)
{
    auto readResult = bus_->read16(pc);
    if(!readResult){
        return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
    }

    auto instructionTypeResult = typeDecoder_->decode(readResult->data);
    if(!instructionTypeResult) {
        return std::unexpected(DecodeError::INVALID_INSTRUCTION);
    }

    switch(*instructionTypeResult) {

        case InstructionType::TST: {
            auto data = decodeTST(readResult->data, pc+2);
        } 

        default: {
            return std::unexpected(DecodeError::INVALID_INSTRUCTION);
        }
    }

    return std::unexpected(DecodeError::INVALID_INSTRUCTION);
}

std::expected<InstructionData::TSTInstructionData, DecodeError> InstructionDecoder::decodeTST(uint16_t opcode, uint32_t instructionDataAddr)
{
    InstructionData::TSTInstructionData instructionData;
    uint8_t sizeValue = (opcode & 0x00C0U) >> 6U;
    int a = 0;

    return instructionData;
}

} // namespace m68k