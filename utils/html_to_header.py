content = None
with open("./page.html", 'r') as f:
    content = f.read()
    # print(f'Contenido:\n{content}')

if content is None:
    print("Content was None!!")

with open("../pageHtml.h", 'w+') as f:
    f.write('#ifndef _PAGE_HTML_H\n#define _PAGE_HTML_H\nconst char index_html[] PROGMEM =  "')
    lines = content.split("\n")
    num_lines = len(lines)
    counter = 0
    for line in lines:
        line2 = line.replace(f'"', f'\\"')
        if counter < num_lines - 2:
            #f.write(f'  "{line2}" \\\n')
            f.write(f'{line2}\\n\ \n')
        else:
            if counter != num_lines - 1:
                #f.write(f'  "{line2}";')
                f.write(f'{line2}";')
        counter = counter + 1
    f.write("\n\n#endif")
