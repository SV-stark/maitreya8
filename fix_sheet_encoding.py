import os

path = 'src/jyotish/Sheet.cpp'

# Read file
try:
    with open(path, 'rb') as f:
        raw = f.read()
except FileNotFoundError:
    print(f"File not found: {path}")
    exit(1)

# Decode (latin-1 maps bytes directly to unicode code points 0-255)
content = raw.decode('latin-1')
lines = content.splitlines()

new_lines = []
modified = False

for line in lines:
    # Look for DEGREE_SYMBOL definition that uses a raw character (not escaped)
    # We assume the good one uses "\u00B0" (literal backslash u...)
    if '#define DEGREE_SYMBOL' in line and (r'\u00B0' not in line):
        print(f"Modifying line: {line}")
        new_lines.append(r'#define DEGREE_SYMBOL wxT( "\u00B0" );')
        modified = True
    else:
        new_lines.append(line)

if modified:
    # Write back as UTF-8
    with open(path, 'w', encoding='utf-8') as f:
        f.write('\n'.join(new_lines) + '\n')
    print("File updated and saved as UTF-8.")
else:
    print("No changes required.")
