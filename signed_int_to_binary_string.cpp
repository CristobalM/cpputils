//
// Created by Cristobal Miranda, 2020
//

#include "cxxopts/cxxopts.hpp"

struct command_line_input {
  int signed_int_input;
  bool sep_8_bits;
};

command_line_input parse_command_line_input(int argc, char **argv) {
  cxxopts::Options options("signed_int_to_binary_string",
                           "Gives the string representation of a signed integer");

  struct SummaryOptions {
    std::string option, description;
    std::shared_ptr<cxxopts::Value> value;
  };

  static const std::string SIGNED_INT = "signed_int";
  static const std::string SIGNED_INT_SHORT = "s";

  static const std::string SEP_8_BITS = "sep_8";
  static const std::string SEP_8_BITS_SHORT = "8";


  std::vector<SummaryOptions> opts = {
          {SIGNED_INT_SHORT + "," + SIGNED_INT, "Signed integer", cxxopts::value<int>()},
          {SEP_8_BITS_SHORT + "," + SEP_8_BITS, "Separate each 8 bits",
                                                                  cxxopts::value<bool>()->default_value("false")
          }
  };

  auto acc_opts = options.add_options();
  for (auto &opt : opts) {
    acc_opts(opt.option, opt.description, opt.value);
  }

  std::unique_ptr<cxxopts::ParseResult> result_opt_ptr;

  try {
    result_opt_ptr = std::make_unique<cxxopts::ParseResult>(options.parse(argc, argv));
  }
  catch (const cxxopts::argument_incorrect_type &e) {
    throw std::runtime_error("Invalid input: type error\nReason: " + std::string(e.what()));
  }

  auto &result_opt = *result_opt_ptr;


  if (result_opt[SIGNED_INT].count() < 1) {
    throw std::runtime_error(SIGNED_INT + " option is missing. Please enter the signed integer");
  }

  auto signed_int_input = result_opt[SIGNED_INT].as<int>();
  auto sep_8_bits = result_opt[SEP_8_BITS].as<bool>();


  return {
          .signed_int_input = signed_int_input,
          .sep_8_bits = sep_8_bits
  };
}

int main(int argc, char **argv) {
  command_line_input command_line_input_result = parse_command_line_input(argc, argv);

  int signed_int_input = command_line_input_result.signed_int_input;
  bool sep_8_bits = command_line_input_result.sep_8_bits;

  auto unsigned_int_input = (unsigned int) signed_int_input;

  std::stringstream string_stream;
  auto bits_count = sizeof(signed_int_input) * 8;
  for (auto bit_pos = 0; bit_pos < bits_count; bit_pos++) {
    unsigned int current_mask = (1u << (bits_count - bit_pos - 1));
    unsigned int masked = unsigned_int_input & current_mask;
    unsigned int shifted = masked >> (bits_count - bit_pos - 1);
    string_stream << shifted;
    if(sep_8_bits && (bit_pos+1) % 8 == 0){
      string_stream << " ";
    }
  }
  std::cout << string_stream.str() << std::endl;
}