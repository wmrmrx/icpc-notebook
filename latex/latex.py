info = {"code": "code/", "template": "latex/template.tex", "contents": "latex/contents.txt", "insert": "#add here"}
languages = {"cpp": "c++", "vimrc": "vim"}

# return file string
def readFile(filename):
	with open(filename) as f:
		return f.read()

def getSections():
	index = open(info['contents'], "r")
	sections = []

	cur_section = []
	for line in index:
		if len(line) == 1 or line[0] == '#':
			pass
		elif line[0] == '[':
			if len(cur_section) > 0:
				sections.append(cur_section)
			section_name = line[1:-2]
			cur_section = [section_name, []]
		else:
			cur_section[1].append(line[0:-1].split(';'))
	if len(cur_section) > 0:
		sections.append(cur_section)
	return sections

def getLanguage(filename):
	extension = filename.split('.')[-1]
	if extension in languages:
		return languages[extension]
	return ""

def getTex():
	sections = getSections()

	template = open(info['template'], "r")
	template = readFile(info['template']).split(info['insert'])

	latex = ""

	for section in sections:
		latex += "\\section{" + section[0] + "}\n"
		for subsection in section[1]:
			latex += "\\subsection{" + subsection[1] + "}\n"
			latex += "\\begin{minted}{"+getLanguage(subsection[0])+"}\n" + readFile(info['code'] + subsection[0]) + "\\end{minted}\n"

	latex = template[0] + latex + template[1]
	
	print(latex)

getTex()