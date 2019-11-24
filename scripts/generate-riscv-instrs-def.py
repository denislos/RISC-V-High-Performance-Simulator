#! /bin/bash/env python3

import argparse
import yaml


def main():
    arg_parser = argparse.ArgumentParser(description = 'Generate RISC-V instr definionts from YAML')
    arg_parser.add_argument('input_file', help='Input YAML RISC-V definition file')
    arg_parser.add_argument('output_file', help='Output file with generated definitions of RISC-V instructions')
    
    args = arg_parser.parse_args()

    mnemonics = []

    with open(args.input_file, 'r') as stream:
        input_data = yaml.safe_load(stream)
        mnemonics = [instr_desc['mnemonic'] for instr_desc in input_data['instructions']]

    with open(args.output_file, 'w') as stream:
        definitions = [f'DEFINSTR({mnemonic.replace(".", "_")}, \"{mnemonic}\")' for mnemonic in mnemonics]
        stream.write('\n'.join(definitions))

if __name__ == '__main__':
    main()