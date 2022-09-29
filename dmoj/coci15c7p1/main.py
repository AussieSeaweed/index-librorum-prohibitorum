s = input()
level = 0
lines = []

for char in s:
    if char == '{':
        lines.append(' ' * (2 * level) + char)
        level += 1
    elif char == '}':
        level -= 1
        lines.append(' ' * (2 * level) + char)
    elif char == ',':
        lines[-1] += char
    else:
        if lines[-1][-1] in (',', '{'):
            lines.append(' ' * (2 * level) + char)
        else:
            lines[-1] += char

print('\n'.join(lines))